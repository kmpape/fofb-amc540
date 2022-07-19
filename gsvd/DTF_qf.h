#ifndef DTF_QF_H_
#define DTF_QF_H_

#include "fofb_config.h"
#define DTF_qf_UNIT_TEST    (0)
#define DTF_qf_MAXVAL    (4.9900000000)
/*
 * Hard-coded vector-wise (length K=32) filter with * N+1 (N=2) output and M+1 (M=2) input taps: * 
 * y0 = cy1*y1+...+cyN*yN+cu0*u0+...+cuM*uM,
 * 
 * where cyi and cui are scalar filter coefficients and
 * yi and ui are arrays of length K.
 * 
 */
#define DTF_qf_LEN (32)

#define DTF_qf_XDIR (XDIR)

typedef double DTF_qf_ARR_TYPE;


/*
 * DTF_qf_ARR_TYPE* DTF_qf_get_u0_ptr(void);
 * Returns pointer to input vector u0. Input data needs to
 * be written to locations 0 ... K to which get_u0_ptr is
 * pointing to.
 * Note: Pointer is changed after every filter call.
 */
DTF_qf_ARR_TYPE* DTF_qf_get_u0_ptr(void);


/*
 * DTF_qf_ARR_TYPE* DTF_qf_get_y0_ptr(void);
 * Returns pointer to output vector y0. Output data needs to
 * be read from locations 0 ... K to which get_y0_ptr is
 * pointing to.
 * Note: Pointer is changed after every filter call.
 */
DTF_qf_ARR_TYPE* DTF_qf_get_y0_ptr(void);


/*
 * void void DTF_qf_execute(void);
 * 
Executes filter. Should be used as follows: * 1.) Retrieve input pointer: input_data = get_u0_ptr()
 * 2.) Write input data to input_data[0] ... input_data[N]
 * 3.) Call DT_FILTER_execute
 * 4.) Retrieve output pointer: output_data = get_y0_ptr()
 */
void DTF_qf_execute(void);


/*
 * void DTF_qf_init(void);
 */
void DTF_qf_init(void);

#define DTF_qf_min(X, Y)  ((X) < (Y) ? (X) : (Y))
#define DTF_qf_max(X, Y)  ((X) > (Y) ? (X) : (Y))
#define DTF_qf_sat(X, Y)  (DTF_qf_min(DTF_qf_max(X,-Y),Y))


#endif // DTF_QF_H_
