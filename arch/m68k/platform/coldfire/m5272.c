/*                                                                         */

/*
 *	linux/arch/m68knommu/platform/5272/config.c
 *
 *	Copyright (C) 1999-2002, Greg Ungerer (gerg@snapgear.com)
 *	Copyright (C) 2001-2002, SnapGear Inc. (www.snapgear.com)
 */

/*                                                                         */

#include <linux/kernel.h>
#include <linux/param.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/phy.h>
#include <linux/phy_fixed.h>
#include <asm/machdep.h>
#include <asm/coldfire.h>
#include <asm/mcfsim.h>
#include <asm/mcfuart.h>
#include <asm/mcfclk.h>

/*                                                                         */

/*
                                                                    
 */
unsigned short ppdata;
unsigned char ledbank = 0xff;

/*                                                                         */

DEFINE_CLK(pll, "pll.0", MCF_CLK);
DEFINE_CLK(sys, "sys.0", MCF_BUSCLK);
DEFINE_CLK(mcftmr0, "mcftmr.0", MCF_BUSCLK);
DEFINE_CLK(mcftmr1, "mcftmr.1", MCF_BUSCLK);
DEFINE_CLK(mcftmr2, "mcftmr.2", MCF_BUSCLK);
DEFINE_CLK(mcftmr3, "mcftmr.3", MCF_BUSCLK);
DEFINE_CLK(mcfuart0, "mcfuart.0", MCF_BUSCLK);
DEFINE_CLK(mcfuart1, "mcfuart.1", MCF_BUSCLK);
DEFINE_CLK(fec0, "fec.0", MCF_BUSCLK);

struct clk *mcf_clks[] = {
	&clk_pll,
	&clk_sys,
	&clk_mcftmr0,
	&clk_mcftmr1,
	&clk_mcftmr2,
	&clk_mcftmr3,
	&clk_mcfuart0,
	&clk_mcfuart1,
	&clk_fec0,
	NULL
};

/*                                                                         */

static void __init m5272_uarts_init(void)
{
	u32 v;

	/*                                              */
	v = readl(MCFSIM_PBCNT);
	v = (v & ~0x000000ff) | 0x00000055;
	writel(v, MCFSIM_PBCNT);

	v = readl(MCFSIM_PDCNT);
	v = (v & ~0x000003fc) | 0x000002a8;
	writel(v, MCFSIM_PDCNT);
}

/*                                                                         */

static void m5272_cpu_reset(void)
{
	local_irq_disable();
	/*                                    */
	__raw_writew(0, MCFSIM_WIRR);
	__raw_writew(1, MCFSIM_WRRR);
	__raw_writew(0, MCFSIM_WCR);
	for (;;)
		/*                              */;
}

/*                                                                         */

void __init config_BSP(char *commandp, int size)
{
#if defined (CONFIG_MOD5272)
	/*                                     */
	writeb(0x40, MCFSIM_PIVR);
#endif

#if defined(CONFIG_NETtel) || defined(CONFIG_SCALES)
	/*                                                 */
	memcpy(commandp, (char *) 0xf0004000, size);
	commandp[size-1] = 0;
#elif defined(CONFIG_CANCam)
	/*                                                 */
	memcpy(commandp, (char *) 0xf0010000, size);
	commandp[size-1] = 0;
#endif

	mach_reset = m5272_cpu_reset;
	mach_sched_init = hw_timer_init;
}

/*                                                                         */

/*
                                                                    
                                                                      
                                           
 */
static struct fixed_phy_status nettel_fixed_phy_status __initdata = {
	.link	= 1,
	.speed	= 100,
	.duplex	= 0,
};

/*                                                                         */

static int __init init_BSP(void)
{
	m5272_uarts_init();
	fixed_phy_add(PHY_POLL, 0, &nettel_fixed_phy_status);
	return 0;
}

arch_initcall(init_BSP);

/*                                                                         */
