#include <stdio.h>
#include "DTF_gf.h"

#ifdef SOC_C6678
#include <c6x.h>
#endif
#if (DTF_gf_UNIT_TEST == 1)
#include "DTF_gf_UNIT_TEST.h"
#endif

/* Arrays */
#ifdef SOC_C6678
#pragma DATA_ALIGN(DTF_gf_y0, 64)
#pragma DATA_ALIGN(DTF_gf_y1, 64)
#pragma DATA_ALIGN(DTF_gf_u0, 64)
#pragma DATA_ALIGN(DTF_gf_u1, 64)
#pragma DATA_ALIGN(DTF_gf_u2, 64)
#pragma DATA_ALIGN(DTF_gf_u3, 64)
#pragma DATA_ALIGN(DTF_gf_u4, 64)
#pragma DATA_ALIGN(DTF_gf_u5, 64)
#pragma DATA_ALIGN(DTF_gf_u6, 64)
#pragma DATA_ALIGN(DTF_gf_u7, 64)
#pragma DATA_ALIGN(DTF_gf_u8, 64)
#pragma DATA_ALIGN(DTF_gf_u9, 64)
#pragma SET_DATA_SECTION(".gsvd_gf")
#endif // SOC_C6678
DTF_gf_ARR_TYPE DTF_gf_y0[DTF_gf_LEN] = {(DTF_gf_ARR_TYPE)0.0};
DTF_gf_ARR_TYPE DTF_gf_y1[DTF_gf_LEN] = {(DTF_gf_ARR_TYPE)0.0};
DTF_gf_ARR_TYPE DTF_gf_u0[DTF_gf_LEN] = {(DTF_gf_ARR_TYPE)0.0};
DTF_gf_ARR_TYPE DTF_gf_u1[DTF_gf_LEN] = {(DTF_gf_ARR_TYPE)0.0};
DTF_gf_ARR_TYPE DTF_gf_u2[DTF_gf_LEN] = {(DTF_gf_ARR_TYPE)0.0};
DTF_gf_ARR_TYPE DTF_gf_u3[DTF_gf_LEN] = {(DTF_gf_ARR_TYPE)0.0};
DTF_gf_ARR_TYPE DTF_gf_u4[DTF_gf_LEN] = {(DTF_gf_ARR_TYPE)0.0};
DTF_gf_ARR_TYPE DTF_gf_u5[DTF_gf_LEN] = {(DTF_gf_ARR_TYPE)0.0};
DTF_gf_ARR_TYPE DTF_gf_u6[DTF_gf_LEN] = {(DTF_gf_ARR_TYPE)0.0};
DTF_gf_ARR_TYPE DTF_gf_u7[DTF_gf_LEN] = {(DTF_gf_ARR_TYPE)0.0};
DTF_gf_ARR_TYPE DTF_gf_u8[DTF_gf_LEN] = {(DTF_gf_ARR_TYPE)0.0};
DTF_gf_ARR_TYPE DTF_gf_u9[DTF_gf_LEN] = {(DTF_gf_ARR_TYPE)0.0};
#ifdef SOC_C6678
#pragma SET_DATA_SECTION()
#endif // SOC_C6678


/* Pointers */
#ifdef SOC_C6678
#pragma SET_DATA_SECTION(".gsvd_gf")
#endif // SOC_C6678
DTF_gf_ARR_TYPE *DTF_gf_y0_ptr = DTF_gf_y0;
DTF_gf_ARR_TYPE *DTF_gf_y1_ptr = DTF_gf_y1;
DTF_gf_ARR_TYPE *DTF_gf_u0_ptr = DTF_gf_u0;
DTF_gf_ARR_TYPE *DTF_gf_u1_ptr = DTF_gf_u1;
DTF_gf_ARR_TYPE *DTF_gf_u2_ptr = DTF_gf_u2;
DTF_gf_ARR_TYPE *DTF_gf_u3_ptr = DTF_gf_u3;
DTF_gf_ARR_TYPE *DTF_gf_u4_ptr = DTF_gf_u4;
DTF_gf_ARR_TYPE *DTF_gf_u5_ptr = DTF_gf_u5;
DTF_gf_ARR_TYPE *DTF_gf_u6_ptr = DTF_gf_u6;
DTF_gf_ARR_TYPE *DTF_gf_u7_ptr = DTF_gf_u7;
DTF_gf_ARR_TYPE *DTF_gf_u8_ptr = DTF_gf_u8;
DTF_gf_ARR_TYPE *DTF_gf_u9_ptr = DTF_gf_u9;
#ifdef SOC_C6678
#pragma SET_DATA_SECTION()
#endif // SOC_C6678


/* Coefficients */
#ifdef SOC_C6678
#pragma SET_DATA_SECTION(".gsvd_gf")
#endif // SOC_C6678
#if (DTF_gf_XDIR == 1)
DTF_gf_ARR_TYPE DTF_gf_cy1 = (DTF_gf_ARR_TYPE)0.7304026910486456;
DTF_gf_ARR_TYPE DTF_gf_cu0 = (DTF_gf_ARR_TYPE)0.0000000000000000;
DTF_gf_ARR_TYPE DTF_gf_cu1 = (DTF_gf_ARR_TYPE)0.0000000000000000;
DTF_gf_ARR_TYPE DTF_gf_cu2 = (DTF_gf_ARR_TYPE)0.0000000000000000;
DTF_gf_ARR_TYPE DTF_gf_cu3 = (DTF_gf_ARR_TYPE)0.0000000000000000;
DTF_gf_ARR_TYPE DTF_gf_cu4 = (DTF_gf_ARR_TYPE)0.0000000000000000;
DTF_gf_ARR_TYPE DTF_gf_cu5 = (DTF_gf_ARR_TYPE)0.0000000000000000;
DTF_gf_ARR_TYPE DTF_gf_cu6 = (DTF_gf_ARR_TYPE)0.0000000000000000;
DTF_gf_ARR_TYPE DTF_gf_cu7 = (DTF_gf_ARR_TYPE)0.0000000000000000;
DTF_gf_ARR_TYPE DTF_gf_cu8 = (DTF_gf_ARR_TYPE)0.0000000000000000;
DTF_gf_ARR_TYPE DTF_gf_cu9 = (DTF_gf_ARR_TYPE)0.2695973089513544;
#else
DTF_gf_ARR_TYPE DTF_gf_cy1 = (DTF_gf_ARR_TYPE)0.6441504439754081;
DTF_gf_ARR_TYPE DTF_gf_cu0 = (DTF_gf_ARR_TYPE)0.0000000000000000;
DTF_gf_ARR_TYPE DTF_gf_cu1 = (DTF_gf_ARR_TYPE)0.0000000000000000;
DTF_gf_ARR_TYPE DTF_gf_cu2 = (DTF_gf_ARR_TYPE)0.0000000000000000;
DTF_gf_ARR_TYPE DTF_gf_cu3 = (DTF_gf_ARR_TYPE)0.0000000000000000;
DTF_gf_ARR_TYPE DTF_gf_cu4 = (DTF_gf_ARR_TYPE)0.0000000000000000;
DTF_gf_ARR_TYPE DTF_gf_cu5 = (DTF_gf_ARR_TYPE)0.0000000000000000;
DTF_gf_ARR_TYPE DTF_gf_cu6 = (DTF_gf_ARR_TYPE)0.0000000000000000;
DTF_gf_ARR_TYPE DTF_gf_cu7 = (DTF_gf_ARR_TYPE)0.0000000000000000;
DTF_gf_ARR_TYPE DTF_gf_cu8 = (DTF_gf_ARR_TYPE)0.0000000000000000;
DTF_gf_ARR_TYPE DTF_gf_cu9 = (DTF_gf_ARR_TYPE)0.3558495560245918;
#endif // XDIR
#ifdef SOC_C6678
#pragma SET_DATA_SECTION()
#endif // SOC_C6678


DTF_gf_ARR_TYPE* DTF_gf_get_y0_ptr(void)
{
	return DTF_gf_y0_ptr;
}


DTF_gf_ARR_TYPE* DTF_gf_get_u0_ptr(void)
{
	return DTF_gf_u0_ptr;
}


void DTF_gf_swap_y(void)
{
	DTF_gf_ARR_TYPE* tmp_y1_ptr = DTF_gf_y1_ptr;
	DTF_gf_y1_ptr = DTF_gf_y0_ptr;
	DTF_gf_y0_ptr = tmp_y1_ptr;
}


void DTF_gf_swap_u(void)
{
	DTF_gf_ARR_TYPE* tmp_u9_ptr = DTF_gf_u9_ptr;
	DTF_gf_u9_ptr = DTF_gf_u8_ptr;
	DTF_gf_u8_ptr = DTF_gf_u7_ptr;
	DTF_gf_u7_ptr = DTF_gf_u6_ptr;
	DTF_gf_u6_ptr = DTF_gf_u5_ptr;
	DTF_gf_u5_ptr = DTF_gf_u4_ptr;
	DTF_gf_u4_ptr = DTF_gf_u3_ptr;
	DTF_gf_u3_ptr = DTF_gf_u2_ptr;
	DTF_gf_u2_ptr = DTF_gf_u1_ptr;
	DTF_gf_u1_ptr = DTF_gf_u0_ptr;
	DTF_gf_u0_ptr = tmp_u9_ptr;
}


void DTF_gf_execute(void)
{
	int i;
	
	DTF_gf_swap_y();

	for (i=0; i<DTF_gf_LEN; i++)
	{
		DTF_gf_y0_ptr[i] = DTF_gf_sat(
			+ DTF_gf_cy1 * DTF_gf_y1_ptr[i]
			//+ DTF_gf_cu0 * DTF_gf_u0_ptr[i]//coefficient is zero
			//+ DTF_gf_cu1 * DTF_gf_u1_ptr[i]//coefficient is zero
			//+ DTF_gf_cu2 * DTF_gf_u2_ptr[i]//coefficient is zero
			//+ DTF_gf_cu3 * DTF_gf_u3_ptr[i]//coefficient is zero
			//+ DTF_gf_cu4 * DTF_gf_u4_ptr[i]//coefficient is zero
			//+ DTF_gf_cu5 * DTF_gf_u5_ptr[i]//coefficient is zero
			//+ DTF_gf_cu6 * DTF_gf_u6_ptr[i]//coefficient is zero
			//+ DTF_gf_cu7 * DTF_gf_u7_ptr[i]//coefficient is zero
			//+ DTF_gf_cu8 * DTF_gf_u8_ptr[i]//coefficient is zero
			+ DTF_gf_cu9 * DTF_gf_u9_ptr[i], DTF_gf_MAXVAL);
	}

	DTF_gf_swap_u();
}


void DTF_gf_init(void)
{
	int i;

	for (i=0; i<DTF_gf_LEN; i++)
	{
		DTF_gf_y0_ptr[i] = 0.0;
		DTF_gf_y1_ptr[i] = 0.0;
		DTF_gf_u0_ptr[i] = 0.0;
		DTF_gf_u1_ptr[i] = 0.0;
		DTF_gf_u2_ptr[i] = 0.0;
		DTF_gf_u3_ptr[i] = 0.0;
		DTF_gf_u4_ptr[i] = 0.0;
		DTF_gf_u5_ptr[i] = 0.0;
		DTF_gf_u6_ptr[i] = 0.0;
		DTF_gf_u7_ptr[i] = 0.0;
		DTF_gf_u8_ptr[i] = 0.0;
		DTF_gf_u9_ptr[i] = 0.0;
	}
}

#if (DTF_gf_UNIT_TEST == 1)
float DTF_gf_calc_error(const float *in1, const float* in2, const int len)
{
    int i;
    float error = 0.0;

    for (i=0; i<len; i++)
        error += (in1[i]-in2[i]) * (in1[i]-in2[i]);
    return error;
}


void DTF_gf_copy_vec(const float *in, float *out, const int len)
{
    int i;
    for (i=0; i<len; i++)
        out[i] = in[i];
}


void DTF_gf_print_vec(const float *in, const int len, const char *name)
{
    int i;
    printf("%s=[", name);
    for (i=0; i<len; i++)
        printf("%.8f,", in[i]);
    printf("]\n");
}


int DTF_gf_unit_test(void)
{
    int i;
    int tot_errors = 0;
    DTF_gf_ARR_TYPE *in_ptr;
    DTF_gf_ARR_TYPE *out_ptr;
    const DTF_gf_ARR_TYPE ABS_ERR_TOL = 1e-8;


    printf("RUNNING DTF_gf_unit_test\n");

    for (i=0; i<DTF_gf_test_nsamples; i++)
    {
        DTF_gf_ARR_TYPE error = 0.0;
        in_ptr = DTF_gf_get_u0_ptr();
        DTF_gf_copy_vec(&DTF_gf_test_input_data[i*DTF_gf_test_vec_len],
                            in_ptr, DTF_gf_test_vec_len);
        DTF_gf_execute();
        out_ptr = DTF_gf_get_y0_ptr();
        error = DTF_gf_calc_error(out_ptr,
                &DTF_gf_test_output_data[i*DTF_gf_test_vec_len],
                DTF_gf_test_vec_len);
        if (error > ABS_ERR_TOL)
        {
            tot_errors++;
            printf("ERROR at index %d=%.6f\n", i, error);
            DTF_gf_print_vec(out_ptr, DTF_gf_test_vec_len, "out=");
            DTF_gf_print_vec(&DTF_gf_test_output_data[i*DTF_gf_test_vec_len],
                                 DTF_gf_test_vec_len, "res=");
        }
    }
    DTF_gf_init();

    if (tot_errors > 0) {
        printf("WARNING DTF_gf_unit_test FAIL: number of errors=%d out of %d tests\n",
               tot_errors, DTF_gf_test_nsamples);
        return 0;
    } else {
        printf("DTF_gf_unit_test SUCCESS\n");
        return 1;
    }
}
#endif
