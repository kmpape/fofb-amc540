#include <string.h>
#ifdef SOC_C6678
#include <c6x.h>
#include <ti/csl/csl_chip.h>
#include <csl_cache.h>
#include <csl_cacheAux.h>
#endif

#if (defined(SOC_C6678) && (USE_IPC==1))
#include "ipc_utils.h"
#endif

#include "fofb_config.h"
#include "gsvd/GSVD_ctr.h"
#include "gsvd/DTF_gs.h"
#include "gsvd/DTF_gf.h"
#include "gsvd/DTF_qs.h"
#include "gsvd/DTF_qf.h"

#if (GSVD_XDIR == 1)
#include "GSVD_gain_x.h"
#else
#include "GSVD_gain_y.h"
#endif /* GSVD_XDIR */

#ifdef SOC_C6678
#pragma DATA_ALIGN(GSVD_ctr_input,       GSVD_ARRAY_ALIGN)
#pragma DATA_ALIGN(GSVD_measurements,    GSVD_ARRAY_ALIGN)
#pragma DATA_ALIGN(out_Ps,          GSVD_ARRAY_ALIGN)
#pragma DATA_ALIGN(out_Pf,          GSVD_ARRAY_ALIGN)
#pragma DATA_ALIGN(out_sum,         GSVD_ARRAY_ALIGN)
#pragma SET_DATA_SECTION(".gsvd_shared")
#endif /* SOC_C6678 */
volatile gsvd_float GSVD_ctr_input[GSVD_NU_PAD];
volatile gsvd_float GSVD_measurements[GSVD_NY_PAD];  // y[k] in nanometers
volatile gsvd_float out_Ps[GSVD_NY_PAD];        // = gs(z) * Ps * us[k]
volatile gsvd_float out_Pf[GSVD_NY_PAD];        // = gf(z) * Pf * uf[k]
volatile gsvd_float out_sum[GSVD_NY_PAD];       // = GSVD_measurements[k] + out_Ps[k] + out_Pf[k]
#ifdef SOC_C6678
#pragma SET_DATA_SECTION()
#endif /* SOC_C6678 */

#ifdef SOC_C6678
#pragma DATA_ALIGN(mat_Ks_local,   GSVD_ARRAY_ALIGN)
#pragma DATA_ALIGN(mat_Kf_local,   GSVD_ARRAY_ALIGN)
#pragma DATA_ALIGN(mat_Ps_local,   GSVD_ARRAY_ALIGN)
#pragma DATA_ALIGN(mat_Pf_local,   GSVD_ARRAY_ALIGN)
#pragma SET_DATA_SECTION(".gsvd_local")
Uint32 volatile GSVD_selfId;
#endif /* SOC_C6678 */
gsvd_float mat_Ks_local[GSVD_SIZE_KS_LOCAL];
gsvd_float mat_Kf_local[GSVD_SIZE_KF_LOCAL];
gsvd_float mat_Ps_local[GSVD_SIZE_PS_LOCAL];
gsvd_float mat_Pf_local[GSVD_SIZE_PF_LOCAL];
#ifdef SOC_C6678
#pragma SET_DATA_SECTION()
#endif /* SOC_C6678 */

void GSVD_double_to_float(const double *in, float *out, const int len)
{
    int i;
#ifdef SOC_C6678
    _nassert((int) in % GSVD_ARRAY_ALIGN == 0);
    _nassert((int) out % GSVD_ARRAY_ALIGN == 0);
#pragma MUST_ITERATE(16, , 16)
#endif /* SOC_C6678 */
    for (i=0; i<len; i++)
        out[i] = (float)in[i];
}

void GSVD_copy_vec(const gsvd_float *in, gsvd_float *out, const int len)
{
    int i;
#ifdef SOC_C6678
    _nassert((int) in % GSVD_ARRAY_ALIGN == 0);
    _nassert((int) out % GSVD_ARRAY_ALIGN == 0);
#pragma MUST_ITERATE(16, , 16)
#endif /* SOC_C6678 */
    for (i=0; i<len; i++)
        out[i] = in[i];
}

gsvd_float * GSVD_get_input(void)
{
    return (gsvd_float *)GSVD_measurements;
}

static void GSVD_mat_mpy(const gsvd_float * in_mat, const gsvd_float * in_vec, double * out_vec,
                    const int nrows, const int ncols)
{
    int i, j;
    const gsvd_float * in_mat_ptr = &in_mat[0];

#ifdef SOC_C6678
    _nassert((int) in_mat % GSVD_ARRAY_ALIGN == 0);
    _nassert((int) in_vec % GSVD_ARRAY_ALIGN == 0);
    _nassert((int) out_vec % GSVD_ARRAY_ALIGN == 0);
#pragma MUST_ITERATE(16, , 16)
#endif /* SOC_C6678 */
    for (i = 0; i < nrows; i++)
    {
        double row_res = 0.0;
#ifdef SOC_C6678
#pragma MUST_ITERATE(16, , 16)
#endif /* SOC_C6678 */
        for (j = 0; j < ncols; j++)
        {
            row_res += (double)(in_mat_ptr[j] * in_vec[j]); // note
        }
        out_vec[i] = row_res;
        in_mat_ptr += ncols;
    }
}

static void GSVD_add_fb_signal(const gsvd_float * in_vec_1, const gsvd_float * in_vec_2, const gsvd_float * in_vec_3,
                          gsvd_float * out_vec, const int len)
{
    int i;

#ifdef SOC_C6678
    _nassert((int) in_vec_1 % GSVD_ARRAY_ALIGN == 0);
    _nassert((int) in_vec_2 % GSVD_ARRAY_ALIGN == 0);
    _nassert((int) in_vec_3 % GSVD_ARRAY_ALIGN == 0);
    _nassert((int) out_vec % GSVD_ARRAY_ALIGN == 0);
#pragma MUST_ITERATE(16, , 16)
#endif /* SOC_C6678 */
    for (i = 0; i < len; i++)
    {
        out_vec[i] = in_vec_1[i] + in_vec_2[i] + in_vec_3[i];
    }
}

void GSVD_init_filters(void)
{
    DTF_gs_init();
    DTF_gf_init();
    DTF_qs_init();
    DTF_qf_init();
}

#if (defined(SOC_C6678) && (USE_IPC==1))

static void GSVD_init_worker(Uint32 selfId)
{
    GSVD_selfId = selfId;
    GSVD_copy_vec(&GSVD_Ks_gain[(selfId-1) * GSVD_SIZE_KS_LOCAL], mat_Ks_local, GSVD_SIZE_KS_LOCAL);
    GSVD_copy_vec(&GSVD_Kf_gain[(selfId-1) * GSVD_SIZE_KF_LOCAL], mat_Kf_local, GSVD_SIZE_KF_LOCAL);
    GSVD_copy_vec(&GSVD_Ps_gain[(selfId-1) * GSVD_SIZE_PS_LOCAL], mat_Ps_local, GSVD_SIZE_PS_LOCAL);
    GSVD_copy_vec(&GSVD_Pf_gain[(selfId-1) * GSVD_SIZE_PF_LOCAL], mat_Pf_local, GSVD_SIZE_PF_LOCAL);
    GSVD_init_filters();
}

void GSVD_ctr_worker(Uint32 selfId)
{
    int req_val;
    GSVD_init_worker(selfId);
    while (1)
    {
        req_val = ipc_slave_wait_req(); // ML 0: Compute slow and fast inputs
        if (req_val == 2)
            GSVD_init_filters();

        CACHE_invL1d ((void *) &out_sum[0], GSVD_NY_PAD*GSVD_FLOAT_SIZE, CACHE_FENCE_WAIT);

        GSVD_mat_mpy((const gsvd_float *)&mat_Ks_local[0], (const gsvd_float *)out_sum,
                     (DTF_qs_ARR_TYPE *)DTF_qs_get_u0_ptr(), GSVD_KS_W_NROWS, GSVD_KS_W_NCOLS);
        DTF_qs_execute();
        GSVD_double_to_float((const DTF_qs_ARR_TYPE *)DTF_qs_get_y0_ptr(),
                             (gsvd_float *)&GSVD_ctr_input[(selfId-1)*GSVD_NS_W], GSVD_NS_W);
        CACHE_wbL1d ((void *) &GSVD_ctr_input[(selfId-1)*GSVD_NS_W], GSVD_NS_W*GSVD_FLOAT_SIZE, CACHE_FENCE_WAIT);

        GSVD_mat_mpy((const gsvd_float *)&mat_Kf_local[0], (const gsvd_float *)out_sum,
                     (DTF_qf_ARR_TYPE *)DTF_qf_get_u0_ptr(), GSVD_KF_W_NROWS, GSVD_KF_W_NCOLS);
        DTF_qf_execute();
        GSVD_double_to_float((const DTF_qf_ARR_TYPE *)DTF_qf_get_y0_ptr(),
                             (gsvd_float *)&GSVD_ctr_input[GSVD_NS_PAD+(selfId-1)*GSVD_NF_W], GSVD_NF_W);
        CACHE_wbL1d ((void *) &GSVD_ctr_input[GSVD_NS_PAD+(selfId-1)*GSVD_NF_W], GSVD_NF_W*GSVD_FLOAT_SIZE, CACHE_FENCE_WAIT);

        ipc_slave_set_ack(1); // ML 0

        ipc_slave_wait_req(); // ML 1: Update slow and fast model outputs

        CACHE_invL1d ((void *) &GSVD_ctr_input[0], GSVD_NU_PAD*GSVD_FLOAT_SIZE, CACHE_FENCE_WAIT);

        GSVD_mat_mpy((const gsvd_float *)&mat_Ps_local[0], (const gsvd_float *)GSVD_ctr_input,
                     (DTF_gs_ARR_TYPE *)DTF_gs_get_u0_ptr(), GSVD_PS_W_NROWS, GSVD_PS_W_NCOLS);
        DTF_gs_execute();
        GSVD_double_to_float((const DTF_gs_ARR_TYPE *)DTF_gs_get_y0_ptr(),
                             (gsvd_float *)&out_Ps[(selfId-1)*GSVD_NY_W], GSVD_NY_W);
        CACHE_wbL1d ((void *) &out_Ps[(selfId-1)*GSVD_NY_W], GSVD_NY_W*GSVD_FLOAT_SIZE, CACHE_FENCE_WAIT);

        GSVD_mat_mpy((const gsvd_float *)&mat_Pf_local[0], (const gsvd_float *)&GSVD_ctr_input[GSVD_NS_PAD],
                     (DTF_gf_ARR_TYPE *)DTF_gf_get_u0_ptr(), GSVD_PF_W_NROWS, GSVD_PF_W_NCOLS);
        DTF_gf_execute();
        GSVD_double_to_float((const DTF_gf_ARR_TYPE *)DTF_gf_get_y0_ptr(),
                             (gsvd_float *)&out_Pf[(selfId-1)*GSVD_NY_W], GSVD_NY_W);

        CACHE_wbL1d ((void *) &out_Pf[(selfId-1)*GSVD_NY_W], GSVD_NY_W*GSVD_FLOAT_SIZE, CACHE_FENCE_WAIT);

        ipc_slave_set_ack(1); // ML 1
    }
}
#endif

gsvd_float * GSVD_ctr(int restart)
{
#if (defined(SOC_C6678) && (USE_IPC==1))

    CACHE_invL1d ((void *) &out_Ps[0], GSVD_NY_PAD*GSVD_FLOAT_SIZE, CACHE_FENCE_WAIT);
    CACHE_invL1d ((void *) &out_Pf[0], GSVD_NY_PAD*GSVD_FLOAT_SIZE, CACHE_FENCE_WAIT);
    GSVD_add_fb_signal((const gsvd_float *)out_Ps, (const gsvd_float *)out_Pf, (const gsvd_float *)GSVD_measurements,
                       (gsvd_float *)out_sum, GSVD_NY_PAD);
    CACHE_wbL1d ((void *) &out_sum[0], GSVD_NY_PAD*GSVD_FLOAT_SIZE, CACHE_FENCE_WAIT);

    if (restart == 1) {
        memset((gsvd_float *)out_Ps, 0, GSVD_NY_PAD*GSVD_FLOAT_SIZE);
        memset((gsvd_float *)out_Pf, 0, GSVD_NY_PAD*GSVD_FLOAT_SIZE);
        memset((gsvd_float *)out_sum, 0, GSVD_NY_PAD*GSVD_FLOAT_SIZE);
        CACHE_wbL1d ((void *) &out_sum[0], GSVD_NY_PAD*GSVD_FLOAT_SIZE, CACHE_FENCE_WAIT);
        ipc_master_set_req(2); // Restart
    } else {
        CACHE_invL1d ((void *) &out_Ps[0], GSVD_NY_PAD*GSVD_FLOAT_SIZE, CACHE_FENCE_WAIT);
        CACHE_invL1d ((void *) &out_Pf[0], GSVD_NY_PAD*GSVD_FLOAT_SIZE, CACHE_FENCE_WAIT);
        GSVD_add_fb_signal((const gsvd_float *)out_Ps, (const gsvd_float *)out_Pf, (const gsvd_float *)GSVD_measurements,
                           (gsvd_float *)out_sum, GSVD_NY_PAD);
        CACHE_wbL1d ((void *) &out_sum[0], GSVD_NY_PAD*GSVD_FLOAT_SIZE, CACHE_FENCE_WAIT);
        ipc_master_set_req(1); // ML 0: Compute slow and fast inputs
    }
    ipc_master_wait_ack();

    ipc_master_set_req(1); // ML 1: Update slow and fast model outputs
    ipc_master_wait_ack();

    CACHE_invL1d ((void *) &GSVD_ctr_input[0], GSVD_NU_PAD*GSVD_FLOAT_SIZE, CACHE_FENCE_WAIT);

#else
    if (restart == 1) {
        GSVD_init_filters();
    }

    GSVD_add_fb_signal((const gsvd_float *)out_Ps, (const gsvd_float *)out_Pf, (const gsvd_float *)GSVD_measurements,
                       (gsvd_float *)out_sum, GSVD_NY_PAD);

    // ML 0: Compute slow and fast inputs
    GSVD_mat_mpy((const gsvd_float *)&GSVD_Ks_gain[0], (const gsvd_float *)out_sum,
                 (DTF_qs_ARR_TYPE *)DTF_qs_get_u0_ptr(), GSVD_KS_W_NROWS, GSVD_KS_W_NCOLS);
    DTF_qs_execute();
    GSVD_double_to_float((const DTF_qs_ARR_TYPE *)DTF_qs_get_y0_ptr(),
                         (gsvd_float *)&GSVD_ctr_input[0], GSVD_NS_W);

    GSVD_mat_mpy((const gsvd_float *)&GSVD_Kf_gain[0], (const gsvd_float *)out_sum,
                 (DTF_qf_ARR_TYPE *)DTF_qf_get_u0_ptr(), GSVD_KF_W_NROWS, GSVD_KF_W_NCOLS);
    DTF_qf_execute();
    GSVD_double_to_float((const DTF_qf_ARR_TYPE *)DTF_qf_get_y0_ptr(),
                         (gsvd_float *)&GSVD_ctr_input[GSVD_NS_PAD], GSVD_NF_W);

    // ML 1: Update slow and fast model outputs
    GSVD_mat_mpy((const gsvd_float *)&GSVD_Ps_gain[0], (const gsvd_float *)&GSVD_ctr_input[0],
                 (DTF_gs_ARR_TYPE *)DTF_gs_get_u0_ptr(), GSVD_PS_W_NROWS, GSVD_PS_W_NCOLS);
    DTF_gs_execute();
    GSVD_double_to_float((const DTF_gs_ARR_TYPE *)DTF_gs_get_y0_ptr(), (gsvd_float *)out_Ps, GSVD_NY_W);

    GSVD_mat_mpy((const gsvd_float *)&GSVD_Pf_gain[0], (const gsvd_float *)&GSVD_ctr_input[GSVD_NS_PAD],
                 (DTF_gf_ARR_TYPE *)DTF_gf_get_u0_ptr(), GSVD_PF_W_NROWS, GSVD_PF_W_NCOLS);
    DTF_gf_execute();
    GSVD_double_to_float((const DTF_gf_ARR_TYPE *)DTF_gf_get_y0_ptr(), (gsvd_float *)out_Pf, GSVD_NY_W);
#endif

    return (gsvd_float *)GSVD_ctr_input;
}

