#ifndef MPC_MPC_CTR_H_
#define MPC_MPC_CTR_H_

#include "mpc/MPC_storage_ring_config.h"
#include "mpc/fast_gradient_method.h"

#define MPC_NU (MPC_NU_)
#define MPC_NY (MPC_NY_)

void MPC_initialize(void);
fgm_float * MPC_get_input(void);
fgm_float * MPC_ctr(int restart);

#endif /* MPC_MPC_CTR_H_ */
