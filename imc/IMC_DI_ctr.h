/*
 * IMC_DI_ctr.h
 *
 *  Created on: Apr 13, 2021
 *      Author: idris
 */

#ifndef IMC_DI_CTR_H_
#define IMC_DI_CTR_H_

#if (defined(SOC_C6678) && (USE_IPC==1))
#include "ipc_utils.h"
#endif
#include "fofb_config.h"

typedef float imc_float;
#define IMC_DI_FLOAT_SIZE   (4)

#define IMC_DI_UNIT_TESTS   (1)

#define IMC_DI_XDIR (XDIR)

#define IMC_DI_NY       (TOT_NUM_BPM)
#define IMC_DI_NU       (TOT_NUM_CM)
#if (defined(SOC_C6678) && (USE_IPC==1))
#define IMC_DI_NUM_WORKERS  (NUMSLAVES)
#else
#define IMC_DI_NUM_WORKERS  (6)
#endif
#define IMC_DI_W_NROWS  (32)
#define IMC_DI_W_NCOLS  (IMC_DI_W_NROWS * IMC_DI_NUM_WORKERS)
#define IMC_DI_DIM      (IMC_DI_W_NROWS * IMC_DI_NUM_WORKERS)
#define IMC_DI_TOT_NROWS  (IMC_DI_W_NROWS * IMC_DI_NUM_WORKERS)
#define IMC_DI_TOT_NCOLS  (IMC_DI_W_NCOLS)

#define IMC_DI_CACHE_LINESIZE      (64) // bytes
#define IMC_DI_ARRAY_ALIGN         (IMC_DI_CACHE_LINESIZE)
#define IMC_DI_SIZE_IN_MAT_LOCAL   (IMC_DI_W_NROWS * IMC_DI_W_NCOLS)
#define IMC_DI_SIZE_IN_MAT_TOTAL   (IMC_DI_DIM * IMC_DI_DIM)
#define IMC_DI_BYTES_WORKER_ARRAYS (IMC_DI_W_NROWS * IMC_DI_FLOAT_SIZE)
#define IMC_DI_BYTES_GLOBAL_ARRAYS (IMC_DI_DIM * IMC_DI_FLOAT_SIZE)

/*
 * imc_float * IMC_DI_ctr(void);
 *
 * Copy measurement to IMC_DI_get_input() and obtain
 * result from IMC_DI_ctr().
 */
imc_float * IMC_DI_get_input(void);
imc_float * IMC_DI_ctr(void);   // returned ptr is of length IMC_DI_DIM and aligned to IMC_DI_ARRAY_ALIGN
#if (IMC_DI_UNIT_TESTS == 1)
int IMC_DI_unit_test(void);
#endif

#ifdef SOC_C6678
#pragma FUNC_NEVER_RETURNS(IMC_DI_ctr_worker)
#endif
void IMC_DI_ctr_worker(Uint32 selfId);

#endif /* IMC_DI_CTR_H_ */
