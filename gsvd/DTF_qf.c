#include <stdio.h>
#include "DTF_qf.h"

#ifdef SOC_C6678
#include <c6x.h>
#endif
#if (DTF_qf_UNIT_TEST == 1)
#include "DTF_qf_UNIT_TEST.h"
#endif

/* Arrays */
#ifdef SOC_C6678
#pragma DATA_ALIGN(DTF_qf_y0, 64)
#pragma DATA_ALIGN(DTF_qf_y1, 64)
#pragma DATA_ALIGN(DTF_qf_y2, 64)
#pragma DATA_ALIGN(DTF_qf_u0, 64)
#pragma DATA_ALIGN(DTF_qf_u1, 64)
#pragma DATA_ALIGN(DTF_qf_u2, 64)
#pragma SET_DATA_SECTION(".gsvd_qf")
#endif // SOC_C6678
DTF_qf_ARR_TYPE DTF_qf_y0[DTF_qf_LEN] = {(DTF_qf_ARR_TYPE)0.0};
DTF_qf_ARR_TYPE DTF_qf_y1[DTF_qf_LEN] = {(DTF_qf_ARR_TYPE)0.0};
DTF_qf_ARR_TYPE DTF_qf_y2[DTF_qf_LEN] = {(DTF_qf_ARR_TYPE)0.0};
DTF_qf_ARR_TYPE DTF_qf_u0[DTF_qf_LEN] = {(DTF_qf_ARR_TYPE)0.0};
DTF_qf_ARR_TYPE DTF_qf_u1[DTF_qf_LEN] = {(DTF_qf_ARR_TYPE)0.0};
DTF_qf_ARR_TYPE DTF_qf_u2[DTF_qf_LEN] = {(DTF_qf_ARR_TYPE)0.0};
#ifdef SOC_C6678
#pragma SET_DATA_SECTION()
#endif // SOC_C6678


/* Pointers */
#ifdef SOC_C6678
#pragma SET_DATA_SECTION(".gsvd_qf")
#endif // SOC_C6678
DTF_qf_ARR_TYPE *DTF_qf_y0_ptr = DTF_qf_y0;
DTF_qf_ARR_TYPE *DTF_qf_y1_ptr = DTF_qf_y1;
DTF_qf_ARR_TYPE *DTF_qf_y2_ptr = DTF_qf_y2;
DTF_qf_ARR_TYPE *DTF_qf_u0_ptr = DTF_qf_u0;
DTF_qf_ARR_TYPE *DTF_qf_u1_ptr = DTF_qf_u1;
DTF_qf_ARR_TYPE *DTF_qf_u2_ptr = DTF_qf_u2;
#ifdef SOC_C6678
#pragma SET_DATA_SECTION()
#endif // SOC_C6678


/* Coefficients */
#ifdef SOC_C6678
#pragma SET_DATA_SECTION(".gsvd_qf")
#endif // SOC_C6678
#if (DTF_qf_XDIR == 1)
DTF_qf_ARR_TYPE DTF_qf_cy1 = (DTF_qf_ARR_TYPE)1.8756478909229544;
DTF_qf_ARR_TYPE DTF_qf_cy2 = (DTF_qf_ARR_TYPE)-0.8763875375141412;
DTF_qf_ARR_TYPE DTF_qf_cu0 = (DTF_qf_ARR_TYPE)0.3800000000000001;
DTF_qf_ARR_TYPE DTF_qf_cu1 = (DTF_qf_ARR_TYPE)-0.6480312431573459;
DTF_qf_ARR_TYPE DTF_qf_cu2 = (DTF_qf_ARR_TYPE)0.2680312431573459;
#else
DTF_qf_ARR_TYPE DTF_qf_cy1 = (DTF_qf_ARR_TYPE)1.8756478909229544;
DTF_qf_ARR_TYPE DTF_qf_cy2 = (DTF_qf_ARR_TYPE)-0.8763875375141412;
DTF_qf_ARR_TYPE DTF_qf_cu0 = (DTF_qf_ARR_TYPE)0.2714285714285715;
DTF_qf_ARR_TYPE DTF_qf_cu1 = (DTF_qf_ARR_TYPE)-0.4309294210190751;
DTF_qf_ARR_TYPE DTF_qf_cu2 = (DTF_qf_ARR_TYPE)0.1595008495905037;
#endif // XDIR
#ifdef SOC_C6678
#pragma SET_DATA_SECTION()
#endif // SOC_C6678


DTF_qf_ARR_TYPE* DTF_qf_get_y0_ptr(void)
{
	return DTF_qf_y0_ptr;
}


DTF_qf_ARR_TYPE* DTF_qf_get_u0_ptr(void)
{
	return DTF_qf_u0_ptr;
}


void DTF_qf_swap_y(void)
{
	DTF_qf_ARR_TYPE* tmp_y2_ptr = DTF_qf_y2_ptr;
	DTF_qf_y2_ptr = DTF_qf_y1_ptr;
	DTF_qf_y1_ptr = DTF_qf_y0_ptr;
	DTF_qf_y0_ptr = tmp_y2_ptr;
}


void DTF_qf_swap_u(void)
{
	DTF_qf_ARR_TYPE* tmp_u2_ptr = DTF_qf_u2_ptr;
	DTF_qf_u2_ptr = DTF_qf_u1_ptr;
	DTF_qf_u1_ptr = DTF_qf_u0_ptr;
	DTF_qf_u0_ptr = tmp_u2_ptr;
}


void DTF_qf_execute(void)
{
	int i;
	
	DTF_qf_swap_y();

	for (i=0; i<DTF_qf_LEN; i++)
	{
		DTF_qf_y0_ptr[i] = DTF_qf_sat(
			+ DTF_qf_cy1 * DTF_qf_y1_ptr[i]
			+ DTF_qf_cy2 * DTF_qf_y2_ptr[i]
			+ DTF_qf_cu0 * DTF_qf_u0_ptr[i]
			+ DTF_qf_cu1 * DTF_qf_u1_ptr[i]
			+ DTF_qf_cu2 * DTF_qf_u2_ptr[i], DTF_qf_MAXVAL);
	}

	DTF_qf_swap_u();
}


void DTF_qf_init(void)
{
	int i;

	for (i=0; i<DTF_qf_LEN; i++)
	{
		DTF_qf_y0_ptr[i] = 0.0;
		DTF_qf_y1_ptr[i] = 0.0;
		DTF_qf_y2_ptr[i] = 0.0;
		DTF_qf_u0_ptr[i] = 0.0;
		DTF_qf_u1_ptr[i] = 0.0;
		DTF_qf_u2_ptr[i] = 0.0;
	}
}

#if (DTF_qf_UNIT_TEST == 1)
float DTF_qf_calc_error(const float *in1, const float* in2, const int len)
{
    int i;
    float error = 0.0;

    for (i=0; i<len; i++)
        error += (in1[i]-in2[i]) * (in1[i]-in2[i]);
    return error;
}


void DTF_qf_copy_vec(const float *in, float *out, const int len)
{
    int i;
    for (i=0; i<len; i++)
        out[i] = in[i];
}


void DTF_qf_print_vec(const float *in, const int len, const char *name)
{
    int i;
    printf("%s=[", name);
    for (i=0; i<len; i++)
        printf("%.8f,", in[i]);
    printf("]\n");
}


int DTF_qf_unit_test(void)
{
    int i;
    int tot_errors = 0;
    DTF_qf_ARR_TYPE *in_ptr;
    DTF_qf_ARR_TYPE *out_ptr;
    const DTF_qf_ARR_TYPE ABS_ERR_TOL = 1e-8;


    printf("RUNNING DTF_qf_unit_test\n");

    for (i=0; i<DTF_qf_test_nsamples; i++)
    {
        DTF_qf_ARR_TYPE error = 0.0;
        in_ptr = DTF_qf_get_u0_ptr();
        DTF_qf_copy_vec(&DTF_qf_test_input_data[i*DTF_qf_test_vec_len],
                            in_ptr, DTF_qf_test_vec_len);
        DTF_qf_execute();
        out_ptr = DTF_qf_get_y0_ptr();
        error = DTF_qf_calc_error(out_ptr,
                &DTF_qf_test_output_data[i*DTF_qf_test_vec_len],
                DTF_qf_test_vec_len);
        if (error > ABS_ERR_TOL)
        {
            tot_errors++;
            printf("ERROR at index %d=%.6f\n", i, error);
            DTF_qf_print_vec(out_ptr, DTF_qf_test_vec_len, "out=");
            DTF_qf_print_vec(&DTF_qf_test_output_data[i*DTF_qf_test_vec_len],
                                 DTF_qf_test_vec_len, "res=");
        }
    }
    DTF_qf_init();

    if (tot_errors > 0) {
        printf("WARNING DTF_qf_unit_test FAIL: number of errors=%d out of %d tests\n",
               tot_errors, DTF_qf_test_nsamples);
        return 0;
    } else {
        printf("DTF_qf_unit_test SUCCESS\n");
        return 1;
    }
}
#endif
