#ifndef IMC_IMC_TRANSFER_H_
#define IMC_IMC_TRANSFER_H_

#include "utils/libQDMA.h"
#include "gsvd/GSVD_ctr.h"

int GSVD_BPM_to_float(const LIBQDMA_ARR_TYPE * in_vec, gsvd_float * out_vec);
int GSVD_CM_to_int(const gsvd_float * in_vec, LIBQDMA_ARR_TYPE * out_vec);

#endif /* IMC_IMC_TRANSFER_H_ */
