#include <linux/io.h>
#include <linux/memblock.h>

#include <asm/cacheflush.h>
#include <asm/pgtable.h>
#include <asm/realmode.h>

struct real_mode_header *real_mode_header;
u32 *trampoline_cr4_features;

void __init reserve_real_mode(void)
{
	phys_addr_t mem;
	unsigned char *base;
	size_t size = PAGE_ALIGN(real_mode_blob_end - real_mode_blob);

	/*                                                         */
	mem = memblock_find_in_range(0, 1<<20, size, PAGE_SIZE);
	if (!mem)
		panic("Cannot allocate trampoline\n");

	base = __va(mem);
	memblock_reserve(mem, size);
	real_mode_header = (struct real_mode_header *) base;
	printk(KERN_DEBUG "Base memory trampoline at [%p] %llx size %zu\n",
	       base, (unsigned long long)mem, size);
}

void __init setup_real_mode(void)
{
	u16 real_mode_seg;
	u32 *rel;
	u32 count;
	u32 *ptr;
	u16 *seg;
	int i;
	unsigned char *base;
	struct trampoline_header *trampoline_header;
	size_t size = PAGE_ALIGN(real_mode_blob_end - real_mode_blob);
#ifdef CONFIG_X86_64
	u64 *trampoline_pgd;
	u64 efer;
#endif

	base = (unsigned char *)real_mode_header;

	memcpy(base, real_mode_blob, size);

	real_mode_seg = __pa(base) >> 4;
	rel = (u32 *) real_mode_relocs;

	/*                             */
	count = rel[0];
	rel = &rel[1];
	for (i = 0; i < count; i++) {
		seg = (u16 *) (base + rel[i]);
		*seg = real_mode_seg;
	}

	/*                            */
	count = rel[i];
	rel =  &rel[i + 1];
	for (i = 0; i < count; i++) {
		ptr = (u32 *) (base + rel[i]);
		*ptr += __pa(base);
	}

	/*                                      */
	trampoline_header = (struct trampoline_header *)
		__va(real_mode_header->trampoline_header);

#ifdef CONFIG_X86_32
	trampoline_header->start = __pa_symbol(startup_32_smp);
	trampoline_header->gdt_limit = __BOOT_DS + 7;
	trampoline_header->gdt_base = __pa_symbol(boot_gdt);
#else
	/*
                                                               
                              
  */
	rdmsrl(MSR_EFER, efer);
	trampoline_header->efer = efer & ~EFER_LMA;

	trampoline_header->start = (u64) secondary_startup_64;
	trampoline_cr4_features = &trampoline_header->cr4;
	*trampoline_cr4_features = read_cr4();

	trampoline_pgd = (u64 *) __va(real_mode_header->trampoline_pgd);
	trampoline_pgd[0] = init_level4_pgt[pgd_index(__PAGE_OFFSET)].pgd;
	trampoline_pgd[511] = init_level4_pgt[511].pgd;
#endif
}

/*
                                                               
                                                                    
                                                               
                                                               
                                                                 
                                     
 */
static int __init set_real_mode_permissions(void)
{
	unsigned char *base = (unsigned char *) real_mode_header;
	size_t size = PAGE_ALIGN(real_mode_blob_end - real_mode_blob);

	size_t ro_size =
		PAGE_ALIGN(real_mode_header->ro_end) -
		__pa(base);

	size_t text_size =
		PAGE_ALIGN(real_mode_header->ro_end) -
		real_mode_header->text_start;

	unsigned long text_start =
		(unsigned long) __va(real_mode_header->text_start);

	set_memory_nx((unsigned long) base, size >> PAGE_SHIFT);
	set_memory_ro((unsigned long) base, ro_size >> PAGE_SHIFT);
	set_memory_x((unsigned long) text_start, text_size >> PAGE_SHIFT);

	return 0;
}
early_initcall(set_real_mode_permissions);
