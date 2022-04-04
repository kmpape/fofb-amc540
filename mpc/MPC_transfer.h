#ifndef IMC_IMC_TRANSFER_H_
#define IMC_IMC_TRANSFER_H_

#include "utils/libQDMA.h"
#include "mpc/fast_gradient_method.h"

#define MPC_SCALING_FACTOR_READ     (0.001f) // receives measurements in micrometers
#define MPC_SCALING_FACTOR_WRITE    (-1e3f) // = - 20000 * 1000 / 1e6

int MPC_BPM_to_float(const LIBQDMA_ARR_TYPE * in_vec, fgm_float * out_vec);
int MPC_CM_to_int(const fgm_float * in_vec, LIBQDMA_ARR_TYPE * out_vec);

#endif /* IMC_IMC_TRANSFER_H_ */
