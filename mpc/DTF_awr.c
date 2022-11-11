#include <stdio.h>
#include "DTF_awr.h"

#ifdef SOC_C6678
#include <c6x.h>
#endif
#if (DTF_awr_UNIT_TEST == 1)
#include "DTF_awr_UNIT_TEST.h"
#endif

/* Arrays */
#ifdef SOC_C6678
#pragma DATA_ALIGN(DTF_awr_y0, 64)
#pragma DATA_ALIGN(DTF_awr_y1, 64)
#pragma DATA_ALIGN(DTF_awr_u0, 64)
#pragma DATA_ALIGN(DTF_awr_u1, 64)
#pragma SET_DATA_SECTION(".mpc_awr")
#endif // SOC_C6678
DTF_awr_ARR_TYPE DTF_awr_y0[DTF_awr_LEN] = {(DTF_awr_ARR_TYPE)0.0};
DTF_awr_ARR_TYPE DTF_awr_y1[DTF_awr_LEN] = {(DTF_awr_ARR_TYPE)0.0};
DTF_awr_ARR_TYPE DTF_awr_u0[DTF_awr_LEN] = {(DTF_awr_ARR_TYPE)0.0};
DTF_awr_ARR_TYPE DTF_awr_u1[DTF_awr_LEN] = {(DTF_awr_ARR_TYPE)0.0};
#ifdef SOC_C6678
#pragma SET_DATA_SECTION()
#endif // SOC_C6678


/* Pointers */
#ifdef SOC_C6678
#pragma SET_DATA_SECTION(".mpc_awr")
#endif // SOC_C6678
DTF_awr_ARR_TYPE *DTF_awr_y0_ptr = DTF_awr_y0;
DTF_awr_ARR_TYPE *DTF_awr_y1_ptr = DTF_awr_y1;
DTF_awr_ARR_TYPE *DTF_awr_u0_ptr = DTF_awr_u0;
DTF_awr_ARR_TYPE *DTF_awr_u1_ptr = DTF_awr_u1;
#ifdef SOC_C6678
#pragma SET_DATA_SECTION()
#endif // SOC_C6678


/* Coefficients */
#ifdef SOC_C6678
#pragma SET_DATA_SECTION(".mpc_awr")
#endif // SOC_C6678
DTF_awr_ARR_TYPE DTF_awr_cy1 = (DTF_awr_ARR_TYPE)9.98744152011127095392E-01;
DTF_awr_ARR_TYPE DTF_awr_cu0 = (DTF_awr_ARR_TYPE)6.27923994436371747836E-04;
DTF_awr_ARR_TYPE DTF_awr_cu1 = (DTF_awr_ARR_TYPE)6.27923994436371747836E-04;
#ifdef SOC_C6678
#pragma SET_DATA_SECTION()
#endif // SOC_C6678


DTF_awr_ARR_TYPE* DTF_awr_get_y0_ptr(void)
{
	return DTF_awr_y0_ptr;
}


DTF_awr_ARR_TYPE* DTF_awr_get_u0_ptr(void)
{
	return DTF_awr_u0_ptr;
}


void DTF_awr_swap_y(void)
{
	DTF_awr_ARR_TYPE* tmp_y1_ptr = DTF_awr_y1_ptr;
	DTF_awr_y1_ptr = DTF_awr_y0_ptr;
	DTF_awr_y0_ptr = tmp_y1_ptr;
}


void DTF_awr_swap_u(void)
{
	DTF_awr_ARR_TYPE* tmp_u1_ptr = DTF_awr_u1_ptr;
	DTF_awr_u1_ptr = DTF_awr_u0_ptr;
	DTF_awr_u0_ptr = tmp_u1_ptr;
}


void DTF_awr_execute(void)
{
	int i;
	
	DTF_awr_swap_y();

	for (i=0; i<DTF_awr_LEN; i++)
	{
		DTF_awr_y0_ptr[i] = DTF_awr_sat(
			+ DTF_awr_cy1 * DTF_awr_y1_ptr[i]
			+ DTF_awr_cu0 * DTF_awr_u0_ptr[i]
			+ DTF_awr_cu1 * DTF_awr_u1_ptr[i], DTF_awr_MAXVAL);
	}

	DTF_awr_swap_u();
}


void DTF_awr_init(void)
{
	int i;

	for (i=0; i<DTF_awr_LEN; i++)
	{
		DTF_awr_y0_ptr[i] = 0.0;
		DTF_awr_y1_ptr[i] = 0.0;
		DTF_awr_u0_ptr[i] = 0.0;
		DTF_awr_u1_ptr[i] = 0.0;
	}
}

#if (DTF_awr_UNIT_TEST == 1)
float DTF_awr_calc_error(const float *in1, const float* in2, const int len)
{
    int i;
    float error = 0.0;

    for (i=0; i<len; i++)
        error += (in1[i]-in2[i]) * (in1[i]-in2[i]);
    return error;
}


void DTF_awr_copy_vec(const float *in, float *out, const int len)
{
    int i;
    for (i=0; i<len; i++)
        out[i] = in[i];
}


void DTF_awr_print_vec(const float *in, const int len, const char *name)
{
    int i;
    printf("%s=[", name);
    for (i=0; i<len; i++)
        printf("%.8f,", in[i]);
    printf("]\n");
}


int DTF_awr_unit_test(void)
{
    int i;
    int tot_errors = 0;
    DTF_awr_ARR_TYPE *in_ptr;
    DTF_awr_ARR_TYPE *out_ptr;
    const DTF_awr_ARR_TYPE ABS_ERR_TOL = 1e-8;


    printf("RUNNING DTF_awr_unit_test\n");

    for (i=0; i<DTF_awr_test_nsamples; i++)
    {
        DTF_awr_ARR_TYPE error = 0.0;
        in_ptr = DTF_awr_get_u0_ptr();
        DTF_awr_copy_vec(&DTF_awr_test_input_data[i*DTF_awr_test_vec_len],
                            in_ptr, DTF_awr_test_vec_len);
        DTF_awr_execute();
        out_ptr = DTF_awr_get_y0_ptr();
        error = DTF_awr_calc_error(out_ptr,
                &DTF_awr_test_output_data[i*DTF_awr_test_vec_len],
                DTF_awr_test_vec_len);
        if (error > ABS_ERR_TOL)
        {
            tot_errors++;
            printf("ERROR at index %d=%.6f\n", i, error);
            DTF_awr_print_vec(out_ptr, DTF_awr_test_vec_len, "out=");
            DTF_awr_print_vec(&DTF_awr_test_output_data[i*DTF_awr_test_vec_len],
                                 DTF_awr_test_vec_len, "res=");
        }
    }
    DTF_awr_init();

    if (tot_errors > 0) {
        printf("WARNING DTF_awr_unit_test FAIL: number of errors=%d out of %d tests\n",
               tot_errors, DTF_awr_test_nsamples);
        return 0;
    } else {
        printf("DTF_awr_unit_test SUCCESS\n");
        return 1;
    }
}
#endif
