/*
 * GSVD_ctr.h
 *
 *  Created on: Apr 13, 2021
 *      Author: idris
 */

#ifndef GSVD_CTR_H_
#define GSVD_CTR_H_

#include "fofb_config.h"
#if (defined(SOC_C6678) && (USE_IPC==1))
#include "utils/ipc_utils.h"
#define GSVD_NUM_WORKERS  (NUMSLAVES) // should be set to 4
#else
#define GSVD_NUM_WORKERS    (1)
#endif

#define GSVD_XDIR               (XDIR)

typedef float gsvd_float;
#define GSVD_FLOAT_SIZE         (sizeof(gsvd_float))
#define GSVD_CACHE_LINESIZE     (64) // bytes
#define GSVD_ARRAY_ALIGN        (GSVD_CACHE_LINESIZE)
#define GSVD_UNIT_TESTS         (1)

#define GSVD_NY       (96)  // HARDCODED (was 108)
#define GSVD_NS       (96)  // HARDCODED (was 108)
#define GSVD_NF       (64)  // HARDCODED (was 60)
#define GSVD_NU       (GSVD_NS+GSVD_NF)

/* Lengths per worker */
#if (defined(SOC_C6678) && (USE_IPC==1))
#define GSVD_NY_W       (32)
#define GSVD_NS_W       (32)
#define GSVD_NF_W       (16)
#else
#define GSVD_NY_W       (128)
#define GSVD_NS_W       (128)
#define GSVD_NF_W       (64)
#endif

#define GSVD_NY_PAD     (GSVD_NY_W * GSVD_NUM_WORKERS)
#define GSVD_NS_PAD     (GSVD_NS_W * GSVD_NUM_WORKERS)
#define GSVD_NF_PAD     (GSVD_NF_W * GSVD_NUM_WORKERS)
#define GSVD_NU_PAD     (GSVD_NS_PAD+GSVD_NF_PAD)

/* Gain matrix sizes */
// Ks : (y-ys-yf) -> us
#define GSVD_KS_W_NROWS     (GSVD_NS_W)
#define GSVD_KS_W_NCOLS     (GSVD_NY_W * GSVD_NUM_WORKERS)
#define GSVD_KS_TOT_NROWS   (GSVD_KS_W_NROWS * GSVD_NUM_WORKERS)
#define GSVD_KS_TOT_NCOLS   (GSVD_KS_W_NCOLS)
#define GSVD_SIZE_KS_LOCAL  (GSVD_KS_W_NROWS * GSVD_KS_W_NCOLS)
#define GSVD_SIZE_KS_TOTAL  (GSVD_KS_TOT_NROWS * GSVD_KS_TOT_NCOLS)
// Kf : (y-ys-yf) -> uf
#define GSVD_KF_W_NROWS     (GSVD_NF_W)
#define GSVD_KF_W_NCOLS     (GSVD_NY_W * GSVD_NUM_WORKERS)
#define GSVD_KF_TOT_NROWS   (GSVD_KF_W_NROWS * GSVD_NUM_WORKERS)
#define GSVD_KF_TOT_NCOLS   (GSVD_KF_W_NCOLS)
#define GSVD_SIZE_KF_LOCAL  (GSVD_KF_W_NROWS * GSVD_KF_W_NCOLS)
#define GSVD_SIZE_KF_TOTAL  (GSVD_KF_TOT_NROWS * GSVD_KF_TOT_NCOLS)
// Ps : us -> -ys
#define GSVD_PS_W_NROWS     (GSVD_NY_W)
#define GSVD_PS_W_NCOLS     (GSVD_NS_W * GSVD_NUM_WORKERS)
#define GSVD_PS_TOT_NROWS   (GSVD_PS_W_NROWS * GSVD_NUM_WORKERS)
#define GSVD_PS_TOT_NCOLS   (GSVD_PS_W_NCOLS)
#define GSVD_SIZE_PS_LOCAL  (GSVD_PS_W_NROWS * GSVD_PS_W_NCOLS)
#define GSVD_SIZE_PS_TOTAL  (GSVD_PS_TOT_NROWS * GSVD_PS_TOT_NCOLS)
// Pf : uf -> -yf
#define GSVD_PF_W_NROWS     (GSVD_NY_W)
#define GSVD_PF_W_NCOLS     (GSVD_NF_W * GSVD_NUM_WORKERS)
#define GSVD_PF_TOT_NROWS   (GSVD_PF_W_NROWS * GSVD_NUM_WORKERS)
#define GSVD_PF_TOT_NCOLS   (GSVD_PF_W_NCOLS)
#define GSVD_SIZE_PF_LOCAL  (GSVD_PF_W_NROWS * GSVD_PF_W_NCOLS)
#define GSVD_SIZE_PF_TOTAL  (GSVD_PF_TOT_NROWS * GSVD_PF_TOT_NCOLS)

/*
 * gsvd_float * GSVD_ctr(void);
 *
 * Copy GSVD_NY measurements to GSVD_get_input() and obtain
 * GSVD_NU inputs from GSVD_ctr().
 */
gsvd_float * GSVD_get_input(void);
gsvd_float * GSVD_ctr(int restart);   // returned ptr is of length GSVD_NU and aligned to GSVD_ARRAY_ALIGN

#ifdef SOC_C6678
#pragma FUNC_NEVER_RETURNS(GSVD_ctr_worker)
void GSVD_ctr_worker(Uint32 selfId);
#endif

#if (~defined(SOC_C6678) && (USE_IPC==0))
void gain_step(const gsvd_float * in_vec, gsvd_float * out_vec);
#endif

#endif /* GSVD_CTR_H_ */
