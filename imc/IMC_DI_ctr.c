#include <c6x.h>
#include <ti/csl/csl_chip.h>
#include <csl_cache.h>
#include <csl_cacheAux.h>

#include "DTF_IMC_DI.h"
#include "IMC_DI_ctr.h"
#include "ipc_utils.h"
#if (IMC_DI_XDIR == 1)
#include "IMC_DI_gain_mc_x.h"
#if (IMC_DI_UNIT_TESTS == 1)
#include "IMC_DI_UNIT_TEST_mc_x.h"
#endif
#else
#include "IMC_DI_gain_mc_y.h"
#if (IMC_DI_UNIT_TESTS == 1)
#include "IMC_DI_UNIT_TEST_mc_y.h"
#endif
#endif

#pragma DATA_ALIGN(ctr_input,   IMC_DI_ARRAY_ALIGN)
#pragma DATA_ALIGN(measurements,   IMC_DI_ARRAY_ALIGN)
#pragma SET_DATA_SECTION(".imc_di_shared")
volatile imc_float ctr_input[IMC_DI_DIM]; // ctr_input = gain matrix x measurements
volatile imc_float measurements[IMC_DI_DIM];
#pragma SET_DATA_SECTION()

#pragma DATA_ALIGN(mat_local,   IMC_DI_ARRAY_ALIGN)
#pragma SET_DATA_SECTION(".imc_di_local")
imc_float mat_local[IMC_DI_SIZE_IN_MAT_LOCAL];
Uint32 volatile IMC_DI_selfId;
#pragma SET_DATA_SECTION()

static void copy_vec(const imc_float *in, imc_float *out, const int len)
{
    int i;
    _nassert((int) in % IMC_DI_ARRAY_ALIGN == 0);
    _nassert((int) out % IMC_DI_ARRAY_ALIGN == 0);
    for (i=0; i<len; i++)
        out[i] = in[i];
}

static void init_worker(Uint32 selfId)
{
    IMC_DI_selfId = selfId;
    copy_vec(&IMC_DI_gain_mat[(selfId-1) * IMC_DI_SIZE_IN_MAT_LOCAL], mat_local, IMC_DI_SIZE_IN_MAT_LOCAL);
}

static void mat_mpy(const imc_float * in_mat, const imc_float * in_vec, imc_float * out_vec)
{
	int i, j;
	const imc_float * in_mat_ptr = &in_mat[0];

    _nassert((int) in_mat % IMC_DI_ARRAY_ALIGN == 0);
    _nassert((int) in_vec % IMC_DI_ARRAY_ALIGN == 0);
    _nassert((int) out_vec % IMC_DI_ARRAY_ALIGN == 0);

#pragma MUST_ITERATE(IMC_DI_W_NROWS, IMC_DI_W_NROWS)
	for (i = 0; i < IMC_DI_W_NROWS; i++)
	{
		imc_float row_res = 0.0;
#pragma MUST_ITERATE(IMC_DI_W_NCOLS, IMC_DI_W_NCOLS)
		for (j = 0; j < IMC_DI_W_NCOLS; j++)
		{
			row_res += in_mat_ptr[j] * in_vec[j];
		}
		out_vec[i] = row_res;
		in_mat_ptr += IMC_DI_W_NCOLS;
	}
}

imc_float * IMC_DI_get_input(void)
{
    return (imc_float *)measurements;
}


void IMC_DI_ctr_worker(Uint32 selfId)
{
    int ind_shift = (selfId - 1) * IMC_DI_W_NROWS;
    init_worker(selfId);
    while (1)
    {
        ipc_slave_wait_req(); // ML 0
        CACHE_invL1d ((void *) &measurements[0], IMC_DI_BYTES_GLOBAL_ARRAYS, CACHE_FENCE_WAIT);
        mat_mpy((const imc_float *)&mat_local[0], (const imc_float *)measurements,
                (imc_float *)&ctr_input[ind_shift]);
        CACHE_wbL1d ((void *) &ctr_input[ind_shift], IMC_DI_BYTES_WORKER_ARRAYS, CACHE_FENCE_WAIT);
        ipc_slave_set_ack(1); // ML 0
    }
}


imc_float * IMC_DI_ctr(void)
{

    /* Matrix-vector multiplication */
    CACHE_wbL1d ((void *) &measurements[0], IMC_DI_BYTES_GLOBAL_ARRAYS, CACHE_FENCE_WAIT);
    ipc_master_set_req(1); // ML 0
    //mat_mpy(&IMC_DI_gain_mat[0], (const imc_float *)out_ptr, &ctr_input[0], IMC_DI_NU, IMC_DI_NY);
    ipc_master_wait_ack();
    CACHE_invL1d ((void *) &ctr_input[0], IMC_DI_BYTES_GLOBAL_ARRAYS, CACHE_FENCE_WAIT);

    /* Filter */
    copy_vec((imc_float *)ctr_input, (imc_float *)DTF_IMC_DI_get_u0_ptr(), IMC_DI_NU);
    DTF_IMC_DI_execute();

    return (imc_float *)DTF_IMC_DI_get_y0_ptr();
}


#if (IMC_DI_UNIT_TESTS == 1)
int IMC_DI_unit_test(void)
{
    int i;
    float error = 0.0;
    const float ABS_ERR_LIM = 1e-6;

    printf("RUNNING IMC_DI_unit_test\n");

    copy_vec(IMC_DI_test_in, (imc_float *)measurements, IMC_DI_NY);
    CACHE_wbL1d ((void *) &measurements[0], IMC_DI_BYTES_GLOBAL_ARRAYS, CACHE_FENCE_WAIT);

    ipc_master_set_req(1); // ML 0
    //mat_mpy(&IMC_DI_gain_mat[0], (const imc_float *)out_ptr, &ctr_input[0], IMC_DI_NU, IMC_DI_NY);
    ipc_master_wait_ack();
    CACHE_invL1d ((void *) &ctr_input[0], IMC_DI_BYTES_GLOBAL_ARRAYS, CACHE_FENCE_WAIT);

    for (i=0; i<IMC_DI_NU; i++)
        error += (ctr_input[i] - IMC_DI_test_out[i]) * (ctr_input[i] - IMC_DI_test_out[i]);

    if (error > ABS_ERR_LIM) {
#if (PRINT_DEBUG == 1)
        for (i=0; i<10; i++)
            printf("%d: sol=%.4f, out=%.4f\n", i, IMC_DI_test_out[i], ctr_input[i]);
#endif
        printf("WARNING IMC_DI_unit_test FAIL: error=%.4f > ABS_ERR_LIM=%.12f\n", error, ABS_ERR_LIM);
        return 0;
    } else {
        printf("IMC_DI_unit_test SUCCESS\n");
        return 1;
    }
}
#endif

