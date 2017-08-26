/*
 * Synaptics TouchPad PS/2 mouse driver
 *
 *   2003 Dmitry Torokhov <dtor@mail.ru>
 *     Added support for pass-through port. Special thanks to Peter Berg Larsen
 *     for explaining various Synaptics quirks.
 *
 *   2003 Peter Osterlund <petero2@telia.com>
 *     Ported to 2.5 input device infrastructure.
 *
 *   Copyright (C) 2001 Stefan Gmeiner <riddlebox@freesurf.ch>
 *     start merging tpconfig and gpm code to a xfree-input module
 *     adding some changes and extensions (ex. 3rd and 4th button)
 *
 *   Copyright (c) 1997 C. Scott Ananian <cananian@alumni.priceton.edu>
 *   Copyright (c) 1998-2000 Bruce Kalk <kall@compass.com>
 *     code for the special synaptics commands (from the tpconfig-source)
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 *
 * Trademarks are the property of their respective owners.
 */

#include <linux/module.h>
#include <linux/delay.h>
#include <linux/dmi.h>
#include <linux/input/mt.h>
#include <linux/serio.h>
#include <linux/libps2.h>
#include <linux/slab.h>
#include "psmouse.h"
#include "synaptics.h"

/*
                                                                          
                                                                        
                             
                                                                      
               
 */
#define XMIN 0
#define XMAX 6143
#define YMIN 0
#define YMAX 6143
#define XMIN_NOMINAL 1472
#define XMAX_NOMINAL 5472
#define YMIN_NOMINAL 1408
#define YMAX_NOMINAL 4448

/*                                                                   */
#define ABS_POS_BITS 13

/*
                                                                     
                                                                     
                                                                     
                                               
  
                                                                       
                                                                   
                                                                     
                                                                   
                                            
 */
#define X_MAX_POSITIVE 8176
#define Y_MAX_POSITIVE 8176

/*                                                                            
                                                                  
                                                                            */

/*
                                                           
 */
static int synaptics_mode_cmd(struct psmouse *psmouse, unsigned char mode)
{
	unsigned char param[1];

	if (psmouse_sliced_command(psmouse, mode))
		return -1;
	param[0] = SYN_PS_SET_MODE2;
	if (ps2_command(&psmouse->ps2dev, param, PSMOUSE_CMD_SETRATE))
		return -1;
	return 0;
}

int synaptics_detect(struct psmouse *psmouse, bool set_properties)
{
	struct ps2dev *ps2dev = &psmouse->ps2dev;
	unsigned char param[4];

	param[0] = 0;

	ps2_command(ps2dev, param, PSMOUSE_CMD_SETRES);
	ps2_command(ps2dev, param, PSMOUSE_CMD_SETRES);
	ps2_command(ps2dev, param, PSMOUSE_CMD_SETRES);
	ps2_command(ps2dev, param, PSMOUSE_CMD_SETRES);
	ps2_command(ps2dev, param, PSMOUSE_CMD_GETINFO);

	if (param[1] != 0x47)
		return -ENODEV;

	if (set_properties) {
		psmouse->vendor = "Synaptics";
		psmouse->name = "TouchPad";
	}

	return 0;
}

void synaptics_reset(struct psmouse *psmouse)
{
	/*                                                        */
	synaptics_mode_cmd(psmouse, 0);
}

#ifdef CONFIG_MOUSE_PS2_SYNAPTICS

/*                                                                            
                                     
                                                                            */

/*
                                                                           
                                        
                                                      
 */
static int synaptics_invert_y(int y)
{
	return YMAX_NOMINAL + YMIN_NOMINAL - y;
}

/*
                                                               
 */
static int synaptics_send_cmd(struct psmouse *psmouse, unsigned char c, unsigned char *param)
{
	if (psmouse_sliced_command(psmouse, c))
		return -1;
	if (ps2_command(&psmouse->ps2dev, param, PSMOUSE_CMD_GETINFO))
		return -1;
	return 0;
}

/*
                                            
                              
 */
static int synaptics_model_id(struct psmouse *psmouse)
{
	struct synaptics_data *priv = psmouse->private;
	unsigned char mi[3];

	if (synaptics_send_cmd(psmouse, SYN_QUE_MODEL, mi))
		return -1;
	priv->model_id = (mi[0]<<16) | (mi[1]<<8) | mi[2];
	return 0;
}

/*
                                      
                                                        
 */
static int synaptics_board_id(struct psmouse *psmouse)
{
	struct synaptics_data *priv = psmouse->private;
	unsigned char bid[3];

	if (synaptics_send_cmd(psmouse, SYN_QUE_MODES, bid))
		return -1;
	priv->board_id = ((bid[0] & 0xfc) << 6) | bid[1];
	return 0;
}

/*
                                         
 */
static int synaptics_firmware_id(struct psmouse *psmouse)
{
	struct synaptics_data *priv = psmouse->private;
	unsigned char fwid[3];

	if (synaptics_send_cmd(psmouse, SYN_QUE_FIRMWARE_ID, fwid))
		return -1;
	priv->firmware_id = (fwid[0] << 16) | (fwid[1] << 8) | fwid[2];
	return 0;
}

/*
                                             
                                
 */
static int synaptics_capability(struct psmouse *psmouse)
{
	struct synaptics_data *priv = psmouse->private;
	unsigned char cap[3];

	if (synaptics_send_cmd(psmouse, SYN_QUE_CAPABILITIES, cap))
		return -1;
	priv->capabilities = (cap[0] << 16) | (cap[1] << 8) | cap[2];
	priv->ext_cap = priv->ext_cap_0c = 0;

	/*
                                                 
  */
	if (SYN_ID_FULL(priv->identity) < 0x705 &&
	    SYN_CAP_SUBMODEL_ID(priv->capabilities) != 0x47) {
		return -1;
	}

	/*
                                                                     
  */
	if (!SYN_CAP_EXTENDED(priv->capabilities))
		priv->capabilities = 0;

	if (SYN_EXT_CAP_REQUESTS(priv->capabilities) >= 1) {
		if (synaptics_send_cmd(psmouse, SYN_QUE_EXT_CAPAB, cap)) {
			psmouse_warn(psmouse,
				     "device claims to have extended capabilities, but I'm not able to read them.\n");
		} else {
			priv->ext_cap = (cap[0] << 16) | (cap[1] << 8) | cap[2];

			/*
                                                          
                              
    */
			if (SYN_CAP_MULTI_BUTTON_NO(priv->ext_cap) > 8)
				priv->ext_cap &= 0xff0fff;
		}
	}

	if (SYN_EXT_CAP_REQUESTS(priv->capabilities) >= 4) {
		if (synaptics_send_cmd(psmouse, SYN_QUE_EXT_CAPAB_0C, cap)) {
			psmouse_warn(psmouse,
				     "device claims to have extended capability 0x0c, but I'm not able to read it.\n");
		} else {
			priv->ext_cap_0c = (cap[0] << 16) | (cap[1] << 8) | cap[2];
		}
	}

	return 0;
}

/*
                    
                               
 */
static int synaptics_identify(struct psmouse *psmouse)
{
	struct synaptics_data *priv = psmouse->private;
	unsigned char id[3];

	if (synaptics_send_cmd(psmouse, SYN_QUE_IDENTIFY, id))
		return -1;
	priv->identity = (id[0]<<16) | (id[1]<<8) | id[2];
	if (SYN_ID_IS_SYNAPTICS(priv->identity))
		return 0;
	return -1;
}

/*
                                                            
                                                                 
 */

static const int *quirk_min_max;

static int synaptics_resolution(struct psmouse *psmouse)
{
	struct synaptics_data *priv = psmouse->private;
	unsigned char resp[3];

	if (quirk_min_max) {
		priv->x_min = quirk_min_max[0];
		priv->x_max = quirk_min_max[1];
		priv->y_min = quirk_min_max[2];
		priv->y_max = quirk_min_max[3];
		return 0;
	}

	if (SYN_ID_MAJOR(priv->identity) < 4)
		return 0;

	if (synaptics_send_cmd(psmouse, SYN_QUE_RESOLUTION, resp) == 0) {
		if (resp[0] != 0 && (resp[1] & 0x80) && resp[2] != 0) {
			priv->x_res = resp[0]; /*                          */
			priv->y_res = resp[2]; /*                          */
		}
	}

	if (SYN_EXT_CAP_REQUESTS(priv->capabilities) >= 5 &&
	    SYN_CAP_MAX_DIMENSIONS(priv->ext_cap_0c)) {
		if (synaptics_send_cmd(psmouse, SYN_QUE_EXT_MAX_COORDS, resp)) {
			psmouse_warn(psmouse,
				     "device claims to have max coordinates query, but I'm not able to read it.\n");
		} else {
			priv->x_max = (resp[0] << 5) | ((resp[1] & 0x0f) << 1);
			priv->y_max = (resp[2] << 5) | ((resp[1] & 0xf0) >> 3);
		}
	}

	if (SYN_EXT_CAP_REQUESTS(priv->capabilities) >= 7 &&
	    SYN_CAP_MIN_DIMENSIONS(priv->ext_cap_0c)) {
		if (synaptics_send_cmd(psmouse, SYN_QUE_EXT_MIN_COORDS, resp)) {
			psmouse_warn(psmouse,
				     "device claims to have min coordinates query, but I'm not able to read it.\n");
		} else {
			priv->x_min = (resp[0] << 5) | ((resp[1] & 0x0f) << 1);
			priv->y_min = (resp[2] << 5) | ((resp[1] & 0xf0) >> 3);
		}
	}

	return 0;
}

static int synaptics_query_hardware(struct psmouse *psmouse)
{
	if (synaptics_identify(psmouse))
		return -1;
	if (synaptics_model_id(psmouse))
		return -1;
	if (synaptics_firmware_id(psmouse))
		return -1;
	if (synaptics_board_id(psmouse))
		return -1;
	if (synaptics_capability(psmouse))
		return -1;
	if (synaptics_resolution(psmouse))
		return -1;

	return 0;
}

static int synaptics_set_advanced_gesture_mode(struct psmouse *psmouse)
{
	static unsigned char param = 0xc8;
	struct synaptics_data *priv = psmouse->private;

	if (!(SYN_CAP_ADV_GESTURE(priv->ext_cap_0c) ||
	      SYN_CAP_IMAGE_SENSOR(priv->ext_cap_0c)))
		return 0;

	if (psmouse_sliced_command(psmouse, SYN_QUE_MODEL))
		return -1;

	if (ps2_command(&psmouse->ps2dev, &param, PSMOUSE_CMD_SETRATE))
		return -1;

	/*                                                    */
	priv->capabilities |= BIT(1);

	return 0;
}

static int synaptics_set_mode(struct psmouse *psmouse)
{
	struct synaptics_data *priv = psmouse->private;

	priv->mode = 0;
	if (priv->absolute_mode)
		priv->mode |= SYN_BIT_ABSOLUTE_MODE;
	if (priv->disable_gesture)
		priv->mode |= SYN_BIT_DISABLE_GESTURE;
	if (psmouse->rate >= 80)
		priv->mode |= SYN_BIT_HIGH_RATE;
	if (SYN_CAP_EXTENDED(priv->capabilities))
		priv->mode |= SYN_BIT_W_MODE;

	if (synaptics_mode_cmd(psmouse, priv->mode))
		return -1;

	if (priv->absolute_mode &&
	    synaptics_set_advanced_gesture_mode(psmouse)) {
		psmouse_err(psmouse, "Advanced gesture mode init failed.\n");
		return -1;
	}

	return 0;
}

static void synaptics_set_rate(struct psmouse *psmouse, unsigned int rate)
{
	struct synaptics_data *priv = psmouse->private;

	if (rate >= 80) {
		priv->mode |= SYN_BIT_HIGH_RATE;
		psmouse->rate = 80;
	} else {
		priv->mode &= ~SYN_BIT_HIGH_RATE;
		psmouse->rate = 40;
	}

	synaptics_mode_cmd(psmouse, priv->mode);
}

/*                                                                            
                                           
                                                                            */
static int synaptics_pt_write(struct serio *serio, unsigned char c)
{
	struct psmouse *parent = serio_get_drvdata(serio->parent);
	char rate_param = SYN_PS_CLIENT_CMD; /*                                          */

	if (psmouse_sliced_command(parent, c))
		return -1;
	if (ps2_command(&parent->ps2dev, &rate_param, PSMOUSE_CMD_SETRATE))
		return -1;
	return 0;
}

static int synaptics_pt_start(struct serio *serio)
{
	struct psmouse *parent = serio_get_drvdata(serio->parent);
	struct synaptics_data *priv = parent->private;

	serio_pause_rx(parent->ps2dev.serio);
	priv->pt_port = serio;
	serio_continue_rx(parent->ps2dev.serio);

	return 0;
}

static void synaptics_pt_stop(struct serio *serio)
{
	struct psmouse *parent = serio_get_drvdata(serio->parent);
	struct synaptics_data *priv = parent->private;

	serio_pause_rx(parent->ps2dev.serio);
	priv->pt_port = NULL;
	serio_continue_rx(parent->ps2dev.serio);
}

static int synaptics_is_pt_packet(unsigned char *buf)
{
	return (buf[0] & 0xFC) == 0x84 && (buf[3] & 0xCC) == 0xC4;
}

static void synaptics_pass_pt_packet(struct serio *ptport, unsigned char *packet)
{
	struct psmouse *child = serio_get_drvdata(ptport);

	if (child && child->state == PSMOUSE_ACTIVATED) {
		serio_interrupt(ptport, packet[1], 0);
		serio_interrupt(ptport, packet[4], 0);
		serio_interrupt(ptport, packet[5], 0);
		if (child->pktsize == 4)
			serio_interrupt(ptport, packet[2], 0);
	} else
		serio_interrupt(ptport, packet[1], 0);
}

static void synaptics_pt_activate(struct psmouse *psmouse)
{
	struct synaptics_data *priv = psmouse->private;
	struct psmouse *child = serio_get_drvdata(priv->pt_port);

	/*                                                   */
	if (child) {
		if (child->pktsize == 4)
			priv->mode |= SYN_BIT_FOUR_BYTE_CLIENT;
		else
			priv->mode &= ~SYN_BIT_FOUR_BYTE_CLIENT;

		if (synaptics_mode_cmd(psmouse, priv->mode))
			psmouse_warn(psmouse,
				     "failed to switch guest protocol\n");
	}
}

static void synaptics_pt_create(struct psmouse *psmouse)
{
	struct serio *serio;

	serio = kzalloc(sizeof(struct serio), GFP_KERNEL);
	if (!serio) {
		psmouse_err(psmouse,
			    "not enough memory for pass-through port\n");
		return;
	}

	serio->id.type = SERIO_PS_PSTHRU;
	strlcpy(serio->name, "Synaptics pass-through", sizeof(serio->name));
	strlcpy(serio->phys, "synaptics-pt/serio0", sizeof(serio->name));
	serio->write = synaptics_pt_write;
	serio->start = synaptics_pt_start;
	serio->stop = synaptics_pt_stop;
	serio->parent = psmouse->ps2dev.serio;

	psmouse->pt_activate = synaptics_pt_activate;

	psmouse_info(psmouse, "serio: %s port at %s\n",
		     serio->name, psmouse->phys);
	serio_register_port(serio);
}

/*                                                                            
                                                   
                                                                            */

static void synaptics_mt_state_set(struct synaptics_mt_state *state, int count,
				   int sgm, int agm)
{
	state->count = count;
	state->sgm = sgm;
	state->agm = agm;
}

static void synaptics_parse_agm(const unsigned char buf[],
				struct synaptics_data *priv,
				struct synaptics_hw_state *hw)
{
	struct synaptics_hw_state *agm = &priv->agm;
	int agm_packet_type;

	agm_packet_type = (buf[5] & 0x30) >> 4;
	switch (agm_packet_type) {
	case 1:
		/*                                           */
		agm->w = hw->w;
		agm->x = (((buf[4] & 0x0f) << 8) | buf[1]) << 1;
		agm->y = (((buf[4] & 0xf0) << 4) | buf[2]) << 1;
		agm->z = ((buf[3] & 0x30) | (buf[5] & 0x0f)) << 1;
		break;

	case 2:
		/*                                       */
		synaptics_mt_state_set(&agm->mt_state, buf[1], buf[2], buf[4]);
		break;

	default:
		break;
	}

	/*                                                               */
	priv->agm_pending = true;
}

static int synaptics_parse_hw_state(const unsigned char buf[],
				    struct synaptics_data *priv,
				    struct synaptics_hw_state *hw)
{
	memset(hw, 0, sizeof(struct synaptics_hw_state));

	if (SYN_MODEL_NEWABS(priv->model_id)) {
		hw->w = (((buf[0] & 0x30) >> 2) |
			 ((buf[0] & 0x04) >> 1) |
			 ((buf[3] & 0x04) >> 2));

		if ((SYN_CAP_ADV_GESTURE(priv->ext_cap_0c) ||
			SYN_CAP_IMAGE_SENSOR(priv->ext_cap_0c)) &&
		    hw->w == 2) {
			synaptics_parse_agm(buf, priv, hw);
			return 1;
		}

		hw->x = (((buf[3] & 0x10) << 8) |
			 ((buf[1] & 0x0f) << 8) |
			 buf[4]);
		hw->y = (((buf[3] & 0x20) << 7) |
			 ((buf[1] & 0xf0) << 4) |
			 buf[5]);
		hw->z = buf[2];

		hw->left  = (buf[0] & 0x01) ? 1 : 0;
		hw->right = (buf[0] & 0x02) ? 1 : 0;

		if (SYN_CAP_FORCEPAD(priv->ext_cap_0c)) {
			/*
			 * ForcePads, like Clickpads, use middle button
			 * bits to report primary button clicks.
			 * Unfortunately they report primary button not
			 * only when user presses on the pad above certain
			 * threshold, but also when there are more than one
			 * finger on the touchpad, which interferes with
			 * out multi-finger gestures.
			 */
			if (hw->z == 0) {
				/* No contacts */
				priv->press = priv->report_press = false;
			} else if (hw->w >= 4 && ((buf[0] ^ buf[3]) & 0x01)) {
				/*
				 * Single-finger touch with pressure above
				 * the threshold. If pressure stays long
				 * enough, we'll start reporting primary
				 * button. We rely on the device continuing
				 * sending data even if finger does not
				 * move.
				 */
				if  (!priv->press) {
					priv->press_start = jiffies;
					priv->press = true;
				} else if (time_after(jiffies,
						priv->press_start +
							msecs_to_jiffies(50))) {
					priv->report_press = true;
				}
			} else {
				priv->press = false;
			}

			hw->left = priv->report_press;

		} else if (SYN_CAP_CLICKPAD(priv->ext_cap_0c)) {
			/*
                                                        
                                                         
                     
    */
			hw->left = ((buf[0] ^ buf[3]) & 0x01) ? 1 : 0;

		} else if (SYN_CAP_MIDDLE_BUTTON(priv->capabilities)) {
			hw->middle = ((buf[0] ^ buf[3]) & 0x01) ? 1 : 0;
			if (hw->w == 2)
				hw->scroll = (signed char)(buf[1]);
		}

		if (SYN_CAP_FOUR_BUTTON(priv->capabilities)) {
			hw->up   = ((buf[0] ^ buf[3]) & 0x01) ? 1 : 0;
			hw->down = ((buf[0] ^ buf[3]) & 0x02) ? 1 : 0;
		}

		if (SYN_CAP_MULTI_BUTTON_NO(priv->ext_cap) &&
		    ((buf[0] ^ buf[3]) & 0x02)) {
			switch (SYN_CAP_MULTI_BUTTON_NO(priv->ext_cap) & ~0x01) {
			default:
				/*
                                                
                                          
     */
				break;
			case 8:
				hw->ext_buttons |= ((buf[5] & 0x08)) ? 0x80 : 0;
				hw->ext_buttons |= ((buf[4] & 0x08)) ? 0x40 : 0;
			case 6:
				hw->ext_buttons |= ((buf[5] & 0x04)) ? 0x20 : 0;
				hw->ext_buttons |= ((buf[4] & 0x04)) ? 0x10 : 0;
			case 4:
				hw->ext_buttons |= ((buf[5] & 0x02)) ? 0x08 : 0;
				hw->ext_buttons |= ((buf[4] & 0x02)) ? 0x04 : 0;
			case 2:
				hw->ext_buttons |= ((buf[5] & 0x01)) ? 0x02 : 0;
				hw->ext_buttons |= ((buf[4] & 0x01)) ? 0x01 : 0;
			}
		}
	} else {
		hw->x = (((buf[1] & 0x1f) << 8) | buf[2]);
		hw->y = (((buf[4] & 0x1f) << 8) | buf[5]);

		hw->z = (((buf[0] & 0x30) << 2) | (buf[3] & 0x3F));
		hw->w = (((buf[1] & 0x80) >> 4) | ((buf[0] & 0x04) >> 1));

		hw->left  = (buf[0] & 0x01) ? 1 : 0;
		hw->right = (buf[0] & 0x02) ? 1 : 0;
	}

	/*
                                                              
                                                                
                                                                
                                                   
  */
	if (hw->x > X_MAX_POSITIVE)
		hw->x -= 1 << ABS_POS_BITS;
	else if (hw->x == X_MAX_POSITIVE)
		hw->x = XMAX;

	if (hw->y > Y_MAX_POSITIVE)
		hw->y -= 1 << ABS_POS_BITS;
	else if (hw->y == Y_MAX_POSITIVE)
		hw->y = YMAX;

	return 0;
}

static void synaptics_report_semi_mt_slot(struct input_dev *dev, int slot,
					  bool active, int x, int y)
{
	input_mt_slot(dev, slot);
	input_mt_report_slot_state(dev, MT_TOOL_FINGER, active);
	if (active) {
		input_report_abs(dev, ABS_MT_POSITION_X, x);
		input_report_abs(dev, ABS_MT_POSITION_Y, synaptics_invert_y(y));
	}
}

static void synaptics_report_semi_mt_data(struct input_dev *dev,
					  const struct synaptics_hw_state *a,
					  const struct synaptics_hw_state *b,
					  int num_fingers)
{
	if (num_fingers >= 2) {
		synaptics_report_semi_mt_slot(dev, 0, true, min(a->x, b->x),
					      min(a->y, b->y));
		synaptics_report_semi_mt_slot(dev, 1, true, max(a->x, b->x),
					      max(a->y, b->y));
	} else if (num_fingers == 1) {
		synaptics_report_semi_mt_slot(dev, 0, true, a->x, a->y);
		synaptics_report_semi_mt_slot(dev, 1, false, 0, 0);
	} else {
		synaptics_report_semi_mt_slot(dev, 0, false, 0, 0);
		synaptics_report_semi_mt_slot(dev, 1, false, 0, 0);
	}
}

static void synaptics_report_buttons(struct psmouse *psmouse,
				     const struct synaptics_hw_state *hw)
{
	struct input_dev *dev = psmouse->dev;
	struct synaptics_data *priv = psmouse->private;
	int i;

	input_report_key(dev, BTN_LEFT, hw->left);
	input_report_key(dev, BTN_RIGHT, hw->right);

	if (SYN_CAP_MIDDLE_BUTTON(priv->capabilities))
		input_report_key(dev, BTN_MIDDLE, hw->middle);

	if (SYN_CAP_FOUR_BUTTON(priv->capabilities)) {
		input_report_key(dev, BTN_FORWARD, hw->up);
		input_report_key(dev, BTN_BACK, hw->down);
	}

	for (i = 0; i < SYN_CAP_MULTI_BUTTON_NO(priv->ext_cap); i++)
		input_report_key(dev, BTN_0 + i, hw->ext_buttons & (1 << i));
}

static void synaptics_report_slot(struct input_dev *dev, int slot,
				  const struct synaptics_hw_state *hw)
{
	input_mt_slot(dev, slot);
	input_mt_report_slot_state(dev, MT_TOOL_FINGER, (hw != NULL));
	if (!hw)
		return;

	input_report_abs(dev, ABS_MT_POSITION_X, hw->x);
	input_report_abs(dev, ABS_MT_POSITION_Y, synaptics_invert_y(hw->y));
	input_report_abs(dev, ABS_MT_PRESSURE, hw->z);
}

static void synaptics_report_mt_data(struct psmouse *psmouse,
				     struct synaptics_mt_state *mt_state,
				     const struct synaptics_hw_state *sgm)
{
	struct input_dev *dev = psmouse->dev;
	struct synaptics_data *priv = psmouse->private;
	struct synaptics_hw_state *agm = &priv->agm;
	struct synaptics_mt_state *old = &priv->mt_state;

	switch (mt_state->count) {
	case 0:
		synaptics_report_slot(dev, 0, NULL);
		synaptics_report_slot(dev, 1, NULL);
		break;
	case 1:
		if (mt_state->sgm == -1) {
			synaptics_report_slot(dev, 0, NULL);
			synaptics_report_slot(dev, 1, NULL);
		} else if (mt_state->sgm == 0) {
			synaptics_report_slot(dev, 0, sgm);
			synaptics_report_slot(dev, 1, NULL);
		} else {
			synaptics_report_slot(dev, 0, NULL);
			synaptics_report_slot(dev, 1, sgm);
		}
		break;
	default:
		/*
                                                             
                                                               
                                        
                                 
   */
		if (mt_state->sgm != -1 &&
		    (mt_state->sgm == old->sgm ||
		     old->sgm == -1 || mt_state->agm == old->sgm))
			synaptics_report_slot(dev, 0, sgm);
		else
			synaptics_report_slot(dev, 0, NULL);

		/*
                                                             
                                                              
                                 
    
                                                              
                                                               
         
    
                                                                 
                                                               
                                                               
                           
    
                                                        
                                 
                                      
                                 
                                      
    
                                                            
                                                            
                                                          
                                    
   */
		if (mt_state->agm != -1 &&
		    (mt_state->agm == old->agm ||
		     (old->agm == -1 &&
		      (old->sgm == -1 || mt_state->agm == old->sgm))))
			synaptics_report_slot(dev, 1, agm);
		else
			synaptics_report_slot(dev, 1, NULL);
		break;
	}

	/*                                                          */
	input_mt_report_pointer_emulation(dev, false);

	/*                                                         */
	input_mt_report_finger_count(dev, mt_state->count);

	synaptics_report_buttons(psmouse, sgm);

	input_sync(dev);
}

/*                                       */
static void synaptics_image_sensor_0f(struct synaptics_data *priv,
				      struct synaptics_mt_state *mt_state)
{
	synaptics_mt_state_set(mt_state, 0, -1, -1);
	priv->mt_state_lost = false;
}

/*                                       */
static void synaptics_image_sensor_1f(struct synaptics_data *priv,
				      struct synaptics_mt_state *mt_state)
{
	struct synaptics_hw_state *agm = &priv->agm;
	struct synaptics_mt_state *old = &priv->mt_state;

	/*
                                                                   
                                                                   
                              
  */
	if (priv->agm_pending && agm->z == 0) {
		synaptics_mt_state_set(mt_state, 1, 0, -1);
		priv->mt_state_lost = false;
		return;
	}

	switch (old->count) {
	case 0:
		synaptics_mt_state_set(mt_state, 1, 0, -1);
		break;
	case 1:
		/*
                                                             
                                                               
                                                                 
    
                               
                                                    
                                
                                      
    
                                                                 
                                                            
                                   
    
                                                          
                                                              
                        
    
                                                            
                                         
    
                                                                
    
                                                 
   */
		if (priv->mt_state_lost ||
		    (priv->agm_pending && old->sgm <= 0))
			synaptics_mt_state_set(mt_state, 1, 1, -1);
		else if (old->sgm == -1)
			synaptics_mt_state_set(mt_state, 1, 0, -1);
		break;
	case 2:
		/*
                                                               
    
                                                    
                                          
   */
		if (priv->mt_state_lost) {
			synaptics_mt_state_set(mt_state, 1, -1, -1);
			break;
		}
		/*
                                                             
                                  
                                                             
           
   */
		synaptics_mt_state_set(mt_state, 1, old->agm, -1);
		break;
	case 3:
		/*
                                                               
             
    
                                                    
                                          
   */
		synaptics_mt_state_set(mt_state, 1, -1, -1);
		priv->mt_state_lost = true;
		break;
	case 4:
	case 5:
		/*                                            */
		break;
	}
}

/*                                       */
static void synaptics_image_sensor_2f(struct synaptics_data *priv,
				      struct synaptics_mt_state *mt_state)
{
	struct synaptics_mt_state *old = &priv->mt_state;

	switch (old->count) {
	case 0:
		synaptics_mt_state_set(mt_state, 2, 0, 1);
		break;
	case 1:
		/*
                                                                 
                                                              
                   
    
                                                              
            
   */
		if (old->sgm >= 1)
			synaptics_mt_state_set(mt_state, 2, 0, old->sgm);
		else
			synaptics_mt_state_set(mt_state, 2, 0, 1);
		break;
	case 2:
		/*
                                                                 
                         
                                                               
   */
		if (priv->mt_state_lost)
			synaptics_mt_state_set(mt_state, 2, 0, 1);
		/*
                                                             
                                                               
            
   */
		break;
	case 3:
		/*
                                                   
                                                        
                                                      
                                             
    
                                               
                                                  
   */
		synaptics_mt_state_set(mt_state, 2, -1, -1);
		priv->mt_state_lost = true;
		break;
	case 4:
	case 5:
		/*                                            */
		break;
	}
}

/*                                       */
static void synaptics_image_sensor_3f(struct synaptics_data *priv,
				      struct synaptics_mt_state *mt_state)
{
	struct synaptics_mt_state *old = &priv->mt_state;

	switch (old->count) {
	case 0:
		synaptics_mt_state_set(mt_state, 3, 0, 2);
		break;
	case 1:
		/*
                                                                 
                                                                
                         
    
                                                                
   */
		if (old->sgm >= 2)
			synaptics_mt_state_set(mt_state, 3, 0, old->sgm);
		else
			synaptics_mt_state_set(mt_state, 3, 0, 2);
		break;
	case 2:
		/*
                                                               
                                                           
    
                                                           
                                                              
                                                      
    
                                                                
                                                  
   */
		if (old->agm >= 3) {
			synaptics_mt_state_set(mt_state, 3, 0, old->agm);
			break;
		}

		/*
                                                            
                                              
    
                                                            
                                                         
    
                                                           
                                       
   */
		if (priv->mt_state_lost) {
			synaptics_mt_state_set(mt_state, 3, -1, -1);
			break;
		}

		/*
                                                               
                                                                
                                                                 
                                                             
                                                  
                                              
    
                                                           
                                      
   */
		synaptics_mt_state_set(mt_state, 3, 0, -1);
		break;
	case 3:
		/*
                                                           
                                                             
   */
		if (old->agm <= 2)
			synaptics_mt_state_set(mt_state, 3, 0, 2);
		/*
                                                                 
                                 
   */
		break;

	case 4:
	case 5:
		/*                                            */
		break;
	}
}

/*                                               */
static void synaptics_image_sensor_45f(struct synaptics_data *priv,
				       struct synaptics_mt_state *mt_state)
{
	/*                                                      */
	priv->mt_state_lost = false;
}

static void synaptics_image_sensor_process(struct psmouse *psmouse,
					   struct synaptics_hw_state *sgm)
{
	struct synaptics_data *priv = psmouse->private;
	struct synaptics_hw_state *agm = &priv->agm;
	struct synaptics_mt_state mt_state;

	/*                                                            */
	mt_state = agm->mt_state;

	/*
                                                                    
  */
	if (sgm->z == 0)
		synaptics_image_sensor_0f(priv, &mt_state);
	else if (sgm->w >= 4)
		synaptics_image_sensor_1f(priv, &mt_state);
	else if (sgm->w == 0)
		synaptics_image_sensor_2f(priv, &mt_state);
	else if (sgm->w == 1 && mt_state.count <= 3)
		synaptics_image_sensor_3f(priv, &mt_state);
	else
		synaptics_image_sensor_45f(priv, &mt_state);

	/*                                           */
	synaptics_report_mt_data(psmouse, &mt_state, sgm);

	/*                        */
	priv->mt_state = agm->mt_state = mt_state;
	priv->agm_pending = false;
}

/*
                                                          
 */
static void synaptics_process_packet(struct psmouse *psmouse)
{
	struct input_dev *dev = psmouse->dev;
	struct synaptics_data *priv = psmouse->private;
	struct synaptics_hw_state hw;
	int num_fingers;
	int finger_width;

	if (synaptics_parse_hw_state(psmouse->packet, priv, &hw))
		return;

	if (SYN_CAP_IMAGE_SENSOR(priv->ext_cap_0c)) {
		synaptics_image_sensor_process(psmouse, &hw);
		return;
	}

	if (hw.scroll) {
		priv->scroll += hw.scroll;

		while (priv->scroll >= 4) {
			input_report_key(dev, BTN_BACK, !hw.down);
			input_sync(dev);
			input_report_key(dev, BTN_BACK, hw.down);
			input_sync(dev);
			priv->scroll -= 4;
		}
		while (priv->scroll <= -4) {
			input_report_key(dev, BTN_FORWARD, !hw.up);
			input_sync(dev);
			input_report_key(dev, BTN_FORWARD, hw.up);
			input_sync(dev);
			priv->scroll += 4;
		}
		return;
	}

	if (hw.z > 0 && hw.x > 1) {
		num_fingers = 1;
		finger_width = 5;
		if (SYN_CAP_EXTENDED(priv->capabilities)) {
			switch (hw.w) {
			case 0 ... 1:
				if (SYN_CAP_MULTIFINGER(priv->capabilities))
					num_fingers = hw.w + 2;
				break;
			case 2:
				if (SYN_MODEL_PEN(priv->model_id))
					;   /*                                         */
				break;
			case 4 ... 15:
				if (SYN_CAP_PALMDETECT(priv->capabilities))
					finger_width = hw.w;
				break;
			}
		}
	} else {
		num_fingers = 0;
		finger_width = 0;
	}

	if (SYN_CAP_ADV_GESTURE(priv->ext_cap_0c))
		synaptics_report_semi_mt_data(dev, &hw, &priv->agm,
					      num_fingers);

	/*            
                                                                 
                                   
  */
	if (hw.z > 30) input_report_key(dev, BTN_TOUCH, 1);
	if (hw.z < 25) input_report_key(dev, BTN_TOUCH, 0);

	if (num_fingers > 0) {
		input_report_abs(dev, ABS_X, hw.x);
		input_report_abs(dev, ABS_Y, synaptics_invert_y(hw.y));
	}
	input_report_abs(dev, ABS_PRESSURE, hw.z);

	if (SYN_CAP_PALMDETECT(priv->capabilities))
		input_report_abs(dev, ABS_TOOL_WIDTH, finger_width);

	input_report_key(dev, BTN_TOOL_FINGER, num_fingers == 1);
	if (SYN_CAP_MULTIFINGER(priv->capabilities)) {
		input_report_key(dev, BTN_TOOL_DOUBLETAP, num_fingers == 2);
		input_report_key(dev, BTN_TOOL_TRIPLETAP, num_fingers == 3);
	}

	synaptics_report_buttons(psmouse, &hw);

	input_sync(dev);
}

static int synaptics_validate_byte(struct psmouse *psmouse,
				   int idx, unsigned char pkt_type)
{
	static const unsigned char newabs_mask[]	= { 0xC8, 0x00, 0x00, 0xC8, 0x00 };
	static const unsigned char newabs_rel_mask[]	= { 0xC0, 0x00, 0x00, 0xC0, 0x00 };
	static const unsigned char newabs_rslt[]	= { 0x80, 0x00, 0x00, 0xC0, 0x00 };
	static const unsigned char oldabs_mask[]	= { 0xC0, 0x60, 0x00, 0xC0, 0x60 };
	static const unsigned char oldabs_rslt[]	= { 0xC0, 0x00, 0x00, 0x80, 0x00 };
	const char *packet = psmouse->packet;

	if (idx < 0 || idx > 4)
		return 0;

	switch (pkt_type) {

	case SYN_NEWABS:
	case SYN_NEWABS_RELAXED:
		return (packet[idx] & newabs_rel_mask[idx]) == newabs_rslt[idx];

	case SYN_NEWABS_STRICT:
		return (packet[idx] & newabs_mask[idx]) == newabs_rslt[idx];

	case SYN_OLDABS:
		return (packet[idx] & oldabs_mask[idx]) == oldabs_rslt[idx];

	default:
		psmouse_err(psmouse, "unknown packet type %d\n", pkt_type);
		return 0;
	}
}

static unsigned char synaptics_detect_pkt_type(struct psmouse *psmouse)
{
	int i;

	for (i = 0; i < 5; i++)
		if (!synaptics_validate_byte(psmouse, i, SYN_NEWABS_STRICT)) {
			psmouse_info(psmouse, "using relaxed packet validation\n");
			return SYN_NEWABS_RELAXED;
		}

	return SYN_NEWABS_STRICT;
}

static psmouse_ret_t synaptics_process_byte(struct psmouse *psmouse)
{
	struct synaptics_data *priv = psmouse->private;

	if (psmouse->pktcnt >= 6) { /*                      */
		if (unlikely(priv->pkt_type == SYN_NEWABS))
			priv->pkt_type = synaptics_detect_pkt_type(psmouse);

		if (SYN_CAP_PASS_THROUGH(priv->capabilities) &&
		    synaptics_is_pt_packet(psmouse->packet)) {
			if (priv->pt_port)
				synaptics_pass_pt_packet(priv->pt_port, psmouse->packet);
		} else
			synaptics_process_packet(psmouse);

		return PSMOUSE_FULL_PACKET;
	}

	return synaptics_validate_byte(psmouse, psmouse->pktcnt - 1, priv->pkt_type) ?
		PSMOUSE_GOOD_DATA : PSMOUSE_BAD_DATA;
}

/*                                                                            
                                          
                                                                            */
static void set_abs_position_params(struct input_dev *dev,
				    struct synaptics_data *priv, int x_code,
				    int y_code)
{
	int x_min = priv->x_min ?: XMIN_NOMINAL;
	int x_max = priv->x_max ?: XMAX_NOMINAL;
	int y_min = priv->y_min ?: YMIN_NOMINAL;
	int y_max = priv->y_max ?: YMAX_NOMINAL;
	int fuzz = SYN_CAP_REDUCED_FILTERING(priv->ext_cap_0c) ?
			SYN_REDUCED_FILTER_FUZZ : 0;

	input_set_abs_params(dev, x_code, x_min, x_max, fuzz, 0);
	input_set_abs_params(dev, y_code, y_min, y_max, fuzz, 0);
	input_abs_set_res(dev, x_code, priv->x_res);
	input_abs_set_res(dev, y_code, priv->y_res);
}

static void set_input_params(struct input_dev *dev, struct synaptics_data *priv)
{
	int i;

	/*                                 */
	__set_bit(INPUT_PROP_POINTER, dev->propbit);
	__set_bit(EV_KEY, dev->evbit);
	__set_bit(BTN_LEFT, dev->keybit);
	__set_bit(BTN_RIGHT, dev->keybit);

	if (SYN_CAP_MIDDLE_BUTTON(priv->capabilities))
		__set_bit(BTN_MIDDLE, dev->keybit);

	if (!priv->absolute_mode) {
		/*               */
		__set_bit(EV_REL, dev->evbit);
		__set_bit(REL_X, dev->relbit);
		__set_bit(REL_Y, dev->relbit);
		return;
	}

	/*               */
	__set_bit(EV_ABS, dev->evbit);
	set_abs_position_params(dev, priv, ABS_X, ABS_Y);
	input_set_abs_params(dev, ABS_PRESSURE, 0, 255, 0, 0);

	if (SYN_CAP_IMAGE_SENSOR(priv->ext_cap_0c)) {
		set_abs_position_params(dev, priv, ABS_MT_POSITION_X,
					ABS_MT_POSITION_Y);
		/*                                               */
		input_set_abs_params(dev, ABS_MT_PRESSURE, 0, 255, 0, 0);
		input_mt_init_slots(dev, 2, INPUT_MT_POINTER);

		/*                                                */
		__set_bit(BTN_TOOL_QUADTAP, dev->keybit);
		__set_bit(BTN_TOOL_QUINTTAP, dev->keybit);
	} else if (SYN_CAP_ADV_GESTURE(priv->ext_cap_0c)) {
		/*                                        */
		__set_bit(INPUT_PROP_SEMI_MT, dev->propbit);
		input_mt_init_slots(dev, 2, 0);
		set_abs_position_params(dev, priv, ABS_MT_POSITION_X,
					ABS_MT_POSITION_Y);
	}

	if (SYN_CAP_PALMDETECT(priv->capabilities))
		input_set_abs_params(dev, ABS_TOOL_WIDTH, 0, 15, 0, 0);

	__set_bit(BTN_TOUCH, dev->keybit);
	__set_bit(BTN_TOOL_FINGER, dev->keybit);

	if (SYN_CAP_MULTIFINGER(priv->capabilities)) {
		__set_bit(BTN_TOOL_DOUBLETAP, dev->keybit);
		__set_bit(BTN_TOOL_TRIPLETAP, dev->keybit);
	}

	if (SYN_CAP_FOUR_BUTTON(priv->capabilities) ||
	    SYN_CAP_MIDDLE_BUTTON(priv->capabilities)) {
		__set_bit(BTN_FORWARD, dev->keybit);
		__set_bit(BTN_BACK, dev->keybit);
	}

	for (i = 0; i < SYN_CAP_MULTI_BUTTON_NO(priv->ext_cap); i++)
		__set_bit(BTN_0 + i, dev->keybit);

	__clear_bit(EV_REL, dev->evbit);
	__clear_bit(REL_X, dev->relbit);
	__clear_bit(REL_Y, dev->relbit);

	if (SYN_CAP_CLICKPAD(priv->ext_cap_0c)) {
		__set_bit(INPUT_PROP_BUTTONPAD, dev->propbit);
		/*                                   */
		__clear_bit(BTN_RIGHT, dev->keybit);
		__clear_bit(BTN_MIDDLE, dev->keybit);
	}
}

static ssize_t synaptics_show_disable_gesture(struct psmouse *psmouse,
					      void *data, char *buf)
{
	struct synaptics_data *priv = psmouse->private;

	return sprintf(buf, "%c\n", priv->disable_gesture ? '1' : '0');
}

static ssize_t synaptics_set_disable_gesture(struct psmouse *psmouse,
					     void *data, const char *buf,
					     size_t len)
{
	struct synaptics_data *priv = psmouse->private;
	unsigned int value;
	int err;

	err = kstrtouint(buf, 10, &value);
	if (err)
		return err;

	if (value > 1)
		return -EINVAL;

	if (value == priv->disable_gesture)
		return len;

	priv->disable_gesture = value;
	if (value)
		priv->mode |= SYN_BIT_DISABLE_GESTURE;
	else
		priv->mode &= ~SYN_BIT_DISABLE_GESTURE;

	if (synaptics_mode_cmd(psmouse, priv->mode))
		return -EIO;

	return len;
}

PSMOUSE_DEFINE_ATTR(disable_gesture, S_IWUSR | S_IRUGO, NULL,
		    synaptics_show_disable_gesture,
		    synaptics_set_disable_gesture);

static void synaptics_disconnect(struct psmouse *psmouse)
{
	struct synaptics_data *priv = psmouse->private;

	if (!priv->absolute_mode && SYN_ID_DISGEST_SUPPORTED(priv->identity))
		device_remove_file(&psmouse->ps2dev.serio->dev,
				   &psmouse_attr_disable_gesture.dattr);

	synaptics_reset(psmouse);
	kfree(priv);
	psmouse->private = NULL;
}

static int synaptics_reconnect(struct psmouse *psmouse)
{
	struct synaptics_data *priv = psmouse->private;
	struct synaptics_data old_priv = *priv;
	unsigned char param[2];
	int retry = 0;
	int error;

	do {
		psmouse_reset(psmouse);
		if (retry) {
			/*
                                                       
                                                      
                                                      
                                                    
          
    */
			ssleep(1);
		}
		ps2_command(&psmouse->ps2dev, param, PSMOUSE_CMD_GETID);
		error = synaptics_detect(psmouse, 0);
	} while (error && ++retry < 3);

	if (error)
		return -1;

	if (retry > 1)
		psmouse_dbg(psmouse, "reconnected after %d tries\n", retry);

	if (synaptics_query_hardware(psmouse)) {
		psmouse_err(psmouse, "Unable to query device.\n");
		return -1;
	}

	if (synaptics_set_mode(psmouse)) {
		psmouse_err(psmouse, "Unable to initialize device.\n");
		return -1;
	}

	if (old_priv.identity != priv->identity ||
	    old_priv.model_id != priv->model_id ||
	    old_priv.capabilities != priv->capabilities ||
	    old_priv.ext_cap != priv->ext_cap) {
		psmouse_err(psmouse,
			    "hardware appears to be different: id(%ld-%ld), model(%ld-%ld), caps(%lx-%lx), ext(%lx-%lx).\n",
			    old_priv.identity, priv->identity,
			    old_priv.model_id, priv->model_id,
			    old_priv.capabilities, priv->capabilities,
			    old_priv.ext_cap, priv->ext_cap);
		return -1;
	}

	return 0;
}

static bool impaired_toshiba_kbc;

static const struct dmi_system_id __initconst toshiba_dmi_table[] = {
#if defined(CONFIG_DMI) && defined(CONFIG_X86)
	{
		/*                   */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Satellite"),
		},
	},
	{
		/*                  */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
			DMI_MATCH(DMI_PRODUCT_NAME, "dynabook"),
		},
	},
	{
		/*                      */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
			DMI_MATCH(DMI_PRODUCT_NAME, "PORTEGE M300"),
		},

	},
	{
		/*                      */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Portable PC"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "Version 1.0"),
		},

	},
#endif
	{ }
};

static bool broken_olpc_ec;

static const struct dmi_system_id __initconst olpc_dmi_table[] = {
#if defined(CONFIG_DMI) && defined(CONFIG_OLPC)
	{
		/*                     */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "OLPC"),
			DMI_MATCH(DMI_PRODUCT_NAME, "XO"),
		},
	},
#endif
	{ }
};

static const struct dmi_system_id min_max_dmi_table[] __initconst = {
#if defined(CONFIG_DMI)
	{
		/*                       */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "ThinkPad Helix"),
		},
		.driver_data = (int []){1024, 5052, 2258, 4832},
	},
	{
		/*                      */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "ThinkPad X240"),
		},
		.driver_data = (int []){1232, 5710, 1156, 4696},
	},
	{
		/*                           */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "ThinkPad Edge E431"),
		},
		.driver_data = (int []){1024, 5022, 2508, 4832},
	},
	{
		/*                       */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "ThinkPad T431"),
		},
		.driver_data = (int []){1024, 5112, 2024, 4832},
	},
	{
		/*                       */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "ThinkPad T440"),
		},
		.driver_data = (int []){1024, 5112, 2024, 4832},
	},
	{
		/*                      */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "ThinkPad L440"),
		},
		.driver_data = (int []){1024, 5112, 2024, 4832},
	},
	{
		/*                       */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "ThinkPad T540"),
		},
		.driver_data = (int []){1024, 5112, 2024, 4832},
	},
	{
		/*                      */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "ThinkPad L540"),
		},
		.driver_data = (int []){1024, 5112, 2024, 4832},
	},
	{
		/*                      */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "ThinkPad W540"),
		},
		.driver_data = (int []){1024, 5112, 2024, 4832},
	},
	{
		/*                */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_EXACT_MATCH(DMI_PRODUCT_VERSION,
					"ThinkPad S1 Yoga"),
		},
		.driver_data = (int []){1232, 5710, 1156, 4696},
	},
	{
		/*                                                    */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_VERSION,
					"ThinkPad X1 Carbon 2nd"),
		},
		.driver_data = (int []){1024, 5112, 2024, 4832},
	},
#endif
	{ }
};

void __init synaptics_module_init(void)
{
	const struct dmi_system_id *min_max_dmi;

	impaired_toshiba_kbc = dmi_check_system(toshiba_dmi_table);
	broken_olpc_ec = dmi_check_system(olpc_dmi_table);

	min_max_dmi = dmi_first_match(min_max_dmi_table);
	if (min_max_dmi)
		quirk_min_max = min_max_dmi->driver_data;
}

static int __synaptics_init(struct psmouse *psmouse, bool absolute_mode)
{
	struct synaptics_data *priv;
	int err = -1;

	/*
                                                                      
                                                                      
                                                                     
                                          
  */
	if (absolute_mode && broken_olpc_ec) {
		psmouse_info(psmouse,
			     "OLPC XO detected, not enabling Synaptics protocol.\n");
		return -ENODEV;
	}

	psmouse->private = priv = kzalloc(sizeof(struct synaptics_data), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	psmouse_reset(psmouse);

	if (synaptics_query_hardware(psmouse)) {
		psmouse_err(psmouse, "Unable to query device.\n");
		goto init_fail;
	}

	priv->absolute_mode = absolute_mode;
	if (SYN_ID_DISGEST_SUPPORTED(priv->identity))
		priv->disable_gesture = true;

	if (synaptics_set_mode(psmouse)) {
		psmouse_err(psmouse, "Unable to initialize device.\n");
		goto init_fail;
	}

	priv->pkt_type = SYN_MODEL_NEWABS(priv->model_id) ? SYN_NEWABS : SYN_OLDABS;

	psmouse_info(psmouse,
		     "Touchpad model: %ld, fw: %ld.%ld, id: %#lx, caps: %#lx/%#lx/%#lx, board id: %lu, fw id: %lu\n",
		     SYN_ID_MODEL(priv->identity),
		     SYN_ID_MAJOR(priv->identity), SYN_ID_MINOR(priv->identity),
		     priv->model_id,
		     priv->capabilities, priv->ext_cap, priv->ext_cap_0c,
		     priv->board_id, priv->firmware_id);

	set_input_params(psmouse->dev, priv);

	/*
                                                       
                                                         
                                                       
                                                         
                                                          
  */
	psmouse->model = ((priv->model_id & 0x00ff0000) >> 8) |
			  (priv->model_id & 0x000000ff);

	if (absolute_mode) {
		psmouse->protocol_handler = synaptics_process_byte;
		psmouse->pktsize = 6;
	} else {
		/*                                                    */
		psmouse->protocol_handler = psmouse_process_byte;
		psmouse->pktsize = 3;
	}

	psmouse->set_rate = synaptics_set_rate;
	psmouse->disconnect = synaptics_disconnect;
	psmouse->reconnect = synaptics_reconnect;
	psmouse->cleanup = synaptics_reset;
	/*                                                       */
	psmouse->resync_time = 0;

	if (SYN_CAP_PASS_THROUGH(priv->capabilities))
		synaptics_pt_create(psmouse);

	/*
                                                          
                                                            
                                            
  */
	if (psmouse->rate >= 80 && impaired_toshiba_kbc) {
		psmouse_info(psmouse,
			     "Toshiba %s detected, limiting rate to 40pps.\n",
			     dmi_get_system_info(DMI_PRODUCT_NAME));
		psmouse->rate = 40;
	}

	if (!priv->absolute_mode && SYN_ID_DISGEST_SUPPORTED(priv->identity)) {
		err = device_create_file(&psmouse->ps2dev.serio->dev,
					 &psmouse_attr_disable_gesture.dattr);
		if (err) {
			psmouse_err(psmouse,
				    "Failed to create disable_gesture attribute (%d)",
				    err);
			goto init_fail;
		}
	}

	return 0;

 init_fail:
	kfree(priv);
	return err;
}

int synaptics_init(struct psmouse *psmouse)
{
	return __synaptics_init(psmouse, true);
}

int synaptics_init_relative(struct psmouse *psmouse)
{
	return __synaptics_init(psmouse, false);
}

bool synaptics_supported(void)
{
	return true;
}

#else /*                            */

void __init synaptics_module_init(void)
{
}

int synaptics_init(struct psmouse *psmouse)
{
	return -ENOSYS;
}

bool synaptics_supported(void)
{
	return false;
}

#endif /*                            */
