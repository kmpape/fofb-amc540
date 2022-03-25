#ifdef SOC_C6678
#include <c6x.h>
#include <ti/csl/csl_chip.h>
#include <csl_cache.h>
#include <csl_cacheAux.h>
#endif // SOC_C6678

#include "fofb_config.h"
#include "mpc/fast_gradient_method.h"
#include "mpc/observer.h"
#if (XDIR == 1)
#if (FGM_MPC_HORIZON == 1)
#include "MPC_data_c6678_NWORKERS6_x.h"
#else
#include "MPC_data_c6678_NWORKERS6_H2_x.h"
#endif /* FGM_MPC_HORIZON */
#else
#if (FGM_MPC_HORIZON == 1)
#include "MPC_data_c6678_NWORKERS6_y.h"
#else
#include "MPC_data_c6678_NWORKERS6_H2_y.h"
#endif /* FGM_MPC_HORIZON */
#endif /* XDIR */

void MPC_initialize(void)
{
    FGM_MPC_initialize(obj_func_matrix,
                       obj_func_vector_matrix,
                       (const fgm_float*)ampl_max_vec,
                       (const fgm_float*)rate_max_vec,
                       solution_0,
                       obj_func_max_eigval,
                       obj_func_min_eigval,
                       TOT_NUM_CM,
                       FGM_MPC_HORIZON,
                       (const obs_float *)&(y_meas_in[0]));

    /* Observer */
    OBS_initialize_master(Lx_pad,
                          Ld_pad,
                          Cx_pad,
                          xd_init_pad,
                          x0_init_pad,
                          x1_init_pad,
                          x2_init_pad,
                          x3_init_pad,
                          x4_init_pad,
                          x5_init_pad,
                          x6_init_pad,
                          x7_init_pad,
                          x8_init_pad,
                          FGM_MPC_N_X0_OR_XD);
}

fgm_float * MPC_get_input(void)
{
    return (fgm_float *)FGM_MPC_get_input():
}

fgm_float * MPC_ctr(int restart)
{
    int retval = FGM_MPC_solve();
    fgm_float * result = (fgm_float *)FGM_MPC_get_output();
    CACHE_invL1d((void *) &result[0], FGM_MPC_BYTES_IN_VEC_TOTAL, CACHE_WAIT);
    return result;
}
