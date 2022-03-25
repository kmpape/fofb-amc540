/****************************************************************************/
/*  IMC_mc_only.cmd                                                         */
/*  Author: Idris Kempf                                                     */
/*                                                                          */
/*  Description: Linker command file for custom IPC and IMC libraries       */
/*                                                                          */
/****************************************************************************/

#include "fofb_config.h"

-stack 0xAFA00
-heap  0xAFA00

SECTIONS
{
	/* TI */
	sharedL2 	> MSMCSRAM
	systemHeap 	> MSMCSRAM
	.sysmem 	> MSMCSRAM
	.args 		> MSMCSRAM
	.cio 		> MSMCSRAM
	.far 		> MSMCSRAM
	.rodata 	> MSMCSRAM
	.neardata 	> MSMCSRAM
	.cppi 		> MSMCSRAM
	.init_array > MSMCSRAM
	.qmss 		> MSMCSRAM
	.cinit 		> MSMCSRAM
	.bss 		> MSMCSRAM
	.const 		> MSMCSRAM
	.text 		> MSMCSRAM
	.code 		> MSMCSRAM
	.switch 	> MSMCSRAM
	.data 		> MSMCSRAM
	.fardata 	> MSMCSRAM
	.args 		> MSMCSRAM
	.cio 		> MSMCSRAM
	.vecs 		> MSMCSRAM
	.far:taskStackSection > L2SRAM
	.stack 		> L2SRAM // must be in L2 for multi-core
	.fardata:benchmarking > DDR3

    /* Various */
    .init_data				> DDR3
    .shared_data			> MSMCSRAM
	.local_data				> L2SRAM

	/* IPC Sections */
	.ipc_nocache_section	> MSMCSRAM_NC_VIRT
	.ipc_local_data			> L2SRAM type=NOINIT
    .ipc_shared_section		> MSMCSRAM

#if (IMC_CONTROL == 1)
    .imc_DI					> L2SRAM
    .imc_di_shared			> MSMCSRAM
    .imc_di_local			> L2SRAM
    .imc_DI_init			> DDR3
    .imc_UNIT_TEST			> DDR3
#endif

#if (GSVD_CONTROL == 1)
    .gsvd_gs				> L2SRAM
    .gsvd_gf				> L2SRAM
    .gsvd_qs				> L2SRAM
    .gsvd_qf				> L2SRAM
    .gsvd_pmcs				> L2SRAM
    .gsvd_pmcf				> L2SRAM
    .gsvd_shared			> MSMCSRAM
    .gsvd_local				> L2SRAM
    .gsvd_init				> DDR3
    .gsvd_unit_test			> DDR3
#endif

#if (MPC_CONTROL == 1)
	.mpc_init				> DDR3
	.mpc_shared				> L2SRAM
    .fgm_local_data  		> L2SRAM
    .fgm_shared_data 		> MSMCSRAM
    .fgm_local_code  		> L2SRAM
    .obs_shared_data 		> MSMCSRAM type=NOINIT
    .obs_shared_const 		> MSMCSRAM
    .obs_local_data  		> L2SRAM type=NOINIT
#endif

	/* AMC540 */
    platform_lib			> DDR3
    .dstBufSec				> MSMCSRAM
}
