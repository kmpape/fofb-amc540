#include <string.h>
#include <math.h>

#include "utils/libQDMA.h"
#include "utils/reference.h"
#include "utils/reference_signal.h"

#pragma SET_DATA_SECTION(".ref_local")
int REF_counter_signal;
int REF_counter_bpm;
int REF_counter_pause;
int REF_counter_last_bpm;
#pragma SET_DATA_SECTION()


void REF_initialize(void)
{
    REF_counter_signal = 0;
    REF_counter_bpm = 0;
    REF_counter_pause = 0;
    REF_counter_last_bpm = 0;
}

void REF_add_ref_input(LIBQDMA_ARR_TYPE * in_out_vec)
{
    REF_counter_last_bpm = REF_counter_bpm;
    if (REF_counter_bpm == REF_MAX_BPM) {
        return;
    }

    if (REF_counter_pause < REF_PAUSE_LEN) {
        REF_counter_pause++;
    } else {
        if (REF_counter_signal < REF_SIGNAL_LEN) {
            in_out_vec[REF_counter_bpm] = in_out_vec[REF_counter_bpm] - ref_signal_nm[REF_counter_signal];
            REF_counter_signal++;
            if (REF_counter_signal == REF_SIGNAL_LEN) {
                REF_counter_signal = 0;
                REF_counter_pause = 0;
                REF_counter_bpm++;
            }
        }
    }
}

void REF_add_ref_output(LIBQDMA_ARR_TYPE * in_out_vec)
{
    if (REF_counter_last_bpm == REF_MAX_BPM) {
        return;
    }
    if ((REF_counter_pause < REF_PAUSE_LEN) && (REF_counter_last_bpm == REF_counter_bpm)) {
        in_out_vec[REF_OUTPUT_IND] = -1;
    } else {
        in_out_vec[REF_OUTPUT_IND] = REF_counter_last_bpm;
    }
}

int REF_ref_is_running(void)
{
    if (REF_counter_bpm < REF_MAX_BPM) {
        return 1;  // Note that it will return 1 after initialization
    } else {
        return 0;
    }
}



