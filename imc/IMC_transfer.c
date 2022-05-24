#include "fofb_config.h"
#include "utils/libQDMA.h"
#include "imc/IMC_DI_ctr.h"
#include "imc/IMC_transfer.h"
#if (XDIR == 1)
#include "storage_ring_config_x.h"
#else
#include "storage_ring_config_y.h"
#endif


#define T_min(X, Y)  ((X) < (Y) ? (X) : (Y))
#define T_max(X, Y)  ((X) > (Y) ? (X) : (Y))
#define T_sat(X, Y)  (T_min(T_max(X,-Y),Y))

void BPM_to_float(const LIBQDMA_ARR_TYPE * in_vec, imc_float * out_vec)
{
    int i;
    for (i = 0; i < TOT_NUM_BPM; i++) {
        LIBQDMA_ARR_TYPE tmp = T_sat(in_vec[i], IMC_LIMIT_READ);
        out_vec[i] = (imc_float)tmp;
    }
}

void CM_to_int(const imc_float * in_vec, LIBQDMA_ARR_TYPE * out_vec)
{
    int i;
    for (i = 0; i < TOT_NUM_CM; i++) {
        LIBQDMA_ARR_TYPE tmp = (LIBQDMA_ARR_TYPE)(in_vec[i]*IMC_SCALING_FACTOR_WRITE);
        out_vec[i] = T_sat(tmp, IMC_LIMIT_WRITE);
    }
}
