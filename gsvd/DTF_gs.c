#include <stdio.h>
#include "DTF_gs.h"

#ifdef SOC_C6678
#include <c6x.h>
#endif
#if (DTF_gs_UNIT_TEST == 1)
#include "DTF_gs_UNIT_TEST.h"
#endif

/* Arrays */
#ifdef SOC_C6678
#pragma DATA_ALIGN(DTF_gs_y0, 64)
#pragma DATA_ALIGN(DTF_gs_y1, 64)
#pragma DATA_ALIGN(DTF_gs_u0, 64)
#pragma DATA_ALIGN(DTF_gs_u1, 64)
#pragma DATA_ALIGN(DTF_gs_u2, 64)
#pragma DATA_ALIGN(DTF_gs_u3, 64)
#pragma DATA_ALIGN(DTF_gs_u4, 64)
#pragma DATA_ALIGN(DTF_gs_u5, 64)
#pragma DATA_ALIGN(DTF_gs_u6, 64)
#pragma DATA_ALIGN(DTF_gs_u7, 64)
#pragma DATA_ALIGN(DTF_gs_u8, 64)
#pragma DATA_ALIGN(DTF_gs_u9, 64)
#pragma DATA_ALIGN(DTF_gs_u10, 64)
#pragma SET_DATA_SECTION(".gsvd_gs")
#endif // SOC_C6678
DTF_gs_ARR_TYPE DTF_gs_y0[DTF_gs_LEN] = {(DTF_gs_ARR_TYPE)0.0};
DTF_gs_ARR_TYPE DTF_gs_y1[DTF_gs_LEN] = {(DTF_gs_ARR_TYPE)0.0};
DTF_gs_ARR_TYPE DTF_gs_u0[DTF_gs_LEN] = {(DTF_gs_ARR_TYPE)0.0};
DTF_gs_ARR_TYPE DTF_gs_u1[DTF_gs_LEN] = {(DTF_gs_ARR_TYPE)0.0};
DTF_gs_ARR_TYPE DTF_gs_u2[DTF_gs_LEN] = {(DTF_gs_ARR_TYPE)0.0};
DTF_gs_ARR_TYPE DTF_gs_u3[DTF_gs_LEN] = {(DTF_gs_ARR_TYPE)0.0};
DTF_gs_ARR_TYPE DTF_gs_u4[DTF_gs_LEN] = {(DTF_gs_ARR_TYPE)0.0};
DTF_gs_ARR_TYPE DTF_gs_u5[DTF_gs_LEN] = {(DTF_gs_ARR_TYPE)0.0};
DTF_gs_ARR_TYPE DTF_gs_u6[DTF_gs_LEN] = {(DTF_gs_ARR_TYPE)0.0};
DTF_gs_ARR_TYPE DTF_gs_u7[DTF_gs_LEN] = {(DTF_gs_ARR_TYPE)0.0};
DTF_gs_ARR_TYPE DTF_gs_u8[DTF_gs_LEN] = {(DTF_gs_ARR_TYPE)0.0};
DTF_gs_ARR_TYPE DTF_gs_u9[DTF_gs_LEN] = {(DTF_gs_ARR_TYPE)0.0};
DTF_gs_ARR_TYPE DTF_gs_u10[DTF_gs_LEN] = {(DTF_gs_ARR_TYPE)0.0};
#ifdef SOC_C6678
#pragma SET_DATA_SECTION()
#endif // SOC_C6678


/* Pointers */
#ifdef SOC_C6678
#pragma SET_DATA_SECTION(".gsvd_gs")
#endif // SOC_C6678
DTF_gs_ARR_TYPE *DTF_gs_y0_ptr = DTF_gs_y0;
DTF_gs_ARR_TYPE *DTF_gs_y1_ptr = DTF_gs_y1;
DTF_gs_ARR_TYPE *DTF_gs_u0_ptr = DTF_gs_u0;
DTF_gs_ARR_TYPE *DTF_gs_u1_ptr = DTF_gs_u1;
DTF_gs_ARR_TYPE *DTF_gs_u2_ptr = DTF_gs_u2;
DTF_gs_ARR_TYPE *DTF_gs_u3_ptr = DTF_gs_u3;
DTF_gs_ARR_TYPE *DTF_gs_u4_ptr = DTF_gs_u4;
DTF_gs_ARR_TYPE *DTF_gs_u5_ptr = DTF_gs_u5;
DTF_gs_ARR_TYPE *DTF_gs_u6_ptr = DTF_gs_u6;
DTF_gs_ARR_TYPE *DTF_gs_u7_ptr = DTF_gs_u7;
DTF_gs_ARR_TYPE *DTF_gs_u8_ptr = DTF_gs_u8;
DTF_gs_ARR_TYPE *DTF_gs_u9_ptr = DTF_gs_u9;
DTF_gs_ARR_TYPE *DTF_gs_u10_ptr = DTF_gs_u10;
#ifdef SOC_C6678
#pragma SET_DATA_SECTION()
#endif // SOC_C6678


/* Coefficients */
#ifdef SOC_C6678
#pragma SET_DATA_SECTION(".gsvd_gs")
#endif // SOC_C6678
#if (DTF_gs_XDIR == 1)
DTF_gs_ARR_TYPE DTF_gs_cy1 = (DTF_gs_ARR_TYPE)0.7304026910486456;
DTF_gs_ARR_TYPE DTF_gs_cu0 = (DTF_gs_ARR_TYPE)0.0000000000000000;
DTF_gs_ARR_TYPE DTF_gs_cu1 = (DTF_gs_ARR_TYPE)0.0000000000000000;
DTF_gs_ARR_TYPE DTF_gs_cu2 = (DTF_gs_ARR_TYPE)0.0000000000000000;
DTF_gs_ARR_TYPE DTF_gs_cu3 = (DTF_gs_ARR_TYPE)0.0000000000000000;
DTF_gs_ARR_TYPE DTF_gs_cu4 = (DTF_gs_ARR_TYPE)0.0000000000000000;
DTF_gs_ARR_TYPE DTF_gs_cu5 = (DTF_gs_ARR_TYPE)0.0000000000000000;
DTF_gs_ARR_TYPE DTF_gs_cu6 = (DTF_gs_ARR_TYPE)0.0000000000000000;
DTF_gs_ARR_TYPE DTF_gs_cu7 = (DTF_gs_ARR_TYPE)0.0000000000000000;
DTF_gs_ARR_TYPE DTF_gs_cu8 = (DTF_gs_ARR_TYPE)0.0000000000000000;
DTF_gs_ARR_TYPE DTF_gs_cu9 = (DTF_gs_ARR_TYPE)0.0000000000000000;
DTF_gs_ARR_TYPE DTF_gs_cu10 = (DTF_gs_ARR_TYPE)0.2695973089513544;
#else
DTF_gs_ARR_TYPE DTF_gs_cy1 = (DTF_gs_ARR_TYPE)0.6441504439754081;
DTF_gs_ARR_TYPE DTF_gs_cu0 = (DTF_gs_ARR_TYPE)0.0000000000000000;
DTF_gs_ARR_TYPE DTF_gs_cu1 = (DTF_gs_ARR_TYPE)0.0000000000000000;
DTF_gs_ARR_TYPE DTF_gs_cu2 = (DTF_gs_ARR_TYPE)0.0000000000000000;
DTF_gs_ARR_TYPE DTF_gs_cu3 = (DTF_gs_ARR_TYPE)0.0000000000000000;
DTF_gs_ARR_TYPE DTF_gs_cu4 = (DTF_gs_ARR_TYPE)0.0000000000000000;
DTF_gs_ARR_TYPE DTF_gs_cu5 = (DTF_gs_ARR_TYPE)0.0000000000000000;
DTF_gs_ARR_TYPE DTF_gs_cu6 = (DTF_gs_ARR_TYPE)0.0000000000000000;
DTF_gs_ARR_TYPE DTF_gs_cu7 = (DTF_gs_ARR_TYPE)0.0000000000000000;
DTF_gs_ARR_TYPE DTF_gs_cu8 = (DTF_gs_ARR_TYPE)0.0000000000000000;
DTF_gs_ARR_TYPE DTF_gs_cu9 = (DTF_gs_ARR_TYPE)0.0000000000000000;
DTF_gs_ARR_TYPE DTF_gs_cu10 = (DTF_gs_ARR_TYPE)0.3558495560245918;
#endif // XDIR
#ifdef SOC_C6678
#pragma SET_DATA_SECTION()
#endif // SOC_C6678


DTF_gs_ARR_TYPE* DTF_gs_get_y0_ptr(void)
{
	return DTF_gs_y0_ptr;
}


DTF_gs_ARR_TYPE* DTF_gs_get_u0_ptr(void)
{
	return DTF_gs_u0_ptr;
}


void DTF_gs_swap_y(void)
{
	DTF_gs_ARR_TYPE* tmp_y1_ptr = DTF_gs_y1_ptr;
	DTF_gs_y1_ptr = DTF_gs_y0_ptr;
	DTF_gs_y0_ptr = tmp_y1_ptr;
}


void DTF_gs_swap_u(void)
{
	DTF_gs_ARR_TYPE* tmp_u10_ptr = DTF_gs_u10_ptr;
	DTF_gs_u10_ptr = DTF_gs_u9_ptr;
	DTF_gs_u9_ptr = DTF_gs_u8_ptr;
	DTF_gs_u8_ptr = DTF_gs_u7_ptr;
	DTF_gs_u7_ptr = DTF_gs_u6_ptr;
	DTF_gs_u6_ptr = DTF_gs_u5_ptr;
	DTF_gs_u5_ptr = DTF_gs_u4_ptr;
	DTF_gs_u4_ptr = DTF_gs_u3_ptr;
	DTF_gs_u3_ptr = DTF_gs_u2_ptr;
	DTF_gs_u2_ptr = DTF_gs_u1_ptr;
	DTF_gs_u1_ptr = DTF_gs_u0_ptr;
	DTF_gs_u0_ptr = tmp_u10_ptr;
}


void DTF_gs_execute(void)
{
	int i;
	
	DTF_gs_swap_y();

	for (i=0; i<DTF_gs_LEN; i++)
	{
		DTF_gs_y0_ptr[i] = DTF_gs_sat(
			+ DTF_gs_cy1 * DTF_gs_y1_ptr[i]
			//+ DTF_gs_cu0 * DTF_gs_u0_ptr[i]//coefficient is zero
			//+ DTF_gs_cu1 * DTF_gs_u1_ptr[i]//coefficient is zero
			//+ DTF_gs_cu2 * DTF_gs_u2_ptr[i]//coefficient is zero
			//+ DTF_gs_cu3 * DTF_gs_u3_ptr[i]//coefficient is zero
			//+ DTF_gs_cu4 * DTF_gs_u4_ptr[i]//coefficient is zero
			//+ DTF_gs_cu5 * DTF_gs_u5_ptr[i]//coefficient is zero
			//+ DTF_gs_cu6 * DTF_gs_u6_ptr[i]//coefficient is zero
			//+ DTF_gs_cu7 * DTF_gs_u7_ptr[i]//coefficient is zero
			//+ DTF_gs_cu8 * DTF_gs_u8_ptr[i]//coefficient is zero
			//+ DTF_gs_cu9 * DTF_gs_u9_ptr[i]//coefficient is zero
			+ DTF_gs_cu10 * DTF_gs_u10_ptr[i], DTF_gs_MAXVAL);
	}

	DTF_gs_swap_u();
}


void DTF_gs_init(void)
{
	int i;

	for (i=0; i<DTF_gs_LEN; i++)
	{
		DTF_gs_y0_ptr[i] = 0.0;
		DTF_gs_y1_ptr[i] = 0.0;
		DTF_gs_u0_ptr[i] = 0.0;
		DTF_gs_u1_ptr[i] = 0.0;
		DTF_gs_u2_ptr[i] = 0.0;
		DTF_gs_u3_ptr[i] = 0.0;
		DTF_gs_u4_ptr[i] = 0.0;
		DTF_gs_u5_ptr[i] = 0.0;
		DTF_gs_u6_ptr[i] = 0.0;
		DTF_gs_u7_ptr[i] = 0.0;
		DTF_gs_u8_ptr[i] = 0.0;
		DTF_gs_u9_ptr[i] = 0.0;
		DTF_gs_u10_ptr[i] = 0.0;
	}
}

#if (DTF_gs_UNIT_TEST == 1)
float DTF_gs_calc_error(const float *in1, const float* in2, const int len)
{
    int i;
    float error = 0.0;

    for (i=0; i<len; i++)
        error += (in1[i]-in2[i]) * (in1[i]-in2[i]);
    return error;
}


void DTF_gs_copy_vec(const float *in, float *out, const int len)
{
    int i;
    for (i=0; i<len; i++)
        out[i] = in[i];
}


void DTF_gs_print_vec(const float *in, const int len, const char *name)
{
    int i;
    printf("%s=[", name);
    for (i=0; i<len; i++)
        printf("%.8f,", in[i]);
    printf("]\n");
}


int DTF_gs_unit_test(void)
{
    int i;
    int tot_errors = 0;
    DTF_gs_ARR_TYPE *in_ptr;
    DTF_gs_ARR_TYPE *out_ptr;
    const DTF_gs_ARR_TYPE ABS_ERR_TOL = 1e-8;


    printf("RUNNING DTF_gs_unit_test\n");

    for (i=0; i<DTF_gs_test_nsamples; i++)
    {
        DTF_gs_ARR_TYPE error = 0.0;
        in_ptr = DTF_gs_get_u0_ptr();
        DTF_gs_copy_vec(&DTF_gs_test_input_data[i*DTF_gs_test_vec_len],
                            in_ptr, DTF_gs_test_vec_len);
        DTF_gs_execute();
        out_ptr = DTF_gs_get_y0_ptr();
        error = DTF_gs_calc_error(out_ptr,
                &DTF_gs_test_output_data[i*DTF_gs_test_vec_len],
                DTF_gs_test_vec_len);
        if (error > ABS_ERR_TOL)
        {
            tot_errors++;
            printf("ERROR at index %d=%.6f\n", i, error);
            DTF_gs_print_vec(out_ptr, DTF_gs_test_vec_len, "out=");
            DTF_gs_print_vec(&DTF_gs_test_output_data[i*DTF_gs_test_vec_len],
                                 DTF_gs_test_vec_len, "res=");
        }
    }
    DTF_gs_init();

    if (tot_errors > 0) {
        printf("WARNING DTF_gs_unit_test FAIL: number of errors=%d out of %d tests\n",
               tot_errors, DTF_gs_test_nsamples);
        return 0;
    } else {
        printf("DTF_gs_unit_test SUCCESS\n");
        return 1;
    }
}
#endif
