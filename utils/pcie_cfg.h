#ifndef PCIE_CFG_H_
#define PCIE_CFG_H_
#include <stdint.h>
#include <c6x.h>

void cycleDelay (uint32_t count);
uint32_t pcieConvert_CoreLocal2GlobalAddr (uint32_t  addr);
volatile uint32_t* pcie_init_all(const int BRAM_offset);
void pcie_close_all(void);

#endif /* PCIE_CFG_H_ */
