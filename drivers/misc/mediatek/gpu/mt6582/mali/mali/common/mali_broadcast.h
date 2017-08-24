/*
 * Copyright (C) 2012-2013 ARM Limited. All rights reserved.
 * 
 * This program is free software and is provided to you under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation, and any use by you of this program is subject to the terms of such GNU licence.
 * 
 * A copy of the licence is included with the program, and can also be obtained from Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

/*
                                                 
  
                                            
                                                                                  
                    
 */

#include "mali_hw_core.h"
#include "mali_group.h"

struct mali_bcast_unit;

struct mali_bcast_unit *mali_bcast_unit_create(const _mali_osk_resource_t *resource);
void mali_bcast_unit_delete(struct mali_bcast_unit *bcast_unit);

/*                                                                   */
void mali_bcast_add_group(struct mali_bcast_unit *bcast_unit, struct mali_group *group);

/*                                                                      */
void mali_bcast_remove_group(struct mali_bcast_unit *bcast_unit, struct mali_group *group);

/*                                                                          */
void mali_bcast_reset(struct mali_bcast_unit *bcast_unit);

/* 
                         
  
                                                                           
                                              
 */
void mali_bcast_disable(struct mali_bcast_unit *bcast_unit);

/* 
                           
  
                                                                                         
 */
MALI_STATIC_INLINE void mali_bcast_enable(struct mali_bcast_unit *bcast_unit)
{
	mali_bcast_reset(bcast_unit);
}
