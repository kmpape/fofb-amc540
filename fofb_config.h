#ifndef FOFB_CONFIG_H_
#define FOFB_CONFIG_H_


/*
 * Control Algorithms
 */
#define IMC_CONTROL         (1) // enable=1, set to 0 if loopback only
#define GSVD_CONTROL        (0) // enable=1, set to 0 if loopback only
#define MPC_CONTROL         (0) // enable=1, set to 0 if loopback only
#define MPC_SLOWFAST        (0) // enable for same storage ring config as GSVD_CONTROL
#define INTEGRATOR_LIMIT    (4.99) // in Amperes
#define XDIR                (0) // 1=horizontal plane, 0=vertical plane
#define USE_IPC             (1) // switch multi-core (1) and single-core (0)

/*
 * Interface
 */
#define TOT_NUM_BPM             (173) // fixed, independent of disabled BPMs, must match IMC_DI_ctr.h or GSVD_ctr.h
#define TOT_NUM_CM              (172) // fixed, independent of disabled CMs, must match IMC_DI_ctr.h or GSVD_ctr.h
#define ORBIT_LIMIT             (100000) // in nanometers
#define READ_WRITE_OFFSET       (1) // BPM ID 1 is on memory location 1 (not 0)

/*
 * DMA: transfers CHUNK_NUM packets of size CHUNK_LEN*4 bytes.
 */
#define CHUNK_LEN_READ (32u) // read requests should be 128 bytes
#define CHUNK_NUM_READ (8u)
#define ARRAY_LEN_READ (CHUNK_LEN_READ*CHUNK_NUM_READ)
#define ARRAY_BYTES_READ (ARRAY_LEN_READ * sizeof(LIBQDMA_ARR_TYPE))
#define CHUNK_LEN_WRITE (16u) // write requests should be 64 bytes
#define CHUNK_NUM_WRITE (16u)
#define ARRAY_LEN_WRITE (CHUNK_LEN_WRITE*CHUNK_NUM_WRITE)
#define ARRAY_BYTES_WRITE (ARRAY_LEN_WRITE * sizeof(LIBQDMA_ARR_TYPE))

/*
 * Miscellaneous
 */
#define NO_PRINT // must be defined for real-time operation
#define UDP_CORENUM     (0) // must be different than IPC_MASTER_CORENUM in ipc_utils.h

#endif /* FOFB_CONFIG_H_ */
