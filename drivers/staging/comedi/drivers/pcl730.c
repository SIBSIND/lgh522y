/*
                          
                                          
                      
 */
/*
              
                                              
                                                   
                
                                                              
                              

                             
                                                                          
*/

#include "../comedidev.h"

#include <linux/ioport.h>

#define PCL730_SIZE		4
#define ACL7130_SIZE	8
#define PCL730_IDIO_LO	0	/*                                         */
#define PCL730_IDIO_HI	1	/*                                           */
#define PCL730_DIO_LO	2	/*                                  */
#define PCL730_DIO_HI	3	/*                                    */

struct pcl730_board {

	const char *name;	/*             */
	unsigned int io_range;	/*                   */
};

static int pcl730_do_insn(struct comedi_device *dev, struct comedi_subdevice *s,
			  struct comedi_insn *insn, unsigned int *data)
{
	if (data[0]) {
		s->state &= ~data[0];
		s->state |= (data[0] & data[1]);
	}
	if (data[0] & 0x00ff)
		outb(s->state & 0xff,
		     dev->iobase + ((unsigned long)s->private));
	if (data[0] & 0xff00)
		outb((s->state >> 8),
		     dev->iobase + ((unsigned long)s->private) + 1);

	data[1] = s->state;

	return insn->n;
}

static int pcl730_di_insn(struct comedi_device *dev, struct comedi_subdevice *s,
			  struct comedi_insn *insn, unsigned int *data)
{
	data[1] = inb(dev->iobase + ((unsigned long)s->private)) |
	    (inb(dev->iobase + ((unsigned long)s->private) + 1) << 8);

	return insn->n;
}

static int pcl730_attach(struct comedi_device *dev, struct comedi_devconfig *it)
{
	const struct pcl730_board *board = comedi_board(dev);
	struct comedi_subdevice *s;
	int ret;

	ret = comedi_request_region(dev, it->options[0], board->io_range);
	if (ret)
		return ret;

	ret = comedi_alloc_subdevices(dev, 4);
	if (ret)
		return ret;

	s = &dev->subdevices[0];
	/*             */
	s->type = COMEDI_SUBD_DO;
	s->subdev_flags = SDF_WRITABLE;
	s->maxdata = 1;
	s->n_chan = 16;
	s->insn_bits = pcl730_do_insn;
	s->range_table = &range_digital;
	s->private = (void *)PCL730_IDIO_LO;

	s = &dev->subdevices[1];
	/*             */
	s->type = COMEDI_SUBD_DI;
	s->subdev_flags = SDF_READABLE;
	s->maxdata = 1;
	s->n_chan = 16;
	s->insn_bits = pcl730_di_insn;
	s->range_table = &range_digital;
	s->private = (void *)PCL730_IDIO_LO;

	s = &dev->subdevices[2];
	/*        */
	s->type = COMEDI_SUBD_DO;
	s->subdev_flags = SDF_WRITABLE;
	s->maxdata = 1;
	s->n_chan = 16;
	s->insn_bits = pcl730_do_insn;
	s->range_table = &range_digital;
	s->private = (void *)PCL730_DIO_LO;

	s = &dev->subdevices[3];
	/*        */
	s->type = COMEDI_SUBD_DI;
	s->subdev_flags = SDF_READABLE;
	s->maxdata = 1;
	s->n_chan = 16;
	s->insn_bits = pcl730_di_insn;
	s->range_table = &range_digital;
	s->private = (void *)PCL730_DIO_LO;

	printk(KERN_INFO "\n");

	return 0;
}

static const struct pcl730_board boardtypes[] = {
	{ "pcl730", PCL730_SIZE, },
	{ "iso730", PCL730_SIZE, },
	{ "acl7130", ACL7130_SIZE, },
};

static struct comedi_driver pcl730_driver = {
	.driver_name	= "pcl730",
	.module		= THIS_MODULE,
	.attach		= pcl730_attach,
	.detach		= comedi_legacy_detach,
	.board_name	= &boardtypes[0].name,
	.num_names	= ARRAY_SIZE(boardtypes),
	.offset		= sizeof(struct pcl730_board),
};
module_comedi_driver(pcl730_driver);

MODULE_AUTHOR("Comedi http://www.comedi.org");
MODULE_DESCRIPTION("Comedi low-level driver");
MODULE_LICENSE("GPL");
