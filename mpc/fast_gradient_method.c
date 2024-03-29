#include <assert.h>
#include <math.h>
#include <vect.h>
#include <xdc/std.h>

#include "fofb_config.h"
#include "mpc/fast_gradient_method.h"
#include "mpc/fgm_utils.h"
#include "mpc/observer.h"
#include "mpc/DTF_awr.h"

extern void touch(const void *array,  int length);

#if defined(FGM_MPC_DEBUG) || defined(FGM_MPC_PROFILING)
#include <stdio.h>
#endif // defined(FGM_MPC_DEBUG) || defined(FGM_MPC_PROFILING)
#if defined(FGM_MPC_PROFILING)
#include <time.h>
#endif // defined(FGM_MPC_PROFILING)

#ifdef SOC_C6678
#include <c6x.h>
#include <ti/csl/csl_chip.h>
#include <csl_cache.h>
#include <csl_cacheAux.h>
#endif // SOC_C6678

#if (XDIR == 1)
#if (FGM_MPC_HORIZON == 1)
#if (MPC_SLOWFAST == 1)
#include "mpc/slowfast_data/FGM_data_c6678_NWORKERS6_x.h"
#else
#include "mpc/standard_data/FGM_data_c6678_NWORKERS6_x.h"
#endif /* MPC_SLOWFAST */
#else
#if (MPC_SLOWFAST == 1)
#include "mpc/slowfast_data/FGM_data_c6678_NWORKERS6_H2_x.h"
#else
#include "mpc/standard_data/FGM_data_c6678_NWORKERS6_H2_x.h"
#endif /* MPC_SLOWFAST */
#endif /* FGM_MPC_HORIZON */
#else
#if (FGM_MPC_HORIZON == 1)
#if (MPC_SLOWFAST == 1)
#include "mpc/slowfast_data/FGM_data_c6678_NWORKERS6_y.h"
#else
#include "mpc/standard_data/FGM_data_c6678_NWORKERS6_y.h"
#endif /* MPC_SLOWFAST */
#else
#if (MPC_SLOWFAST == 1)
#include "mpc/slowfast_data/FGM_data_c6678_NWORKERS6_H2_y.h"
#else
#include "mpc/standard_data/FGM_data_c6678_NWORKERS6_H2_y.h"
#endif /* MPC_SLOWFAST */
#endif /* FGM_MPC_HORIZON */
#endif /* XDIR */

/* Algorithm:
 *
 * for ()
 *   t(i) = (I - J / L) y(i) - q / L
 *   z(i+1) = P(t(i))
 *   y(i+1) = (1 + beta) z(i+1) - beta z(i)
 * end
 *
 * (I - J / L)  = FGM_MPC_in_mat
 * q / L        = FGM_MPC_in_vec
 * y(i), y(i+1) = out
 * z(i+1)       = FGM_MPC_vec_z_new
 * z(i)         = FGM_MPC_vec_z_old
 * t(i)         = FGM_MPC_vec_t
 *
 * Note that this scheme automatically warm starts.
 *
 */


#define FGM_MPC_min(X, Y)  ((X) < (Y) ? (X) : (Y))
#define FGM_MPC_max(X, Y)  ((X) > (Y) ? (X) : (Y))
#define FGM_MPC_abs_float(X)  (((X) > 0) ? (X) : -(X))

/* Arrays used for initalization*/
#ifdef SOC_C6678
#pragma DATA_ALIGN(FGM_MPC_in_mat_static,       FGM_MPC_ARRAY_ALIGN)
#pragma DATA_ALIGN(FGM_MPC_in_mat_vec_static,   FGM_MPC_ARRAY_ALIGN)
#if (FGM_MPC_DEBUG_LEVEL > 0)
#pragma DATA_ALIGN(FGM_MPC_in_vec_global,       FGM_MPC_ARRAY_ALIGN)
#endif
#pragma SET_DATA_SECTION(".mpc_init")
#endif // SOC_C6678
volatile fgm_float FGM_MPC_in_mat_static[FGM_MPC_DIM * FGM_MPC_DIM];    // J
volatile fgm_float FGM_MPC_in_mat_vec_static[FGM_MPC_DIM * 2 * FGM_MPC_N_X0_OR_XD]; // q = in_mat_vec*[x0_obs; xd_obs]
#ifdef SOC_C6678
#pragma SET_DATA_SECTION()
#endif // SOC_C6678

/* Shared Arrays */
#ifdef SOC_C6678
#pragma DATA_ALIGN(FGM_MPC_in_vec_static,       FGM_MPC_ARRAY_ALIGN)
#pragma DATA_ALIGN(FGM_MPC_out_vec_static,      FGM_MPC_ARRAY_ALIGN)
#pragma DATA_ALIGN(FGM_MPC_x0_obs_static,       FGM_MPC_ARRAY_ALIGN)
#pragma DATA_ALIGN(FGM_MPC_xd_obs_static,       FGM_MPC_ARRAY_ALIGN)
#pragma DATA_ALIGN(FGM_MPC_y_meas_in,           FGM_MPC_ARRAY_ALIGN)
#pragma DATA_ALIGN(FGM_MPC_ampl_max_static,     FGM_MPC_ARRAY_ALIGN)
#pragma DATA_ALIGN(FGM_MPC_rate_max_static,     FGM_MPC_ARRAY_ALIGN)
#if (FGM_MPC_DEBUG_LEVEL > 0)
#pragma DATA_ALIGN(FGM_MPC_in_vec_global,       FGM_MPC_ARRAY_ALIGN)
#endif
#pragma SET_DATA_SECTION(".fgm_shared_data")
#endif // SOC_C6678
volatile fgm_float FGM_MPC_in_vec_static[FGM_MPC_DIM];                  // q
volatile fgm_float FGM_MPC_out_vec_static[FGM_MPC_DIM];
volatile fgm_float FGM_MPC_x0_obs_static[FGM_MPC_N_X0_OR_XD];
volatile fgm_float FGM_MPC_xd_obs_static[FGM_MPC_N_X0_OR_XD];
volatile fgm_float FGM_MPC_y_meas_in[FGM_MPC_N_X0_OR_XD];
volatile fgm_float FGM_MPC_ampl_max_static[FGM_MPC_DIM];
volatile fgm_float FGM_MPC_rate_max_static[FGM_MPC_DIM];
#if (FGM_MPC_DEBUG_LEVEL > 0)
volatile fgm_float FGM_MPC_in_vec_global[FGM_MPC_DIM];
#endif
#ifdef SOC_C6678
#pragma SET_DATA_SECTION()
#endif // SOC_C6678

/* Shared Scalars */
#ifdef SOC_C6678
#pragma DATA_ALIGN(FGM_MPC_max_eigval,   FGM_MPC_ARRAY_ALIGN)
#pragma DATA_ALIGN(FGM_MPC_min_eigval,   FGM_MPC_ARRAY_ALIGN)
#pragma DATA_ALIGN(FGM_MPC_beta,         FGM_MPC_ARRAY_ALIGN)
#pragma SET_DATA_SECTION(".fgm_shared_data")
#endif // SOC_C6678
int FGM_MPC_last_num_iter;
int FGM_MPC_is_initialized;
fgm_float FGM_MPC_max_eigval;
fgm_float FGM_MPC_min_eigval;
volatile fgm_float FGM_MPC_beta;
volatile fgm_float FGM_MPC_beta_p1;
#ifdef SOC_C6678
#pragma SET_DATA_SECTION()
#endif // SOC_C6678

/* Local Arrays */
#ifdef SOC_C6678
#pragma DATA_ALIGN(FGM_MPC_in_mat_local,     FGM_MPC_ARRAY_ALIGN)
#pragma DATA_ALIGN(FGM_MPC_in_vec_local,     FGM_MPC_ARRAY_ALIGN)
#pragma DATA_ALIGN(FGM_MPC_x0_mat_local,     FGM_MPC_ARRAY_ALIGN)
#pragma DATA_ALIGN(FGM_MPC_xd_mat_local,     FGM_MPC_ARRAY_ALIGN)
#pragma DATA_ALIGN(FGM_MPC_vec_t_static,     FGM_MPC_ARRAY_ALIGN)
#pragma DATA_ALIGN(FGM_MPC_vec_z_new_static, FGM_MPC_ARRAY_ALIGN)
#pragma DATA_ALIGN(FGM_MPC_vec_z_old_static, FGM_MPC_ARRAY_ALIGN)
#pragma DATA_ALIGN(FGM_MPC_sofb_local,       FGM_MPC_ARRAY_ALIGN)
#if (FGM_MPC_HORIZON == 1)
#pragma DATA_ALIGN(FGM_MPC_box_min_local, FGM_MPC_ARRAY_ALIGN)
#pragma DATA_ALIGN(FGM_MPC_box_max_local, FGM_MPC_ARRAY_ALIGN)
#else
#pragma DATA_ALIGN(FGM_MPC_A0_min_local,    FGM_MPC_ARRAY_ALIGN)
#pragma DATA_ALIGN(FGM_MPC_A0_max_local,    FGM_MPC_ARRAY_ALIGN)
#pragma DATA_ALIGN(FGM_MPC_A1_min_local,    FGM_MPC_ARRAY_ALIGN)
#pragma DATA_ALIGN(FGM_MPC_A1_max_local,    FGM_MPC_ARRAY_ALIGN)
#pragma DATA_ALIGN(FGM_MPC_C1_local,        FGM_MPC_ARRAY_ALIGN)
#pragma DATA_ALIGN(FGM_MPC_C2_local,        FGM_MPC_ARRAY_ALIGN)
#pragma DATA_ALIGN(FGM_MPC_C3_local,        FGM_MPC_ARRAY_ALIGN)
#pragma DATA_ALIGN(FGM_MPC_C4_local,        FGM_MPC_ARRAY_ALIGN)
#pragma DATA_ALIGN(FGM_MPC_diag_lim1_local, FGM_MPC_ARRAY_ALIGN)
#pragma DATA_ALIGN(FGM_MPC_diag_lim2_local, FGM_MPC_ARRAY_ALIGN)
#endif
#pragma SET_DATA_SECTION(".fgm_local_data")
#endif // SOC_C6678
fgm_float FGM_MPC_in_mat_local[FGM_MPC_W_NROWS * FGM_MPC_W_NCOLS];  // matrix J
fgm_float FGM_MPC_in_vec_local[FGM_MPC_W_NROWS];                    // vector q
// matrix to compute q from x0_obs and xd_obs
fgm_float FGM_MPC_x0_mat_local[FGM_MPC_W_NROWS * FGM_MPC_N_X0_OR_XD];
fgm_float FGM_MPC_xd_mat_local[FGM_MPC_W_NROWS * FGM_MPC_N_X0_OR_XD];
fgm_float FGM_MPC_sofb_local[FGM_MPC_W_NROWS]; // Slow orbit feedback setpoints
#if (FGM_MPC_DEBUG_LEVEL == 0) // if master prints every step then save this in shared memory
volatile fgm_float FGM_MPC_vec_t_static[FGM_MPC_DIM];
volatile fgm_float FGM_MPC_vec_z_new_static[FGM_MPC_DIM];
volatile fgm_float FGM_MPC_vec_z_old_static[FGM_MPC_DIM];
#endif // (FGM_MPC_DEBUG_LEVEL == 0)
#if (FGM_MPC_HORIZON == 1)
volatile fgm_float FGM_MPC_box_min_local[FGM_MPC_W_NROWS];
volatile fgm_float FGM_MPC_box_max_local[FGM_MPC_W_NROWS];
#else
// See FGM-DYKSTRA paper for the definition of these points
fgm_float FGM_MPC_A0_min_local[FGM_MPC_W_NROWS_HALF];
fgm_float FGM_MPC_A0_max_local[FGM_MPC_W_NROWS_HALF];
fgm_float FGM_MPC_A1_min_local[FGM_MPC_W_NROWS_HALF];
fgm_float FGM_MPC_A1_max_local[FGM_MPC_W_NROWS_HALF];
fgm_float FGM_MPC_C1_local[FGM_MPC_W_NROWS];
fgm_float FGM_MPC_C2_local[FGM_MPC_W_NROWS];
fgm_float FGM_MPC_C3_local[FGM_MPC_W_NROWS];
fgm_float FGM_MPC_C4_local[FGM_MPC_W_NROWS];
fgm_float FGM_MPC_diag_lim1_local[FGM_MPC_W_NROWS];
fgm_float FGM_MPC_diag_lim2_local[FGM_MPC_W_NROWS];
#endif // (FGM_MPC_HORIZON == 1)
#ifdef SOC_C6678
#pragma SET_DATA_SECTION()
#endif // SOC_C6678

#ifdef SOC_C6678
#pragma SET_DATA_SECTION(".fgm_shared_data")
#endif // SOC_C6678
#if (FGM_MPC_DEBUG_LEVEL > 0) // if master prints every step then save this in shared memory
volatile fgm_float FGM_MPC_vec_t_static[FGM_MPC_DIM];
volatile fgm_float FGM_MPC_vec_z_new_static[FGM_MPC_DIM];
volatile fgm_float FGM_MPC_vec_z_old_static[FGM_MPC_DIM];
#ifdef SOC_C6678
#pragma SET_DATA_SECTION()
#endif // SOC_C6678
#endif // (FGM_MPC_DEBUG_LEVEL > 0)

/* Local Pointers */
#ifdef SOC_C6678
#pragma SET_DATA_SECTION(".fgm_local_data")
#endif // SOC_C6678
fgm_float * FGM_MPC_in_mat; // = FGM_MPC_in_mat_static; points to the NROWS part per worker
fgm_float * FGM_MPC_in_vec; // = FGM_MPC_in_vec_static; points to the NROWS part per worker
volatile fgm_float * volatile FGM_MPC_vec_t; // = FGM_MPC_vec_t_static;
volatile fgm_float * volatile FGM_MPC_vec_z_new; // = FGM_MPC_vec_z_new_static;
volatile fgm_float * volatile FGM_MPC_vec_z_old; // = FGM_MPC_vec_z_old_static;
volatile fgm_float * volatile out_local; // points to the NROWS part per worker
volatile fgm_float * volatile out_global; // points to the beginning
volatile fgm_float * volatile FGM_MPC_ampl_max_local;
volatile fgm_float * volatile FGM_MPC_rate_max_local;
volatile fgm_float * volatile FGM_MPC_x0_obs_local; // points to the beginning of the newest state estimate
volatile fgm_float * volatile FGM_MPC_xd_obs_local; // points to the beginning of the disturbance state estimate
#ifdef SOC_C6678
#pragma SET_DATA_SECTION()
#endif // SOC_C6678

/* Local Scalars */
#ifdef SOC_C6678
#pragma DATA_ALIGN(fgm_box_min_local, FGM_MPC_ARRAY_ALIGN)
#pragma DATA_ALIGN(FGM_MPC_selfId, FGM_MPC_ARRAY_ALIGN)
#pragma SET_DATA_SECTION(".fgm_local_data")
#endif // SOC_C6678
fgm_float fgm_box_min_local = 0.0;
fgm_float fgm_box_max_local = 0.0;
fgm_float fgm_beta_local = 0.0;
fgm_float fgm_beta_p1_local = 0.0;
Uint32 volatile FGM_MPC_selfId;
#ifdef SOC_C6678
#pragma SET_DATA_SECTION()
#endif // SOC_C6678


/*
float debug_vec_t[FGM_MPC_DIM];
void gradient_step_master(void)
{
    int i, j;
    for (i = 0; i < FGM_MPC_DIM; i++)
    {
        fgm_float row_res = 0.0;
        for (j = 0; j < FGM_MPC_DIM; j++)
        {
            row_res += FGM_MPC_in_mat_static[i*FGM_MPC_DIM+j]*FGM_MPC_out_vec_static[j];
        }
        debug_vec_t[i] = row_res - FGM_MPC_in_vec_static[i];
    }
}
*/


/* Prototypes */
void FGM_MPC_gradient_step(const fgm_float *restrict in_mat,
                           const fgm_float *restrict in_vec,
                           const fgm_float *restrict in_vec_sub,
                           fgm_float *restrict out_vec);
void FGM_MPC_initialize_obj_func_vec(const fgm_float * restrict in_x0_mat,
                                     const fgm_float * restrict in_x0_vec,
                                     const fgm_float * restrict in_xd_mat,
                                     const fgm_float * restrict in_xd_vec,
                                     fgm_float * restrict out_q_vec);
void FGM_MPC_beta_step(const fgm_float * restrict in1,
                       const fgm_float * restrict in2, fgm_float * restrict out);
void FGM_MPC_initialize_projection(void);

#if (FGM_MPC_HORIZON == 1)
void FGM_MPC_project(const fgm_float * restrict in,
                     const fgm_float * restrict min_local,
                     const fgm_float * restrict max_local,
                     fgm_float * restrict out);
#else
void FGM_MPC_project(const fgm_float * restrict in,
                     fgm_float * restrict out);
#endif

/* Prototypes algebra */
void FGM_MPC_vec_copy(const fgm_float * restrict in, fgm_float * restrict out, const int len);
void FGM_MPC_vec_swap(fgm_float **in_out1, fgm_float **in_out2);
void FGM_MPC_vec_swap_volatile(volatile fgm_float * volatile * in_out1,
                               volatile fgm_float * volatile * in_out2);
void FGM_MPC_vec_init(fgm_float * restrict out, const fgm_float in);

/* Permutations for efficient matrix-vector multiplication */
int arr_ind(const int ncols, const int i_row, const int i_col);

void permXN_2waySIMD(const volatile fgm_float * volatile in_mat,
                     volatile fgm_float * volatile out_mat, const int unroll,
                     const int nrows, const int ncols);

void permXN_4waySIMD(const volatile fgm_float * volatile in_mat,
                     volatile fgm_float * volatile out_mat, const int unroll,
                     const int nrows, const int ncols);

void FGM_MPC_gradient_step(const fgm_float *restrict in_mat,
                            const fgm_float *restrict in_vec,
                            const fgm_float *restrict in_vec_sub,
                            fgm_float *restrict out_vec)
{

    int i, j, ind_shift;

    _nassert((int) in_mat % FGM_MPC_ARRAY_ALIGN == 0);
    _nassert((int) in_vec % FGM_MPC_ARRAY_ALIGN == 0);
    _nassert((int) out_vec % FGM_MPC_ARRAY_ALIGN == 0);
    _nassert((int) in_vec_sub % FGM_MPC_ARRAY_ALIGN == 0);
    _nassert(FGM_MPC_W_NROWS >= 32);
    _nassert(FGM_MPC_W_NCOLS >= 32);
    _nassert(FGM_MPC_W_NROWS % 32 == 0);
    _nassert(FGM_MPC_W_NCOLS % 32 == 0);

#ifdef FGM_MPC_UNROLL // no unrolling uses standard row-major mat-mpy defined below
#ifdef FGM_MPC_QMPY // uses quad-mpy function

#pragma MUST_ITERATE(FGM_MPC_W_NROWS/8, FGM_MPC_W_NROWS/8)
#pragma UNROLL(1)
    for (i = 0, ind_shift = 0; i < FGM_MPC_W_NROWS; i += 8)
    {
        __float2_t row_res_0 = 0.0;
        __float2_t row_res_1 = 0.0;
        __float2_t row_res_2 = 0.0;
        __float2_t row_res_3 = 0.0;
        __float2_t row_res_4 = 0.0;
        __float2_t row_res_5 = 0.0;
        __float2_t row_res_6 = 0.0;
        __float2_t row_res_7 = 0.0;

#pragma MUST_ITERATE(FGM_MPC_W_NCOLS/4, FGM_MPC_W_NCOLS/4)
#pragma UNROLL(1)
        for (j = 0; j < FGM_MPC_W_NCOLS; j += 4, ind_shift += 32)
        {

            __x128_t f4_in_vec = _f2to128(_amem8_f2_const(&in_vec[j]),
                                          _amem8_f2_const(&in_vec[j + 2]));

            __x128_t f4_in_mat_row0 = _f2to128(
                    _amem8_f2_const(&in_mat[ind_shift]),
                    _amem8_f2_const(&in_mat[ind_shift + 2]));
            __x128_t f4_in_mat_row1 = _f2to128(
                    _amem8_f2_const(&in_mat[ind_shift + 4]),
                    _amem8_f2_const(&in_mat[ind_shift + 6]));
            __x128_t f4_in_mat_row2 = _f2to128(
                    _amem8_f2_const(&in_mat[ind_shift + 8]),
                    _amem8_f2_const(&in_mat[ind_shift + 10]));
            __x128_t f4_in_mat_row3 = _f2to128(
                    _amem8_f2_const(&in_mat[ind_shift + 12]),
                    _amem8_f2_const(&in_mat[ind_shift + 14]));
            __x128_t f4_in_mat_row4 = _f2to128(
                    _amem8_f2_const(&in_mat[ind_shift + 16]),
                    _amem8_f2_const(&in_mat[ind_shift + 18]));
            __x128_t f4_in_mat_row5 = _f2to128(
                    _amem8_f2_const(&in_mat[ind_shift + 20]),
                    _amem8_f2_const(&in_mat[ind_shift + 22]));
            __x128_t f4_in_mat_row6 = _f2to128(
                    _amem8_f2_const(&in_mat[ind_shift + 24]),
                    _amem8_f2_const(&in_mat[ind_shift + 26]));
            __x128_t f4_in_mat_row7 = _f2to128(
                    _amem8_f2_const(&in_mat[ind_shift + 28]),
                    _amem8_f2_const(&in_mat[ind_shift + 30]));


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
        _amem8_f2(&out_vec[i]) = _dsubsp(
                _ftof2(_lof2(row_res_1) + _hif2(row_res_1),
                       _lof2(row_res_0) + _hif2(row_res_0)),
                       _amem8_f2_const(&in_vec_sub[i]));
        _amem8_f2(&out_vec[i + 2]) = _dsubsp(
                _ftof2(_lof2(row_res_3) + _hif2(row_res_3),
                       _lof2(row_res_2) + _hif2(row_res_2)),
                       _amem8_f2_const(&in_vec_sub[i + 2]));
        _amem8_f2(&out_vec[i + 4]) = _dsubsp(
                _ftof2(_lof2(row_res_5) + _hif2(row_res_5),
                       _lof2(row_res_4) + _hif2(row_res_4)),
                       _amem8_f2_const(&in_vec_sub[i + 4]));
        _amem8_f2(&out_vec[i + 6]) = _dsubsp(
                _ftof2(_lof2(row_res_7) + _hif2(row_res_7),
                       _lof2(row_res_6) + _hif2(row_res_6)),
                       _amem8_f2_const(&in_vec_sub[i + 6]));
    }
#else // not FGM_MPC_QMPY: uses dual mpy function

#pragma MUST_ITERATE(FGM_MPC_W_NROWS/8, FGM_MPC_W_NROWS/8)
#pragma UNROLL(1)
    for (i = 0, ind_shift = 0; i < FGM_MPC_W_NROWS; i += 8)
    {
        __float2_t  f2_res_row1 = 0.0;
        __float2_t  f2_res_row2 = 0.0;
        __float2_t  f2_res_row3 = 0.0;
        __float2_t  f2_res_row4 = 0.0;
        __float2_t  f2_res_row5 = 0.0;
        __float2_t  f2_res_row6 = 0.0;
        __float2_t  f2_res_row7 = 0.0;
        __float2_t  f2_res_row8 = 0.0;

#pragma MUST_ITERATE(FGM_MPC_W_NCOLS/2, FGM_MPC_W_NCOLS/2)
#pragma UNROLL(1)
        for (j = 0; j < FGM_MPC_W_NCOLS; j += 2, ind_shift += 16)
        {

            __float2_t f2_in_mat_row1 = _amem8_f2_const(&in_mat[ind_shift]);
            __float2_t f2_in_mat_row2 = _amem8_f2_const(&in_mat[ind_shift+2]);
            __float2_t f2_in_mat_row3 = _amem8_f2_const(&in_mat[ind_shift+4]);
            __float2_t f2_in_mat_row4 = _amem8_f2_const(&in_mat[ind_shift+6]);
            __float2_t f2_in_mat_row5 = _amem8_f2_const(&in_mat[ind_shift+8]);
            __float2_t f2_in_mat_row6 = _amem8_f2_const(&in_mat[ind_shift+10]);
            __float2_t f2_in_mat_row7 = _amem8_f2_const(&in_mat[ind_shift+12]);
            __float2_t f2_in_mat_row8 = _amem8_f2_const(&in_mat[ind_shift+14]);

            __float2_t f2_in_vec = _amem8_f2_const(&in_vec[j]);

            f2_res_row1 = _daddsp(f2_res_row1, _dmpysp(f2_in_mat_row1, f2_in_vec));
            f2_res_row2 = _daddsp(f2_res_row2, _dmpysp(f2_in_mat_row2, f2_in_vec));
            f2_res_row3 = _daddsp(f2_res_row3, _dmpysp(f2_in_mat_row3, f2_in_vec));
            f2_res_row4 = _daddsp(f2_res_row4, _dmpysp(f2_in_mat_row4, f2_in_vec));
            f2_res_row5 = _daddsp(f2_res_row5, _dmpysp(f2_in_mat_row5, f2_in_vec));
            f2_res_row6 = _daddsp(f2_res_row6, _dmpysp(f2_in_mat_row6, f2_in_vec));
            f2_res_row7 = _daddsp(f2_res_row7, _dmpysp(f2_in_mat_row7, f2_in_vec));
            f2_res_row8 = _daddsp(f2_res_row8, _dmpysp(f2_in_mat_row8, f2_in_vec));
        }
        _amem8_f2(&out_vec[i])     = _dsubsp(_ftof2(_lof2(f2_res_row2) + _hif2(f2_res_row2),
                                                    _lof2(f2_res_row1) + _hif2(f2_res_row1)),
                                             _amem8_f2_const(&in_vec_sub[i]));
        _amem8_f2(&out_vec[i + 2]) = _dsubsp(_ftof2(_lof2(f2_res_row4) + _hif2(f2_res_row4),
                                                    _lof2(f2_res_row3) + _hif2(f2_res_row3)),
                                             _amem8_f2_const(&in_vec_sub[i+2]));
        _amem8_f2(&out_vec[i + 4]) = _dsubsp(_ftof2(_lof2(f2_res_row6) + _hif2(f2_res_row6),
                                                    _lof2(f2_res_row5) + _hif2(f2_res_row5)),
                                             _amem8_f2_const(&in_vec_sub[i+4]));
        _amem8_f2(&out_vec[i + 6]) = _dsubsp(_ftof2(_lof2(f2_res_row8) + _hif2(f2_res_row8),
                                                    _lof2(f2_res_row7) + _hif2(f2_res_row7)),
                                             _amem8_f2_const(&in_vec_sub[i+6]));
    }
#endif // FGM_MPC_QMPY
#else
    for (i = 0; i < FGM_MPC_W_NROWS; i++)
    {
        fgm_float row_res = 0.0;
        for (j = 0; j < FGM_MPC_W_NCOLS; j++)
        {
            row_res += in_mat[i*FGM_MPC_W_NCOLS+j]*in_vec[j];
        }
        out_vec[i] = row_res - in_vec_sub[i];
    }
#endif // FGM_MPC_UNROLL
}


void FGM_MPC_beta_step(const fgm_float * restrict in1,
                   const fgm_float * restrict in2, fgm_float * restrict out)
{
    const float beta_p1_local = fgm_beta_p1_local;
    const float beta_local_neg = -fgm_beta_local;
    int i_row;
#ifdef SOC_C6678
    _nassert(FGM_MPC_W_NROWS >= 32);
    _nassert(FGM_MPC_W_NROWS % 32 == 0);
    _nassert((int) in1 % 16 == 0);
    _nassert((int) in2 % 16 == 0);
    _nassert((int) out % 16 == 0);
#endif // SOC_C6678
#if 0
#pragma MUST_ITERATE(FGM_MPC_W_NROWS, FGM_MPC_W_NROWS)
    for (i_row = 0; i_row < FGM_MPC_W_NROWS; i_row++)
    {
        out[i_row] = beta_p1_local * in1[i_row] + beta_local_neg * in2[i_row];
    }
#else
    //__float2_t b_p1 = _ftof2(beta_p1_local, beta_p1_local);
    //__float2_t b_neg = _ftof2(beta_local_neg, beta_local_neg);
#pragma MUST_ITERATE(FGM_MPC_W_NROWS/8, FGM_MPC_W_NROWS/8)
#pragma UNROLL(1)
    for (i_row = 0; i_row < FGM_MPC_W_NROWS; i_row+=8)
    {
        /*
        _amem8_f2(&out[i_row]) = _daddsp(_dmpysp(_amem8_f2_const(&in1[i_row]), b_p1),
                                         _dmpysp(_amem8_f2_const(&in2[i_row]), b_neg));
        _amem8_f2(&out[i_row+2]) = _daddsp(_dmpysp(_amem8_f2_const(&in1[i_row+2]), b_p1),
                                           _dmpysp(_amem8_f2_const(&in2[i_row+2]), b_neg));
        _amem8_f2(&out[i_row+4]) = _daddsp(_dmpysp(_amem8_f2_const(&in1[i_row+4]), b_p1),
                                           _dmpysp(_amem8_f2_const(&in2[i_row+4]), b_neg));
        _amem8_f2(&out[i_row+6]) = _daddsp(_dmpysp(_amem8_f2_const(&in1[i_row+6]), b_p1),
                                           _dmpysp(_amem8_f2_const(&in2[i_row+6]), b_neg));
        */
        out[i_row] = beta_p1_local * in1[i_row] + beta_local_neg * in2[i_row];
        out[i_row+1] = beta_p1_local * in1[i_row+1] + beta_local_neg * in2[i_row+1];
        out[i_row+2] = beta_p1_local * in1[i_row+2] + beta_local_neg * in2[i_row+2];
        out[i_row+3] = beta_p1_local * in1[i_row+3] + beta_local_neg * in2[i_row+3];
        out[i_row+4] = beta_p1_local * in1[i_row+4] + beta_local_neg * in2[i_row+4];
        out[i_row+5] = beta_p1_local * in1[i_row+5] + beta_local_neg * in2[i_row+5];
        out[i_row+6] = beta_p1_local * in1[i_row+6] + beta_local_neg * in2[i_row+6];
        out[i_row+7] = beta_p1_local * in1[i_row+7] + beta_local_neg * in2[i_row+7];
    }
#endif
}

void FGM_MPC_initialize_obj_func_vec(const fgm_float * restrict in_x0_mat,
                                     const fgm_float * restrict in_x0_vec,
                                     const fgm_float * restrict in_xd_mat,
                                     const fgm_float * restrict in_xd_vec,
                                     fgm_float * restrict out_q_vec)
{
    int i_row, i_col, i_shift;

    _nassert((int) in_x0_mat % OBS_ARRAY_ALIGN == 0);
    _nassert((int) in_x0_vec % OBS_ARRAY_ALIGN == 0);
    _nassert((int) in_xd_mat % OBS_ARRAY_ALIGN == 0);
    _nassert((int) in_xd_vec % OBS_ARRAY_ALIGN == 0);
    _nassert((int) out_q_vec % OBS_ARRAY_ALIGN == 0);

    for (i_row = 0, i_shift = 0; i_row < FGM_MPC_W_NROWS; i_row++, i_shift += FGM_MPC_N_X0_OR_XD)
    {
        fgm_float row_res = 0.0;
        for (i_col = 0; i_col < FGM_MPC_N_X0_OR_XD; i_col++)
        {
            row_res += in_x0_mat[i_shift + i_col] * in_x0_vec[i_col]+
                       in_xd_mat[i_shift + i_col] * in_xd_vec[i_col];
        }
        out_q_vec[i_row] = row_res;
    }
}
/*
 * Horizon-dependent functions
 * 1. 2 hard-coded projections for horizon 1 and 2. Switch implementation based on header constants.
 */
#if (FGM_MPC_HORIZON == 1)

void FGM_MPC_initialize_projection(void)
{
    int i_row;
    fgm_float *awr;

    // Compute AWR signal (lowpass-filtered input)
    FGM_MPC_vec_copy((const fgm_float *)out_local, DTF_awr_get_u0_ptr(), FGM_MPC_W_NROWS);
    DTF_awr_execute();
    awr = DTF_awr_get_y0_ptr();

#pragma MUST_ITERATE(FGM_MPC_W_NROWS/4, FGM_MPC_W_NROWS/4)
    for (i_row = 0; i_row < FGM_MPC_W_NROWS; i_row+=4)
    {
        FGM_MPC_box_min_local[i_row] = FGM_MPC_max(-FGM_MPC_sofb_local[i_row]-FGM_MPC_ampl_max_local[i_row],
                                                   awr[i_row] - FGM_MPC_rate_max_local[i_row]);
        FGM_MPC_box_max_local[i_row] = FGM_MPC_min(-FGM_MPC_sofb_local[i_row]+FGM_MPC_ampl_max_local[i_row],
                                                   awr[i_row] + FGM_MPC_rate_max_local[i_row]);

        FGM_MPC_box_min_local[i_row+1] = FGM_MPC_max(-FGM_MPC_sofb_local[i_row+1]-FGM_MPC_ampl_max_local[i_row+1],
                                                     awr[i_row+1] - FGM_MPC_rate_max_local[i_row+1]);
        FGM_MPC_box_max_local[i_row+1] = FGM_MPC_min(-FGM_MPC_sofb_local[i_row+1]+FGM_MPC_ampl_max_local[i_row+1],
                                                     awr[i_row+1] + FGM_MPC_rate_max_local[i_row+1]);

        FGM_MPC_box_min_local[i_row+2] = FGM_MPC_max(-FGM_MPC_sofb_local[i_row+2]-FGM_MPC_ampl_max_local[i_row+2],
                                                     awr[i_row+2] - FGM_MPC_rate_max_local[i_row+2]);
        FGM_MPC_box_max_local[i_row+2] = FGM_MPC_min(-FGM_MPC_sofb_local[i_row+2]+FGM_MPC_ampl_max_local[i_row+2],
                                                     awr[i_row+2] + FGM_MPC_rate_max_local[i_row+2]);

        FGM_MPC_box_min_local[i_row+3] = FGM_MPC_max(-FGM_MPC_sofb_local[i_row+3]-FGM_MPC_ampl_max_local[i_row+3],
                                                     awr[i_row+3] - FGM_MPC_rate_max_local[i_row+3]);
        FGM_MPC_box_max_local[i_row+3] = FGM_MPC_min(-FGM_MPC_sofb_local[i_row+3]+FGM_MPC_ampl_max_local[i_row+3],
                                                     awr[i_row+3] + FGM_MPC_rate_max_local[i_row+3]);
    }
}

void FGM_MPC_project(const fgm_float * restrict in,
                     const fgm_float * restrict min_local,
                     const fgm_float * restrict max_local,
                     fgm_float * restrict out)
{
    int i_row;
#ifdef SOC_C6678
    _nassert((int) in % 16 == 0);
    _nassert((int) out % 16 == 0);
    _nassert(FGM_MPC_W_NROWS >= 32);
    _nassert(FGM_MPC_W_NROWS % 32 == 0);
#endif // SOC_C6678
#if 0
#pragma MUST_ITERATE(FGM_MPC_W_NROWS, FGM_MPC_W_NROWS)
    for (i_row = 0; i_row < FGM_MPC_W_NROWS; i_row++)
    {
        out[i_row] = FGM_MPC_max(FGM_MPC_box_min_local[i_row],
                                 FGM_MPC_min(in[i_row], FGM_MPC_box_max_local[i_row]));
    }
#else
#pragma MUST_ITERATE(FGM_MPC_W_NROWS/8, FGM_MPC_W_NROWS/8)
#pragma UNROLL(1)
    for (i_row = 0; i_row < FGM_MPC_W_NROWS; i_row+=8)
    {
        out[i_row] = FGM_MPC_max(min_local[i_row],
                                 FGM_MPC_min(in[i_row], max_local[i_row]));

        out[i_row+1] = FGM_MPC_max(min_local[i_row+1],
                                 FGM_MPC_min(in[i_row+1], max_local[i_row+1]));

        out[i_row+2] = FGM_MPC_max(min_local[i_row+2],
                                 FGM_MPC_min(in[i_row+2], max_local[i_row+2]));

        out[i_row+3] = FGM_MPC_max(min_local[i_row+3],
                                 FGM_MPC_min(in[i_row+3], max_local[i_row+3]));

        out[i_row+4] = FGM_MPC_max(min_local[i_row+4],
                                 FGM_MPC_min(in[i_row+4], max_local[i_row+4]));

        out[i_row+5] = FGM_MPC_max(min_local[i_row+5],
                                 FGM_MPC_min(in[i_row+5], max_local[i_row+5]));

        out[i_row+6] = FGM_MPC_max(min_local[i_row+6],
                                 FGM_MPC_min(in[i_row+6], max_local[i_row+6]));

        out[i_row+7] = FGM_MPC_max(min_local[i_row+7],
                                 FGM_MPC_min(in[i_row+7], max_local[i_row+7]));
    }
#endif
}

#else // (FGM_MPC_HORIZON == 1)

void FGM_MPC_initialize_projection(void)
{
    int i, j;
    for (i=0, j=0; i < FGM_MPC_W_NROWS_HALF; i++, j+=2) {
        const fgm_float ampl_minus_rate = FGM_MPC_ampl_max_local[i] - FGM_MPC_rate_max_local[i];
        // Compute new u0 limits
        // a0_min = max(-a, -r + u_old);
        FGM_MPC_A0_min_local[i] = FGM_MPC_max(-FGM_MPC_ampl_max_local[i], out_local[j] - FGM_MPC_rate_max_local[i]);
        // a0_max = min(a, r + u_old)
        FGM_MPC_A0_max_local[i] = FGM_MPC_min(FGM_MPC_ampl_max_local[i], out_local[j] + FGM_MPC_rate_max_local[i]);
        // a1_min = max(-a, -r + a0_min)
        FGM_MPC_A1_min_local[i] = FGM_MPC_max(-FGM_MPC_ampl_max_local[i], FGM_MPC_A0_min_local[i] - FGM_MPC_rate_max_local[i]);
        // a1_max = min(a, r + obj.a0_max)
        FGM_MPC_A1_max_local[i] = FGM_MPC_min(FGM_MPC_ampl_max_local[i], FGM_MPC_A0_max_local[i] + FGM_MPC_rate_max_local[i]);
        // Compute corner points
        // C1 = [a0_min; min(r + a0_min, a)]
        FGM_MPC_C1_local[j] = FGM_MPC_A0_min_local[i];
        FGM_MPC_C1_local[j + 1] = FGM_MPC_min(FGM_MPC_rate_max_local[i] + FGM_MPC_A0_min_local[i], FGM_MPC_ampl_max_local[i]);
        // C2 = [min(a0_max, a - r); min(a, r + a0_max)]
        FGM_MPC_C2_local[j] = FGM_MPC_min(FGM_MPC_A0_max_local[i], ampl_minus_rate);
        FGM_MPC_C2_local[j + 1] = FGM_MPC_min(FGM_MPC_ampl_max_local[i], FGM_MPC_rate_max_local[i] + FGM_MPC_A0_max_local[i]);
        // C3 = [a0_max; -r + a0_max]
        FGM_MPC_C3_local[j] = FGM_MPC_A0_max_local[i];
        FGM_MPC_C3_local[j + 1] = FGM_MPC_A0_max_local[i] - FGM_MPC_rate_max_local[i];
        // C4 = [max(r - a, a0_min); max(-a, -r + a0_min)]
        FGM_MPC_C4_local[j] = FGM_MPC_max(-ampl_minus_rate, FGM_MPC_A0_min_local[i]);
        FGM_MPC_C4_local[j + 1] = FGM_MPC_max(-FGM_MPC_ampl_max_local[i], FGM_MPC_A0_min_local[i]-FGM_MPC_rate_max_local[i]);

        // Compute limits of diagonal for regions A1 and A2
        FGM_MPC_diag_lim1_local[j] = FGM_MPC_C1_local[j] + FGM_MPC_C1_local[j + 1];
        FGM_MPC_diag_lim1_local[j + 1] = FGM_MPC_C2_local[j] + FGM_MPC_C2_local[j + 1];
        FGM_MPC_diag_lim2_local[j] = FGM_MPC_C4_local[j] + FGM_MPC_C4_local[j + 1];
        FGM_MPC_diag_lim2_local[j + 1] = FGM_MPC_C3_local[j] + FGM_MPC_C3_local[j + 1];
    }
}

void FGM_MPC_project(const fgm_float * restrict in, fgm_float * restrict out)
{
    int i, ix2;

    for (i=0, ix2=0; ix2<FGM_MPC_W_NROWS; i++, ix2+=2)
    {
        // [1; 1]' * x0
        const fgm_float rdiag = in[ix2] + in[ix2+1];
        // [-1; 1] * x0
        const fgm_float ldiag = in[ix2+1] - in[ix2];

        if ((rdiag >= FGM_MPC_diag_lim1_local[ix2]) &&
                (rdiag <= FGM_MPC_diag_lim1_local[ix2+1]) &&
                (ldiag >= FGM_MPC_rate_max_local[i]))
        { // A1
            const fgm_float tmp = FGM_MPC_min(FGM_MPC_rate_max_local[i], ldiag);
            out[ix2] = 0.5 * (rdiag - tmp);
            out[ix2+1] = 0.5 * (tmp + rdiag);
        } else if ((rdiag >= FGM_MPC_diag_lim2_local[ix2]) &&
                   (rdiag <= FGM_MPC_diag_lim2_local[ix2+1]) &&
                   (ldiag <= -FGM_MPC_rate_max_local[i]))
        { // A2
            const fgm_float tmp = FGM_MPC_max(-FGM_MPC_rate_max_local[i], ldiag);
            out[ix2] = 0.5 * (-tmp + rdiag);
            out[ix2+1] = 0.5 * (tmp + rdiag);
        } else if ((rdiag <= FGM_MPC_diag_lim1_local[ix2]) &&
                   (in[ix2] <= FGM_MPC_C1_local[ix2]) &&
                   (in[ix2+1] >= FGM_MPC_C1_local[ix2+1]))
        { // C1
            out[ix2] = FGM_MPC_C1_local[ix2];
            out[ix2+1] = FGM_MPC_C1_local[ix2+1];
        } else if ((rdiag <= FGM_MPC_diag_lim2_local[ix2]) &&
                   (in[ix2] >= FGM_MPC_C4_local[ix2]) &&
                   (in[ix2+1] <= FGM_MPC_C4_local[ix2+1]))
        { // C4
            out[ix2] = FGM_MPC_C4_local[ix2];
            out[ix2+1] = FGM_MPC_C4_local[ix2+1];
        } else if ((rdiag >= FGM_MPC_diag_lim1_local[ix2+1]) &&
                   (in[ix2] <= FGM_MPC_C2_local[ix2]) &&
                   (in[ix2+1] >= FGM_MPC_C2_local[ix2+1]))
        { // C2
            out[ix2] = FGM_MPC_C2_local[ix2];
            out[ix2+1] = FGM_MPC_C2_local[ix2+1];
        } else if ((rdiag >= FGM_MPC_diag_lim2_local[ix2+1]) &&
                   (in[ix2] >= FGM_MPC_C3_local[ix2]) &&
                   (in[ix2+1] <= FGM_MPC_C3_local[ix2+1]))
        { // C3
            out[ix2] = FGM_MPC_C3_local[ix2];
            out[ix2+1] = FGM_MPC_C3_local[ix2+1];
        } else
        {
            out[ix2] = FGM_MPC_max(FGM_MPC_A0_min_local[i], FGM_MPC_min(in[ix2], FGM_MPC_A0_max_local[i]));
            out[ix2+1] = FGM_MPC_max(FGM_MPC_A1_min_local[i], FGM_MPC_min(in[ix2+1], FGM_MPC_A1_max_local[i]));
        }
    }
}
#endif // (FGM_MPC_HORIZON == 1)

#pragma FUNCTION_OPTIONS(FGM_MPC_initialize, "--opt_level=off --opt_for_speed=0")
void FGM_MPC_initialize(void)
{
    int i;
    assert(FGM_MPC_BYTES_GLOBAL_ARRAYS <= 4*65408); // TODO: is this number correct?

    /* Store projection limits, projection initialized by slaves */
    for (i = 0; i < FGM_MPC_DIM; i++)
    {
        FGM_MPC_ampl_max_static[i] = ampl_max_vec[i];
        FGM_MPC_rate_max_static[i] = rate_max_vec[i];
    }
    CACHE_wbL1d((void *) &FGM_MPC_ampl_max_static[0], FGM_MPC_BYTES_GLOBAL_ARRAYS,
                CACHE_WAIT);
    CACHE_wbL1d((void *) &FGM_MPC_rate_max_static[0], FGM_MPC_BYTES_GLOBAL_ARRAYS,
                CACHE_WAIT);

    /* Zero all other vectors */
    FGM_MPC_vec_init((fgm_float *)FGM_MPC_out_vec_static, 0.0);
    FGM_MPC_vec_init((fgm_float *)FGM_MPC_vec_t_static, 0.0);
    FGM_MPC_vec_init((fgm_float *)FGM_MPC_vec_z_new_static, 0.0);
    FGM_MPC_vec_init((fgm_float *)FGM_MPC_vec_z_old_static, 0.0);
    CACHE_wbL1d((void *) &(FGM_MPC_out_vec_static[0]), FGM_MPC_BYTES_GLOBAL_ARRAYS,
                CACHE_WAIT);
    CACHE_wbL1d((void *) &FGM_MPC_vec_t_static[0], FGM_MPC_BYTES_GLOBAL_ARRAYS,
                CACHE_WAIT);
    CACHE_wbL1d((void *) &FGM_MPC_vec_z_new_static[0], FGM_MPC_BYTES_GLOBAL_ARRAYS,
                CACHE_WAIT);
    CACHE_wbL1d((void *) &FGM_MPC_vec_z_old_static[0], FGM_MPC_BYTES_GLOBAL_ARRAYS,
                CACHE_WAIT);

    /* Assign these pointer for printing of debug info */
    FGM_MPC_vec_t = &(FGM_MPC_vec_t_static[0]);
    FGM_MPC_vec_z_new = &(FGM_MPC_vec_z_new_static[0]);
    FGM_MPC_vec_z_old = &(FGM_MPC_vec_z_old_static[0]);
    out_global = &(FGM_MPC_out_vec_static[0]);

    FGM_MPC_is_initialized = 1;
}

void FGM_MPC_reset(void)
{
    FGM_MPC_vec_init((fgm_float *)FGM_MPC_out_vec_static, 0.0);
    FGM_MPC_vec_init((fgm_float *)FGM_MPC_vec_z_new_static, 0.0);
    FGM_MPC_vec_init((fgm_float *)FGM_MPC_vec_z_old_static, 0.0);
    FGM_MPC_vec_init((fgm_float *)FGM_MPC_vec_t_static, 0.0);
    CACHE_wbL1d((void *) &(FGM_MPC_out_vec_static[0]), FGM_MPC_BYTES_GLOBAL_ARRAYS,
                CACHE_WAIT);
    CACHE_wbL1d((void *) &FGM_MPC_vec_t_static[0], FGM_MPC_BYTES_GLOBAL_ARRAYS,
                CACHE_WAIT);
    CACHE_wbL1d((void *) &FGM_MPC_vec_z_new_static[0], FGM_MPC_BYTES_GLOBAL_ARRAYS,
                CACHE_WAIT);
    CACHE_wbL1d((void *) &FGM_MPC_vec_z_old_static[0], FGM_MPC_BYTES_GLOBAL_ARRAYS,
                CACHE_WAIT);
}

void FGM_MPC_reset_worker(volatile fgm_float* sofb_setpoints)
{
    CACHE_invL1d((void *) &FGM_MPC_out_vec_static[0], FGM_MPC_BYTES_GLOBAL_ARRAYS,
                 CACHE_WAIT);
    CACHE_invL1d((void *) &FGM_MPC_vec_t_static[0], FGM_MPC_BYTES_GLOBAL_ARRAYS,
                 CACHE_WAIT);
    CACHE_invL1d((void *) &FGM_MPC_vec_z_new_static[0], FGM_MPC_BYTES_GLOBAL_ARRAYS,
                 CACHE_WAIT);
    CACHE_invL1d((void *) &FGM_MPC_vec_z_old_static[0], FGM_MPC_BYTES_GLOBAL_ARRAYS,
                 CACHE_WAIT);
    CACHE_invL1d((void *) &(sofb_setpoints[0]), FGM_MPC_BYTES_GLOBAL_ARRAYS,
                 CACHE_WAIT);
    DTF_awr_init();
    FGM_MPC_vec_copy((fgm_float *)&sofb_setpoints[(FGM_MPC_selfId - 1) * FGM_MPC_W_NROWS], FGM_MPC_sofb_local, FGM_MPC_W_NROWS);
    FGM_MPC_initialize_projection();
}

#pragma FUNCTION_OPTIONS(FGM_MPC_initialize_worker, "--opt_level=off --opt_for_speed=0")
void FGM_MPC_initialize_worker(volatile int selfId, volatile fgm_float* sofb_setpoints)
{
    int i, j;
    int ind_shift;

    FGM_MPC_selfId = selfId;

    /* Invalidate cache - arrays initialized by master core */
    CACHE_invL1d((void *) &FGM_MPC_in_vec_static[0], FGM_MPC_BYTES_GLOBAL_ARRAYS,
                 CACHE_WAIT);
    CACHE_invL1d((void *) &FGM_MPC_out_vec_static[0], FGM_MPC_BYTES_GLOBAL_ARRAYS,
                 CACHE_WAIT);
    CACHE_invL1d((void *) &FGM_MPC_ampl_max_static[0], FGM_MPC_BYTES_GLOBAL_ARRAYS,
                 CACHE_WAIT);
    CACHE_invL1d((void *) &FGM_MPC_rate_max_static[0], FGM_MPC_BYTES_GLOBAL_ARRAYS,
                 CACHE_WAIT);
    CACHE_invL1d((void *) &FGM_MPC_vec_t_static[0], FGM_MPC_BYTES_GLOBAL_ARRAYS,
                 CACHE_WAIT);
    CACHE_invL1d((void *) &FGM_MPC_vec_z_new_static[0], FGM_MPC_BYTES_GLOBAL_ARRAYS,
                 CACHE_WAIT);
    CACHE_invL1d((void *) &FGM_MPC_vec_z_old_static[0], FGM_MPC_BYTES_GLOBAL_ARRAYS,
                 CACHE_WAIT);
    CACHE_invL1d((void *) &(sofb_setpoints[0]), FGM_MPC_BYTES_GLOBAL_ARRAYS,
                 CACHE_WAIT);

    fgm_beta_local = beta_fgm;
    fgm_beta_p1_local = beta_fgm+1;

    /* Copy worker's matrix */
    ind_shift = (selfId - 1) * FGM_MPC_W_NROWS * FGM_MPC_W_NCOLS;
    assert((FGM_MPC_W_NROWS % 8) == 0);
    assert((FGM_MPC_W_NCOLS % 4) == 0);
#ifdef FGM_MPC_UNROLL
#ifdef FGM_MPC_QMPY
    // for QMPY following unrolling is optimal
    permXN_4waySIMD(&obj_func_matrix[ind_shift], FGM_MPC_in_mat_local, 8,
                    FGM_MPC_W_NROWS, FGM_MPC_W_NCOLS);
#else
    // for DMPY following unrolling is optimal
    permXN_2waySIMD(&obj_func_matrix[ind_shift], FGM_MPC_in_mat_local, 8,
                    FGM_MPC_W_NROWS, FGM_MPC_W_NCOLS);
#endif // FGM_MPC_QMPY
#else
    // no unrolling, just copy the matrix
    for (i = 0; i < FGM_MPC_W_NROWS * FGM_MPC_W_NCOLS; i++)
    {
        FGM_MPC_in_mat_local[i] = obj_func_matrix[ind_shift + i];
    }
#endif // FGM_MPC_UNROLL
    FGM_MPC_in_mat = &FGM_MPC_in_mat_local[0];

    /* Copy worker's matrix to compute vector */
    ind_shift = (selfId - 1) * FGM_MPC_W_NROWS * 2 * FGM_MPC_N_X0_OR_XD;
    for (i = 0; i < FGM_MPC_W_NROWS; i++)
    {
        for (j = 0; j < FGM_MPC_N_X0_OR_XD; j++)
        {
            // q = in_mat_vec*[x0_obs; xd_obs]
            FGM_MPC_x0_mat_local[i * FGM_MPC_N_X0_OR_XD + j] =
                    obj_func_vector_matrix[2*i * FGM_MPC_N_X0_OR_XD + j + ind_shift];
            FGM_MPC_xd_mat_local[i * FGM_MPC_N_X0_OR_XD + j] =
                    obj_func_vector_matrix[(2*i+1) * FGM_MPC_N_X0_OR_XD + j + ind_shift];
        }
    }

    /* Initialize worker's vector: now initialized in for loop */
    for (i = 0; i < FGM_MPC_W_NROWS; i++)
        FGM_MPC_in_vec_local[i] = 0.0;
    FGM_MPC_in_vec = &(FGM_MPC_in_vec_local[0]);

    /* Assign shared arrays */
    ind_shift = (selfId - 1) * FGM_MPC_W_NROWS;
    out_local = &(FGM_MPC_out_vec_static[(selfId - 1) * FGM_MPC_W_NROWS]);
    out_global = &(FGM_MPC_out_vec_static[0]);
    FGM_MPC_vec_t = &(FGM_MPC_vec_t_static[(selfId - 1) * FGM_MPC_W_NROWS]);
    FGM_MPC_vec_z_new = &(FGM_MPC_vec_z_new_static[(selfId - 1) * FGM_MPC_W_NROWS]);
    FGM_MPC_vec_z_old = &(FGM_MPC_vec_z_old_static[(selfId - 1) * FGM_MPC_W_NROWS]);
    FGM_MPC_ampl_max_local = &(FGM_MPC_ampl_max_static[(selfId - 1) * FGM_MPC_W_NROWS]);
    FGM_MPC_rate_max_local = &(FGM_MPC_rate_max_static[(selfId - 1) * FGM_MPC_W_NROWS]);

    /* Projection is also re-initialized after every FGM_MPC_solve() */
    FGM_MPC_vec_copy((fgm_float *)&sofb_setpoints[(selfId - 1) * FGM_MPC_W_NROWS], FGM_MPC_sofb_local, FGM_MPC_W_NROWS);
    FGM_MPC_initialize_projection();
}

int arr_ind(const int ncols, const int i_row, const int i_col)
{
    return i_col + i_row * ncols;
}

void permXN_2waySIMD(const volatile fgm_float * volatile in_mat,
                     volatile fgm_float * volatile out_mat, const int unroll,
                     const int nrows, const int ncols)
{
    int ind_out = 0, row_block, col, row_unroll;

    assert((ncols % 2) == 0);
    assert((nrows % unroll) == 0);

#pragma UNROLL(1)
    for (row_block = 0, ind_out = 0; row_block < nrows; row_block += unroll)
    {
#pragma UNROLL(1)
        for (col = 0; col < ncols; col += 2)
        {
#pragma UNROLL(1)
            for (row_unroll = 0; row_unroll < unroll;
                    row_unroll += 1, ind_out += 2)
            {
                out_mat[ind_out] = in_mat[arr_ind(ncols, row_block + row_unroll,
                                                  col)];
                out_mat[ind_out + 1] = in_mat[arr_ind(ncols,
                                                      row_block + row_unroll,
                                                      col + 1)];
            }
        }
    }
}

/*
 * permXN_4waySIMD prepares a matrix for a 4-way SIMD matrix-vector multiplication
 * unrolled by <unroll> rows.
 *
 */
void permXN_4waySIMD(const volatile fgm_float * volatile in_mat,
                     volatile fgm_float * volatile out_mat, const int unroll,
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
                out_mat[ind_out] = in_mat[arr_ind(ncols, row_block + row_unroll,
                                                  col)];
                out_mat[ind_out + 1] = in_mat[arr_ind(ncols,
                                                      row_block + row_unroll,
                                                      col + 1)];
                out_mat[ind_out + 2] = in_mat[arr_ind(ncols,
                                                      row_block + row_unroll,
                                                      col + 2)];
                out_mat[ind_out + 3] = in_mat[arr_ind(ncols,
                                                      row_block + row_unroll,
                                                      col + 3)];
            }
        }
    }
}

fgm_float * FGM_MPC_get_in_mat(void)
{
    return FGM_MPC_in_mat;
}

fgm_float * FGM_MPC_get_in_vec(void)
{
    return FGM_MPC_in_vec;
}

fgm_float volatile * FGM_MPC_get_out_vec(void)
{
    return &(out_global[0]);
}

fgm_float FGM_MPC_get_beta(void)
{
    return FGM_MPC_beta;
}

fgm_float FGM_MPC_get_beta_p1(void)
{
    return FGM_MPC_beta_p1;
}

fgm_float volatile * FGM_MPC_get_out_local(void)
{
    return out_local;
}

fgm_float volatile * FGM_MPC_get_FGM_MPC_vec_t(void)
{
    return FGM_MPC_vec_t;
}

void FGM_MPC_vec_init(fgm_float * restrict out, const fgm_float in)
{
    int i;
    for (i = 0; i < FGM_MPC_DIM; i++)
        out[i] = in;
}

/*
 void swap_vectors(c_float **a, c_float **b) {
 c_float *temp;

 temp = *b;
 *b   = *a;
 *a   = temp;
 }
 */
void FGM_MPC_vec_swap(fgm_float **in_out1, fgm_float **in_out2)
{
    fgm_float * tmp;
    tmp = *in_out2;
    *in_out2 = *in_out1;
    *in_out1 = tmp;
}

void FGM_MPC_vec_swap_volatile(volatile fgm_float * volatile * in_out1,
                           volatile fgm_float * volatile * in_out2)
{
    volatile fgm_float * tmp;
    tmp = *in_out2;
    *in_out2 = *in_out1;
    *in_out1 = tmp;
}

void FGM_MPC_vec_copy(const fgm_float * restrict in, fgm_float * restrict out, const int len)
{
    _nassert((int) in % 16 == 0);
    _nassert((int) out % 16 == 0);
    _nassert(len % 32 == 0);
    int i;
    for (i = 0; i < len; i++)
    {
        out[i] = in[i];
    }
}

fgm_float * FGM_MPC_get_input(void)
{
    return (fgm_float *)FGM_MPC_y_meas_in;
}

fgm_float * FGM_MPC_get_output(void)
{
    return (fgm_float *)out_global;
}


//#if (defined(SOC_C6678) && (USE_IPC == 1))
extern void print_vec(const obs_float *in, const int len, const char *name);
//#pragma FUNCTION_OPTIONS(FGM_MPC_solve, "--opt_level=off --opt_for_speed=0")
int FGM_MPC_solve(void)
{
    /* Algorithm:
     *
     * for ()
     *   t(i) = (I - J / L) y(i) - q / L
     *   z(i+1) = P(t(i))
     *   y(i+1) = (1 + beta) z(i+1) - beta z(i)
     * end
     *
     * (I - J / L)  = FGM_MPC_in_mat
     * q / L        = FGM_MPC_in_vec
     * y(i), y(i+1) = out
     * z(i+1)       = FGM_MPC_vec_z_new
     * z(i)         = FGM_MPC_vec_z_old
     * t(i)         = FGM_MPC_vec_t
     *
     */
    volatile int i_iter;
#ifdef FGM_MPC_PROFILING
    FGM_MPC_init_timers();
    FGM_MPC_tic(0);
#endif
    /*
     * Update fast gradient method objective vector
     */
#if defined(FGM_MPC_PROFILING) && (FGM_MPC_PROFILING_LEVEL > 1)
    FGM_MPC_tic(6);
#endif
#if (defined(FGM_MPC_PROFILING) && (FGM_MPC_PROFILING_LEVEL > 1)) || defined(FGM_MPC_SYNC_EVERY_STEP)
    ipc_master_set_req(1); // ML 0
    /* initialize_obj_func_vec(...); */
    ipc_master_wait_ack();
#endif
#if defined(FGM_MPC_PROFILING) && (FGM_MPC_PROFILING_LEVEL > 1)
    FGM_MPC_toc(6);
#endif

    /* Fast gradient method  loop */
#pragma UNROLL(1)
    for (i_iter = 0; i_iter < FGM_MPC_MAX_ITER; i_iter++)
    {
        /*
         * FGM_MPC_vec_t = (I - J / L) out - FGM_MPC_in_vec
         */
#if defined(FGM_MPC_PROFILING) && (FGM_MPC_PROFILING_LEVEL > 1)
        FGM_MPC_tic(1);
#endif
        ipc_master_set_req(1); // ML 1
#if (defined(FGM_MPC_PROFILING) && (FGM_MPC_PROFILING_LEVEL > 1)) || defined(FGM_MPC_SYNC_EVERY_STEP)
        ipc_master_wait_ack();
#endif
        /* FGM_MPC_gradient_step(out, FGM_MPC_vec_t); */
#if defined(FGM_MPC_PROFILING) && (FGM_MPC_PROFILING_LEVEL > 1)
        FGM_MPC_toc(1);
#endif
        /*
         * z(i+1) = P(t(i))
         */
#if defined(FGM_MPC_PROFILING) && (FGM_MPC_PROFILING_LEVEL > 1)
        FGM_MPC_tic(2);
#endif
#if (defined(FGM_MPC_PROFILING) && (FGM_MPC_PROFILING_LEVEL > 1)) || defined(FGM_MPC_SYNC_EVERY_STEP)
        ipc_master_set_req(1); // ML 2
        ipc_master_wait_ack();
#endif
        /* FGM_MPC_vec_swap(&(FGM_MPC_vec_z_new), &(FGM_MPC_vec_z_old)); */
        /* FGM_MPC_project(FGM_MPC_vec_t, FGM_MPC_vec_z_new); */
#if defined(FGM_MPC_PROFILING) && (FGM_MPC_PROFILING_LEVEL > 1)
        FGM_MPC_toc(2);
#endif
        /*
         * y(i+1) = (1 + beta) z(i+1) - beta z(i)
         */
#if defined(FGM_MPC_PROFILING) && (FGM_MPC_PROFILING_LEVEL > 1)
        FGM_MPC_tic(3);
#endif
#if (defined(FGM_MPC_PROFILING) && (FGM_MPC_PROFILING_LEVEL > 1)) || defined(FGM_MPC_SYNC_EVERY_STEP)
        ipc_master_set_req(1); // ML 3
#endif
        ipc_master_wait_ack();
        /* FGM_MPC_beta_step(FGM_MPC_vec_z_new, FGM_MPC_vec_z_old, out); */
#if defined(FGM_MPC_PROFILING) && (FGM_MPC_PROFILING_LEVEL > 1)
        FGM_MPC_toc(3);
#endif

#if (defined(FGM_MPC_PROFILING) && (FGM_MPC_PROFILING_LEVEL > 1)) || defined(FGM_MPC_SYNC_EVERY_STEP)
        ipc_master_set_req(1); // ML 4
        ipc_master_wait_ack();
#endif
#if (FGM_MPC_DEBUG_LEVEL > 0)
        if (i_iter <= FGM_MPC_DEBUG_ITERMAX)
        {
            printf("Iter %d\n", i_iter);
            CACHE_invL1d ((void *) &out_global[0], NUMSLAVES * FGM_MPC_BYTES_WORKER_ARRAYS, CACHE_WAIT);
            for (i = 0; i < NUMSLAVES; i++)
            {
                print_vec(&out_global[i * FGM_MPC_W_NROWS],FGM_MPC_W_NROWS,"out_global");
                //printf("out_global[%d]=%.4f, ", i * FGM_MPC_W_NROWS, out_global[i * FGM_MPC_W_NROWS]);
                //printf("out_global[%d]=%.4f\n", (i+1) * FGM_MPC_W_NROWS - 1, out_global[(i+1) * FGM_MPC_W_NROWS - 1]);
            }
        }
#endif /* FGM_MPC_DEBUG */
    }
    /*
     * Update projection limits
     */
#if defined(FGM_MPC_PROFILING) && (FGM_MPC_PROFILING_LEVEL > 1)
        FGM_MPC_tic(7);
#endif
#if (defined(FGM_MPC_PROFILING) && (FGM_MPC_PROFILING_LEVEL > 1)) || defined(FGM_MPC_SYNC_EVERY_STEP)
        ipc_master_set_req(1); // ML 5
        ipc_master_wait_ack();
#endif
    /* initialize_projection(...); */
#if defined(FGM_MPC_PROFILING) && (FGM_MPC_PROFILING_LEVEL > 1)
        FGM_MPC_toc(7);
#endif

#if defined(FGM_MPC_PROFILING)
    FGM_MPC_toc(0);
#endif
    return 0;
}

/* Workers end up in this loop after initialization */
//#pragma FUNCTION_OPTIONS(FGM_MPC_solve_worker, "--opt_level=off --opt_for_speed=0")
void FGM_MPC_solve_worker(const fgm_float * x0, const fgm_float * xd)
{
    volatile int iter;
    /* Update objective function vector based on observer output */
#if (defined(FGM_MPC_PROFILING) && (FGM_MPC_PROFILING_LEVEL > 1)) || defined(FGM_MPC_SYNC_EVERY_STEP)
    ipc_slave_wait_req(); // ML 0
#endif
    FGM_MPC_initialize_obj_func_vec((const fgm_float *)FGM_MPC_x0_mat_local,
                                    x0,
                                    (const fgm_float *)FGM_MPC_xd_mat_local,
                                    xd,
                                    (fgm_float *)FGM_MPC_in_vec);
#if (defined(FGM_MPC_PROFILING) && (FGM_MPC_PROFILING_LEVEL > 1)) || defined(FGM_MPC_SYNC_EVERY_STEP)
    ipc_slave_set_ack(1);
#endif

#pragma UNROLL(1)
    for (iter = 0; iter < FGM_MPC_MAX_ITER; iter++)
    {
        ipc_slave_wait_req(); // ML 1
        CACHE_invL1d((void *) &(out_global[0]), FGM_MPC_BYTES_GLOBAL_ARRAYS,
                                 CACHE_WAIT);
        FGM_MPC_gradient_step((const fgm_float *) FGM_MPC_in_mat,
                              (const fgm_float *) out_global,
                              (const fgm_float *) FGM_MPC_in_vec,
                              (fgm_float *) FGM_MPC_vec_t);
#if (defined(FGM_MPC_PROFILING) && (FGM_MPC_PROFILING_LEVEL > 1)) || defined(FGM_MPC_SYNC_EVERY_STEP)
        ipc_slave_set_ack(1);
        ipc_slave_wait_req(); // ML 2
#endif
        FGM_MPC_vec_swap_volatile(&(FGM_MPC_vec_z_new), &(FGM_MPC_vec_z_old));
#if (FGM_MPC_HORIZON == 1)
        FGM_MPC_project((const fgm_float *) FGM_MPC_vec_t,
                        (const fgm_float *) FGM_MPC_box_min_local,
                        (const fgm_float *) FGM_MPC_box_max_local,
                        (fgm_float *) FGM_MPC_vec_z_new);
#else
        FGM_MPC_project((const fgm_float *) FGM_MPC_vec_t,
                        (fgm_float *) FGM_MPC_vec_z_new);
#endif
#if (defined(FGM_MPC_PROFILING) && (FGM_MPC_PROFILING_LEVEL > 1)) || defined(FGM_MPC_SYNC_EVERY_STEP)
        ipc_slave_set_ack(1);
        ipc_slave_wait_req(); // ML 3
#endif
        FGM_MPC_beta_step((const fgm_float *) FGM_MPC_vec_z_new,
                          (const fgm_float *) FGM_MPC_vec_z_old,
                          (fgm_float *) out_local);
        CACHE_wbL1d((void *) &(out_local[0]), FGM_MPC_BYTES_LOCAL_ARRAYS,
                    CACHE_WAIT);
#if (defined(FGM_MPC_PROFILING) && (FGM_MPC_PROFILING_LEVEL > 1)) || defined(FGM_MPC_SYNC_EVERY_STEP)
        ipc_slave_set_ack(1);
        ipc_slave_wait_req(); // ML 4
#endif
        ipc_slave_set_ack(1);

    }
    /* Re-initialize projection using computed solution */
#if (defined(FGM_MPC_PROFILING) && (FGM_MPC_PROFILING_LEVEL > 1)) || defined(FGM_MPC_SYNC_EVERY_STEP)
    ipc_slave_wait_req(); // ML 5
#endif
    FGM_MPC_initialize_projection();
#if (defined(FGM_MPC_PROFILING) && (FGM_MPC_PROFILING_LEVEL > 1)) || defined(FGM_MPC_SYNC_EVERY_STEP)
    ipc_slave_set_ack(1);
#endif
}
