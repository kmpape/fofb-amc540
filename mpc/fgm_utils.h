/*
 * fgm_utils.h
 *
 *  Created on: Apr 7, 2020
 *      Author: idris
 */

#ifndef FGM_MPC_UTILS_H_
#define FGM_MPC_UTILS_H_

#include "fast_gradient_method.h"

/* Profiling Utilities */
#ifdef FGM_MPC_PROFILING
static double CLOCK_RATE = 1000000000.0;

void FGM_MPC_init_timers(void);
void FGM_MPC_tic(const int i_timer);
void FGM_MPC_toc(const int i_timer);
#if (FGM_MPC_PROFILING_LEVEL == 2)
#define FGM_MPC_n_timers  (8)
#else
#define FGM_MPC_n_timers  (1)
#endif /* FGM_MPC_PROFILING_LEVEL */
#endif /* FGM_MPC_PROFILING */

#endif /* FGM_MPC_UTILS_H_ */
