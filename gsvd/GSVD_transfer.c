#include <string.h>
#include <math.h>

#include "fofb_config.h"
#include "utils/libQDMA.h"
#include "gsvd/GSVD_transfer.h"
#include "gsvd/GSVD_ctr.h"

#if (GSVD_XDIR == 1)
#include "gsvd/GSVD_storage_ring_config_x.h"
#else
#include "gsvd/GSVD_storage_ring_config_y.h"
#endif /* GSVD_XDIR */


#define T_min(X, Y)  ((X) < (Y) ? (X) : (Y))
#define T_max(X, Y)  ((X) > (Y) ? (X) : (Y))
#define T_sat(X, Y)  (T_min(T_max(X,-Y),Y))

int GSVD_BPM_to_float(const LIBQDMA_ARR_TYPE * in_vec, gsvd_float * out_vec)
{
    int i;
    for (i = 0; i < GSVD_NY; i++) {
        int tmp = T_sat(in_vec[GSVD_ID_TO_BPM[i]], GSVD_LIMIT_READ);
        out_vec[i] = (gsvd_float)tmp;
    }
    return 0;
}

int GSVD_CM_to_int(const gsvd_float * in_vec, LIBQDMA_ARR_TYPE * out_vec)
{
    int i;
    memset((LIBQDMA_ARR_TYPE *)out_vec, 0, TOT_NUM_CM*sizeof(LIBQDMA_ARR_TYPE));
    for (i = 0; i < GSVD_NS; i++) {
        LIBQDMA_ARR_TYPE tmp = round(in_vec[i]*GSVD_SCALING_FACTOR_WRITE);
        out_vec[GSVD_SLOW_TO_BPM[i]] = T_sat(tmp, GSVD_LIMIT_WRITE);
    }
    for (i = 0; i < GSVD_NF; i++) {
        LIBQDMA_ARR_TYPE tmp = round(in_vec[GSVD_NS_PAD+i]*GSVD_SCALING_FACTOR_WRITE);
        out_vec[GSVD_FAST_TO_BPM[i]] = T_sat(tmp, GSVD_LIMIT_WRITE);
    }
    return 0;
}
