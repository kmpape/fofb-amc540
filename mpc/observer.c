#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <c6x.h>
#include <ti/csl/csl_chip.h>
#include <csl_cache.h>
#include <csl_cacheAux.h>

#include "fofb_config.h"
#include "mpc/observer.h"
#include "utils/ipc_utils.h"
#include "mpc/fast_gradient_method.h"

#if (XDIR == 1)
#if (FGM_MPC_HORIZON == 1)
#include "OBS_data_c6678_NWORKERS6_x.h"
#else
#include "OBS_data_c6678_NWORKERS6_H2_x.h"
#endif /* FGM_MPC_HORIZON */
#else
#if (FGM_MPC_HORIZON == 1)
#include "OBS_data_c6678_NWORKERS6_y.h"
#else
#include "OBS_data_c6678_NWORKERS6_H2_y.h"
#endif /* FGM_MPC_HORIZON */
#endif /* XDIR */

/* Prototypes */
void OBS_swap_global_pointers(void);
void OBS_swap_local_pointers(void);
void OBS_update_state_global(const obs_float * restrict x_in,
                  const obs_float * restrict u_in,
                  const obs_float A_in, const obs_float B_in,
                  obs_float * restrict x_out);
void OBS_update_delta_y(const obs_float * restrict Cx_in,
                    const obs_float * restrict x7_in,
                    const obs_float * restrict y_in,
                    const obs_float * restrict xd_in,
                    obs_float * restrict delta_y_out);
void OBS_update_delta_x8_or_xd(const obs_float * restrict L_in,
                           const obs_float * restrict delta_y_in,
                           obs_float * restrict delta_x_out);
void OBS_update_x8_or_xd(const obs_float * restrict delta_x_in,
                     obs_float * restrict x_in_out);
void OBS_update_xi(const obs_float * restrict delta_x7_in,
               const obs_float Apowi_in,
               obs_float * restrict xi_in_out);
void OBS_permXN_4waySIMD(const volatile obs_float * volatile in_mat,
                     volatile obs_float * volatile out_mat, const int unroll,
                     const int nrows, const int ncols);
void OBS_vec_copy_vol_vol(const volatile obs_float * restrict in, volatile obs_float * restrict out,
                  const int len);

/* Shared arrays */
#pragma DATA_ALIGN(OBS_delta_y_static,  OBS_ARRAY_ALIGN)
#pragma DATA_ALIGN(OBS_delta_x8_static, OBS_ARRAY_ALIGN)
#pragma DATA_ALIGN(OBS_delta_xd_static, OBS_ARRAY_ALIGN)
#pragma DATA_ALIGN(OBS_x0_new_static,   OBS_ARRAY_ALIGN)
#pragma DATA_ALIGN(OBS_x0_old_static,   OBS_ARRAY_ALIGN)
#pragma DATA_ALIGN(OBS_x1_static,       OBS_ARRAY_ALIGN)
#pragma DATA_ALIGN(OBS_x2_static,       OBS_ARRAY_ALIGN)
#pragma DATA_ALIGN(OBS_x3_static,       OBS_ARRAY_ALIGN)
#pragma DATA_ALIGN(OBS_x4_static,       OBS_ARRAY_ALIGN)
#pragma DATA_ALIGN(OBS_x5_static,       OBS_ARRAY_ALIGN)
#pragma DATA_ALIGN(OBS_x6_static,       OBS_ARRAY_ALIGN)
#pragma DATA_ALIGN(OBS_x7_static,       OBS_ARRAY_ALIGN)
#pragma DATA_ALIGN(OBS_x8_static,       OBS_ARRAY_ALIGN)
#pragma DATA_ALIGN(OBS_xd_static,       OBS_ARRAY_ALIGN)
#pragma SET_DATA_SECTION(".obs_shared_data")
volatile obs_float OBS_delta_y_static[OBS_DIM]={0.0};     // delta_y = y - Cx*x7 - xd
volatile obs_float OBS_delta_x8_static[OBS_DIM]={0.0};    // delta_x7 = Lx*delta_y
volatile obs_float OBS_delta_xd_static[OBS_DIM]={0.0};    // delta_xd = Ld*delta_y
volatile obs_float OBS_x0_new_static[OBS_DIM]={0.0};  // 0 delay  -> RESULT
volatile obs_float OBS_x0_old_static[OBS_DIM]={0.0};  // 0 delay
volatile obs_float OBS_x1_static[OBS_DIM]={0.0};      // 1 step delay
volatile obs_float OBS_x2_static[OBS_DIM]={0.0};      // 2 steps delay
volatile obs_float OBS_x3_static[OBS_DIM]={0.0};      // 3 steps delay
volatile obs_float OBS_x4_static[OBS_DIM]={0.0};      // 4 steps delay
volatile obs_float OBS_x5_static[OBS_DIM]={0.0};      // 5 steps delay
volatile obs_float OBS_x6_static[OBS_DIM]={0.0};      // 6 steps delay
volatile obs_float OBS_x7_static[OBS_DIM]={0.0};      // 7 steps delay
volatile obs_float OBS_x8_static[OBS_DIM]={0.0};      // 8 steps delay
volatile obs_float OBS_xd_static[OBS_DIM]={0.0};      // disturbance  -> RESULT
#pragma SET_DATA_SECTION()

/* Shared pointers */
#pragma DATA_ALIGN(OBS_y_new_global,        OBS_ARRAY_ALIGN)
#pragma DATA_ALIGN(OBS_old_input_global,    OBS_ARRAY_ALIGN)
#pragma SET_DATA_SECTION(".obs_shared_data")
volatile obs_float * volatile OBS_y_new_global; // INPUT
volatile obs_float * volatile OBS_old_input_global; // INPUT
#pragma SET_DATA_SECTION()

/* Local arrays */
#pragma DATA_ALIGN(OBS_Lx_local,    OBS_ARRAY_ALIGN)
#pragma DATA_ALIGN(OBS_Ld_local,    OBS_ARRAY_ALIGN)
#pragma DATA_ALIGN(OBS_Cx_local,    OBS_ARRAY_ALIGN)
#pragma SET_DATA_SECTION(".obs_local_data")
volatile obs_float OBS_Lx_local[OBS_W_NROWS*OBS_DIM];
volatile obs_float OBS_Ld_local[OBS_W_NROWS*OBS_DIM];
volatile obs_float OBS_Cx_local[OBS_W_NROWS*OBS_DIM];
#pragma SET_DATA_SECTION()

/* Local pointers */
#pragma DATA_ALIGN(OBS_xd_local,    OBS_ARRAY_ALIGN)
#pragma SET_DATA_SECTION(".obs_local_data")
volatile obs_float * volatile OBS_xd_local;
volatile obs_float * volatile OBS_x0_new_local;
volatile obs_float * volatile OBS_x0_old_local;
volatile obs_float * volatile OBS_x1_local;
volatile obs_float * volatile OBS_x2_local;
volatile obs_float * volatile OBS_x3_local;
volatile obs_float * volatile OBS_x4_local;
volatile obs_float * volatile OBS_x5_local;
volatile obs_float * volatile OBS_x6_local;
volatile obs_float * volatile OBS_x7_local;
volatile obs_float * volatile OBS_x8_local;
volatile obs_float * volatile OBS_delta_y_local;
volatile obs_float * volatile OBS_delta_x8_local;
volatile obs_float * volatile OBS_delta_xd_local;
volatile obs_float * volatile OBS_old_input_local;
volatile obs_float * volatile OBS_y_new_local;
volatile obs_float * volatile OBS_delta_y_global;
volatile obs_float * volatile OBS_delta_x8_global;
volatile obs_float * volatile OBS_delta_xd_global;
volatile obs_float * volatile OBS_xd_global;
volatile obs_float * volatile OBS_x0_new_global;
volatile obs_float * volatile OBS_x0_old_global;
volatile obs_float * volatile OBS_x1_global;
volatile obs_float * volatile OBS_x2_global;
volatile obs_float * volatile OBS_x3_global;
volatile obs_float * volatile OBS_x4_global;
volatile obs_float * volatile OBS_x5_global;
volatile obs_float * volatile OBS_x6_global;
volatile obs_float * volatile OBS_x7_global;
volatile obs_float * volatile OBS_x8_global;
#pragma SET_DATA_SECTION()

/* Shared scalars */
#pragma SET_DATA_SECTION(".obs_shared_const")
const obs_float OBS_Ax = 0.644150443975408;
const obs_float OBS_Bx = 0.355849556024592;
const obs_float OBS_Ax_pow_1 = 0.644150443975408;
const obs_float OBS_Ax_pow_2 = 0.414929794473715;
const obs_float OBS_Ax_pow_3 = 0.267277211328869;
const obs_float OBS_Ax_pow_4 = 0.172166734342000;
const obs_float OBS_Ax_pow_5 = 0.110901278364195;
const obs_float OBS_Ax_pow_6 = 0.071437107695737;
const obs_float OBS_Ax_pow_7 = 0.046016244638528;
const obs_float OBS_Ax_pow_8 = 0.029641384413989;
#pragma SET_DATA_SECTION()

/* Local scalars */
#pragma SET_DATA_SECTION(".obs_local_data")
Uint32 volatile OBS_selfId;
#pragma SET_DATA_SECTION()

void OBS_vec_init(obs_float volatile * out, const obs_float in)
{
    int i;
    for (i = 0; i < OBS_DIM; i++)
        out[i] = in;
}

obs_float volatile * OBS_get_xd(void)
{
    return &(OBS_xd_global[0]);
}

obs_float volatile * OBS_get_x0_new(void)
{
    return &(OBS_x0_new_global[0]);
}

/*** State update functions ***/
void OBS_swap_global_pointers(void)
{
    volatile obs_float * volatile tmp_x0_new_global = OBS_x0_new_global;
    OBS_x0_new_global = OBS_x8_global;
    OBS_x0_old_global = tmp_x0_new_global;
    OBS_x8_global = OBS_x7_global;
    OBS_x7_global = OBS_x6_global;
    OBS_x6_global = OBS_x5_global;
    OBS_x5_global = OBS_x4_global;
    OBS_x4_global = OBS_x3_global;
    OBS_x3_global = OBS_x2_global;
    OBS_x2_global = OBS_x1_global;
    OBS_x1_global = OBS_x0_old_global;
}

void OBS_swap_local_pointers(void)
{
    volatile obs_float * volatile tmp_x0_new_local = OBS_x0_new_local;
    OBS_x0_new_local = OBS_x8_local;
    OBS_x0_old_local = tmp_x0_new_local;
    OBS_x8_local = OBS_x7_local;
    OBS_x7_local = OBS_x6_local;
    OBS_x6_local = OBS_x5_local;
    OBS_x5_local = OBS_x4_local;
    OBS_x4_local = OBS_x3_local;
    OBS_x3_local = OBS_x2_local;
    OBS_x2_local = OBS_x1_local;
    OBS_x1_local = OBS_x0_old_local;
}

// x_out = A_scalar*x_in + B_scalar*u_in
void OBS_update_state_global(const obs_float * restrict x_in,
                             const obs_float * restrict u_in,
                             const obs_float A_in, const obs_float B_in,
                             obs_float * restrict x_out)
{
    int i;

    _nassert((int) x_in % OBS_ARRAY_ALIGN == 0);
    _nassert((int) u_in % OBS_ARRAY_ALIGN == 0);
    _nassert((int) x_out % OBS_ARRAY_ALIGN == 0);

#pragma MUST_ITERATE(OBS_DIM, OBS_DIM)
    for (i = 0; i < OBS_DIM; i++)
    {
#if (FGM_MPC_HORIZON == 2)
        x_out[i] = A_in * x_in[i] + B_in * u_in[2*i];
#else
        x_out[i] = A_in * x_in[i] + B_in * u_in[i];
#endif
    }
}

// delta_y = y - Cx*x7 - xd
#ifdef OBS_UNROLL
void OBS_update_delta_y(const obs_float * restrict Cx_in,
                        const obs_float * restrict x8_in,
                        const obs_float * restrict y_in,
                        const obs_float * restrict xd_in,
                        obs_float * restrict delta_y_out)
{
    int i, j, ind_shift;

    _nassert((int) Cx_in % OBS_ARRAY_ALIGN == 0);
    _nassert((int) x8_in % OBS_ARRAY_ALIGN == 0);
    _nassert((int) y_in % OBS_ARRAY_ALIGN == 0);
    _nassert((int) xd_in % OBS_ARRAY_ALIGN == 0);
    _nassert((int) delta_y_out % OBS_ARRAY_ALIGN == 0);

#pragma MUST_ITERATE(OBS_W_NROWS/8, OBS_W_NROWS/8)
#pragma UNROLL(1)
    for (i = 0, ind_shift = 0; i < OBS_W_NROWS; i += 8)
    {
        __float2_t tmp_sub_0;
        __float2_t tmp_sub_1;
        __float2_t tmp_sub_2;
        __float2_t tmp_sub_3;
        __float2_t row_res_0 = 0.0;
        __float2_t row_res_1 = 0.0;
        __float2_t row_res_2 = 0.0;
        __float2_t row_res_3 = 0.0;
        __float2_t row_res_4 = 0.0;
        __float2_t row_res_5 = 0.0;
        __float2_t row_res_6 = 0.0;
        __float2_t row_res_7 = 0.0;

#pragma MUST_ITERATE(OBS_W_NCOLS/4, OBS_W_NCOLS/4)
#pragma UNROLL(1)
        for (j = 0; j < OBS_W_NCOLS; j += 4, ind_shift += 32)
        {

            __x128_t f4_in_vec = _f2to128(_amem8_f2_const(&x8_in[j]),
                                          _amem8_f2_const(&x8_in[j + 2]));

            __x128_t f4_in_mat_row0 = _f2to128(
                    _amem8_f2_const(&Cx_in[ind_shift]),
                    _amem8_f2_const(&Cx_in[ind_shift + 2]));
            __x128_t f4_in_mat_row1 = _f2to128(
                    _amem8_f2_const(&Cx_in[ind_shift + 4]),
                    _amem8_f2_const(&Cx_in[ind_shift + 6]));
            __x128_t f4_in_mat_row2 = _f2to128(
                    _amem8_f2_const(&Cx_in[ind_shift + 8]),
                    _amem8_f2_const(&Cx_in[ind_shift + 10]));
            __x128_t f4_in_mat_row3 = _f2to128(
                    _amem8_f2_const(&Cx_in[ind_shift + 12]),
                    _amem8_f2_const(&Cx_in[ind_shift + 14]));
            __x128_t f4_in_mat_row4 = _f2to128(
                    _amem8_f2_const(&Cx_in[ind_shift + 16]),
                    _amem8_f2_const(&Cx_in[ind_shift + 18]));
            __x128_t f4_in_mat_row5 = _f2to128(
                    _amem8_f2_const(&Cx_in[ind_shift + 20]),
                    _amem8_f2_const(&Cx_in[ind_shift + 22]));
            __x128_t f4_in_mat_row6 = _f2to128(
                    _amem8_f2_const(&Cx_in[ind_shift + 24]),
                    _amem8_f2_const(&Cx_in[ind_shift + 26]));
            __x128_t f4_in_mat_row7 = _f2to128(
                    _amem8_f2_const(&Cx_in[ind_shift + 28]),
                    _amem8_f2_const(&Cx_in[ind_shift + 30]));

            __x128_t f4_tmpres_row0 = _qmpysp(f4_in_mat_row0, f4_in_vec);
            __x128_t f4_tmpres_row1 = _qmpysp(f4_in_mat_row1, f4_in_vec);
            __x128_t f4_tmpres_row2 = _qmpysp(f4_in_mat_row2, f4_in_vec);
            __x128_t f4_tmpres_row3 = _qmpysp(f4_in_mat_row3, f4_in_vec);
            __x128_t f4_tmpres_row4 = _qmpysp(f4_in_mat_row4, f4_in_vec);
            __x128_t f4_tmpres_row5 = _qmpysp(f4_in_mat_row5, f4_in_vec);
            __x128_t f4_tmpres_row6 = _qmpysp(f4_in_mat_row6, f4_in_vec);
            __x128_t f4_tmpres_row7 = _qmpysp(f4_in_mat_row7, f4_in_vec);

            row_res_0 = _daddsp(
                    row_res_0,
                    _daddsp(_hif2_128(f4_tmpres_row0),
                            _lof2_128(f4_tmpres_row0)));
            row_res_1 = _daddsp(
                    row_res_1,
                    _daddsp(_hif2_128(f4_tmpres_row1),
                            _lof2_128(f4_tmpres_row1)));
            row_res_2 = _daddsp(
                    row_res_2,
                    _daddsp(_hif2_128(f4_tmpres_row2),
                            _lof2_128(f4_tmpres_row2)));
            row_res_3 = _daddsp(
                    row_res_3,
                    _daddsp(_hif2_128(f4_tmpres_row3),
                            _lof2_128(f4_tmpres_row3)));
            row_res_4 = _daddsp(
                    row_res_4,
                    _daddsp(_hif2_128(f4_tmpres_row4),
                            _lof2_128(f4_tmpres_row4)));
            row_res_5 = _daddsp(
                    row_res_5,
                    _daddsp(_hif2_128(f4_tmpres_row5),
                            _lof2_128(f4_tmpres_row5)));
            row_res_6 = _daddsp(
                    row_res_6,
                    _daddsp(_hif2_128(f4_tmpres_row6),
                            _lof2_128(f4_tmpres_row6)));
            row_res_7 = _daddsp(
                    row_res_7,
                    _daddsp(_hif2_128(f4_tmpres_row7),
                            _lof2_128(f4_tmpres_row7)));
        }
        tmp_sub_0 = _dsubsp(_amem8_f2_const(&y_in[i]),
                            _amem8_f2_const(&xd_in[i]));
        tmp_sub_1 = _dsubsp(_amem8_f2_const(&y_in[i + 2]),
                            _amem8_f2_const(&xd_in[i + 2]));
        tmp_sub_2 = _dsubsp(_amem8_f2_const(&y_in[i + 4]),
                            _amem8_f2_const(&xd_in[i + 4]));
        tmp_sub_3 = _dsubsp(_amem8_f2_const(&y_in[i + 6]),
                            _amem8_f2_const(&xd_in[i + 6]));

        _amem8_f2(&delta_y_out[i]) = _dsubsp(tmp_sub_0,
                _ftof2(_lof2(row_res_1) + _hif2(row_res_1),
                       _lof2(row_res_0) + _hif2(row_res_0)));
        _amem8_f2(&delta_y_out[i + 2]) = _dsubsp(tmp_sub_1,
                _ftof2(_lof2(row_res_3) + _hif2(row_res_3),
                       _lof2(row_res_2) + _hif2(row_res_2)));
        _amem8_f2(&delta_y_out[i + 4]) = _dsubsp(tmp_sub_2,
                _ftof2(_lof2(row_res_5) + _hif2(row_res_5),
                       _lof2(row_res_4) + _hif2(row_res_4)));
        _amem8_f2(&delta_y_out[i + 6]) = _dsubsp(tmp_sub_3,
                _ftof2(_lof2(row_res_7) + _hif2(row_res_7),
                       _lof2(row_res_6) + _hif2(row_res_6)));
    }
}
#else
void OBS_update_delta_y(const obs_float * restrict Cx_in,
                        const obs_float * restrict x8_in,
                        const obs_float * restrict y_in,
                        const obs_float * restrict xd_in,
                        obs_float * restrict delta_y_out)
{
    int i, j, ind_shift;
    for (i = 0, ind_shift = 0; i < OBS_W_NROWS; i++, ind_shift+=OBS_W_NCOLS)
    {
        obs_float tmp_row_res = 0.0;
        for (j = 0; j < OBS_W_NCOLS; j++)
        {
            tmp_row_res += Cx_in[ind_shift + j] * x8_in[j];
        }
        delta_y_out[i] = y_in[i] - tmp_row_res - xd_in[i];
    }

}
#endif


// delta_x8 = Lx*delta_y or delta_xd = Ld*delta_y
#ifdef OBS_UNROLL
void OBS_update_delta_x8_or_xd(const obs_float * restrict L_in,
                               const obs_float * restrict delta_y_in,
                               obs_float * restrict delta_x_out)
{
    int i, j, ind_shift;
    _nassert((int) L_in % OBS_ARRAY_ALIGN == 0);
    _nassert((int) delta_y_in % OBS_ARRAY_ALIGN == 0);
    _nassert((int) delta_x_out % OBS_ARRAY_ALIGN == 0);

#pragma MUST_ITERATE(OBS_W_NROWS/8, OBS_W_NROWS/8)
#pragma UNROLL(1)
    for (i = 0, ind_shift = 0; i < OBS_W_NROWS; i += 8)
    {
        __float2_t row_res_0 = 0.0;
        __float2_t row_res_1 = 0.0;
        __float2_t row_res_2 = 0.0;
        __float2_t row_res_3 = 0.0;
        __float2_t row_res_4 = 0.0;
        __float2_t row_res_5 = 0.0;
        __float2_t row_res_6 = 0.0;
        __float2_t row_res_7 = 0.0;

#pragma MUST_ITERATE(OBS_W_NCOLS/4, OBS_W_NCOLS/4)
#pragma UNROLL(1)
        for (j = 0; j < OBS_W_NCOLS; j += 4, ind_shift += 32)
        {

            __x128_t f4_in_vec = _f2to128(_amem8_f2_const(&delta_y_in[j]),
                                          _amem8_f2_const(&delta_y_in[j + 2]));

            __x128_t f4_in_mat_row0 = _f2to128(
                    _amem8_f2_const(&L_in[ind_shift]),
                    _amem8_f2_const(&L_in[ind_shift + 2]));
            __x128_t f4_in_mat_row1 = _f2to128(
                    _amem8_f2_const(&L_in[ind_shift + 4]),
                    _amem8_f2_const(&L_in[ind_shift + 6]));
            __x128_t f4_in_mat_row2 = _f2to128(
                    _amem8_f2_const(&L_in[ind_shift + 8]),
                    _amem8_f2_const(&L_in[ind_shift + 10]));
            __x128_t f4_in_mat_row3 = _f2to128(
                    _amem8_f2_const(&L_in[ind_shift + 12]),
                    _amem8_f2_const(&L_in[ind_shift + 14]));
            __x128_t f4_in_mat_row4 = _f2to128(
                    _amem8_f2_const(&L_in[ind_shift + 16]),
                    _amem8_f2_const(&L_in[ind_shift + 18]));
            __x128_t f4_in_mat_row5 = _f2to128(
                    _amem8_f2_const(&L_in[ind_shift + 20]),
                    _amem8_f2_const(&L_in[ind_shift + 22]));
            __x128_t f4_in_mat_row6 = _f2to128(
                    _amem8_f2_const(&L_in[ind_shift + 24]),
                    _amem8_f2_const(&L_in[ind_shift + 26]));
            __x128_t f4_in_mat_row7 = _f2to128(
                    _amem8_f2_const(&L_in[ind_shift + 28]),
                    _amem8_f2_const(&L_in[ind_shift + 30]));


            __x128_t f4_tmpres_row0 = _qmpysp(f4_in_mat_row0, f4_in_vec);
            __x128_t f4_tmpres_row1 = _qmpysp(f4_in_mat_row1, f4_in_vec);
            __x128_t f4_tmpres_row2 = _qmpysp(f4_in_mat_row2, f4_in_vec);
            __x128_t f4_tmpres_row3 = _qmpysp(f4_in_mat_row3, f4_in_vec);
            __x128_t f4_tmpres_row4 = _qmpysp(f4_in_mat_row4, f4_in_vec);
            __x128_t f4_tmpres_row5 = _qmpysp(f4_in_mat_row5, f4_in_vec);
            __x128_t f4_tmpres_row6 = _qmpysp(f4_in_mat_row6, f4_in_vec);
            __x128_t f4_tmpres_row7 = _qmpysp(f4_in_mat_row7, f4_in_vec);

            row_res_0 = _daddsp(
                    row_res_0,
                    _daddsp(_hif2_128(f4_tmpres_row0),
                            _lof2_128(f4_tmpres_row0)));
            row_res_1 = _daddsp(
                    row_res_1,
                    _daddsp(_hif2_128(f4_tmpres_row1),
                            _lof2_128(f4_tmpres_row1)));
            row_res_2 = _daddsp(
                    row_res_2,
                    _daddsp(_hif2_128(f4_tmpres_row2),
                            _lof2_128(f4_tmpres_row2)));
            row_res_3 = _daddsp(
                    row_res_3,
                    _daddsp(_hif2_128(f4_tmpres_row3),
                            _lof2_128(f4_tmpres_row3)));
            row_res_4 = _daddsp(
                    row_res_4,
                    _daddsp(_hif2_128(f4_tmpres_row4),
                            _lof2_128(f4_tmpres_row4)));
            row_res_5 = _daddsp(
                    row_res_5,
                    _daddsp(_hif2_128(f4_tmpres_row5),
                            _lof2_128(f4_tmpres_row5)));
            row_res_6 = _daddsp(
                    row_res_6,
                    _daddsp(_hif2_128(f4_tmpres_row6),
                            _lof2_128(f4_tmpres_row6)));
            row_res_7 = _daddsp(
                    row_res_7,
                    _daddsp(_hif2_128(f4_tmpres_row7),
                            _lof2_128(f4_tmpres_row7)));
        }
        _amem8_f2(&delta_x_out[i]) = _ftof2(_lof2(row_res_1) + _hif2(row_res_1),
                       _lof2(row_res_0) + _hif2(row_res_0));
        _amem8_f2(&delta_x_out[i + 2]) = _ftof2(_lof2(row_res_3) + _hif2(row_res_3),
                       _lof2(row_res_2) + _hif2(row_res_2));
        _amem8_f2(&delta_x_out[i + 4]) = _ftof2(_lof2(row_res_5) + _hif2(row_res_5),
                       _lof2(row_res_4) + _hif2(row_res_4));
        _amem8_f2(&delta_x_out[i + 6]) = _ftof2(_lof2(row_res_7) + _hif2(row_res_7),
                       _lof2(row_res_6) + _hif2(row_res_6));
    }
}
#else
void OBS_update_delta_x8_or_xd(const obs_float * restrict L_in,
                               const obs_float * restrict delta_y_in,
                               obs_float * restrict delta_x_out)
{
    int i, j, ind_shift;
    for (i = 0, ind_shift = 0; i < OBS_W_NROWS; i++, ind_shift+=OBS_W_NCOLS)
    {
        obs_float tmp_row_res = 0.0;
        for (j = 0; j < OBS_W_NCOLS; j++)
        {
            tmp_row_res += L_in[ind_shift + j] * delta_y_in[j];
        }
        delta_x_out[i] = tmp_row_res;
    }
}

#endif

// x7 += delta_x7 or xd += delta_xd
void OBS_update_x8_or_xd(const obs_float * restrict delta_x_in,
                     obs_float * restrict x_in_out)
{
    int i;
    _nassert((int) x_in_out % OBS_ARRAY_ALIGN == 0);
    _nassert((int) delta_x_in % OBS_ARRAY_ALIGN == 0);
    for (i = 0; i < OBS_W_NROWS; i++)
    {
        x_in_out[i] += delta_x_in[i];
    }
}

// xi += Apowi * delta_x8
void OBS_update_xi(const obs_float * restrict delta_x8_in,
               const obs_float Apowi_in,
               obs_float * restrict xi_in_out)
{
    int i;
    _nassert((int) xi_in_out % OBS_ARRAY_ALIGN == 0);
    _nassert((int) delta_x8_in % OBS_ARRAY_ALIGN == 0);
    for (i = 0; i < OBS_W_NROWS; i++)
    {
        xi_in_out[i] += Apowi_in * delta_x8_in[i];
    }
}

int OBS_arr_ind(const int ncols, const int i_row, const int i_col)
{
    return i_col + i_row * ncols;
}

void OBS_permXN_4waySIMD(const volatile obs_float * volatile in_mat,
                     volatile obs_float * volatile out_mat, const int unroll,
                     const int nrows, const int ncols)
{
    int ind_out = 0, row_block, col, row_unroll;

    assert((ncols % 4) == 0);
    assert((nrows % unroll) == 0);

#pragma UNROLL(1)
    for (row_block = 0, ind_out = 0; row_block < nrows; row_block += unroll)
    {
#pragma UNROLL(1)
        for (col = 0; col < ncols; col += 4)
        {
#pragma UNROLL(1)
            for (row_unroll = 0; row_unroll < unroll;
                    row_unroll += 1, ind_out += 4)
            {
                out_mat[ind_out] = in_mat[OBS_arr_ind(ncols, row_block + row_unroll,
                                                  col)];
                out_mat[ind_out + 1] = in_mat[OBS_arr_ind(ncols,
                                                      row_block + row_unroll,
                                                      col + 1)];
                out_mat[ind_out + 2] = in_mat[OBS_arr_ind(ncols,
                                                      row_block + row_unroll,
                                                      col + 2)];
                out_mat[ind_out + 3] = in_mat[OBS_arr_ind(ncols,
                                                      row_block + row_unroll,
                                                      col + 3)];
            }
        }
    }
}

void OBS_vec_copy_vol_vol(const volatile obs_float * restrict in, volatile obs_float * restrict out,
                  const int len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        out[i] = in[i];
    }
}


#pragma FUNCTION_OPTIONS(OBS_initialize_master, "--opt_level=off --opt_for_speed=0")
void OBS_initialize_master(void)
{
    int i;

    OBS_selfId = 0;

    OBS_vec_init(OBS_delta_y_static,0.0);
    OBS_vec_init(OBS_delta_x8_static,0.0);
    OBS_vec_init(OBS_delta_xd_static,0.0);
    OBS_vec_init(OBS_xd_static,0.0);
    OBS_vec_init(OBS_x0_new_static,0.0);
    OBS_vec_init(OBS_x0_old_static,0.0);
    OBS_vec_init(OBS_x1_static,0.0);
    OBS_vec_init(OBS_x2_static,0.0);
    OBS_vec_init(OBS_x3_static,0.0);
    OBS_vec_init(OBS_x4_static,0.0);
    OBS_vec_init(OBS_x5_static,0.0);
    OBS_vec_init(OBS_x6_static,0.0);
    OBS_vec_init(OBS_x7_static,0.0);
    OBS_vec_init(OBS_x8_static,0.0);
    CACHE_wbL1d((void *) OBS_delta_y_static, OBS_BYTES_GLOBAL_ARRAYS, CACHE_WAIT);
    CACHE_wbL1d((void *) OBS_delta_x8_static, OBS_BYTES_GLOBAL_ARRAYS, CACHE_WAIT);
    CACHE_wbL1d((void *) OBS_delta_xd_static, OBS_BYTES_GLOBAL_ARRAYS, CACHE_WAIT);
    CACHE_wbL1d((void *) OBS_xd_static, OBS_BYTES_GLOBAL_ARRAYS, CACHE_WAIT);
    CACHE_wbL1d((void *) OBS_x0_new_static, OBS_BYTES_GLOBAL_ARRAYS, CACHE_WAIT);
    CACHE_wbL1d((void *) OBS_x0_old_static, OBS_BYTES_GLOBAL_ARRAYS, CACHE_WAIT);
    CACHE_wbL1d((void *) OBS_x1_static, OBS_BYTES_GLOBAL_ARRAYS, CACHE_WAIT);
    CACHE_wbL1d((void *) OBS_x2_static, OBS_BYTES_GLOBAL_ARRAYS, CACHE_WAIT);
    CACHE_wbL1d((void *) OBS_x3_static, OBS_BYTES_GLOBAL_ARRAYS, CACHE_WAIT);
    CACHE_wbL1d((void *) OBS_x4_static, OBS_BYTES_GLOBAL_ARRAYS, CACHE_WAIT);
    CACHE_wbL1d((void *) OBS_x5_static, OBS_BYTES_GLOBAL_ARRAYS, CACHE_WAIT);
    CACHE_wbL1d((void *) OBS_x6_static, OBS_BYTES_GLOBAL_ARRAYS, CACHE_WAIT);
    CACHE_wbL1d((void *) OBS_x7_static, OBS_BYTES_GLOBAL_ARRAYS, CACHE_WAIT);
    CACHE_wbL1d((void *) OBS_x8_static, OBS_BYTES_GLOBAL_ARRAYS, CACHE_WAIT);

    OBS_delta_y_global = &(OBS_delta_y_static[0]);
    OBS_delta_x8_global = &(OBS_delta_x8_static[0]);
    OBS_delta_xd_global = &(OBS_delta_xd_static[0]);
    OBS_xd_global = &(OBS_xd_static[0]);
    OBS_x0_new_global = &(OBS_x0_new_static[0]);
    OBS_x0_old_global = &(OBS_x0_old_static[0]);
    OBS_x1_global = &(OBS_x1_static[0]);
    OBS_x2_global = &(OBS_x2_static[0]);
    OBS_x3_global = &(OBS_x3_static[0]);
    OBS_x4_global = &(OBS_x4_static[0]);
    OBS_x5_global = &(OBS_x5_static[0]);
    OBS_x6_global = &(OBS_x6_static[0]);
    OBS_x7_global = &(OBS_x7_static[0]);
    OBS_x8_global = &(OBS_x8_static[0]);

#if (OBS_DEBUG_LEVEL > 1)
    printf("OBS_Lx_static[%d]=%.4f,", 0, OBS_Cx_static[0]);
    printf("OBS_Ld_static[%d]=%.4f,", 0, OBS_Ld_static[0]);
    printf("OBS_Cx_static[%d]=%.4f,", 0, OBS_Cx_static[0]);
    printf("OBS_xd_static[%d]=%.4f\n", 0, OBS_xd_static[0]);
    printf("OBS_x0_new_static[%d]=%.4f,", 0, OBS_x0_new_static[0]);
    printf("OBS_x0_old_static[%d]=%.4f,", 0, OBS_x0_old_static[0]);
    printf("OBS_x1_static[%d]=%.4f,", 0, OBS_x1_static[0]);
    printf("OBS_x2_static[%d]=%.4f\n", 0, OBS_x2_static[0]);
    printf("OBS_x3_static[%d]=%.4f,", 0, OBS_x3_static[0]);
    printf("OBS_x4_static[%d]=%.4f,", 0, OBS_x4_static[0]);
    printf("OBS_x5_static[%d]=%.4f,", 0, OBS_x5_static[0]);
    printf("OBS_x6_static[%d]=%.4f,", 0, OBS_x6_static[0]);
    printf("OBS_x7_static[%d]=%.4f\n", 0, OBS_x7_static[0]);
    printf("OBS_x8_static[%d]=%.4f\n", 0, OBS_x8_static[0]);
#endif
}

#pragma FUNCTION_OPTIONS(OBS_initialize_worker, "--opt_level=off --opt_for_speed=0")
void OBS_initialize_worker(volatile int selfId)
{
    int ind_shift,i;

    OBS_selfId = selfId;
    assert(OBS_selfId >= 1);

    /* Assign workers part of matrices */
    ind_shift = (selfId - 1) * OBS_W_NROWS * OBS_W_NCOLS;
#ifdef OBS_UNROLL
    OBS_permXN_4waySIMD(&(Lx_pad[ind_shift]), OBS_Lx_local, 8, OBS_W_NROWS, OBS_W_NCOLS);
    OBS_permXN_4waySIMD(&(Ld_pad[ind_shift]), OBS_Ld_local, 8, OBS_W_NROWS, OBS_W_NCOLS);
    OBS_permXN_4waySIMD(&(Cx_pad[ind_shift]), OBS_Cx_local, 8, OBS_W_NROWS, OBS_W_NCOLS);
#else
    OBS_vec_copy_vol_vol(&Lx_pad[ind_shift], OBS_Lx_local, OBS_W_NROWS * OBS_W_NCOLS);
    OBS_vec_copy_vol_vol(&Ld_pad[ind_shift], OBS_Ld_local, OBS_W_NROWS * OBS_W_NCOLS);
    OBS_vec_copy_vol_vol(&Cx_pad[ind_shift], OBS_Cx_local, OBS_W_NROWS * OBS_W_NCOLS);
#endif

    CACHE_invL1d((void *) &OBS_xd_static[0], OBS_BYTES_GLOBAL_ARRAYS, CACHE_WAIT);
    CACHE_invL1d((void *) &OBS_x0_new_static[0], OBS_BYTES_GLOBAL_ARRAYS, CACHE_WAIT);
    CACHE_invL1d((void *) &OBS_x0_old_static[0], OBS_BYTES_GLOBAL_ARRAYS, CACHE_WAIT);
    CACHE_invL1d((void *) &OBS_x1_static[0], OBS_BYTES_GLOBAL_ARRAYS, CACHE_WAIT);
    CACHE_invL1d((void *) &OBS_x2_static[0], OBS_BYTES_GLOBAL_ARRAYS, CACHE_WAIT);
    CACHE_invL1d((void *) &OBS_x3_static[0], OBS_BYTES_GLOBAL_ARRAYS, CACHE_WAIT);
    CACHE_invL1d((void *) &OBS_x4_static[0], OBS_BYTES_GLOBAL_ARRAYS, CACHE_WAIT);
    CACHE_invL1d((void *) &OBS_x5_static[0], OBS_BYTES_GLOBAL_ARRAYS, CACHE_WAIT);
    CACHE_invL1d((void *) &OBS_x6_static[0], OBS_BYTES_GLOBAL_ARRAYS, CACHE_WAIT);
    CACHE_invL1d((void *) &OBS_x7_static[0], OBS_BYTES_GLOBAL_ARRAYS, CACHE_WAIT);
    CACHE_invL1d((void *) &OBS_x8_static[0], OBS_BYTES_GLOBAL_ARRAYS, CACHE_WAIT);

    /* Assign pointers */
    ind_shift = (selfId - 1) * OBS_W_NROWS;
    OBS_xd_local = &(OBS_xd_static[ind_shift]);
    OBS_x0_new_local = &(OBS_x0_new_static[ind_shift]);
    OBS_x0_old_local = &(OBS_x0_old_static[ind_shift]);
    OBS_x1_local = &(OBS_x1_static[ind_shift]);
    OBS_x2_local = &(OBS_x2_static[ind_shift]);
    OBS_x3_local = &(OBS_x3_static[ind_shift]);
    OBS_x4_local = &(OBS_x4_static[ind_shift]);
    OBS_x5_local = &(OBS_x5_static[ind_shift]);
    OBS_x6_local = &(OBS_x6_static[ind_shift]);
    OBS_x7_local = &(OBS_x7_static[ind_shift]);
    OBS_x8_local = &(OBS_x8_static[ind_shift]);
    OBS_delta_y_local = &(OBS_delta_y_static[ind_shift]);
    OBS_delta_x8_local = &(OBS_delta_x8_static[ind_shift]);
    OBS_delta_xd_local = &(OBS_delta_xd_static[ind_shift]);

    OBS_delta_y_global = &(OBS_delta_y_static[0]);
    OBS_delta_x8_global = &(OBS_delta_x8_static[0]);
    OBS_delta_xd_global = &(OBS_delta_xd_static[0]);
    OBS_xd_global = &(OBS_xd_static[0]);
    OBS_x0_new_global = &(OBS_x0_new_static[0]);
    OBS_x0_old_global = &(OBS_x0_old_static[0]);
    OBS_x1_global = &(OBS_x1_static[0]);
    OBS_x2_global = &(OBS_x2_static[0]);
    OBS_x3_global = &(OBS_x3_static[0]);
    OBS_x4_global = &(OBS_x4_static[0]);
    OBS_x5_global = &(OBS_x5_static[0]);
    OBS_x6_global = &(OBS_x6_static[0]);
    OBS_x7_global = &(OBS_x7_static[0]);
    OBS_x8_global = &(OBS_x8_static[0]);

#if (OBS_DEBUG_LEVEL > 1)
    if (OBS_selfId == 1) {
        printf("OBS_Lx_local[%d]=%.4f, ", 0, OBS_Lx_local[0]);
        printf("OBS_Ld_local[%d]=%.4f, ", 0, OBS_Ld_local[0]);
        printf("OBS_Cx_local[%d]=%.4f\n", 0, OBS_Cx_local[0]);

        printf("OBS_x1_global[%d]=%.4f, ", 0, OBS_x1_global[0]);
        printf("OBS_x2_global[%d]=%.4f, ", 0, OBS_x2_global[0]);
        printf("OBS_x3_global[%d]=%.4f, ", 0, OBS_x3_global[0]);
        printf("OBS_x4_global[%d]=%.4f, ", 0, OBS_x4_global[0]);
        printf("OBS_x5_global[%d]=%.4f, ", 0, OBS_x5_global[0]);
        printf("OBS_x6_global[%d]=%.4f, ", 0, OBS_x6_global[0]);
        printf("OBS_x7_global[%d]=%.4f\n", 0, OBS_x7_global[0]);
        printf("OBS_x8_global[%d]=%.4f\n", 0, OBS_x8_global[0]);

        printf("OBS_xd_local[%d]=%.4f, ", 0, OBS_xd_local[0]);
        printf("OBS_xd_static[%d]=%.4f\n", 0, OBS_xd_static[0]);

        printf("OBS_x0_new_local[%d]=%.4f, ", 0, OBS_x0_new_local[0]);
        printf("OBS_x0_old_local[%d]=%.4f\n", 0, OBS_x0_old_local[0]);
    }
#endif
}


// Observer update
#pragma FUNCTION_OPTIONS(OBS_update_observer_master, "--opt_level=off --opt_for_speed=0")
void OBS_update_observer_master(const obs_float * y_meas, const obs_float * u_old)
{
#if (OBS_DEBUG_LEVEL > 0)
    int i;
#endif
    ipc_master_set_req(1);      // ML 0
    OBS_swap_global_pointers();
    OBS_swap_local_pointers();

#if (OBS_DEBUG_LEVEL > 1)
    printf("Master: Swap pointers\n");
#endif


    // Master updates the whole state
    OBS_update_state_global((const obs_float *)OBS_x0_old_global,
                            (const obs_float *)u_old,
                            OBS_Ax, OBS_Bx, (obs_float *)OBS_x0_new_global);
    CACHE_wbL1d((void *) (&(OBS_x0_new_global[0])), OBS_BYTES_GLOBAL_ARRAYS, CACHE_WAIT);

#if (OBS_DEBUG_LEVEL > 1)
    printf("OBS_update_state_global\n");
    for (i = 0; i < NUMSLAVES; i++)
    {
        printf("OBS_x0_old_global[%d]=%.4f,", i * OBS_W_NROWS, OBS_x0_old_global[i * OBS_W_NROWS]);
        printf("OBS_x0_old_global[%d]=%.4f\n", (i+1) * OBS_W_NROWS - 1, OBS_x0_old_global[(i+1) * OBS_W_NROWS - 1]);
    }
    for (i = 0; i < NUMSLAVES; i++)
    {
        printf("OBS_old_input_global[%d]=%.4f,", i * OBS_W_NROWS, u_old[i * OBS_W_NROWS]);
        printf("OBS_old_input_global[%d]=%.4f\n", (i+1) * OBS_W_NROWS - 1, u_old[(i+1) * OBS_W_NROWS - 1]);
    }
    for (i = 0; i < NUMSLAVES; i++)
    {
        printf("OBS_xd_static[%d]=%.4f,", i * OBS_W_NROWS, OBS_xd_static[i * OBS_W_NROWS]);
        printf("OBS_xd_static[%d]=%.4f\n", (i+1) * OBS_W_NROWS - 1, OBS_xd_static[(i+1) * OBS_W_NROWS - 1]);
    }
#endif
#if (OBS_DEBUG_LEVEL > 0)
    for (i = 0; i < NUMSLAVES; i++)
    {
        printf("OBS_x0_new_global[%d]=%.4f,", i * OBS_W_NROWS, OBS_x0_new_global[i * OBS_W_NROWS]);
        printf("OBS_x0_new_global[%d]=%.4f\n", (i+1) * OBS_W_NROWS - 1, OBS_x0_new_global[(i+1) * OBS_W_NROWS - 1]);
    }
#endif

    // This is done in parallel to state update from master
#if (OBS_DEBUG_LEVEL > 0)
    printf("OBS_update_delta_y\n");
#endif
#ifdef OBS_SYNC_EVERY_STEP
    ipc_master_wait_ack();
    ipc_master_set_req(1);      // ML 1
#endif
    /* Compute: delta_y = y - Cx*x7 - xd */
    /*update_delta_y(...);*/

#if (OBS_DEBUG_LEVEL > 1)
    for (i = 0; i < NUMSLAVES; i++)
    {
        printf("y_meas[%d]=%.4f,", i * OBS_W_NROWS, y_meas[i * OBS_W_NROWS]);
        printf("y_meas[%d]=%.4f\n", (i+1) * OBS_W_NROWS - 1, y_meas[(i+1) * OBS_W_NROWS - 1]);
    }
#endif
#if (OBS_DEBUG_LEVEL > 0)
    CACHE_invL1d((void *) (&(OBS_delta_y_global[0])), OBS_BYTES_GLOBAL_ARRAYS, CACHE_WAIT);
    _mfence();
    _mfence();
    for (i = 0; i < NUMSLAVES; i++)
    {
        printf("OBS_delta_y_global[%d]=%.4f,", i * OBS_W_NROWS, OBS_delta_y_global[i * OBS_W_NROWS]);
        printf("OBS_delta_y_global[%d]=%.4f\n", (i+1) * OBS_W_NROWS - 1, OBS_delta_y_global[(i+1) * OBS_W_NROWS - 1]);
    }
#endif

#if (OBS_DEBUG_LEVEL > 0)
    printf("OBS_update_delta_x8_or_xd\n");
#endif
    ipc_master_wait_ack();
    ipc_master_set_req(1);      // ML 2
    /* Compute: delta_x8 = Lx*delta_y */
    /* update_delta_x8(...); */
    /* Compute: delta_xd = Ld*delta_y */
    /* update_delta_xd(...); */
#ifdef OBS_SYNC_EVERY_STEP
    ipc_master_wait_ack();

#if (OBS_DEBUG_LEVEL > 0)
    CACHE_invL1d((void *) (&(OBS_delta_x8_global[0])), OBS_BYTES_GLOBAL_ARRAYS, CACHE_WAIT);
    CACHE_invL1d((void *) (&(OBS_delta_xd_global[0])), OBS_BYTES_GLOBAL_ARRAYS, CACHE_WAIT);
    _mfence();
    _mfence();
    for (i = 0; i < NUMSLAVES; i++)
    {
        printf("OBS_delta_x8_global[%d]=%.4f,", i * OBS_W_NROWS, OBS_delta_x8_global[i * OBS_W_NROWS]);
        printf("OBS_delta_x8_global[%d]=%.4f\n", (i+1) * OBS_W_NROWS - 1, OBS_delta_x8_global[(i+1) * OBS_W_NROWS - 1]);
    }
    for (i = 0; i < NUMSLAVES; i++)
    {
        printf("OBS_delta_xd_global[%d]=%.4f,", i * OBS_W_NROWS, OBS_delta_xd_global[i * OBS_W_NROWS]);
        printf("OBS_delta_xd_global[%d]=%.4f\n", (i+1) * OBS_W_NROWS - 1, OBS_delta_xd_global[(i+1) * OBS_W_NROWS - 1]);
    }
#endif

#if (OBS_DEBUG_LEVEL > 0)
    printf("OBS_update_xi\n");
#endif
    ipc_master_set_req(1);      // ML 3
#endif
    /* update_x8(...); */
    /* update_xd(...); */
    /* update_xi(...); */
    ipc_master_wait_ack();

#if (OBS_DEBUG_LEVEL > 0)
    CACHE_invL1d((void *) (&(OBS_x0_new_global[0])), OBS_BYTES_GLOBAL_ARRAYS, CACHE_WAIT);
    CACHE_invL1d((void *) (&(OBS_xd_global[0])), OBS_BYTES_GLOBAL_ARRAYS, CACHE_WAIT);
    for (i = 0; i < NUMSLAVES; i++)
    {
        printf("OBS_x0_new_global[%d]=%.4f,", i * OBS_W_NROWS, OBS_x0_new_global[i * OBS_W_NROWS]);
        printf("OBS_x0_new_global[%d]=%.4f\n", (i+1) * OBS_W_NROWS - 1, OBS_x0_new_global[(i+1) * OBS_W_NROWS - 1]);
    }
    for (i = 0; i < NUMSLAVES; i++)
    {
        printf("OBS_xd_global[%d]=%.4f,", i * OBS_W_NROWS, OBS_xd_global[i * OBS_W_NROWS]);
        printf("OBS_xd_global[%d]=%.4f\n", (i+1) * OBS_W_NROWS - 1, OBS_xd_global[(i+1) * OBS_W_NROWS - 1]);
    }
#endif
    ipc_master_set_req(1);      // ML 4

    /* All workers invalidate global result */
    CACHE_invL1d((void *) (&(OBS_xd_global[0])), OBS_BYTES_GLOBAL_ARRAYS, CACHE_WAIT);
    CACHE_invL1d((void *) (&(OBS_x0_new_global[0])), OBS_BYTES_GLOBAL_ARRAYS, CACHE_WAIT);

    ipc_master_wait_ack();
}


#pragma FUNCTION_OPTIONS(OBS_update_observer_worker, "--opt_level=off --opt_for_speed=0")
void OBS_update_observer_worker(const obs_float * y_meas, const obs_float * u_old)
{
    const int ind_shift = (OBS_selfId - 1) * OBS_W_NROWS;
    ipc_slave_wait_req();      // ML 0

    CACHE_invL1d((void *) &(y_meas[0]), FGM_MPC_BYTES_X0_OR_XD, CACHE_WAIT);
    OBS_swap_local_pointers();
    OBS_swap_global_pointers();


#if (OBS_DEBUG_LEVEL > 1)
    if (OBS_selfId == 1)
        printf("Slave: Waiting for state update from master\n");
#endif


    /* Master updates the whole state */
    /* update_state_global(...); */

#ifdef OBS_SYNC_EVERY_STEP
    ipc_slave_set_ack(1);
    ipc_slave_wait_req();      // ML 1
#endif

#if (OBS_DEBUG_LEVEL > 1)
    if (OBS_selfId == 1)
        printf("Slave: Updating delta y\n");

    if (OBS_selfId == 1) {
        printf("OBS_Cx_local[%d]=%.4f,", 0, OBS_Cx_local[0]);
        printf("OBS_x8_global[%d]=%.4f,", 0, OBS_x8_global[0]);
        printf("y_meas[%d]=%.4f,", 0, y_meas[0]);
        printf("OBS_xd_local[%d]=%.4f,", 0, OBS_xd_local[0]);
        printf("OBS_xd_static[%d]=%.4f,", 0, OBS_xd_static[0]);
        printf("OBS_delta_y_local[%d]=%.4f\n", 0, OBS_delta_y_local[0]);
    }
#endif
    /* Compute: delta_y = y - Cx*x7 - xd */
    CACHE_invL1d((void *) (&(OBS_x8_global[0])), OBS_BYTES_GLOBAL_ARRAYS, CACHE_WAIT);
    OBS_update_delta_y((const obs_float *)(&(OBS_Cx_local[0])),
                       (const obs_float *)OBS_x8_global,
                       (const obs_float *)&(y_meas[ind_shift]),
                       (const obs_float *)OBS_xd_local,
                       (obs_float *)OBS_delta_y_local);
    CACHE_wbL1d((void *) (&(OBS_delta_y_local[0])), OBS_BYTES_LOCAL_ARRAYS, CACHE_WAIT);

#if (OBS_DEBUG_LEVEL > 1)
    if (OBS_selfId == 1) {
        printf("OBS_Cx_local[%d]=%.4f,", 0, OBS_Cx_local[0]);
        printf("OBS_x8_global[%d]=%.4f,", 0, OBS_x8_global[0]);
        printf("y_meas[%d]=%.4f,", 0, y_meas[0]);
        printf("OBS_xd_local[%d]=%.4f,", 0, OBS_xd_local[0]);
        printf("OBS_xd_static[%d]=%.4f,", 0, OBS_xd_static[0]);
        printf("OBS_delta_y_local[%d]=%.4f\n", 0, OBS_delta_y_local[0]);
    }
#endif

    ipc_slave_set_ack(1);
    ipc_slave_wait_req();      // ML 2

    CACHE_invL1d((void *) (&(OBS_x0_new_global[0])), OBS_BYTES_GLOBAL_ARRAYS, CACHE_WAIT);    // TODO: remove this?
    CACHE_invL1d((void *) (&(OBS_delta_y_global[0])), OBS_BYTES_GLOBAL_ARRAYS, CACHE_WAIT);

    /* Compute: delta_x8 = Lx*delta_y */
    OBS_update_delta_x8_or_xd((const obs_float *)(&(OBS_Lx_local[0])),
                              (const obs_float *)OBS_delta_y_global,
                              (obs_float *)OBS_delta_x8_local);

#if (OBS_DEBUG_LEVEL > 1)
    if (OBS_selfId == 1) {
        printf("OBS_Lx_local[%d]=%.4f,", 0, OBS_Lx_local[0]);
        printf("OBS_delta_y_global[%d]=%.4f,", 0, OBS_delta_y_global[0]);
        printf("OBS_delta_x8_local[%d]=%.4f\n", 0, OBS_delta_x8_local[0]);
    }
#endif

    /* Compute: delta_xd = Ld*delta_y */
    OBS_update_delta_x8_or_xd((const obs_float *)(&(OBS_Ld_local[0])),
                              (const obs_float *)OBS_delta_y_global,
                              (obs_float *)OBS_delta_xd_local);

#if (OBS_DEBUG_LEVEL > 1)
    if (OBS_selfId == 1) {
        printf("OBS_Ld_local[%d]=%.4f,", 0, OBS_Ld_local[0]);
        printf("OBS_delta_y_global[%d]=%.4f,", 0, OBS_delta_y_global[0]);
        printf("OBS_delta_xd_local[%d]=%.4f\n", 0, OBS_delta_xd_local[0]);
    }
#endif

#ifdef OBS_SYNC_EVERY_STEP
    CACHE_wbL1d((void *) (&(OBS_delta_x8_local[0])), OBS_BYTES_LOCAL_ARRAYS, CACHE_WAIT);
    CACHE_wbL1d((void *) (&(OBS_delta_xd_local[0])), OBS_BYTES_LOCAL_ARRAYS, CACHE_WAIT);
    _mfence();
    _mfence();

    ipc_slave_set_ack(1);

    ipc_slave_wait_req();      // ML 3
#endif

    OBS_update_x8_or_xd((const obs_float *)OBS_delta_x8_local, (obs_float *)OBS_x8_local);
    OBS_update_x8_or_xd((const obs_float *)OBS_delta_xd_local, (obs_float *)OBS_xd_local);
    OBS_update_xi((const obs_float *)OBS_delta_x8_local, OBS_Ax, (obs_float *)OBS_x7_local);
    OBS_update_xi((const obs_float *)OBS_delta_x8_local, OBS_Ax_pow_2, (obs_float *)OBS_x6_local);
    OBS_update_xi((const obs_float *)OBS_delta_x8_local, OBS_Ax_pow_3, (obs_float *)OBS_x5_local);
    OBS_update_xi((const obs_float *)OBS_delta_x8_local, OBS_Ax_pow_4, (obs_float *)OBS_x4_local);
    OBS_update_xi((const obs_float *)OBS_delta_x8_local, OBS_Ax_pow_5, (obs_float *)OBS_x3_local);
    OBS_update_xi((const obs_float *)OBS_delta_x8_local, OBS_Ax_pow_6, (obs_float *)OBS_x2_local);
    OBS_update_xi((const obs_float *)OBS_delta_x8_local, OBS_Ax_pow_7, (obs_float *)OBS_x1_local);
    OBS_update_xi((const obs_float *)OBS_delta_x8_local, OBS_Ax_pow_8, (obs_float *)OBS_x0_new_local);

    CACHE_wbL1d((void *) (&(OBS_x0_new_local[0])), OBS_BYTES_LOCAL_ARRAYS, CACHE_WAIT);
    CACHE_wbL1d((void *) (&(OBS_xd_local[0])), OBS_BYTES_LOCAL_ARRAYS, CACHE_WAIT);

    ipc_slave_set_ack(1);
    ipc_slave_wait_req();      // ML 4

    CACHE_invL1d((void *) (&(OBS_x0_new_global[0])), OBS_BYTES_GLOBAL_ARRAYS, CACHE_WAIT);
    CACHE_invL1d((void *) (&(OBS_xd_global[0])), OBS_BYTES_GLOBAL_ARRAYS, CACHE_WAIT);

    ipc_slave_set_ack(1);
}
