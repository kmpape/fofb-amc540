#include <stdint.h>
#include <ti/drv/pcie/soc/pcie_soc.h>
#include <ti/csl/csl_bootcfgAux.h>
#include <ti/csl/csl_xmcAux.h>
#include <ti/csl/csl_serdes_pcie.h>
#include <ti/csl/csl_pscAux.h>
#include <ti/csl/csl_cacheAux.h>
#include <ti/csl/csl_chip.h>
#include <ti/sdo/edma3/drv/sample/bios6_edma3_drv_sample.h>

#include "pcie_sample.h"
#include "pcie_defs.h"


uint32_t pcieConvert_CoreLocal2GlobalAddr (uint32_t  addr)
{
  uint32_t coreNum;

  /* Get the core number. */
  coreNum = CSL_chipReadReg(CSL_CHIP_DNUM);

  /* Compute the global address. */
  return ((1 << 28) | (coreNum << 24) | (addr & 0x00ffffff));
}

/*****************************************************************************
 * Function: Enable/Disable DBI writes
 ****************************************************************************/
pcieRet_e pcieCfgDbi(Pcie_Handle handle, uint8_t enable)
{
  pcieRegisters_t        regs;
  pcieRet_e              retVal;
  pcieCmdStatusReg_t     cmdStatus;

  memset (&cmdStatus, 0, sizeof(cmdStatus));
  memset (&regs, 0, sizeof(regs));

  regs.cmdStatus = &cmdStatus;
  if ((retVal = Pcie_readRegs (handle, pcie_LOCATION_LOCAL, &regs)) != pcie_RET_OK)
  {
    PCIE_logPrintf ("Read CMD STATUS register failed!\n");
    return retVal;
  }
  cmdStatus.dbi = enable;

  if ((retVal = Pcie_writeRegs (handle, pcie_LOCATION_LOCAL, &regs)) != pcie_RET_OK)
  {
    PCIE_logPrintf ("SET CMD STATUS register failed!\n");
    return retVal;
  }

  return pcie_RET_OK;
} /* pcieCfgDbi */

/*****************************************************************************
 * Function: Power domain configuration
 ****************************************************************************/
pcieRet_e pciePowerCfg(void)
{
  /* Turn on the PCIe power domain */
  if (CSL_PSC_getPowerDomainState (CSL_PSC_PD_PCIE) != PSC_PDSTATE_ON) {
    /* Enable the domain */
    CSL_PSC_enablePowerDomain (CSL_PSC_PD_PCIE);
    /* Enable MDCTL */
    CSL_PSC_setModuleNextState (CSL_PSC_LPSC_PCIE, PSC_MODSTATE_ENABLE);
    /* Apply the domain */
    CSL_PSC_startStateTransition (CSL_PSC_PD_PCIE);
    /* Wait for it to finish */
    while (! CSL_PSC_isStateTransitionDone (CSL_PSC_PD_PCIE));
  } else {
    PCIE_logPrintf ("Power domain is already enabled.  You probably re-ran without device reset (which is OK)\n");
  }

  return pcie_RET_OK;
}

/*****************************************************************************
 * Function: Utility function a cycle clock
 ****************************************************************************/
static uint32_t readTime32(void)
{
  uint32_t timeVal;

  timeVal = TSCL;
  return timeVal;
}

/*****************************************************************************
 * Function: Utility function to introduce delay
 ****************************************************************************/
void cycleDelay (uint32_t count)
{
  uint32_t start = (uint32_t)readTime32();

  while (((uint32_t)readTime32() - start) < count);
}

/*****************************************************************************
 * Function: Serdes configuration
 ****************************************************************************/
pcieRet_e pcieSerdesCfg(void)
{
  uint16_t cfg;

  /* Provide PLL reference clock to SERDES inside PCIESS
     Program PLL settings and enable PLL from PCIe SERDES.*/
  cfg = 0x01C9; /* value based on PCIe userguide */

  CSL_BootCfgSetPCIEConfigPLL(cfg);

  /*Wait for PLL to lock (3000 CLKIN1 cycles) */
  cycleDelay(10000);

  return pcie_RET_OK;
}

/*****************************************************************************
 * Function: Enable/Disable LTSSM (Link Training)
 * This function demonstrates how one can write one binary to use either
 * rev of PCIE
 ****************************************************************************/
pcieRet_e pcieLtssmCtrl(Pcie_Handle handle, uint8_t enable)
{
  pcieCmdStatusReg_t       cmdStatus;
  pcieTiConfDeviceCmdReg_t deviceCmd;
  pcieRegisters_t          regs;
  pcieRet_e retVal;

  memset (&cmdStatus,    0, sizeof(cmdStatus));
  memset (&deviceCmd,    0, sizeof(deviceCmd));
  memset (&regs,         0, sizeof(regs));

  regs.cmdStatus = &cmdStatus;
  if ((retVal = Pcie_readRegs (handle, pcie_LOCATION_LOCAL, &regs)) != pcie_RET_OK)
  {
    if (retVal == pcie_RET_INV_REG)
    {
      /* The cmdStatus register doesn't exist; try the deviceCmd instead */
      regs.cmdStatus       = NULL;
      regs.tiConfDeviceCmd = &deviceCmd;
      if ((retVal = Pcie_readRegs (handle, pcie_LOCATION_LOCAL, &regs)) != pcie_RET_OK)
      {
        PCIE_logPrintf ("Read CMD STATUS and DEVICE CMD registers failed!\n");
        return retVal;
      }
    }
    else
    {
      PCIE_logPrintf ("Read CMD STATUS register failed!\n");
      return retVal;
    }
  }

  if(enable)
    deviceCmd.ltssmEn = cmdStatus.ltssmEn = 1;
  else
    deviceCmd.ltssmEn = cmdStatus.ltssmEn = 0;

  if ((retVal = Pcie_writeRegs (handle, pcie_LOCATION_LOCAL, &regs)) != pcie_RET_OK)
  {
    PCIE_logPrintf ("SET CMD STATUS register failed!\n");
    return retVal;
  }

  return pcie_RET_OK;
}

pcieRet_e pcieLtssmCtrlOnly(Pcie_Handle handle, uint8_t enable)
{
  pcieCmdStatusReg_t       cmdStatus;
  pcieTiConfDeviceCmdReg_t deviceCmd;
  pcieRegisters_t          regs;
  pcieRet_e retVal;

  memset (&cmdStatus,    0, sizeof(cmdStatus));
  memset (&deviceCmd,    0, sizeof(deviceCmd));
  memset (&regs,         0, sizeof(regs));

  regs.cmdStatus = &cmdStatus;
  if ((retVal = Pcie_readRegs (handle, pcie_LOCATION_LOCAL, &regs)) != pcie_RET_OK)
  {
    if (retVal == pcie_RET_INV_REG)
    {
      /* The cmdStatus register doesn't exist; try the deviceCmd instead */
      regs.cmdStatus       = NULL;
      regs.tiConfDeviceCmd = &deviceCmd;
      if ((retVal = Pcie_readRegs (handle, pcie_LOCATION_LOCAL, &regs)) != pcie_RET_OK)
      {
        PCIE_logPrintf ("Read CMD STATUS and DEVICE CMD registers failed!\n");
        return retVal;
      }
    }
    else
    {
      PCIE_logPrintf ("Read CMD STATUS register failed!\n");
      return retVal;
    }
  }

  deviceCmd.ltssmEn = cmdStatus.dbi = 1;
  deviceCmd.ltssmEn = cmdStatus.ibXltEn = 1;
  deviceCmd.ltssmEn = cmdStatus.obXltEn = 1;
  if(enable)
    deviceCmd.ltssmEn = cmdStatus.ltssmEn = 1;
  else
    deviceCmd.ltssmEn = cmdStatus.ltssmEn = 0;

  if ((retVal = Pcie_writeRegs (handle, pcie_LOCATION_LOCAL, &regs)) != pcie_RET_OK)
  {
    PCIE_logPrintf ("SET CMD STATUS register failed!\n");
    return retVal;
  }

  return pcie_RET_OK;
}

/*****************************************************************************
 * Function: Configure PCIe in Gen1 vs Gen2 mode
 ****************************************************************************/
pcieRet_e pcieSetGen2(Pcie_Handle handle)
{
  pcieRet_e              retVal;

  pcieRegisters_t        regs;
  pcieLinkCapReg_t       linkCap;
  pcieGen2Reg_t          gen2;

  uint8_t                targetGen, dirSpd;

#ifdef GEN2
  targetGen = 2;
  dirSpd    = 1;
#else
  targetGen = 1;
  dirSpd    = 0;
#endif

  memset (&gen2,             0, sizeof(gen2));
  memset (&linkCap,          0, sizeof(linkCap));
  memset (&regs,             0, sizeof(regs));

  /* Set gen1/gen2 in link cap */
  regs.linkCap = &linkCap;
  if ((retVal = Pcie_readRegs (handle, pcie_LOCATION_LOCAL, &regs)) != pcie_RET_OK)
  {
    PCIE_logPrintf ("GET linkCap register failed!\n");
    return retVal;
  }

  if (linkCap.maxLinkSpeed != targetGen)
  {
    PCIE_logPrintf ("PowerUP linkCap gen=%d change to %d\n", linkCap.maxLinkSpeed, targetGen);
    linkCap.maxLinkSpeed = targetGen;
  }
  else
  {
    regs.linkCap = NULL; /* Nothing to write back */
  }

  /* Setting PL_GEN2 */
  gen2.numFts = 0xF;
  gen2.dirSpd = dirSpd;
  gen2.lnEn   = 1;
#ifdef PCIESS1_X2
  gen2.lnEn = 2;
#endif
  regs.gen2 = &gen2;

  if ((retVal = Pcie_writeRegs (handle, pcie_LOCATION_LOCAL, &regs)) != pcie_RET_OK)
  {
    PCIE_logPrintf ("SET GEN2/link cap register failed!\n");
    return retVal;
  }

  return retVal;
}

/*****************************************************************************
 * Function: Configure PCIe in Root Complex Mode
 ****************************************************************************/
pcieRet_e pcieCfgRC(Pcie_Handle handle)
{
  pcieRet_e retVal;

  pcieObSizeReg_t        obSize;
  pcieType1Bar32bitIdx_t type1Bar32bitIdx;
  pcieStatusCmdReg_t     statusCmd;
  pcieDevStatCtrlReg_t   devStatCtrl;
  pcieAccrReg_t          accr;
  pcieDeviceCapReg_t     deviceCap;

  pcieRegisters_t        setRegs;
  pcieRegisters_t        getRegs;

  memset (&obSize,           0, sizeof(obSize));
  memset (&type1Bar32bitIdx, 0, sizeof(type1Bar32bitIdx));
  memset (&statusCmd,        0, sizeof(statusCmd));
  memset (&devStatCtrl,      0, sizeof(devStatCtrl));
  memset (&deviceCap,        0, sizeof(deviceCap));
  memset (&accr,             0, sizeof(accr));

  /*Disable link training*/
  if ((retVal = pcieLtssmCtrl(handle, FALSE)) != pcie_RET_OK)
  {
    PCIE_logPrintf ("Failed to disable Link Training!\n");
    return retVal;
  }

  /* Configure the size of the translation regions */
  memset (&setRegs, 0, sizeof(setRegs));
  memset (&getRegs, 0, sizeof(getRegs));

  /* Only required for v0 hw */
  obSize.size = pcie_OB_SIZE_8MB;
  setRegs.obSize = &obSize;

  if ((retVal = Pcie_writeRegs (handle, pcie_LOCATION_LOCAL, &setRegs)) != pcie_RET_OK)
  {
    PCIE_logPrintf ("SET OB_SIZE register failed!\n");
    return retVal;
  }

  /* Set gen2/link cap */
  if ((retVal = pcieSetGen2(handle)) != pcie_RET_OK)
  {
    PCIE_logPrintf ("pcieSetGen2 failed!\n");
    return retVal;
  }

  /* Configure BAR Masks */
  /* First need to enable writing on BAR mask registers */
  if ((retVal = pcieCfgDbi (handle, 1)) != pcie_RET_OK)
  {
    return retVal;
  }

  /* Configure Masks*/
  memset (&setRegs, 0, sizeof(setRegs));
  memset (&getRegs, 0, sizeof(getRegs));

  type1Bar32bitIdx.reg.reg32 = PCIE_BAR_MASK;
  setRegs.type1BarMask32bitIdx = &type1Bar32bitIdx;

  /* BAR 0 */
  type1Bar32bitIdx.idx = 0; /* configure BAR 0*/
  if ((retVal = Pcie_writeRegs (handle, pcie_LOCATION_LOCAL, &setRegs)) != pcie_RET_OK)
  {
    PCIE_logPrintf ("SET BAR MASK register failed!\n");
    return retVal;
  }

  /* Disable writing on BAR Masks */
  if ((retVal = pcieCfgDbi (handle, 0)) != pcie_RET_OK)
  {
    return retVal;
  }

  /* Enable memory access and mastership of the bus */
  memset (&setRegs, 0, sizeof(setRegs));
  memset (&getRegs, 0, sizeof(getRegs));

  getRegs.statusCmd = &statusCmd;
  if ((retVal = Pcie_readRegs (handle, pcie_LOCATION_LOCAL, &getRegs)) != pcie_RET_OK)
  {
    PCIE_logPrintf ("Read Status Comand register failed!\n");
    return retVal;
  }
  statusCmd.memSp  = 1;
  statusCmd.busMs  = 1;
  statusCmd.resp   = 1;
  statusCmd.serrEn = 1;
  setRegs.statusCmd = &statusCmd;

  if ((retVal = Pcie_writeRegs (handle, pcie_LOCATION_LOCAL, &setRegs)) != pcie_RET_OK)
  {
    PCIE_logPrintf ("SET Status Command register failed!\n");
    return retVal;
  }

  /* Enable Error Reporting */
  memset (&setRegs, 0, sizeof(setRegs));
  memset (&getRegs, 0, sizeof(getRegs));

  getRegs.devStatCtrl = &devStatCtrl;
  if ((retVal = Pcie_readRegs (handle, pcie_LOCATION_LOCAL, &getRegs)) != pcie_RET_OK)
  {
    PCIE_logPrintf ("Read Device Status Control register failed!\n");
    return retVal;
  }
  devStatCtrl.reqRp = 1;
  devStatCtrl.fatalErRp = 1;
  devStatCtrl.nFatalErRp = 1;
  devStatCtrl.corErRp = 1;
  setRegs.devStatCtrl = &devStatCtrl;

  if ((retVal = Pcie_writeRegs (handle, pcie_LOCATION_LOCAL, &setRegs)) != pcie_RET_OK)
  {
    PCIE_logPrintf ("SET Device Status Control register failed!\n");
    return retVal;
  }

  /* Transaction Layer Packet Config */
  memset (&setRegs, 0, sizeof(setRegs));
  memset (&getRegs, 0, sizeof(getRegs));

  getRegs.accr = &accr;
  if ((retVal = Pcie_readRegs (handle, pcie_LOCATION_LOCAL, &getRegs)) != pcie_RET_OK)
  {
    PCIE_logPrintf ("Read Device Status Control register failed!\n");
    return retVal;
  }

  // Advanced Capabilities and Control
  accr.chkEn=0;
  accr.chkCap=0;
  accr.genEn=0;
  accr.genCap=0;
  setRegs.accr = &accr;

  if ((retVal = Pcie_writeRegs (handle, pcie_LOCATION_LOCAL, &setRegs)) != pcie_RET_OK)
  {
    PCIE_logPrintf ("SET accr register failed!\n");
    return retVal;
  }

  return pcie_RET_OK;
}

/*****************************************************************************
 * Function: Configure and enable Outbound Address Translation for rev 0
 ****************************************************************************/
pcieRet_e pcieObTransCfg(Pcie_Handle handle, uint32_t obAddrLo, uint32_t obAddrHi, uint8_t region)
{

  pcieRet_e retVal;

  pcieRegisters_t      setRegs;
  pcieRegisters_t      getRegs;

  pcieCmdStatusReg_t   cmdStatus;

  memset (&setRegs,   0, sizeof(setRegs));
  memset (&getRegs,   0, sizeof(getRegs));
  memset (&cmdStatus, 0, sizeof(cmdStatus));

  /* Set outbound offset registers */
  if ((retVal = Pcie_cfgObOffset(handle, obAddrLo, obAddrHi, region)) != pcie_RET_OK)
  {
    PCIE_logPrintf ("Failed to configure ObOffset registers!\n");
    return retVal;
  }

  /*enable Outbound address translation*/
  memset (&setRegs,    0, sizeof(setRegs));
  memset (&getRegs,    0, sizeof(getRegs));

  getRegs.cmdStatus = &cmdStatus;
  if ((retVal = Pcie_readRegs (handle, pcie_LOCATION_LOCAL, &getRegs)) != pcie_RET_OK)
  {
    PCIE_logPrintf ("Read CMD STATUS register failed!\n");
    return retVal;
  }
  cmdStatus.obXltEn = 1;
  setRegs.cmdStatus = &cmdStatus;

  if ((retVal = Pcie_writeRegs (handle, pcie_LOCATION_LOCAL, &setRegs)) != pcie_RET_OK)
  {
    PCIE_logPrintf ("SET CMD STATUS register failed!\n");
    return retVal;
  }

  return pcie_RET_OK;
}

/*****************************************************************************
 * Function: Check LTSSM status and wait for the link to be up
 ****************************************************************************/
void pcieWaitLinkUp(Pcie_Handle handle)
{
  pcieRegisters_t  getRegs;

  memset (&getRegs, 0, sizeof(getRegs));

  pcieDebug0Reg_t            ltssmStateReg;
  getRegs.debug0 =          &ltssmStateReg;

  memset (&ltssmStateReg,  0, sizeof(ltssmStateReg));

  uint8_t ltssmState = 0;

  PCIE_logPrintf ("IN pcieWaitLinkUp.\n");
  while(ltssmState != pcie_LTSSM_L0)
  {
    cycleDelay(100);
    if (Pcie_readRegs (handle, pcie_LOCATION_LOCAL, &getRegs) != pcie_RET_OK)
    {
      PCIE_logPrintf ("Read LTSSM state failed!\n");
      return;
    }
    ltssmState = ltssmStateReg.ltssmState;
    PCIE_logPrintf ("ltssmState=%d, waiting for=%d.\n", (int)ltssmState, (int)pcie_LTSSM_L0);
  }
}

void config_pcie_fpga(Pcie_Handle handle)
{
    pcieBarCfg_t            barCfg;
    pcieRegisters_t         getRegs;
    pcieRegisters_t         setRegs;
    pcieVndDevIdReg_t       vndDevId;
    pcieStatusCmdReg_t      statusCmd;
    pcieType0Bar32bitIdx_t  type0Bar32bitIdx;

    // Read RC DeviceId and VendorId
    memset (&vndDevId,  0, sizeof(vndDevId));
    memset (&getRegs, 0, sizeof(getRegs));
    getRegs.vndDevId = &vndDevId;
    if (Pcie_readRegs (handle, pcie_LOCATION_LOCAL, &getRegs) != pcie_RET_OK) {
      PCIE_logPrintf ("AMC540 DSP's VendorId and DevicId read failed!\n");
      return;
    }
#ifndef NO_PRINT
    PCIE_logPrintf ("AMC540 DSP's Vendor ID 0x%x Device ID 0x%x\n", vndDevId.vndId, vndDevId.devId);
#endif

    // Read FPGA's VendorId and DeviceId
    memset (&getRegs, 0, sizeof(getRegs));
    memset (&vndDevId,  0, sizeof(vndDevId));
    getRegs.vndDevId = &vndDevId;
    if (Pcie_readRegs (handle, pcie_LOCATION_REMOTE, &getRegs) != pcie_RET_OK) {
        PCIE_logPrintf ("AMC540 FPGA's Read VendorId and DeviceId failed!\n");
        return;
    }
#ifndef NO_PRINT
    PCIE_logPrintf ("AMC540 FPGA's Vendor ID 0x%x Device ID 0x%x\n", vndDevId.vndId, vndDevId.devId);
#endif

    /* Configure FPGA's BAR0 */
    // Write FPGA's BAR0 mask first
    memset (&type0Bar32bitIdx, 0, sizeof(type0Bar32bitIdx));
    memset (&setRegs, 0, sizeof(setRegs));
    type0Bar32bitIdx.reg.reg32 = 0xffffffff; // mask
    type0Bar32bitIdx.idx = 0; // BAR0
    setRegs.type0Bar32bitIdx = &type0Bar32bitIdx;
    if (Pcie_writeRegs (handle, pcie_LOCATION_REMOTE, &setRegs) != pcie_RET_OK) {
        PCIE_logPrintf ("Write FPGA's BAR0 mask failed!\n");
        return;
    }

    // Read FPGA's BAR0 size
    memset (&type0Bar32bitIdx, 0, sizeof(type0Bar32bitIdx));
    memset (&getRegs, 0, sizeof(getRegs));
    type0Bar32bitIdx.idx = 0; // BAR0
    getRegs.type0Bar32bitIdx = &type0Bar32bitIdx;
    if (Pcie_readRegs (handle, pcie_LOCATION_REMOTE, &getRegs) != pcie_RET_OK) {
      PCIE_logPrintf ("Read FPGA's BAR0 size failed!\n");
      return;
    }
#ifndef NO_PRINT
    PCIE_logPrintf("FPGA's BAR0 size %dKB\n", (~(type0Bar32bitIdx.reg.reg32 & ~0xf) + 1) / 1024);
#endif

    /* Configure FPGA's BAR0 */
    barCfg.location = pcie_LOCATION_REMOTE;
    barCfg.mode     = pcie_EP_MODE;
    barCfg.base     = 0x00000000;
    barCfg.prefetch = pcie_BAR_NON_PREF; //pcie_BAR_NON_PREF
    barCfg.type     = pcie_BAR_TYPE32;
    barCfg.memSpace = pcie_BAR_MEM_MEM;
    barCfg.idx      = 0;

    if (Pcie_cfgBar(handle, &barCfg) != pcie_RET_OK) {
      PCIE_logPrintf ("Failed to configure FPGA's BAR0\n");
      return;
    }

    // Set FPGA statusCmd
    memset (&setRegs, 0, sizeof(setRegs));
    memset (&statusCmd, 0, sizeof(statusCmd));

    statusCmd.memSp = 1;
    statusCmd.busMs = 1;
    statusCmd.resp = 1;
    statusCmd.serrEn = 1;
    setRegs.statusCmd = &statusCmd;

    if (Pcie_writeRegs (handle, pcie_LOCATION_REMOTE, &setRegs) != pcie_RET_OK) {
        PCIE_logPrintf ("Set FPGA's statusCmd failed!\n");
        return;
    }
}

Pcie_Handle handle = NULL;

volatile uint32_t* pcie_init_all(const int BRAM_offset) {
    TSCL = 1;
    uint16_t lock = 0;
    void *pcieBase;
    pcieRet_e retVal;

    /* Unlock kicker once, and don't relock, because its not multicore safe */
    CSL_BootCfgUnlockKicker();

#ifndef NO_PRINT
    PCIE_logPrintf ("\n==================== AMC540 PCIe RC mode Test ================= \n\n");
    PCIE_logPrintf ("Version #: 0x%08x; string %s\n\n", (unsigned)Pcie_getVersion(), Pcie_getVersionStr());
#endif

    /* Pass device config to LLD */
    if ((retVal = Pcie_init (&pcieInitCfg)) != pcie_RET_OK) {
      PCIE_logPrintf ("LLD device configuration failed\n");
      exit(1);
    }

    /* Power up PCIe Module */
    if ((retVal = pciePowerCfg()) != pcie_RET_OK) {
      PCIE_logPrintf ("PCIe Power Up failed (%d)\n", (int)retVal);
      exit(1);
    }

#ifndef NO_PRINT
    PCIE_logPrintf ("PCIe Power Up.\n");
#endif

    if ((retVal = Pcie_open(0, &handle)) != pcie_RET_OK) {
      PCIE_logPrintf ("Open failed (%d)\n", (int)retVal);
      exit(1);
    }
    cycleDelay (1000*1000*1000);

    /* Configure SERDES*/
    if ((retVal = pcieSerdesCfg()) != pcie_RET_OK) {
      PCIE_logPrintf ("PCIe Serdes config failed (%d)\n", (int)retVal);
      exit(1);
    }

    /* Set the PCIe mode*/
    if ((retVal = Pcie_setInterfaceMode(handle, pcie_RC_MODE)) != pcie_RET_OK) {
      PCIE_logPrintf ("Set PCIe Mode failed (%d)\n", (int)retVal);
      exit(1);
    }

    /* Wait until the PCIe SERDES PLL locks */
    while (!lock) CSL_BootCfgGetPCIEPLLLock(&lock);

#ifndef NO_PRINT
    PCIE_logPrintf ("PLL configured.\n");
#endif

    /* Configure application registers for Root Complex*/
    if ((retVal = pcieCfgRC(handle)) != pcie_RET_OK) {
        PCIE_logPrintf ("Failed to configure PCIe in RC mode (%d)\n", (int)retVal);
        exit(1);
    }

    if ((retVal = pcieObTransCfg (handle, PCIE_OB_LO_ADDR_RC, PCIE_OB_HI_ADDR_RC, PCIE_OB_REGION_RC)) != pcie_RET_OK) {
        PCIE_logPrintf ("Failed to configure Outbound Address Translation (%d)\n", (int)retVal);
        exit(1);
    }

#ifndef NO_PRINT
    PCIE_logPrintf ("Successfully configured Outbound Translation!\n");
    PCIE_logPrintf ("Starting link training...\n");
#endif

    /* Enable link training */
    if ((retVal = pcieLtssmCtrl(handle, TRUE)) != pcie_RET_OK) {
      PCIE_logPrintf ("Failed to Enable Link Training! (%d)\n", (int)retVal);
      exit(1);
    }

    /* Wait for link to be up */
#ifndef NO_PRINT
    PCIE_logPrintf ("AT pcieWaitLinkUp.\n");
#endif
    pcieWaitLinkUp(handle);
#ifndef NO_PRINT
    PCIE_logPrintf ("Link is up.\n");
#endif

    config_pcie_fpga(handle);

    if ((retVal = Pcie_getMemSpaceRange (handle, &pcieBase, NULL)) != pcie_RET_OK) {
      PCIE_logPrintf ("getMemSpaceRange failed (%d)\n", (int)retVal);
      exit(1);
    }
    PCIE_logPrintf ("PCIe setup success.\n");

    volatile uint32_t *ptr = (uint32_t *)pcieBase;

    /* Assign BRAM location */
    return ((volatile uint32_t *) (&ptr[BRAM_offset]));
}

void pcie_close_all(void) {
  pcieRet_e retVal;
#if 1
  PCIE_logPrintf ("Closing link training...\n");
  retVal = pcieLtssmCtrl(handle, FALSE);
  PCIE_logPrintf ("Link training closed with retval=%d.\n", retVal);
#endif
  PCIE_logPrintf ("Closing PCIe link...\n");
  retVal = Pcie_close (&handle);
  PCIE_logPrintf ("PCIe link closed with retval=%d.\n", retVal);
#if 0
  PCIE_logPrintf ("Disabling power domain...\n");
  CSL_PSC_disablePowerDomain(CSL_PSC_PD_PCIE);
#endif

  cycleDelay (1000*1000*1000);
}
