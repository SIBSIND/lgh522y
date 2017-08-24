/*
 *
 * (C) COPYRIGHT ARM Limited. All rights reserved.
 *
 * This program is free software and is provided to you under the terms of the
 * GNU General Public License version 2 as published by the Free Software
 * Foundation, and any use by you of this program is subject to the terms
 * of such GNU licence.
 *
 * A copy of the licence is included with the program, and can also be obtained
 * from Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 *
 */



/* 
                      
                                                        
 */
#include <linux/amba/bus.h>
#include <linux/amba/clcd.h>
#include <linux/version.h>
#include <linux/shmem_fs.h>
#include <linux/dma-buf.h>
#include <linux/module.h>

#include <drm/drmP.h>
#include <drm/drm_crtc_helper.h>

#include "pl111_drm.h"

#ifdef CONFIG_DMA_SHARED_BUFFER_USES_KDS
static void obtain_kds_if_currently_displayed(struct drm_device *dev,
						struct pl111_gem_bo *bo,
						struct dma_buf *dma_buf)
{
	unsigned long shared[1] = { 0 };
	struct kds_resource *resource_list[1];
	struct kds_resource_set *kds_res_set;
	struct drm_crtc *crtc;
	bool cb_has_called = false;
	unsigned long flags;
	int err;
	DECLARE_WAIT_QUEUE_HEAD_ONSTACK(wake);

	DRM_DEBUG_KMS("Obtaining initial KDS res for bo:%p dma_buf:%p\n",
			bo, dma_buf);

	resource_list[0] = get_dma_buf_kds_resource(dma_buf);
	get_dma_buf(dma_buf);

	/*
                                                                     
                  
  */
	err = kds_async_waitall(&kds_res_set,
				&priv.kds_obtain_current_cb, &wake,
				&cb_has_called, 1, shared, resource_list);
	BUG_ON(err);
	wait_event(wake, cb_has_called == true);

	list_for_each_entry(crtc, &dev->mode_config.crtc_list, head) {
		struct pl111_drm_crtc *pl111_crtc = to_pl111_crtc(crtc);
		spin_lock_irqsave(&pl111_crtc->current_displaying_lock, flags);
		if (pl111_crtc->displaying_fb) {
			struct pl111_drm_framebuffer *pl111_fb;
			struct drm_framebuffer *fb = pl111_crtc->displaying_fb;

			pl111_fb = PL111_FB_FROM_FRAMEBUFFER(fb);

			if (pl111_fb->bo == bo) {
				DRM_DEBUG_KMS("Initial KDS resource for bo %p", bo);
				DRM_DEBUG_KMS(" is being displayed, keeping\n");
				/*                                                 */
				BUG_ON(pl111_crtc->old_kds_res_set);

				if (kds_res_set == NULL) {
					err = kds_async_waitall(&kds_res_set,
							&priv.kds_obtain_current_cb,
							&wake, &cb_has_called,
							1, shared, resource_list);
					BUG_ON(err);
					wait_event(wake, cb_has_called == true);
				}

				/*                                                 */
				pl111_crtc->old_kds_res_set = kds_res_set;

				/*
                                                          
                          
    */
				kds_res_set = NULL;
			}
		}
		spin_unlock_irqrestore(&pl111_crtc->current_displaying_lock, flags);
	}

	/*                                                              */
	if (kds_res_set != NULL) {
		DRM_DEBUG_KMS("Initial KDS resource for bo %p", bo);
		DRM_DEBUG_KMS(" not being displayed, discarding\n");
		/*                                           */
		kds_resource_set_release(&kds_res_set);
	}

	dma_buf_put(dma_buf);
}
#endif

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 11, 0))

static int pl111_dma_buf_mmap(struct dma_buf *buffer,
			struct vm_area_struct *vma)
{
	struct drm_gem_object *obj = buffer->priv;
	struct pl111_gem_bo *bo = PL111_BO_FROM_GEM(obj);
	struct drm_device *dev = obj->dev;
	int ret;

	DRM_DEBUG_KMS("DRM %s on dma_buf=%p\n", __func__, buffer);

	mutex_lock(&dev->struct_mutex);
	ret = drm_gem_mmap_obj(obj, obj->size, vma);
	mutex_unlock(&dev->struct_mutex);
	if (ret)
		return ret;

	return pl111_bo_mmap(obj, bo, vma, buffer->size);
}

#else

static int pl111_dma_buf_mmap(struct dma_buf *buffer,
			struct vm_area_struct *vma)
{
	struct drm_gem_object *obj = buffer->priv;
	struct pl111_gem_bo *bo = PL111_BO_FROM_GEM(obj);
	struct drm_device *dev = obj->dev;

	DRM_DEBUG_KMS("DRM %s on dma_buf=%p\n", __func__, buffer);

	mutex_lock(&dev->struct_mutex);

	/*                       */
	if (obj->size < vma->vm_end - vma->vm_start)
		return -EINVAL;

	BUG_ON(!dev->driver->gem_vm_ops);

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 7, 0))
	vma->vm_flags |= VM_IO | VM_PFNMAP | VM_DONTEXPAND | VM_DONTDUMP;
#else
	vma->vm_flags |= VM_RESERVED | VM_IO | VM_PFNMAP | VM_DONTEXPAND;
#endif

	vma->vm_ops = dev->driver->gem_vm_ops;
	vma->vm_private_data = obj;

	/*                                                             
                                                                   
                                                             
                                                                    
                                                            
 */
	drm_gem_object_reference(obj);

#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 10, 0))
	pl111_drm_vm_open_locked(dev, vma);
#else
	drm_vm_open_locked(dev, vma);
#endif

	mutex_unlock(&dev->struct_mutex);

	return pl111_bo_mmap(obj, bo, vma, buffer->size);
}

#endif /*                */

static void pl111_dma_buf_release(struct dma_buf *buf)
{
	/*
                                                                    
                                                                 
                                                  
  */
	struct drm_gem_object *obj = (struct drm_gem_object *)buf->priv;
	struct pl111_gem_bo *bo;
#ifdef CONFIG_DMA_SHARED_BUFFER_USES_KDS
	struct drm_crtc *crtc;
	unsigned long flags;
#endif
	bo = PL111_BO_FROM_GEM(obj);

	DRM_DEBUG_KMS("Releasing dma_buf %p, drm_gem_obj=%p\n", buf, obj);

#ifdef CONFIG_DMA_SHARED_BUFFER_USES_KDS
	list_for_each_entry(crtc, &bo->gem_object.dev->mode_config.crtc_list,
				head) {
		struct pl111_drm_crtc *pl111_crtc = to_pl111_crtc(crtc);
		spin_lock_irqsave(&pl111_crtc->current_displaying_lock, flags);
		if (pl111_crtc->displaying_fb) {
			struct pl111_drm_framebuffer *pl111_fb;
			struct drm_framebuffer *fb = pl111_crtc->displaying_fb;

			pl111_fb = PL111_FB_FROM_FRAMEBUFFER(fb);
			if (pl111_fb->bo == bo) {
				kds_resource_set_release(&pl111_crtc->old_kds_res_set);
				pl111_crtc->old_kds_res_set = NULL;
			}
		}
		spin_unlock_irqrestore(&pl111_crtc->current_displaying_lock, flags);
	}
#endif
	mutex_lock(&priv.export_dma_buf_lock);

	obj->export_dma_buf = NULL;
	drm_gem_object_unreference_unlocked(obj);

	mutex_unlock(&priv.export_dma_buf_lock);
}

static int pl111_dma_buf_attach(struct dma_buf *buf, struct device *dev,
				struct dma_buf_attachment *attach)
{
	DRM_DEBUG_KMS("Attaching dma_buf %p to device %p attach=%p\n", buf,
			dev, attach);

	attach->priv = dev;

	return 0;
}

static void pl111_dma_buf_detach(struct dma_buf *buf,
				struct dma_buf_attachment *attach)
{
	DRM_DEBUG_KMS("Detaching dma_buf %p attach=%p\n", attach->dmabuf,
			attach);
}

/*                                  */
static struct sg_table *pl111_dma_buf_map_dma_buf(struct dma_buf_attachment
						*attach,
						enum dma_data_direction
						direction)
{
	struct drm_gem_object *obj = attach->dmabuf->priv;
	struct pl111_gem_bo *bo = PL111_BO_FROM_GEM(obj);
	struct drm_device *dev = obj->dev;
	int size, n_pages, nents;
	struct scatterlist *s, *sg;
	struct sg_table *sgt;
	int ret, i;

	DRM_DEBUG_KMS("Mapping dma_buf %p from attach=%p (bo=%p)\n", attach->dmabuf,
		      attach, bo);

	/*
                                                                           
                                 
  */
	if (obj->import_attach) {
		BUG_ON(!bo->sgt);
		return bo->sgt;
	}

	size = obj->size;
	n_pages = PAGE_ALIGN(size) >> PAGE_SHIFT;

	if (bo->type & PL111_BOT_DMA) {
		sgt = kzalloc(sizeof(*sgt), GFP_KERNEL);
		if (!sgt) {
			DRM_ERROR("Failed to allocate sg_table\n");
			return ERR_PTR(-ENOMEM);
		}

		ret = sg_alloc_table(sgt, 1, GFP_KERNEL);
		if (ret < 0) {
			DRM_ERROR("Failed to allocate page table\n");
			return ERR_PTR(-ENOMEM);
		}
		sg_dma_len(sgt->sgl) = size;
		/*                                                          
                                                           */
		sg_set_buf(sgt->sgl, bo->backing_data.dma.fb_cpu_addr, size);
		sg_dma_address(sgt->sgl) = bo->backing_data.dma.fb_dev_addr;
	} else { /*               */
		struct page **pages;
		int pg = 0;

		mutex_lock(&dev->struct_mutex);
		pages = get_pages(obj);
		if (IS_ERR(pages)) {
			dev_err(obj->dev->dev, "could not get pages: %ld\n",
				PTR_ERR(pages));
			return ERR_CAST(pages);
		}
		sgt = drm_prime_pages_to_sg(pages, n_pages);
		if (sgt == NULL)
			return ERR_PTR(-ENOMEM);

		pl111_gem_sync_to_dma(bo);

		/*
                                                           
                                                               
                                                          
                       
                                                               
                                                               
                                                             
                                                              
                
   */
		sg = sgt->sgl;
		nents = sgt->nents;

		for_each_sg(sg, s, nents, i) {
			int j, n_pages_in_chunk = sg_dma_len(s) >> PAGE_SHIFT;

			sg_dma_address(s) = bo->backing_data.shm.dma_addrs[pg];

			for (j = pg+1; j < pg+n_pages_in_chunk; j++) {
				BUG_ON(bo->backing_data.shm.dma_addrs[j] !=
						bo->backing_data.shm.dma_addrs[j-1]+PAGE_SIZE);
			}

			pg += n_pages_in_chunk;
		}

		mutex_unlock(&dev->struct_mutex);
	}
	bo->sgt = sgt;
	return sgt;
}

static void pl111_dma_buf_unmap_dma_buf(struct dma_buf_attachment *attach,
					struct sg_table *sgt,
					enum dma_data_direction direction)
{
	struct drm_gem_object *obj = attach->dmabuf->priv;
	struct pl111_gem_bo *bo = PL111_BO_FROM_GEM(obj);

	DRM_DEBUG_KMS("Unmapping dma_buf %p from attach=%p (bo=%p)\n", attach->dmabuf,
			attach, bo);

	sg_free_table(sgt);
	kfree(sgt);
	bo->sgt = NULL;
}

/*
                                                                             
                                                         
 */
static void *pl111_dma_buf_kmap(struct dma_buf *dma_buf, unsigned long pageno)
{
	struct pl111_gem_bo *bo = dma_buf->priv;
	void *vaddr = NULL;

	/*                                                     */
	if (((pageno + 1) << PAGE_SHIFT) > bo->gem_object.size)
		return NULL;

	if (bo->type & PL111_BOT_DMA) {
		vaddr = (bo->backing_data.dma.fb_cpu_addr +
						(pageno << PAGE_SHIFT));
	} else {
		vaddr = page_address(bo->backing_data.shm.pages[pageno]);
	}

	return vaddr;
}

/*
                                                          
                               
 */
static dma_addr_t pl111_find_matching_sg(struct sg_table *sgt, size_t start,
					size_t len)
{
	struct scatterlist *sg;
	unsigned int count;
	size_t size = 0;
	dma_addr_t dma_handle = 0;

	/*                                                        
                   */
	for_each_sg(sgt->sgl, sg, sgt->nents, count) {
		if ((size == start) && (len == sg_dma_len(sg))) {
			dma_handle = sg_dma_address(sg);
			break;
		}
		size += sg_dma_len(sg);
	}
	return dma_handle;
}

static int pl111_dma_buf_begin_cpu(struct dma_buf *dma_buf,
					size_t start, size_t len,
					enum dma_data_direction dir)
{
	struct pl111_gem_bo *bo = dma_buf->priv;
	struct sg_table *sgt = bo->sgt;
	dma_addr_t dma_handle;

	if ((start + len) > bo->gem_object.size)
		return -EINVAL;

	if (!(bo->type & PL111_BOT_SHM)) {
		struct device *dev = bo->gem_object.dev->dev;

		dma_handle = pl111_find_matching_sg(sgt, start, len);
		if (!dma_handle)
			return -EINVAL;

		dma_sync_single_range_for_cpu(dev, dma_handle, 0, len, dir);
	}
	/*                                                        */
	return 0;
}

static void pl111_dma_buf_end_cpu(struct dma_buf *dma_buf,
					size_t start, size_t len,
					enum dma_data_direction dir)
{
	struct pl111_gem_bo *bo = dma_buf->priv;
	struct sg_table *sgt = bo->sgt;
	dma_addr_t dma_handle;

	if ((start + len) > bo->gem_object.size)
		return;

	if (!(bo->type & PL111_BOT_DMA)) {
		struct device *dev = bo->gem_object.dev->dev;

		dma_handle = pl111_find_matching_sg(sgt, start, len);
		if (!dma_handle)
			return;

		dma_sync_single_range_for_device(dev, dma_handle, 0, len, dir);
	}
	/*                                                        */
}

static struct dma_buf_ops pl111_dma_buf_ops = {
	.release = &pl111_dma_buf_release,
	.attach = &pl111_dma_buf_attach,
	.detach = &pl111_dma_buf_detach,
	.map_dma_buf = &pl111_dma_buf_map_dma_buf,
	.unmap_dma_buf = &pl111_dma_buf_unmap_dma_buf,
	.kmap_atomic = &pl111_dma_buf_kmap,
	.kmap = &pl111_dma_buf_kmap,
	.begin_cpu_access = &pl111_dma_buf_begin_cpu,
	.end_cpu_access = &pl111_dma_buf_end_cpu,
	.mmap = &pl111_dma_buf_mmap,
};

struct drm_gem_object *pl111_gem_prime_import(struct drm_device *dev,
				       struct dma_buf *dma_buf)
{
	struct dma_buf_attachment *attachment;
	struct drm_gem_object *obj;
	struct pl111_gem_bo *bo;
	struct scatterlist *sgl;
	struct sg_table *sgt;
	dma_addr_t cont_phys;
	int ret = 0;
	int i;

	DRM_DEBUG_KMS("DRM %s on dev=%p dma_buf=%p\n", __func__, dev, dma_buf);

	/*                             */
	if (dma_buf->ops == &pl111_dma_buf_ops) {
		obj = dma_buf->priv;
		/*                        */
		if (obj->dev == dev) {
			/*
                                                         
                                                         
   */
			drm_gem_object_reference(obj);

#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 10, 0))
			/*                                                                   
                                                                 */
			dma_buf_put(dma_buf);
#endif

			return obj;
		}
	}

	attachment = dma_buf_attach(dma_buf, dev->dev);
	if (IS_ERR(attachment))
		return ERR_CAST(attachment);

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 10, 0))
	/*                                                                          */
	get_dma_buf(dma_buf);
#endif

	sgt = dma_buf_map_attachment(attachment, DMA_BIDIRECTIONAL);
	if (IS_ERR_OR_NULL(sgt)) {
		ret = PTR_ERR(sgt);
		goto err_buf_detach;
	}

	bo = kzalloc(sizeof(*bo), GFP_KERNEL);
	if (!bo) {
		DRM_ERROR("%s: failed to allocate buffer object.\n", __func__);
		ret = -ENOMEM;
		goto err_unmap_attach;
	}

	/*                                                  */
	sgl = sgt->sgl;
	cont_phys = sg_phys(sgl);
	bo->type |= PL111_BOT_DMA;
	for_each_sg(sgt->sgl, sgl, sgt->nents, i) {
		dma_addr_t real_phys = sg_phys(sgl);
		if (real_phys != cont_phys) {
			bo->type &= ~PL111_BOT_DMA;
			break;
		}
		cont_phys += (PAGE_SIZE - sgl->offset);
	}

	ret = drm_gem_private_object_init(dev, &bo->gem_object,
					  dma_buf->size);
	if (ret != 0) {
		DRM_ERROR("DRM could not import DMA GEM obj\n");
		goto err_free_buffer;
	}

	if (bo->type & PL111_BOT_DMA) {
		bo->backing_data.dma.fb_cpu_addr = sg_virt(sgt->sgl);
		bo->backing_data.dma.fb_dev_addr = sg_phys(sgt->sgl);
		DRM_DEBUG_KMS("DRM %s pl111_gem_bo=%p, contiguous import\n", __func__, bo);
	} else { /*               */
		DRM_DEBUG_KMS("DRM %s pl111_gem_bo=%p, non contiguous import\n", __func__, bo);
	}

	bo->gem_object.import_attach = attachment;
	bo->sgt = sgt;

	return &bo->gem_object;

err_free_buffer:
	kfree(bo);
	bo = NULL;
err_unmap_attach:
	dma_buf_unmap_attachment(attachment, sgt, DMA_BIDIRECTIONAL);
err_buf_detach:
	dma_buf_detach(dma_buf, attachment);
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 10, 0))
	/*                                                      */
	dma_buf_put(dma_buf);
#endif
	return ERR_PTR(ret);
}

struct dma_buf *pl111_gem_prime_export(struct drm_device *dev,
				      struct drm_gem_object *obj, int flags)
{
	struct dma_buf *new_buf;
	struct pl111_gem_bo *bo;
	size_t size;

	DRM_DEBUG("DRM %s on dev=%p drm_gem_obj=%p\n", __func__, dev, obj);
	size = obj->size;

	new_buf = dma_buf_export(obj /*     */ , &pl111_dma_buf_ops, size,
					flags | O_RDWR);
	bo = PL111_BO_FROM_GEM(new_buf->priv);

	/*
                                                                        
            
  */

#ifdef CONFIG_DMA_SHARED_BUFFER_USES_KDS
	/*
                                                              
                     
  */
	obtain_kds_if_currently_displayed(dev, bo, new_buf);
#endif

	DRM_DEBUG("Created dma_buf %p\n", new_buf);

	return new_buf;
}

int pl111_prime_handle_to_fd(struct drm_device *dev, struct drm_file *file_priv,
				uint32_t handle, uint32_t flags, int *prime_fd)
{
	int result;
	/*
                                                    
                                                               
  */
	DRM_DEBUG_KMS("DRM %s on file_priv=%p, handle=0x%.8x\n", __func__,
			file_priv, handle);

	mutex_lock(&priv.export_dma_buf_lock);
	result = drm_gem_prime_handle_to_fd(dev, file_priv, handle, flags,
						prime_fd);
	mutex_unlock(&priv.export_dma_buf_lock);

	return result;
}
