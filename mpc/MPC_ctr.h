#ifndef MPC_MPC_CTR_H_
#define MPC_MPC_CTR_H_

#include "mpc/fast_gradient_method.h"

#define MPC_NU (172)
#define MPC_NY (171)

void MPC_initialize(void);
void MPC_initialize_worker(volatile int selfId);
fgm_float * MPC_get_input(void);
fgm_float * MPC_ctr(int restart);
#pragma FUNC_NEVER_RETURNS(MPC_ctr_worker)
void MPC_ctr_worker(void);

#endif /* MPC_MPC_CTR_H_ */
