#ifndef FAST_GRADIENT_METHOD_H_
#define FAST_GRADIENT_METHOD_H_

#include "utils/ipc_utils.h"
#include "mpc/observer.h"

/* Options */
#define FGM_MPC_EMBEDDED
#define FGM_MPC_PARALLELIZE
#ifndef SOC_C6678
#define SOC_C6678
#endif

#undef DOUBLE_PRECISION

#undef use_global_volatile // to test difference between using global volatile arrays and casted arrays with func args

/* Settings */
#ifdef DOUBLE_PRECISION
typedef double fgm_float;
#define FGM_MPC_EPS_ABS (1e-4)
#define FGM_MPC_EPS_REL (1e-4)
#define FGM_MPC_FLOAT_SIZE  (8) // bytes
#else
typedef float fgm_float;
#define FGM_MPC_EPS_ABS (1e-4f)
#define FGM_MPC_EPS_REL (1e-4f)
#define FGM_MPC_FLOAT_SIZE  (4) // bytes
#endif

/* FGM dimensions */
#define FGM_MPC_NUM_WORKERS     (NUMSLAVES)
#define FGM_MPC_HORIZON         (1)
#if (FGM_MPC_HORIZON == 1)
#define FGM_MPC_W_NROWS         (32) // row length per worker, FGM_MPC_W_NROWS * FGM_MPC_FLOAT_SIZE > FGM_MPC_CACHE_LINESIZE
#define FGM_MPC_W_NROWS_HALF    (16)
#else // HORIZON == 2
#define FGM_MPC_W_NROWS         (64) // row length per worker, FGM_MPC_W_NROWS * FGM_MPC_FLOAT_SIZE > FGM_MPC_CACHE_LINESIZE
#define FGM_MPC_W_NROWS_HALF    (32)
#endif
#define FGM_MPC_W_NCOLS         (FGM_MPC_W_NROWS * FGM_MPC_NUM_WORKERS) // col length per worker, total col length of obj func matrix
#define FGM_MPC_DIM             (FGM_MPC_W_NROWS * FGM_MPC_NUM_WORKERS) // square system

#define FGM_MPC_CACHE_LINESIZE      (64) // bytes
#define FGM_MPC_ARRAY_ALIGN         (FGM_MPC_CACHE_LINESIZE)
#define FGM_MPC_BYTES_IN_MAT_TOTAL  (FGM_MPC_DIM * FGM_MPC_DIM * FGM_MPC_FLOAT_SIZE)
#define FGM_MPC_BYTES_IN_VEC_TOTAL  (FGM_MPC_DIM * FGM_MPC_FLOAT_SIZE)
#define FGM_MPC_BYTES_WORKER_ARRAYS (FGM_MPC_W_NROWS * FGM_MPC_FLOAT_SIZE)
#define FGM_MPC_BYTES_GLOBAL_ARRAYS (FGM_MPC_DIM * FGM_MPC_FLOAT_SIZE)

/* FGM settings */
#define FGM_MPC_MAX_ITER            (20)
#define FGM_MPC_CHECK_TERMINATION   (0) // 0 -> no check, >0 -> check on iter % CHECK_TERMINATION==0
#undef FGM_MPC_SYNC_EVERY_STEP          // sync cores after every FGM operation
#define FGM_MPC_UNROLL                  // unroll the mat-mpy in gradient step
#define FGM_MPC_QMPY                    // use quad-multiply, if undefined uses dual multiply instead
#undef FGM_MPC_COMBINE_GRAD_PROJ

/* FGM - observer interface */
#define FGM_MPC_N_X0_OR_XD          (192) // defines the length of padded x0 or xd from observer
#define FGM_MPC_SIZE_Q_MAT          (FGM_MPC_DIM * 2 * FGM_MPC_N_X0_OR_XD)
#define FGM_MPC_BYTES_Q_MAT_TOTAL   (FGM_MPC_SIZE_Q_MAT * FGM_MPC_FLOAT_SIZE)
#define FGM_MPC_BYTES_X0_OR_XD      (FGM_MPC_N_X0_OR_XD * FGM_MPC_FLOAT_SIZE)

/* DEBUG FLAGS */
#define FGM_MPC_DEBUG_LEVEL     (0)     // prints the different steps 0,1,2
#define FGM_MPC_DEBUG_ITERMAX   (41)    // prints until itermax
#define FGM_MPC_DEBUG_SLAVE_I   (0)     // print slave data 0,1
#define FGM_MPC_DEBUG_SLAVE_IP  (1)     // number of iterations until printing disabled 1...MAX_ITER
#if (FGM_MPC_DEBUG_LEVEL == 2)
#ifndef FGM_MPC_SYNC_EVERY_STEP
#define FGM_MPC_SYNC_EVERY_STEP
#endif
#endif

/* Profiling */
#define FGM_MPC_PROFILING // enable profiling
#define FGM_MPC_PROFILING_LEVEL (0) // 0, 1, 2
#if (FGM_MPC_PROFILING_LEVEL == 2)
#ifndef FGM_MPC_SYNC_EVERY_STEP
#define FGM_MPC_SYNC_EVERY_STEP
#endif
#endif

/* Functions */

/*
 * FGM_MPC_initialize:
 * Copies problem data and assigns the projection function: void proj_func(const float * restrict in, float * restrict out).
 * Needs to be called before FGM_MPC_solve.
 */
void FGM_MPC_initialize(const fgm_float * obj_func_matrix,
                        const fgm_float * obj_func_vector_matrix,
                        const fgm_float * ampl_max_vector,
                        const fgm_float * rate_max_vector,
                        const fgm_float obj_func_grad_max_eigval,
                        const fgm_float obj_func_grad_min_eigval,
                        const int fgm_dim,
                        const int fgm_horizon);
void FGM_MPC_initialize_worker(volatile int selfId);
void FGM_MPC_finalize(void);
void FGM_MPC_print_settings(void);

/*
 * FGM_MPC_solve:
 * Solves the QP. Warm-start using out-array if warm_start == 1. Solution in out. Returns 0
 * if problem has been solved. Returns 1 if maximum iterations reached.
 */
fgm_float * FGM_MPC_get_input(void);
fgm_float * FGM_MPC_get_output(void);
int FGM_MPC_solve(void);
#pragma FUNC_NEVER_RETURNS(FGM_MPC_solve_worker)
void FGM_MPC_solve_worker(void);
//int FGM_MPC_solve_aircraft_example(fgm_float * out, const int warm_start, const int horiz_len); // calls projection three times
int FGM_MPC_get_num_iter(void);
fgm_float FGM_MPC_compute_obj_val(fgm_float * solution, fgm_float * obj_fun_matrix, fgm_float * obj_fun_vec);

/* Only here for tests */
void FGM_MPC_gradient_step(const fgm_float *restrict in_mat, const fgm_float *restrict in_vec,
                           const fgm_float *restrict in_vec_sub, fgm_float *restrict out_vec);
//void FGM_MPC_initialize_box_projection(const fgm_float box_min, const fgm_float box_max);
//void FGM_MPC_box_projection(const fgm_float * restrict in, fgm_float * restrict out);
fgm_float * FGM_MPC_get_in_mat(void);
fgm_float * FGM_MPC_get_in_vec(void);
fgm_float volatile * FGM_MPC_get_out_vec(void);
fgm_float FGM_MPC_get_beta(void);
fgm_float FGM_MPC_get_beta_p1(void);
fgm_float volatile * FGM_MPC_get_out_local(void);
fgm_float volatile * FGM_MPC_get_FGM_MPC_vec_t(void);
fgm_float FGM_MPC_check_solution(const fgm_float *restrict sol);

#ifdef FGM_MPC_PROFILING
typedef struct FGMTimer {
#ifdef SOC_C6678
    unsigned long int tic;
    unsigned long int toc;
#else
    struct timespec tic;
    struct timespec toc;
#endif
    unsigned long int cycles_cumsum;
    int n_calls;
    float t_cumsum;
} FGM_MPC_Timer;
int FGM_MPC_get_num_timers(void);
FGM_MPC_Timer * FGM_MPC_get_all_timers(void); // returns 5 timers for FGM_MPC_PROFILING_LEVEL==2,  1 timer else
char ** FGM_MPC_get_timer_names(void);
float FGM_MPC_average_time(FGM_MPC_Timer *t);
float FGM_MPC_total_time(FGM_MPC_Timer *t);
void FGM_MPC_print_timer_info(FGM_MPC_Timer timer, char *timer_name);
#endif

#endif /* FAST_GRADIENT_METHOD_H_ */
