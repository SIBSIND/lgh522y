/*
 * Copyright (c) 2013-2014 TRUSTONIC LIMITED
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the TRUSTONIC LIMITED nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
                                                                              
                                                                              
                                                                              
                                                                      
                                                          
                                                                         
                                                                           
                                                                      
 */

#ifndef _MC_LINUX_H_
#define _MC_LINUX_H_

#include "version.h"

#ifndef __KERNEL__
#include <stdint.h>
#endif

#define MC_ADMIN_DEVNODE	"mobicore"
#define MC_USER_DEVNODE		"mobicore-user"

/*
                                                                   
                           
 */
struct mc_ioctl_init {
	/*                              */
	uint32_t  nq_length;
	/*                                                 */
	uint32_t  mcp_offset;
	/*                      */
	uint32_t  mcp_length;
};

/*
                                                                   
                               
 */
struct mc_ioctl_info {
	uint32_t  ext_info_id;	/*                  */
	uint32_t  state;	/*       */
	uint32_t  ext_info;	/*               */
};

/*
                                                                           
  
                                                     
                                                               
                                                                         
                                                                            
                                      
 */
struct mc_ioctl_map {
	uint32_t	len;	/*               */
	uint32_t	handle;	/*            */
	uint64_t	phys_addr; /*                                */
	uint32_t	rfu;
	bool		reused;	/*                                            */
};

/*
                                                        
  
                                                                     
                                                 
                                                                               
                                       
  
                                                                
                                                                  
 */
struct mc_compat_ioctl_reg_wsm {
	uint32_t buffer;	/*                                      */
	uint32_t len;		/*                                   */
	uint32_t pid;		/*            */
	uint32_t handle;	/*                                 */
	uint64_t table_phys;	/*                                   */
};

struct mc_ioctl_reg_wsm {
	uint64_t buffer;	/*                                      */
	uint32_t len;		/*                                   */
	uint32_t pid;		/*            */
	uint32_t handle;	/*                                 */
	uint64_t table_phys;/*                                   */
};

/*
                                                                       
 */
struct mc_ioctl_resolv_cont_wsm {
	/*                          */
	uint32_t handle;
	/*               */
	uint32_t length;
	/*                        */
	uint64_t phys;
	/*                           */
	int32_t fd;
};

/*
                                                                  
 */
struct mc_ioctl_resolv_wsm {
	/*                          */
	uint32_t handle;
	/*                           */
	int32_t fd;
	/*                        */
	uint64_t phys;
};


/*
                                                                              
 */
/*                             */
#define MC_IOC_MAGIC	'M'

#define MC_IO_INIT		_IOWR(MC_IOC_MAGIC, 0, struct mc_ioctl_init)
#define MC_IO_INFO		_IOWR(MC_IOC_MAGIC, 1, struct mc_ioctl_info)
#define MC_IO_VERSION		_IOR(MC_IOC_MAGIC, 2, uint32_t)
/*
                                                        
                                    
                                 
 */
#define MC_IO_YIELD		_IO(MC_IOC_MAGIC, 3)
/*
                                                      
                                   
                                
 */
#define MC_IO_NSIQ		_IO(MC_IOC_MAGIC, 4)
/*
                                                                 
                                                      
                                                                      
                                                                       
                                  
                                                                       
                    
 */
#define MC_IO_FREE		_IO(MC_IOC_MAGIC, 5)
/*
                                                                    
        
                              
  
                                                                    
                                      
 */
#define MC_IO_REG_WSM		_IOWR(MC_IOC_MAGIC, 6, struct mc_ioctl_reg_wsm)
#define MC_COMPAT_REG_WSM	_IOWR(MC_IOC_MAGIC, 6, \
			struct mc_compat_ioctl_reg_wsm)

#define MC_IO_UNREG_WSM		_IO(MC_IOC_MAGIC, 7)
#define MC_IO_LOCK_WSM		_IO(MC_IOC_MAGIC, 8)
#define MC_IO_UNLOCK_WSM	_IO(MC_IOC_MAGIC, 9)

/*
                                                                        
                                                         
                                        
                                                        
                        
 */
#define MC_IO_MAP_WSM		_IOWR(MC_IOC_MAGIC, 11, struct mc_ioctl_map)
#define MC_IO_MAP_MCI		_IOWR(MC_IOC_MAGIC, 12, struct mc_ioctl_map)

/*
                                                                      
                                                                      
                        
                                                                            
                                                                            
                                                                             
                                  
 */
#define MC_IO_CLEAN_WSM		_IO(MC_IOC_MAGIC, 14)

/*
                                                                 
                                
 */
#define MC_IO_RESOLVE_WSM	_IOWR(MC_IOC_MAGIC, 15, \
					struct mc_ioctl_resolv_wsm)

/*
                                                                  
                                */
#define MC_IO_RESOLVE_CONT_WSM	_IOWR(MC_IOC_MAGIC, 16, \
					struct mc_ioctl_resolv_cont_wsm)

/*
                                    
                                */
#define MC_IO_LOG_SETUP		_IO(MC_IOC_MAGIC, 17)

#endif /*              */
