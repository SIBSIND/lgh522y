/*
 * NUMA memory policies for Linux.
 * Copyright 2003,2004 Andi Kleen SuSE Labs
 */
#ifndef _LINUX_MEMPOLICY_H
#define _LINUX_MEMPOLICY_H 1


#include <linux/mmzone.h>
#include <linux/slab.h>
#include <linux/rbtree.h>
#include <linux/spinlock.h>
#include <linux/nodemask.h>
#include <linux/pagemap.h>
#include <uapi/linux/mempolicy.h>

struct mm_struct;

#ifdef CONFIG_NUMA

/*
                            
  
                                                                     
                                                                     
                                                                  
                          
  
                                
                                                                           
                                                                              
            
  
                  
                                                                           
                                                     
  
                              
                                                                          
                                                                            
                                               
 */
struct mempolicy {
	atomic_t refcnt;
	unsigned short mode; 	/*                  */
	unsigned short flags;	/*                                    */
	union {
		short 		 preferred_node; /*           */
		nodemask_t	 nodes;		/*                 */
		/*                       */
	} v;
	union {
		nodemask_t cpuset_mems_allowed;	/*                         */
		nodemask_t user_nodemask;	/*                         */
	} w;
};

/*
                                                                     
                                                                         
 */

extern void __mpol_put(struct mempolicy *pol);
static inline void mpol_put(struct mempolicy *pol)
{
	if (pol)
		__mpol_put(pol);
}

/*
                                                    
                                             
 */
static inline int mpol_needs_cond_ref(struct mempolicy *pol)
{
	return (pol && (pol->flags & MPOL_F_SHARED));
}

static inline void mpol_cond_put(struct mempolicy *pol)
{
	if (mpol_needs_cond_ref(pol))
		__mpol_put(pol);
}

extern struct mempolicy *__mpol_dup(struct mempolicy *pol);
static inline struct mempolicy *mpol_dup(struct mempolicy *pol)
{
	if (pol)
		pol = __mpol_dup(pol);
	return pol;
}

#define vma_policy(vma) ((vma)->vm_policy)
#define vma_set_policy(vma, pol) ((vma)->vm_policy = (pol))

static inline void mpol_get(struct mempolicy *pol)
{
	if (pol)
		atomic_inc(&pol->refcnt);
}

extern bool __mpol_equal(struct mempolicy *a, struct mempolicy *b);
static inline bool mpol_equal(struct mempolicy *a, struct mempolicy *b)
{
	if (a == b)
		return true;
	return __mpol_equal(a, b);
}

/*
                                                      
                                                                    
                                                                              
                                                                     
                 
 */

struct sp_node {
	struct rb_node nd;
	unsigned long start, end;
	struct mempolicy *policy;
};

struct shared_policy {
	struct rb_root root;
	spinlock_t lock;
};

void mpol_shared_policy_init(struct shared_policy *sp, struct mempolicy *mpol);
int mpol_set_shared_policy(struct shared_policy *info,
				struct vm_area_struct *vma,
				struct mempolicy *new);
void mpol_free_shared_policy(struct shared_policy *p);
struct mempolicy *mpol_shared_policy_lookup(struct shared_policy *sp,
					    unsigned long idx);

struct mempolicy *get_vma_policy(struct task_struct *tsk,
		struct vm_area_struct *vma, unsigned long addr);

extern void numa_default_policy(void);
extern void numa_policy_init(void);
extern void mpol_rebind_task(struct task_struct *tsk, const nodemask_t *new,
				enum mpol_rebind_step step);
extern void mpol_rebind_mm(struct mm_struct *mm, nodemask_t *new);
extern void mpol_fix_fork_child_flag(struct task_struct *p);

extern struct zonelist *huge_zonelist(struct vm_area_struct *vma,
				unsigned long addr, gfp_t gfp_flags,
				struct mempolicy **mpol, nodemask_t **nodemask);
extern bool init_nodemask_of_mempolicy(nodemask_t *mask);
extern bool mempolicy_nodemask_intersects(struct task_struct *tsk,
				const nodemask_t *mask);
extern unsigned slab_node(void);

extern enum zone_type policy_zone;

static inline void check_highest_zone(enum zone_type k)
{
	if (k > policy_zone && k != ZONE_MOVABLE)
		policy_zone = k;
}

int do_migrate_pages(struct mm_struct *mm, const nodemask_t *from,
		     const nodemask_t *to, int flags);


#ifdef CONFIG_TMPFS
extern int mpol_parse_str(char *str, struct mempolicy **mpol);
#endif

extern int mpol_to_str(char *buffer, int maxlen, struct mempolicy *pol);

/*                              */
static inline int vma_migratable(struct vm_area_struct *vma)
{
	if (vma->vm_flags & (VM_IO | VM_HUGETLB | VM_PFNMAP))
		return 0;
	/*
                                                               
                                                            
             
  */
	if (vma->vm_file &&
		gfp_zone(mapping_gfp_mask(vma->vm_file->f_mapping))
								< policy_zone)
			return 0;
	return 1;
}

extern int mpol_misplaced(struct page *, struct vm_area_struct *, unsigned long);

#else

struct mempolicy {};

static inline bool mpol_equal(struct mempolicy *a, struct mempolicy *b)
{
	return true;
}

static inline void mpol_put(struct mempolicy *p)
{
}

static inline void mpol_cond_put(struct mempolicy *pol)
{
}

static inline void mpol_get(struct mempolicy *pol)
{
}

static inline struct mempolicy *mpol_dup(struct mempolicy *old)
{
	return NULL;
}

struct shared_policy {};

static inline int mpol_set_shared_policy(struct shared_policy *info,
					struct vm_area_struct *vma,
					struct mempolicy *new)
{
	return -EINVAL;
}

static inline void mpol_shared_policy_init(struct shared_policy *sp,
						struct mempolicy *mpol)
{
}

static inline void mpol_free_shared_policy(struct shared_policy *p)
{
}

static inline struct mempolicy *
mpol_shared_policy_lookup(struct shared_policy *sp, unsigned long idx)
{
	return NULL;
}

#define vma_policy(vma) NULL
#define vma_set_policy(vma, pol) do {} while(0)

static inline void numa_policy_init(void)
{
}

static inline void numa_default_policy(void)
{
}

static inline void mpol_rebind_task(struct task_struct *tsk,
				const nodemask_t *new,
				enum mpol_rebind_step step)
{
}

static inline void mpol_rebind_mm(struct mm_struct *mm, nodemask_t *new)
{
}

static inline void mpol_fix_fork_child_flag(struct task_struct *p)
{
}

static inline struct zonelist *huge_zonelist(struct vm_area_struct *vma,
				unsigned long addr, gfp_t gfp_flags,
				struct mempolicy **mpol, nodemask_t **nodemask)
{
	*mpol = NULL;
	*nodemask = NULL;
	return node_zonelist(0, gfp_flags);
}

static inline bool init_nodemask_of_mempolicy(nodemask_t *m)
{
	return false;
}

static inline bool mempolicy_nodemask_intersects(struct task_struct *tsk,
			const nodemask_t *mask)
{
	return false;
}

static inline int do_migrate_pages(struct mm_struct *mm, const nodemask_t *from,
				   const nodemask_t *to, int flags)
{
	return 0;
}

static inline void check_highest_zone(int k)
{
}

#ifdef CONFIG_TMPFS
static inline int mpol_parse_str(char *str, struct mempolicy **mpol)
{
	return 1;	/*       */
}
#endif

static inline int mpol_to_str(char *buffer, int maxlen, struct mempolicy *pol)
{
	return 0;
}

static inline int mpol_misplaced(struct page *page, struct vm_area_struct *vma,
				 unsigned long address)
{
	return -1; /*                    */
}

#endif /*             */
#endif
