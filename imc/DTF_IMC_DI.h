#ifndef DTF_IMC_DI_H_
#define DTF_IMC_DI_H_

#include "fofb_config.h"
#define DTF_IMC_DI_UNIT_TEST    (0)
#define DTF_IMC_DI_MAXVAL    (4.9900000000)
/*
 * Hard-coded vector-wise (length K=171) filter with * N+1 (N=2) output and M+1 (M=11) input taps: * 
 * y0 = cy1*y1+...+cyN*yN+cu0*u0+...+cuM*uM,
 * 
 * where cyi and cui are scalar filter coefficients and
 * yi and ui are arrays of length K.
 * 
 */
#define DTF_IMC_DI_LEN (171)

#define DTF_IMC_DI_XDIR (XDIR)

typedef double DTF_IMC_DI_ARR_TYPE;


/*
 * DTF_IMC_DI_ARR_TYPE* DTF_IMC_DI_get_u0_ptr(void);
 * Returns pointer to input vector u0. Input data needs to
 * be written to locations 0 ... K to which get_u0_ptr is
 * pointing to.
 * Note: Pointer is changed after every filter call.
 */
DTF_IMC_DI_ARR_TYPE* DTF_IMC_DI_get_u0_ptr(void);


/*
 * DTF_IMC_DI_ARR_TYPE* DTF_IMC_DI_get_y0_ptr(void);
 * Returns pointer to output vector y0. Output data needs to
 * be read from locations 0 ... K to which get_y0_ptr is
 * pointing to.
 * Note: Pointer is changed after every filter call.
 */
DTF_IMC_DI_ARR_TYPE* DTF_IMC_DI_get_y0_ptr(void);


/*
 * void void DTF_IMC_DI_execute(void);
 * 
Executes filter. Should be used as follows: * 1.) Retrieve input pointer: input_data = get_u0_ptr()
 * 2.) Write input data to input_data[0] ... input_data[N]
 * 3.) Call DT_FILTER_execute
 * 4.) Retrieve output pointer: output_data = get_y0_ptr()
 */
void DTF_IMC_DI_execute(void);


/*
 * void DTF_IMC_DI_init(void);
 */
void DTF_IMC_DI_init(void);

#define DTF_IMC_DI_min(X, Y)  ((X) < (Y) ? (X) : (Y))
#define DTF_IMC_DI_max(X, Y)  ((X) > (Y) ? (X) : (Y))
#define DTF_IMC_DI_sat(X, Y)  (DTF_IMC_DI_min(DTF_IMC_DI_max(X,-Y),Y))


#endif // DTF_IMC_DI_H_
