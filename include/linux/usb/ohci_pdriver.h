/*
 * Copyright (C) 2012 Hauke Mehrtens <hauke@hauke-m.de>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef __USB_CORE_OHCI_PDRIVER_H
#define __USB_CORE_OHCI_PDRIVER_H

/* 
                                                                
  
                                   
                                 
                                                 
                               
  
                                                                          
                                                                           
 */
struct usb_ohci_pdata {
	unsigned	big_endian_desc:1;
	unsigned	big_endian_mmio:1;
	unsigned	no_big_frame_no:1;
	unsigned int	num_ports;

	/*                              */
	int (*power_on)(struct platform_device *pdev);
	/*                               */
	void (*power_off)(struct platform_device *pdev);
	/*                                                       
                             */
	void (*power_suspend)(struct platform_device *pdev);
};

#endif /*                           */
