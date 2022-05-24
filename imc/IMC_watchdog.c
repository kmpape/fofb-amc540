#include <string.h>
#include <stdio.h>

#ifdef SOC_C6678
#include <c6x.h>
#include <ti/csl/csl_chip.h>
#include <csl_cache.h>
#include <csl_cacheAux.h>
#endif // SOC_C6678

#include "imc/IMC_watchdog.h"
#include "imc/IMC_watchdog_data.h"
#include "imc/IMC_DI_ctr.h"

#define WD_IMC_ABS(X)  (((X) > 0) ? (X) : -(X))

#ifdef SOC_C6678
#pragma DATA_ALIGN(WD_IMC_sofb_values,  2)
#pragma DATA_ALIGN(WD_IMC_beam_error,   2)
#pragma DATA_ALIGN(WD_IMC_sofb_error,   2)
#pragma DATA_ALIGN(WD_IMC_fofb_error,   2)
#pragma SET_DATA_SECTION(".IMC_watchdog_local")
#endif // SOC_C6678
float WD_IMC_sofb_values[WD_IMC_LEN] = {0.0};
uint16_t WD_IMC_beam_error[WD_IMC_LEN] = {0};
uint16_t WD_IMC_sofb_error[WD_IMC_LEN] = {0};
uint16_t WD_IMC_fofb_error[WD_IMC_LEN] = {0};
int WD_IMC_beam_err_num = 0;
int WD_IMC_sofb_err_num = 0;
int WD_IMC_fofb_err_num = 0;
#ifdef SOC_C6678
#pragma SET_DATA_SECTION()
#endif // SOC_C6678

#ifdef SOC_C6678
#pragma SET_DATA_SECTION(".IMC_shared")
#endif // SOC_C6678
char WD_IMC_error_msg[] =     "ERRORS: BEAM=%d (at %d)\tSOFB=%d (at %d)\tFOFB=%d (at %d)\n ";
char WD_IMC_error_msg_tmp[] = "00000000000000000000000000000000000000000000000000000000000 ";
#ifdef SOC_C6678
#pragma SET_DATA_SECTION()
#endif // SOC_C6678

void IMC_watchdog_initialize(void)
{
    WD_IMC_beam_err_num = 0;
    WD_IMC_sofb_err_num = 0;
    WD_IMC_fofb_err_num = 0;
    memset((void *)WD_IMC_sofb_values, 0, WD_IMC_LEN*sizeof(float));
    memset((void *)WD_IMC_beam_error, 0, WD_IMC_LEN*sizeof(uint16_t));
    memset((void *)WD_IMC_sofb_error, 0, WD_IMC_LEN*sizeof(uint16_t));
    memset((void *)WD_IMC_fofb_error, 0, WD_IMC_LEN*sizeof(uint16_t));
}

int IMC_check_watchdog(void)
{
    return ((WD_IMC_beam_err_num > 0) || (WD_IMC_sofb_err_num > 0) || (WD_IMC_fofb_err_num > 0));
}

char* IMC_get_watchdog_msg(void)
{
    int i;
    int first_beam_err_ind = -1;
    int first_sofb_err_ind = -1;
    int first_fofb_err_ind = -1;
    for (i=0; i<WD_IMC_LEN; i++) {
        if ((WD_IMC_beam_error[i] > 0) && (first_beam_err_ind < 0)) first_beam_err_ind = i;
        if ((WD_IMC_sofb_error[i] > 0) && (first_sofb_err_ind < 0)) first_sofb_err_ind = i;
        if ((WD_IMC_fofb_error[i] > 0) && (first_fofb_err_ind < 0)) first_fofb_err_ind = i;
    }

    // "ERRORS: BEAM=%d (at %d)\tSOFB=%d (at %d)\tFOFB=%d (at %d)\n "
    sprintf(WD_IMC_error_msg_tmp, WD_IMC_error_msg, WD_IMC_beam_err_num, first_beam_err_ind,
            WD_IMC_sofb_err_num, first_sofb_err_ind, WD_IMC_fofb_err_num, first_fofb_err_ind);

    return WD_IMC_error_msg_tmp;
}

void IMC_watch_beam_mum(float beam_mum, int index)
{
        if (WD_IMC_ABS(beam_mum) >= WD_IMC_BEAM_LIMIT_MUM) {
            WD_IMC_beam_error[index]++;
            if (WD_IMC_beam_error[index] >= WD_IMC_BEAM_MAX_TRIP_COUNT)
                WD_IMC_beam_err_num++;
        }
}

void IMC_watch_beam_nm(float beam_nm, int index)
{
        if (WD_IMC_ABS(beam_nm) >= WD_IMC_BEAM_LIMIT_NM) {
            WD_IMC_beam_error[index]++;
            if (WD_IMC_beam_error[index] >= WD_IMC_BEAM_MAX_TRIP_COUNT)
                WD_IMC_beam_err_num++;
        }
}

void IMC_watch_sofb_A(float sofb_A, int index)
{
    float upper_lim = WD_IMC_hardlimits_A[index] - sofb_A;
    float lower_lim = -WD_IMC_hardlimits_A[index] - sofb_A;

    if ((upper_lim <= lower_lim) ||
            (upper_lim < WD_IMC_SOFB_MIN_MARGIN_A) || (lower_lim > -WD_IMC_SOFB_MIN_MARGIN_A)) {
        WD_IMC_sofb_error[index]++;
        if (WD_IMC_sofb_error[index] >= WD_IMC_SOFB_MAX_TRIP_COUNT)
            WD_IMC_sofb_err_num++;
    }
}

void IMC_watch_fofb_A(float fofb_A, int index)
{

    if (WD_IMC_ABS(fofb_A) >= WD_IMC_hardlimits_A[index]) {
        WD_IMC_fofb_error[index]++;
        if (WD_IMC_fofb_error[index] >= WD_IMC_FOFB_MAX_TRIP_COUNT)
            WD_IMC_fofb_err_num++;
    }
}


