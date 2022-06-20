#include <string.h>
#include <stdio.h>

#ifdef SOC_C6678
#include <c6x.h>
#include <ti/csl/csl_chip.h>
#include <csl_cache.h>
#include <csl_cacheAux.h>
#endif // SOC_C6678

#include "mpc/MPC_watchdog.h"
#include "mpc/MPC_watchdog_data.h"
#include "mpc/fast_gradient_method.h"

#define WD_ABS(X)  (((X) > 0) ? (X) : -(X))

#ifdef SOC_C6678
#pragma DATA_ALIGN(WD_sofb_values,  FGM_MPC_ARRAY_ALIGN)
#pragma DATA_ALIGN(WD_beam_error,   FGM_MPC_ARRAY_ALIGN)
#pragma DATA_ALIGN(WD_sofb_error,   FGM_MPC_ARRAY_ALIGN)
#pragma DATA_ALIGN(WD_fofb_error,   FGM_MPC_ARRAY_ALIGN)
#pragma SET_DATA_SECTION(".mpc_watchdog_local")
#endif // SOC_C6678
float WD_sofb_values[FGM_MPC_DIM] = {0.0};
int WD_beam_error[FGM_MPC_DIM] = {0};
int WD_sofb_error[FGM_MPC_DIM] = {0};
int WD_fofb_error[FGM_MPC_DIM] = {0};
int WD_beam_err_num = 0;
int WD_sofb_err_num = 0;
int WD_fofb_err_num = 0;
#ifdef SOC_C6678
#pragma SET_DATA_SECTION()
#endif // SOC_C6678

#ifdef SOC_C6678
#pragma SET_DATA_SECTION(".mpc_shared")
#endif // SOC_C6678
char WD_error_msg[] =     "ERRORS: BEAM=%d (at %d)\tSOFB=%d (at %d)\tFOFB=%d (at %d)\n ";
char WD_error_msg_tmp[] = "00000000000000000000000000000000000000000000000000000000000 ";
#ifdef SOC_C6678
#pragma SET_DATA_SECTION()
#endif // SOC_C6678

void MPC_watchdog_initialize(void)
{
    WD_beam_err_num = 0;
    WD_sofb_err_num = 0;
    WD_fofb_err_num = 0;
    memset((void *)WD_sofb_values, 0.0, FGM_MPC_DIM*sizeof(float));
    memset((void *)WD_beam_error, 0, FGM_MPC_DIM*sizeof(int));
    memset((void *)WD_sofb_error, 0, FGM_MPC_DIM*sizeof(int));
    memset((void *)WD_fofb_error, 0, FGM_MPC_DIM*sizeof(int));
}

int MPC_check_watchdog(void)
{
    return ((WD_beam_err_num > 0) || (WD_sofb_err_num > 0) || (WD_fofb_err_num > 0));
}

void MPC_print_watchdog_msg(void)
{
    int i;
    int first_beam_err_ind = -1;
    int first_sofb_err_ind = -1;
    int first_fofb_err_ind = -1;

    for (i=0; i<FGM_MPC_DIM; i++) {
        if (WD_beam_error[i] > 0) {
            first_beam_err_ind = i;
            break;
        }
    }
    for (i=0; i<FGM_MPC_DIM; i++) {
        if (WD_sofb_error[i] > 0) {
            first_sofb_err_ind = i;
            break;
        }
    }
    for (i=0; i<FGM_MPC_DIM; i++) {
        if (WD_fofb_error[i] > 0) {
            first_fofb_err_ind = i;
            break;
        }
    }

    // "ERRORS: BEAM=%d (at %d)\tSOFB=%d (at %d)\tFOFB=%d (at %d)\n "
    printf(WD_error_msg, WD_beam_err_num, first_beam_err_ind,
            WD_sofb_err_num, first_sofb_err_ind, WD_fofb_err_num, first_fofb_err_ind);
}

void MPC_watch_beam_mum(float beam_mum, int index)
{
        if (WD_ABS(beam_mum) >= WD_BEAM_LIMIT_MUM) {
            WD_beam_error[index]++;
            if (WD_beam_error[index] >= WD_BEAM_MAX_TRIP_COUNT)
                WD_beam_err_num++;
        }
}

void MPC_watch_beam_nm(float beam_nm, int index)
{
        if (WD_ABS(beam_nm) >= WD_BEAM_LIMIT_NM) {
            WD_beam_error[index]++;
            if (WD_beam_error[index] >= WD_BEAM_MAX_TRIP_COUNT)
                WD_beam_err_num++;
        }
}

void MPC_watch_sofb_mA(float sofb_mA, int index)
{
    WD_sofb_values[index] = sofb_mA;
    float upper_lim = WD_hardlimits_mA[index] - sofb_mA;
    float lower_lim = -WD_hardlimits_mA[index] - sofb_mA;

    if ((upper_lim <= lower_lim) ||
            (upper_lim < WD_SOFB_MIN_MARGIN_MA) || (lower_lim > -WD_SOFB_MIN_MARGIN_MA)) {
        WD_sofb_error[index]++;
        if (WD_sofb_error[index] >= WD_SOFB_MAX_TRIP_COUNT)
            WD_sofb_err_num++;
    }
}

void MPC_watch_fofb_mA(float fofb_mA, int index)
{

    if (WD_ABS(WD_sofb_values[index] + fofb_mA) >= WD_hardlimits_mA[index]) {
        WD_fofb_error[index]++;
        if (WD_fofb_error[index] >= WD_FOFB_MAX_TRIP_COUNT)
            WD_fofb_err_num++;
    }
}


