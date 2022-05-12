#ifdef SOC_C6678
#include <c6x.h>
#include <ti/csl/csl_chip.h>
#include <csl_cache.h>
#include <csl_cacheAux.h>
#endif // SOC_C6678

#include "fofb_config.h"
#include "utils/ipc_utils.h"
#include "mpc/fast_gradient_method.h"
#include "mpc/observer.h"

void MPC_initialize(void)
{
    FGM_MPC_initialize();
    OBS_initialize_master();
}

void MPC_initialize_worker(volatile int selfId)
{
    FGM_MPC_initialize_worker(selfId);
    OBS_initialize_worker(selfId);
}

fgm_float * MPC_get_input(void)
{
    return (fgm_float *)FGM_MPC_get_input(); // this array is used as input for the observer
}

fgm_float * MPC_ctr(int restart)
{
    fgm_float * result;
    CACHE_wbL1d((void *)FGM_MPC_get_input(), FGM_MPC_BYTES_X0_OR_XD, CACHE_WAIT);
    if (restart == 0) {
        ipc_master_set_req(1);
    } else {
        FGM_MPC_reset();
        OBS_reset_master();
        ipc_master_set_req(2);
    }
    ipc_master_wait_ack();
    if (restart == 0) {
        OBS_update_observer_master((const fgm_float *)FGM_MPC_get_output());
        FGM_MPC_solve();
    }
    result = (fgm_float *)FGM_MPC_get_output();
    CACHE_invL1d((void *) &result[0], FGM_MPC_BYTES_GLOBAL_ARRAYS, CACHE_WAIT);
    return result;
}


#pragma FUNC_NEVER_RETURNS(MPC_ctr_worker)
void MPC_ctr_worker(void)
{
    int req_val;
    while (1) {
        req_val = ipc_slave_wait_req();
        CACHE_invL1d((void *) FGM_MPC_get_input(), FGM_MPC_BYTES_X0_OR_XD, CACHE_WAIT);
        CACHE_invL1d((void *) FGM_MPC_get_output(), FGM_MPC_BYTES_GLOBAL_ARRAYS, CACHE_WAIT);
        if (req_val == 2) {
            FGM_MPC_reset_worker();
            OBS_reset_worker();
        }
        ipc_slave_set_ack(1);

        if (req_val != 2) {
            OBS_update_observer_worker((const fgm_float *)FGM_MPC_get_input());
            FGM_MPC_solve_worker((const fgm_float *)OBS_get_x0_new(), (const fgm_float *)OBS_get_xd());
        }
    }
}
