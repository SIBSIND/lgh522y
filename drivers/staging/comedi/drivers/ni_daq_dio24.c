/*
    comedi/drivers/ni_daq_dio24.c
    Driver for National Instruments PCMCIA DAQ-Card DIO-24
    Copyright (C) 2002 Daniel Vecino Castel <dvecino@able.es>

    PCMCIA crap at end of file is adapted from dummy_cs.c 1.31 2001/08/24 12:13:13
    from the pcmcia package.
    The initial developer of the pcmcia dummy_cs.c code is David A. Hinds
    <dahinds@users.sourceforge.net>.  Portions created by David A. Hinds
    are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

************************************************************************
*/
/*
                    
                                                        
                                              
                                                                     
         
                                        

                                                                  
                     
*/

#include "../comedidev.h"

#include <pcmcia/cistpl.h>
#include <pcmcia/cisreg.h>
#include <pcmcia/ds.h>

#include "8255.h"

static int dio24_auto_attach(struct comedi_device *dev,
			     unsigned long context)
{
	struct pcmcia_device *link = comedi_to_pcmcia_dev(dev);
	struct comedi_subdevice *s;
	int ret;

	link->config_flags |= CONF_AUTO_SET_IO;
	ret = comedi_pcmcia_enable(dev, NULL);
	if (ret)
		return ret;
	dev->iobase = link->resource[0]->start;

	ret = comedi_alloc_subdevices(dev, 1);
	if (ret)
		return ret;

	/*          */
	s = &dev->subdevices[0];
	ret = subdev_8255_init(dev, s, NULL, dev->iobase);
	if (ret)
		return ret;

	return 0;
}

static void dio24_detach(struct comedi_device *dev)
{
	comedi_spriv_free(dev, 0);
	comedi_pcmcia_disable(dev);
}

static struct comedi_driver driver_dio24 = {
	.driver_name	= "ni_daq_dio24",
	.module		= THIS_MODULE,
	.auto_attach	= dio24_auto_attach,
	.detach		= dio24_detach,
};

static int dio24_cs_attach(struct pcmcia_device *link)
{
	return comedi_pcmcia_auto_config(link, &driver_dio24);
}

static const struct pcmcia_device_id dio24_cs_ids[] = {
	PCMCIA_DEVICE_MANF_CARD(0x010b, 0x475c),	/*               */
	PCMCIA_DEVICE_NULL
};
MODULE_DEVICE_TABLE(pcmcia, dio24_cs_ids);

static struct pcmcia_driver dio24_cs_driver = {
	.name		= "ni_daq_dio24",
	.owner		= THIS_MODULE,
	.id_table	= dio24_cs_ids,
	.probe		= dio24_cs_attach,
	.remove		= comedi_pcmcia_auto_unconfig,
};
module_comedi_pcmcia_driver(driver_dio24, dio24_cs_driver);

MODULE_AUTHOR("Daniel Vecino Castel <dvecino@able.es>");
MODULE_DESCRIPTION(
	"Comedi driver for National Instruments PCMCIA DAQ-Card DIO-24");
MODULE_LICENSE("GPL");
