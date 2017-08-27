/*
 *	Video for Linux Two
 *
 *	A generic video device interface for the LINUX operating system
 *	using a set of device structures/vectors for low level operations.
 *
 *	This file replaces the videodev.c file that comes with the
 *	regular kernel distribution.
 *
 *	This program is free software; you can redistribute it and/or
 *	modify it under the terms of the GNU General Public License
 *	as published by the Free Software Foundation; either version
 *	2 of the License, or (at your option) any later version.
 *
 * Author:	Bill Dirks <bill@thedirks.org>
 *		based on code by Alan Cox, <alan@cymru.net>
 *
 */

/*
 * Video capture interface for Linux
 *
 *	A generic video device interface for the LINUX operating system
 *	using a set of device structures/vectors for low level operations.
 *
 *		This program is free software; you can redistribute it and/or
 *		modify it under the terms of the GNU General Public License
 *		as published by the Free Software Foundation; either version
 *		2 of the License, or (at your option) any later version.
 *
 * Author:	Alan Cox, <alan@lxorguk.ukuu.org.uk>
 *
 * Fixes:
 */

/*
                                                 
                                
                                                
                                                     
                                                       
                                               
                                   
                                                        
 */

#include <linux/module.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/string.h>
#include <linux/errno.h>
#include <linux/i2c.h>
#if defined(CONFIG_SPI)
#include <linux/spi/spi.h>
#endif
#include <asm/uaccess.h>
#include <asm/pgtable.h>
#include <asm/io.h>
#include <asm/div64.h>
#include <media/v4l2-common.h>
#include <media/v4l2-device.h>
#include <media/v4l2-ctrls.h>
#include <media/v4l2-chip-ident.h>

#include <linux/videodev2.h>

MODULE_AUTHOR("Bill Dirks, Justin Schoeman, Gerd Knorr");
MODULE_DESCRIPTION("misc helper functions for v4l2 device drivers");
MODULE_LICENSE("GPL");

/*
  
                                              
  
 */

/*
                                                              
 */

/*                                              */

/*                                                                 
                                                                
                                                       */
int v4l2_ctrl_check(struct v4l2_ext_control *ctrl, struct v4l2_queryctrl *qctrl,
		const char * const *menu_items)
{
	if (qctrl->flags & V4L2_CTRL_FLAG_DISABLED)
		return -EINVAL;
	if (qctrl->flags & V4L2_CTRL_FLAG_GRABBED)
		return -EBUSY;
	if (qctrl->type == V4L2_CTRL_TYPE_STRING)
		return 0;
	if (qctrl->type == V4L2_CTRL_TYPE_BUTTON ||
	    qctrl->type == V4L2_CTRL_TYPE_INTEGER64 ||
	    qctrl->type == V4L2_CTRL_TYPE_CTRL_CLASS)
		return 0;
	if (ctrl->value < qctrl->minimum || ctrl->value > qctrl->maximum)
		return -ERANGE;
	if (qctrl->type == V4L2_CTRL_TYPE_MENU && menu_items != NULL) {
		if (menu_items[ctrl->value] == NULL ||
		    menu_items[ctrl->value][0] == '\0')
			return -EINVAL;
	}
	if (qctrl->type == V4L2_CTRL_TYPE_BITMASK &&
			(ctrl->value & ~qctrl->maximum))
		return -ERANGE;
	return 0;
}
EXPORT_SYMBOL(v4l2_ctrl_check);

/*                                 */
int v4l2_ctrl_query_fill(struct v4l2_queryctrl *qctrl, s32 min, s32 max, s32 step, s32 def)
{
	const char *name;

	v4l2_ctrl_fill(qctrl->id, &name, &qctrl->type,
		       &min, &max, &step, &def, &qctrl->flags);

	if (name == NULL)
		return -EINVAL;

	qctrl->minimum = min;
	qctrl->maximum = max;
	qctrl->step = step;
	qctrl->default_value = def;
	qctrl->reserved[0] = qctrl->reserved[1] = 0;
	strlcpy(qctrl->name, name, sizeof(qctrl->name));
	return 0;
}
EXPORT_SYMBOL(v4l2_ctrl_query_fill);

/*                                                                       
                                                                        
                                                                 
                       */
int v4l2_ctrl_query_menu(struct v4l2_querymenu *qmenu, struct v4l2_queryctrl *qctrl,
	       const char * const *menu_items)
{
	int i;

	qmenu->reserved = 0;
	if (menu_items == NULL)
		menu_items = v4l2_ctrl_get_menu(qmenu->id);
	if (menu_items == NULL ||
	    (qctrl && (qmenu->index < qctrl->minimum || qmenu->index > qctrl->maximum)))
		return -EINVAL;
	for (i = 0; i < qmenu->index && menu_items[i]; i++) ;
	if (menu_items[i] == NULL || menu_items[i][0] == '\0')
		return -EINVAL;
	strlcpy(qmenu->name, menu_items[qmenu->index], sizeof(qmenu->name));
	return 0;
}
EXPORT_SYMBOL(v4l2_ctrl_query_menu);

/*                                                                      
                                                     
                                                                  */
int v4l2_ctrl_query_menu_valid_items(struct v4l2_querymenu *qmenu, const u32 *ids)
{
	const char * const *menu_items = v4l2_ctrl_get_menu(qmenu->id);

	qmenu->reserved = 0;
	if (menu_items == NULL || ids == NULL)
		return -EINVAL;
	while (*ids != V4L2_CTRL_MENU_IDS_END) {
		if (*ids++ == qmenu->index) {
			strlcpy(qmenu->name, menu_items[qmenu->index],
					sizeof(qmenu->name));
			return 0;
		}
	}
	return -EINVAL;
}
EXPORT_SYMBOL(v4l2_ctrl_query_menu_valid_items);

/*                                                                     
                                                                         
                                                                       
                                                                           
                     

                                                                      
                                                      */
u32 v4l2_ctrl_next(const u32 * const * ctrl_classes, u32 id)
{
	u32 ctrl_class = V4L2_CTRL_ID2CLASS(id);
	const u32 *pctrl;

	if (ctrl_classes == NULL)
		return 0;

	/*                                                                      */
	if ((id & V4L2_CTRL_FLAG_NEXT_CTRL) == 0) {
		/*            */
		while (*ctrl_classes && V4L2_CTRL_ID2CLASS(**ctrl_classes) != ctrl_class)
			ctrl_classes++;
		if (*ctrl_classes == NULL)
			return 0;
		pctrl = *ctrl_classes;
		/*                 */
		while (*pctrl && *pctrl != id) pctrl++;
		return *pctrl ? id : 0;
	}
	id &= V4L2_CTRL_ID_MASK;
	id++;	/*                     */
	/*                                                                
           */
	while (*ctrl_classes && V4L2_CTRL_ID2CLASS(**ctrl_classes) < ctrl_class)
		ctrl_classes++;
	/*                 */
	if (*ctrl_classes == NULL)
		return 0;
	pctrl = *ctrl_classes;
	/*                                                */
	while (*pctrl && *pctrl < id) pctrl++;
	if (*pctrl)
		return *pctrl;
	/*                                                         */
	/*                                       */
	ctrl_classes++;
	if (*ctrl_classes == NULL)
		return 0;
	return **ctrl_classes;
}
EXPORT_SYMBOL(v4l2_ctrl_next);

int v4l2_chip_match_host(const struct v4l2_dbg_match *match)
{
	switch (match->type) {
	case V4L2_CHIP_MATCH_BRIDGE:
		return match->addr == 0;
	default:
		return 0;
	}
}
EXPORT_SYMBOL(v4l2_chip_match_host);

#if IS_ENABLED(CONFIG_I2C)
int v4l2_chip_match_i2c_client(struct i2c_client *c, const struct v4l2_dbg_match *match)
{
	int len;

	if (c == NULL || match == NULL)
		return 0;

	switch (match->type) {
	case V4L2_CHIP_MATCH_I2C_DRIVER:
		if (c->driver == NULL || c->driver->driver.name == NULL)
			return 0;
		len = strlen(c->driver->driver.name);
		return len && !strncmp(c->driver->driver.name, match->name, len);
	case V4L2_CHIP_MATCH_I2C_ADDR:
		return c->addr == match->addr;
	case V4L2_CHIP_MATCH_SUBDEV:
		return 1;
	default:
		return 0;
	}
}
EXPORT_SYMBOL(v4l2_chip_match_i2c_client);

int v4l2_chip_ident_i2c_client(struct i2c_client *c, struct v4l2_dbg_chip_ident *chip,
		u32 ident, u32 revision)
{
	if (!v4l2_chip_match_i2c_client(c, &chip->match))
		return 0;
	if (chip->ident == V4L2_IDENT_NONE) {
		chip->ident = ident;
		chip->revision = revision;
	}
	else {
		chip->ident = V4L2_IDENT_AMBIGUOUS;
		chip->revision = 0;
	}
	return 0;
}
EXPORT_SYMBOL(v4l2_chip_ident_i2c_client);

/*                                                                   */

/*                      */


void v4l2_i2c_subdev_init(struct v4l2_subdev *sd, struct i2c_client *client,
		const struct v4l2_subdev_ops *ops)
{
	v4l2_subdev_init(sd, ops);
	sd->flags |= V4L2_SUBDEV_FL_IS_I2C;
	/*                                                        */
	sd->owner = client->driver->driver.owner;
	/*                                                 */
	v4l2_set_subdevdata(sd, client);
	i2c_set_clientdata(client, sd);
	/*                 */
	snprintf(sd->name, sizeof(sd->name), "%s %d-%04x",
		client->driver->driver.name, i2c_adapter_id(client->adapter),
		client->addr);
}
EXPORT_SYMBOL_GPL(v4l2_i2c_subdev_init);



/*                         */
struct v4l2_subdev *v4l2_i2c_new_subdev_board(struct v4l2_device *v4l2_dev,
		struct i2c_adapter *adapter, struct i2c_board_info *info,
		const unsigned short *probe_addrs)
{
	struct v4l2_subdev *sd = NULL;
	struct i2c_client *client;

	BUG_ON(!v4l2_dev);

	request_module(I2C_MODULE_PREFIX "%s", info->type);

	/*                       */
	if (info->addr == 0 && probe_addrs)
		client = i2c_new_probed_device(adapter, info, probe_addrs,
					       NULL);
	else
		client = i2c_new_device(adapter, info);

	/*                                                                
                                                                     
                                                                   
                                                                
                                                                   
                                                                
                             */
	if (client == NULL || client->driver == NULL)
		goto error;

	/*                                                              */
	if (!try_module_get(client->driver->driver.owner))
		goto error;
	sd = i2c_get_clientdata(client);

	/*                                                           
                       */
	if (v4l2_device_register_subdev(v4l2_dev, sd))
		sd = NULL;
	/*                                                                  */
	module_put(client->driver->driver.owner);

error:
	/*                                                                 
                                   */
	if (client && sd == NULL)
		i2c_unregister_device(client);
	return sd;
}
EXPORT_SYMBOL_GPL(v4l2_i2c_new_subdev_board);

struct v4l2_subdev *v4l2_i2c_new_subdev(struct v4l2_device *v4l2_dev,
		struct i2c_adapter *adapter, const char *client_type,
		u8 addr, const unsigned short *probe_addrs)
{
	struct i2c_board_info info;

	/*                                                  
                        */
	memset(&info, 0, sizeof(info));
	strlcpy(info.type, client_type, sizeof(info.type));
	info.addr = addr;

	return v4l2_i2c_new_subdev_board(v4l2_dev, adapter, &info, probe_addrs);
}
EXPORT_SYMBOL_GPL(v4l2_i2c_new_subdev);

/*                                           */
unsigned short v4l2_i2c_subdev_addr(struct v4l2_subdev *sd)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);

	return client ? client->addr : I2C_CLIENT_END;
}
EXPORT_SYMBOL_GPL(v4l2_i2c_subdev_addr);

/*                                                                     
                          */
const unsigned short *v4l2_i2c_tuner_addrs(enum v4l2_i2c_tuner_type type)
{
	static const unsigned short radio_addrs[] = {
#if IS_ENABLED(CONFIG_MEDIA_TUNER_TEA5761)
		0x10,
#endif
		0x60,
		I2C_CLIENT_END
	};
	static const unsigned short demod_addrs[] = {
		0x42, 0x43, 0x4a, 0x4b,
		I2C_CLIENT_END
	};
	static const unsigned short tv_addrs[] = {
		0x42, 0x43, 0x4a, 0x4b,		/*         */
		0x60, 0x61, 0x62, 0x63, 0x64,
		I2C_CLIENT_END
	};

	switch (type) {
	case ADDRS_RADIO:
		return radio_addrs;
	case ADDRS_DEMOD:
		return demod_addrs;
	case ADDRS_TV:
		return tv_addrs;
	case ADDRS_TV_WITH_DEMOD:
		return tv_addrs + 4;
	}
	return NULL;
}
EXPORT_SYMBOL_GPL(v4l2_i2c_tuner_addrs);

#endif /*                     */

#if defined(CONFIG_SPI)

/*                         */

void v4l2_spi_subdev_init(struct v4l2_subdev *sd, struct spi_device *spi,
		const struct v4l2_subdev_ops *ops)
{
	v4l2_subdev_init(sd, ops);
	sd->flags |= V4L2_SUBDEV_FL_IS_SPI;
	/*                                                        */
	sd->owner = spi->dev.driver->owner;
	/*                                                 */
	v4l2_set_subdevdata(sd, spi);
	spi_set_drvdata(spi, sd);
	/*                 */
	strlcpy(sd->name, spi->dev.driver->name, sizeof(sd->name));
}
EXPORT_SYMBOL_GPL(v4l2_spi_subdev_init);

struct v4l2_subdev *v4l2_spi_new_subdev(struct v4l2_device *v4l2_dev,
		struct spi_master *master, struct spi_board_info *info)
{
	struct v4l2_subdev *sd = NULL;
	struct spi_device *spi = NULL;

	BUG_ON(!v4l2_dev);

	if (info->modalias[0])
		request_module(info->modalias);

	spi = spi_new_device(master, info);

	if (spi == NULL || spi->dev.driver == NULL)
		goto error;

	if (!try_module_get(spi->dev.driver->owner))
		goto error;

	sd = spi_get_drvdata(spi);

	/*                                                           
                       */
	if (v4l2_device_register_subdev(v4l2_dev, sd))
		sd = NULL;

	/*                                                                  */
	module_put(spi->dev.driver->owner);

error:
	/*                                                                 
                                   */
	if (spi && sd == NULL)
		spi_unregister_device(spi);

	return sd;
}
EXPORT_SYMBOL_GPL(v4l2_spi_new_subdev);

#endif /*                     */

/*                                                                          
                                                                         
                                                                               
                             */
static unsigned int clamp_align(unsigned int x, unsigned int min,
				unsigned int max, unsigned int align)
{
 	/* Bits that must be zero to be aligned */
	unsigned int mask = ~((1 << align) - 1);

	/* Clamp to aligned min and max */
	x = clamp(x, (min + ~mask) & mask, max & mask);

 	/* Round to nearest aligned value */
	if (align)
		x = (x + (1 << (align - 1))) & mask;

	return x;
}

/*                                                                         
                                                                           
                                                                            
                                                                          
                                                
  
                                                                         
                                                                           
                                                                     
                                                                          
                                                                        
                                                                         
                     
 */
void v4l_bound_align_image(u32 *w, unsigned int wmin, unsigned int wmax,
			   unsigned int walign,
			   u32 *h, unsigned int hmin, unsigned int hmax,
			   unsigned int halign, unsigned int salign)
{
	*w = clamp_align(*w, wmin, wmax, walign);
	*h = clamp_align(*h, hmin, hmax, halign);

	/*                                                           */
	if (!salign)
		return;

	/*                                */
	walign = __ffs(*w);
	halign = __ffs(*h);
	/*                                        */
	if (walign + halign < salign) {
		/*                                               */
		unsigned int wmaxa = __fls(wmax ^ (wmin - 1));
		/*                                                */
		unsigned int hmaxa = __fls(hmax ^ (hmin - 1));

		/*                                               */
		do {
			if (halign >= hmaxa ||
			    (walign <= halign && walign < wmaxa)) {
				*w = clamp_align(*w, wmin, wmax, walign + 1);
				walign = __ffs(*w);
			} else {
				*h = clamp_align(*h, hmin, hmax, halign + 1);
				halign = __ffs(*h);
			}
		} while (halign + walign < salign);
	}
}
EXPORT_SYMBOL_GPL(v4l_bound_align_image);

/* 
                                                    
                                               
                          
                                                    
  
                                                                      
 */
bool v4l_match_dv_timings(const struct v4l2_dv_timings *t1,
			  const struct v4l2_dv_timings *t2,
			  unsigned pclock_delta)
{
	if (t1->type != t2->type || t1->type != V4L2_DV_BT_656_1120)
		return false;
	if (t1->bt.width == t2->bt.width &&
	    t1->bt.height == t2->bt.height &&
	    t1->bt.interlaced == t2->bt.interlaced &&
	    t1->bt.polarities == t2->bt.polarities &&
	    t1->bt.pixelclock >= t2->bt.pixelclock - pclock_delta &&
	    t1->bt.pixelclock <= t2->bt.pixelclock + pclock_delta &&
	    t1->bt.hfrontporch == t2->bt.hfrontporch &&
	    t1->bt.vfrontporch == t2->bt.vfrontporch &&
	    t1->bt.vsync == t2->bt.vsync &&
	    t1->bt.vbackporch == t2->bt.vbackporch &&
	    (!t1->bt.interlaced ||
		(t1->bt.il_vfrontporch == t2->bt.il_vfrontporch &&
		 t1->bt.il_vsync == t2->bt.il_vsync &&
		 t1->bt.il_vbackporch == t2->bt.il_vbackporch)))
		return true;
	return false;
}
EXPORT_SYMBOL_GPL(v4l_match_dv_timings);

/*
              
                                              
                                 
 */

#define CVT_PXL_CLK_GRAN	250000	/*                         */

/*                 */
#define CVT_MIN_V_BPORCH	7	/*       */
#define CVT_MIN_V_PORCH_RND	3	/*       */
#define CVT_MIN_VSYNC_BP	550	/*                                     */

/*                                                                   */
#define CVT_CELL_GRAN		8	/*                            */
#define CVT_M			600	/*                           */
#define CVT_C			40	/*                         */
#define CVT_K			128	/*                                 */
#define CVT_J			20	/*                                 */
#define CVT_C_PRIME (((CVT_C - CVT_J) * CVT_K / 256) + CVT_J)
#define CVT_M_PRIME (CVT_K * CVT_M / 256)

/*                  */
#define CVT_RB_MIN_V_BPORCH    7       /*        */
#define CVT_RB_V_FPORCH        3       /*        */
#define CVT_RB_MIN_V_BLANK   460     /*        */
#define CVT_RB_H_SYNC         32       /*        */
#define CVT_RB_H_BPORCH       80       /*        */
#define CVT_RB_H_BLANK       160       /*        */

/*                                                                       
                                                                               
                                           
                                                     
                                                                       
                                
                                
  
                                                                           
                                                                            
                                 
 */
bool v4l2_detect_cvt(unsigned frame_height, unsigned hfreq, unsigned vsync,
		u32 polarities, struct v4l2_dv_timings *fmt)
{
	int  v_fp, v_bp, h_fp, h_bp, hsync;
	int  frame_width, image_height, image_width;
	bool reduced_blanking;
	unsigned pix_clk;

	if (vsync < 4 || vsync > 7)
		return false;

	if (polarities == V4L2_DV_VSYNC_POS_POL)
		reduced_blanking = false;
	else if (polarities == V4L2_DV_HSYNC_POS_POL)
		reduced_blanking = true;
	else
		return false;

	/*          */
	if (reduced_blanking) {
		v_fp = CVT_RB_V_FPORCH;
		v_bp = (CVT_RB_MIN_V_BLANK * hfreq + 999999) / 1000000;
		v_bp -= vsync + v_fp;

		if (v_bp < CVT_RB_MIN_V_BPORCH)
			v_bp = CVT_RB_MIN_V_BPORCH;
	} else {
		v_fp = CVT_MIN_V_PORCH_RND;
		v_bp = (CVT_MIN_VSYNC_BP * hfreq + 999999) / 1000000 - vsync;

		if (v_bp < CVT_MIN_V_BPORCH)
			v_bp = CVT_MIN_V_BPORCH;
	}
	image_height = (frame_height - v_fp - vsync - v_bp + 1) & ~0x1;

	/*                             */
	switch (vsync) {
	case 4:
		image_width = (image_height * 4) / 3;
		break;
	case 5:
		image_width = (image_height * 16) / 9;
		break;
	case 6:
		image_width = (image_height * 16) / 10;
		break;
	case 7:
		/*              */
		if (image_height == 1024)
			image_width = (image_height * 5) / 4;
		else if (image_height == 768)
			image_width = (image_height * 15) / 9;
		else
			return false;
		break;
	default:
		return false;
	}

	image_width = image_width & ~7;

	/*            */
	if (reduced_blanking) {
		pix_clk = (image_width + CVT_RB_H_BLANK) * hfreq;
		pix_clk = (pix_clk / CVT_PXL_CLK_GRAN) * CVT_PXL_CLK_GRAN;

		h_bp = CVT_RB_H_BPORCH;
		hsync = CVT_RB_H_SYNC;
		h_fp = CVT_RB_H_BLANK - h_bp - hsync;

		frame_width = image_width + CVT_RB_H_BLANK;
	} else {
		int h_blank;
		unsigned ideal_duty_cycle = CVT_C_PRIME - (CVT_M_PRIME * 1000) / hfreq;

		h_blank = (image_width * ideal_duty_cycle + (100 - ideal_duty_cycle) / 2) /
						(100 - ideal_duty_cycle);
		h_blank = h_blank - h_blank % (2 * CVT_CELL_GRAN);

		if (h_blank * 100 / image_width < 20) {
			h_blank = image_width / 5;
			h_blank = (h_blank + 0x7) & ~0x7;
		}

		pix_clk = (image_width + h_blank) * hfreq;
		pix_clk = (pix_clk / CVT_PXL_CLK_GRAN) * CVT_PXL_CLK_GRAN;

		h_bp = h_blank / 2;
		frame_width = image_width + h_blank;

		hsync = (frame_width * 8 + 50) / 100;
		hsync = hsync - hsync % CVT_CELL_GRAN;
		h_fp = h_blank - hsync - h_bp;
	}

	fmt->bt.polarities = polarities;
	fmt->bt.width = image_width;
	fmt->bt.height = image_height;
	fmt->bt.hfrontporch = h_fp;
	fmt->bt.vfrontporch = v_fp;
	fmt->bt.hsync = hsync;
	fmt->bt.vsync = vsync;
	fmt->bt.hbackporch = frame_width - image_width - h_fp - hsync;
	fmt->bt.vbackporch = frame_height - image_height - v_fp - vsync;
	fmt->bt.pixelclock = pix_clk;
	fmt->bt.standards = V4L2_DV_BT_STD_CVT;
	if (reduced_blanking)
		fmt->bt.flags |= V4L2_DV_FL_REDUCED_BLANKING;
	return true;
}
EXPORT_SYMBOL_GPL(v4l2_detect_cvt);

/*
              
                                               
                                
 */

#define GTF_PXL_CLK_GRAN	250000	/*                         */

#define GTF_MIN_VSYNC_BP	550	/*                                     */
#define GTF_V_FP		1	/*                              */
#define GTF_CELL_GRAN		8	/*                            */

/*         */
#define GTF_D_M			600	/*                           */
#define GTF_D_C			40	/*                         */
#define GTF_D_K			128	/*                                 */
#define GTF_D_J			20	/*                                 */
#define GTF_D_C_PRIME ((((GTF_D_C - GTF_D_J) * GTF_D_K) / 256) + GTF_D_J)
#define GTF_D_M_PRIME ((GTF_D_K * GTF_D_M) / 256)

/*           */
#define GTF_S_M			3600	/*                           */
#define GTF_S_C			40	/*                         */
#define GTF_S_K			128	/*                                 */
#define GTF_S_J			35	/*                                 */
#define GTF_S_C_PRIME ((((GTF_S_C - GTF_S_J) * GTF_S_K) / 256) + GTF_S_J)
#define GTF_S_M_PRIME ((GTF_S_K * GTF_S_M) / 256)

/*                                                                       
                                                                               
                                           
                                                     
                                                                       
                                
                                                                         
                                                            
                                                            
                                                          
                                                          
                                
  
                                                                           
                                                                            
                                 
 */
bool v4l2_detect_gtf(unsigned frame_height,
		unsigned hfreq,
		unsigned vsync,
		u32 polarities,
		struct v4l2_fract aspect,
		struct v4l2_dv_timings *fmt)
{
	int pix_clk;
	int  v_fp, v_bp, h_fp, hsync;
	int frame_width, image_height, image_width;
	bool default_gtf;
	int h_blank;

	if (vsync != 3)
		return false;

	if (polarities == V4L2_DV_VSYNC_POS_POL)
		default_gtf = true;
	else if (polarities == V4L2_DV_HSYNC_POS_POL)
		default_gtf = false;
	else
		return false;

	/*          */
	v_fp = GTF_V_FP;
	v_bp = (GTF_MIN_VSYNC_BP * hfreq + 999999) / 1000000 - vsync;
	image_height = (frame_height - v_fp - vsync - v_bp + 1) & ~0x1;

	if (aspect.numerator == 0 || aspect.denominator == 0) {
		aspect.numerator = 16;
		aspect.denominator = 9;
	}
	image_width = ((image_height * aspect.numerator) / aspect.denominator);

	/*            */
	if (default_gtf)
		h_blank = ((image_width * GTF_D_C_PRIME * hfreq) -
					(image_width * GTF_D_M_PRIME * 1000) +
			(hfreq * (100 - GTF_D_C_PRIME) + GTF_D_M_PRIME * 1000) / 2) /
			(hfreq * (100 - GTF_D_C_PRIME) + GTF_D_M_PRIME * 1000);
	else
		h_blank = ((image_width * GTF_S_C_PRIME * hfreq) -
					(image_width * GTF_S_M_PRIME * 1000) +
			(hfreq * (100 - GTF_S_C_PRIME) + GTF_S_M_PRIME * 1000) / 2) /
			(hfreq * (100 - GTF_S_C_PRIME) + GTF_S_M_PRIME * 1000);

	h_blank = h_blank - h_blank % (2 * GTF_CELL_GRAN);
	frame_width = image_width + h_blank;

	pix_clk = (image_width + h_blank) * hfreq;
	pix_clk = pix_clk / GTF_PXL_CLK_GRAN * GTF_PXL_CLK_GRAN;

	hsync = (frame_width * 8 + 50) / 100;
	hsync = hsync - hsync % GTF_CELL_GRAN;

	h_fp = h_blank / 2 - hsync;

	fmt->bt.polarities = polarities;
	fmt->bt.width = image_width;
	fmt->bt.height = image_height;
	fmt->bt.hfrontporch = h_fp;
	fmt->bt.vfrontporch = v_fp;
	fmt->bt.hsync = hsync;
	fmt->bt.vsync = vsync;
	fmt->bt.hbackporch = frame_width - image_width - h_fp - hsync;
	fmt->bt.vbackporch = frame_height - image_height - v_fp - vsync;
	fmt->bt.pixelclock = pix_clk;
	fmt->bt.standards = V4L2_DV_BT_STD_GTF;
	if (!default_gtf)
		fmt->bt.flags |= V4L2_DV_FL_REDUCED_BLANKING;
	return true;
}
EXPORT_SYMBOL_GPL(v4l2_detect_gtf);

/*                                                                    
                               
                                            
                                            
  
                                             
                                                                    
                                                        
 */
struct v4l2_fract v4l2_calc_aspect_ratio(u8 hor_landscape, u8 vert_portrait)
{
	struct v4l2_fract aspect = { 16, 9 };
	u32 tmp;
	u8 ratio;

	/*                                     */
	if (!hor_landscape && !vert_portrait)
		return aspect;
	/*                                                                  */
	if (hor_landscape && vert_portrait) {
		aspect.numerator = hor_landscape;
		aspect.denominator = vert_portrait;
		return aspect;
	}
	/*                                                     
                     */
	ratio = hor_landscape | vert_portrait;
	/*                                                        */
	if (ratio == 79) {
		aspect.numerator = 16;
		aspect.denominator = 9;
	} else if (ratio == 34) {
		aspect.numerator = 4;
		aspect.numerator = 3;
	} else if (ratio == 68) {
		aspect.numerator = 15;
		aspect.numerator = 9;
	} else {
		aspect.numerator = hor_landscape + 99;
		aspect.denominator = 100;
	}
	if (hor_landscape)
		return aspect;
	/*                                                                     */
	tmp = aspect.denominator;
	aspect.denominator = aspect.numerator;
	aspect.numerator = tmp;
	return aspect;
}
EXPORT_SYMBOL_GPL(v4l2_calc_aspect_ratio);

const struct v4l2_frmsize_discrete *v4l2_find_nearest_format(
		const struct v4l2_discrete_probe *probe,
		s32 width, s32 height)
{
	int i;
	u32 error, min_error = UINT_MAX;
	const struct v4l2_frmsize_discrete *size, *best = NULL;

	if (!probe)
		return best;

	for (i = 0, size = probe->sizes; i < probe->num_sizes; i++, size++) {
		error = abs(size->width - width) + abs(size->height - height);
		if (error < min_error) {
			min_error = error;
			best = size;
		}
		if (!error)
			break;
	}

	return best;
}
EXPORT_SYMBOL_GPL(v4l2_find_nearest_format);

void v4l2_get_timestamp(struct timeval *tv)
{
	struct timespec ts;

	ktime_get_ts(&ts);
	tv->tv_sec = ts.tv_sec;
	tv->tv_usec = ts.tv_nsec / NSEC_PER_USEC;
}
EXPORT_SYMBOL_GPL(v4l2_get_timestamp);
