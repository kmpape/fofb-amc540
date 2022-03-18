#include "DTF_pmcf.h"

#ifdef SOC_C6678
#include <c6x.h>
#endif
#if (DTF_pmcf_UNIT_TEST == 1)
#include "DTF_pmcf_UNIT_TEST.h"
#endif

/* Arrays */
#ifdef SOC_C6678
#pragma DATA_ALIGN(DTF_pmcf_y0, 64)
#pragma DATA_ALIGN(DTF_pmcf_y1, 64)
#pragma DATA_ALIGN(DTF_pmcf_y2, 64)
#pragma DATA_ALIGN(DTF_pmcf_y3, 64)
#pragma DATA_ALIGN(DTF_pmcf_u0, 64)
#pragma DATA_ALIGN(DTF_pmcf_u1, 64)
#pragma DATA_ALIGN(DTF_pmcf_u2, 64)
#pragma DATA_ALIGN(DTF_pmcf_u3, 64)
#pragma SET_DATA_SECTION(".gsvd_pmcf")
#endif // SOC_C6678
DTF_pmcf_ARR_TYPE DTF_pmcf_y0[DTF_pmcf_LEN] = {(DTF_pmcf_ARR_TYPE)0.0};
DTF_pmcf_ARR_TYPE DTF_pmcf_y1[DTF_pmcf_LEN] = {(DTF_pmcf_ARR_TYPE)0.0};
DTF_pmcf_ARR_TYPE DTF_pmcf_y2[DTF_pmcf_LEN] = {(DTF_pmcf_ARR_TYPE)0.0};
DTF_pmcf_ARR_TYPE DTF_pmcf_y3[DTF_pmcf_LEN] = {(DTF_pmcf_ARR_TYPE)0.0};
DTF_pmcf_ARR_TYPE DTF_pmcf_u0[DTF_pmcf_LEN] = {(DTF_pmcf_ARR_TYPE)0.0};
DTF_pmcf_ARR_TYPE DTF_pmcf_u1[DTF_pmcf_LEN] = {(DTF_pmcf_ARR_TYPE)0.0};
DTF_pmcf_ARR_TYPE DTF_pmcf_u2[DTF_pmcf_LEN] = {(DTF_pmcf_ARR_TYPE)0.0};
DTF_pmcf_ARR_TYPE DTF_pmcf_u3[DTF_pmcf_LEN] = {(DTF_pmcf_ARR_TYPE)0.0};
#ifdef SOC_C6678
#pragma SET_DATA_SECTION()
#endif // SOC_C6678


/* Pointers */
#ifdef SOC_C6678
#pragma SET_DATA_SECTION(".gsvd_pmcf")
#endif // SOC_C6678
DTF_pmcf_ARR_TYPE *DTF_pmcf_y0_ptr = DTF_pmcf_y0;
DTF_pmcf_ARR_TYPE *DTF_pmcf_y1_ptr = DTF_pmcf_y1;
DTF_pmcf_ARR_TYPE *DTF_pmcf_y2_ptr = DTF_pmcf_y2;
DTF_pmcf_ARR_TYPE *DTF_pmcf_y3_ptr = DTF_pmcf_y3;
DTF_pmcf_ARR_TYPE *DTF_pmcf_u0_ptr = DTF_pmcf_u0;
DTF_pmcf_ARR_TYPE *DTF_pmcf_u1_ptr = DTF_pmcf_u1;
DTF_pmcf_ARR_TYPE *DTF_pmcf_u2_ptr = DTF_pmcf_u2;
DTF_pmcf_ARR_TYPE *DTF_pmcf_u3_ptr = DTF_pmcf_u3;
#ifdef SOC_C6678
#pragma SET_DATA_SECTION()
#endif // SOC_C6678


/* Coefficients */
#ifdef SOC_C6678
#pragma SET_DATA_SECTION(".gsvd_pmcf")
#endif // SOC_C6678
DTF_pmcf_ARR_TYPE DTF_pmcf_cy1 = (DTF_pmcf_ARR_TYPE)1.9997369618850134;
DTF_pmcf_ARR_TYPE DTF_pmcf_cy2 = (DTF_pmcf_ARR_TYPE)-1.4487433807850150;
DTF_pmcf_ARR_TYPE DTF_pmcf_cy3 = (DTF_pmcf_ARR_TYPE)0.3707354566715290;
DTF_pmcf_ARR_TYPE DTF_pmcf_cu0 = (DTF_pmcf_ARR_TYPE)0.0000000000000000;
DTF_pmcf_ARR_TYPE DTF_pmcf_cu1 = (DTF_pmcf_ARR_TYPE)0.1201511491187628;
DTF_pmcf_ARR_TYPE DTF_pmcf_cu2 = (DTF_pmcf_ARR_TYPE)0.0224086403490909;
DTF_pmcf_ARR_TYPE DTF_pmcf_cu3 = (DTF_pmcf_ARR_TYPE)-0.0642888272393811;
#ifdef SOC_C6678
#pragma SET_DATA_SECTION()
#endif // SOC_C6678


DTF_pmcf_ARR_TYPE* DTF_pmcf_get_y0_ptr(void)
{
	return DTF_pmcf_y0_ptr;
}


DTF_pmcf_ARR_TYPE* DTF_pmcf_get_u0_ptr(void)
{
	return DTF_pmcf_u0_ptr;
}


void DTF_pmcf_swap_y(void)
{
	DTF_pmcf_ARR_TYPE* tmp_y3_ptr = DTF_pmcf_y3_ptr;
	DTF_pmcf_y3_ptr = DTF_pmcf_y2_ptr;
	DTF_pmcf_y2_ptr = DTF_pmcf_y1_ptr;
	DTF_pmcf_y1_ptr = DTF_pmcf_y0_ptr;
	DTF_pmcf_y0_ptr = tmp_y3_ptr;
}


void DTF_pmcf_swap_u(void)
{
	DTF_pmcf_ARR_TYPE* tmp_u3_ptr = DTF_pmcf_u3_ptr;
	DTF_pmcf_u3_ptr = DTF_pmcf_u2_ptr;
	DTF_pmcf_u2_ptr = DTF_pmcf_u1_ptr;
	DTF_pmcf_u1_ptr = DTF_pmcf_u0_ptr;
	DTF_pmcf_u0_ptr = tmp_u3_ptr;
}


void DTF_pmcf_execute(void)
{
	int i;
	const DTF_pmcf_ARR_TYPE maxval = 10000.0;

	DTF_pmcf_swap_y();

	for (i=0; i<DTF_pmcf_LEN; i++)
	{
		DTF_pmcf_y0_ptr[i] = DTF_pmcf_sat(
			+ DTF_pmcf_cy1 * DTF_pmcf_y1_ptr[i]
			+ DTF_pmcf_cy2 * DTF_pmcf_y2_ptr[i]
			+ DTF_pmcf_cy3 * DTF_pmcf_y3_ptr[i]
			//+ DTF_pmcf_cu0 * DTF_pmcf_u0_ptr[i]//coefficient is zero
			+ DTF_pmcf_cu1 * DTF_pmcf_u1_ptr[i]
			+ DTF_pmcf_cu2 * DTF_pmcf_u2_ptr[i]
			+ DTF_pmcf_cu3 * DTF_pmcf_u3_ptr[i], maxval);
	}

	DTF_pmcf_swap_u();
}


void DTF_pmcf_init(void)
{
	int i;

	for (i=0; i<DTF_pmcf_LEN; i++)
	{
		DTF_pmcf_y0_ptr[i] = 0.0;
		DTF_pmcf_y1_ptr[i] = 0.0;
		DTF_pmcf_y2_ptr[i] = 0.0;
		DTF_pmcf_y3_ptr[i] = 0.0;
		DTF_pmcf_u0_ptr[i] = 0.0;
		DTF_pmcf_u1_ptr[i] = 0.0;
		DTF_pmcf_u2_ptr[i] = 0.0;
		DTF_pmcf_u3_ptr[i] = 0.0;
	}
}

#if (DTF_pmcf_UNIT_TEST == 1)
float DTF_pmcf_calc_error(const float *in1, const float* in2, const int len)
{
    int i;
    float error = 0.0;

    for (i=0; i<len; i++)
        error += (in1[i]-in2[i]) * (in1[i]-in2[i]);
    return error;
}


void DTF_pmcf_copy_vec(const float *in, float *out, const int len)
{
    int i;
    for (i=0; i<len; i++)
        out[i] = in[i];
}


void DTF_pmcf_print_vec(const float *in, const int len, const char *name)
{
    int i;
    printf("%s=[", name);
    for (i=0; i<len; i++)
        printf("%.8f,", in[i]);
    printf("]\n");
}


int DTF_pmcf_unit_test(void)
{
    int i;
    int tot_errors = 0;
    DTF_pmcf_ARR_TYPE *in_ptr;
    DTF_pmcf_ARR_TYPE *out_ptr;
    const DTF_pmcf_ARR_TYPE ABS_ERR_TOL = 1e-8;


    printf("RUNNING DTF_pmcf_unit_test\n");

    for (i=0; i<DTF_pmcf_test_nsamples; i++)
    {
        DTF_pmcf_ARR_TYPE error = 0.0;
        in_ptr = DTF_pmcf_get_u0_ptr();
        DTF_pmcf_copy_vec(&DTF_pmcf_test_input_data[i*DTF_pmcf_test_vec_len],
                            in_ptr, DTF_pmcf_test_vec_len);
        DTF_pmcf_execute();
        out_ptr = DTF_pmcf_get_y0_ptr();
        error = DTF_pmcf_calc_error(out_ptr,
                &DTF_pmcf_test_output_data[i*DTF_pmcf_test_vec_len],
                DTF_pmcf_test_vec_len);
        if (error > ABS_ERR_TOL)
        {
            tot_errors++;
            printf("ERROR at index %d=%.6f\n", i, error);
            DTF_pmcf_print_vec(out_ptr, DTF_pmcf_test_vec_len, "out=");
            DTF_pmcf_print_vec(&DTF_pmcf_test_output_data[i*DTF_pmcf_test_vec_len],
                                 DTF_pmcf_test_vec_len, "res=");
        }
    }
    DTF_pmcf_init();

    if (tot_errors > 0) {
        printf("WARNING DTF_pmcf_unit_test FAIL: number of errors=%d out of %d tests\n",
               tot_errors, DTF_pmcf_test_nsamples);
        return 0;
    } else {
        printf("DTF_pmcf_unit_test SUCCESS\n");
        return 1;
    }
}
#endif
