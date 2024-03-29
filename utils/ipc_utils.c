#include <c6x.h>
#include <ti/csl/csl.h>
#include <ti/csl/csl_cache.h>
#include <ti/csl/csl_cacheAux.h>
#include <ti/csl/csl_xmc.h>
#include <ti/csl/csl_chip.h>
#include "ipc_utils.h"
#ifdef IPC_ASSERTS
#include <assert.h>
#endif
#ifdef USEMULTIPROC
#include <ti/ipc/MultiProc.h>
#else
#ifndef USECSLDNUM
extern uint32_t get_corenum();
#endif
#endif

/****************************************************
 * Flags per slave:                                 *
 * request_i: 0 -> 1 (master), 1 -> 0 (slave_i)     *
 * acknowledge_i: 0 -> 1 (slave_i), 1 -> 0 (master) *
 * ncalls: for terminating the loop                 *
 ****************************************************/
/* Slave 1 */
#pragma DATA_SECTION (request_1,     ".ipc_nocache_section");
int volatile request_1 = 0;
#pragma DATA_SECTION (acknowledge_1, ".ipc_nocache_section");
int volatile acknowledge_1 = 0;
#pragma DATA_SECTION (ncalls_1,      ".ipc_nocache_section"); //".ipc_shared_section_1")
int volatile ncalls_1 = 0;
#pragma DATA_SECTION (selfId_1,      ".ipc_shared_section")
volatile const int selfId_1 = 1;
#pragma DATA_SECTION (is_alive_1,    ".ipc_nocache_section")
volatile int is_alive_1 = 0;

/* Slave 2 */
#if NUMSLAVES >= 2
#pragma DATA_SECTION (request_2,     ".ipc_nocache_section");
int volatile request_2 = 0;
#pragma DATA_SECTION (acknowledge_2, ".ipc_nocache_section");
int volatile acknowledge_2 = 0;
#pragma DATA_SECTION (ncalls_2,      ".ipc_nocache_section");
int volatile ncalls_2 = 0;
#pragma DATA_SECTION (selfId_2,      ".ipc_shared_section");
volatile const int selfId_2 = 2;
#pragma DATA_SECTION (is_alive_2,    ".ipc_nocache_section")
volatile int is_alive_2 = 0;
#endif

/* Slave 3 */
#if NUMSLAVES >= 3
#pragma DATA_SECTION (request_3,     ".ipc_nocache_section");
int volatile request_3 = 0;
#pragma DATA_SECTION (acknowledge_3, ".ipc_nocache_section");
int volatile acknowledge_3 = 0;
#pragma DATA_SECTION (ncalls_3,      ".ipc_nocache_section");
int volatile ncalls_3 = 0;
#pragma DATA_SECTION (selfId_3,      ".ipc_shared_section");
volatile const int selfId_3 = 3;
#pragma DATA_SECTION (is_alive_3,    ".ipc_nocache_section")
volatile int is_alive_3 = 0;
#endif

/* Slave 4 */
#if NUMSLAVES >= 4
#pragma DATA_SECTION (request_4,     ".ipc_nocache_section");
int volatile request_4 = 0;
#pragma DATA_SECTION (acknowledge_4, ".ipc_nocache_section");
int volatile acknowledge_4 = 0;
#pragma DATA_SECTION (ncalls_4,      ".ipc_nocache_section");
int volatile ncalls_4 = 0;
#pragma DATA_SECTION (selfId_4,      ".ipc_shared_section");
volatile const int selfId_4 = 4;
#pragma DATA_SECTION (is_alive_4,    ".ipc_nocache_section")
volatile int is_alive_4 = 0;
#endif

/* Slave 5 */
#if NUMSLAVES >= 5
#pragma DATA_SECTION (request_5,     ".ipc_nocache_section");
int volatile request_5 = 0;
#pragma DATA_SECTION (acknowledge_5, ".ipc_nocache_section");
int volatile acknowledge_5 = 0;
#pragma DATA_SECTION (ncalls_5,      ".ipc_nocache_section");
int volatile ncalls_5 = 0;
#pragma DATA_SECTION (selfId_5,      ".ipc_shared_section");
volatile const int selfId_5 = 5;
#pragma DATA_SECTION (is_alive_5,    ".ipc_nocache_section")
volatile int is_alive_5 = 0;
#endif

/* Slave 6 */
#if NUMSLAVES >= 6
#pragma DATA_SECTION (request_6,     ".ipc_nocache_section");
int volatile request_6 = 0;
#pragma DATA_SECTION (acknowledge_6, ".ipc_nocache_section");
int volatile acknowledge_6 = 0;
#pragma DATA_SECTION (ncalls_6,      ".ipc_nocache_section");
int volatile ncalls_6 = 0;
#pragma DATA_SECTION (selfId_6,      ".ipc_shared_section");
volatile const int selfId_6 = 6;
#pragma DATA_SECTION (is_alive_6,    ".ipc_nocache_section")
volatile int is_alive_6 = 0;
#endif

/* Slave 7 */
#if NUMSLAVES >= 7
#pragma DATA_SECTION (request_7, ".ipc_nocache_section");
int volatile request_7 = 0;
#pragma DATA_SECTION (acknowledge_7, ".ipc_nocache_section");
int volatile acknowledge_7 = 0;
#pragma DATA_SECTION (ncalls_7, ".ipc_nocache_section");
int volatile ncalls_7 = 0;
#pragma DATA_SECTION (selfId_7, ".ipc_shared_section");
volatile const int selfId_7 = 7;
#pragma DATA_SECTION (is_alive_7, ".ipc_nocache_section")
volatile int is_alive_7 = 0;
#endif

/* Pointers to flags, initialised by slaves */
#pragma DATA_SECTION(req_flag,   ".ipc_local_data")
int volatile * volatile req_flag = NULL;

#pragma DATA_SECTION(ack_flag,   ".ipc_local_data")
int volatile * volatile ack_flag = NULL;

#pragma DATA_SECTION(ncalls,     ".ipc_local_data")
int volatile * volatile ncalls = NULL;

#pragma DATA_SECTION(ipc_selfId, ".ipc_local_data")
const int volatile * volatile ipc_selfId = NULL;

#pragma DATA_SECTION(local_selfId, ".ipc_local_data")
Uint32 volatile local_selfId;

#pragma DATA_SECTION(n_req,     ".ipc_local_data")
volatile int n_req = 0;

#pragma DATA_SECTION(n_ack,     ".ipc_local_data")
volatile int n_ack = 0;

/* Prototypes */
int volatile * _get_ncalls_var(Uint32 volatile selfId);
int volatile * _get_req_flag(Uint32 volatile selfId);
int volatile * _get_ack_flag(Uint32 volatile selfId);
const int volatile * _get_selfId_var(Uint32 volatile selfId);
void _set_slave_i_is_alive(Uint32 volatile slaveId);

#ifdef IPC_ASSERTS
void _assert_ptrs(void) {
    assert(req_flag);
    assert(ack_flag);
    assert(ncalls);
}
#endif


void ipc_slave_init(Uint32 volatile selfId) {
    Uint32 this_selfId;
    /* If we get selfId=0, swap with master core ID */
    if (selfId == 0) {
        this_selfId = IPC_MASTER_CORENUM;
    } else {
        this_selfId = local_selfId;
    }
#ifdef IPC_ASSERTS
    assert(selfId > 0);
#endif
    req_flag = _get_req_flag(this_selfId);
    ack_flag = _get_ack_flag(this_selfId);
    ncalls   = _get_ncalls_var(this_selfId);
    ipc_selfId = _get_selfId_var(this_selfId);
#if IPC_DEBUGLEVEL >= 4
    printf("core_%d: assigned selfId = %d\n", selfId, *ipc_selfId);
    printf("core_%d: &req_flag = %x, &req_flag_ptr = %d\n", selfId, req_flag, &req_flag);
    printf("core_%d: &ack_flag = %x, &ack_flag_ptr = %x\n", selfId, ack_flag, &ack_flag);
    printf("core_%d: &ncalls   = %x, &ncalls_ptr   = %x\n", selfId, ncalls, &ncalls);
#endif
#ifdef IPC_ASSERTS
    /* Check if pointers have been assigned */
    assert(req_flag);
    assert(ack_flag);
    assert(ncalls);
    assert(ipc_selfId);
    assert(*ipc_selfId == this_selfId);
#endif
    /* Reset ncalls in case the DSP was restarted */
    ipc_slave_reset_num_requests();
    _set_slave_i_is_alive(this_selfId);
#ifdef IPC_ASSERTS
    assert(*ncalls == 0);
    /* Check if pointers have been assigned */
    assert(req_flag != NULL);
    assert(ack_flag != NULL);
    assert(ncalls != NULL);
    assert(ipc_selfId != NULL);
    assert(*ipc_selfId == this_selfId);
#endif
}

void ipc_slave_init2(void) {
    unsigned int restore_val;
    Uint32 this_selfId;
#ifdef USECSLDNUM
    restore_val = _disable_interrupts();
    local_selfId = CSL_chipReadReg(CSL_CHIP_DNUM);
    _restore_interrupts(restore_val);
#else
    local_selfId = get_corenum();
#endif
    /* If we get selfId=0, swap with master core ID */
    if (local_selfId == 0) {
        this_selfId = IPC_MASTER_CORENUM;
    } else {
        this_selfId = local_selfId;
    }
#ifdef IPC_ASSERTS
    assert(this_selfId > 0);
    assert(this_selfId <= 7);
#endif
    req_flag = _get_req_flag(this_selfId);
    ack_flag = _get_ack_flag(this_selfId);
    ncalls   = _get_ncalls_var(this_selfId);
    ipc_selfId = _get_selfId_var(this_selfId);
#if IPC_DEBUGLEVEL >= 4
    printf("core_%d: assigned selfId = %d\n", selfId, *ipc_selfId);
    printf("core_%d: &req_flag = %x, &req_flag_ptr = %d\n", selfId, req_flag, &req_flag);
    printf("core_%d: &ack_flag = %x, &ack_flag_ptr = %x\n", selfId, ack_flag, &ack_flag);
    printf("core_%d: &ncalls   = %x, &ncalls_ptr   = %x\n", selfId, ncalls, &ncalls);
#endif
#ifdef IPC_ASSERTS
    /* Check if pointers have been assigned */
    assert(req_flag);
    assert(ack_flag);
    assert(ncalls);
    assert(ipc_selfId);
    assert(*ipc_selfId == this_selfId);
#endif
    /* Reset in case the DSP was restarted */
    ipc_slave_reset_req();
    ipc_slave_reset_num_requests();
    _set_slave_i_is_alive(this_selfId);
#ifdef IPC_ASSERTS
    assert(*ncalls == 0);
    /* Check if pointers have been assigned */
    assert(req_flag != NULL);
    assert(ack_flag != NULL);
    assert(ncalls != NULL);
    assert(ipc_selfId != NULL);
    assert(*ipc_selfId == local_selfId);
#endif
    n_ack = 0;
    n_req = 0;
}


int ipc_slave_get_selfId(void) {
    return (*ipc_selfId);
}


int ipc_slave_wait_req(void) {
    int req_val;
    unsigned int restore_val;
#ifdef IPC_ASSERTS
    /* Check if pointers have been assigned */
    assert(req_flag);
    assert(ack_flag);
    assert(ncalls);
#endif
#if IPC_DEBUGLEVEL >= 4
    printf("s: waiting for req %d\n", *ncalls);
#endif
    restore_val = _disable_interrupts();
    //while (*req_flag == 0);
    while ((*req_flag != 1) && (*req_flag != 2));
    req_val = *req_flag;
    _restore_interrupts(restore_val);
    *ncalls = *ncalls + 1;
#if IPC_DEBUGLEVEL >= 4
    printf("s: req %d received\n", *ncalls);
#endif
    restore_val = _disable_interrupts();
    ipc_slave_reset_req();
    _restore_interrupts(restore_val);
    n_req++;
    return req_val;
}


void ipc_slave_reset_req(void) {
#ifdef IPC_ASSERTS
    /* Check if pointers have been assigned */
    assert(req_flag != NULL);
    assert(ack_flag != NULL);
    assert(ncalls != NULL);
#endif
    *req_flag = 0;
}


void ipc_slave_set_ack(int ack_val) {
    unsigned int restore_val;
#ifdef IPC_ASSERTS
    /* Check if pointers have been assigned */
    assert(req_flag);
    assert(ack_flag);
    assert(ncalls);
#endif
#if IPC_DEBUGLEVEL >= 4
    printf("s: ack req %d\n", *ncalls - 1);
#endif
    restore_val = _disable_interrupts();
    *ack_flag = ack_val;
    _restore_interrupts(restore_val);
    n_ack++;
}


int ipc_slave_get_num_requests(void) {
    return *ncalls;
}


void ipc_slave_reset_num_requests(void) {
    *ncalls = 0;
}


void ipc_master_init(void) {
    ipc_master_reset_ack();
    //ipc_master_set_req(0); now in slave init
    n_ack = 0;
    n_req = 0;
}


void ipc_master_reset_req(void) {
    ipc_master_set_req(0);
}


void ipc_master_set_req(int req_val) {
    unsigned int restore_val;
    restore_val = _disable_interrupts();
    request_1 = req_val;
#if NUMSLAVES >= 2
    request_2 = req_val;
#endif
#if NUMSLAVES >= 3
    request_3 = req_val;
#endif
#if NUMSLAVES >= 4
    request_4 = req_val;
#endif
#if NUMSLAVES >= 5
    request_5 = req_val;
#endif
#if NUMSLAVES >= 6
    request_6 = req_val;
#endif
#if NUMSLAVES >= 7
    request_7 = req_val;
#endif
    _restore_interrupts(restore_val);

    n_req++;
}


void ipc_master_set_req_slave_i(int req_val, Uint32 slaveId) {
    unsigned int restore_val;
#ifdef IPC_ASSERTS
    assert(slaveId <= NUMSLAVES);
    assert(slaveId > 0);
#endif
    restore_val = _disable_interrupts();
    if (slaveId == 1) {
        request_1 = req_val;
        n_req++;
#if NUMSLAVES >= 2
    } else if (slaveId == 2) {
        request_2 = req_val;
#endif
#if NUMSLAVES >= 3
    } else if (slaveId == 3) {
        request_3 = req_val;
#endif
#if NUMSLAVES >= 4
    } else if (slaveId == 4) {
        request_4 = req_val;
#endif
#if NUMSLAVES >= 5
    } else if (slaveId == 5) {
        request_5 = req_val;
#endif
#if NUMSLAVES >= 6
    } else if (slaveId == 6) {
        request_6 = req_val;
#endif
#if NUMSLAVES >= 7
    } else if (slaveId == 7) {
        request_7 = req_val;
#endif
    } else {
#ifdef IPC_ASSERTS
        assert(0);
#endif
    }
    _restore_interrupts(restore_val);
}


void ipc_master_wait_for_slaves_after_init(void) {
    unsigned int restore_val;
    restore_val = _disable_interrupts();
#if IPC_DEBUGLEVEL >= 4
    printf("m: waiting for slave 1\n");
#endif
    while (is_alive_1 == 0);
#if NUMSLAVES >= 2
#if IPC_DEBUGLEVEL >= 4
    printf("m: waiting for slave 2\n");
#endif
    while (is_alive_2 == 0);
#endif
#if NUMSLAVES >= 3
#if IPC_DEBUGLEVEL >= 4
    printf("m: waiting for slave 3\n");
#endif
    while (is_alive_3 == 0);
#endif
#if NUMSLAVES >= 4
#if IPC_DEBUGLEVEL >= 4
    printf("m: waiting for slave 4\n");
#endif
    while (is_alive_4 == 0);
#endif
#if NUMSLAVES >= 5
#if IPC_DEBUGLEVEL >= 4
    printf("m: waiting for slave 5\n");
#endif
    while (is_alive_5 == 0);
#endif
#if NUMSLAVES >= 6
#if IPC_DEBUGLEVEL >= 4
    printf("m: waiting for slave 6\n");
#endif
    while (is_alive_6 == 0);
#endif
#if NUMSLAVES >= 7
#if IPC_DEBUGLEVEL >= 4
    printf("m: waiting for slave 7\n");
#endif
    while (is_alive_7 == 0);
#endif
    _restore_interrupts(restore_val);
}


void ipc_master_wait_ack(void) {
    unsigned int restore_val;
    restore_val = _disable_interrupts();
#if IPC_DEBUGLEVEL >= 4
    printf("m: waiting for slave 1\n");
#endif
    while (acknowledge_1 != 1);
#if NUMSLAVES >= 2
#if IPC_DEBUGLEVEL >= 4
    printf("m: waiting for slave 2\n");
#endif
    while (acknowledge_2 != 1);
#endif
#if NUMSLAVES >= 3
#if IPC_DEBUGLEVEL >= 4
    printf("m: waiting for slave 3\n");
#endif
    while (acknowledge_3 != 1);
#endif
#if NUMSLAVES >= 4
#if IPC_DEBUGLEVEL >= 4
    printf("m: waiting for slave 4\n");
#endif
    while (acknowledge_4 != 1);
#endif
#if NUMSLAVES >= 5
#if IPC_DEBUGLEVEL >= 4
    printf("m: waiting for slave 5\n");
#endif
    while (acknowledge_5 != 1);
#endif
#if NUMSLAVES >= 6
#if IPC_DEBUGLEVEL >= 4
    printf("m: waiting for slave 6\n");
#endif
    while (acknowledge_6 != 1);
#endif
#if NUMSLAVES >= 7
#if IPC_DEBUGLEVEL >= 4
    printf("m: waiting for slave 7\n");
#endif
    while (acknowledge_7 != 1);
#endif
    _restore_interrupts(restore_val);
    ipc_master_reset_ack();

    n_ack++;
}


void ipc_master_wait_ack_slave_i(Uint32 slaveId) {
    unsigned int restore_val;
    restore_val = _disable_interrupts();
#ifdef IPC_ASSERTS
    assert(NUMSLAVES >= slaveId);
    assert(slaveId > 0);
#endif
    if (slaveId == 1) {
        while (acknowledge_1 != 1);
        n_ack++;
#if NUMSLAVES >= 2
    } else if (slaveId == 2) {
        while (acknowledge_2 != 1);
#endif
#if NUMSLAVES >= 3
    } else if (slaveId == 3) {
        while (acknowledge_3 != 1);
#endif
#if NUMSLAVES >= 4
    } else if (slaveId == 4) {
        while (acknowledge_4 != 1);
#endif
#if NUMSLAVES >= 5
    } else if (slaveId == 5) {
        while (acknowledge_5 != 1);
#endif
#if NUMSLAVES >= 6
    } else if (slaveId == 6) {
        while (acknowledge_6 != 1);
#endif
#if NUMSLAVES >= 7
    } else if (slaveId == 7) {
        while (acknowledge_7 != 1);
#endif
    } else {
#ifdef IPC_ASSERTS
        assert(0);
#endif
    }
    _restore_interrupts(restore_val);
    ipc_master_reset_ack_slave_i(slaveId);
}


void ipc_master_reset_ack() {
    unsigned int restore_val;
    restore_val = _disable_interrupts();
    acknowledge_1 = 0;
#if NUMSLAVES >= 2
    acknowledge_2 = 0;
#endif
#if NUMSLAVES >= 3
    acknowledge_3 = 0;
#endif
#if NUMSLAVES >= 4
    acknowledge_4 = 0;
#endif
#if NUMSLAVES >= 5
    acknowledge_5 = 0;
#endif
#if NUMSLAVES >= 6
    acknowledge_6 = 0;
#endif
#if NUMSLAVES >= 7
    acknowledge_7 = 0;
#endif
    _restore_interrupts(restore_val);
}


void ipc_master_reset_ack_slave_i(Uint32 slaveId) {
    unsigned int restore_val;
    restore_val = _disable_interrupts();
#ifdef IPC_ASSERTS
    assert(NUMSLAVES >= slaveId);
    assert(slaveId > 0);
#endif
    if (slaveId == 1) {
        acknowledge_1 = 0;
#if NUMSLAVES >= 2
    } else if (slaveId == 2) {
        acknowledge_2 = 0;
#endif
#if NUMSLAVES >= 3
    } else if (slaveId == 3) {
        acknowledge_3 = 0;
#endif
#if NUMSLAVES >= 4
    } else if (slaveId == 4) {
        acknowledge_4 = 0;
#endif
#if NUMSLAVES >= 5
    } else if (slaveId == 5) {
        acknowledge_5 = 0;
#endif
#if NUMSLAVES >= 6
    } else if (slaveId == 6) {
        acknowledge_6 = 0;
#endif
#if NUMSLAVES >= 7
    } else if (slaveId == 7) {
        acknowledge_6 = 0;
#endif
    } else {
#ifdef IPC_ASSERTS
        assert(0);
#endif
    }
    _restore_interrupts(restore_val);
}


void _set_slave_i_is_alive(Uint32 volatile slaveId) {
    unsigned int restore_val;
    restore_val = _disable_interrupts();
#ifdef IPC_ASSERTS
    assert(NUMSLAVES >= slaveId);
    assert(slaveId > 0);
#endif
    if (slaveId == 1) {
        is_alive_1 = 1;
#if NUMSLAVES >= 2
    } else if (slaveId == 2) {
        is_alive_2 = 1;
#endif
#if NUMSLAVES >= 3
    } else if (slaveId == 3) {
        is_alive_3 = 1;
#endif
#if NUMSLAVES >= 4
    } else if (slaveId == 4) {
        is_alive_4 = 1;
#endif
#if NUMSLAVES >= 5
    } else if (slaveId == 5) {
        is_alive_5 = 1;
#endif
#if NUMSLAVES >= 6
    } else if (slaveId == 6) {
        is_alive_6 = 1;
#endif
#if NUMSLAVES >= 7
    } else if (slaveId == 7) {
        is_alive_7 = 1;
#endif
    } else {
#ifdef IPC_ASSERTS
        assert(0);
#endif
    }
    _restore_interrupts(restore_val);
}


void _set_slave_i_not_alive(Uint32 volatile slaveId) {
#ifdef IPC_ASSERTS
    assert(NUMSLAVES >= slaveId);
    assert(slaveId > 0);
#endif
    if (slaveId == 1) {
        is_alive_1 = 0;
#if NUMSLAVES >= 2
    } else if (slaveId == 2) {
        is_alive_2 = 0;
#endif
#if NUMSLAVES >= 3
    } else if (slaveId == 3) {
        is_alive_3 = 0;
#endif
#if NUMSLAVES >= 4
    } else if (slaveId == 4) {
        is_alive_4 = 0;
#endif
#if NUMSLAVES >= 5
    } else if (slaveId == 5) {
        is_alive_5 = 0;
#endif
#if NUMSLAVES >= 6
    } else if (slaveId == 6) {
        is_alive_6 = 0;
#endif
#if NUMSLAVES >= 7
    } else if (slaveId == 7) {
        is_alive_7 = 0;
#endif
    } else {
#ifdef IPC_ASSERTS
        assert(0);
#endif
    }
}


#if 0
int volatile * _get_req_flag(Uint32 volatile selfId) {
    volatile int *ptr = NULL;
    if (selfId == 1)
        ptr = &request_1;
#if NUMSLAVES >= 2
    if (selfId == 2)
        ptr = &request_2;
#endif
#if NUMSLAVES >= 3
    if (selfId == 3)
        ptr = &request_3;
#endif
#if NUMSLAVES >= 4
    if (selfId == 4)
        ptr = &request_4;
#endif
#if NUMSLAVES >= 5
    if (selfId == 5)
        ptr = &request_5;
#endif
#if NUMSLAVES >= 6
    if (selfId == 6)
        ptr = &request_6;
#endif
#if NUMSLAVES >= 7
    if (selfId == 7)
        ptr = &request_7;
#endif
    if (!ptr)
        printf("Invalid selfId = %d\n", (int)selfId);
    return ptr;
}
#endif

int volatile * _get_req_flag(Uint32 volatile selfId) {
    unsigned int restore_val;
    restore_val = _disable_interrupts();
    if (selfId == 1)
        return &request_1;
#if NUMSLAVES >= 2
    if (selfId == 2)
        return &request_2;
#endif
#if NUMSLAVES >= 3
    if (selfId == 3)
        return &request_3;
#endif
#if NUMSLAVES >= 4
    if (selfId == 4)
        return &request_4;
#endif
#if NUMSLAVES >= 5
    if (selfId == 5)
        return &request_5;
#endif
#if NUMSLAVES >= 6
    if (selfId == 6)
        return &request_6;
#endif
#if NUMSLAVES >= 7
    if (selfId == 7)
        return &request_7;
#endif
    _restore_interrupts(restore_val);
    printf("Invalid selfId = %d (_get_req_flag)\n", (int)selfId);
    return NULL;
}


int volatile * _get_ack_flag(Uint32 volatile selfId) {
    unsigned int restore_val;
    restore_val = _disable_interrupts();
    if (selfId == 1)
        return &acknowledge_1;
#if NUMSLAVES >= 2
    if (selfId == 2)
        return &acknowledge_2;
#endif
#if NUMSLAVES >= 3
    if (selfId == 3)
        return &acknowledge_3;
#endif
#if NUMSLAVES >= 4
    if (selfId == 4)
        return &acknowledge_4;
#endif
#if NUMSLAVES >= 5
    if (selfId == 5)
        return &acknowledge_5;
#endif
#if NUMSLAVES >= 6
    if (selfId == 6)
        return &acknowledge_6;
#endif
#if NUMSLAVES >= 7
    if (selfId == 7)
        return &acknowledge_7;
#endif
    _restore_interrupts(restore_val);
    printf("Invalid selfId = %d (_get_ack_flag)\n", (int)selfId);
    return NULL;
}


int volatile * _get_ncalls_var(Uint32 volatile selfId) {
    if (selfId == 1)
        return &ncalls_1;
#if NUMSLAVES >= 2
    if (selfId == 2)
        return &ncalls_2;
#endif
#if NUMSLAVES >= 3
    if (selfId == 3)
        return &ncalls_3;
#endif
#if NUMSLAVES >= 4
    if (selfId == 4)
        return &ncalls_4;
#endif
#if NUMSLAVES >= 5
    if (selfId == 5)
        return &ncalls_5;
#endif
#if NUMSLAVES >= 6
    if (selfId == 6)
        return &ncalls_6;
#endif
#if NUMSLAVES >= 7
    if (selfId == 7)
        return &ncalls_7;
#endif
    printf("Invalid selfId = %d\n", (int)selfId);
    return NULL;
}


const int volatile * _get_selfId_var(Uint32 volatile selfId) {
    if (selfId == 1)
        return &(selfId_1);
#if NUMSLAVES >= 2
    if (selfId == 2)
        return &(selfId_2);
#endif
#if NUMSLAVES >= 3
    if (selfId == 3)
        return &selfId_3;
#endif
#if NUMSLAVES >= 4
    if (selfId == 4)
        return &selfId_4;
#endif
#if NUMSLAVES >= 5
    if (selfId == 5)
        return &selfId_5;
#endif
#if NUMSLAVES >= 6
    if (selfId == 6)
        return &selfId_6;
#endif
#if NUMSLAVES >= 7
    if (selfId == 7)
        return &selfId_7;
#endif
    printf("Invalid selfId = %d\n", (int)selfId);
    return NULL;
}


void __TI_setMPAX(unsigned int mpax_id, unsigned int base_addr,
                  unsigned long long replacement_addr,
                  unsigned int seg_size_encoding) {
    CSL_XMC_XMPAXH lvMpaxh;
    CSL_XMC_XMPAXL lvMpaxl;

    lvMpaxh.segSize = seg_size_encoding;
    lvMpaxh.bAddr = base_addr >> 12;
    CSL_XMC_setXMPAXH(mpax_id, &lvMpaxh);
    lvMpaxl.ux = 1;
    lvMpaxl.uw = 1;
    lvMpaxl.ur = 1;
    lvMpaxl.sx = 1;
    lvMpaxl.sw = 1;
    lvMpaxl.sr = 1;
    lvMpaxl.rAddr = replacement_addr >> 12;
    CSL_XMC_setXMPAXL(mpax_id, &lvMpaxl);
}


void config_cache(Uint32 volatile selfId) {
#if IPC_DEBUGLEVEL >= 3
    printf("CORE%d: Configuring Cache\n", selfId);
#endif
    int i;

    /* All cores map MSMCSRAM_NC_VIRT to MSMCSRAM_NC_PHY */
    __TI_setMPAX(3, MSMCSRAM_NC_START_ADDR, MSMCSRAM_START_ADDR, 0x10);

    /* Disable cache for MSMCSRAM_NC_VIRT (MAR160) */
    for (i = MAR_NC_START; i <= MAR_NC_END; i++)
        CACHE_disableCaching(i);

    /* Disable cache for DDR3 */
    for (i = MAR_CACHE_DDR3_START; i <= MAR_CACHE_DDR3_END; i++)
        CACHE_disableCaching(i);
        //CACHE_enableCaching(i);

    /* Disable Prefetching for MSMCSRAM */
#if 0
    Uint8 pcx, pfx;
    for (i = MAR_MSMCSRAM_START; i <= MAR_MSMCSRAM_END; i++) {
        CACHE_getMemRegionInfo (i, &pcx, &pfx);
        CACHE_setMemRegionInfo(i, pfx, 1);
    }
#endif

    /* Set L2 cache size */
    // This can eventually mess up with variables located in L2 memory
#if 0
    CACHE_setL2Size(IPC_L2MODE);
    if (IPC_L2MODE != CACHE_0KCACHE)
        CACHE_invAllL2Wait();
#endif
#if IPC_DEBUGLEVEL >= 1
    if (selfId == 0)
        printf("IPC_utils_rev CACHE: l2 %d l1d %d l1p %d\n",
               (int)CACHE_getL2Size(),
               (int)CACHE_getL1DSize(),
               (int)CACHE_getL1PSize());
#endif
}
