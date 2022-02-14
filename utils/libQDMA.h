/*
 * libQDMA.h
 *
 *  Created on: Dec 11, 2020
 *      Author: idris
 */

#ifndef LIBQDMA_H_
#define LIBQDMA_H_

#include <stdio.h>
#include <xdc/std.h>


/*
 * ENUM LIBQDMA_STATUS
 * Defines status values for setup/transfer functions
 */
typedef enum
{
    LIBQDMA_SUCCESS         = 0,
    LIBQDMA_ERROR_ARR_SIZE  = 1,
    LIBQDMA_ERROR_ANY       = 2

} LIBQDMA_STATUS;


/*
 * TYPE LIBQDMA_ARR_TYPE
 * Array type hard-coded here
 */
typedef int LIBQDMA_ARR_TYPE;


/*
 * ARRAY_TYPE* LIBQDMA_getGlobalAddr
 * Use to transform a local address to a global one when
 * calling LIBQDMA_setup
 */
LIBQDMA_ARR_TYPE* LIBQDMA_getGlobalAddr(LIBQDMA_ARR_TYPE* addr);


/*
 * LIBQDMA_STATUS LIBQDMA_init
 * Sets up one QDMA transfer. If transfer parameters are changed
 * it is required to call this function again.
 */
LIBQDMA_STATUS LIBQDMA_init(
        uint32_t arr_len, // length of array
        LIBQDMA_ARR_TYPE *src, // points to start of source array
        LIBQDMA_ARR_TYPE *dst // points to start of destination array
        );


/*
 * LIBQDMA_STATUS LIBQDMA_init_AB
 * Sets up arr_num QDMA transfers with Acnt=arr_len*sizeof(LIBQDMA_ARR_TYPE)
 * and Ccnt=1. Total length of array = arr_num*arr_len
 * If transfer parameters are changed
 * it is required to call this function again. *
 */
LIBQDMA_STATUS LIBQDMA_init_AB(
        uint32_t arr_len, // length of array
        uint32_t arr_num, // number of arrays
        LIBQDMA_ARR_TYPE *src, // points to start of source array
        LIBQDMA_ARR_TYPE *dst // points to start of destination array
        );


/*
 * LIBQDMA_STATUS LIBQDMA_change_transfer_params_AB
 * Changes the provided transfer parameters
 */
LIBQDMA_STATUS LIBQDMA_change_transfer_params_AB(
        uint32_t arr_len, // length of array
        uint32_t arr_num, // number of arrays
        LIBQDMA_ARR_TYPE *src, // points to start of source array
        LIBQDMA_ARR_TYPE *dst // points to start of destination array
        );


void LIBQDMA_print_parameters(void);

/*
 * LIBQDMA_STATUS LIBQDMA_trigger_and_wait
 * Trigger QDMA transfer and wait for completion
 */
LIBQDMA_STATUS LIBQDMA_trigger_and_wait(void);


/*
 * LIBQDMA_STATUS LIBQDMA_stop
 * Frees QDMA channels
 */
LIBQDMA_STATUS LIBQDMA_stop(void);




/*** DO NOT MODIFY ***/

/* Max byte transfer count */
#define LIBQDMA_MAX_BYTE_COUNT (65535)

#endif /* LIBQDMA_H_ */
