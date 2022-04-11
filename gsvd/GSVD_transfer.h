#ifndef GSVD_TRANSFER_H_
#define GSVD_TRANSFER_H_

#include "fofb_config.h"
#include "utils/libQDMA.h"
#include "gsvd/GSVD_ctr.h"

#define GSVD_LIMIT_READ             (ORBIT_LIMIT) // in nanometers
#define GSVD_LIMIT_WRITE            (5000000) // in Amperes/GSVD_SCALING_FACTOR_WRITE
#define GSVD_SCALING_FACTOR_WRITE   (1000000.0) // must match Python script gain

int GSVD_BPM_to_float(const LIBQDMA_ARR_TYPE * in_vec, gsvd_float * out_vec);
int GSVD_CM_to_int(const gsvd_float * in_vec, LIBQDMA_ARR_TYPE * out_vec);

#endif /* GSVD_TRANSFER_H_ */
