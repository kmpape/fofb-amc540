#ifndef MPC_MPC_CTR_H_
#define MPC_MPC_CTR_H_

#include "mpc/fast_gradient_method.h"

void MPC_initialize(void);
void MPC_initialize_worker(volatile int selfId, volatile fgm_float* sofb_setpoints);
fgm_float * MPC_get_input(void);
fgm_float * MPC_ctr(int restart);
#pragma FUNC_NEVER_RETURNS(MPC_ctr_worker)
void MPC_ctr_worker(volatile fgm_float* sofb_setpoints);

#endif /* MPC_MPC_CTR_H_ */
