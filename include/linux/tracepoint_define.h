#ifndef _LINUX_TRACEPOINT_H
#include <linux/tracepoint.h>
#else

#ifndef _TRACEPOINT_DEFINE
#define _TRACEPOINT_DEFINE

#ifdef CONFIG_TRACEPOINTS
/*
                                                                             
                                                                        
                                                                         
 */
#undef TP_PROTO
#define TP_PROTO(args...)	args
#undef TP_ARGS
#define TP_ARGS(args...)	args
#undef PARAMS
#define PARAMS(args...) args

#undef DECLARE_TRACE
#define DECLARE_TRACE(name, proto, args)				\
	extern struct tracepoint __tracepoint_##name;			\
	static inline void trace_##name(proto)				\
	{								\
		if (unlikely(__tracepoint_##name.state))		\
			__DO_TRACE(&__tracepoint_##name,		\
				TP_PROTO(proto), TP_ARGS(args));	\
	}								\
	static inline int register_trace_##name(void (*probe)(proto))	\
	{								\
		return tracepoint_probe_register(#name, (void *)probe);	\
	}								\
	static inline int unregister_trace_##name(void (*probe)(proto))	\
	{								\
		return tracepoint_probe_unregister(#name, (void *)probe);\
	}

#else				/*                     */
#undef DECLARE_TRACE
#define DECLARE_TRACE(name, proto, args)				\
	static inline void _do_trace_##name(struct tracepoint *tp, proto) \
	{ }								\
	static inline void trace_##name(proto)				\
	{ }								\
	static inline int register_trace_##name(void (*probe)(proto))	\
	{								\
		return -ENOSYS;						\
	}								\
	static inline int unregister_trace_##name(void (*probe)(proto))	\
	{								\
		return -ENOSYS;						\
	}
#endif				/*                    */

/*                                                */

#undef TRACE_EVENT
#define TRACE_EVENT(name, proto, args, struct, assign, print)	\
	DECLARE_TRACE(name, PARAMS(proto), PARAMS(args))
#undef TRACE_EVENT_FN
#define TRACE_EVENT_FN(name, proto, args, struct,		\
		assign, print, reg, unreg)			\
	DECLARE_TRACE(name, PARAMS(proto), PARAMS(args))
#endif /*                  */
#endif				/*                     */
