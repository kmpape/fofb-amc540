#ifndef IMC_IMC_TRANSFER_H_
#define IMC_IMC_TRANSFER_H_

#include "fofb_config.h"
#include "utils/libQDMA.h"
#include "imc/IMC_DI_ctr.h"

#define IMC_LIMIT_READ             (ORBIT_LIMIT) // in nanometers
#define IMC_LIMIT_WRITE            (5000000) // in Amperes/IMC_SCALING_FACTOR_WRITE
#define IMC_SCALING_FACTOR_WRITE   (1000000.0) // must match Python script gain

void BPM_to_float(const LIBQDMA_ARR_TYPE * in_vec, imc_float * out_vec);
void CM_to_int(const imc_float * in_vec, LIBQDMA_ARR_TYPE * out_vec);

#endif /* IMC_IMC_TRANSFER_H_ */
