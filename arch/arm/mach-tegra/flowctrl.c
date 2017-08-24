/*
 * arch/arm/mach-tegra/flowctrl.c
 *
 * functions and macros to control the flowcontroller
 *
 * Copyright (c) 2010-2012, NVIDIA Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/io.h>
#include <linux/cpumask.h>

#include "flowctrl.h"
#include "iomap.h"
#include "fuse.h"

static u8 flowctrl_offset_halt_cpu[] = {
	FLOW_CTRL_HALT_CPU0_EVENTS,
	FLOW_CTRL_HALT_CPU1_EVENTS,
	FLOW_CTRL_HALT_CPU1_EVENTS + 8,
	FLOW_CTRL_HALT_CPU1_EVENTS + 16,
};

static u8 flowctrl_offset_cpu_csr[] = {
	FLOW_CTRL_CPU0_CSR,
	FLOW_CTRL_CPU1_CSR,
	FLOW_CTRL_CPU1_CSR + 8,
	FLOW_CTRL_CPU1_CSR + 16,
};

static void flowctrl_update(u8 offset, u32 value)
{
	void __iomem *addr = IO_ADDRESS(TEGRA_FLOW_CTRL_BASE) + offset;

	writel(value, addr);

	/*                                                   */
	wmb();
	readl_relaxed(addr);
}

u32 flowctrl_read_cpu_csr(unsigned int cpuid)
{
	u8 offset = flowctrl_offset_cpu_csr[cpuid];
	void __iomem *addr = IO_ADDRESS(TEGRA_FLOW_CTRL_BASE) + offset;

	return readl(addr);
}

void flowctrl_write_cpu_csr(unsigned int cpuid, u32 value)
{
	return flowctrl_update(flowctrl_offset_cpu_csr[cpuid], value);
}

void flowctrl_write_cpu_halt(unsigned int cpuid, u32 value)
{
	return flowctrl_update(flowctrl_offset_halt_cpu[cpuid], value);
}

void flowctrl_cpu_suspend_enter(unsigned int cpuid)
{
	unsigned int reg;
	int i;

	reg = flowctrl_read_cpu_csr(cpuid);
	switch (tegra_chip_id) {
	case TEGRA20:
		/*                  */
		reg &= ~TEGRA20_FLOW_CTRL_CSR_WFE_BITMAP;
		/*                  */
		reg &= ~TEGRA20_FLOW_CTRL_CSR_WFI_BITMAP;
		/*                   */
		reg |= TEGRA20_FLOW_CTRL_CSR_WFE_CPU0 << cpuid;
		break;
	case TEGRA30:
		/*                  */
		reg &= ~TEGRA30_FLOW_CTRL_CSR_WFE_BITMAP;
		/*                  */
		reg &= ~TEGRA30_FLOW_CTRL_CSR_WFI_BITMAP;
		/*                   */
		reg |= TEGRA30_FLOW_CTRL_CSR_WFI_CPU0 << cpuid;
		break;
	}
	reg |= FLOW_CTRL_CSR_INTR_FLAG;			/*                 */
	reg |= FLOW_CTRL_CSR_EVENT_FLAG;		/*                  */
	reg |= FLOW_CTRL_CSR_ENABLE;			/*            */
	flowctrl_write_cpu_csr(cpuid, reg);

	for (i = 0; i < num_possible_cpus(); i++) {
		if (i == cpuid)
			continue;
		reg = flowctrl_read_cpu_csr(i);
		reg |= FLOW_CTRL_CSR_EVENT_FLAG;
		reg |= FLOW_CTRL_CSR_INTR_FLAG;
		flowctrl_write_cpu_csr(i, reg);
	}
}

void flowctrl_cpu_suspend_exit(unsigned int cpuid)
{
	unsigned int reg;

	/*                                                  */
	reg = flowctrl_read_cpu_csr(cpuid);
	switch (tegra_chip_id) {
	case TEGRA20:
		/*                  */
		reg &= ~TEGRA20_FLOW_CTRL_CSR_WFE_BITMAP;
		/*                  */
		reg &= ~TEGRA20_FLOW_CTRL_CSR_WFI_BITMAP;
		break;
	case TEGRA30:
		/*                  */
		reg &= ~TEGRA30_FLOW_CTRL_CSR_WFE_BITMAP;
		/*                  */
		reg &= ~TEGRA30_FLOW_CTRL_CSR_WFI_BITMAP;
		break;
	}
	reg &= ~FLOW_CTRL_CSR_ENABLE;			/*              */
	reg |= FLOW_CTRL_CSR_INTR_FLAG;			/*            */
	reg |= FLOW_CTRL_CSR_EVENT_FLAG;		/*             */
	flowctrl_write_cpu_csr(cpuid, reg);
}
