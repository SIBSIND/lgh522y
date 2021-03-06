/*
 * mtip32xx.h - Header file for the P320 SSD Block Driver
 *   Copyright (C) 2011 Micron Technology, Inc.
 *
 * Portions of this code were derived from works subjected to the
 * following copyright:
 *    Copyright (C) 2009 Integrated Device Technology, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef __MTIP32XX_H__
#define __MTIP32XX_H__

#include <linux/spinlock.h>
#include <linux/rwsem.h>
#include <linux/ata.h>
#include <linux/interrupt.h>
#include <linux/genhd.h>

/*                                                          */
#define PCI_SUBSYSTEM_DEVICEID	0x2E

/*                                                                      */
#define PCIE_CONFIG_EXT_DEVICE_CONTROL_OFFSET	0x48

/*                                                  */
#define MTIP_SEC_ERASE_MODE     0x2

/*                                          */
#define MTIP_MAX_RETRIES	2

/*                              */
#define MTIP_NCQ_COMMAND_TIMEOUT_MS       5000
#define MTIP_IOCTL_COMMAND_TIMEOUT_MS     5000
#define MTIP_INTERNAL_COMMAND_TIMEOUT_MS  5000

/*                                */
#define MTIP_TIMEOUT_CHECK_PERIOD	500

/*             */
#define MTIP_FTL_REBUILD_OFFSET		142
#define MTIP_FTL_REBUILD_MAGIC		0xED51
#define MTIP_FTL_REBUILD_TIMEOUT_MS	2400000

/*                       */
#define MTIP_MAX_UNALIGNED_SLOTS	8

/*                                                       */
#define MTIP_TAG_BIT(tag)	(tag & 0x1F)

/*
                                                             
                                                                      
                    
 */
#define MTIP_TAG_INDEX(tag)	(tag >> 5)

/*
                                           
                             
 */
#define MTIP_MAX_SG		128

/*
                                                                     
                                                                            
 */
#define MTIP_MAX_SLOT_GROUPS	8

/*                       */
#define MTIP_TAG_INTERNAL	0

/*                                        */
#define PCI_VENDOR_ID_MICRON    0x1344
#define P320H_DEVICE_ID		0x5150
#define P320M_DEVICE_ID		0x5151
#define P320S_DEVICE_ID		0x5152
#define P325M_DEVICE_ID		0x5153
#define P420H_DEVICE_ID		0x5160
#define P420M_DEVICE_ID		0x5161
#define P425M_DEVICE_ID		0x5163

/*                                 */
#define MTIP_DRV_NAME		"mtip32xx"
#define MTIP_DRV_VERSION	"1.2.6os3"

/*                                                    */
#define MTIP_MAX_MINORS		16

/*                                            */
#define MTIP_MAX_COMMAND_SLOTS	(MTIP_MAX_SLOT_GROUPS * 32)

/*
                                  
                                   
                                              
                                                               
                                                                  
                                                     
 */
#define U32_PER_LONG	(sizeof(long) / sizeof(u32))
#define SLOTBITS_IN_LONGS ((MTIP_MAX_SLOT_GROUPS + \
					(U32_PER_LONG-1))/U32_PER_LONG)

/*                                              */
#define MTIP_ABAR		5

#ifdef DEBUG
 #define dbg_printk(format, arg...)	\
	printk(pr_fmt(format), ##arg);
#else
 #define dbg_printk(format, arg...)
#endif

#define MTIP_DFS_MAX_BUF_SIZE 1024

#define __force_bit2int (unsigned int __force)

enum {
	/*                                                       */
	MTIP_PF_IC_ACTIVE_BIT       = 0, /*           */
	MTIP_PF_EH_ACTIVE_BIT       = 1, /*                */
	MTIP_PF_SE_ACTIVE_BIT       = 2, /*              */
	MTIP_PF_DM_ACTIVE_BIT       = 3, /*                   */
	MTIP_PF_PAUSE_IO      =	((1 << MTIP_PF_IC_ACTIVE_BIT) |
				(1 << MTIP_PF_EH_ACTIVE_BIT) |
				(1 << MTIP_PF_SE_ACTIVE_BIT) |
				(1 << MTIP_PF_DM_ACTIVE_BIT)),

	MTIP_PF_SVC_THD_ACTIVE_BIT  = 4,
	MTIP_PF_ISSUE_CMDS_BIT      = 5,
	MTIP_PF_REBUILD_BIT         = 6,
	MTIP_PF_SVC_THD_STOP_BIT    = 8,

	/*                                                           */
	MTIP_DDF_SEC_LOCK_BIT	    = 0,
	MTIP_DDF_REMOVE_PENDING_BIT = 1,
	MTIP_DDF_OVER_TEMP_BIT      = 2,
	MTIP_DDF_WRITE_PROTECT_BIT  = 3,
	MTIP_DDF_STOP_IO      = ((1 << MTIP_DDF_REMOVE_PENDING_BIT) |
				(1 << MTIP_DDF_SEC_LOCK_BIT) |
				(1 << MTIP_DDF_OVER_TEMP_BIT) |
				(1 << MTIP_DDF_WRITE_PROTECT_BIT)),

	MTIP_DDF_CLEANUP_BIT        = 5,
	MTIP_DDF_RESUME_BIT         = 6,
	MTIP_DDF_INIT_DONE_BIT      = 7,
	MTIP_DDF_REBUILD_FAILED_BIT = 8,
};

struct smart_attr {
	u8 attr_id;
	u16 flags;
	u8 cur;
	u8 worst;
	u32 data;
	u8 res[3];
} __packed;

struct mtip_work {
	struct work_struct work;
	void *port;
	int cpu_binding;
	u32 completed;
} ____cacheline_aligned_in_smp;

#define DEFINE_HANDLER(group)                                  \
	void mtip_workq_sdbf##group(struct work_struct *work)       \
	{                                                      \
		struct mtip_work *w = (struct mtip_work *) work;         \
		mtip_workq_sdbfx(w->port, group, w->completed);     \
	}

#define MTIP_TRIM_TIMEOUT_MS		240000
#define MTIP_MAX_TRIM_ENTRIES		8
#define MTIP_MAX_TRIM_ENTRY_LEN		0xfff8

struct mtip_trim_entry {
	u32 lba;   /*                        */
	u16 rsvd;  /*        */
	u16 range; /*                          */
} __packed;

struct mtip_trim {
	/*                          */
	struct mtip_trim_entry entry[MTIP_MAX_TRIM_ENTRIES];
} __packed;

/*                                                             */
struct host_to_dev_fis {
	/*
             
                                       
                                       
                                           
                                        
                                   
                                            
                                        
                                              
  */
	unsigned char type;
	unsigned char opts;
	unsigned char command;
	unsigned char features;

	union {
		unsigned char lba_low;
		unsigned char sector;
	};
	union {
		unsigned char lba_mid;
		unsigned char cyl_low;
	};
	union {
		unsigned char lba_hi;
		unsigned char cyl_hi;
	};
	union {
		unsigned char device;
		unsigned char head;
	};

	union {
		unsigned char lba_low_ex;
		unsigned char sector_ex;
	};
	union {
		unsigned char lba_mid_ex;
		unsigned char cyl_low_ex;
	};
	union {
		unsigned char lba_hi_ex;
		unsigned char cyl_hi_ex;
	};
	unsigned char features_ex;

	unsigned char sect_count;
	unsigned char sect_cnt_ex;
	unsigned char res2;
	unsigned char control;

	unsigned int res3;
};

/*                           */
struct mtip_cmd_hdr {
	/*
                    
                                       
                                              
                                                                    
                                                                     
                                          
                                                                     
  */
	unsigned int opts;
	/*                                     */
	union {
		unsigned int byte_count;
		unsigned int status;
	};
	/*
                                                                   
                                                                 
  */
	unsigned int ctba;
	/*
                                                                
                                                              
  */
	unsigned int ctbau;
	/*                      */
	unsigned int res[4];
};

/*                                         */
struct mtip_cmd_sg {
	/*
                                                         
                                                              
             
  */
	unsigned int dba;
	/*
                                                          
                                       
  */
	unsigned int dba_upper;
	/*         */
	unsigned int reserved;
	/*
                                                                
                         
                                                                      
                                                        
  */
	unsigned int info;
};
struct mtip_port;

/*                                       */
struct mtip_cmd {

	struct mtip_cmd_hdr *command_header; /*                             */

	dma_addr_t command_header_dma; /*                                */

	void *command; /*                            */

	dma_addr_t command_dma; /*                                */

	void *comp_data; /*                                                */
	/*
                                                            
              
  */
	void (*comp_func)(struct mtip_port *port,
				int tag,
				void *data,
				int status);
	/*                                                                */
	void (*async_callback)(void *data, int status);

	void *async_data; /*                                       */

	int scatter_ents; /*                                     */

	int unaligned; /*                                     */

	struct scatterlist sg[MTIP_MAX_SG]; /*                      */

	int retries; /*                                              */

	int direction; /*                         */

	unsigned long comp_time; /*                                     */

	atomic_t active; /*                                             */
};

/*                                    */
struct mtip_port {
	/*                                                */
	struct driver_data *dd;
	/*
                                                   
                            
  */
	unsigned long identify_valid;
	/*                                                    */
	void __iomem *mmio;
	/*                                                            */
	void __iomem *s_active[MTIP_MAX_SLOT_GROUPS];
	/*                                                             */
	void __iomem *completed[MTIP_MAX_SLOT_GROUPS];
	/*                                                                 */
	void __iomem *cmd_issue[MTIP_MAX_SLOT_GROUPS];
	/*
                                                                 
                  
  */
	void *command_list;
	/*
                                                                 
               
  */
	dma_addr_t command_list_dma;
	/*
                                                         
                  
  */
	void *rxfis;
	/*
                                                         
               
  */
	dma_addr_t rxfis_dma;
	/*
                                                                
                  
  */
	void *command_table;
	/*
                                                                
               
  */
	dma_addr_t command_tbl_dma;
	/*
                                                                
                  
  */
	u16 *identify;
	/*
                                                                
               
  */
	dma_addr_t identify_dma;
	/*
                                                            
                                                 
  */
	u16 *sector_buffer;
	/*
                                                            
                                                        
  */
	dma_addr_t sector_buffer_dma;
	/*
                                                            
                                                              
                                                            
                         
  */
	u16 *log_buf;
	dma_addr_t log_buf_dma;

	u8 *smart_buf;
	dma_addr_t smart_buf_dma;

	unsigned long allocated[SLOTBITS_IN_LONGS];
	/*
                                                                  
                               
  */
	unsigned long cmds_to_issue[SLOTBITS_IN_LONGS];
	/*
                                                              
                                                                      
             
  */
	struct mtip_cmd commands[MTIP_MAX_COMMAND_SLOTS];
	/*                                                  */
	wait_queue_head_t svc_wait;
	/*
                                                                   
                                       
  */
	unsigned long flags;
	/*
                                                                       
  */
	struct timer_list cmd_timer;
	unsigned long ic_pause_timer;
	/*
                                                   
                            
  */
	struct semaphore cmd_slot;

	/*                                                   */
	struct semaphore cmd_slot_unal;

	/*                                                */
	spinlock_t cmd_issue_lock[MTIP_MAX_SLOT_GROUPS];
};

/*
                                 
  
                                                
 */
struct driver_data {
	void __iomem *mmio; /*                                    */

	int major; /*                      */

	int instance; /*                                                */

	struct gendisk *disk; /*                                   */

	struct pci_dev *pdev; /*                                      */

	struct request_queue *queue; /*                    */

	struct mtip_port *port; /*                                     */

	unsigned product_type; /*                                        */

	unsigned slot_groups; /*                                            */

	unsigned long index; /*                                  */

	unsigned long dd_flag; /*                                         */

	struct task_struct *mtip_svc_handler; /*                        */

	struct dentry *dfs_node;

	bool trim_supp; /*                              */

	int numa_node; /*              */

	char workq_name[32];

	struct workqueue_struct *isr_workq;

	struct mtip_work work[MTIP_MAX_SLOT_GROUPS];

	atomic_t irq_workers_active;

	int isr_binding;

	int unal_qdepth; /*                              */

	struct list_head online_list; /*                         */

	struct list_head remove_list; /*                           */
};

#endif
