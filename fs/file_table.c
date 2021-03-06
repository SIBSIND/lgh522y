/*
 *  linux/fs/file_table.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *  Copyright (C) 1997 David S. Miller (davem@caip.rutgers.edu)
 */

#include <linux/string.h>
#include <linux/slab.h>
#include <linux/file.h>
#include <linux/fdtable.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/security.h>
#include <linux/eventpoll.h>
#include <linux/rcupdate.h>
#include <linux/mount.h>
#include <linux/capability.h>
#include <linux/cdev.h>
#include <linux/fsnotify.h>
#include <linux/sysctl.h>
#include <linux/lglock.h>
#include <linux/percpu_counter.h>
#include <linux/percpu.h>
#include <linux/hardirq.h>
#include <linux/task_work.h>
#include <linux/ima.h>

#include <linux/atomic.h>

#include "internal.h"

#define FILE_OVER_MAX
#ifdef FILE_OVER_MAX
extern void fd_show_open_files(pid_t pid, struct files_struct *files, struct fdtable *fdt);
#endif

/*                    */
struct files_stat_struct files_stat = {
	.max_files = NR_FILE
};

DEFINE_STATIC_LGLOCK(files_lglock);

/*                                */
static struct kmem_cache *filp_cachep __read_mostly;

static struct percpu_counter nr_files __cacheline_aligned_in_smp;

static void file_free_rcu(struct rcu_head *head)
{
	struct file *f = container_of(head, struct file, f_u.fu_rcuhead);

	put_cred(f->f_cred);
	kmem_cache_free(filp_cachep, f);
}

static inline void file_free(struct file *f)
{
	percpu_counter_dec(&nr_files);
	file_check_state(f);
	call_rcu(&f->f_u.fu_rcuhead, file_free_rcu);
}

/*
                                                      
 */
static long get_nr_files(void)
{
	return percpu_counter_read_positive(&nr_files);
}

/*
                                                        
 */
unsigned long get_max_files(void)
{
	return files_stat.max_files;
}
EXPORT_SYMBOL_GPL(get_max_files);

/*
                         
 */
#if defined(CONFIG_SYSCTL) && defined(CONFIG_PROC_FS)
int proc_nr_files(ctl_table *table, int write,
                     void __user *buffer, size_t *lenp, loff_t *ppos)
{
	files_stat.nr_files = get_nr_files();
	return proc_doulongvec_minmax(table, write, buffer, lenp, ppos);
}
#else
int proc_nr_files(ctl_table *table, int write,
                     void __user *buffer, size_t *lenp, loff_t *ppos)
{
	return -ENOSYS;
}
#endif

/*                                                          
                                                                   
                                                                     
  
                                                       
                                                          
                                                           
                                                        
                                  
 */
struct file *get_empty_filp(void)
{
	const struct cred *cred = current_cred();
	static long old_max;
	struct file *f;
	int error;

	/*
                                           
  */
	if (get_nr_files() >= files_stat.max_files && !capable(CAP_SYS_ADMIN)) {
		/*
                                                                  
                    
   */
		if (percpu_counter_sum_positive(&nr_files) >= files_stat.max_files)
			goto over;
	}

	f = kmem_cache_zalloc(filp_cachep, GFP_KERNEL);
	if (unlikely(!f))
		return ERR_PTR(-ENOMEM);

	percpu_counter_inc(&nr_files);
	f->f_cred = get_cred(cred);
	error = security_file_alloc(f);
	if (unlikely(error)) {
		file_free(f);
		return ERR_PTR(error);
	}

	INIT_LIST_HEAD(&f->f_u.fu_list);
	atomic_long_set(&f->f_count, 1);
	rwlock_init(&f->f_owner.lock);
	spin_lock_init(&f->f_lock);
	eventpoll_init_file(f);
	/*                 */
	return f;

over:
	/*                                */
	if (get_nr_files() > old_max) {
#ifdef FILE_OVER_MAX
        static int fd_dump_all_files = 0;     
        if(!fd_dump_all_files) { 
	        struct task_struct *p;
	        pr_debug("[FD_LEAK](PID:%d)files %ld over old_max:%ld", current->pid, get_nr_files(), old_max);
	        for_each_process(p) {
	            pid_t pid = p->pid;
	            struct files_struct *files = p->files;
	            struct fdtable *fdt = files_fdtable(files);
	            if(files && fdt) {
	                fd_show_open_files(pid, files, fdt);
	            }
	        }
	        fd_dump_all_files = 0x1;
        }
#endif
		pr_info("VFS: file-max limit %lu reached\n", get_max_files());
		old_max = get_nr_files();
	}
	return ERR_PTR(-ENFILE);
}

/* 
                                                       
                                                   
                                                
                                                         
                                                      
  
                                                    
                                                           
                                                      
                                            
  
                                                        
                                           
 */
struct file *alloc_file(struct path *path, fmode_t mode,
		const struct file_operations *fop)
{
	struct file *file;

	file = get_empty_filp();
	if (IS_ERR(file))
		return file;

	file->f_path = *path;
	file->f_inode = path->dentry->d_inode;
	file->f_mapping = path->dentry->d_inode->i_mapping;
	file->f_mode = mode;
	file->f_op = fop;

	/*
                                                
                                                
                                                
                                               
  */
	if ((mode & FMODE_WRITE) && !special_file(path->dentry->d_inode->i_mode)) {
		file_take_write(file);
		WARN_ON(mnt_clone_write(path->mnt));
	}
	if ((mode & (FMODE_READ | FMODE_WRITE)) == FMODE_READ)
		i_readcount_inc(path->dentry->d_inode);
	return file;
}
EXPORT_SYMBOL(alloc_file);

/* 
                                                              
                                                
  
                                                         
                                                        
                
 */
static void drop_file_write_access(struct file *file)
{
	struct vfsmount *mnt = file->f_path.mnt;
	struct dentry *dentry = file->f_path.dentry;
	struct inode *inode = dentry->d_inode;

	if (special_file(inode->i_mode))
		return;

	put_write_access(inode);
	if (file_check_writeable(file) != 0)
		return;
	__mnt_drop_write(mnt);
	file_release_write(file);
}

/*                                                               
 */
static void __fput(struct file *file)
{
	struct dentry *dentry = file->f_path.dentry;
	struct vfsmount *mnt = file->f_path.mnt;
	struct inode *inode = dentry->d_inode;

	might_sleep();

	fsnotify_close(file);
	/*
                                                               
                              
  */
	eventpoll_release(file);
	locks_remove_flock(file);

	if (unlikely(file->f_flags & FASYNC)) {
		if (file->f_op && file->f_op->fasync)
			file->f_op->fasync(-1, file, 0);
	}
	ima_file_free(file);
	if (file->f_op && file->f_op->release)
		file->f_op->release(inode, file);
	security_file_free(file);
	if (unlikely(S_ISCHR(inode->i_mode) && inode->i_cdev != NULL &&
		     !(file->f_mode & FMODE_PATH))) {
		cdev_put(inode->i_cdev);
	}
	fops_put(file->f_op);
	put_pid(file->f_owner.pid);
	if ((file->f_mode & (FMODE_READ | FMODE_WRITE)) == FMODE_READ)
		i_readcount_dec(inode);
	if (file->f_mode & FMODE_WRITE)
		drop_file_write_access(file);
	file->f_path.dentry = NULL;
	file->f_path.mnt = NULL;
	file->f_inode = NULL;
	file_free(file);
	dput(dentry);
	mntput(mnt);
}

static DEFINE_SPINLOCK(delayed_fput_lock);
static LIST_HEAD(delayed_fput_list);
static void delayed_fput(struct work_struct *unused)
{
	LIST_HEAD(head);
	spin_lock_irq(&delayed_fput_lock);
	list_splice_init(&delayed_fput_list, &head);
	spin_unlock_irq(&delayed_fput_lock);
	while (!list_empty(&head)) {
		struct file *f = list_first_entry(&head, struct file, f_u.fu_list);
		list_del_init(&f->f_u.fu_list);
		__fput(f);
	}
}

static void ____fput(struct callback_head *work)
{
	__fput(container_of(work, struct file, f_u.fu_rcuhead));
}

/*
                                                                     
                                                                    
                                                                 
                                                                      
                                                                   
                                                               
                                                               
                                   
 */
void flush_delayed_fput(void)
{
	delayed_fput(NULL);
}

static DECLARE_WORK(delayed_fput_work, delayed_fput);

void fput(struct file *file)
{
	if (atomic_long_dec_and_test(&file->f_count)) {
		struct task_struct *task = current;
		unsigned long flags;

		file_sb_list_del(file);
		if (likely(!in_interrupt() && !(task->flags & PF_KTHREAD))) {
			init_task_work(&file->f_u.fu_rcuhead, ____fput);
			if (!task_work_add(task, &file->f_u.fu_rcuhead, true))
				return;
		}
		spin_lock_irqsave(&delayed_fput_lock, flags);
		list_add(&file->f_u.fu_list, &delayed_fput_list);
		schedule_work(&delayed_fput_work);
		spin_unlock_irqrestore(&delayed_fput_lock, flags);
	}
}

/*
                                                                        
                                                                    
                                                                       
                                                                     
                                                                  
                                                         
 */
void __fput_sync(struct file *file)
{
	if (atomic_long_dec_and_test(&file->f_count)) {
		struct task_struct *task = current;
		file_sb_list_del(file);
		BUG_ON(!(task->flags & PF_KTHREAD));
		__fput(file);
	}
}

EXPORT_SYMBOL(fput);

void put_filp(struct file *file)
{
	if (atomic_long_dec_and_test(&file->f_count)) {
		security_file_free(file);
		file_sb_list_del(file);
		file_free(file);
	}
}

static inline int file_list_cpu(struct file *file)
{
#ifdef CONFIG_SMP
	return file->f_sb_list_cpu;
#else
	return smp_processor_id();
#endif
}

/*                                              */
static inline void __file_sb_list_add(struct file *file, struct super_block *sb)
{
	struct list_head *list;
#ifdef CONFIG_SMP
	int cpu;
	cpu = smp_processor_id();
	file->f_sb_list_cpu = cpu;
	list = per_cpu_ptr(sb->s_files, cpu);
#else
	list = &sb->s_files;
#endif
	list_add(&file->f_u.fu_list, list);
}

/* 
                                                      
                     
                       
  
                                                                            
             
 */
void file_sb_list_add(struct file *file, struct super_block *sb)
{
	lg_local_lock(&files_lglock);
	__file_sb_list_add(file, sb);
	lg_local_unlock(&files_lglock);
}

/* 
                                                           
                        
                            
  
                                                          
 */
void file_sb_list_del(struct file *file)
{
	if (!list_empty(&file->f_u.fu_list)) {
		lg_local_lock_cpu(&files_lglock, file_list_cpu(file));
		list_del_init(&file->f_u.fu_list);
		lg_local_unlock_cpu(&files_lglock, file_list_cpu(file));
	}
}

#ifdef CONFIG_SMP

/*
                                                                     
                                      
 */
#define do_file_list_for_each_entry(__sb, __file)		\
{								\
	int i;							\
	for_each_possible_cpu(i) {				\
		struct list_head *list;				\
		list = per_cpu_ptr((__sb)->s_files, i);		\
		list_for_each_entry((__file), list, f_u.fu_list)

#define while_file_list_for_each_entry				\
	}							\
}

#else

#define do_file_list_for_each_entry(__sb, __file)		\
{								\
	struct list_head *list;					\
	list = &(sb)->s_files;					\
	list_for_each_entry((__file), list, f_u.fu_list)

#define while_file_list_for_each_entry				\
}

#endif

/* 
                                           
                              
  
                                                               
                                                            
 */
void mark_files_ro(struct super_block *sb)
{
	struct file *f;

	lg_global_lock(&files_lglock);
	do_file_list_for_each_entry(sb, f) {
		if (!S_ISREG(file_inode(f)->i_mode))
		       continue;
		if (!file_count(f))
			continue;
		if (!(f->f_mode & FMODE_WRITE))
			continue;
		spin_lock(&f->f_lock);
		f->f_mode &= ~FMODE_WRITE;
		spin_unlock(&f->f_lock);
		if (file_check_writeable(f) != 0)
			continue;
		__mnt_drop_write(f->f_path.mnt);
		file_release_write(f);
	} while_file_list_for_each_entry;
	lg_global_unlock(&files_lglock);
}

void __init files_init(unsigned long mempages)
{ 
	unsigned long n;

	filp_cachep = kmem_cache_create("filp", sizeof(struct file), 0,
			SLAB_HWCACHE_ALIGN | SLAB_PANIC, NULL);

	/*
                                                                 
                                                                 
  */ 

	n = (mempages * (PAGE_SIZE / 1024)) / 10;
	files_stat.max_files = max_t(unsigned long, n, NR_FILE);
	files_defer_init();
	lg_lock_init(&files_lglock, "files_lglock");
	percpu_counter_init(&nr_files, 0);
} 
