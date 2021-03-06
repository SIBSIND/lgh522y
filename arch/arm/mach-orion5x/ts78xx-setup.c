/*
 * arch/arm/mach-orion5x/ts78xx-setup.c
 *
 * Maintainer: Alexander Clouter <alex@digriz.org.uk>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sysfs.h>
#include <linux/platform_device.h>
#include <linux/mv643xx_eth.h>
#include <linux/ata_platform.h>
#include <linux/m48t86.h>
#include <linux/mtd/nand.h>
#include <linux/mtd/partitions.h>
#include <linux/timeriomem-rng.h>
#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <mach/orion5x.h>
#include "common.h"
#include "mpp.h"
#include "ts78xx-fpga.h"

/*                                                                            
               
                                                                            */

/*
                                                                       
 */
#define TS78XX_FPGA_REGS_PHYS_BASE	0xe8000000
#define TS78XX_FPGA_REGS_VIRT_BASE	IOMEM(0xff900000)
#define TS78XX_FPGA_REGS_SIZE		SZ_1M

static struct ts78xx_fpga_data ts78xx_fpga = {
	.id		= 0,
	.state		= 1,
/*                                                       */
};

/*                                                                            
                      
                                                                            */
static struct map_desc ts78xx_io_desc[] __initdata = {
	{
		.virtual	= (unsigned long)TS78XX_FPGA_REGS_VIRT_BASE,
		.pfn		= __phys_to_pfn(TS78XX_FPGA_REGS_PHYS_BASE),
		.length		= TS78XX_FPGA_REGS_SIZE,
		.type		= MT_DEVICE,
	},
};

void __init ts78xx_map_io(void)
{
	orion5x_map_io();
	iotable_init(ts78xx_io_desc, ARRAY_SIZE(ts78xx_io_desc));
}

/*                                                                            
           
                                                                            */
static struct mv643xx_eth_platform_data ts78xx_eth_data = {
	.phy_addr	= MV643XX_ETH_PHY_ADDR(0),
};

/*                                                                            
       
                                                                            */
static struct mv_sata_platform_data ts78xx_sata_data = {
	.n_ports	= 2,
};

/*                                                                            
                                                                   
                                                                            */
#define TS_RTC_CTRL	(TS78XX_FPGA_REGS_VIRT_BASE + 0x808)
#define TS_RTC_DATA	(TS78XX_FPGA_REGS_VIRT_BASE + 0x80c)

static unsigned char ts78xx_ts_rtc_readbyte(unsigned long addr)
{
	writeb(addr, TS_RTC_CTRL);
	return readb(TS_RTC_DATA);
}

static void ts78xx_ts_rtc_writebyte(unsigned char value, unsigned long addr)
{
	writeb(addr, TS_RTC_CTRL);
	writeb(value, TS_RTC_DATA);
}

static struct m48t86_ops ts78xx_ts_rtc_ops = {
	.readbyte	= ts78xx_ts_rtc_readbyte,
	.writebyte	= ts78xx_ts_rtc_writebyte,
};

static struct platform_device ts78xx_ts_rtc_device = {
	.name		= "rtc-m48t86",
	.id		= -1,
	.dev		= {
		.platform_data	= &ts78xx_ts_rtc_ops,
	},
	.num_resources	= 0,
};

/*
                                                                         
                                                                           
                       
  
                                                                           
  
                                                                           
                                
 */
static int ts78xx_ts_rtc_load(void)
{
	int rc;
	unsigned char tmp_rtc0, tmp_rtc1;

	tmp_rtc0 = ts78xx_ts_rtc_readbyte(126);
	tmp_rtc1 = ts78xx_ts_rtc_readbyte(127);

	ts78xx_ts_rtc_writebyte(0x00, 126);
	ts78xx_ts_rtc_writebyte(0x55, 127);
	if (ts78xx_ts_rtc_readbyte(127) == 0x55) {
		ts78xx_ts_rtc_writebyte(0xaa, 127);
		if (ts78xx_ts_rtc_readbyte(127) == 0xaa
				&& ts78xx_ts_rtc_readbyte(126) == 0x00) {
			ts78xx_ts_rtc_writebyte(tmp_rtc0, 126);
			ts78xx_ts_rtc_writebyte(tmp_rtc1, 127);

			if (ts78xx_fpga.supports.ts_rtc.init == 0) {
				rc = platform_device_register(&ts78xx_ts_rtc_device);
				if (!rc)
					ts78xx_fpga.supports.ts_rtc.init = 1;
			} else
				rc = platform_device_add(&ts78xx_ts_rtc_device);

			if (rc)
				pr_info("RTC could not be registered: %d\n",
					rc);
			return rc;
		}
	}

	pr_info("RTC not found\n");
	return -ENODEV;
};

static void ts78xx_ts_rtc_unload(void)
{
	platform_device_del(&ts78xx_ts_rtc_device);
}

/*                                                                            
             
                                                                            */
#define TS_NAND_CTRL	(TS78XX_FPGA_REGS_VIRT_BASE + 0x800)	/*      */
#define TS_NAND_DATA	(TS78XX_FPGA_REGS_PHYS_BASE + 0x804)	/*      */

/*
                                            
  
        
                           
                           
                           
 */
static void ts78xx_ts_nand_cmd_ctrl(struct mtd_info *mtd, int cmd,
			unsigned int ctrl)
{
	struct nand_chip *this = mtd->priv;

	if (ctrl & NAND_CTRL_CHANGE) {
		unsigned char bits;

		bits = (ctrl & NAND_NCE) << 2;
		bits |= ctrl & NAND_CLE;
		bits |= (ctrl & NAND_ALE) >> 2;

		writeb((readb(TS_NAND_CTRL) & ~0x7) | bits, TS_NAND_CTRL);
	}

	if (cmd != NAND_CMD_NONE)
		writeb(cmd, this->IO_ADDR_W);
}

static int ts78xx_ts_nand_dev_ready(struct mtd_info *mtd)
{
	return readb(TS_NAND_CTRL) & 0x20;
}

static void ts78xx_ts_nand_write_buf(struct mtd_info *mtd,
			const uint8_t *buf, int len)
{
	struct nand_chip *chip = mtd->priv;
	void __iomem *io_base = chip->IO_ADDR_W;
	unsigned long off = ((unsigned long)buf & 3);
	int sz;

	if (off) {
		sz = min_t(int, 4 - off, len);
		writesb(io_base, buf, sz);
		buf += sz;
		len -= sz;
	}

	sz = len >> 2;
	if (sz) {
		u32 *buf32 = (u32 *)buf;
		writesl(io_base, buf32, sz);
		buf += sz << 2;
		len -= sz << 2;
	}

	if (len)
		writesb(io_base, buf, len);
}

static void ts78xx_ts_nand_read_buf(struct mtd_info *mtd,
			uint8_t *buf, int len)
{
	struct nand_chip *chip = mtd->priv;
	void __iomem *io_base = chip->IO_ADDR_R;
	unsigned long off = ((unsigned long)buf & 3);
	int sz;

	if (off) {
		sz = min_t(int, 4 - off, len);
		readsb(io_base, buf, sz);
		buf += sz;
		len -= sz;
	}

	sz = len >> 2;
	if (sz) {
		u32 *buf32 = (u32 *)buf;
		readsl(io_base, buf32, sz);
		buf += sz << 2;
		len -= sz << 2;
	}

	if (len)
		readsb(io_base, buf, len);
}

static struct mtd_partition ts78xx_ts_nand_parts[] = {
	{
		.name		= "mbr",
		.offset		= 0,
		.size		= SZ_128K,
		.mask_flags	= MTD_WRITEABLE,
	}, {
		.name		= "kernel",
		.offset		= MTDPART_OFS_APPEND,
		.size		= SZ_4M,
	}, {
		.name		= "initrd",
		.offset		= MTDPART_OFS_APPEND,
		.size		= SZ_4M,
	}, {
		.name		= "rootfs",
		.offset		= MTDPART_OFS_APPEND,
		.size		= MTDPART_SIZ_FULL,
	}
};

static struct platform_nand_data ts78xx_ts_nand_data = {
	.chip	= {
		.nr_chips		= 1,
		.partitions		= ts78xx_ts_nand_parts,
		.nr_partitions		= ARRAY_SIZE(ts78xx_ts_nand_parts),
		.chip_delay		= 15,
		.bbt_options		= NAND_BBT_USE_FLASH,
	},
	.ctrl	= {
		/*
                                                             
                                                               
                                                          
                                                             
                                                              
   */
		.cmd_ctrl		= ts78xx_ts_nand_cmd_ctrl,
		.dev_ready		= ts78xx_ts_nand_dev_ready,
		.write_buf		= ts78xx_ts_nand_write_buf,
		.read_buf		= ts78xx_ts_nand_read_buf,
	},
};

static struct resource ts78xx_ts_nand_resources
			= DEFINE_RES_MEM(TS_NAND_DATA, 4);

static struct platform_device ts78xx_ts_nand_device = {
	.name		= "gen_nand",
	.id		= -1,
	.dev		= {
		.platform_data	= &ts78xx_ts_nand_data,
	},
	.resource	= &ts78xx_ts_nand_resources,
	.num_resources	= 1,
};

static int ts78xx_ts_nand_load(void)
{
	int rc;

	if (ts78xx_fpga.supports.ts_nand.init == 0) {
		rc = platform_device_register(&ts78xx_ts_nand_device);
		if (!rc)
			ts78xx_fpga.supports.ts_nand.init = 1;
	} else
		rc = platform_device_add(&ts78xx_ts_nand_device);

	if (rc)
		pr_info("NAND could not be registered: %d\n", rc);
	return rc;
};

static void ts78xx_ts_nand_unload(void)
{
	platform_device_del(&ts78xx_ts_nand_device);
}

/*                                                                            
         
                                                                            */
#define TS_RNG_DATA	(TS78XX_FPGA_REGS_PHYS_BASE | 0x044)

static struct resource ts78xx_ts_rng_resource
			= DEFINE_RES_MEM(TS_RNG_DATA, 4);

static struct timeriomem_rng_data ts78xx_ts_rng_data = {
	.period		= 1000000, /*            */
};

static struct platform_device ts78xx_ts_rng_device = {
	.name		= "timeriomem_rng",
	.id		= -1,
	.dev		= {
		.platform_data	= &ts78xx_ts_rng_data,
	},
	.resource	= &ts78xx_ts_rng_resource,
	.num_resources	= 1,
};

static int ts78xx_ts_rng_load(void)
{
	int rc;

	if (ts78xx_fpga.supports.ts_rng.init == 0) {
		rc = platform_device_register(&ts78xx_ts_rng_device);
		if (!rc)
			ts78xx_fpga.supports.ts_rng.init = 1;
	} else
		rc = platform_device_add(&ts78xx_ts_rng_device);

	if (rc)
		pr_info("RNG could not be registered: %d\n", rc);
	return rc;
};

static void ts78xx_ts_rng_unload(void)
{
	platform_device_del(&ts78xx_ts_rng_device);
}

/*                                                                            
                              
                                                                            */
static void ts78xx_fpga_devices_zero_init(void)
{
	ts78xx_fpga.supports.ts_rtc.init = 0;
	ts78xx_fpga.supports.ts_nand.init = 0;
	ts78xx_fpga.supports.ts_rng.init = 0;
}

static void ts78xx_fpga_supports(void)
{
	/*                                           */
	switch (ts78xx_fpga.id) {
	case TS7800_REV_1:
	case TS7800_REV_2:
	case TS7800_REV_3:
	case TS7800_REV_4:
	case TS7800_REV_5:
	case TS7800_REV_6:
	case TS7800_REV_7:
	case TS7800_REV_8:
	case TS7800_REV_9:
		ts78xx_fpga.supports.ts_rtc.present = 1;
		ts78xx_fpga.supports.ts_nand.present = 1;
		ts78xx_fpga.supports.ts_rng.present = 1;
		break;
	default:
		/*                                 */
		switch ((ts78xx_fpga.id >> 8) & 0xffffff) {
		case TS7800_FPGA_MAGIC:
			pr_warning("unrecognised FPGA revision 0x%.2x\n",
					ts78xx_fpga.id & 0xff);
			ts78xx_fpga.supports.ts_rtc.present = 1;
			ts78xx_fpga.supports.ts_nand.present = 1;
			ts78xx_fpga.supports.ts_rng.present = 1;
			break;
		default:
			ts78xx_fpga.supports.ts_rtc.present = 0;
			ts78xx_fpga.supports.ts_nand.present = 0;
			ts78xx_fpga.supports.ts_rng.present = 0;
		}
	}
}

static int ts78xx_fpga_load_devices(void)
{
	int tmp, ret = 0;

	if (ts78xx_fpga.supports.ts_rtc.present == 1) {
		tmp = ts78xx_ts_rtc_load();
		if (tmp)
			ts78xx_fpga.supports.ts_rtc.present = 0;
		ret |= tmp;
	}
	if (ts78xx_fpga.supports.ts_nand.present == 1) {
		tmp = ts78xx_ts_nand_load();
		if (tmp)
			ts78xx_fpga.supports.ts_nand.present = 0;
		ret |= tmp;
	}
	if (ts78xx_fpga.supports.ts_rng.present == 1) {
		tmp = ts78xx_ts_rng_load();
		if (tmp)
			ts78xx_fpga.supports.ts_rng.present = 0;
		ret |= tmp;
	}

	return ret;
}

static int ts78xx_fpga_unload_devices(void)
{
	int ret = 0;

	if (ts78xx_fpga.supports.ts_rtc.present == 1)
		ts78xx_ts_rtc_unload();
	if (ts78xx_fpga.supports.ts_nand.present == 1)
		ts78xx_ts_nand_unload();
	if (ts78xx_fpga.supports.ts_rng.present == 1)
		ts78xx_ts_rng_unload();

	return ret;
}

static int ts78xx_fpga_load(void)
{
	ts78xx_fpga.id = readl(TS78XX_FPGA_REGS_VIRT_BASE);

	pr_info("FPGA magic=0x%.6x, rev=0x%.2x\n",
			(ts78xx_fpga.id >> 8) & 0xffffff,
			ts78xx_fpga.id & 0xff);

	ts78xx_fpga_supports();

	if (ts78xx_fpga_load_devices()) {
		ts78xx_fpga.state = -1;
		return -EBUSY;
	}

	return 0;
};

static int ts78xx_fpga_unload(void)
{
	unsigned int fpga_id;

	fpga_id = readl(TS78XX_FPGA_REGS_VIRT_BASE);

	/*
                                                                        
                                                                         
                                                  
   
                                                            
  */
	if (ts78xx_fpga.id != fpga_id) {
		pr_err("FPGA magic/rev mismatch\n"
			"TS-78xx FPGA: was 0x%.6x/%.2x but now 0x%.6x/%.2x\n",
			(ts78xx_fpga.id >> 8) & 0xffffff, ts78xx_fpga.id & 0xff,
			(fpga_id >> 8) & 0xffffff, fpga_id & 0xff);
		ts78xx_fpga.state = -1;
		return -EBUSY;
	}

	if (ts78xx_fpga_unload_devices()) {
		ts78xx_fpga.state = -1;
		return -EBUSY;
	}

	return 0;
};

static ssize_t ts78xx_fpga_show(struct kobject *kobj,
			struct kobj_attribute *attr, char *buf)
{
	if (ts78xx_fpga.state < 0)
		return sprintf(buf, "borked\n");

	return sprintf(buf, "%s\n", (ts78xx_fpga.state) ? "online" : "offline");
}

static ssize_t ts78xx_fpga_store(struct kobject *kobj,
			struct kobj_attribute *attr, const char *buf, size_t n)
{
	int value, ret;

	if (ts78xx_fpga.state < 0) {
		pr_err("FPGA borked, you must powercycle ASAP\n");
		return -EBUSY;
	}

	if (strncmp(buf, "online", sizeof("online") - 1) == 0)
		value = 1;
	else if (strncmp(buf, "offline", sizeof("offline") - 1) == 0)
		value = 0;
	else
		return -EINVAL;

	if (ts78xx_fpga.state == value)
		return n;

	ret = (ts78xx_fpga.state == 0)
		? ts78xx_fpga_load()
		: ts78xx_fpga_unload();

	if (!(ret < 0))
		ts78xx_fpga.state = value;

	return n;
}

static struct kobj_attribute ts78xx_fpga_attr =
	__ATTR(ts78xx_fpga, 0644, ts78xx_fpga_show, ts78xx_fpga_store);

/*                                                                            
                
                                                                            */
static unsigned int ts78xx_mpp_modes[] __initdata = {
	MPP0_UNUSED,
	MPP1_GPIO,		/*            */
	MPP2_GPIO,		/*              */
	MPP3_GPIO,		/*                          */
	MPP4_GPIO,		/*               */
	MPP5_GPIO,		/*          */
	MPP6_GPIO,		/*                                 */
	MPP7_GPIO,		/*                           */
	MPP8_UNUSED,
	MPP9_UNUSED,
	MPP10_UNUSED,
	MPP11_UNUSED,
	MPP12_UNUSED,
	MPP13_UNUSED,
	MPP14_UNUSED,
	MPP15_UNUSED,
	MPP16_UART,
	MPP17_UART,
	MPP18_UART,
	MPP19_UART,
	/*
                           
                           
                  
                  
                  
                  
  */
	0,
};

static void __init ts78xx_init(void)
{
	int ret;

	/*
                                                         
  */
	orion5x_init();

	orion5x_mpp_conf(ts78xx_mpp_modes);

	/*
                          
  */
	orion5x_ehci0_init();
	orion5x_ehci1_init();
	orion5x_eth_init(&ts78xx_eth_data);
	orion5x_sata_init(&ts78xx_sata_data);
	orion5x_uart0_init();
	orion5x_uart1_init();
	orion5x_xor_init();

	/*           */
	ts78xx_fpga_devices_zero_init();
	ret = ts78xx_fpga_load();
	ret = sysfs_create_file(firmware_kobj, &ts78xx_fpga_attr.attr);
	if (ret)
		pr_err("sysfs_create_file failed: %d\n", ret);
}

MACHINE_START(TS78XX, "Technologic Systems TS-78xx SBC")
	/*                                                    */
	.atag_offset	= 0x100,
	.init_machine	= ts78xx_init,
	.map_io		= ts78xx_map_io,
	.init_early	= orion5x_init_early,
	.init_irq	= orion5x_init_irq,
	.init_time	= orion5x_timer_init,
	.restart	= orion5x_restart,
MACHINE_END
