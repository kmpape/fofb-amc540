#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include <c6x.h>
#include <ti/drv/pcie/soc/pcie_soc.h>
#include <ti/csl/csl_bootcfgAux.h>
#include <ti/csl/csl_xmcAux.h>
#include <ti/csl/csl_serdes_pcie.h>
#include <ti/csl/csl_pscAux.h>
#include <ti/csl/csl_chip.h>
#include <ti/sdo/edma3/drv/sample/bios6_edma3_drv_sample.h>
#include <ti/csl/csl_cache.h>
#include <ti/sysbios/BIOS.h>

/* Configuration */
#include "fofb_config.h"

/* IMC */
#if (IMC_CONTROL == 1)
#include "imc/DTF_IMC_DI.h"
#include "imc/IMC_DI_ctr.h"
#include "imc/IMC_transfer.h"
#endif

/* IMC */
#if (GSVD_CONTROL == 1)
#include "gsvd/GSVD_ctr.h"
#include "gsvd/GSVD_transfer.h"
#endif

/* MPC */
#if (MPC_CONTROL == 1)
#include "mpc/MPC_ctr.h"
#include "mpc/MPC_transfer.h"
#include "mpc/fast_gradient_method.h"
#endif

/* Utilities */
#include "utils/pcie_sample.h"
#include "utils/libQDMA.h"
#include "utils/timing_utils.h"
#include "utils/pcie_defs.h"
#include "utils/pcie_cfg.h"
#include "utils/gpio_utils.h"
#include "utils/ipc_utils.h"
#include "utils/cache_utils.h"

/*
 * Pointer offset for read or write. Should match settings on AMC540.
 */
const int BRAM_offset = 0x3000/4; // points to address 0x80003000

/*
 * BPM data comes in [nm] as integer.
 */
#pragma DATA_SECTION(pcie_read_buffer, ".dstBufSec")
#pragma DATA_ALIGN(pcie_read_buffer, 256) // TI way of aligning
volatile LIBQDMA_ARR_TYPE pcie_read_buffer[ARRAY_LEN_READ];

/*
 * Corrector data is sent in [A]*SCALING_FACTOR_WRITE as integer. Must be divided by SCALING_FACTOR_WRITE on PMCs.
 */
#pragma DATA_SECTION(pcie_write_buffer, ".dstBufSec")
#pragma DATA_ALIGN(pcie_write_buffer, 256) // TI way of aligning
volatile LIBQDMA_ARR_TYPE pcie_write_buffer[ARRAY_LEN_WRITE];

/*
 * Processor ID required for IPC
 */
#pragma DATA_ALIGN(selfId, CACHE_L1D_LINESIZE)
#pragma DATA_SECTION(selfId, ".local_data")
Uint32 volatile selfId;

int counter = 0;
void pcie_loop (void)
{
    int i;
    int read_errors = 0;
    int write_errors = 0;
    LIBQDMA_STATUS QDMAresult;
    volatile uint32_t *fpga_array;

    /* Config GPIO directions */
    config_GPIO();

    /* Setup PCIe and assign pointer */
    fpga_array = pcie_init_all(BRAM_offset);
    memset((LIBQDMA_ARR_TYPE *)pcie_read_buffer, 0, ARRAY_LEN_READ*sizeof(LIBQDMA_ARR_TYPE));

    /* Initialize DMA transfer */
    QDMAresult = LIBQDMA_init_AB(CHUNK_LEN_READ, CHUNK_NUM_READ,
                    (LIBQDMA_ARR_TYPE *)fpga_array,
                    (LIBQDMA_ARR_TYPE *)LIBQDMA_getGlobalAddr((LIBQDMA_ARR_TYPE *)pcie_read_buffer));


    /* Main loop */
    set_GPIO_out_to_0(GPIO_OUT_1);
    while (1)
    {
        /* Wait for FPGA */
        while (read_GPIO_in(GPIO_IN_1) != 1) {;}

        /* Indicate transfer */
        set_GPIO_out_to_1(GPIO_OUT_1);

        /* Trigger transfer, block until completion */
        tic();
        QDMAresult = LIBQDMA_trigger_and_wait();
        toc();
        tic();

        cache_invalidate((void *)pcie_read_buffer, ARRAY_BYTES_READ);

#if (IMC_CONTROL == 1)
        imc_float * float_meas = IMC_DI_get_input();
        read_errors = BPM_to_float((LIBQDMA_ARR_TYPE *)(&pcie_read_buffer[READ_WRITE_OFFSET]), float_meas);
        imc_float * corr_values = IMC_DI_ctr(); // calls parallel routines and invalidates cache
        if (read_GPIO_in(GPIO_IN_2) == 1) {
            write_errors = CM_to_int(corr_values, (LIBQDMA_ARR_TYPE *)(&pcie_write_buffer[READ_WRITE_OFFSET]));
        } else {
            DTF_IMC_DI_init();
            memset((LIBQDMA_ARR_TYPE *)pcie_write_buffer, 0, ARRAY_LEN_WRITE*sizeof(LIBQDMA_ARR_TYPE));
        }
        if ((read_errors > 0) || (write_errors > 0)) {
            memset((LIBQDMA_ARR_TYPE *)pcie_write_buffer, 0, ARRAY_LEN_WRITE*sizeof(LIBQDMA_ARR_TYPE));
        }
#elif (GSVD_CONTROL == 1)
        int restart_gsvd = (read_GPIO_in(GPIO_IN_2) == 0);
        read_errors = GSVD_BPM_to_float((LIBQDMA_ARR_TYPE *)(&pcie_read_buffer[READ_WRITE_OFFSET]), GSVD_get_input());
        gsvd_float * corr_values = GSVD_ctr(restart_gsvd); // calls parallel routines and invalidates cache
        if (restart_gsvd == 0) {
            write_errors = GSVD_CM_to_int(corr_values, (LIBQDMA_ARR_TYPE *)(&pcie_write_buffer[READ_WRITE_OFFSET]));
        } else {
            memset((LIBQDMA_ARR_TYPE *)pcie_write_buffer, 0, ARRAY_LEN_WRITE*sizeof(LIBQDMA_ARR_TYPE));
        }
        if ((read_errors > 0) || (write_errors > 0)) {
            memset((LIBQDMA_ARR_TYPE *)pcie_write_buffer, 0, ARRAY_LEN_WRITE*sizeof(LIBQDMA_ARR_TYPE));
        }
#elif (MPC_CONTROL == 1)
        int restart_mpc = (read_GPIO_in(GPIO_IN_2) == 0);
        read_errors = MPC_BPM_to_float((LIBQDMA_ARR_TYPE *)(&pcie_read_buffer[READ_WRITE_OFFSET]), MPC_get_input());
        fgm_float * corr_values = MPC_ctr(restart_mpc); // calls parallel routines and invalidates cache
        if (restart_mpc == 0) {
            write_errors = MPC_CM_to_int(corr_values, (LIBQDMA_ARR_TYPE *)(&pcie_write_buffer[READ_WRITE_OFFSET]));
        } else {
            memset((LIBQDMA_ARR_TYPE *)pcie_write_buffer, 0, ARRAY_LEN_WRITE*sizeof(LIBQDMA_ARR_TYPE));
        }
        if ((read_errors > 0) || (write_errors > 0)) {
            memset((LIBQDMA_ARR_TYPE *)pcie_write_buffer, 0, ARRAY_LEN_WRITE*sizeof(LIBQDMA_ARR_TYPE));
        }
#else // loopback
        if (read_GPIO_in(GPIO_IN_2) == 1) {
            int len_cpy = (ARRAY_LEN_READ > ARRAY_LEN_WRITE) ? ARRAY_LEN_WRITE : ARRAY_LEN_READ;
            for (i = 0; i < len_cpy; i++)
                pcie_write_buffer[i] = pcie_read_buffer[i];
        } else {
            memset((LIBQDMA_ARR_TYPE *)pcie_write_buffer, 0, ARRAY_LEN_WRITE*sizeof(LIBQDMA_ARR_TYPE));
        }
#endif

        cache_writeback((void *)pcie_write_buffer, ARRAY_BYTES_WRITE);

        /* Change transfer params -> write*/
        QDMAresult = LIBQDMA_change_transfer_params_AB(CHUNK_LEN_WRITE, CHUNK_NUM_WRITE,
                        (LIBQDMA_ARR_TYPE *)LIBQDMA_getGlobalAddr((LIBQDMA_ARR_TYPE *)pcie_write_buffer),
                        (LIBQDMA_ARR_TYPE *)fpga_array);

        toc();
#ifndef NO_PRINT
        print_timing_info(1, get_elapsed_ticks(), "PROCESS");
#endif

        /* Trigger transfer, block until completion */
        tic();
        QDMAresult = LIBQDMA_trigger_and_wait();
        toc();
#ifndef NO_PRINT
        print_timing_info(ARRAY_LEN_WRITE, get_elapsed_ticks(), "WRITE");
#endif

        /* Indicate transfer completion */
        set_GPIO_out_to_0(GPIO_OUT_1);

        /* Wait for FPGA */
        while (read_GPIO_in(GPIO_IN_1) != 0) {;}

        /* Change transfer params -> read */
        QDMAresult = LIBQDMA_change_transfer_params_AB(CHUNK_LEN_READ, CHUNK_NUM_READ,
                        (LIBQDMA_ARR_TYPE *)fpga_array,
                        (LIBQDMA_ARR_TYPE *)LIBQDMA_getGlobalAddr((LIBQDMA_ARR_TYPE *)pcie_read_buffer));
        counter++;
    }
}

int main() {
    TSCL = 0; // initialise timer
    selfId = CSL_chipReadReg(CSL_CHIP_DNUM);

    config_cache(selfId);
    platform_uart_init();
    platform_uart_set_baudrate(115200);

    if (selfId == IPC_MASTER_CORENUM)
    {   // MASTER
        PCIE_logPrintf ("Master core is %d.\n", (int)selfId);
#if (IMC_CONTROL == 1)
        PCIE_logPrintf ("IMC_CONTROL\nTOT_NUM_BPM=%d, NUM_ENABLED=%d, NUM_CMs=%d\n",
                        TOT_NUM_BPM, IMC_DI_NY, IMC_DI_NU);
#elif (GSVD_CONTROL == 1)
        PCIE_logPrintf ("GSVD_CONTROL\nNY=%d, NS=%d, NF=%d\n",
                        TOT_NUM_BPM, GSVD_NY, GSVD_NS, GSVD_NF);
#elif (MPC_CONTROL == 1)
        PCIE_logPrintf ("MPC_CONTROL\nNY=%d, NU=%d\n", MPC_NY, MPC_NU);
#else
        PCIE_logPrintf ("LOOPBACK\n");
#endif
#if (USE_IPC == 1)
        /* Initialise IPC framework */
        ipc_master_init();
        ipc_master_wait_for_slaves_after_init();
#if (MPC_CONTROL == 1)
        PCIE_logPrintf ("Initialize MPC.\n");
        MPC_initialize();
#endif /* (MPC_CONTROL == 1) */
        int i;
        for (i = 1; i <= NUMSLAVES; i++) {
            ipc_master_set_req_slave_i(1, i); // INIT 1
            ipc_master_wait_ack_slave_i(i);
        }
#if (IMC_CONTROL == 1)
        PCIE_logPrintf ("Initialize IMC.\n");
        DTF_IMC_DI_init();
#endif /* (IMC_CONTROL == 1) */
#endif /* ((USE_IPC == 1) */

        PCIE_logPrintf ("Start PCIe loop.\n");
        pcie_loop();
    } else {
        if (selfId == UDP_CORENUM) {   // UDP communication
            srand(1111);
            /* Goes into UDP task */
            BIOS_start();
            ;
        } else { // WORKER
#if (USE_IPC == 1)
            /* Initialize IPC framework */
            ipc_slave_init2();

            ipc_slave_wait_req(); // INIT 1
            ipc_slave_set_ack(1);

#if (IMC_CONTROL == 1)
            IMC_DI_ctr_worker(ipc_slave_get_selfId());
#elif (GSVD_CONTROL == 1)
            GSVD_ctr_worker(ipc_slave_get_selfId());
#elif (MPC_CONTROL == 1)
            OBS_initialize_worker(ipc_slave_get_selfId());
            FGM_MPC_initialize_worker(ipc_slave_get_selfId());
            FGM_MPC_solve_worker();
#endif
#endif /* (USE_IPC == 1) */

        }
    }
    return 0;
}

