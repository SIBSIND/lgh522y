/*
 *  (C) 2010,2011       Thomas Renninger <trenn@suse.de>, Novell Inc.
 *
 *  Licensed under the terms of the GNU GPL License version 2.
 *
 */

#ifndef __CPUIDLE_INFO_HW__
#define __CPUIDLE_INFO_HW__

#include <stdarg.h>
#include <time.h>

#include "idle_monitor/idle_monitors.h"

#define MONITORS_MAX 20
#define MONITOR_NAME_LEN 20
#define CSTATE_NAME_LEN 5
#define CSTATE_DESC_LEN 60

int cpu_count;

/*                                     */
enum power_range_e {
	RANGE_THREAD,	/*                                                      
                        */
	RANGE_CORE,	/*                                               */
	RANGE_PACKAGE,	/*                           */
	RANGE_MACHINE,	/*                        */
	RANGE_MAX };

typedef struct cstate {
	int  id;
	enum power_range_e range;
	char name[CSTATE_NAME_LEN];
	char desc[CSTATE_DESC_LEN];

	/*                                                */
	int (*get_count_percent)(unsigned int self_id, double *percent,
				 unsigned int cpu);
	int (*get_count)(unsigned int self_id, unsigned long long *count,
			 unsigned int cpu);
} cstate_t;

struct cpuidle_monitor {
	/*                                   */
	char name[MONITOR_NAME_LEN];
	int name_len;
	int hw_states_num;
	cstate_t *hw_states;
	int (*start) (void);
	int (*stop) (void);
	struct cpuidle_monitor* (*do_register) (void);
	void (*unregister)(void);
	unsigned int overflow_s;
	int needs_root;
};

extern long long timespec_diff_us(struct timespec start, struct timespec end);

#define print_overflow_err(mes, ov)						\
{										\
	fprintf(stderr, gettext("Measure took %u seconds, but registers could "	\
				"overflow at %u seconds, results "		\
				"could be inaccurate\n"), mes, ov);		\
}


/*                                                                 */
#include <sched.h>
#include <sys/types.h>
#include <unistd.h>
static inline int bind_cpu(int cpu)
{
	cpu_set_t set;

	if (sched_getaffinity(getpid(), sizeof(set), &set) == 0) {
		CPU_ZERO(&set);
		CPU_SET(cpu, &set);
		return sched_setaffinity(getpid(), sizeof(set), &set);
	}
	return 1;
}

#endif /*                     */
