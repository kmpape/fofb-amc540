#include "fofb_config.h"
#include "utils/libQDMA.h"
#include "imc/IMC_DI_ctr.h"
#if (XDIR == 1)
#include "storage_ring_config_x.h"
#else
#include "storage_ring_config_y.h"
#endif


#define T_min(X, Y)  ((X) < (Y) ? (X) : (Y))
#define T_max(X, Y)  ((X) > (Y) ? (X) : (Y))
#define T_sat(X, Y)  (T_min(T_max(X,-Y),Y))

int BPM_to_float(const LIBQDMA_ARR_TYPE * in_vec, imc_float * out_vec)
{
    int i, errors = 0;
    for (i = 0; i < TOT_NUM_BPM; i++) {
        LIBQDMA_ARR_TYPE tmp = T_sat(in_vec[i], ORBIT_LIMIT);
        out_vec[i] = (imc_float)tmp;
        if (tmp != in_vec[i])
            errors += IMC_DI_BPM_ENABLED[i];
    }

    return errors;
}

int CM_to_int(const imc_float * in_vec, LIBQDMA_ARR_TYPE * out_vec)
{
    int i, errors = 0;
    for (i = 0; i < TOT_NUM_CM; i++) {
        LIBQDMA_ARR_TYPE tmp = (LIBQDMA_ARR_TYPE)(in_vec[i]*SCALING_FACTOR_WRITE);
        out_vec[i] = T_sat(tmp, ORBIT_LIMIT);
        if (tmp != out_vec[i])
            errors += IMC_DI_CM_ENABLED[i];
    }

    return errors;
}
