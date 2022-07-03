#include <string.h>
#include <stdio.h>

#ifdef SOC_C6678
#include <c6x.h>
#include <ti/csl/csl_chip.h>
#include <csl_cache.h>
#include <csl_cacheAux.h>
#endif // SOC_C6678

#include "utils/watchdog.h"
#include "utils/watchdog_data.h"

#define WD_ABS(X)  (((X) > 0) ? (X) : -(X))

#ifdef SOC_C6678
#pragma DATA_ALIGN(WD_setpoint_scaled_min,  2)
#pragma DATA_ALIGN(WD_setpoint_scaled_max,  2)
#pragma DATA_ALIGN(WD_beam_error,   2)
#pragma DATA_ALIGN(WD_sofb_error,   2)
#pragma DATA_ALIGN(WD_fofb_error,   2)
#pragma SET_DATA_SECTION(".watchdog_local")
#endif // SOC_C6678
int WD_setpoint_scaled_min[WD_LEN] = {0};
int WD_setpoint_scaled_max[WD_LEN] = {0};

uint16_t WD_beam_error[WD_LEN] = {0};
uint16_t WD_sofb_error[WD_LEN] = {0};
uint16_t WD_fofb_error[WD_LEN] = {0};

int WD_beam_err_num = 0;
int WD_sofb_err_num = 0;
int WD_fofb_err_num = 0;

#ifdef SOC_C6678
#pragma SET_DATA_SECTION()
#endif // SOC_C6678

#ifdef SOC_C6678
#pragma SET_DATA_SECTION(".shared")
#endif // SOC_C6678
char WD_error_msg[] =     "ERRORS: BEAM=%d (at %d)\tSOFB=%d (at %d)\tFOFB=%d (at %d)\n ";
#ifdef SOC_C6678
#pragma SET_DATA_SECTION()
#endif // SOC_C6678

void watchdog_initialize(void)
{
    int i;

    WD_beam_err_num = 0;
    WD_sofb_err_num = 0;
    WD_fofb_err_num = 0;

    memset((void *)WD_setpoint_scaled_min, 0, WD_LEN*sizeof(float));
    memset((void *)WD_setpoint_scaled_max, 0, WD_LEN*sizeof(float));

    memset((void *)WD_beam_error, 0, WD_LEN*sizeof(uint16_t));
    memset((void *)WD_sofb_error, 0, WD_LEN*sizeof(uint16_t));
    memset((void *)WD_fofb_error, 0, WD_LEN*sizeof(uint16_t));

    // Must be re-initialized using watchdog_read_SOFB_A()
    for (i=0; i<WD_LEN; i++) {
        WD_setpoint_scaled_max[i] = HARDLIMITS_SCALED[i];
        WD_setpoint_scaled_min[i] = -HARDLIMITS_SCALED[i];
    }
}

void watchdog_read_SOFB_mA(float *sofb_mA)
{
    int i;
    for (i=0; i<WD_LEN-1; i++) {
        int sofb_scaled = (int)(sofb_mA[i] * WD_SETP_mA_SCALING);
        WD_setpoint_scaled_max[i] = HARDLIMITS_SCALED[i] - sofb_scaled;
        WD_setpoint_scaled_min[i] = -HARDLIMITS_SCALED[i] - sofb_scaled;

        if ((WD_setpoint_scaled_max[i] <= WD_setpoint_scaled_min[i]) ||
            (WD_setpoint_scaled_max[i] < WD_SOFB_MIN_MARGIN_SCALED) ||
            (WD_setpoint_scaled_min[i] > -WD_SOFB_MIN_MARGIN_SCALED) ||
            (WD_setpoint_scaled_max[i] <= 0) ||
            (WD_setpoint_scaled_min[i] >= 0)) {
                WD_sofb_error[i]++;
                if (WD_sofb_error[i] >= WD_SOFB_MAX_TRIP_COUNT)
                    WD_sofb_err_num++;
        }
    }
}

void watch_beam(int *beam_in)
{
    int i;
    for (i=0; i<WD_LEN; i++) {
        if ((WD_ABS(beam_in[i]) >= WD_BEAM_LIMIT_NM_INT) &&
                ((i != 75) && (i != 78))) { // TODO: HARDCODED DISABLED BPMs
            WD_beam_error[i]++;
            if (WD_beam_error[i] >= WD_BEAM_MAX_TRIP_COUNT)
                WD_beam_err_num++;
        } else {
            WD_beam_error[i] = 0;
        }
    }
}

void watch_setpoints(int *setp_out)
{
    int i;
    for (i=0; i<WD_LEN-1; i++) {
        if ((-setp_out[i] >= WD_setpoint_scaled_max[i]) ||
                (-setp_out[i] <= WD_setpoint_scaled_min[i])) {
                WD_fofb_error[i]++;
                if (WD_fofb_error[i] >= WD_FOFB_MAX_TRIP_COUNT)
                    WD_fofb_err_num++;
        } else {
            WD_fofb_error[i] = 0;
        }
    }
}

int check_watchdog(void)
{
    return ((WD_beam_err_num > 0) || (WD_sofb_err_num > 0) || (WD_fofb_err_num > 0));
}

void print_watchdog_msg(void)
{
    int i;
    int first_beam_err_ind = -1;
    int first_sofb_err_ind = -1;
    int first_fofb_err_ind = -1;

    for (i=0; i<WD_LEN; i++) {
        if (WD_beam_error[i] > 0) {
            first_beam_err_ind = i;
            break;
        }
    }
    for (i=0; i<WD_LEN-1; i++) {
        if (WD_sofb_error[i] > 0) {
            first_sofb_err_ind = i;
            break;
        }
    }
    for (i=0; i<WD_LEN-1; i++) {
        if (WD_fofb_error[i] > 0) {
            first_fofb_err_ind = i;
            break;
        }
    }

    // "ERRORS: BEAM=%d (at %d)\tSOFB=%d (at %d)\tFOFB=%d (at %d)\n "
    printf(WD_error_msg, WD_beam_err_num, first_beam_err_ind,
            WD_sofb_err_num, first_sofb_err_ind, WD_fofb_err_num, first_fofb_err_ind);
}

void test_watchdog(void)
{
    int i,j;
    int test_array[WD_LEN] = {0};
    float test_sofb[WD_LEN] = {0.0};

    const int beam_fail_max = WD_BEAM_LIMIT_NM_INT+1;
    const int beam_fail_min = -WD_BEAM_LIMIT_NM_INT-1;

    watchdog_read_SOFB_mA(test_sofb);
    if (check_watchdog() == 0) {
        printf("Watchdog SOFB test passed\n");
    } else {
        printf("Watchdog SOFB test failed\n");
    }

    int fail = 0;
    for (i=0; i<WD_LEN; i++) {
        watchdog_initialize();
        test_array[i] = beam_fail_max;
        for (j=0; j<WD_BEAM_MAX_TRIP_COUNT; j++)
            watch_beam(test_array);
        if (check_watchdog() == 0)
            fail = 1;

        watchdog_initialize();
        test_array[i] = beam_fail_min;
        for (j=0; j<WD_BEAM_MAX_TRIP_COUNT; j++)
            watch_beam(test_array);
        if (check_watchdog() == 0)
            fail = 1;
    }
    if (fail == 1) {
        printf("Watchdog BEAM test failed\n");
    } else {
        printf("Watchdog BEAM test passed\n");
    }

    fail = 0;
    for (i=0; i<WD_LEN; i++) {
        watchdog_initialize();
        test_array[i] = WD_setpoint_scaled_max[i]+1;
        for (j=0; j<WD_FOFB_MAX_TRIP_COUNT; j++)
            watch_setpoints(test_array);
        if (check_watchdog() == 0)
            fail = 1;

        watchdog_initialize();
        test_array[i] = WD_setpoint_scaled_min[i]-1;
        for (j=0; j<WD_FOFB_MAX_TRIP_COUNT; j++)
            watch_setpoints(test_array);
        if (check_watchdog() == 0)
            fail = 1;
    }
    if (fail == 1) {
        printf("Watchdog SETPOINT test failed\n");
    } else {
        printf("Watchdog SETPOINT test passed\n");
    }
    watchdog_initialize();
}


