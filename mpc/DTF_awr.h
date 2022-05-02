#ifndef DTF_AWR_H_
#define DTF_AWR_H_

#include "fofb_config.h"
#define DTF_awr_UNIT_TEST    (0)
#define DTF_awr_MAXVAL    (100000000000000000000.0000000000)
/*
 * Hard-coded vector-wise (length K=32) filter with * N+1 (N=1) output and M+1 (M=1) input taps: * 
 * y0 = cy1*y1+...+cyN*yN+cu0*u0+...+cuM*uM,
 * 
 * where cyi and cui are scalar filter coefficients and
 * yi and ui are arrays of length K.
 * 
 */
#define DTF_awr_LEN (32)

#define DTF_awr_XDIR (XDIR)

typedef float DTF_awr_ARR_TYPE;


/*
 * DTF_awr_ARR_TYPE* DTF_awr_get_u0_ptr(void);
 * Returns pointer to input vector u0. Input data needs to
 * be written to locations 0 ... K to which get_u0_ptr is
 * pointing to.
 * Note: Pointer is changed after every filter call.
 */
DTF_awr_ARR_TYPE* DTF_awr_get_u0_ptr(void);


/*
 * DTF_awr_ARR_TYPE* DTF_awr_get_y0_ptr(void);
 * Returns pointer to output vector y0. Output data needs to
 * be read from locations 0 ... K to which get_y0_ptr is
 * pointing to.
 * Note: Pointer is changed after every filter call.
 */
DTF_awr_ARR_TYPE* DTF_awr_get_y0_ptr(void);


/*
 * void void DTF_awr_execute(void);
 * 
Executes filter. Should be used as follows: * 1.) Retrieve input pointer: input_data = get_u0_ptr()
 * 2.) Write input data to input_data[0] ... input_data[N]
 * 3.) Call DT_FILTER_execute
 * 4.) Retrieve output pointer: output_data = get_y0_ptr()
 */
void DTF_awr_execute(void);


/*
 * void DTF_awr_init(void);
 */
void DTF_awr_init(void);

#define DTF_awr_min(X, Y)  ((X) < (Y) ? (X) : (Y))
#define DTF_awr_max(X, Y)  ((X) > (Y) ? (X) : (Y))
#define DTF_awr_sat(X, Y)  (DTF_awr_min(DTF_awr_max(X,-Y),Y))


#endif // DTF_AWR_H_
