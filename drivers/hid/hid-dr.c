/*
 * Force feedback support for DragonRise Inc. game controllers
 *
 * From what I have gathered, these devices are mass produced in China and are
 * distributed under several vendors. They often share the same design as
 * the original PlayStation DualShock controller.
 *
 * 0079:0006 "DragonRise Inc.   Generic   USB  Joystick  "
 *  - tested with a Tesun USB-703 game controller.
 *
 * Copyright (c) 2009 Richard Walmsley <richwalm@gmail.com>
 */

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include <linux/input.h>
#include <linux/slab.h>
#include <linux/hid.h>
#include <linux/module.h>

#include "hid-ids.h"

#ifdef CONFIG_DRAGONRISE_FF

struct drff_device {
	struct hid_report *report;
};

static int drff_play(struct input_dev *dev, void *data,
				 struct ff_effect *effect)
{
	struct hid_device *hid = input_get_drvdata(dev);
	struct drff_device *drff = data;
	int strong, weak;

	strong = effect->u.rumble.strong_magnitude;
	weak = effect->u.rumble.weak_magnitude;

	dbg_hid("called with 0x%04x 0x%04x", strong, weak);

	if (strong || weak) {
		strong = strong * 0xff / 0xffff;
		weak = weak * 0xff / 0xffff;

		/*                                                         
                                                               
                                                  */
		if (weak == 0x0a)
			weak = 0x0b;

		drff->report->field[0]->value[0] = 0x51;
		drff->report->field[0]->value[1] = 0x00;
		drff->report->field[0]->value[2] = weak;
		drff->report->field[0]->value[4] = strong;
		hid_hw_request(hid, drff->report, HID_REQ_SET_REPORT);

		drff->report->field[0]->value[0] = 0xfa;
		drff->report->field[0]->value[1] = 0xfe;
	} else {
		drff->report->field[0]->value[0] = 0xf3;
		drff->report->field[0]->value[1] = 0x00;
	}

	drff->report->field[0]->value[2] = 0x00;
	drff->report->field[0]->value[4] = 0x00;
	dbg_hid("running with 0x%02x 0x%02x", strong, weak);
	hid_hw_request(hid, drff->report, HID_REQ_SET_REPORT);

	return 0;
}

static int drff_init(struct hid_device *hid)
{
	struct drff_device *drff;
	struct hid_report *report;
	struct hid_input *hidinput = list_first_entry(&hid->inputs,
						struct hid_input, list);
	struct list_head *report_list =
			&hid->report_enum[HID_OUTPUT_REPORT].report_list;
	struct input_dev *dev = hidinput->input;
	int error;

	if (list_empty(report_list)) {
		hid_err(hid, "no output reports found\n");
		return -ENODEV;
	}

	report = list_first_entry(report_list, struct hid_report, list);
	if (report->maxfield < 1) {
		hid_err(hid, "no fields in the report\n");
		return -ENODEV;
	}

	if (report->field[0]->report_count < 7) {
		hid_err(hid, "not enough values in the field\n");
		return -ENODEV;
	}

	drff = kzalloc(sizeof(struct drff_device), GFP_KERNEL);
	if (!drff)
		return -ENOMEM;

	set_bit(FF_RUMBLE, dev->ffbit);

	error = input_ff_create_memless(dev, drff, drff_play);
	if (error) {
		kfree(drff);
		return error;
	}

	drff->report = report;
	drff->report->field[0]->value[0] = 0xf3;
	drff->report->field[0]->value[1] = 0x00;
	drff->report->field[0]->value[2] = 0x00;
	drff->report->field[0]->value[3] = 0x00;
	drff->report->field[0]->value[4] = 0x00;
	drff->report->field[0]->value[5] = 0x00;
	drff->report->field[0]->value[6] = 0x00;
	hid_hw_request(hid, drff->report, HID_REQ_SET_REPORT);

	hid_info(hid, "Force Feedback for DragonRise Inc. "
		 "game controllers by Richard Walmsley <richwalm@gmail.com>\n");

	return 0;
}
#else
static inline int drff_init(struct hid_device *hid)
{
	return 0;
}
#endif

/*
                                                                                
                                                                           
                                                                         
                                                              
  
                                                                      
                                                                             
                             
                           
                        
                         
                            
                              
                             
                               
                                                              
                                                              
                                                              
                                                              
                                                              
                         
                        
                         
                            
                               
                       
                    
                                     
             
                        
                          
                            
                             
                                                    
                            
                            
                         
                                                             
                        
                          
                            
                             
                    
                         
                     
                           
                        
                         
                               
                              
                    
                          
                     
                  
 */

/*                                                            */
#define PID0011_RDESC_ORIG_SIZE	101

/*                                                */
static __u8 pid0011_rdesc_fixed[] = {
	0x05, 0x01,         /*                                  */
	0x09, 0x04,         /*                                  */
	0xA1, 0x01,         /*                                  */
	0xA1, 0x02,         /*                                  */
	0x14,               /*                                  */
	0x75, 0x08,         /*                                  */
	0x95, 0x03,         /*                                  */
	0x81, 0x01,         /*                                  */
	0x26, 0xFF, 0x00,   /*                                  */
	0x95, 0x02,         /*                                  */
	0x09, 0x30,         /*                                  */
	0x09, 0x31,         /*                                  */
	0x81, 0x02,         /*                                  */
	0x75, 0x01,         /*                                  */
	0x95, 0x04,         /*                                  */
	0x81, 0x01,         /*                                  */
	0x25, 0x01,         /*                                  */
	0x95, 0x0A,         /*                                  */
	0x05, 0x09,         /*                                  */
	0x19, 0x01,         /*                                  */
	0x29, 0x0A,         /*                                  */
	0x81, 0x02,         /*                                  */
	0x95, 0x0A,         /*                                  */
	0x81, 0x01,         /*                                  */
	0xC0,               /*                                  */
	0xC0                /*                                  */
};

static __u8 *dr_report_fixup(struct hid_device *hdev, __u8 *rdesc,
				unsigned int *rsize)
{
	switch (hdev->product) {
	case 0x0011:
		if (*rsize == PID0011_RDESC_ORIG_SIZE) {
			rdesc = pid0011_rdesc_fixed;
			*rsize = sizeof(pid0011_rdesc_fixed);
		}
		break;
	}
	return rdesc;
}

static int dr_probe(struct hid_device *hdev, const struct hid_device_id *id)
{
	int ret;

	dev_dbg(&hdev->dev, "DragonRise Inc. HID hardware probe...");

	ret = hid_parse(hdev);
	if (ret) {
		hid_err(hdev, "parse failed\n");
		goto err;
	}

	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT & ~HID_CONNECT_FF);
	if (ret) {
		hid_err(hdev, "hw start failed\n");
		goto err;
	}

	switch (hdev->product) {
	case 0x0006:
		ret = drff_init(hdev);
		if (ret) {
			dev_err(&hdev->dev, "force feedback init failed\n");
			hid_hw_stop(hdev);
			goto err;
		}
		break;
	}

	return 0;
err:
	return ret;
}

static const struct hid_device_id dr_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOR_ID_DRAGONRISE, 0x0006),  },
	{ HID_USB_DEVICE(USB_VENDOR_ID_DRAGONRISE, 0x0011),  },
	{ }
};
MODULE_DEVICE_TABLE(hid, dr_devices);

static struct hid_driver dr_driver = {
	.name = "dragonrise",
	.id_table = dr_devices,
	.report_fixup = dr_report_fixup,
	.probe = dr_probe,
};
module_hid_driver(dr_driver);

MODULE_LICENSE("GPL");
