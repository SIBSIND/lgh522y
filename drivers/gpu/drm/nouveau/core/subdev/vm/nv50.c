/*
 * Copyright 2010 Red Hat Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Ben Skeggs
 */

#include <core/device.h>
#include <core/gpuobj.h>

#include <subdev/timer.h>
#include <subdev/fb.h>
#include <subdev/vm.h>

struct nv50_vmmgr_priv {
	struct nouveau_vmmgr base;
	spinlock_t lock;
};

static void
nv50_vm_map_pgt(struct nouveau_gpuobj *pgd, u32 pde,
		struct nouveau_gpuobj *pgt[2])
{
	u64 phys = 0xdeadcafe00000000ULL;
	u32 coverage = 0;

	if (pgt[0]) {
		phys = 0x00000003 | pgt[0]->addr; /*                     */
		coverage = (pgt[0]->size >> 3) << 12;
	} else
	if (pgt[1]) {
		phys = 0x00000001 | pgt[1]->addr; /*         */
		coverage = (pgt[1]->size >> 3) << 16;
	}

	if (phys & 1) {
		if (coverage <= 32 * 1024 * 1024)
			phys |= 0x60;
		else if (coverage <= 64 * 1024 * 1024)
			phys |= 0x40;
		else if (coverage <= 128 * 1024 * 1024)
			phys |= 0x20;
	}

	nv_wo32(pgd, (pde * 8) + 0, lower_32_bits(phys));
	nv_wo32(pgd, (pde * 8) + 4, upper_32_bits(phys));
}

static inline u64
vm_addr(struct nouveau_vma *vma, u64 phys, u32 memtype, u32 target)
{
	phys |= 1; /*         */
	phys |= (u64)memtype << 40;
	phys |= target << 4;
	if (vma->access & NV_MEM_ACCESS_SYS)
		phys |= (1 << 6);
	if (!(vma->access & NV_MEM_ACCESS_WO))
		phys |= (1 << 3);
	return phys;
}

static void
nv50_vm_map(struct nouveau_vma *vma, struct nouveau_gpuobj *pgt,
	    struct nouveau_mem *mem, u32 pte, u32 cnt, u64 phys, u64 delta)
{
	u32 comp = (mem->memtype & 0x180) >> 7;
	u32 block, target;
	int i;

	/*                                                              */
	target = 0;
	if (nouveau_fb(vma->vm->vmm)->ram.stolen) {
		phys += nouveau_fb(vma->vm->vmm)->ram.stolen;
		target = 3;
	}

	phys  = vm_addr(vma, phys, mem->memtype, target);
	pte <<= 3;
	cnt <<= 3;

	while (cnt) {
		u32 offset_h = upper_32_bits(phys);
		u32 offset_l = lower_32_bits(phys);

		for (i = 7; i >= 0; i--) {
			block = 1 << (i + 3);
			if (cnt >= block && !(pte & (block - 1)))
				break;
		}
		offset_l |= (i << 7);

		phys += block << (vma->node->type - 3);
		cnt  -= block;
		if (comp) {
			u32 tag = mem->tag->offset + ((delta >> 16) * comp);
			offset_h |= (tag << 17);
			delta    += block << (vma->node->type - 3);
		}

		while (block) {
			nv_wo32(pgt, pte + 0, offset_l);
			nv_wo32(pgt, pte + 4, offset_h);
			pte += 8;
			block -= 8;
		}
	}
}

static void
nv50_vm_map_sg(struct nouveau_vma *vma, struct nouveau_gpuobj *pgt,
	       struct nouveau_mem *mem, u32 pte, u32 cnt, dma_addr_t *list)
{
	u32 target = (vma->access & NV_MEM_ACCESS_NOSNOOP) ? 3 : 2;
	pte <<= 3;
	while (cnt--) {
		u64 phys = vm_addr(vma, (u64)*list++, mem->memtype, target);
		nv_wo32(pgt, pte + 0, lower_32_bits(phys));
		nv_wo32(pgt, pte + 4, upper_32_bits(phys));
		pte += 8;
	}
}

static void
nv50_vm_unmap(struct nouveau_gpuobj *pgt, u32 pte, u32 cnt)
{
	pte <<= 3;
	while (cnt--) {
		nv_wo32(pgt, pte + 0, 0x00000000);
		nv_wo32(pgt, pte + 4, 0x00000000);
		pte += 8;
	}
}

static void
nv50_vm_flush(struct nouveau_vm *vm)
{
	struct nouveau_engine *engine;
	int i;

	for (i = 0; i < NVDEV_SUBDEV_NR; i++) {
		if (atomic_read(&vm->engref[i])) {
			engine = nouveau_engine(vm->vmm, i);
			if (engine && engine->tlb_flush)
				engine->tlb_flush(engine);
		}
	}
}

void
nv50_vm_flush_engine(struct nouveau_subdev *subdev, int engine)
{
	struct nv50_vmmgr_priv *priv = (void *)nouveau_vmmgr(subdev);
	unsigned long flags;

	spin_lock_irqsave(&priv->lock, flags);
	nv_wr32(subdev, 0x100c80, (engine << 16) | 1);
	if (!nv_wait(subdev, 0x100c80, 0x00000001, 0x00000000))
		nv_error(subdev, "vm flush timeout: engine %d\n", engine);
	spin_unlock_irqrestore(&priv->lock, flags);
}

static int
nv50_vm_create(struct nouveau_vmmgr *vmm, u64 offset, u64 length,
	       u64 mm_offset, struct nouveau_vm **pvm)
{
	u32 block = (1 << (vmm->pgt_bits + 12));
	if (block > length)
		block = length;

	return nouveau_vm_create(vmm, offset, length, mm_offset, block, pvm);
}

static int
nv50_vmmgr_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
		struct nouveau_oclass *oclass, void *data, u32 size,
		struct nouveau_object **pobject)
{
	struct nv50_vmmgr_priv *priv;
	int ret;

	ret = nouveau_vmmgr_create(parent, engine, oclass, "VM", "vm", &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	priv->base.limit = 1ULL << 40;
	priv->base.dma_bits = 40;
	priv->base.pgt_bits  = 29 - 12;
	priv->base.spg_shift = 12;
	priv->base.lpg_shift = 16;
	priv->base.create = nv50_vm_create;
	priv->base.map_pgt = nv50_vm_map_pgt;
	priv->base.map = nv50_vm_map;
	priv->base.map_sg = nv50_vm_map_sg;
	priv->base.unmap = nv50_vm_unmap;
	priv->base.flush = nv50_vm_flush;
	spin_lock_init(&priv->lock);
	return 0;
}

struct nouveau_oclass
nv50_vmmgr_oclass = {
	.handle = NV_SUBDEV(VM, 0x50),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nv50_vmmgr_ctor,
		.dtor = _nouveau_vmmgr_dtor,
		.init = _nouveau_vmmgr_init,
		.fini = _nouveau_vmmgr_fini,
	},
};
