#ifndef __ASM_SH_IODATA_LANDISK_H
#define __ASM_SH_IODATA_LANDISK_H

/*
 * arch/sh/include/mach-landisk/mach/iodata_landisk.h
 *
 * Copyright (C) 2000  Atom Create Engineering Co., Ltd.
 *
 * IO-DATA LANDISK support
 */
#include <linux/sh_intc.h>

/*                          */

#define PA_USB		0xa4000000	/*                       */

#define PA_ATARST	0xb0000000	/*                                  */
#define PA_LED		0xb0000001	/*                      */
#define PA_STATUS	0xb0000002	/*                        */
#define PA_SHUTDOWN	0xb0000003	/*                           */
#define PA_PCIPME	0xb0000004	/*                         */
#define PA_IMASK	0xb0000005	/*                         */
/*                                                          */
#define PA_PWRINT_CLR	0xb0000006	/*                                   */

#define PA_PIDE_OFFSET	0x40		/*               */
#define PA_SIDE_OFFSET	0x40		/*                */

#define IRQ_PCIINTA	evt2irq(0x2a0)	/*              */
#define IRQ_PCIINTB	evt2irq(0x2c0)	/*              */
#define IRQ_PCIINTC	evt2irq(0x2e0)	/*              */
#define IRQ_PCIINTD	evt2irq(0x300)	/*              */
#define IRQ_ATA		evt2irq(0x320)	/*         */
#define IRQ_FATA	evt2irq(0x340)	/*          */
#define IRQ_POWER	evt2irq(0x360)	/*                  */
#define IRQ_BUTTON	evt2irq(0x380)	/*                   */
#define IRQ_FAULT	evt2irq(0x3a0)	/*                   */

void init_landisk_IRQ(void);

#define __IO_PREFIX landisk
#include <asm/io_generic.h>

#endif  /*                           */

