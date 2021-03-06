/*     
                                                                       
                                                                               
                                                                         
 */
#include <linux/module.h>
#include <linux/stringify.h>
#include <linux/stddef.h>
#include <linux/io.h>
#include <linux/mm.h>
#include <linux/vmalloc.h>
#include <linux/cpu.h>
#include <linux/freezer.h>
#include <linux/highmem.h>
#include <linux/slab.h>
#include <asm/paravirt.h>
#include <asm/pgtable.h>
#include <asm/uaccess.h>
#include <asm/poll.h>
#include <asm/asm-offsets.h>
#include "lg.h"

unsigned long switcher_addr;
struct page **lg_switcher_pages;
static struct vm_struct *switcher_vma;

/*                                                             */
DEFINE_MUTEX(lguest_lock);

/*     
                                                                          
                                                                               
                                                                         
                     
  
                                                                            
                                                          
  
                                                                             
                               
 */
static __init int map_switcher(void)
{
	int i, err;
	struct page **pagep;

	/*
                                       
   
                                                                        
                                                                    
         
  */

	/*                                                  */
	if (end_switcher_text - start_switcher_text > PAGE_SIZE) {
		printk(KERN_ERR "lguest: switcher text too large (%zu)\n",
		       end_switcher_text - start_switcher_text);
		return -EINVAL;
	}

	/*
                                                                      
                                             
  */
	lg_switcher_pages = kmalloc(sizeof(lg_switcher_pages[0])
				    * TOTAL_SWITCHER_PAGES,
				    GFP_KERNEL);
	if (!lg_switcher_pages) {
		err = -ENOMEM;
		goto out;
	}

	/*
                                                                        
                                   
  */
	for (i = 0; i < TOTAL_SWITCHER_PAGES; i++) {
		lg_switcher_pages[i] = alloc_page(GFP_KERNEL|__GFP_ZERO);
		if (!lg_switcher_pages[i]) {
			err = -ENOMEM;
			goto free_some_pages;
		}
	}

	/*
                                                                  
                                                                    
                                                                      
                        
  */
	switcher_addr = FIXADDR_START - (TOTAL_SWITCHER_PAGES+1)*PAGE_SIZE;

	/*
                                                               
                                                             
                                                               
                                                
  */
	switcher_vma = __get_vm_area(TOTAL_SWITCHER_PAGES * PAGE_SIZE,
				     VM_ALLOC, switcher_addr, switcher_addr
				     + (TOTAL_SWITCHER_PAGES+1) * PAGE_SIZE);
	if (!switcher_vma) {
		err = -ENOMEM;
		printk("lguest: could not map switcher pages high\n");
		goto free_pages;
	}

	/*
                                                                     
                                                                       
                                                                    
                                                                    
         
  */
	pagep = lg_switcher_pages;
	err = map_vm_area(switcher_vma, PAGE_KERNEL_EXEC, &pagep);
	if (err) {
		printk("lguest: map_vm_area failed: %i\n", err);
		goto free_vma;
	}

	/*
                                                                   
                                                                   
  */
	memcpy(switcher_vma->addr, start_switcher_text,
	       end_switcher_text - start_switcher_text);

	printk(KERN_INFO "lguest: mapped switcher at %p\n",
	       switcher_vma->addr);
	/*                     */
	return 0;

free_vma:
	vunmap(switcher_vma->addr);
free_pages:
	i = TOTAL_SWITCHER_PAGES;
free_some_pages:
	for (--i; i >= 0; i--)
		__free_pages(lg_switcher_pages[i], 0);
	kfree(lg_switcher_pages);
out:
	return err;
}
/* */

/*                                                                            */
static void unmap_switcher(void)
{
	unsigned int i;

	/*                                                           */
	vunmap(switcher_vma->addr);
	/*                                                                */
	for (i = 0; i < TOTAL_SWITCHER_PAGES; i++)
		__free_pages(lg_switcher_pages[i], 0);
	kfree(lg_switcher_pages);
}

/*     
                             
  
                                                                            
                                    
  
                                                                             
                                                                             
                                               
  
                                                                          
                                                                             
                                                                         
                                
 */
bool lguest_address_ok(const struct lguest *lg,
		       unsigned long addr, unsigned long len)
{
	return (addr+len) / PAGE_SIZE < lg->pfn_limit && (addr+len >= addr);
}

/*
                                                                             
                                                                          
                                                            
 */
void __lgread(struct lg_cpu *cpu, void *b, unsigned long addr, unsigned bytes)
{
	if (!lguest_address_ok(cpu->lg, addr, bytes)
	    || copy_from_user(b, cpu->lg->mem_base + addr, bytes) != 0) {
		/*                                                        */
		memset(b, 0, bytes);
		kill_guest(cpu, "bad read address %#lx len %u", addr, bytes);
	}
}

/*                                              */
void __lgwrite(struct lg_cpu *cpu, unsigned long addr, const void *b,
	       unsigned bytes)
{
	if (!lguest_address_ok(cpu->lg, addr, bytes)
	    || copy_to_user(cpu->lg->mem_base + addr, b, bytes) != 0)
		kill_guest(cpu, "bad write address %#lx len %u", addr, bytes);
}
/* */

/*     
                                                                 
                                                                            
                                                               
 */
int run_guest(struct lg_cpu *cpu, unsigned long __user *user)
{
	/*                                         */
	while (!cpu->lg->dead) {
		unsigned int irq;
		bool more;

		/*                                                   */
		if (cpu->hcall)
			do_hypercalls(cpu);

		/*
                                                          
              
   */
		if (cpu->pending_notify) {
			/*
                                                 
                                                     
    */
			if (!send_notify_to_eventfd(cpu)) {
				/*                                */
				if (put_user(cpu->pending_notify, user))
					return -EFAULT;
				return sizeof(cpu->pending_notify);
			}
		}

		/*
                                                                 
                                                                 
                 
   */
		try_to_freeze();

		/*                   */
		if (signal_pending(current))
			return -ERESTARTSYS;

		/*
                                                                  
                                                               
                   
   */
		irq = interrupt_pending(cpu, &more);
		if (irq < LGUEST_IRQS)
			try_deliver_interrupt(cpu, irq, more);

		/*
                                                                
                                                         
   */
		if (cpu->lg->dead)
			break;

		/*
                                                             
                              
   */
		if (cpu->halted) {
			set_current_state(TASK_INTERRUPTIBLE);
			/*
                                                           
                               
    */
			if (interrupt_pending(cpu, &more) < LGUEST_IRQS)
				set_current_state(TASK_RUNNING);
			else
				schedule();
			continue;
		}

		/*
                                                                 
                               
   */
		local_irq_disable();

		/*                                                 */
		lguest_arch_run_guest(cpu);

		/*                                                          */
		local_irq_enable();

		/*                                                  */
		lguest_arch_handle_trap(cpu);
	}

	/*                                                   */
	if (cpu->lg->dead == ERR_PTR(-ERESTART))
		return -ERESTART;

	/*                                                  */
	return -ENOENT;
}

/*     
                       
  
                                                                            
                                                                               
                                                                          
          
 */
static int __init init(void)
{
	int err;

	/*                                                                   */
	if (get_kernel_rpl() != 0) {
		printk("lguest is afraid of being a guest\n");
		return -EPERM;
	}

	/*                                                           */
	err = map_switcher();
	if (err)
		goto out;

	/*                                               */
	err = init_interrupts();
	if (err)
		goto unmap;

	/*                                     */
	err = lguest_device_init();
	if (err)
		goto free_interrupts;

	/*                                                 */
	lguest_arch_host_init();

	/*           */
	return 0;

free_interrupts:
	free_interrupts();
unmap:
	unmap_switcher();
out:
	return err;
}

/*                                                                      */
static void __exit fini(void)
{
	lguest_device_remove();
	free_interrupts();
	unmap_switcher();

	lguest_arch_host_fini();
}
/* */

/*
                                                                             
                
 */
module_init(init);
module_exit(fini);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rusty Russell <rusty@rustcorp.com.au>");
