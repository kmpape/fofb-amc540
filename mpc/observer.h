#ifndef OBSERVER_H_
#define OBSERVER_H_

typedef float obs_float;
#define OBS_FLOAT_SIZE  (sizeof(obs_float)) // bytes

#define OBS_NUM_WORKERS     (NUMSLAVES)
#define OBS_W_NROWS         (32)
#define OBS_W_NCOLS         (OBS_NUM_WORKERS*OBS_W_NROWS)
#define OBS_DIM             (OBS_NUM_WORKERS*OBS_W_NROWS)

#undef OBS_SYNC_EVERY_STEP
#define OBS_DEBUG_LEVEL     (0) // 0,1,2
#if (OBS_DEBUG_LEVEL > 0)
#ifndef OBS_SYNC_EVERY_STEP
#define OBS_SYNC_EVERY_STEP
#endif
#endif

#define OBS_UNROLL

#define OBS_CACHE_LINESIZE      (64) // bytes
#define OBS_ARRAY_ALIGN         (OBS_CACHE_LINESIZE)
#define OBS_BYTES_MAT_TOTAL     (OBS_DIM * OBS_DIM * OBS_FLOAT_SIZE)
#define OBS_BYTES_LOCAL_ARRAYS  (OBS_W_NROWS * OBS_FLOAT_SIZE)
#define OBS_BYTES_GLOBAL_ARRAYS (OBS_DIM * OBS_FLOAT_SIZE)


void OBS_initialize_master(const obs_float * Lx_init,
                           const obs_float * Ld_init,
                           const obs_float * Cx_init,
                           const obs_float * xd_init,
                           const obs_float * x0_init,
                           const obs_float * x1_init,
                           const obs_float * x2_init,
                           const obs_float * x3_init,
                           const obs_float * x4_init,
                           const obs_float * x5_init,
                           const obs_float * x6_init,
                           const obs_float * x7_init,
                           const obs_float * x8_init,
                           const int obs_dim);
void OBS_initialize_worker(volatile int selfId);

void OBS_update_observer_master(const obs_float * y_meas,
                                const obs_float * u_old);
void OBS_update_observer_worker(const obs_float * y_meas,
                                const obs_float * u_old);
obs_float volatile * OBS_get_xd(void); // to be queried every time after OBS_update_observer
obs_float volatile * OBS_get_x0_new(void); // to be queried every time after OBS_update_observer

#endif /* OBSERVER_H_ */
