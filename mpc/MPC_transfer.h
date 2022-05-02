#ifndef MPC_TRANSFER_H_
#define MPC_TRANSFER_H_

#include "fofb_config.h"
#include "utils/libQDMA.h"
#include "mpc/fast_gradient_method.h"

#define MPC_LIMIT_READ              (ORBIT_LIMIT) // in nanometers
#define MPC_LIMIT_WRITE             (5000000) // in Amperes/MPC_SCALING_FACTOR_WRITE
#define MPC_SCALING_FACTOR_READ     (0.001f) // receives measurements in micrometers
#define MPC_SCALING_FACTOR_WRITE    (-1e3f) // Python script needs 1/1e6 gain

int MPC_BPM_to_float(const LIBQDMA_ARR_TYPE * in_vec, fgm_float * out_vec);
int MPC_CM_to_int(const fgm_float * in_vec, LIBQDMA_ARR_TYPE * out_vec);
int MPC_get_num_BPM(void);
int MPC_get_num_CM(void);

#endif /* MPC_TRANSFER_H_ */
