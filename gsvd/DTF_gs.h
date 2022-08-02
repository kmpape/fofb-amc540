#ifndef DTF_GS_H_
#define DTF_GS_H_

#include "fofb_config.h"
#define DTF_gs_UNIT_TEST    (0)
#define DTF_gs_MAXVAL    (100000000000000000000.0000000000)
/*
 * Hard-coded vector-wise (length K=32) filter with * N+1 (N=10) output and M+1 (M=1) input taps: * 
 * y0 = cy1*y1+...+cyN*yN+cu0*u0+...+cuM*uM,
 * 
 * where cyi and cui are scalar filter coefficients and
 * yi and ui are arrays of length K.
 * 
 */
#define DTF_gs_LEN (32)

#define DTF_gs_XDIR (XDIR)

typedef double DTF_gs_ARR_TYPE;


/*
 * DTF_gs_ARR_TYPE* DTF_gs_get_u0_ptr(void);
 * Returns pointer to input vector u0. Input data needs to
 * be written to locations 0 ... K to which get_u0_ptr is
 * pointing to.
 * Note: Pointer is changed after every filter call.
 */
DTF_gs_ARR_TYPE* DTF_gs_get_u0_ptr(void);


/*
 * DTF_gs_ARR_TYPE* DTF_gs_get_y0_ptr(void);
 * Returns pointer to output vector y0. Output data needs to
 * be read from locations 0 ... K to which get_y0_ptr is
 * pointing to.
 * Note: Pointer is changed after every filter call.
 */
DTF_gs_ARR_TYPE* DTF_gs_get_y0_ptr(void);


/*
 * void void DTF_gs_execute(void);
 * 
Executes filter. Should be used as follows: * 1.) Retrieve input pointer: input_data = get_u0_ptr()
 * 2.) Write input data to input_data[0] ... input_data[N]
 * 3.) Call DT_FILTER_execute
 * 4.) Retrieve output pointer: output_data = get_y0_ptr()
 */
void DTF_gs_execute(void);


/*
 * void DTF_gs_init(void);
 */
void DTF_gs_init(void);

#define DTF_gs_min(X, Y)  ((X) < (Y) ? (X) : (Y))
#define DTF_gs_max(X, Y)  ((X) > (Y) ? (X) : (Y))
#define DTF_gs_sat(X, Y)  (DTF_gs_min(DTF_gs_max(X,-Y),Y))


#endif // DTF_GS_H_
