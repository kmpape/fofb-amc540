#include <string.h>
#include <math.h>

#include "fofb_config.h"
#include "utils/libQDMA.h"
#include "mpc/MPC_transfer.h"
#include "mpc/MPC_ctr.h"

#if (MPC_SLOWFAST == 1)
#include "mpc/slowfast_data/MPC_storage_ring_config.h"
#else
#include "mpc/standard_data/MPC_storage_ring_config.h"
#endif /* MPC_SLOWFAST */

#define TMPC_min(X, Y)  ((X) < (Y) ? (X) : (Y))
#define TMPC_max(X, Y)  ((X) > (Y) ? (X) : (Y))
#define TMPC_sat(X, Y)  (TMPC_min(TMPC_max(X,-Y),Y))

int MPC_BPM_to_float(const LIBQDMA_ARR_TYPE * in_vec, fgm_float * out_vec)
{
    int i;
    for (i = 0; i < MPC_NY_; i++) {
        LIBQDMA_ARR_TYPE tmp = TMPC_sat(in_vec[MPC_ID_TO_BPM[i]], MPC_LIMIT_READ);
        out_vec[i] = ((fgm_float)tmp) * MPC_SCALING_FACTOR_READ;
    }
    return 0;
}

int MPC_CM_to_int(const fgm_float * in_vec, LIBQDMA_ARR_TYPE * out_vec)
{
    int i;
    memset((LIBQDMA_ARR_TYPE *)out_vec, 0, TOT_NUM_CM*sizeof(LIBQDMA_ARR_TYPE));
    for (i = 0; i < MPC_NU_; i++) {
        LIBQDMA_ARR_TYPE tmp = round(in_vec[i]*MPC_SCALING_FACTOR_WRITE);
        out_vec[MPC_CM_TO_ID[i]] = tmp;//TMPC_sat(tmp, MPC_LIMIT_WRITE);
    }
    return 0;
}

int MPC_get_num_BPM(void) {
    return MPC_NY_;
}

int MPC_get_num_CM(void) {
    return MPC_NU_;
}
