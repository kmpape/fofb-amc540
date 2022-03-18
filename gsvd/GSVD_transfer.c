#include <string.h>

#include "fofb_config.h"
#include "utils/libQDMA.h"
#include "gsvd/GSVD_ctr.h"
#include "gsvd/GSVD_storage_ring_config.h"


#define T_min(X, Y)  ((X) < (Y) ? (X) : (Y))
#define T_max(X, Y)  ((X) > (Y) ? (X) : (Y))
#define T_sat(X, Y)  (T_min(T_max(X,-Y),Y))

int GSVD_BPM_to_float(const LIBQDMA_ARR_TYPE * in_vec, gsvd_float * out_vec)
{
    int i;
    for (i = 0; i < GSVD_NY; i++) {
        LIBQDMA_ARR_TYPE tmp = T_sat(in_vec[GSVD_ID_TO_BPM[i]], ORBIT_LIMIT);
        out_vec[i] = (gsvd_float)tmp;
    }
    return 0;
}

int GSVD_CM_to_int(const gsvd_float * in_vec, LIBQDMA_ARR_TYPE * out_vec)
{
    int i;
    memset((LIBQDMA_ARR_TYPE *)out_vec, 0.0, TOT_NUM_CM*sizeof(LIBQDMA_ARR_TYPE));
    for (i = 0; i < GSVD_NS; i++) {
        LIBQDMA_ARR_TYPE tmp = (LIBQDMA_ARR_TYPE)(in_vec[i]*SCALING_FACTOR_WRITE);
        out_vec[GSVD_SLOW_TO_BPM[i]] = T_sat(tmp, ORBIT_LIMIT);
    }
    for (i = 0; i < GSVD_NF; i++) {
        LIBQDMA_ARR_TYPE tmp = (LIBQDMA_ARR_TYPE)(in_vec[GSVD_NS_PAD+i]*SCALING_FACTOR_WRITE);
        out_vec[GSVD_FAST_TO_BPM[i]] = T_sat(tmp, ORBIT_LIMIT);
    }
    return 0;
}
