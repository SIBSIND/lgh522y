/*
 * VMware VMCI driver (vmciContext.h)
 *
 * Copyright (C) 2012 VMware, Inc. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation version 2 and no later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */

#ifndef _VMCI_CONTEXT_H_
#define _VMCI_CONTEXT_H_

#include <linux/vmw_vmci_defs.h>
#include <linux/atomic.h>
#include <linux/kref.h>
#include <linux/types.h>
#include <linux/wait.h>

#include "vmci_handle_array.h"
#include "vmci_datagram.h"

/*                                                         */
enum {
	VMCI_NOTIFICATION_CPT_STATE = 1,
	VMCI_WELLKNOWN_CPT_STATE    = 2,
	VMCI_DG_OUT_STATE           = 3,
	VMCI_DG_IN_STATE            = 4,
	VMCI_DG_IN_SIZE_STATE       = 5,
	VMCI_DOORBELL_CPT_STATE     = 6,
};

/*                                          */
struct vmci_host {
	wait_queue_head_t wait_queue;
};

struct vmci_handle_list {
	struct list_head node;
	struct vmci_handle handle;
};

struct vmci_ctx {
	struct list_head list_item;       /*                       */
	u32 cid;
	struct kref kref;
	struct list_head datagram_queue;  /*                       */
	u32 pending_datagrams;
	size_t datagram_queue_size;	  /*                                  */

	/*
                                    
                            
  */
	int user_version;
	spinlock_t lock;  /*                                    */

	/*
                                          
                                       
                                       
                                       
                                     
                                 
                                    
                                       
  */
	struct vmci_handle_arr *queue_pair_array;

	/*                               */
	struct vmci_handle_arr *doorbell_array;

	/*                                */
	struct vmci_handle_arr *pending_doorbell_array;

	/*                                             */
	struct list_head notifier_list;
	unsigned int n_notifiers;

	struct vmci_host host_context;
	u32 priv_flags;

	const struct cred *cred;
	bool *notify;		/*                                    */
	struct page *notify_page;	/*                              */
};

/*                                                                           */
struct vmci_ctx_info {
	u32 remote_cid;
	int result;
};

/*                                                                     */
struct vmci_ctx_chkpt_buf_info {
	u64 cpt_buf;
	u32 cpt_type;
	u32 buf_size;
	s32 result;
	u32 _pad;
};

/*
                                                                     
                                 
 */
struct vmci_ctx_notify_recv_info {
	u64 db_handle_buf_uva;
	u64 db_handle_buf_size;
	u64 qp_handle_buf_uva;
	u64 qp_handle_buf_size;
	s32 result;
	u32 _pad;
};

/*
                                                                  
                                                                
              
 */
static inline bool vmci_deny_interaction(u32 part_one, u32 part_two)
{
	return ((part_one & VMCI_PRIVILEGE_FLAG_RESTRICTED) &&
		!(part_two & VMCI_PRIVILEGE_FLAG_TRUSTED)) ||
	       ((part_two & VMCI_PRIVILEGE_FLAG_RESTRICTED) &&
		!(part_one & VMCI_PRIVILEGE_FLAG_TRUSTED));
}

struct vmci_ctx *vmci_ctx_create(u32 cid, u32 flags,
				 uintptr_t event_hnd, int version,
				 const struct cred *cred);
void vmci_ctx_destroy(struct vmci_ctx *context);

bool vmci_ctx_supports_host_qp(struct vmci_ctx *context);
int vmci_ctx_enqueue_datagram(u32 cid, struct vmci_datagram *dg);
int vmci_ctx_dequeue_datagram(struct vmci_ctx *context,
			      size_t *max_size, struct vmci_datagram **dg);
int vmci_ctx_pending_datagrams(u32 cid, u32 *pending);
struct vmci_ctx *vmci_ctx_get(u32 cid);
void vmci_ctx_put(struct vmci_ctx *context);
bool vmci_ctx_exists(u32 cid);

int vmci_ctx_add_notification(u32 context_id, u32 remote_cid);
int vmci_ctx_remove_notification(u32 context_id, u32 remote_cid);
int vmci_ctx_get_chkpt_state(u32 context_id, u32 cpt_type,
			     u32 *num_cids, void **cpt_buf_ptr);
int vmci_ctx_set_chkpt_state(u32 context_id, u32 cpt_type,
			     u32 num_cids, void *cpt_buf);

int vmci_ctx_qp_create(struct vmci_ctx *context, struct vmci_handle handle);
int vmci_ctx_qp_destroy(struct vmci_ctx *context, struct vmci_handle handle);
bool vmci_ctx_qp_exists(struct vmci_ctx *context, struct vmci_handle handle);

void vmci_ctx_check_signal_notify(struct vmci_ctx *context);
void vmci_ctx_unset_notify(struct vmci_ctx *context);

int vmci_ctx_dbell_create(u32 context_id, struct vmci_handle handle);
int vmci_ctx_dbell_destroy(u32 context_id, struct vmci_handle handle);
int vmci_ctx_dbell_destroy_all(u32 context_id);
int vmci_ctx_notify_dbell(u32 cid, struct vmci_handle handle,
			  u32 src_priv_flags);

int vmci_ctx_rcv_notifications_get(u32 context_id, struct vmci_handle_arr
				   **db_handle_array, struct vmci_handle_arr
				   **qp_handle_array);
void vmci_ctx_rcv_notifications_release(u32 context_id, struct vmci_handle_arr
					*db_handle_array, struct vmci_handle_arr
					*qp_handle_array, bool success);

static inline u32 vmci_ctx_get_id(struct vmci_ctx *context)
{
	if (!context)
		return VMCI_INVALID_ID;
	return context->cid;
}

#endif /*                  */
