/*
 *  arch/arm/include/asm/domain.h
 *
 *  Copyright (C) 1999 Russell King.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef __ASM_PROC_DOMAIN_H
#define __ASM_PROC_DOMAIN_H

#ifndef __ASSEMBLY__
#include <asm/barrier.h>
#endif

/*
                 
  
                                                 
                                                          
                                                            
  
                                                                 
                                                                   
                                                                
                                                                    
                                                                   
                                                                
                                                    
  
                                                            
                                               
 */
#ifndef CONFIG_IO_36
#define DOMAIN_KERNEL	0
#define DOMAIN_TABLE	0
#define DOMAIN_USER	1
#define DOMAIN_IO	2
#else
#define DOMAIN_KERNEL	2
#define DOMAIN_TABLE	2
#define DOMAIN_USER	1
#define DOMAIN_IO	0
#endif

/*
               
 */
#define DOMAIN_NOACCESS	0
#define DOMAIN_CLIENT	1
#ifdef CONFIG_CPU_USE_DOMAINS
#define DOMAIN_MANAGER	3
#else
#define DOMAIN_MANAGER	1
#endif

#define domain_val(dom,type)	((type) << (2*(dom)))

#ifndef __ASSEMBLY__

#ifdef CONFIG_CPU_USE_DOMAINS
static inline void set_domain(unsigned val)
{
	asm volatile(
	"mcr	p15, 0, %0, c3, c0	@ set domain"
	  : : "r" (val));
	isb();
}

#define modify_domain(dom,type)					\
	do {							\
	struct thread_info *thread = current_thread_info();	\
	unsigned int domain = thread->cpu_domain;		\
	domain &= ~domain_val(dom, DOMAIN_MANAGER);		\
	thread->cpu_domain = domain | domain_val(dom, type);	\
	set_domain(thread->cpu_domain);				\
	} while (0)

#else
static inline void set_domain(unsigned val) { }
static inline void modify_domain(unsigned dom, unsigned type)	{ }
#endif

/*
                                                            
                                 
 */
#ifdef CONFIG_CPU_USE_DOMAINS
#define TUSER(instr)	#instr "t"
#else
#define TUSER(instr)	#instr
#endif

#else /*              */

/*
                                                            
               
 */
#ifdef CONFIG_CPU_USE_DOMAINS
#define TUSER(instr)	instr ## t
#else
#define TUSER(instr)	instr
#endif

#endif /*              */

#endif /*                      */
