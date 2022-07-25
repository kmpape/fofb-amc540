#include <stdio.h>
/* Configuration */
#include "fofb_config.h"

/* IMC */
#if (IMC_CONTROL == 1)
#include "imc/DTF_IMC_DI.h"
#include "imc/IMC_DI_ctr.h"
#include "imc/IMC_transfer.h"
#if (IMC_DI_XDIR == 1)
#include "imc/IMC_test_data_x.h"
#else
#include "imc/IMC_test_data_y.h"
#endif
#endif

/* GSVD */
#if (GSVD_CONTROL == 1)
#include "gsvd/GSVD_ctr.h"
#include "gsvd/GSVD_transfer.h"
#if (IMC_DI_XDIR == 1)
#include "gsvd/GSVD_test_data_x.h"
#else
#include "gsvd/GSVD_test_data_y.h"
#endif
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
#include "utils/watchdog.h"

#pragma DATA_SECTION(pcie_write_buffer_test, ".dstBufSec")
#pragma DATA_ALIGN(pcie_write_buffer_test, 256)
volatile LIBQDMA_ARR_TYPE pcie_write_buffer_test[256];

#if (GSVD_CONTROL == 1)
#include "gsvd/GSVD_test_data_horizontal.h"
void gsvd_test(void) {
    int i, j;
    for (i=0; i<GSVD_NTEST+1; i++) {
        const int *tmp_in = &GSVD_TEST_IN[i*173];
        const int *tmp_out = &GSVD_TEST_OUT[i*172];
        GSVD_BPM_to_float(tmp_in, GSVD_get_input());
        gsvd_float * corr_values = GSVD_ctr(0); // calls parallel routines and invalidates cache
        GSVD_CM_to_int(corr_values, (LIBQDMA_ARR_TYPE *)(&pcie_write_buffer_test[READ_WRITE_OFFSET]));

        int error = 0;
        for (j=0; j<172; j++) {
            error += (pcie_write_buffer_test[READ_WRITE_OFFSET+j]+tmp_out[j])*(pcie_write_buffer_test[READ_WRITE_OFFSET+j]+tmp_out[j]);
        }
        if (1) {
            printf("\nError at %d = %d\nres=", i, error);
            for (j=0; j<10; j++) {
                printf("%d, ", pcie_write_buffer_test[READ_WRITE_OFFSET+j]);
            }
            printf("\ndes=");
            for (j=0; j<10; j++) {
                printf("%d, ", -tmp_out[j]);
            }
        }
    }
    printf("gsvd test finished\n");
}
#endif

#if (IMC_CONTROL == 1)
void imc_test(void) {
    int i, j;
    for (i=0; i<IMC_NTEST+1; i++) {
        const int *tmp_in = &IMC_TEST_IN[i*173];
        const int *tmp_out = &IMC_TEST_OUT[i*172];
        BPM_to_float(tmp_in, IMC_DI_get_input());
        imc_float * corr_values = IMC_DI_ctr(); // calls parallel routines and invalidates cache
        CM_to_int(corr_values, (LIBQDMA_ARR_TYPE *)(&pcie_write_buffer_test[0]));

        int error = 0;
        for (j=0; j<172; j++) {
            error += (pcie_write_buffer_test[0+j]+tmp_out[j])*(pcie_write_buffer_test[0+j]+tmp_out[j]);
        }
        if (1) {
            printf("\nError at %d = %d\nres=", i, error);
            for (j=0; j<10; j++) {
                printf("%d, ", pcie_write_buffer_test[0+j]);
            }
            printf("\ndes=");
            for (j=0; j<10; j++) {
                printf("%d, ", -tmp_out[j]);
            }
        }
    }
    printf("gsvd test finished\n");
}
#endif
