#ifndef DTF_PMCF_H_
#define DTF_PMCF_H_

#include "fofb_config.h"
#define DTF_pmcf_UNIT_TEST    (1)
/*
 * Hard-coded vector-wise (length K=16) filter with * N+1 (N=3) output and M+1 (M=3) input taps: * 
 * y0 = cy1*y1+...+cyN*yN+cu0*u0+...+cuM*uM,
 * 
 * where cyi and cui are scalar filter coefficients and
 * yi and ui are arrays of length K.
 * 
 */
#define DTF_pmcf_LEN (16)

#define DTF_pmcf_LIMIT (INTEGRATOR_LIMIT)

#define DTF_pmcf_XDIR (XDIR)

typedef float DTF_pmcf_ARR_TYPE;


/*
 * DTF_pmcf_ARR_TYPE* DTF_pmcf_get_u0_ptr(void);
 * Returns pointer to input vector u0. Input data needs to
 * be written to locations 0 ... K to which get_u0_ptr is
 * pointing to.
 * Note: Pointer is changed after every filter call.
 */
DTF_pmcf_ARR_TYPE* DTF_pmcf_get_u0_ptr(void);


/*
 * DTF_pmcf_ARR_TYPE* DTF_pmcf_get_y0_ptr(void);
 * Returns pointer to output vector y0. Output data needs to
 * be read from locations 0 ... K to which get_y0_ptr is
 * pointing to.
 * Note: Pointer is changed after every filter call.
 */
DTF_pmcf_ARR_TYPE* DTF_pmcf_get_y0_ptr(void);


/*
 * void void DTF_pmcf_execute(void);
 * 
Executes filter. Should be used as follows: * 1.) Retrieve input pointer: input_data = get_u0_ptr()
 * 2.) Write input data to input_data[0] ... input_data[N]
 * 3.) Call DT_FILTER_execute
 * 4.) Retrieve output pointer: output_data = get_y0_ptr()
 */
void DTF_pmcf_execute(void);


/*
 * void DTF_pmcf_init(void);
 */
void DTF_pmcf_init(void);
#if (DTF_pmcf_UNIT_TEST == 1)
int DTF_pmcf_unit_test(void);
#endif

#define DTF_pmcf_min(X, Y)  ((X) < (Y) ? (X) : (Y))
#define DTF_pmcf_max(X, Y)  ((X) > (Y) ? (X) : (Y))
#define DTF_pmcf_sat(X, Y)  (DTF_pmcf_min(DTF_pmcf_max(X,-Y),Y))


#endif // DTF_PMCF_H_
