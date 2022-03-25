#include <string.h>
#include <math.h>

#include "fofb_config.h"
#include "utils/libQDMA.h"
#include "mpc/MPC_transfer.h"
#include "mpc/MPC_ctr.h"
#include "mpc/MPC_storage_ring_config.h"


#define TMPC_min(X, Y)  ((X) < (Y) ? (X) : (Y))
#define TMPC_max(X, Y)  ((X) > (Y) ? (X) : (Y))
#define TMPC_sat(X, Y)  (TMPC_min(TMPC_max(X,-Y),Y))

int MPC_BPM_to_float(const LIBQDMA_ARR_TYPE * in_vec, fgm_float * out_vec)
{
    int i;
    for (i = 0; i < MPC_NY; i++) {
        LIBQDMA_ARR_TYPE tmp = TMPC_sat(in_vec[MPC_ID_TO_BPM[i]], ORBIT_LIMIT);
        out_vec[i] = ((fgm_float)tmp) * MPC_SCALING_FACTOR_READ;
    }
    return 0;
}

int MPC_CM_to_int(const fgm_float * in_vec, LIBQDMA_ARR_TYPE * out_vec)
{
    int i;
    memset((LIBQDMA_ARR_TYPE *)out_vec, 0, TOT_NUM_CM*sizeof(LIBQDMA_ARR_TYPE));
    for (i = 0; i < MPC_NU; i++) {
        LIBQDMA_ARR_TYPE tmp = round(in_vec[i]*MPC_SCALING_FACTOR_WRITE);
        out_vec[MPC_CM_TO_ID[i]] = TMPC_sat(tmp, ORBIT_LIMIT);
    }
    return 0;
}
