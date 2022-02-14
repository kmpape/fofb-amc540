#include "DTF_IMC_DI.h"

#ifdef SOC_C6678
#include <c6x.h>
#endif

#if (DTF_IMC_DI_UNIT_TEST == 1)
#include "DTF_IMC_DI_UNIT_TEST.h"
#endif

/* Arrays */
#ifdef SOC_C6678
#pragma DATA_ALIGN(DTF_IMC_DI_y0, 64)
#pragma DATA_ALIGN(DTF_IMC_DI_y1, 64)
#pragma DATA_ALIGN(DTF_IMC_DI_y2, 64)
#pragma DATA_ALIGN(DTF_IMC_DI_y3, 64)
#pragma DATA_ALIGN(DTF_IMC_DI_y4, 64)
#pragma DATA_ALIGN(DTF_IMC_DI_y5, 64)
#pragma DATA_ALIGN(DTF_IMC_DI_y6, 64)
#pragma DATA_ALIGN(DTF_IMC_DI_y7, 64)
#pragma DATA_ALIGN(DTF_IMC_DI_y8, 64)
#pragma DATA_ALIGN(DTF_IMC_DI_u0, 64)
#pragma DATA_ALIGN(DTF_IMC_DI_u1, 64)
#pragma SET_DATA_SECTION(".imc_DI")
#endif // SOC_C6678
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_y0[DTF_IMC_DI_LEN] = {(DTF_IMC_DI_ARR_TYPE)0.0};
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_y1[DTF_IMC_DI_LEN] = {(DTF_IMC_DI_ARR_TYPE)0.0};
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_y2[DTF_IMC_DI_LEN] = {(DTF_IMC_DI_ARR_TYPE)0.0};
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_y3[DTF_IMC_DI_LEN] = {(DTF_IMC_DI_ARR_TYPE)0.0};
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_y4[DTF_IMC_DI_LEN] = {(DTF_IMC_DI_ARR_TYPE)0.0};
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_y5[DTF_IMC_DI_LEN] = {(DTF_IMC_DI_ARR_TYPE)0.0};
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_y6[DTF_IMC_DI_LEN] = {(DTF_IMC_DI_ARR_TYPE)0.0};
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_y7[DTF_IMC_DI_LEN] = {(DTF_IMC_DI_ARR_TYPE)0.0};
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_y8[DTF_IMC_DI_LEN] = {(DTF_IMC_DI_ARR_TYPE)0.0};
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_u0[DTF_IMC_DI_LEN] = {(DTF_IMC_DI_ARR_TYPE)0.0};
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_u1[DTF_IMC_DI_LEN] = {(DTF_IMC_DI_ARR_TYPE)0.0};
#ifdef SOC_C6678
#pragma SET_DATA_SECTION()
#endif // SOC_C6678


/* Pointers */
#ifdef SOC_C6678
#pragma SET_DATA_SECTION(".imc_DI")
#endif // SOC_C6678
DTF_IMC_DI_ARR_TYPE *DTF_IMC_DI_y0_ptr = DTF_IMC_DI_y0;
DTF_IMC_DI_ARR_TYPE *DTF_IMC_DI_y1_ptr = DTF_IMC_DI_y1;
DTF_IMC_DI_ARR_TYPE *DTF_IMC_DI_y2_ptr = DTF_IMC_DI_y2;
DTF_IMC_DI_ARR_TYPE *DTF_IMC_DI_y3_ptr = DTF_IMC_DI_y3;
DTF_IMC_DI_ARR_TYPE *DTF_IMC_DI_y4_ptr = DTF_IMC_DI_y4;
DTF_IMC_DI_ARR_TYPE *DTF_IMC_DI_y5_ptr = DTF_IMC_DI_y5;
DTF_IMC_DI_ARR_TYPE *DTF_IMC_DI_y6_ptr = DTF_IMC_DI_y6;
DTF_IMC_DI_ARR_TYPE *DTF_IMC_DI_y7_ptr = DTF_IMC_DI_y7;
DTF_IMC_DI_ARR_TYPE *DTF_IMC_DI_y8_ptr = DTF_IMC_DI_y8;
DTF_IMC_DI_ARR_TYPE *DTF_IMC_DI_u0_ptr = DTF_IMC_DI_u0;
DTF_IMC_DI_ARR_TYPE *DTF_IMC_DI_u1_ptr = DTF_IMC_DI_u1;
#ifdef SOC_C6678
#pragma SET_DATA_SECTION()
#endif // SOC_C6678


/* Coefficients */
#ifdef SOC_C6678
#pragma SET_DATA_SECTION(".imc_DI")
#endif // SOC_C6678
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_cy1 = (DTF_IMC_DI_ARR_TYPE)0.8668778997501816;
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_cy2 = (DTF_IMC_DI_ARR_TYPE)-0.0000000000000000;
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_cy3 = (DTF_IMC_DI_ARR_TYPE)-0.0000000000000000;
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_cy4 = (DTF_IMC_DI_ARR_TYPE)-0.0000000000000000;
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_cy5 = (DTF_IMC_DI_ARR_TYPE)-0.0000000000000000;
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_cy6 = (DTF_IMC_DI_ARR_TYPE)-0.0000000000000000;
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_cy7 = (DTF_IMC_DI_ARR_TYPE)-0.0000000000000000;
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_cy8 = (DTF_IMC_DI_ARR_TYPE)0.1331219671277181;
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_cu0 = (DTF_IMC_DI_ARR_TYPE)0.3740962012567987;
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_cu1 = (DTF_IMC_DI_ARR_TYPE)-0.2409742341290805;
#ifdef SOC_C6678
#pragma SET_DATA_SECTION()
#endif // SOC_C6678


DTF_IMC_DI_ARR_TYPE* DTF_IMC_DI_get_y0_ptr(void)
{
	return DTF_IMC_DI_y0_ptr;
}


DTF_IMC_DI_ARR_TYPE* DTF_IMC_DI_get_u0_ptr(void)
{
	return DTF_IMC_DI_u0_ptr;
}


void DTF_IMC_DI_swap_y(void)
{
	DTF_IMC_DI_ARR_TYPE* tmp_y8_ptr = DTF_IMC_DI_y8_ptr;
	DTF_IMC_DI_y8_ptr = DTF_IMC_DI_y7_ptr;
	DTF_IMC_DI_y7_ptr = DTF_IMC_DI_y6_ptr;
	DTF_IMC_DI_y6_ptr = DTF_IMC_DI_y5_ptr;
	DTF_IMC_DI_y5_ptr = DTF_IMC_DI_y4_ptr;
	DTF_IMC_DI_y4_ptr = DTF_IMC_DI_y3_ptr;
	DTF_IMC_DI_y3_ptr = DTF_IMC_DI_y2_ptr;
	DTF_IMC_DI_y2_ptr = DTF_IMC_DI_y1_ptr;
	DTF_IMC_DI_y1_ptr = DTF_IMC_DI_y0_ptr;
	DTF_IMC_DI_y0_ptr = tmp_y8_ptr;
}


void DTF_IMC_DI_swap_u(void)
{
	DTF_IMC_DI_ARR_TYPE* tmp_u1_ptr = DTF_IMC_DI_u1_ptr;
	DTF_IMC_DI_u1_ptr = DTF_IMC_DI_u0_ptr;
	DTF_IMC_DI_u0_ptr = tmp_u1_ptr;
}


void DTF_IMC_DI_execute(void)
{
	int i;
	const DTF_IMC_DI_ARR_TYPE maxval = 10000.0;

	DTF_IMC_DI_swap_y();

	for (i=0; i<DTF_IMC_DI_LEN; i++)
	{
		DTF_IMC_DI_y0_ptr[i] = DTF_IMC_DI_sat(
			+ DTF_IMC_DI_cy1 * DTF_IMC_DI_y1_ptr[i]
			//+ DTF_IMC_DI_cy2 * DTF_IMC_DI_y2_ptr[i]//coefficient is zero
			//+ DTF_IMC_DI_cy3 * DTF_IMC_DI_y3_ptr[i]//coefficient is zero
			//+ DTF_IMC_DI_cy4 * DTF_IMC_DI_y4_ptr[i]//coefficient is zero
			//+ DTF_IMC_DI_cy5 * DTF_IMC_DI_y5_ptr[i]//coefficient is zero
			//+ DTF_IMC_DI_cy6 * DTF_IMC_DI_y6_ptr[i]//coefficient is zero
			//+ DTF_IMC_DI_cy7 * DTF_IMC_DI_y7_ptr[i]//coefficient is zero
			+ DTF_IMC_DI_cy8 * DTF_IMC_DI_y8_ptr[i]
			+ DTF_IMC_DI_cu0 * DTF_IMC_DI_u0_ptr[i]
			+ DTF_IMC_DI_cu1 * DTF_IMC_DI_u1_ptr[i], maxval);
	}

	DTF_IMC_DI_swap_u();
}


void DTF_IMC_DI_init(void)
{
	int i;

	for (i=0; i<DTF_IMC_DI_LEN; i++)
	{
		DTF_IMC_DI_y0_ptr[i] = 0.0;
		DTF_IMC_DI_y1_ptr[i] = 0.0;
		DTF_IMC_DI_y2_ptr[i] = 0.0;
		DTF_IMC_DI_y3_ptr[i] = 0.0;
		DTF_IMC_DI_y4_ptr[i] = 0.0;
		DTF_IMC_DI_y5_ptr[i] = 0.0;
		DTF_IMC_DI_y6_ptr[i] = 0.0;
		DTF_IMC_DI_y7_ptr[i] = 0.0;
		DTF_IMC_DI_y8_ptr[i] = 0.0;
		DTF_IMC_DI_u0_ptr[i] = 0.0;
		DTF_IMC_DI_u1_ptr[i] = 0.0;
	}
}

#if (DTF_IMC_DI_UNIT_TEST == 1)
float DTF_IMC_DI_calc_error(const float *in1, const float* in2, const int len)
{
    int i;
    float error = 0.0;

    for (i=0; i<len; i++)
        error += (in1[i]-in2[i]) * (in1[i]-in2[i]);
    return error;
}


void DTF_IMC_DI_copy_vec(const float *in, float *out, const int len)
{
    int i;
    for (i=0; i<len; i++)
        out[i] = in[i];
}


void DTF_IMC_DI_print_vec(const float *in, const int len, const char *name)
{
    int i;
    printf("%s=[", name);
    for (i=0; i<len; i++)
        printf("%.8f,", in[i]);
    printf("]\n");
}


int DTF_IMC_DI_unit_test(void)
{
    int i;
    int tot_errors = 0;
    DTF_IMC_DI_ARR_TYPE *in_ptr;
    DTF_IMC_DI_ARR_TYPE *out_ptr;
    const DTF_IMC_DI_ARR_TYPE ABS_ERR_TOL = 1e-8;


    printf("RUNNING DTF_IMC_DI_unit_test\n");

    for (i=0; i<DTF_IMC_DI_test_nsamples; i++)
    {
        DTF_IMC_DI_ARR_TYPE error = 0.0;
        in_ptr = DTF_IMC_DI_get_u0_ptr();
        DTF_IMC_DI_copy_vec(&DTF_IMC_DI_test_input_data[i*DTF_IMC_DI_test_vec_len],
                            in_ptr, DTF_IMC_DI_test_vec_len);
        DTF_IMC_DI_execute();
        out_ptr = DTF_IMC_DI_get_y0_ptr();
        error = DTF_IMC_DI_calc_error(out_ptr,
                &DTF_IMC_DI_test_output_data[i*DTF_IMC_DI_test_vec_len],
                DTF_IMC_DI_test_vec_len);
        if (error > ABS_ERR_TOL)
        {
            tot_errors++;
            printf("ERROR at index %d=%.6f\n", i, error);
            DTF_IMC_DI_print_vec(out_ptr, DTF_IMC_DI_test_vec_len, "out=");
            DTF_IMC_DI_print_vec(&DTF_IMC_DI_test_output_data[i*DTF_IMC_DI_test_vec_len],
                                 DTF_IMC_DI_test_vec_len, "res=");
        }
    }
    DTF_IMC_DI_init();

    if (tot_errors > 0) {
        printf("WARNING DTF_IMC_DI_unit_test FAIL: number of errors=%d out of %d tests\n",
               tot_errors, DTF_IMC_DI_test_nsamples);
        return 0;
    } else {
        printf("DTF_IMC_DI_unit_test SUCCESS\n");
        return 1;
    }
}
#endif
