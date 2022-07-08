#include <string.h>
#include <math.h>

#include "fofb_config.h"
#include "utils/libQDMA.h"
#include "imc/IMC_DI_ctr.h"
#include "imc/IMC_transfer.h"
#if (XDIR == 1)
#include "imc/IMC_storage_ring_config_x.h"
#else
#include "imc/IMC_storage_ring_config_y.h"
#endif


#define T_min(X, Y)  ((X) < (Y) ? (X) : (Y))
#define T_max(X, Y)  ((X) > (Y) ? (X) : (Y))
#define T_sat(X, Y)  (T_min(T_max(X,-Y),Y))

void BPM_to_float(const LIBQDMA_ARR_TYPE * in_vec, imc_float * out_vec)
{
    int i;
    for (i = 0; i < IMC_DI_NY; i++) {
        LIBQDMA_ARR_TYPE tmp = T_sat(in_vec[IMC_ID_TO_BPM[i]], IMC_LIMIT_READ);
        out_vec[i] = (imc_float)tmp;
    }
}

void CM_to_int(const imc_float * in_vec, LIBQDMA_ARR_TYPE * out_vec)
{
    int i;
    memset((LIBQDMA_ARR_TYPE *)out_vec, 0, TOT_NUM_CM*sizeof(LIBQDMA_ARR_TYPE));
    for (i = 0; i < IMC_DI_NU; i++) {
        LIBQDMA_ARR_TYPE tmp = round((LIBQDMA_ARR_TYPE)(in_vec[i]*IMC_SCALING_FACTOR_WRITE));
        out_vec[IMC_CM_TO_BPM[i]] = tmp; // T_sat(tmp, IMC_LIMIT_WRITE);
    }
}
