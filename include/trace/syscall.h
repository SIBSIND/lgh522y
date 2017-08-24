#ifndef _TRACE_SYSCALL_H
#define _TRACE_SYSCALL_H

#include <linux/tracepoint.h>
#include <linux/unistd.h>
#include <linux/ftrace_event.h>
#include <linux/thread_info.h>

#include <asm/ptrace.h>


/*
                                                
  
                             
                                     
                                          
                                   
                                                            
                                                     
                                                   
 */
struct syscall_metadata {
	const char	*name;
	int		syscall_nr;
	int		nb_args;
	const char	**types;
	const char	**args;
	struct list_head enter_fields;

	struct ftrace_event_call *enter_event;
	struct ftrace_event_call *exit_event;
};

#if defined(CONFIG_TRACEPOINTS) && defined(CONFIG_HAVE_SYSCALL_TRACEPOINTS)
static inline void syscall_tracepoint_update(struct task_struct *p)
{
	if (test_thread_flag(TIF_SYSCALL_TRACEPOINT))
		set_tsk_thread_flag(p, TIF_SYSCALL_TRACEPOINT);
	else
		clear_tsk_thread_flag(p, TIF_SYSCALL_TRACEPOINT);
}
#else
static inline void syscall_tracepoint_update(struct task_struct *p)
{
}
#endif

#endif /*                  */
