#ifndef _ASM_M68K_PCI_H
#define _ASM_M68K_PCI_H

#include <asm-generic/pci-dma-compat.h>
#include <asm-generic/pci.h>

/*                                                     
                                                             
                                            
 */
#define PCI_DMA_BUS_IS_PHYS	(1)

#define	pcibios_assign_all_busses()	1

#define	PCIBIOS_MIN_IO		0x00000100
#define	PCIBIOS_MIN_MEM		0x02000000

#endif /*                 */
