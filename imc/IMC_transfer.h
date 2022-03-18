#ifndef IMC_IMC_TRANSFER_H_
#define IMC_IMC_TRANSFER_H_

int BPM_to_float(const LIBQDMA_ARR_TYPE * in_vec, imc_float * out_vec);
int CM_to_int(const imc_float * in_vec, LIBQDMA_ARR_TYPE * out_vec);

#endif /* IMC_IMC_TRANSFER_H_ */
