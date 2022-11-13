#include <stdio.h>
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
#pragma DATA_ALIGN(DTF_IMC_DI_y9, 64)
#pragma DATA_ALIGN(DTF_IMC_DI_y10, 64)
#pragma DATA_ALIGN(DTF_IMC_DI_y11, 64)
#pragma DATA_ALIGN(DTF_IMC_DI_u0, 64)
#pragma DATA_ALIGN(DTF_IMC_DI_u1, 64)
#pragma DATA_ALIGN(DTF_IMC_DI_u2, 64)
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
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_y9[DTF_IMC_DI_LEN] = {(DTF_IMC_DI_ARR_TYPE)0.0};
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_y10[DTF_IMC_DI_LEN] = {(DTF_IMC_DI_ARR_TYPE)0.0};
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_y11[DTF_IMC_DI_LEN] = {(DTF_IMC_DI_ARR_TYPE)0.0};
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_u0[DTF_IMC_DI_LEN] = {(DTF_IMC_DI_ARR_TYPE)0.0};
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_u1[DTF_IMC_DI_LEN] = {(DTF_IMC_DI_ARR_TYPE)0.0};
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_u2[DTF_IMC_DI_LEN] = {(DTF_IMC_DI_ARR_TYPE)0.0};
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
DTF_IMC_DI_ARR_TYPE *DTF_IMC_DI_y9_ptr = DTF_IMC_DI_y9;
DTF_IMC_DI_ARR_TYPE *DTF_IMC_DI_y10_ptr = DTF_IMC_DI_y10;
DTF_IMC_DI_ARR_TYPE *DTF_IMC_DI_y11_ptr = DTF_IMC_DI_y11;
DTF_IMC_DI_ARR_TYPE *DTF_IMC_DI_u0_ptr = DTF_IMC_DI_u0;
DTF_IMC_DI_ARR_TYPE *DTF_IMC_DI_u1_ptr = DTF_IMC_DI_u1;
DTF_IMC_DI_ARR_TYPE *DTF_IMC_DI_u2_ptr = DTF_IMC_DI_u2;
#ifdef SOC_C6678
#pragma SET_DATA_SECTION()
#endif // SOC_C6678


/* Coefficients */
#ifdef SOC_C6678
#pragma SET_DATA_SECTION(".imc_DI")
#endif // SOC_C6678
#if (DTF_IMC_DI_XDIR == 1)
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_cy1 = (DTF_IMC_DI_ARR_TYPE)1.78967863362873957911E+00;
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_cy2 = (DTF_IMC_DI_ARR_TYPE)-8.00737402916808060915E-01;
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_cy3 = (DTF_IMC_DI_ARR_TYPE)-0.00000000000000000000E+00;
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_cy4 = (DTF_IMC_DI_ARR_TYPE)-0.00000000000000000000E+00;
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_cy5 = (DTF_IMC_DI_ARR_TYPE)-0.00000000000000000000E+00;
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_cy6 = (DTF_IMC_DI_ARR_TYPE)-0.00000000000000000000E+00;
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_cy7 = (DTF_IMC_DI_ARR_TYPE)-0.00000000000000000000E+00;
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_cy8 = (DTF_IMC_DI_ARR_TYPE)-0.00000000000000000000E+00;
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_cy9 = (DTF_IMC_DI_ARR_TYPE)-0.00000000000000000000E+00;
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_cy10 = (DTF_IMC_DI_ARR_TYPE)1.05160683185630210446E-01;
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_cy11 = (DTF_IMC_DI_ARR_TYPE)-9.41019138975617286391E-02;
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_cu0 = (DTF_IMC_DI_ARR_TYPE)3.90065774746309545939E-01;
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_cu1 = (DTF_IMC_DI_ARR_TYPE)-6.33951282947334826545E-01;
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_cu2 = (DTF_IMC_DI_ARR_TYPE)2.54944277489093762412E-01;
#else
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_cy1 = (DTF_IMC_DI_ARR_TYPE)1.78967863362873957911E+00;
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_cy2 = (DTF_IMC_DI_ARR_TYPE)-8.00737402916808060915E-01;
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_cy3 = (DTF_IMC_DI_ARR_TYPE)-0.00000000000000000000E+00;
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_cy4 = (DTF_IMC_DI_ARR_TYPE)-0.00000000000000000000E+00;
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_cy5 = (DTF_IMC_DI_ARR_TYPE)-0.00000000000000000000E+00;
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_cy6 = (DTF_IMC_DI_ARR_TYPE)-0.00000000000000000000E+00;
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_cy7 = (DTF_IMC_DI_ARR_TYPE)-0.00000000000000000000E+00;
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_cy8 = (DTF_IMC_DI_ARR_TYPE)-0.00000000000000000000E+00;
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_cy9 = (DTF_IMC_DI_ARR_TYPE)-0.00000000000000000000E+00;
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_cy10 = (DTF_IMC_DI_ARR_TYPE)1.05160683185630210446E-01;
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_cy11 = (DTF_IMC_DI_ARR_TYPE)-9.41019138975617286391E-02;
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_cu0 = (DTF_IMC_DI_ARR_TYPE)2.95520062917720260920E-01;
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_cu1 = (DTF_IMC_DI_ARR_TYPE)-4.54802350938322497154E-01;
DTF_IMC_DI_ARR_TYPE DTF_IMC_DI_cu2 = (DTF_IMC_DI_ARR_TYPE)1.70341057308670662529E-01;
#endif // XDIR
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
	DTF_IMC_DI_ARR_TYPE* tmp_y11_ptr = DTF_IMC_DI_y11_ptr;
	DTF_IMC_DI_y11_ptr = DTF_IMC_DI_y10_ptr;
	DTF_IMC_DI_y10_ptr = DTF_IMC_DI_y9_ptr;
	DTF_IMC_DI_y9_ptr = DTF_IMC_DI_y8_ptr;
	DTF_IMC_DI_y8_ptr = DTF_IMC_DI_y7_ptr;
	DTF_IMC_DI_y7_ptr = DTF_IMC_DI_y6_ptr;
	DTF_IMC_DI_y6_ptr = DTF_IMC_DI_y5_ptr;
	DTF_IMC_DI_y5_ptr = DTF_IMC_DI_y4_ptr;
	DTF_IMC_DI_y4_ptr = DTF_IMC_DI_y3_ptr;
	DTF_IMC_DI_y3_ptr = DTF_IMC_DI_y2_ptr;
	DTF_IMC_DI_y2_ptr = DTF_IMC_DI_y1_ptr;
	DTF_IMC_DI_y1_ptr = DTF_IMC_DI_y0_ptr;
	DTF_IMC_DI_y0_ptr = tmp_y11_ptr;
}


void DTF_IMC_DI_swap_u(void)
{
	DTF_IMC_DI_ARR_TYPE* tmp_u2_ptr = DTF_IMC_DI_u2_ptr;
	DTF_IMC_DI_u2_ptr = DTF_IMC_DI_u1_ptr;
	DTF_IMC_DI_u1_ptr = DTF_IMC_DI_u0_ptr;
	DTF_IMC_DI_u0_ptr = tmp_u2_ptr;
}


void DTF_IMC_DI_execute(void)
{
	int i;
	
	DTF_IMC_DI_swap_y();

	for (i=0; i<DTF_IMC_DI_LEN; i++)
	{
		DTF_IMC_DI_y0_ptr[i] = DTF_IMC_DI_sat(
			+ DTF_IMC_DI_cy1 * DTF_IMC_DI_y1_ptr[i]
			+ DTF_IMC_DI_cy2 * DTF_IMC_DI_y2_ptr[i]
			//+ DTF_IMC_DI_cy3 * DTF_IMC_DI_y3_ptr[i]//coefficient is zero
			//+ DTF_IMC_DI_cy4 * DTF_IMC_DI_y4_ptr[i]//coefficient is zero
			//+ DTF_IMC_DI_cy5 * DTF_IMC_DI_y5_ptr[i]//coefficient is zero
			//+ DTF_IMC_DI_cy6 * DTF_IMC_DI_y6_ptr[i]//coefficient is zero
			//+ DTF_IMC_DI_cy7 * DTF_IMC_DI_y7_ptr[i]//coefficient is zero
			//+ DTF_IMC_DI_cy8 * DTF_IMC_DI_y8_ptr[i]//coefficient is zero
			//+ DTF_IMC_DI_cy9 * DTF_IMC_DI_y9_ptr[i]//coefficient is zero
			+ DTF_IMC_DI_cy10 * DTF_IMC_DI_y10_ptr[i]
			+ DTF_IMC_DI_cy11 * DTF_IMC_DI_y11_ptr[i]
			+ DTF_IMC_DI_cu0 * DTF_IMC_DI_u0_ptr[i]
			+ DTF_IMC_DI_cu1 * DTF_IMC_DI_u1_ptr[i]
			+ DTF_IMC_DI_cu2 * DTF_IMC_DI_u2_ptr[i], DTF_IMC_DI_MAXVAL);
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
		DTF_IMC_DI_y9_ptr[i] = 0.0;
		DTF_IMC_DI_y10_ptr[i] = 0.0;
		DTF_IMC_DI_y11_ptr[i] = 0.0;
		DTF_IMC_DI_u0_ptr[i] = 0.0;
		DTF_IMC_DI_u1_ptr[i] = 0.0;
		DTF_IMC_DI_u2_ptr[i] = 0.0;
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
