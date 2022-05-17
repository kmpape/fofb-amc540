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
#define FGM_MPC_BYTES_LOCAL_ARRAYS  (FGM_MPC_W_NROWS * FGM_MPC_FLOAT_SIZE)
#define FGM_MPC_BYTES_GLOBAL_ARRAYS (FGM_MPC_DIM * FGM_MPC_FLOAT_SIZE)

/* FGM settings */
#define FGM_MPC_MAX_ITER            (20)
#define FGM_MPC_CHECK_TERMINATION   (0) // 0 -> no check, >0 -> check on iter % CHECK_TERMINATION==0
#undef FGM_MPC_SYNC_EVERY_STEP          // sync cores after every FGM operation
#define FGM_MPC_UNROLL                  // unroll the mat-mpy in gradient step
#define FGM_MPC_QMPY                    // use quad-multiply, if undefined uses dual multiply instead

/* FGM - observer interface */
#define FGM_MPC_N_X0_OR_XD          (192) // defines the length of padded x0 or xd from observer
#define FGM_MPC_SIZE_Q_MAT          (FGM_MPC_DIM * 2 * FGM_MPC_N_X0_OR_XD)
#define FGM_MPC_BYTES_Q_MAT_TOTAL   (FGM_MPC_SIZE_Q_MAT * FGM_MPC_FLOAT_SIZE)
#define FGM_MPC_BYTES_X0_OR_XD      (FGM_MPC_N_X0_OR_XD * FGM_MPC_FLOAT_SIZE)

/* DEBUG FLAGS */
#define FGM_MPC_DEBUG_LEVEL     (0)     // prints the different steps 0,1,2

/* Profiling */
#define FGM_MPC_PROFILING // enable profiling
#define FGM_MPC_PROFILING_LEVEL (0) // 0, 1, 2
#if (FGM_MPC_PROFILING_LEVEL == 2)
#ifndef FGM_MPC_SYNC_EVERY_STEP
#define FGM_MPC_SYNC_EVERY_STEP
#endif
#endif

void FGM_MPC_initialize(void);
void FGM_MPC_initialize_worker(volatile int selfId, volatile fgm_float* sofb_setpoints);

fgm_float * FGM_MPC_get_input(void); // placeholder for measurements
fgm_float * FGM_MPC_get_output(void); // solution of MPC problem

int FGM_MPC_solve(void);
void FGM_MPC_solve_worker(const fgm_float * x0, const fgm_float * xd); // takes observer variables as input

void FGM_MPC_reset(void); // zeros previous solutions, workers must invalidate
void FGM_MPC_reset_worker(volatile fgm_float* sofb_setpoints); // zeros previous solutions, workers must invalidate

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
