/*
 * intel_idle.c - native hardware idle loop for modern Intel processors
 *
 * Copyright (c) 2010, Intel Corporation.
 * Len Brown <len.brown@intel.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 */

/*
                                                                         
                                                                      
                                                                     
                                                                       
 */

/*
                     
  
                                             
  
                                                  
                                         
 */

/*
                    
  
                                                                        
                                                                  
                                                              
                                                         
  
                                                                     
                                                          
                                                                        
  
                                                                         
                                      
 */

/*                                                  */
#define DEBUG

#include <linux/kernel.h>
#include <linux/cpuidle.h>
#include <linux/clockchips.h>
#include <trace/events/power.h>
#include <linux/sched.h>
#include <linux/notifier.h>
#include <linux/cpu.h>
#include <linux/module.h>
#include <asm/cpu_device_id.h>
#include <asm/mwait.h>
#include <asm/msr.h>

#define INTEL_IDLE_VERSION "0.4"
#define PREFIX "intel_idle: "

static struct cpuidle_driver intel_idle_driver = {
	.name = "intel_idle",
	.owner = THIS_MODULE,
};
/*                                         */
static int max_cstate = CPUIDLE_STATE_MAX - 1;

static unsigned int mwait_substates;

#define LAPIC_TIMER_ALWAYS_RELIABLE 0xFFFFFFFF
/*                                                 */
static unsigned int lapic_timer_reliable_states = (1 << 1);	 /*                    */

struct idle_cpu {
	struct cpuidle_state *state_table;

	/*
                                                             
                                             
  */
	unsigned long auto_demotion_disable_flags;
	bool disable_promotion_to_c1e;
};

static const struct idle_cpu *icpu;
static struct cpuidle_device __percpu *intel_idle_cpuidle_devices;
static int intel_idle(struct cpuidle_device *dev,
			struct cpuidle_driver *drv, int index);
static int intel_idle_cpu_init(int cpu);

static struct cpuidle_state *cpuidle_state_table;

/*
                                                               
                                                          
                                                          
                                                        
 */
#define CPUIDLE_FLAG_TLB_FLUSHED	0x10000

/*
                                                  
                                                         
                                                      
  
                                                              
 */
#define flg2MWAIT(flags) (((flags) >> 24) & 0xFF)
#define MWAIT2flg(eax) ((eax & 0xFF) << 24)

/*
                                           
                                                     
                      
 */
static struct cpuidle_state nehalem_cstates[CPUIDLE_STATE_MAX] = {
	{
		.name = "C1-NHM",
		.desc = "MWAIT 0x00",
		.flags = MWAIT2flg(0x00) | CPUIDLE_FLAG_TIME_VALID,
		.exit_latency = 3,
		.target_residency = 6,
		.enter = &intel_idle },
	{
		.name = "C1E-NHM",
		.desc = "MWAIT 0x01",
		.flags = MWAIT2flg(0x01) | CPUIDLE_FLAG_TIME_VALID,
		.exit_latency = 10,
		.target_residency = 20,
		.enter = &intel_idle },
	{
		.name = "C3-NHM",
		.desc = "MWAIT 0x10",
		.flags = MWAIT2flg(0x10) | CPUIDLE_FLAG_TIME_VALID | CPUIDLE_FLAG_TLB_FLUSHED,
		.exit_latency = 20,
		.target_residency = 80,
		.enter = &intel_idle },
	{
		.name = "C6-NHM",
		.desc = "MWAIT 0x20",
		.flags = MWAIT2flg(0x20) | CPUIDLE_FLAG_TIME_VALID | CPUIDLE_FLAG_TLB_FLUSHED,
		.exit_latency = 200,
		.target_residency = 800,
		.enter = &intel_idle },
	{
		.enter = NULL }
};

static struct cpuidle_state snb_cstates[CPUIDLE_STATE_MAX] = {
	{
		.name = "C1-SNB",
		.desc = "MWAIT 0x00",
		.flags = MWAIT2flg(0x00) | CPUIDLE_FLAG_TIME_VALID,
		.exit_latency = 2,
		.target_residency = 2,
		.enter = &intel_idle },
	{
		.name = "C1E-SNB",
		.desc = "MWAIT 0x01",
		.flags = MWAIT2flg(0x01) | CPUIDLE_FLAG_TIME_VALID,
		.exit_latency = 10,
		.target_residency = 20,
		.enter = &intel_idle },
	{
		.name = "C3-SNB",
		.desc = "MWAIT 0x10",
		.flags = MWAIT2flg(0x10) | CPUIDLE_FLAG_TIME_VALID | CPUIDLE_FLAG_TLB_FLUSHED,
		.exit_latency = 80,
		.target_residency = 211,
		.enter = &intel_idle },
	{
		.name = "C6-SNB",
		.desc = "MWAIT 0x20",
		.flags = MWAIT2flg(0x20) | CPUIDLE_FLAG_TIME_VALID | CPUIDLE_FLAG_TLB_FLUSHED,
		.exit_latency = 104,
		.target_residency = 345,
		.enter = &intel_idle },
	{
		.name = "C7-SNB",
		.desc = "MWAIT 0x30",
		.flags = MWAIT2flg(0x30) | CPUIDLE_FLAG_TIME_VALID | CPUIDLE_FLAG_TLB_FLUSHED,
		.exit_latency = 109,
		.target_residency = 345,
		.enter = &intel_idle },
	{
		.enter = NULL }
};

static struct cpuidle_state ivb_cstates[CPUIDLE_STATE_MAX] = {
	{
		.name = "C1-IVB",
		.desc = "MWAIT 0x00",
		.flags = MWAIT2flg(0x00) | CPUIDLE_FLAG_TIME_VALID,
		.exit_latency = 1,
		.target_residency = 1,
		.enter = &intel_idle },
	{
		.name = "C1E-IVB",
		.desc = "MWAIT 0x01",
		.flags = MWAIT2flg(0x01) | CPUIDLE_FLAG_TIME_VALID,
		.exit_latency = 10,
		.target_residency = 20,
		.enter = &intel_idle },
	{
		.name = "C3-IVB",
		.desc = "MWAIT 0x10",
		.flags = MWAIT2flg(0x10) | CPUIDLE_FLAG_TIME_VALID | CPUIDLE_FLAG_TLB_FLUSHED,
		.exit_latency = 59,
		.target_residency = 156,
		.enter = &intel_idle },
	{
		.name = "C6-IVB",
		.desc = "MWAIT 0x20",
		.flags = MWAIT2flg(0x20) | CPUIDLE_FLAG_TIME_VALID | CPUIDLE_FLAG_TLB_FLUSHED,
		.exit_latency = 80,
		.target_residency = 300,
		.enter = &intel_idle },
	{
		.name = "C7-IVB",
		.desc = "MWAIT 0x30",
		.flags = MWAIT2flg(0x30) | CPUIDLE_FLAG_TIME_VALID | CPUIDLE_FLAG_TLB_FLUSHED,
		.exit_latency = 87,
		.target_residency = 300,
		.enter = &intel_idle },
	{
		.enter = NULL }
};

static struct cpuidle_state hsw_cstates[CPUIDLE_STATE_MAX] = {
	{
		.name = "C1-HSW",
		.desc = "MWAIT 0x00",
		.flags = MWAIT2flg(0x00) | CPUIDLE_FLAG_TIME_VALID,
		.exit_latency = 2,
		.target_residency = 2,
		.enter = &intel_idle },
	{
		.name = "C1E-HSW",
		.desc = "MWAIT 0x01",
		.flags = MWAIT2flg(0x01) | CPUIDLE_FLAG_TIME_VALID,
		.exit_latency = 10,
		.target_residency = 20,
		.enter = &intel_idle },
	{
		.name = "C3-HSW",
		.desc = "MWAIT 0x10",
		.flags = MWAIT2flg(0x10) | CPUIDLE_FLAG_TIME_VALID | CPUIDLE_FLAG_TLB_FLUSHED,
		.exit_latency = 33,
		.target_residency = 100,
		.enter = &intel_idle },
	{
		.name = "C6-HSW",
		.desc = "MWAIT 0x20",
		.flags = MWAIT2flg(0x20) | CPUIDLE_FLAG_TIME_VALID | CPUIDLE_FLAG_TLB_FLUSHED,
		.exit_latency = 133,
		.target_residency = 400,
		.enter = &intel_idle },
	{
		.name = "C7s-HSW",
		.desc = "MWAIT 0x32",
		.flags = MWAIT2flg(0x32) | CPUIDLE_FLAG_TIME_VALID | CPUIDLE_FLAG_TLB_FLUSHED,
		.exit_latency = 166,
		.target_residency = 500,
		.enter = &intel_idle },
	{
		.name = "C8-HSW",
		.desc = "MWAIT 0x40",
		.flags = MWAIT2flg(0x40) | CPUIDLE_FLAG_TIME_VALID | CPUIDLE_FLAG_TLB_FLUSHED,
		.exit_latency = 300,
		.target_residency = 900,
		.enter = &intel_idle },
	{
		.name = "C9-HSW",
		.desc = "MWAIT 0x50",
		.flags = MWAIT2flg(0x50) | CPUIDLE_FLAG_TIME_VALID | CPUIDLE_FLAG_TLB_FLUSHED,
		.exit_latency = 600,
		.target_residency = 1800,
		.enter = &intel_idle },
	{
		.name = "C10-HSW",
		.desc = "MWAIT 0x60",
		.flags = MWAIT2flg(0x60) | CPUIDLE_FLAG_TIME_VALID | CPUIDLE_FLAG_TLB_FLUSHED,
		.exit_latency = 2600,
		.target_residency = 7700,
		.enter = &intel_idle },
	{
		.enter = NULL }
};

static struct cpuidle_state atom_cstates[CPUIDLE_STATE_MAX] = {
	{
		.name = "C1E-ATM",
		.desc = "MWAIT 0x00",
		.flags = MWAIT2flg(0x00) | CPUIDLE_FLAG_TIME_VALID,
		.exit_latency = 10,
		.target_residency = 20,
		.enter = &intel_idle },
	{
		.name = "C2-ATM",
		.desc = "MWAIT 0x10",
		.flags = MWAIT2flg(0x10) | CPUIDLE_FLAG_TIME_VALID,
		.exit_latency = 20,
		.target_residency = 80,
		.enter = &intel_idle },
	{
		.name = "C4-ATM",
		.desc = "MWAIT 0x30",
		.flags = MWAIT2flg(0x30) | CPUIDLE_FLAG_TIME_VALID | CPUIDLE_FLAG_TLB_FLUSHED,
		.exit_latency = 100,
		.target_residency = 400,
		.enter = &intel_idle },
	{
		.name = "C6-ATM",
		.desc = "MWAIT 0x52",
		.flags = MWAIT2flg(0x52) | CPUIDLE_FLAG_TIME_VALID | CPUIDLE_FLAG_TLB_FLUSHED,
		.exit_latency = 140,
		.target_residency = 560,
		.enter = &intel_idle },
	{
		.enter = NULL }
};

/* 
             
                       
                       
                                 
  
                                            
 */
static int intel_idle(struct cpuidle_device *dev,
		struct cpuidle_driver *drv, int index)
{
	unsigned long ecx = 1; /*                         */
	struct cpuidle_state *state = &drv->states[index];
	unsigned long eax = flg2MWAIT(state->flags);
	unsigned int cstate;
	int cpu = smp_processor_id();

	cstate = (((eax) >> MWAIT_SUBSTATE_SIZE) & MWAIT_CSTATE_MASK) + 1;

	/*
                                                            
                                                              
  */
	if (state->flags & CPUIDLE_FLAG_TLB_FLUSHED)
		leave_mm(cpu);

	if (!(lapic_timer_reliable_states & (1 << (cstate))))
		clockevents_notify(CLOCK_EVT_NOTIFY_BROADCAST_ENTER, &cpu);

	if (!current_set_polling_and_test()) {

		if (this_cpu_has(X86_FEATURE_CLFLUSH_MONITOR))
			clflush((void *)&current_thread_info()->flags);

		__monitor((void *)&current_thread_info()->flags, 0, 0);
		smp_mb();
		if (!need_resched())
			__mwait(eax, ecx);
	}

	if (!(lapic_timer_reliable_states & (1 << (cstate))))
		clockevents_notify(CLOCK_EVT_NOTIFY_BROADCAST_EXIT, &cpu);

	return index;
}

static void __setup_broadcast_timer(void *arg)
{
	unsigned long reason = (unsigned long)arg;
	int cpu = smp_processor_id();

	reason = reason ?
		CLOCK_EVT_NOTIFY_BROADCAST_ON : CLOCK_EVT_NOTIFY_BROADCAST_OFF;

	clockevents_notify(reason, &cpu);
}

static int cpu_hotplug_notify(struct notifier_block *n,
			      unsigned long action, void *hcpu)
{
	int hotcpu = (unsigned long)hcpu;
	struct cpuidle_device *dev;

	switch (action & 0xf) {
	case CPU_ONLINE:

		if (lapic_timer_reliable_states != LAPIC_TIMER_ALWAYS_RELIABLE)
			smp_call_function_single(hotcpu, __setup_broadcast_timer,
						 (void *)true, 1);

		/*
                                                    
                                                     
                        
   */
		dev = per_cpu_ptr(intel_idle_cpuidle_devices, hotcpu);
		if (!dev->registered)
			intel_idle_cpu_init(hotcpu);

		break;
	}
	return NOTIFY_OK;
}

static struct notifier_block cpu_hotplug_notifier = {
	.notifier_call = cpu_hotplug_notify,
};

static void auto_demotion_disable(void *dummy)
{
	unsigned long long msr_bits;

	rdmsrl(MSR_NHM_SNB_PKG_CST_CFG_CTL, msr_bits);
	msr_bits &= ~(icpu->auto_demotion_disable_flags);
	wrmsrl(MSR_NHM_SNB_PKG_CST_CFG_CTL, msr_bits);
}
static void c1e_promotion_disable(void *dummy)
{
	unsigned long long msr_bits;

	rdmsrl(MSR_IA32_POWER_CTL, msr_bits);
	msr_bits &= ~0x2;
	wrmsrl(MSR_IA32_POWER_CTL, msr_bits);
}

static const struct idle_cpu idle_cpu_nehalem = {
	.state_table = nehalem_cstates,
	.auto_demotion_disable_flags = NHM_C1_AUTO_DEMOTE | NHM_C3_AUTO_DEMOTE,
	.disable_promotion_to_c1e = true,
};

static const struct idle_cpu idle_cpu_atom = {
	.state_table = atom_cstates,
};

static const struct idle_cpu idle_cpu_lincroft = {
	.state_table = atom_cstates,
	.auto_demotion_disable_flags = ATM_LNC_C6_AUTO_DEMOTE,
};

static const struct idle_cpu idle_cpu_snb = {
	.state_table = snb_cstates,
	.disable_promotion_to_c1e = true,
};

static const struct idle_cpu idle_cpu_ivb = {
	.state_table = ivb_cstates,
	.disable_promotion_to_c1e = true,
};

static const struct idle_cpu idle_cpu_hsw = {
	.state_table = hsw_cstates,
	.disable_promotion_to_c1e = true,
};

#define ICPU(model, cpu) \
	{ X86_VENDOR_INTEL, 6, model, X86_FEATURE_MWAIT, (unsigned long)&cpu }

static const struct x86_cpu_id intel_idle_ids[] = {
	ICPU(0x1a, idle_cpu_nehalem),
	ICPU(0x1e, idle_cpu_nehalem),
	ICPU(0x1f, idle_cpu_nehalem),
	ICPU(0x25, idle_cpu_nehalem),
	ICPU(0x2c, idle_cpu_nehalem),
	ICPU(0x2e, idle_cpu_nehalem),
	ICPU(0x1c, idle_cpu_atom),
	ICPU(0x26, idle_cpu_lincroft),
	ICPU(0x2f, idle_cpu_nehalem),
	ICPU(0x2a, idle_cpu_snb),
	ICPU(0x2d, idle_cpu_snb),
	ICPU(0x3a, idle_cpu_ivb),
	ICPU(0x3e, idle_cpu_ivb),
	ICPU(0x3c, idle_cpu_hsw),
	ICPU(0x3f, idle_cpu_hsw),
	ICPU(0x45, idle_cpu_hsw),
	ICPU(0x46, idle_cpu_hsw),
	{}
};
MODULE_DEVICE_TABLE(x86cpu, intel_idle_ids);

/*
                     
 */
static int intel_idle_probe(void)
{
	unsigned int eax, ebx, ecx;
	const struct x86_cpu_id *id;

	if (max_cstate == 0) {
		pr_debug(PREFIX "disabled\n");
		return -EPERM;
	}

	id = x86_match_cpu(intel_idle_ids);
	if (!id) {
		if (boot_cpu_data.x86_vendor == X86_VENDOR_INTEL &&
		    boot_cpu_data.x86 == 6)
			pr_debug(PREFIX "does not run on family %d model %d\n",
				boot_cpu_data.x86, boot_cpu_data.x86_model);
		return -ENODEV;
	}

	if (boot_cpu_data.cpuid_level < CPUID_MWAIT_LEAF)
		return -ENODEV;

	cpuid(CPUID_MWAIT_LEAF, &eax, &ebx, &ecx, &mwait_substates);

	if (!(ecx & CPUID5_ECX_EXTENSIONS_SUPPORTED) ||
	    !(ecx & CPUID5_ECX_INTERRUPT_BREAK) ||
	    !mwait_substates)
			return -ENODEV;

	pr_debug(PREFIX "MWAIT substates: 0x%x\n", mwait_substates);

	icpu = (const struct idle_cpu *)id->driver_data;
	cpuidle_state_table = icpu->state_table;

	if (boot_cpu_has(X86_FEATURE_ARAT))	/*                            */
		lapic_timer_reliable_states = LAPIC_TIMER_ALWAYS_RELIABLE;
	else
		on_each_cpu(__setup_broadcast_timer, (void *)true, 1);

	pr_debug(PREFIX "v" INTEL_IDLE_VERSION
		" model 0x%X\n", boot_cpu_data.x86_model);

	pr_debug(PREFIX "lapic_timer_reliable_states 0x%x\n",
		lapic_timer_reliable_states);
	return 0;
}

/*
                                      
                                   
 */
static void intel_idle_cpuidle_devices_uninit(void)
{
	int i;
	struct cpuidle_device *dev;

	for_each_online_cpu(i) {
		dev = per_cpu_ptr(intel_idle_cpuidle_devices, i);
		cpuidle_unregister_device(dev);
	}

	free_percpu(intel_idle_cpuidle_devices);
	return;
}
/*
                                   
                                      
 */
static int intel_idle_cpuidle_driver_init(void)
{
	int cstate;
	struct cpuidle_driver *drv = &intel_idle_driver;

	drv->state_count = 1;

	for (cstate = 0; cstate < CPUIDLE_STATE_MAX; ++cstate) {
		int num_substates, mwait_hint, mwait_cstate, mwait_substate;

		if (cpuidle_state_table[cstate].enter == NULL)
			break;

		if (cstate + 1 > max_cstate) {
			printk(PREFIX "max_cstate %d reached\n",
				max_cstate);
			break;
		}

		mwait_hint = flg2MWAIT(cpuidle_state_table[cstate].flags);
		mwait_cstate = MWAIT_HINT2CSTATE(mwait_hint);
		mwait_substate = MWAIT_HINT2SUBSTATE(mwait_hint);

		/*                                      */
		num_substates = (mwait_substates >> ((mwait_cstate + 1) * 4))
					& MWAIT_SUBSTATE_MASK;

		/*                                                  */
		if ((mwait_substate + 1) > num_substates)
			continue;

		if (((mwait_cstate + 1) > 2) &&
			!boot_cpu_has(X86_FEATURE_NONSTOP_TSC))
			mark_tsc_unstable("TSC halts in idle"
					" states deeper than C2");

		drv->states[drv->state_count] =	/*                */
			cpuidle_state_table[cstate];

		drv->state_count += 1;
	}

	if (icpu->auto_demotion_disable_flags)
		on_each_cpu(auto_demotion_disable, NULL, 1);

	if (icpu->disable_promotion_to_c1e)	/*                       */
		on_each_cpu(c1e_promotion_disable, NULL, 1);

	return 0;
}


/*
                        
                                                 
                               
 */
static int intel_idle_cpu_init(int cpu)
{
	int cstate;
	struct cpuidle_device *dev;

	dev = per_cpu_ptr(intel_idle_cpuidle_devices, cpu);

	dev->state_count = 1;

	for (cstate = 0; cstate < CPUIDLE_STATE_MAX; ++cstate) {
		int num_substates, mwait_hint, mwait_cstate, mwait_substate;

		if (cpuidle_state_table[cstate].enter == NULL)
			continue;

		if (cstate + 1 > max_cstate) {
			printk(PREFIX "max_cstate %d reached\n", max_cstate);
			break;
		}

		mwait_hint = flg2MWAIT(cpuidle_state_table[cstate].flags);
		mwait_cstate = MWAIT_HINT2CSTATE(mwait_hint);
		mwait_substate = MWAIT_HINT2SUBSTATE(mwait_hint);

		/*                                      */
		num_substates = (mwait_substates >> ((mwait_cstate + 1) * 4))
					& MWAIT_SUBSTATE_MASK;

		/*                                                  */
		if ((mwait_substate + 1) > num_substates)
			continue;

		dev->state_count += 1;
	}

	dev->cpu = cpu;

	if (cpuidle_register_device(dev)) {
		pr_debug(PREFIX "cpuidle_register_device %d failed!\n", cpu);
		intel_idle_cpuidle_devices_uninit();
		return -EIO;
	}

	if (icpu->auto_demotion_disable_flags)
		smp_call_function_single(cpu, auto_demotion_disable, NULL, 1);

	return 0;
}

static int __init intel_idle_init(void)
{
	int retval, i;

	/*                                                          */
	if (boot_option_idle_override != IDLE_NO_OVERRIDE)
		return -ENODEV;

	retval = intel_idle_probe();
	if (retval)
		return retval;

	intel_idle_cpuidle_driver_init();
	retval = cpuidle_register_driver(&intel_idle_driver);
	if (retval) {
		struct cpuidle_driver *drv = cpuidle_get_driver();
		printk(KERN_DEBUG PREFIX "intel_idle yielding to %s",
			drv ? drv->name : "none");
		return retval;
	}

	intel_idle_cpuidle_devices = alloc_percpu(struct cpuidle_device);
	if (intel_idle_cpuidle_devices == NULL)
		return -ENOMEM;

	for_each_online_cpu(i) {
		retval = intel_idle_cpu_init(i);
		if (retval) {
			cpuidle_unregister_driver(&intel_idle_driver);
			return retval;
		}
	}
	register_cpu_notifier(&cpu_hotplug_notifier);

	return 0;
}

static void __exit intel_idle_exit(void)
{
	intel_idle_cpuidle_devices_uninit();
	cpuidle_unregister_driver(&intel_idle_driver);


	if (lapic_timer_reliable_states != LAPIC_TIMER_ALWAYS_RELIABLE)
		on_each_cpu(__setup_broadcast_timer, (void *)false, 1);
	unregister_cpu_notifier(&cpu_hotplug_notifier);

	return;
}

module_init(intel_idle_init);
module_exit(intel_idle_exit);

module_param(max_cstate, int, 0444);

MODULE_AUTHOR("Len Brown <len.brown@intel.com>");
MODULE_DESCRIPTION("Cpuidle driver for Intel Hardware v" INTEL_IDLE_VERSION);
MODULE_LICENSE("GPL");
