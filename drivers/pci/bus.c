/*
                    
  
                        
                                               
                                          
                                  
                                             
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/pci.h>
#include <linux/errno.h>
#include <linux/ioport.h>
#include <linux/proc_fs.h>
#include <linux/init.h>
#include <linux/slab.h>

#include "pci.h"

void pci_add_resource_offset(struct list_head *resources, struct resource *res,
			     resource_size_t offset)
{
	struct pci_host_bridge_window *window;

	window = kzalloc(sizeof(struct pci_host_bridge_window), GFP_KERNEL);
	if (!window) {
		printk(KERN_ERR "PCI: can't add host bridge window %pR\n", res);
		return;
	}

	window->res = res;
	window->offset = offset;
	list_add_tail(&window->list, resources);
}
EXPORT_SYMBOL(pci_add_resource_offset);

void pci_add_resource(struct list_head *resources, struct resource *res)
{
	pci_add_resource_offset(resources, res, 0);
}
EXPORT_SYMBOL(pci_add_resource);

void pci_free_resource_list(struct list_head *resources)
{
	struct pci_host_bridge_window *window, *tmp;

	list_for_each_entry_safe(window, tmp, resources, list) {
		list_del(&window->list);
		kfree(window);
	}
}
EXPORT_SYMBOL(pci_free_resource_list);

void pci_bus_add_resource(struct pci_bus *bus, struct resource *res,
			  unsigned int flags)
{
	struct pci_bus_resource *bus_res;

	bus_res = kzalloc(sizeof(struct pci_bus_resource), GFP_KERNEL);
	if (!bus_res) {
		dev_err(&bus->dev, "can't add %pR resource\n", res);
		return;
	}

	bus_res->res = res;
	bus_res->flags = flags;
	list_add_tail(&bus_res->list, &bus->resources);
}

struct resource *pci_bus_resource_n(const struct pci_bus *bus, int n)
{
	struct pci_bus_resource *bus_res;

	if (n < PCI_BRIDGE_RESOURCE_NUM)
		return bus->resource[n];

	n -= PCI_BRIDGE_RESOURCE_NUM;
	list_for_each_entry(bus_res, &bus->resources, list) {
		if (n-- == 0)
			return bus_res->res;
	}
	return NULL;
}
EXPORT_SYMBOL_GPL(pci_bus_resource_n);

void pci_bus_remove_resources(struct pci_bus *bus)
{
	int i;
	struct pci_bus_resource *bus_res, *tmp;

	for (i = 0; i < PCI_BRIDGE_RESOURCE_NUM; i++)
		bus->resource[i] = NULL;

	list_for_each_entry_safe(bus_res, tmp, &bus->resources, list) {
		list_del(&bus_res->list);
		kfree(bus_res);
	}
}

/* 
                                                                 
                
                             
                                      
                                            
                                                
                                      
                                       
                                                              
  
                                                                    
                                                                    
                                  
 */
int
pci_bus_alloc_resource(struct pci_bus *bus, struct resource *res,
		resource_size_t size, resource_size_t align,
		resource_size_t min, unsigned int type_mask,
		resource_size_t (*alignf)(void *,
					  const struct resource *,
					  resource_size_t,
					  resource_size_t),
		void *alignf_data)
{
	int i, ret = -ENOMEM;
	struct resource *r;
	resource_size_t max = -1;

	type_mask |= IORESOURCE_IO | IORESOURCE_MEM;

	/*                                                              */
	if (!(res->flags & IORESOURCE_MEM_64))
		max = PCIBIOS_MAX_MEM_32;

	pci_bus_for_each_resource(bus, r, i) {
		if (!r)
			continue;

		/*                      */
		if ((res->flags ^ r->flags) & type_mask)
			continue;

		/*                                              
                              */
		if ((r->flags & IORESOURCE_PREFETCH) &&
		    !(res->flags & IORESOURCE_PREFETCH))
			continue;

		/*                  */
		ret = allocate_resource(r, res, size,
					r->start ? : min,
					max, align,
					alignf, alignf_data);
		if (ret == 0)
			break;
	}
	return ret;
}

void __weak pcibios_resource_survey_bus(struct pci_bus *bus) { }

/* 
                                                        
                      
  
                                                       
 */
int pci_bus_add_device(struct pci_dev *dev)
{
	int retval;

	/*
                                                       
                                          
  */
	pci_fixup_device(pci_fixup_final, dev);
	pci_create_sysfs_dev_files(dev);

	dev->match_driver = true;
	retval = device_attach(&dev->dev);
	WARN_ON(retval < 0);

	dev->is_added = 1;

	return 0;
}

/* 
                                                     
                                     
  
                                                           
 */
void pci_bus_add_devices(const struct pci_bus *bus)
{
	struct pci_dev *dev;
	struct pci_bus *child;
	int retval;

	list_for_each_entry(dev, &bus->devices, bus_list) {
		/*                            */
		if (dev->is_added)
			continue;
		retval = pci_bus_add_device(dev);
		if (retval)
			dev_err(&dev->dev, "Error adding device (%d)\n",
				retval);
	}

	list_for_each_entry(dev, &bus->devices, bus_list) {
		BUG_ON(!dev->is_added);
		child = dev->subordinate;
		if (child)
			pci_bus_add_devices(child);
	}
}

void pci_enable_bridges(struct pci_bus *bus)
{
	struct pci_dev *dev;
	int retval;

	list_for_each_entry(dev, &bus->devices, bus_list) {
		if (dev->subordinate) {
			if (!pci_is_enabled(dev)) {
				retval = pci_enable_device(dev);
				if (retval)
					dev_err(&dev->dev, "Error enabling bridge (%d), continuing\n", retval);
				pci_set_master(dev);
			}
			pci_enable_bridges(dev->subordinate);
		}
	}
}

/*                                                             
                                                
                                                         
                                                         
  
                                                     
                                                        
                         
  
                                                                
                               
  
 */
void pci_walk_bus(struct pci_bus *top, int (*cb)(struct pci_dev *, void *),
		  void *userdata)
{
	struct pci_dev *dev;
	struct pci_bus *bus;
	struct list_head *next;
	int retval;

	bus = top;
	down_read(&pci_bus_sem);
	next = top->devices.next;
	for (;;) {
		if (next == &bus->devices) {
			/*                                  */
			if (bus == top)
				break;
			next = bus->self->bus_list.next;
			bus = bus->self->bus;
			continue;
		}
		dev = list_entry(next, struct pci_dev, bus_list);
		if (dev->subordinate) {
			/*                                               */
			next = dev->subordinate->devices.next;
			bus = dev->subordinate;
		} else
			next = dev->bus_list.next;

		retval = cb(dev, userdata);
		if (retval)
			break;
	}
	up_read(&pci_bus_sem);
}
EXPORT_SYMBOL_GPL(pci_walk_bus);

EXPORT_SYMBOL(pci_bus_alloc_resource);
EXPORT_SYMBOL_GPL(pci_bus_add_device);
EXPORT_SYMBOL(pci_bus_add_devices);
EXPORT_SYMBOL(pci_enable_bridges);
