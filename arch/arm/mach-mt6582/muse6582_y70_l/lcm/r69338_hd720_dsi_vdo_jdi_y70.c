/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 */
/* MediaTek Inc. (C) 2013. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
 * AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek Software")
 * have been modified by MediaTek Inc. All revisions are subject to any receiver's
 * applicable license agreements with MediaTek Inc.
 */

/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2008
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/

#ifdef BUILD_LK
#include <string.h>
#include <mt_gpio.h>
#include <platform/mt_pmic.h>
#elif defined(BUILD_UBOOT)
#include <asm/arch/mt_gpio.h>
#else
#include <linux/string.h>
#include <mach/mt_gpio.h>
#include <mach/mt_pm_ldo.h>
#endif

#include "lcm_drv.h"
#include <cust_gpio_usage.h>
#if defined(BUILD_LK)
#define LCM_PRINT printf
#elif defined(BUILD_UBOOT)
#define LCM_PRINT printf
#else
#define LCM_PRINT printk
#endif

//                                                                            
//                 
//                                                                            
//      
#if 1
#define FRAME_WIDTH  			(720)
#define FRAME_HEIGHT 			(1280)
#else
#define FRAME_WIDTH  			(540)
#define FRAME_HEIGHT 			(960)
#endif

//                   
#if 1
#define PHYSICAL_WIDTH        (58)
#define PHYSICAL_HIGHT         (104)
#else
#define PHYSICAL_WIDTH        (70)
#define PHYSICAL_HIGHT         (122)
#endif

#define LCM_ID       (0xb9)
#define LCM_DSI_CMD_MODE		0

#define REGFLAG_DELAY 0xAB
#define REGFLAG_END_OF_TABLE 0xAA //                        

//                                                                            
//                 
//                                                                            

static LCM_UTIL_FUNCS lcm_util = {0};

#define SET_RESET_PIN(v)    								(lcm_util.set_reset_pin((v)))
#define UDELAY(n) 											(lcm_util.udelay(n))
#define MDELAY(n) 											(lcm_util.mdelay(n))

//                                                                            
//                 
//                                                                            

#define dsi_set_cmdq_V3(para_tbl, size, force_update)   	lcm_util.dsi_set_cmdq_V3(para_tbl, size, force_update)
#define dsi_set_cmdq_V2(cmd, count, ppara, force_update)	        lcm_util.dsi_set_cmdq_V2(cmd, count, ppara, force_update)
#define dsi_set_cmdq(pdata, queue_size, force_update)		lcm_util.dsi_set_cmdq(pdata, queue_size, force_update)
#define wrtie_cmd(cmd)										lcm_util.dsi_write_cmd(cmd)
#define write_regs(addr, pdata, byte_nums)					lcm_util.dsi_write_regs(addr, pdata, byte_nums)
#define read_reg(cmd)											lcm_util.dsi_dcs_read_lcm_reg(cmd)
#define read_reg_v2(cmd, buffer, buffer_size)   				lcm_util.dsi_dcs_read_lcm_reg_v2(cmd, buffer, buffer_size)    

static unsigned int need_set_lcm_addr = 1;

struct LCM_setting_table {
    unsigned char cmd;
    unsigned char count;
    unsigned char para_list[64];
};

#if 1
/*                       */
static struct LCM_setting_table lcm_initialization_setting[] = {

	{0x51,  1,  {0xFF}},     //               
	{0x53,  1,  {0x2C}},     //               
	{0x55,  1,  {0x40}},     //               
	{0xB0,  1,  {0x04}},	 //             
	{0xC1,  3,  {0x84, 0x61, 0x00}},	//            
	{0xD6,  1,  {0x01}},	//             

	{0x36,  1,  {0x00}},	//                 

	/*          */
	{0x29,	0,  {}},            //                  

	/*           */
	{0x11,	0,  {}},            //                   
	{REGFLAG_DELAY, 120, {}},    //           
	{REGFLAG_END_OF_TABLE, 0x00, {}},
};
#else
#if 1

/*                           */
static LCM_setting_table_V3 lcm_initialization_setting[] = {

	{0X39, 0X51, 1, {0XFF}},	//                        
	{0X39, 0X53, 1, {0X0C}},		//                  
	{0X39, 0X55, 1, {0X00}},		//          
	{0X29, 0XB0, 1, {0X04}},		//            
	{0X29, 0XC1, 3, {0X84,0X61,0X00}},	//            
	{0X29, 0XC7, 30, {0x00,0x0A,0x16,0x20,0x2C, //       
					0x39,0x43,0x52,0x36,0x3E,
					0x4B,0x58,0x5A,0x5F,0x67,
					0x00,0x0A,0x16,0x20,0x2C,
					0x39,0x43,0x52,0x36,0x3E,
					0x4B,0x58,0x5A,0x5F,0x67}}, //       
	{0X29, 0XC8, 19, {0x00,0x00,0x00,0x00,0x00,
						0xFC,0x00,0x00,0x00,0x00,
						0x00,0xFC,0x00,0x00,0x00,
						0x00,0x00,0xFC,0x00}},
	{0X29, 0XB8, 6, {0x07,0x90,0x1E,0x00,0x40,0x32}}, //                    
	{0X29, 0XB9, 6, {0x07,0x8C,0x3C,0x20,0x2D,0x87}},
	{0X29, 0XBA, 6, {0x07,0x82,0x3C,0x10,0x3C,0xB4}},
	{0X29, 0XCE, 24, {0x7D,0x40,0x43,0x49,0x55,
					0x62,0x71,0x82,0x94,0xA8,
					0xB9,0xCB,0xDB,0xE9,0xF5,
					0xFC,0xFF,0x02,0x00,0x04,
					0x04,0x44,0x04,0x01}},
	{0X29, 0XBB, 3, {0x01,0x1E,0x14}},
	{0X29, 0XBC, 3, {0x01,0x50,0x32}},
	{0X29, 0XBD, 3, {0x00,0xB4,0xA0}},
	{0X29, 0XD6, 1, {0x01}},
	{0X15, 0X36, 1, {0x00}},
	{0X05, 0X29, 1, {0x00}},
	{0X05, 0X11, 1, {0x00}},
	{REGFLAG_DELAY, 120, {}},    //           
	{REGFLAG_END_OF_TABLE, 0x00, {}},

};
#else

/*                           */
static LCM_setting_table_V3 lcm_initialization_setting_V3[] = {

	{0X39, 0X51, 1, {0XFF}},	//                        
	{0X39, 0X53, 1, {0X2C}},		//                  
	{0X39, 0X55, 1, {0X40}},		//          
	{0X29, 0XB0, 1, {0X04}},		//            
	{0X29, 0XC1, 3, {0X84,0X61,0X00}},	//            
	{0X29, 0XC7, 30, {0x00,0x0A,0x16,0x20,0x2C, //       
					0x39,0x43,0x52,0x36,0x3E,
					0x4B,0x58,0x5A,0x5F,0x67,
					0x00,0x0A,0x16,0x20,0x2C,
					0x39,0x43,0x52,0x36,0x3E,
					0x4B,0x58,0x5A,0x5F,0x67}}, //       
	{0X29, 0XC8, 19, {0x00,0x00,0x00,0x00,0x00,
						0xFC,0x00,0x00,0x00,0x00,
						0x00,0xFC,0x00,0x00,0x00,
						0x00,0x00,0xFC,0x00}},
	#if 1
	{0X29, 0XB8, 6, {0x07,0x90,0x1E,0x00,0x40,0x32}}, //                    
	{0X29, 0XB9, 6, {0x07,0x8C,0x3C,0x20,0x2D,0x87}},
	{0X29, 0XBA, 6, {0x07,0x82,0x3C,0x10,0x3C,0xB4}},
	{0X29, 0XCE, 24, {0x7D,0x40,0x43,0x49,0x55,
					0x62,0x71,0x82,0x94,0xA8,
					0xB9,0xCB,0xDB,0xE9,0xF5,
					0xFC,0xFF,0x02,0x00,0x04,
					0x04,0x44,0x04,0x01}},
	{0X29, 0XBB, 3, {0x01,0x1E,0x14}},
	{0X29, 0XBC, 3, {0x01,0x50,0x32}},
	{0X29, 0XBD, 3, {0x00,0xB4,0xA0}},
	#endif
	{0X29, 0XD6, 1, {0x01}},
	{0X15, 0X36, 1, {0x00}},
//                         
//                         
};
#endif
#endif

static struct LCM_setting_table __attribute__ ((unused)) lcm_backlight_level_setting[] = {
	{0x51, 1, {0xFF}},
	{REGFLAG_END_OF_TABLE, 0x00, {}}
};


static void push_table(struct LCM_setting_table *table, unsigned int count, unsigned char force_update)
{
	unsigned int i;

	for(i = 0; i < count; i++) {
		unsigned cmd;
		
		cmd = table[i].cmd;

		switch (cmd) {
		case REGFLAG_DELAY:
			MDELAY(table[i].count);
			break;

		case REGFLAG_END_OF_TABLE:
			break;

		default:
			dsi_set_cmdq_V2(cmd, table[i].count, table[i].para_list, force_update);
		}
	}
	LCM_PRINT("[LCD] push_table \n");
}
//                                                                            
//                            
//                                                                            
static void lcm_set_util_funcs(const LCM_UTIL_FUNCS *util)
{
    memcpy((void*)&lcm_util, (void*)util, sizeof(LCM_UTIL_FUNCS));
}

static void lcm_get_params(LCM_PARAMS * params) 
{
	memset(params, 0, sizeof(LCM_PARAMS));

	params->type   = LCM_TYPE_DSI;

	params->width  = FRAME_WIDTH;
	params->height = FRAME_HEIGHT;

       params->dsi.mode   = SYNC_EVENT_VDO_MODE; //                                     
//                                    
//                                    
	 //                    
	//                                                   
	//                                                    

	//    
	/*                      */
	params->dsi.LANE_NUM				    = LCM_FOUR_LANE;
	//                                                                
	params->dsi.data_format.color_order 	= LCM_COLOR_ORDER_RGB;
	params->dsi.data_format.trans_seq   	= LCM_DSI_TRANS_SEQ_MSB_FIRST;
	params->dsi.data_format.padding     	= LCM_DSI_PADDING_ON_LSB;
	params->dsi.data_format.format      	= LCM_DSI_FORMAT_RGB888;

	//                                         
	params->dsi.packet_size=256;
	//                 
	//                   
	params->dsi.intermediat_buffer_num = 2;

	params->dsi.PS=LCM_PACKED_PS_24BIT_RGB888;

	#if 0
	params->dsi.vertical_sync_active				= 1;//  
	params->dsi.vertical_backporch					= 3;   //              
	params->dsi.vertical_frontporch					= 4;  //             
	params->dsi.vertical_active_line				= FRAME_HEIGHT;

	params->dsi.horizontal_sync_active				= 5;//   
	params->dsi.horizontal_backporch				= 40; //              
	params->dsi.horizontal_frontporch				= 140;  //              
	params->dsi.horizontal_active_pixel				= FRAME_WIDTH;

	params->dsi.PLL_CLOCK = 210;//                                                

	#else
	params->dsi.vertical_sync_active = 1; 
	params->dsi.vertical_backporch = 3; 
	params->dsi.vertical_frontporch = 6; 
	params->dsi.vertical_active_line = FRAME_HEIGHT; 

	params->dsi.horizontal_sync_active				= 5;
	params->dsi.horizontal_backporch				= 60;
	params->dsi.horizontal_frontporch				= 140;
	params->dsi.horizontal_active_pixel 			= FRAME_WIDTH;

	params->dsi.PLL_CLOCK = 208;
	#endif

}

static void init_lcm_registers(void)
{
	unsigned int data_array[32];

#if 1 
#if 1
	push_table(lcm_initialization_setting, sizeof(lcm_initialization_setting) / sizeof(struct LCM_setting_table), 1);
#else

	data_array[0] = 0xff513900; //                        
	dsi_set_cmdq(data_array, 1, 1);

	data_array[0] = 0x2c533900; //                  
//                                                 
	dsi_set_cmdq(data_array, 1, 1);

	data_array[0] = 0x40553900; //          
//                                         
	dsi_set_cmdq(data_array, 1, 1);

	data_array[0] = 0x04B02900; //            
	dsi_set_cmdq(data_array, 1, 1);

	data_array[0] = 0x84C12900;  //            
	data_array[1] = 0x00000061;
	dsi_set_cmdq(data_array, 2, 1);
#if 0
	data_array[0] = 0x00C72900; //       
	data_array[1] = 0x2C20160A;
	data_array[2] = 0x36524339;
	data_array[3] = 0x5A584B3E;
	data_array[4] = 0x0A00675F;
	data_array[5] = 0x392C2016;
	data_array[6] = 0x3E365243;
	data_array[7] = 0x5A584B3E;
	data_array[8] = 0x00000067;
	dsi_set_cmdq(data_array, 9, 1);

	data_array[0] = 0x00C82900; //       
	data_array[1] = 0x00000000;
	data_array[2] = 0x000000FC;
	data_array[3] = 0x00FC0000;
	data_array[4] = 0x00000000;
	data_array[5] = 0x000000FC;
	dsi_set_cmdq(data_array, 6, 1);

	data_array[0] = 0x07B82900; 	//           
	data_array[1] = 0x40001E90;
	data_array[2] = 0x00000032;
	dsi_set_cmdq(data_array, 3, 1);	

	data_array[0] = 0x07B92900; 	//           
	data_array[1] = 0x2D203C8C;
	data_array[2] = 0x00000087;
	dsi_set_cmdq(data_array, 3, 1);	

	data_array[0] = 0x07BA2900; 	//           
	data_array[1] = 0x3C103C82;
	data_array[2] = 0x000000B4;
	dsi_set_cmdq(data_array, 3, 1);	

	data_array[0] = 0x7DCE2900; 	//           
	data_array[1] = 0x55494340;
	data_array[2] = 0x94827162;
	data_array[3] = 0xDBCBB9A8;
	data_array[4] = 0xFFFCF5E9;
	data_array[5] = 0x040402FF;
	data_array[6] = 0x0002FFFC;
	data_array[7] = 0x00010444;
	dsi_set_cmdq(data_array, 8, 1);	

	data_array[0] = 0x01BB2900; //          
	data_array[0] = 0x0000141E;
	dsi_set_cmdq(data_array, 2, 1);

	data_array[0] = 0x01BC2900; //          
	data_array[0] = 0x00003250;
	dsi_set_cmdq(data_array, 2, 1);

	data_array[0] = 0x00BD2900; //          
	data_array[0] = 0x0000A0B4;
	dsi_set_cmdq(data_array, 2, 1);

#endif
	data_array[0] = 0x01D62900; //           
	dsi_set_cmdq(data_array, 1, 1);

	data_array[0] = 0x00361500; //                
	dsi_set_cmdq(data_array, 1, 1);

	data_array[0] = 0x00290500; //          
	dsi_set_cmdq(data_array, 1, 1);

	data_array[0] = 0x00110500; //         
	dsi_set_cmdq(data_array, 1, 1);

#endif
#else
	dsi_set_cmdq_V3(lcm_initialization_setting_V3, sizeof(lcm_initialization_setting_V3) / sizeof(LCM_setting_table_V3), 1);

	data_array[0] = 0x00290500;	//          
	dsi_set_cmdq(data_array, 1, 1);

	data_array[0] = 0x00110500;	//         
	dsi_set_cmdq(data_array, 1, 1);

	MDELAY(120);
#endif
	LCM_PRINT("[LCD] init_lcm_registers \n");
}

static void init_lcm_registers_sleep(void)
{
	unsigned int data_array[1];

	MDELAY(10);
	data_array[0] = 0x00280500; //           
	dsi_set_cmdq(data_array, 1, 1);
	MDELAY(20);
	data_array[0] = 0x00100500; //           
	dsi_set_cmdq(data_array, 1, 1);
	MDELAY(80);
	LCM_PRINT("[LCD] init_lcm_registers_sleep \n");
}


/*                       */
static void ldo_1v8io_on(void)
{
#ifdef BUILD_UBOOT 
	#error "not implemeted"
#elif defined(BUILD_LK) 	
	upmu_set_rg_vcamd_vosel(3);
	upmu_set_rg_vcamd_en(1);
#else
	hwPowerOn(MT6323_POWER_LDO_VGP2, VOL_1800, "1V8_LCD_VIO_MTK_S");
#endif 
}

/*                        */
static void ldo_1v8io_off(void)
{
#ifdef BUILD_UBOOT 
#error "not implemeted"
#elif defined(BUILD_LK) 	
	upmu_set_rg_vcamd_en(0);

#else
	hwPowerDown(MT6323_POWER_LDO_VGP2, "1V8_LCD_VIO_MTK_S");
#endif 
}

/*                      */
static void ldo_3v0_on(void)
{
#if 1 //                  
#ifdef BUILD_UBOOT 
	#error "not implemeted"
#elif defined(BUILD_LK)
	upmu_set_rg_vgp2_vosel(6);  //                                  
	upmu_set_rg_vgp2_en(1);


#else
	hwPowerOn(MT6323_POWER_LDO_VGP1, VOL_3000, "3V0_TOUCH_VDD");
#endif
#else
	mt_set_gpio_mode(GPIO_LCM_PWR, GPIO_LCM_PWR_M_GPIO);
	mt_set_gpio_pull_enable(GPIO_LCM_PWR, GPIO_PULL_ENABLE);
	mt_set_gpio_dir(GPIO_LCM_PWR, GPIO_DIR_OUT);
	mt_set_gpio_out(GPIO_LCM_PWR, GPIO_OUT_ONE);
#endif
}

/*                       */
static void ldo_3v0_off(void)
{
#if 1 //                  
#ifdef BUILD_UBOOT 
	#error "not implemeted"
#elif defined(BUILD_LK)
	upmu_set_rg_vgp2_en(0);
#else
	hwPowerDown(MT6323_POWER_LDO_VGP1, "3V0_TOUCH_VDD");
#endif
#else
	mt_set_gpio_mode(GPIO_LCM_PWR, GPIO_LCM_PWR_M_GPIO);
	mt_set_gpio_pull_enable(GPIO_LCM_PWR, GPIO_PULL_ENABLE);
	mt_set_gpio_dir(GPIO_LCM_PWR, GPIO_DIR_OUT);
	mt_set_gpio_out(GPIO_LCM_PWR, GPIO_OUT_ZERO);
#endif
}

/*
                 
*/
static void ldo_p5m5_dsv_5v5_on(void)
{
	mt_set_gpio_mode(GPIO_DSV_AVDD_EN, GPIO_DSV_AVDD_EN_M_GPIO);
	mt_set_gpio_pull_enable(GPIO_DSV_AVDD_EN, GPIO_PULL_ENABLE);
	mt_set_gpio_dir(GPIO_DSV_AVDD_EN, GPIO_DIR_OUT);
	mt_set_gpio_mode(GPIO_DSV_AVEE_EN, GPIO_DSV_AVEE_EN_M_GPIO);
	mt_set_gpio_pull_enable(GPIO_DSV_AVEE_EN, GPIO_PULL_ENABLE);
	mt_set_gpio_dir(GPIO_DSV_AVEE_EN, GPIO_DIR_OUT);
	
	mt_set_gpio_out(GPIO_DSV_AVEE_EN, GPIO_OUT_ONE);
	MDELAY(4);
	mt_set_gpio_out(GPIO_DSV_AVDD_EN, GPIO_OUT_ONE);
}

static void ldo_p5m5_dsv_5v5_off(void)
{
	mt_set_gpio_mode(GPIO_DSV_AVDD_EN, GPIO_DSV_AVDD_EN_M_GPIO);
	mt_set_gpio_pull_enable(GPIO_DSV_AVDD_EN, GPIO_PULL_ENABLE);
	mt_set_gpio_dir(GPIO_DSV_AVDD_EN, GPIO_DIR_OUT);
	mt_set_gpio_mode(GPIO_DSV_AVEE_EN, GPIO_DSV_AVEE_EN_M_GPIO);
	mt_set_gpio_pull_enable(GPIO_DSV_AVEE_EN, GPIO_PULL_ENABLE);
	mt_set_gpio_dir(GPIO_DSV_AVEE_EN, GPIO_DIR_OUT);
	
	mt_set_gpio_out(GPIO_DSV_AVDD_EN, GPIO_OUT_ZERO);
	MDELAY(10);
	mt_set_gpio_out(GPIO_DSV_AVEE_EN, GPIO_OUT_ZERO);
}


static void reset_lcd_module(unsigned char reset)
{
	mt_set_gpio_mode(GPIO_LCM_RST, GPIO_LCM_RST_M_GPIO);
	mt_set_gpio_pull_enable(GPIO_LCM_RST, GPIO_PULL_ENABLE);
	mt_set_gpio_dir(GPIO_LCM_RST, GPIO_DIR_OUT);

   if(reset){
   	mt_set_gpio_out(GPIO_LCM_RST, GPIO_OUT_ZERO);
      MDELAY(50);	
   }else{
   	mt_set_gpio_out(GPIO_LCM_RST, GPIO_OUT_ONE);
   }
}
   

static void lcm_init(void)
{
#if defined(BUILD_LK) 	
	ldo_p5m5_dsv_5v5_off();
#endif
	//                 

	//              
	ldo_3v0_on();
	MDELAY(200);

	ldo_1v8io_on();

	MDELAY(200);

	ldo_p5m5_dsv_5v5_on();

	MDELAY(20);

	SET_RESET_PIN(1);
	MDELAY(20);
	SET_RESET_PIN(0);
	MDELAY(2);
	SET_RESET_PIN(1);
	MDELAY(20);

	init_lcm_registers();	//                             

	MDELAY(80);
	
//                                         
	need_set_lcm_addr = 1;
	LCM_PRINT("[SEOSCTEST] lcm_init \n");
	LCM_PRINT("[LCD] lcm_init \n");
}

static void lcm_suspend(void)
{
	init_lcm_registers_sleep();

	SET_RESET_PIN(0);
	MDELAY(20);
	//       
	ldo_p5m5_dsv_5v5_off();
	MDELAY(10);
	//             
	ldo_1v8io_off();
	//                  

	LCM_PRINT("[LCD] lcm_suspend \n");
}


static void lcm_resume(void)
{
	lcm_init();
    need_set_lcm_addr = 1;
	LCM_PRINT("[LCD] lcm_resume \n");
}

static void lcm_esd_recover(void)
{
	lcm_suspend();
	lcm_resume();

	LCM_PRINT("[LCD] lcm_esd_recover \n");
}

static void lcm_update(unsigned int x, unsigned int y,
                       unsigned int width, unsigned int height)
{
	unsigned int x0 = x;
	unsigned int y0 = y;
	unsigned int x1 = x0 + width - 1;
	unsigned int y1 = y0 + height - 1;

	unsigned char x0_MSB = ((x0>>8)&0xFF);
	unsigned char x0_LSB = (x0&0xFF);
	unsigned char x1_MSB = ((x1>>8)&0xFF);
	unsigned char x1_LSB = (x1&0xFF);
	unsigned char y0_MSB = ((y0>>8)&0xFF);
	unsigned char y0_LSB = (y0&0xFF);
	unsigned char y1_MSB = ((y1>>8)&0xFF);
	unsigned char y1_LSB = (y1&0xFF);

	unsigned int data_array[16];

	//                              
	if(need_set_lcm_addr)
	{
		data_array[0]= 0x00053902;
		data_array[1]= (x1_MSB<<24)|(x0_LSB<<16)|(x0_MSB<<8)|0x2a;
		data_array[2]= (x1_LSB);
		dsi_set_cmdq(data_array, 3, 1);
		
		data_array[0]= 0x00053902;
		data_array[1]= (y1_MSB<<24)|(y0_LSB<<16)|(y0_MSB<<8)|0x2b;
		data_array[2]= (y1_LSB);
		dsi_set_cmdq(data_array, 3, 1);		
		need_set_lcm_addr = 0;
	}
	
	data_array[0]= 0x002c3909;
   dsi_set_cmdq(data_array, 1, 0);
	LCM_PRINT("[LCD] lcm_update \n");	
}

static unsigned int lcm_compare_id(void)
{
#if 0
	unsigned int id=0;
	unsigned char buffer[2];
	unsigned int array[16];  
    SET_RESET_PIN(1);
    SET_RESET_PIN(0);
    MDELAY(1);
    SET_RESET_PIN(1);
    MDELAY(10);//              
	array[0]=0x00043902;
	array[1]=0x8983FFB9;//            
	dsi_set_cmdq(array, 2, 1);
	MDELAY(10);
	array[0] = 0x00023700;//                   
	dsi_set_cmdq(array, 1, 1);
	MDELAY(10);
	read_reg_v2(0xF4, buffer, 2);
	id = buffer[0]; 
	LCM_PRINT("%s, id = 0x%08x\n", __func__, id);
	return (LCM_ID == id)?1:0;
#else
	LCM_PRINT("[SEOSCTEST] lcm_compare_id \n");	
	return 1;
#endif	
}
//                                                                            
//                      
//                                                                            
LCM_DRIVER r69338_hd720_dsi_vdo_jdi_y70_drv = {
	.name = "r69338_hd720_dsi_vdo_jdi_y70",
	.set_util_funcs = lcm_set_util_funcs,
	.get_params = lcm_get_params,
	.init = lcm_init,
	.suspend = lcm_suspend,
	.resume = lcm_resume,
//                              
//                      
#if (!defined(BUILD_UBOOT) && !defined(BUILD_LK))
//                                
#endif
};
