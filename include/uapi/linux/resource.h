#ifndef _UAPI_LINUX_RESOURCE_H
#define _UAPI_LINUX_RESOURCE_H

#include <linux/time.h>
#include <linux/types.h>

/*
                                                    
 */

/*
 * Definition of struct rusage taken from BSD 4.3 Reno
 * 
 * We don't support all of these yet, but we might as well have them....
 * Otherwise, each time we add new items, programs which depend on this
 * structure will lose.  This reduces the chances of that happening.
 */
#define	RUSAGE_SELF	0
#define	RUSAGE_CHILDREN	(-1)
#define RUSAGE_BOTH	(-2)		/*                       */
#define	RUSAGE_THREAD	1		/*                         */

struct	rusage {
	struct timeval ru_utime;	/*                */
	struct timeval ru_stime;	/*                  */
	long	ru_maxrss;		/*                           */
	long	ru_ixrss;		/*                             */
	long	ru_idrss;		/*                             */
	long	ru_isrss;		/*                              */
	long	ru_minflt;		/*               */
	long	ru_majflt;		/*             */
	long	ru_nswap;		/*       */
	long	ru_inblock;		/*                        */
	long	ru_oublock;		/*                         */
	long	ru_msgsnd;		/*               */
	long	ru_msgrcv;		/*                   */
	long	ru_nsignals;		/*                  */
	long	ru_nvcsw;		/*                            */
	long	ru_nivcsw;		/*               */
};

struct rlimit {
	unsigned long	rlim_cur;
	unsigned long	rlim_max;
};

#define RLIM64_INFINITY		(~0ULL)

struct rlimit64 {
	__u64 rlim_cur;
	__u64 rlim_max;
};

#define	PRIO_MIN	(-20)
#define	PRIO_MAX	20

#define	PRIO_PROCESS	0
#define	PRIO_PGRP	1
#define	PRIO_USER	2

/*
                                                           
                                                         
 */
#define _STK_LIM	(8*1024*1024)

/*
                                                               
                                                             
 */
#define MLOCK_LIMIT	((PAGE_SIZE > 64*1024) ? PAGE_SIZE : 64*1024)

/*
                                                           
                                                  
 */
#include <asm/resource.h>


#endif /*                        */
