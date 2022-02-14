#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/System.h>
#include <stdio.h>
#include <string.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sdo/edma3/drv/sample/bios6_edma3_drv_sample.h>

#include "libQDMA.h"

extern signed char*  getGlobalAddr(signed char* addr);
extern EDMA3_DRV_InstanceInitConfig sampleInstInitConfig[][EDMA3_MAX_REGIONS];
extern EDMA3_RM_InstanceInitConfig defInstInitConfig [][EDMA3_MAX_REGIONS];
extern EDMA3_DRV_GblConfigParams sampleEdma3GblCfgParams[];

/* placeholder for destination array */
LIBQDMA_ARR_TYPE* LIBQDMA_dst_ptr;
/* placeholder for source array */
LIBQDMA_ARR_TYPE* LIBQDMA_src_ptr;
/* placeholder for bzte count array */
uint32_t LIBQDMA_byte_cnt;
/* hardware instance ID */
uint32_t LIBQDMA_select_edma3Id = 0;
/* channel controller ID. NOTE: getting conflicts with UDP */
uint32_t LIBQDMA_qCh1Id = EDMA3_DRV_QDMA_CHANNEL_ANY; // EDMA3_DRV_QDMA_CHANNEL_0;
const uint32_t LIBQDMA_qCh1Id_reset = EDMA3_DRV_QDMA_CHANNEL_ANY; //EDMA3_DRV_QDMA_CHANNEL_0;
/* transfer controller ID */
uint32_t LIBQDMA_qTcc1 = EDMA3_DRV_TCC_ANY;
const uint32_t LIBQDMA_qTcc1_reset = EDMA3_DRV_TCC_ANY;

/*
 * EDMA3 Driver Handle, which is used to call all the Driver APIs.
 * It gets initialized during EDMA3 Initialization.
 */
EDMA3_DRV_Handle LIBQDMA_hEdma;


/*
 * ARRAY_TYPE* LIBQDMA_getGlobalAddr
 */
LIBQDMA_ARR_TYPE* LIBQDMA_getGlobalAddr(LIBQDMA_ARR_TYPE* addr)
{
    return ((LIBQDMA_ARR_TYPE*)getGlobalAddr((signed char*)addr));
}


/*
 * LIBQDMA_reset_Cc_Tcc
 * Internal use only
 */
void _LIBQDMA_reset_Cc_Tcc(void)
{
    LIBQDMA_qCh1Id = LIBQDMA_qCh1Id_reset;
    LIBQDMA_qTcc1 = LIBQDMA_qTcc1_reset;
}



/*
 * LIBQDMA_STATUS LIBQDMA_init
 */
LIBQDMA_STATUS LIBQDMA_init(
        uint32_t arr_len,
        LIBQDMA_ARR_TYPE *src,
        LIBQDMA_ARR_TYPE *dst)
{
    /* transfer parameters */
    const uint32_t acnt = arr_len * ((uint32_t)sizeof(LIBQDMA_ARR_TYPE));
    const uint32_t bcnt = 1;
    const uint32_t ccnt = 1;
    uint32_t BRCnt      = 0;
    /* status flag */
    EDMA3_DRV_Result result = EDMA3_DRV_SOK;

    /* Init EDMA3 */
    memset(LIBQDMA_hEdma,0,sizeof(LIBQDMA_hEdma));
    LIBQDMA_hEdma = edma3init(LIBQDMA_select_edma3Id, &result);
    if (!LIBQDMA_hEdma) {
        System_printf("edma3init() Failed, error code: %d\n", (int)result);
        return LIBQDMA_ERROR_ANY;
    }

    /* Request DMA channel and TCC, do not provide ISR */
    result = EDMA3_DRV_requestChannel(LIBQDMA_hEdma, &LIBQDMA_qCh1Id, &LIBQDMA_qTcc1,
                (EDMA3_RM_EventQueue)0, NULL, NULL);
    if (result != EDMA3_DRV_SOK) {
        System_printf("EDMA3_DRV_requestChannel() Failed, error code: %d\n", (int)result);
        return LIBQDMA_ERROR_ANY;
    }

    /* Set QDMA Trigger Word as Destination Address */
    result =  EDMA3_DRV_setQdmaTrigWord(LIBQDMA_hEdma, LIBQDMA_qCh1Id,
                EDMA3_RM_QDMA_TRIG_DST);
    if (result != EDMA3_DRV_SOK) {
        System_printf("EDMA3_DRV_setQdmaTrigWord() Failed, error code: %d\n", (int)result);
        return LIBQDMA_ERROR_ANY;
    }

    /* Set source index */
    result = EDMA3_DRV_setSrcIndex(LIBQDMA_hEdma, LIBQDMA_qCh1Id, 0, 0);
    if (result != EDMA3_DRV_SOK) {
        System_printf("EDMA3_DRV_setSrcIndex() Failed, error code: %d\n", (int)result);
        return LIBQDMA_ERROR_ANY;
    }

    /* Set destination index */
    result = EDMA3_DRV_setDestIndex(LIBQDMA_hEdma, LIBQDMA_qCh1Id, 0, 0);
    if (result != EDMA3_DRV_SOK) {
        System_printf("EDMA3_DRV_setDestIndex() Failed, error code: %d\n", (int)result);
        return LIBQDMA_ERROR_ANY;
    }

    /* Set transfer params */
    result = EDMA3_DRV_setTransferParams(LIBQDMA_hEdma, LIBQDMA_qCh1Id, acnt, bcnt,
        ccnt, BRCnt, EDMA3_DRV_SYNC_A);
    if (result != EDMA3_DRV_SOK) {
        System_printf("EDMA3_DRV_setTransferParams() Failed, error code: %d\n", (int)result);
        if (acnt > LIBQDMA_MAX_BYTE_COUNT)
            return LIBQDMA_ERROR_ARR_SIZE;
        else
            return LIBQDMA_ERROR_ANY;
    }

    /* Enable Transfer Completion Interrupt required for
     * reading completion bit */
    result = EDMA3_DRV_setOptField(LIBQDMA_hEdma, LIBQDMA_qCh1Id,
        EDMA3_DRV_OPT_FIELD_TCINTEN, 1u);
    if (result != EDMA3_DRV_SOK) {
        System_printf("EDMA3_DRV_setOptField(TCINTEN) Failed, error code: %d\n", (int)result);
        return LIBQDMA_ERROR_ANY;
    }

    /* Disable Intermediate Transfer Completion Interrupt */
    result = EDMA3_DRV_setOptField(LIBQDMA_hEdma, LIBQDMA_qCh1Id,
                EDMA3_DRV_OPT_FIELD_ITCINTEN, 0u);
    if (result != EDMA3_DRV_SOK) {
        System_printf("EDMA3_DRV_setOptField(ITCINTEN) Failed, error code: %d\n", (int)result);
        return LIBQDMA_ERROR_ANY;
    }

    /* Set Source Transfer Mode as Increment Mode. */
    result = EDMA3_DRV_setOptField(LIBQDMA_hEdma, LIBQDMA_qCh1Id, EDMA3_DRV_OPT_FIELD_SAM,
        EDMA3_DRV_ADDR_MODE_INCR);
    if (result != EDMA3_DRV_SOK) {
        System_printf("EDMA3_DRV_setOptField(SAM) Failed, error code: %d\n", (int)result);
        return LIBQDMA_ERROR_ANY;
    }

    /* Set Destination Transfer Mode as Increment Mode. */
    result = EDMA3_DRV_setOptField(LIBQDMA_hEdma, LIBQDMA_qCh1Id, EDMA3_DRV_OPT_FIELD_DAM,
        EDMA3_DRV_ADDR_MODE_INCR);
    if (result != EDMA3_DRV_SOK) {
        System_printf("EDMA3_DRV_setOptField(DAM) Failed, error code: %d\n", (int)result);
        return LIBQDMA_ERROR_ANY;
    }

    /*
     * Since OPT.STATIC field should be SET for isolated QDMA
     * transfers or for the final transfer in a linked list of QDMA
     * transfers, do the needful for the last request.
     */
    result = EDMA3_DRV_setOptField(LIBQDMA_hEdma, LIBQDMA_qCh1Id,
                        EDMA3_DRV_OPT_FIELD_STATIC, 1u);
    if (result != EDMA3_DRV_SOK) {
        System_printf("EDMA3_DRV_setOptField(STATIC) Failed, error code: %d\n", (int)result);
        return LIBQDMA_ERROR_ANY;
    }

    /* Set the Source Address */
    result = EDMA3_DRV_setSrcParams(LIBQDMA_hEdma, LIBQDMA_qCh1Id, (uint32_t)(src),
        EDMA3_DRV_ADDR_MODE_INCR, EDMA3_DRV_W8BIT);
    if (result != EDMA3_DRV_SOK) {
        System_printf("EDMA3_DRV_setSrcParams() Failed, error code: %d\n", (int)result);
        return LIBQDMA_ERROR_ANY;
    }

    /* Save parameters */
    LIBQDMA_dst_ptr = dst;
    LIBQDMA_src_ptr = src;
    LIBQDMA_byte_cnt = acnt;

    return LIBQDMA_SUCCESS;
}


/*
 * LIBQDMA_STATUS LIBQDMA_init_AB
 */
LIBQDMA_STATUS LIBQDMA_init_AB(
        uint32_t arr_len,
        uint32_t arr_num,
        LIBQDMA_ARR_TYPE *src,
        LIBQDMA_ARR_TYPE *dst)
{
    /* transfer parameters */
    const uint32_t acnt = arr_len * ((uint32_t)sizeof(LIBQDMA_ARR_TYPE));
    const uint32_t bcnt = arr_num;
    const uint32_t ccnt = 1;
    uint32_t BRCnt      = bcnt;
    /* status flag */
    EDMA3_DRV_Result result = EDMA3_DRV_SOK;

    /* Init EDMA3 */
    memset(LIBQDMA_hEdma,0,sizeof(LIBQDMA_hEdma));
    LIBQDMA_hEdma = edma3init(LIBQDMA_select_edma3Id, &result);
    if (LIBQDMA_hEdma) {
        System_printf("edma3init() Passed\n");
    } else {
        System_printf("edma3init() Failed, error code: %d\n", (int)result);
        return LIBQDMA_ERROR_ANY;
    }

    /* Request DMA channel and TCC, do not provide ISR */
    _LIBQDMA_reset_Cc_Tcc();
    result = EDMA3_DRV_requestChannel(LIBQDMA_hEdma, &LIBQDMA_qCh1Id, &LIBQDMA_qTcc1,
                (EDMA3_RM_EventQueue)0, NULL, NULL);
    if (result != EDMA3_DRV_SOK) {
        System_printf("EDMA3_DRV_requestChannel() Failed, error code: %d\n", (int)result);
        return LIBQDMA_ERROR_ANY;
    }

    /* Set QDMA Trigger Word as Destination Address */
    result =  EDMA3_DRV_setQdmaTrigWord(LIBQDMA_hEdma, LIBQDMA_qCh1Id,
                EDMA3_RM_QDMA_TRIG_DST);
    if (result != EDMA3_DRV_SOK) {
        System_printf("EDMA3_DRV_setQdmaTrigWord() Failed, error code: %d\n", (int)result);
        return LIBQDMA_ERROR_ANY;
    }

    /* Set source index */
    result = EDMA3_DRV_setSrcIndex(LIBQDMA_hEdma, LIBQDMA_qCh1Id, acnt, acnt*bcnt);
    if (result != EDMA3_DRV_SOK) {
        System_printf("EDMA3_DRV_setSrcIndex() Failed, error code: %d\n", (int)result);
        return LIBQDMA_ERROR_ANY;
    }

    /* Set destination index */
    result = EDMA3_DRV_setDestIndex(LIBQDMA_hEdma, LIBQDMA_qCh1Id, acnt, acnt*bcnt);
    if (result != EDMA3_DRV_SOK) {
        System_printf("EDMA3_DRV_setDestIndex() Failed, error code: %d\n", (int)result);
        return LIBQDMA_ERROR_ANY;
    }

    /* Set transfer params */
    result = EDMA3_DRV_setTransferParams(LIBQDMA_hEdma, LIBQDMA_qCh1Id, acnt, bcnt,
        ccnt, BRCnt, EDMA3_DRV_SYNC_AB);
    if (result != EDMA3_DRV_SOK) {
        System_printf("EDMA3_DRV_setTransferParams() Failed, error code: %d\n", (int)result);
        if (acnt > LIBQDMA_MAX_BYTE_COUNT)
            return LIBQDMA_ERROR_ARR_SIZE;
        else
            return LIBQDMA_ERROR_ANY;
    }

    /* Enable Transfer Completion Interrupt required for
     * reading completion bit */
    result = EDMA3_DRV_setOptField(LIBQDMA_hEdma, LIBQDMA_qCh1Id,
        EDMA3_DRV_OPT_FIELD_TCINTEN, 1u);
    if (result != EDMA3_DRV_SOK) {
        System_printf("EDMA3_DRV_setOptField(TCINTEN) Failed, error code: %d\n", (int)result);
        return LIBQDMA_ERROR_ANY;
    }

    /* Disable Intermediate Transfer Completion Interrupt */
    result = EDMA3_DRV_setOptField(LIBQDMA_hEdma, LIBQDMA_qCh1Id,
                EDMA3_DRV_OPT_FIELD_ITCINTEN, 0u);
    if (result != EDMA3_DRV_SOK) {
        System_printf("EDMA3_DRV_setOptField(ITCINTEN) Failed, error code: %d\n", (int)result);
        return LIBQDMA_ERROR_ANY;
    }

    /* Set Source Transfer Mode as Increment Mode. */
    result = EDMA3_DRV_setOptField(LIBQDMA_hEdma, LIBQDMA_qCh1Id, EDMA3_DRV_OPT_FIELD_SAM,
        EDMA3_DRV_ADDR_MODE_INCR);
    if (result != EDMA3_DRV_SOK) {
        System_printf("EDMA3_DRV_setOptField(SAM) Failed, error code: %d\n", (int)result);
        return LIBQDMA_ERROR_ANY;
    }

    /* Set Destination Transfer Mode as Increment Mode. */
    result = EDMA3_DRV_setOptField(LIBQDMA_hEdma, LIBQDMA_qCh1Id, EDMA3_DRV_OPT_FIELD_DAM,
        EDMA3_DRV_ADDR_MODE_INCR);
    if (result != EDMA3_DRV_SOK) {
        System_printf("EDMA3_DRV_setOptField(DAM) Failed, error code: %d\n", (int)result);
        return LIBQDMA_ERROR_ANY;
    }

    /* Enable intermediate transfer completion chaining. */
    result = EDMA3_DRV_setOptField(LIBQDMA_hEdma, LIBQDMA_qCh1Id, EDMA3_DRV_OPT_FIELD_ITCCHEN,
        1u);
    if (result != EDMA3_DRV_SOK) {
        System_printf("EDMA3_DRV_setOptField(ITCCHEN) Failed, error code: %d\n", (int)result);
        return LIBQDMA_ERROR_ANY;
    }

    /* Disable complete transfer completion chaining. */
    result = EDMA3_DRV_setOptField(LIBQDMA_hEdma, LIBQDMA_qCh1Id, EDMA3_DRV_OPT_FIELD_TCCHEN,
        0u);
    if (result != EDMA3_DRV_SOK) {
        System_printf("EDMA3_DRV_setOptField(ITCCHEN) Failed, error code: %d\n", (int)result);
        return LIBQDMA_ERROR_ANY;
    }

    /*
     * Since OPT.STATIC field should be SET for isolated QDMA
     * transfers or for the final transfer in a linked list of QDMA
     * transfers, do the needful for the last request.
     */
    result = EDMA3_DRV_setOptField(LIBQDMA_hEdma, LIBQDMA_qCh1Id,
                        EDMA3_DRV_OPT_FIELD_STATIC, 1u);
    if (result != EDMA3_DRV_SOK) {
        System_printf("EDMA3_DRV_setOptField(STATIC) Failed, error code: %d\n", (int)result);
        return LIBQDMA_ERROR_ANY;
    }

    /* Set the Source Address */
    result = EDMA3_DRV_setSrcParams(LIBQDMA_hEdma, LIBQDMA_qCh1Id, (uint32_t)(src),
        EDMA3_DRV_ADDR_MODE_INCR, EDMA3_DRV_W8BIT);
    if (result != EDMA3_DRV_SOK) {
        System_printf("EDMA3_DRV_setSrcParams() Failed, error code: %d\n", (int)result);
        return LIBQDMA_ERROR_ANY;
    }

    /* Save parameters */
    LIBQDMA_dst_ptr = dst;
    LIBQDMA_src_ptr = src;
    LIBQDMA_byte_cnt = acnt*bcnt;

    return LIBQDMA_SUCCESS;
}


/*
 * LIBQDMA_STATUS LIBQDMA_change_transfer_params_AB
 */
LIBQDMA_STATUS LIBQDMA_change_transfer_params_AB(
        uint32_t arr_len,
        uint32_t arr_num,
        LIBQDMA_ARR_TYPE *src,
        LIBQDMA_ARR_TYPE *dst)
{
    /* transfer parameters */
    const uint32_t acnt = arr_len * ((uint32_t)sizeof(LIBQDMA_ARR_TYPE));
    const uint32_t bcnt = arr_num;
    const uint32_t ccnt = 1;
    uint32_t BRCnt      = bcnt;
    /* status flag */
    EDMA3_DRV_Result result = EDMA3_DRV_SOK;

    /* Set source index */
    result = EDMA3_DRV_setSrcIndex(LIBQDMA_hEdma, LIBQDMA_qCh1Id, acnt, acnt*bcnt);
    if (result != EDMA3_DRV_SOK) {
        System_printf("EDMA3_DRV_setSrcIndex() Failed, error code: %d\n", (int)result);
        return LIBQDMA_ERROR_ANY;
    }

    /* Set destination index */
    result = EDMA3_DRV_setDestIndex(LIBQDMA_hEdma, LIBQDMA_qCh1Id, acnt, acnt*bcnt);
    if (result != EDMA3_DRV_SOK) {
        System_printf("EDMA3_DRV_setDestIndex() Failed, error code: %d\n", (int)result);
        return LIBQDMA_ERROR_ANY;
    }

    /* Set transfer params */
    result = EDMA3_DRV_setTransferParams(LIBQDMA_hEdma, LIBQDMA_qCh1Id, acnt, bcnt,
        ccnt, BRCnt, EDMA3_DRV_SYNC_AB);
    if (result != EDMA3_DRV_SOK) {
        System_printf("EDMA3_DRV_setTransferParams() Failed, error code: %d\n", (int)result);
        if (acnt > LIBQDMA_MAX_BYTE_COUNT)
            return LIBQDMA_ERROR_ARR_SIZE;
        else
            return LIBQDMA_ERROR_ANY;
    }

    /* Set the Source Address */
    result = EDMA3_DRV_setSrcParams(LIBQDMA_hEdma, LIBQDMA_qCh1Id, (uint32_t)(src),
        EDMA3_DRV_ADDR_MODE_INCR, EDMA3_DRV_W8BIT);
    if (result != EDMA3_DRV_SOK) {
        System_printf("EDMA3_DRV_setSrcParams() Failed, error code: %d\n", (int)result);
        return LIBQDMA_ERROR_ANY;
    }

    /* Save parameters */
    LIBQDMA_dst_ptr = dst;
    LIBQDMA_src_ptr = src;
    LIBQDMA_byte_cnt = acnt*bcnt;

    return LIBQDMA_SUCCESS;
}

void LIBQDMA_print_parameters(void) {
    System_printf("LIBQDMA parameters\n");
    System_printf("destination address: 0x%x\n", (uint32_t)LIBQDMA_dst_ptr);
    System_printf("source address:      0x%x\n", (uint32_t)LIBQDMA_src_ptr);
    System_printf("byte count:          %d\n", (uint32_t)LIBQDMA_byte_cnt);
}


/*
 * LIBQDMA_STATUS LIBQDMA_trigger_and_wait
 */
LIBQDMA_STATUS LIBQDMA_trigger_and_wait(void)
{
    /* status flag */
    EDMA3_DRV_Result result = EDMA3_DRV_SOK;

    /*
     * Now trigger the QDMA channel by writing to the Trigger
     * Word which is set as Destination Address.
     */
    result = EDMA3_DRV_setPaRAMEntry(LIBQDMA_hEdma, LIBQDMA_qCh1Id,
        EDMA3_DRV_PARAM_ENTRY_DST, (uint32_t)(LIBQDMA_dst_ptr));
    if (result != EDMA3_DRV_SOK) {
        System_printf("EDMA3_DRV_setPaRAMEntry(DST) Failed, error code: %d\n", (int)result);
        return LIBQDMA_ERROR_ANY;
    }

    /* Wait for the Completion Bit to be SET in the IPR/IPRH register. */
    result = EDMA3_DRV_waitAndClearTcc(LIBQDMA_hEdma, LIBQDMA_qTcc1);
    if (result != EDMA3_DRV_SOK) {
        System_printf("EDMA3_DRV_waitAndClearTcc() Failed, error code: %d\n", (int)result);
        return LIBQDMA_ERROR_ANY;
    } else {
        return LIBQDMA_SUCCESS;
    }
}


/*
 * LIBQDMA_STATUS LIBQDMA_stop
 */
LIBQDMA_STATUS LIBQDMA_stop(void)
{
    /* status flag */
    EDMA3_DRV_Result result = EDMA3_DRV_SOK;

    /* free channel */
    result = EDMA3_DRV_freeChannel(LIBQDMA_hEdma, LIBQDMA_qCh1Id);
    if (result != EDMA3_DRV_SOK) {
        System_printf("EDMA3_DRV_freeChannel() Failed, error code: %d\n", (int)result);
        return LIBQDMA_ERROR_ANY;
    }

    /* de-initialize DMA */
    result = edma3deinit(LIBQDMA_select_edma3Id, LIBQDMA_hEdma);
    if (result != EDMA3_DRV_SOK) {
        System_printf("edma3deinit() Failed, error code: %d\n", (int)result);
        return LIBQDMA_ERROR_ANY;
    }

    return LIBQDMA_SUCCESS;
}
