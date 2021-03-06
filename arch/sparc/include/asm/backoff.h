#ifndef _SPARC64_BACKOFF_H
#define _SPARC64_BACKOFF_H

/*                                                                  
                         
  
                                                              
                                                                
                                                           
                                                              
                        
  
                                                                    
                                                                   
                                                               
           
  
                                                               
                                                                 
                                                                
                                        
  
                                                               
                                                                      
                                
  
                                                               
                                                                   
                                                                     
                                                                 
                                                                    
                                                                     
                                                                     
                                                                     
                           
  
                                                                     
                                                                     
                                                                     
                                                                     
                              
 */

#define BACKOFF_LIMIT	(4 * 1024)

#ifdef CONFIG_SMP

#define BACKOFF_SETUP(reg)	\
	mov	1, reg

#define BACKOFF_LABEL(spin_label, continue_label) \
	spin_label

#define BACKOFF_SPIN(reg, tmp, label)		\
	mov		reg, tmp;		\
88:	rd		%ccr, %g0;		\
	rd		%ccr, %g0;		\
	rd		%ccr, %g0;		\
	.section	.pause_3insn_patch,"ax";\
	.word		88b;			\
	sllx		tmp, 7, tmp;		\
	wr		tmp, 0, %asr27;		\
	clr		tmp;			\
	.previous;				\
	brnz,pt		tmp, 88b;		\
	 sub		tmp, 1, tmp;		\
	set		BACKOFF_LIMIT, tmp;	\
	cmp		reg, tmp;		\
	bg,pn		%xcc, label;		\
	 nop;					\
	ba,pt		%xcc, label;		\
	 sllx		reg, 1, reg;

#else

#define BACKOFF_SETUP(reg)

#define BACKOFF_LABEL(spin_label, continue_label) \
	continue_label

#define BACKOFF_SPIN(reg, tmp, label)

#endif

#endif /*                    */
