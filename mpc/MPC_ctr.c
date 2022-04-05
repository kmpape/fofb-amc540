#ifdef SOC_C6678
#include <c6x.h>
#include <ti/csl/csl_chip.h>
#include <csl_cache.h>
#include <csl_cacheAux.h>
#endif // SOC_C6678

#include "fofb_config.h"
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
    return (fgm_float *)FGM_MPC_get_input();
}

fgm_float * MPC_ctr(int restart)
{
    CACHE_wbL1d((void *)FGM_MPC_get_input(), FGM_MPC_BYTES_X0_OR_XD, CACHE_WAIT);
    int retval = FGM_MPC_solve();
    fgm_float * result = (fgm_float *)FGM_MPC_get_output();
    CACHE_invL1d((void *) &result[0], FGM_MPC_BYTES_IN_VEC_TOTAL, CACHE_WAIT);
    return result;
}
