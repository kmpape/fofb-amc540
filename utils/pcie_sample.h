/**  
 * @file pcie_sample.h
 *
 * @brief 
 *  Holds all the constants and API definitions required by the example
 *  application to run.  
 */

#ifndef _PCIE_ENUMERATION_H_
#define _PCIE_ENUMERATION_H_

/* C Standard library include */
#include <string.h>

/* XDC include */
#include <xdc/std.h>
#include <xdc/runtime/System.h>

/* BIOS include */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/family/c64p/EventCombiner.h>
#include <ti/sysbios/family/c64p/Hwi.h>
#include <ti/sysbios/knl/Event.h>

/* CSL include */
#include <ti/csl/cslr_device.h>

/* PCIE LLD include */
#include <ti/drv/pcie/pcie.h>

#define EDMA
#define EDMA_SYNCH_AB

/* Do gen2 on all devices -- remove or -U for GEN1 */
#define GEN2
#define PCIESS1_X2

/* Set up printf */
#include <xdc/runtime/System.h>
#define Console_printf System_printf

/* Enable the below macro to have prints on the IO Console */
#if !defined(SOC_AM572x) && !defined(SOC_AM571x) && !defined(SOC_K2G) && \
    !defined(__ARM_ARCH_7A__)
/* AM57x and K2G always use UART for all cores.  Also all ARM use UART */
#define IO_CONSOLE
#endif

#ifndef IO_CONSOLE
#include <ti/drv/uart/UART_stdio.h>
#define PCIE_logPrintf  UART_printf
#define PCIE_logScanf   UART_scanFmt
#elif defined(AMC540)
#include <ti/platform/platform.h>
#define PCIE_logPrintf  platform_uart_printf
#define PCIE_logScanf   Console_scanf
#else
#define PCIE_logPrintf  Console_printf
#define PCIE_logScanf   Console_scanf
#endif

/* Size of application buffers */
#define PCIE_BUFSIZE_APP 40 

/* Number of each type of interrupt to send */
#define PCIE_NUM_INTS   10

/* Write pattern */
#define PCIE_WR_PATTERN 0xFACEFACE

/* In this example all addresses are 32bit */
/* Outbound Base Address for PCIe RC */
#define PCIE_OB_LO_ADDR_RC   0
#define PCIE_OB_HI_ADDR_RC   0

/* Inbound  Base Address for PCIe RC */
#define PCIE_IB_LO_ADDR_RC   0x90000000
#define PCIE_IB_HI_ADDR_RC   0

/* Outbound Base Address for PCIe EP */
#define PCIE_OB_LO_ADDR_EP   PCIE_IB_LO_ADDR_RC
#define PCIE_OB_HI_ADDR_EP   0

/* Inbound  Base Address for PCIe EP */
#define PCIE_IB_LO_ADDR_EP   PCIE_OB_LO_ADDR_RC
#define PCIE_IB_HI_ADDR_EP   0

/* Data area offset relative to PCIe base (only used rev 1) */
#define PCIE_WINDOW_MEM_BASE 0x01000000U
#define PCIE_WINDOW_MEM_MASK 0x00FFFFFFU

/* Cfg area offset relative to PCIe base (only used rev 1) */
/* This MUST agree Pciev1_DeviceCfgBaseAddrs.bases! */
#define PCIE_WINDOW_CFG_BASE 0x00001000U
#define PCIE_WINDOW_CFG_MASK 0x00000FFFU

/* MSI address in PCIE data window */
#define PCIE_WINDOW_MSI_ADDR 0x02000000U
#define PCIE_WINDOW_MSI_DATA 0x00000000U

/* Inbound limit (only used rev 1) */
#define PCIE_INBOUND_MASK    0x0FFFFFFFU

/* BAR mask */
#define PCIE_BAR_MASK         0x0FFFFFFF

/* BAR Index PCie*/
#define PCIE_BAR_IDX_RC        1
#define PCIE_BAR_IDX_EP        0


/* PCIe Regions used in the example */
#define PCIE_IB_REGION_RC   0
#define PCIE_OB_REGION_RC   0
#define PCIE_IB_REGION_EP   0
#define PCIE_OB_REGION_EP   0

#ifdef EDMA
/* Synchronized token passing between two endpoints using EDMA IO */
#define PCIE_EXAMPLE_DMA_RC
#endif

#ifdef EDMA
/* Asynchronous block transfers using EDMA */
#define PCIE_EXAMPLE_DMA_EP
#endif

#ifdef EDMA
#define PCIE_EXAMPLE_LINE_SIZE      128
#endif

#ifdef EDMA
/*****************************************************************************
 * Choose the type of EDMA transfer (Current options are "DMA" and "QDMA")
 *****************************************************************************/
#define EDMA_TYPE 0 //DMA
//#define EDMA_TYPE 1 //QDMA

#endif

#endif
