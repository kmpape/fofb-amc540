#include "DTF_qs.h"

#ifdef SOC_C6678
#include <c6x.h>
#endif
#if (DTF_qs_UNIT_TEST == 1)
#include "DTF_qs_UNIT_TEST.h"
#endif

/* Arrays */
#ifdef SOC_C6678
#pragma DATA_ALIGN(DTF_qs_y0, 64)
#pragma DATA_ALIGN(DTF_qs_y1, 64)
#pragma DATA_ALIGN(DTF_qs_y2, 64)
#pragma DATA_ALIGN(DTF_qs_y3, 64)
#pragma DATA_ALIGN(DTF_qs_y4, 64)
#pragma DATA_ALIGN(DTF_qs_u0, 64)
#pragma DATA_ALIGN(DTF_qs_u1, 64)
#pragma DATA_ALIGN(DTF_qs_u2, 64)
#pragma DATA_ALIGN(DTF_qs_u3, 64)
#pragma DATA_ALIGN(DTF_qs_u4, 64)
#pragma SET_DATA_SECTION(".gsvd_qs")
#endif // SOC_C6678
DTF_qs_ARR_TYPE DTF_qs_y0[DTF_qs_LEN] = {(DTF_qs_ARR_TYPE)0.0};
DTF_qs_ARR_TYPE DTF_qs_y1[DTF_qs_LEN] = {(DTF_qs_ARR_TYPE)0.0};
DTF_qs_ARR_TYPE DTF_qs_y2[DTF_qs_LEN] = {(DTF_qs_ARR_TYPE)0.0};
DTF_qs_ARR_TYPE DTF_qs_y3[DTF_qs_LEN] = {(DTF_qs_ARR_TYPE)0.0};
DTF_qs_ARR_TYPE DTF_qs_y4[DTF_qs_LEN] = {(DTF_qs_ARR_TYPE)0.0};
DTF_qs_ARR_TYPE DTF_qs_u0[DTF_qs_LEN] = {(DTF_qs_ARR_TYPE)0.0};
DTF_qs_ARR_TYPE DTF_qs_u1[DTF_qs_LEN] = {(DTF_qs_ARR_TYPE)0.0};
DTF_qs_ARR_TYPE DTF_qs_u2[DTF_qs_LEN] = {(DTF_qs_ARR_TYPE)0.0};
DTF_qs_ARR_TYPE DTF_qs_u3[DTF_qs_LEN] = {(DTF_qs_ARR_TYPE)0.0};
DTF_qs_ARR_TYPE DTF_qs_u4[DTF_qs_LEN] = {(DTF_qs_ARR_TYPE)0.0};
#ifdef SOC_C6678
#pragma SET_DATA_SECTION()
#endif // SOC_C6678


/* Pointers */
#ifdef SOC_C6678
#pragma SET_DATA_SECTION(".gsvd_qs")
#endif // SOC_C6678
DTF_qs_ARR_TYPE *DTF_qs_y0_ptr = DTF_qs_y0;
DTF_qs_ARR_TYPE *DTF_qs_y1_ptr = DTF_qs_y1;
DTF_qs_ARR_TYPE *DTF_qs_y2_ptr = DTF_qs_y2;
DTF_qs_ARR_TYPE *DTF_qs_y3_ptr = DTF_qs_y3;
DTF_qs_ARR_TYPE *DTF_qs_y4_ptr = DTF_qs_y4;
DTF_qs_ARR_TYPE *DTF_qs_u0_ptr = DTF_qs_u0;
DTF_qs_ARR_TYPE *DTF_qs_u1_ptr = DTF_qs_u1;
DTF_qs_ARR_TYPE *DTF_qs_u2_ptr = DTF_qs_u2;
DTF_qs_ARR_TYPE *DTF_qs_u3_ptr = DTF_qs_u3;
DTF_qs_ARR_TYPE *DTF_qs_u4_ptr = DTF_qs_u4;
#ifdef SOC_C6678
#pragma SET_DATA_SECTION()
#endif // SOC_C6678


/* Coefficients */
#ifdef SOC_C6678
#pragma SET_DATA_SECTION(".gsvd_qs")
#endif // SOC_C6678
DTF_qs_ARR_TYPE DTF_qs_cy1 = (DTF_qs_ARR_TYPE)3.9943512468013100;
DTF_qs_ARR_TYPE DTF_qs_cy2 = (DTF_qs_ARR_TYPE)-5.9830635921697510;
DTF_qs_ARR_TYPE DTF_qs_cy3 = (DTF_qs_ARR_TYPE)3.9830734372540126;
DTF_qs_ARR_TYPE DTF_qs_cy4 = (DTF_qs_ARR_TYPE)-0.9943610918871258;
DTF_qs_ARR_TYPE DTF_qs_cu0 = (DTF_qs_ARR_TYPE)0.0000000000000000;
DTF_qs_ARR_TYPE DTF_qs_cu1 = (DTF_qs_ARR_TYPE)0.0000000022018152;
DTF_qs_ARR_TYPE DTF_qs_cu2 = (DTF_qs_ARR_TYPE)-0.0000000020966603;
DTF_qs_ARR_TYPE DTF_qs_cu3 = (DTF_qs_ARR_TYPE)-0.0000000022470842;
DTF_qs_ARR_TYPE DTF_qs_cu4 = (DTF_qs_ARR_TYPE)0.0000000021434835;
#ifdef SOC_C6678
#pragma SET_DATA_SECTION()
#endif // SOC_C6678


DTF_qs_ARR_TYPE* DTF_qs_get_y0_ptr(void)
{
	return DTF_qs_y0_ptr;
}


DTF_qs_ARR_TYPE* DTF_qs_get_u0_ptr(void)
{
	return DTF_qs_u0_ptr;
}


void DTF_qs_swap_y(void)
{
	DTF_qs_ARR_TYPE* tmp_y4_ptr = DTF_qs_y4_ptr;
	DTF_qs_y4_ptr = DTF_qs_y3_ptr;
	DTF_qs_y3_ptr = DTF_qs_y2_ptr;
	DTF_qs_y2_ptr = DTF_qs_y1_ptr;
	DTF_qs_y1_ptr = DTF_qs_y0_ptr;
	DTF_qs_y0_ptr = tmp_y4_ptr;
}


void DTF_qs_swap_u(void)
{
	DTF_qs_ARR_TYPE* tmp_u4_ptr = DTF_qs_u4_ptr;
	DTF_qs_u4_ptr = DTF_qs_u3_ptr;
	DTF_qs_u3_ptr = DTF_qs_u2_ptr;
	DTF_qs_u2_ptr = DTF_qs_u1_ptr;
	DTF_qs_u1_ptr = DTF_qs_u0_ptr;
	DTF_qs_u0_ptr = tmp_u4_ptr;
}


void DTF_qs_execute(void)
{
	int i;
	const DTF_qs_ARR_TYPE maxval = 10000.0;

	DTF_qs_swap_y();

	for (i=0; i<DTF_qs_LEN; i++)
	{
		DTF_qs_y0_ptr[i] = DTF_qs_sat(
			+ DTF_qs_cy1 * DTF_qs_y1_ptr[i]
			+ DTF_qs_cy2 * DTF_qs_y2_ptr[i]
			+ DTF_qs_cy3 * DTF_qs_y3_ptr[i]
			+ DTF_qs_cy4 * DTF_qs_y4_ptr[i]
			//+ DTF_qs_cu0 * DTF_qs_u0_ptr[i]//coefficient is zero
			+ DTF_qs_cu1 * DTF_qs_u1_ptr[i]
			+ DTF_qs_cu2 * DTF_qs_u2_ptr[i]
			+ DTF_qs_cu3 * DTF_qs_u3_ptr[i]
			+ DTF_qs_cu4 * DTF_qs_u4_ptr[i], maxval);
	}

	DTF_qs_swap_u();
}


void DTF_qs_init(void)
{
	int i;

	for (i=0; i<DTF_qs_LEN; i++)
	{
		DTF_qs_y0_ptr[i] = 0.0;
		DTF_qs_y1_ptr[i] = 0.0;
		DTF_qs_y2_ptr[i] = 0.0;
		DTF_qs_y3_ptr[i] = 0.0;
		DTF_qs_y4_ptr[i] = 0.0;
		DTF_qs_u0_ptr[i] = 0.0;
		DTF_qs_u1_ptr[i] = 0.0;
		DTF_qs_u2_ptr[i] = 0.0;
		DTF_qs_u3_ptr[i] = 0.0;
		DTF_qs_u4_ptr[i] = 0.0;
	}
}

#if (DTF_qs_UNIT_TEST == 1)
float DTF_qs_calc_error(const float *in1, const float* in2, const int len)
{
    int i;
    float error = 0.0;

    for (i=0; i<len; i++)
        error += (in1[i]-in2[i]) * (in1[i]-in2[i]);
    return error;
}


void DTF_qs_copy_vec(const float *in, float *out, const int len)
{
    int i;
    for (i=0; i<len; i++)
        out[i] = in[i];
}


void DTF_qs_print_vec(const float *in, const int len, const char *name)
{
    int i;
    printf("%s=[", name);
    for (i=0; i<len; i++)
        printf("%.8f,", in[i]);
    printf("]\n");
}


int DTF_qs_unit_test(void)
{
    int i;
    int tot_errors = 0;
    DTF_qs_ARR_TYPE *in_ptr;
    DTF_qs_ARR_TYPE *out_ptr;
    const DTF_qs_ARR_TYPE ABS_ERR_TOL = 1e-8;


    printf("RUNNING DTF_qs_unit_test\n");

    for (i=0; i<DTF_qs_test_nsamples; i++)
    {
        DTF_qs_ARR_TYPE error = 0.0;
        in_ptr = DTF_qs_get_u0_ptr();
        DTF_qs_copy_vec(&DTF_qs_test_input_data[i*DTF_qs_test_vec_len],
                            in_ptr, DTF_qs_test_vec_len);
        DTF_qs_execute();
        out_ptr = DTF_qs_get_y0_ptr();
        error = DTF_qs_calc_error(out_ptr,
                &DTF_qs_test_output_data[i*DTF_qs_test_vec_len],
                DTF_qs_test_vec_len);
        if (error > ABS_ERR_TOL)
        {
            tot_errors++;
            printf("ERROR at index %d=%.6f\n", i, error);
            DTF_qs_print_vec(out_ptr, DTF_qs_test_vec_len, "out=");
            DTF_qs_print_vec(&DTF_qs_test_output_data[i*DTF_qs_test_vec_len],
                                 DTF_qs_test_vec_len, "res=");
        }
    }
    DTF_qs_init();

    if (tot_errors > 0) {
        printf("WARNING DTF_qs_unit_test FAIL: number of errors=%d out of %d tests\n",
               tot_errors, DTF_qs_test_nsamples);
        return 0;
    } else {
        printf("DTF_qs_unit_test SUCCESS\n");
        return 1;
    }
}
#endif
