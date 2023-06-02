#ifndef REFERENCE_H_
#define REFERENCE_H_

#include "fofb_config.h"
#include "utils/libQDMA.h"

#define REF_OUTPUT_IND              (173) // outputs ID of BPM affected by ref on REF_OUTPUT_IND
#define REF_MAX_BPM                 (TOT_NUM_BPM)

void REF_initialize(void);
void REF_add_ref_input(LIBQDMA_ARR_TYPE * in_out_vec);
void REF_add_ref_output(LIBQDMA_ARR_TYPE * in_out_vec);
int REF_ref_is_running(void);

#endif /* REFERENCE_H_ */
