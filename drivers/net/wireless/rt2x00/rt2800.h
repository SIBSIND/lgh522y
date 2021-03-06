/*
	Copyright (C) 2004 - 2010 Ivo van Doorn <IvDoorn@gmail.com>
	Copyright (C) 2010 Willow Garage <http://www.willowgarage.com>
	Copyright (C) 2009 Alban Browaeys <prahal@yahoo.com>
	Copyright (C) 2009 Felix Fietkau <nbd@openwrt.org>
	Copyright (C) 2009 Luis Correia <luis.f.correia@gmail.com>
	Copyright (C) 2009 Mattias Nissler <mattias.nissler@gmx.de>
	Copyright (C) 2009 Mark Asselstine <asselsm@gmail.com>
	Copyright (C) 2009 Xose Vazquez Perez <xose.vazquez@gmail.com>
	Copyright (C) 2009 Bart Zolnierkiewicz <bzolnier@gmail.com>
	<http://rt2x00.serialmonkey.com>

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the
	Free Software Foundation, Inc.,
	59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

/*
               
                                                                
                                                 
 */

#ifndef RT2800_H
#define RT2800_H

/*
                   
  
                   
                      
                   
                      
                   
                  
                   
                   
                      
                      
                                         
                                                       
                                                          
                      
                   
                   
                   
 */
#define RF2820				0x0001
#define RF2850				0x0002
#define RF2720				0x0003
#define RF2750				0x0004
#define RF3020				0x0005
#define RF2020				0x0006
#define RF3021				0x0007
#define RF3022				0x0008
#define RF3052				0x0009
#define RF2853				0x000a
#define RF3320				0x000b
#define RF3322				0x000c
#define RF3053				0x000d
#define RF5592				0x000f
#define RF3290				0x3290
#define RF5360				0x5360
#define RF5370				0x5370
#define RF5372				0x5372
#define RF5390				0x5390
#define RF5392				0x5392

/*
                     
 */
#define REV_RT2860C			0x0100
#define REV_RT2860D			0x0101
#define REV_RT2872E			0x0200
#define REV_RT3070E			0x0200
#define REV_RT3070F			0x0201
#define REV_RT3071E			0x0211
#define REV_RT3090E			0x0211
#define REV_RT3390E			0x0211
#define REV_RT5390F			0x0502
#define REV_RT5390R			0x1502
#define REV_RT5592C			0x0221

#define DEFAULT_RSSI_OFFSET		120

/*
                               
 */
#define CSR_REG_BASE			0x1000
#define CSR_REG_SIZE			0x0800
#define EEPROM_BASE			0x0000
#define EEPROM_SIZE			0x0110
#define BBP_BASE			0x0000
#define BBP_SIZE			0x00ff
#define RF_BASE				0x0004
#define RF_SIZE				0x0010
#define RFCSR_BASE			0x0000
#define RFCSR_SIZE			0x0040

/*
                       
 */
#define NUM_TX_QUEUES			4

/*
             
 */


/*
                                                                     
 */
#define MAC_CSR0_3290				0x0000

/*
                                           
                                            
                           
                                  
 */
#define E2PROM_CSR			0x0004
#define E2PROM_CSR_DATA_CLOCK		FIELD32(0x00000001)
#define E2PROM_CSR_CHIP_SELECT		FIELD32(0x00000002)
#define E2PROM_CSR_DATA_IN		FIELD32(0x00000004)
#define E2PROM_CSR_DATA_OUT		FIELD32(0x00000008)
#define E2PROM_CSR_TYPE			FIELD32(0x00000030)
#define E2PROM_CSR_LOAD_STATUS		FIELD32(0x00000040)
#define E2PROM_CSR_RELOAD		FIELD32(0x00000080)

/*
               
 */
#define CMB_CTRL		0x0020
#define AUX_OPT_BIT0		FIELD32(0x00000001)
#define AUX_OPT_BIT1		FIELD32(0x00000002)
#define AUX_OPT_BIT2		FIELD32(0x00000004)
#define AUX_OPT_BIT3		FIELD32(0x00000008)
#define AUX_OPT_BIT4		FIELD32(0x00000010)
#define AUX_OPT_BIT5		FIELD32(0x00000020)
#define AUX_OPT_BIT6		FIELD32(0x00000040)
#define AUX_OPT_BIT7		FIELD32(0x00000080)
#define AUX_OPT_BIT8		FIELD32(0x00000100)
#define AUX_OPT_BIT9		FIELD32(0x00000200)
#define AUX_OPT_BIT10		FIELD32(0x00000400)
#define AUX_OPT_BIT11		FIELD32(0x00000800)
#define AUX_OPT_BIT12		FIELD32(0x00001000)
#define AUX_OPT_BIT13		FIELD32(0x00002000)
#define AUX_OPT_BIT14		FIELD32(0x00004000)
#define AUX_OPT_BIT15		FIELD32(0x00008000)
#define LDO25_LEVEL		FIELD32(0x00030000)
#define LDO25_LARGEA		FIELD32(0x00040000)
#define LDO25_FRC_ON		FIELD32(0x00080000)
#define CMB_RSV			FIELD32(0x00300000)
#define XTAL_RDY		FIELD32(0x00400000)
#define PLL_LD			FIELD32(0x00800000)
#define LDO_CORE_LEVEL		FIELD32(0x0F000000)
#define LDO_BGSEL		FIELD32(0x30000000)
#define LDO3_EN			FIELD32(0x40000000)
#define LDO0_EN			FIELD32(0x80000000)

/*
                                
 */
#define EFUSE_CTRL_3290			0x0024

/*
                      
 */
#define EFUSE_DATA3_3290		0x0028

/*
                      
 */
#define EFUSE_DATA2_3290		0x002c

/*
                      
 */
#define EFUSE_DATA1_3290		0x0030

/*
                      
 */
#define EFUSE_DATA0_3290		0x0034

/*
               
                                
 */
#define OSC_CTRL		0x0038
#define OSC_REF_CYCLE		FIELD32(0x00001fff)
#define OSC_RSV			FIELD32(0x0000e000)
#define OSC_CAL_CNT		FIELD32(0x0fff0000)
#define OSC_CAL_ACK		FIELD32(0x10000000)
#define OSC_CLK_32K_VLD		FIELD32(0x20000000)
#define OSC_CAL_REQ		FIELD32(0x40000000)
#define OSC_ROSC_EN		FIELD32(0x80000000)

/*
             
 */
#define COEX_CFG0			0x0040
#define COEX_CFG_ANT		FIELD32(0xff000000)
/*
             
 */
#define COEX_CFG1			0x0044

/*
             
 */
#define COEX_CFG2			0x0048
#define BT_COEX_CFG1		FIELD32(0xff000000)
#define BT_COEX_CFG0		FIELD32(0x00ff0000)
#define WL_COEX_CFG1		FIELD32(0x0000ff00)
#define WL_COEX_CFG0		FIELD32(0x000000ff)
/*
               
                             
 */
#define PLL_CTRL		0x0050
#define PLL_RESERVED_INPUT1	FIELD32(0x000000ff)
#define PLL_RESERVED_INPUT2	FIELD32(0x0000ff00)
#define PLL_CONTROL		FIELD32(0x00070000)
#define PLL_LPF_R1		FIELD32(0x00080000)
#define PLL_LPF_C1_CTRL	FIELD32(0x00300000)
#define PLL_LPF_C2_CTRL	FIELD32(0x00c00000)
#define PLL_CP_CURRENT_CTRL	FIELD32(0x03000000)
#define PLL_PFD_DELAY_CTRL	FIELD32(0x0c000000)
#define PLL_LOCK_CTRL		FIELD32(0x70000000)
#define PLL_VBGBK_EN		FIELD32(0x80000000)


/*
                
                            
 */
#define WLAN_FUN_CTRL			0x0080
#define WLAN_EN				FIELD32(0x00000001)
#define WLAN_CLK_EN			FIELD32(0x00000002)
#define WLAN_RSV1			FIELD32(0x00000004)
#define WLAN_RESET			FIELD32(0x00000008)
#define PCIE_APP0_CLK_REQ		FIELD32(0x00000010)
#define FRC_WL_ANT_SET			FIELD32(0x00000020)
#define INV_TR_SW0			FIELD32(0x00000040)
#define WLAN_GPIO_IN_BIT0		FIELD32(0x00000100)
#define WLAN_GPIO_IN_BIT1		FIELD32(0x00000200)
#define WLAN_GPIO_IN_BIT2		FIELD32(0x00000400)
#define WLAN_GPIO_IN_BIT3		FIELD32(0x00000800)
#define WLAN_GPIO_IN_BIT4		FIELD32(0x00001000)
#define WLAN_GPIO_IN_BIT5		FIELD32(0x00002000)
#define WLAN_GPIO_IN_BIT6		FIELD32(0x00004000)
#define WLAN_GPIO_IN_BIT7		FIELD32(0x00008000)
#define WLAN_GPIO_IN_BIT_ALL		FIELD32(0x0000ff00)
#define WLAN_GPIO_OUT_BIT0		FIELD32(0x00010000)
#define WLAN_GPIO_OUT_BIT1		FIELD32(0x00020000)
#define WLAN_GPIO_OUT_BIT2		FIELD32(0x00040000)
#define WLAN_GPIO_OUT_BIT3		FIELD32(0x00050000)
#define WLAN_GPIO_OUT_BIT4		FIELD32(0x00100000)
#define WLAN_GPIO_OUT_BIT5		FIELD32(0x00200000)
#define WLAN_GPIO_OUT_BIT6		FIELD32(0x00400000)
#define WLAN_GPIO_OUT_BIT7		FIELD32(0x00800000)
#define WLAN_GPIO_OUT_BIT_ALL		FIELD32(0x00ff0000)
#define WLAN_GPIO_OUT_OE_BIT0		FIELD32(0x01000000)
#define WLAN_GPIO_OUT_OE_BIT1		FIELD32(0x02000000)
#define WLAN_GPIO_OUT_OE_BIT2		FIELD32(0x04000000)
#define WLAN_GPIO_OUT_OE_BIT3		FIELD32(0x08000000)
#define WLAN_GPIO_OUT_OE_BIT4		FIELD32(0x10000000)
#define WLAN_GPIO_OUT_OE_BIT5		FIELD32(0x20000000)
#define WLAN_GPIO_OUT_OE_BIT6		FIELD32(0x40000000)
#define WLAN_GPIO_OUT_OE_BIT7		FIELD32(0x80000000)
#define WLAN_GPIO_OUT_OE_BIT_ALL	FIELD32(0xff000000)

/*
                                            
 */
#define AUX_CTRL			0x10c
#define AUX_CTRL_WAKE_PCIE_EN		FIELD32(0x00000002)
#define AUX_CTRL_FORCE_PCIE_CLK		FIELD32(0x00000400)

/*
                                                   
 */
#define OPT_14_CSR			0x0114
#define OPT_14_CSR_BIT0			FIELD32(0x00000001)

/*
                                             
                                        
                                                                      
 */
#define INT_SOURCE_CSR			0x0200
#define INT_SOURCE_CSR_RXDELAYINT	FIELD32(0x00000001)
#define INT_SOURCE_CSR_TXDELAYINT	FIELD32(0x00000002)
#define INT_SOURCE_CSR_RX_DONE		FIELD32(0x00000004)
#define INT_SOURCE_CSR_AC0_DMA_DONE	FIELD32(0x00000008)
#define INT_SOURCE_CSR_AC1_DMA_DONE	FIELD32(0x00000010)
#define INT_SOURCE_CSR_AC2_DMA_DONE	FIELD32(0x00000020)
#define INT_SOURCE_CSR_AC3_DMA_DONE	FIELD32(0x00000040)
#define INT_SOURCE_CSR_HCCA_DMA_DONE	FIELD32(0x00000080)
#define INT_SOURCE_CSR_MGMT_DMA_DONE	FIELD32(0x00000100)
#define INT_SOURCE_CSR_MCU_COMMAND	FIELD32(0x00000200)
#define INT_SOURCE_CSR_RXTX_COHERENT	FIELD32(0x00000400)
#define INT_SOURCE_CSR_TBTT		FIELD32(0x00000800)
#define INT_SOURCE_CSR_PRE_TBTT		FIELD32(0x00001000)
#define INT_SOURCE_CSR_TX_FIFO_STATUS	FIELD32(0x00002000)
#define INT_SOURCE_CSR_AUTO_WAKEUP	FIELD32(0x00004000)
#define INT_SOURCE_CSR_GPTIMER		FIELD32(0x00008000)
#define INT_SOURCE_CSR_RX_COHERENT	FIELD32(0x00010000)
#define INT_SOURCE_CSR_TX_COHERENT	FIELD32(0x00020000)

/*
                                                                       
 */
#define INT_MASK_CSR			0x0204
#define INT_MASK_CSR_RXDELAYINT		FIELD32(0x00000001)
#define INT_MASK_CSR_TXDELAYINT		FIELD32(0x00000002)
#define INT_MASK_CSR_RX_DONE		FIELD32(0x00000004)
#define INT_MASK_CSR_AC0_DMA_DONE	FIELD32(0x00000008)
#define INT_MASK_CSR_AC1_DMA_DONE	FIELD32(0x00000010)
#define INT_MASK_CSR_AC2_DMA_DONE	FIELD32(0x00000020)
#define INT_MASK_CSR_AC3_DMA_DONE	FIELD32(0x00000040)
#define INT_MASK_CSR_HCCA_DMA_DONE	FIELD32(0x00000080)
#define INT_MASK_CSR_MGMT_DMA_DONE	FIELD32(0x00000100)
#define INT_MASK_CSR_MCU_COMMAND	FIELD32(0x00000200)
#define INT_MASK_CSR_RXTX_COHERENT	FIELD32(0x00000400)
#define INT_MASK_CSR_TBTT		FIELD32(0x00000800)
#define INT_MASK_CSR_PRE_TBTT		FIELD32(0x00001000)
#define INT_MASK_CSR_TX_FIFO_STATUS	FIELD32(0x00002000)
#define INT_MASK_CSR_AUTO_WAKEUP	FIELD32(0x00004000)
#define INT_MASK_CSR_GPTIMER		FIELD32(0x00008000)
#define INT_MASK_CSR_RX_COHERENT	FIELD32(0x00010000)
#define INT_MASK_CSR_TX_COHERENT	FIELD32(0x00020000)

/*
                
 */
#define WPDMA_GLO_CFG 			0x0208
#define WPDMA_GLO_CFG_ENABLE_TX_DMA	FIELD32(0x00000001)
#define WPDMA_GLO_CFG_TX_DMA_BUSY    	FIELD32(0x00000002)
#define WPDMA_GLO_CFG_ENABLE_RX_DMA	FIELD32(0x00000004)
#define WPDMA_GLO_CFG_RX_DMA_BUSY	FIELD32(0x00000008)
#define WPDMA_GLO_CFG_WP_DMA_BURST_SIZE	FIELD32(0x00000030)
#define WPDMA_GLO_CFG_TX_WRITEBACK_DONE	FIELD32(0x00000040)
#define WPDMA_GLO_CFG_BIG_ENDIAN	FIELD32(0x00000080)
#define WPDMA_GLO_CFG_RX_HDR_SCATTER	FIELD32(0x0000ff00)
#define WPDMA_GLO_CFG_HDR_SEG_LEN	FIELD32(0xffff0000)

/*
                
 */
#define WPDMA_RST_IDX 			0x020c
#define WPDMA_RST_IDX_DTX_IDX0		FIELD32(0x00000001)
#define WPDMA_RST_IDX_DTX_IDX1		FIELD32(0x00000002)
#define WPDMA_RST_IDX_DTX_IDX2		FIELD32(0x00000004)
#define WPDMA_RST_IDX_DTX_IDX3		FIELD32(0x00000008)
#define WPDMA_RST_IDX_DTX_IDX4		FIELD32(0x00000010)
#define WPDMA_RST_IDX_DTX_IDX5		FIELD32(0x00000020)
#define WPDMA_RST_IDX_DRX_IDX0		FIELD32(0x00010000)

/*
                
 */
#define DELAY_INT_CFG			0x0210
#define DELAY_INT_CFG_RXMAX_PTIME	FIELD32(0x000000ff)
#define DELAY_INT_CFG_RXMAX_PINT	FIELD32(0x00007f00)
#define DELAY_INT_CFG_RXDLY_INT_EN	FIELD32(0x00008000)
#define DELAY_INT_CFG_TXMAX_PTIME	FIELD32(0x00ff0000)
#define DELAY_INT_CFG_TXMAX_PINT	FIELD32(0x7f000000)
#define DELAY_INT_CFG_TXDLY_INT_EN	FIELD32(0x80000000)

/*
                                        
                
                
                
                
 */
#define WMM_AIFSN_CFG			0x0214
#define WMM_AIFSN_CFG_AIFSN0		FIELD32(0x0000000f)
#define WMM_AIFSN_CFG_AIFSN1		FIELD32(0x000000f0)
#define WMM_AIFSN_CFG_AIFSN2		FIELD32(0x00000f00)
#define WMM_AIFSN_CFG_AIFSN3		FIELD32(0x0000f000)

/*
                                        
                
                
                
                
 */
#define WMM_CWMIN_CFG			0x0218
#define WMM_CWMIN_CFG_CWMIN0		FIELD32(0x0000000f)
#define WMM_CWMIN_CFG_CWMIN1		FIELD32(0x000000f0)
#define WMM_CWMIN_CFG_CWMIN2		FIELD32(0x00000f00)
#define WMM_CWMIN_CFG_CWMIN3		FIELD32(0x0000f000)

/*
                                        
                
                
                
                
 */
#define WMM_CWMAX_CFG			0x021c
#define WMM_CWMAX_CFG_CWMAX0		FIELD32(0x0000000f)
#define WMM_CWMAX_CFG_CWMAX1		FIELD32(0x000000f0)
#define WMM_CWMAX_CFG_CWMAX2		FIELD32(0x00000f00)
#define WMM_CWMAX_CFG_CWMAX3		FIELD32(0x0000f000)

/*
                                      
                                 
                                 
 */
#define WMM_TXOP0_CFG			0x0220
#define WMM_TXOP0_CFG_AC0TXOP		FIELD32(0x0000ffff)
#define WMM_TXOP0_CFG_AC1TXOP		FIELD32(0xffff0000)

/*
                                      
                                 
                                 
 */
#define WMM_TXOP1_CFG			0x0224
#define WMM_TXOP1_CFG_AC2TXOP		FIELD32(0x0000ffff)
#define WMM_TXOP1_CFG_AC3TXOP		FIELD32(0xffff0000)

/*
             
                             
                                                        
 */
#define GPIO_CTRL			0x0228
#define GPIO_CTRL_VAL0			FIELD32(0x00000001)
#define GPIO_CTRL_VAL1			FIELD32(0x00000002)
#define GPIO_CTRL_VAL2			FIELD32(0x00000004)
#define GPIO_CTRL_VAL3			FIELD32(0x00000008)
#define GPIO_CTRL_VAL4			FIELD32(0x00000010)
#define GPIO_CTRL_VAL5			FIELD32(0x00000020)
#define GPIO_CTRL_VAL6			FIELD32(0x00000040)
#define GPIO_CTRL_VAL7			FIELD32(0x00000080)
#define GPIO_CTRL_DIR0			FIELD32(0x00000100)
#define GPIO_CTRL_DIR1			FIELD32(0x00000200)
#define GPIO_CTRL_DIR2			FIELD32(0x00000400)
#define GPIO_CTRL_DIR3			FIELD32(0x00000800)
#define GPIO_CTRL_DIR4			FIELD32(0x00001000)
#define GPIO_CTRL_DIR5			FIELD32(0x00002000)
#define GPIO_CTRL_DIR6			FIELD32(0x00004000)
#define GPIO_CTRL_DIR7			FIELD32(0x00008000)
#define GPIO_CTRL_VAL8			FIELD32(0x00010000)
#define GPIO_CTRL_VAL9			FIELD32(0x00020000)
#define GPIO_CTRL_VAL10			FIELD32(0x00040000)
#define GPIO_CTRL_DIR8			FIELD32(0x01000000)
#define GPIO_CTRL_DIR9			FIELD32(0x02000000)
#define GPIO_CTRL_DIR10			FIELD32(0x04000000)

/*
              
 */
#define MCU_CMD_CFG			0x022c

/*
                         
 */
#define TX_BASE_PTR0			0x0230
#define TX_MAX_CNT0			0x0234
#define TX_CTX_IDX0			0x0238
#define TX_DTX_IDX0			0x023c

/*
                         
 */
#define TX_BASE_PTR1			0x0240
#define TX_MAX_CNT1			0x0244
#define TX_CTX_IDX1			0x0248
#define TX_DTX_IDX1			0x024c

/*
                         
 */
#define TX_BASE_PTR2			0x0250
#define TX_MAX_CNT2			0x0254
#define TX_CTX_IDX2			0x0258
#define TX_DTX_IDX2			0x025c

/*
                         
 */
#define TX_BASE_PTR3			0x0260
#define TX_MAX_CNT3			0x0264
#define TX_CTX_IDX3			0x0268
#define TX_DTX_IDX3			0x026c

/*
                        
 */
#define TX_BASE_PTR4			0x0270
#define TX_MAX_CNT4			0x0274
#define TX_CTX_IDX4			0x0278
#define TX_DTX_IDX4			0x027c

/*
                        
 */
#define TX_BASE_PTR5			0x0280
#define TX_MAX_CNT5			0x0284
#define TX_CTX_IDX5			0x0288
#define TX_DTX_IDX5			0x028c

/*
                      
 */
#define RX_BASE_PTR			0x0290
#define RX_MAX_CNT			0x0294
#define RX_CRX_IDX			0x0298
#define RX_DRX_IDX			0x029c

/*
              
                                                                    
                                                                     
                                   
                                   
                                                          
                                              
                                 
                                 
                                         
                                
                                
 */
#define USB_DMA_CFG			0x02a0
#define USB_DMA_CFG_RX_BULK_AGG_TIMEOUT	FIELD32(0x000000ff)
#define USB_DMA_CFG_RX_BULK_AGG_LIMIT	FIELD32(0x0000ff00)
#define USB_DMA_CFG_PHY_CLEAR		FIELD32(0x00010000)
#define USB_DMA_CFG_TX_CLEAR		FIELD32(0x00080000)
#define USB_DMA_CFG_TXOP_HALT		FIELD32(0x00100000)
#define USB_DMA_CFG_RX_BULK_AGG_EN	FIELD32(0x00200000)
#define USB_DMA_CFG_RX_BULK_EN		FIELD32(0x00400000)
#define USB_DMA_CFG_TX_BULK_EN		FIELD32(0x00800000)
#define USB_DMA_CFG_EP_OUT_VALID	FIELD32(0x3f000000)
#define USB_DMA_CFG_RX_BUSY		FIELD32(0x40000000)
#define USB_DMA_CFG_TX_BUSY		FIELD32(0x80000000)

/*
             
                                    
                                         
                                
 */
#define US_CYC_CNT			0x02a4
#define US_CYC_CNT_BT_MODE_EN		FIELD32(0x00000100)
#define US_CYC_CNT_CLOCK_CYCLE		FIELD32(0x000000ff)

/*
               
                                                          
 */
#define PBF_SYS_CTRL			0x0400
#define PBF_SYS_CTRL_READY		FIELD32(0x00000080)
#define PBF_SYS_CTRL_HOST_RAM_WRITE	FIELD32(0x00010000)

/*
                         
 */
#define HOST_CMD_CSR			0x0404
#define HOST_CMD_CSR_HOST_COMMAND	FIELD32(0x000000ff)

/*
                
                                                         
 */
#define PBF_CFG				0x0408
#define PBF_MAX_PCNT			0x040c
#define PBF_CTRL			0x0410
#define PBF_INT_STA			0x0414
#define PBF_INT_ENA			0x0418

/*
               
 */
#define BCN_OFFSET0			0x042c
#define BCN_OFFSET0_BCN0		FIELD32(0x000000ff)
#define BCN_OFFSET0_BCN1		FIELD32(0x0000ff00)
#define BCN_OFFSET0_BCN2		FIELD32(0x00ff0000)
#define BCN_OFFSET0_BCN3		FIELD32(0xff000000)

/*
               
 */
#define BCN_OFFSET1			0x0430
#define BCN_OFFSET1_BCN4		FIELD32(0x000000ff)
#define BCN_OFFSET1_BCN5		FIELD32(0x0000ff00)
#define BCN_OFFSET1_BCN6		FIELD32(0x00ff0000)
#define BCN_OFFSET1_BCN7		FIELD32(0xff000000)

/*
                           
                                                
                                                
                                                
                                              
 */
#define TXRXQ_PCNT			0x0438
#define TXRXQ_PCNT_TX0Q			FIELD32(0x000000ff)
#define TXRXQ_PCNT_TX1Q			FIELD32(0x0000ff00)
#define TXRXQ_PCNT_TX2Q			FIELD32(0x00ff0000)
#define TXRXQ_PCNT_RX0Q			FIELD32(0xff000000)

/*
               
                                            
 */
#define PBF_DBG				0x043c

/*
               
 */
#define	RF_CSR_CFG			0x0500
#define RF_CSR_CFG_DATA			FIELD32(0x000000ff)
#define RF_CSR_CFG_REGNUM		FIELD32(0x00003f00)
#define RF_CSR_CFG_WRITE		FIELD32(0x00010000)
#define RF_CSR_CFG_BUSY			FIELD32(0x00020000)

/*
                           
 */
#define EFUSE_CTRL			0x0580
#define EFUSE_CTRL_ADDRESS_IN		FIELD32(0x03fe0000)
#define EFUSE_CTRL_MODE			FIELD32(0x000000c0)
#define EFUSE_CTRL_KICK			FIELD32(0x40000000)
#define EFUSE_CTRL_PRESENT		FIELD32(0x80000000)

/*
              
 */
#define EFUSE_DATA0			0x0590

/*
              
 */
#define EFUSE_DATA1			0x0594

/*
              
 */
#define EFUSE_DATA2			0x0598

/*
              
 */
#define EFUSE_DATA3			0x059c

/*
           
 */
#define LDO_CFG0			0x05d4
#define LDO_CFG0_DELAY3			FIELD32(0x000000ff)
#define LDO_CFG0_DELAY2			FIELD32(0x0000ff00)
#define LDO_CFG0_DELAY1			FIELD32(0x00ff0000)
#define LDO_CFG0_BGSEL			FIELD32(0x03000000)
#define LDO_CFG0_LDO_CORE_VLEVEL	FIELD32(0x1c000000)
#define LD0_CFG0_LDO25_LEVEL		FIELD32(0x60000000)
#define LDO_CFG0_LDO25_LARGEA		FIELD32(0x80000000)

/*
              
 */
#define GPIO_SWITCH			0x05dc
#define GPIO_SWITCH_0			FIELD32(0x00000001)
#define GPIO_SWITCH_1			FIELD32(0x00000002)
#define GPIO_SWITCH_2			FIELD32(0x00000004)
#define GPIO_SWITCH_3			FIELD32(0x00000008)
#define GPIO_SWITCH_4			FIELD32(0x00000010)
#define GPIO_SWITCH_5			FIELD32(0x00000020)
#define GPIO_SWITCH_6			FIELD32(0x00000040)
#define GPIO_SWITCH_7			FIELD32(0x00000080)

/*
                                               
 */
#define MAC_DEBUG_INDEX			0x05e8
#define MAC_DEBUG_INDEX_XTAL		FIELD32(0x80000000)

/*
                                     
                                                      
 */

/*
                                  
              
                         
 */
#define MAC_CSR0			0x1000
#define MAC_CSR0_REVISION		FIELD32(0x0000ffff)
#define MAC_CSR0_CHIPSET		FIELD32(0xffff0000)

/*
                
 */
#define MAC_SYS_CTRL			0x1004
#define MAC_SYS_CTRL_RESET_CSR		FIELD32(0x00000001)
#define MAC_SYS_CTRL_RESET_BBP		FIELD32(0x00000002)
#define MAC_SYS_CTRL_ENABLE_TX		FIELD32(0x00000004)
#define MAC_SYS_CTRL_ENABLE_RX		FIELD32(0x00000008)
#define MAC_SYS_CTRL_CONTINUOUS_TX	FIELD32(0x00000010)
#define MAC_SYS_CTRL_LOOPBACK		FIELD32(0x00000020)
#define MAC_SYS_CTRL_WLAN_HALT		FIELD32(0x00000040)
#define MAC_SYS_CTRL_RX_TIMESTAMP	FIELD32(0x00000080)

/*
                                   
 */
#define MAC_ADDR_DW0			0x1008
#define MAC_ADDR_DW0_BYTE0		FIELD32(0x000000ff)
#define MAC_ADDR_DW0_BYTE1		FIELD32(0x0000ff00)
#define MAC_ADDR_DW0_BYTE2		FIELD32(0x00ff0000)
#define MAC_ADDR_DW0_BYTE3		FIELD32(0xff000000)

/*
                                   
                      
                                                       
                                                    
                                                
                                             
 */
#define MAC_ADDR_DW1			0x100c
#define MAC_ADDR_DW1_BYTE4		FIELD32(0x000000ff)
#define MAC_ADDR_DW1_BYTE5		FIELD32(0x0000ff00)
#define MAC_ADDR_DW1_UNICAST_TO_ME_MASK	FIELD32(0x00ff0000)

/*
                                  
 */
#define MAC_BSSID_DW0			0x1010
#define MAC_BSSID_DW0_BYTE0		FIELD32(0x000000ff)
#define MAC_BSSID_DW0_BYTE1		FIELD32(0x0000ff00)
#define MAC_BSSID_DW0_BYTE2		FIELD32(0x00ff0000)
#define MAC_BSSID_DW0_BYTE3		FIELD32(0xff000000)

/*
                                  
               
                                      
                                                
                                                    
                                                    
                                                                 
                                                             
                                            
 */
#define MAC_BSSID_DW1			0x1014
#define MAC_BSSID_DW1_BYTE4		FIELD32(0x000000ff)
#define MAC_BSSID_DW1_BYTE5		FIELD32(0x0000ff00)
#define MAC_BSSID_DW1_BSS_ID_MASK	FIELD32(0x00030000)
#define MAC_BSSID_DW1_BSS_BCN_NUM	FIELD32(0x001c0000)

/*
                                              
                                  
                                
                                                
 */
#define MAX_LEN_CFG			0x1018
#define MAX_LEN_CFG_MAX_MPDU		FIELD32(0x00000fff)
#define MAX_LEN_CFG_MAX_PSDU		FIELD32(0x00003000)
#define MAX_LEN_CFG_MIN_PSDU		FIELD32(0x0000c000)
#define MAX_LEN_CFG_MIN_MPDU		FIELD32(0x000f0000)

/*
                                           
                                            
                                 
                                        
                                            
                                              
                                    
 */
#define BBP_CSR_CFG			0x101c
#define BBP_CSR_CFG_VALUE		FIELD32(0x000000ff)
#define BBP_CSR_CFG_REGNUM		FIELD32(0x0000ff00)
#define BBP_CSR_CFG_READ_CONTROL	FIELD32(0x00010000)
#define BBP_CSR_CFG_BUSY		FIELD32(0x00020000)
#define BBP_CSR_CFG_BBP_PAR_DUR		FIELD32(0x00040000)
#define BBP_CSR_CFG_BBP_RW_MODE		FIELD32(0x00080000)

/*
                                   
                                                     
                                 
                                                       
                                            
                                           
 */
#define RF_CSR_CFG0			0x1020
#define RF_CSR_CFG0_REGID_AND_VALUE	FIELD32(0x00ffffff)
#define RF_CSR_CFG0_BITWIDTH		FIELD32(0x1f000000)
#define RF_CSR_CFG0_REG_VALUE_BW	FIELD32(0x1fffffff)
#define RF_CSR_CFG0_STANDBYMODE		FIELD32(0x20000000)
#define RF_CSR_CFG0_SEL			FIELD32(0x40000000)
#define RF_CSR_CFG0_BUSY		FIELD32(0x80000000)

/*
                                   
                                                     
                                             
                                            
                                            
 */
#define RF_CSR_CFG1			0x1024
#define RF_CSR_CFG1_REGID_AND_VALUE	FIELD32(0x00ffffff)
#define RF_CSR_CFG1_RFGAP		FIELD32(0x1f000000)

/*
                                   
                                           
 */
#define RF_CSR_CFG2			0x1028
#define RF_CSR_CFG2_VALUE		FIELD32(0x00ffffff)

/*
                       
                                                                       
                                                                          
                                                                              
               
           
                         
                              
                 
                
                  
                   
 */
#define LED_CFG				0x102c
#define LED_CFG_ON_PERIOD		FIELD32(0x000000ff)
#define LED_CFG_OFF_PERIOD		FIELD32(0x0000ff00)
#define LED_CFG_SLOW_BLINK_PERIOD	FIELD32(0x003f0000)
#define LED_CFG_R_LED_MODE		FIELD32(0x03000000)
#define LED_CFG_G_LED_MODE		FIELD32(0x0c000000)
#define LED_CFG_Y_LED_MODE		FIELD32(0x30000000)
#define LED_CFG_LED_POLAR		FIELD32(0x40000000)

/*
                                               
                        
                                               
                                                                          
                                      
                                      
 */
#define AMPDU_BA_WINSIZE		0x1040
#define AMPDU_BA_WINSIZE_FORCE_WINSIZE_ENABLE FIELD32(0x00000020)
#define AMPDU_BA_WINSIZE_FORCE_WINSIZE	FIELD32(0x0000001f)

/*
                            
                                                    
                                                     
                                                  
                                                
                 
                                                              
  
 */
#define XIFS_TIME_CFG			0x1100
#define XIFS_TIME_CFG_CCKM_SIFS_TIME	FIELD32(0x000000ff)
#define XIFS_TIME_CFG_OFDM_SIFS_TIME	FIELD32(0x0000ff00)
#define XIFS_TIME_CFG_OFDM_XIFS_TIME	FIELD32(0x000f0000)
#define XIFS_TIME_CFG_EIFS		FIELD32(0x1ff00000)
#define XIFS_TIME_CFG_BB_RXEND_ENABLE	FIELD32(0x20000000)

/*
                  
 */
#define BKOFF_SLOT_CFG			0x1104
#define BKOFF_SLOT_CFG_SLOT_TIME	FIELD32(0x000000ff)
#define BKOFF_SLOT_CFG_CC_DELAY_TIME	FIELD32(0x0000ff00)

/*
                
 */
#define NAV_TIME_CFG			0x1108
#define NAV_TIME_CFG_SIFS		FIELD32(0x000000ff)
#define NAV_TIME_CFG_SLOT_TIME		FIELD32(0x0000ff00)
#define NAV_TIME_CFG_EIFS		FIELD32(0x01ff0000)
#define NAV_TIME_ZERO_SIFS		FIELD32(0x02000000)

/*
                                     
                                        
                                      
                                    
                                    
                                          
 */
#define CH_TIME_CFG     	        0x110c
#define CH_TIME_CFG_EIFS_BUSY		FIELD32(0x00000010)
#define CH_TIME_CFG_NAV_BUSY		FIELD32(0x00000008)
#define CH_TIME_CFG_RX_BUSY		FIELD32(0x00000004)
#define CH_TIME_CFG_TX_BUSY		FIELD32(0x00000002)
#define CH_TIME_CFG_TMR_EN		FIELD32(0x00000001)

/*
                                                                  
 */
#define PBF_LIFE_TIMER     	        0x1110

/*
                
                                      
                                        
                                                                          
                                      
 */
#define BCN_TIME_CFG			0x1114
#define BCN_TIME_CFG_BEACON_INTERVAL	FIELD32(0x0000ffff)
#define BCN_TIME_CFG_TSF_TICKING	FIELD32(0x00010000)
#define BCN_TIME_CFG_TSF_SYNC		FIELD32(0x00060000)
#define BCN_TIME_CFG_TBTT_ENABLE	FIELD32(0x00080000)
#define BCN_TIME_CFG_BEACON_GEN		FIELD32(0x00100000)
#define BCN_TIME_CFG_TX_TIME_COMPENSATE	FIELD32(0xf0000000)

/*
                 
                                                        
                                                        
 */
#define TBTT_SYNC_CFG			0x1118
#define TBTT_SYNC_CFG_TBTT_ADJUST	FIELD32(0x000000ff)
#define TBTT_SYNC_CFG_BCN_EXP_WIN	FIELD32(0x0000ff00)
#define TBTT_SYNC_CFG_BCN_AIFSN		FIELD32(0x000f0000)
#define TBTT_SYNC_CFG_BCN_CWMIN		FIELD32(0x00f00000)

/*
                                                
 */
#define TSF_TIMER_DW0			0x111c
#define TSF_TIMER_DW0_LOW_WORD		FIELD32(0xffffffff)

/*
                                                
 */
#define TSF_TIMER_DW1			0x1120
#define TSF_TIMER_DW1_HIGH_WORD		FIELD32(0xffffffff)

/*
                                                      
 */
#define TBTT_TIMER			0x1124

/*
                                     
                                                                             
                                                                
 */
#define INT_TIMER_CFG			0x1128
#define INT_TIMER_CFG_PRE_TBTT_TIMER	FIELD32(0x0000ffff)
#define INT_TIMER_CFG_GP_TIMER		FIELD32(0xffff0000)

/*
                                                 
 */
#define INT_TIMER_EN			0x112c
#define INT_TIMER_EN_PRE_TBTT_TIMER	FIELD32(0x00000001)
#define INT_TIMER_EN_GP_TIMER		FIELD32(0x00000002)

/*
                                         
 */
#define CH_IDLE_STA			0x1130

/*
                                                            
 */
#define CH_BUSY_STA			0x1134

/*
                                                                               
 */
#define CH_BUSY_STA_SEC			0x1138

/*
                  
                                                     
                                                 
 */
#define MAC_STATUS_CFG			0x1200
#define MAC_STATUS_CFG_BBP_RF_BUSY	FIELD32(0x00000003)

/*
               
 */
#define PWR_PIN_CFG			0x1204

/*
                                                         
                                                                               
                             
 */
#define AUTOWAKEUP_CFG			0x1208
#define AUTOWAKEUP_CFG_AUTO_LEAD_TIME	FIELD32(0x000000ff)
#define AUTOWAKEUP_CFG_TBCN_BEFORE_WAKE	FIELD32(0x00007f00)
#define AUTOWAKEUP_CFG_AUTOWAKE		FIELD32(0x00008000)

/*
                
 */
#define EDCA_AC0_CFG			0x1300
#define EDCA_AC0_CFG_TX_OP		FIELD32(0x000000ff)
#define EDCA_AC0_CFG_AIFSN		FIELD32(0x00000f00)
#define EDCA_AC0_CFG_CWMIN		FIELD32(0x0000f000)
#define EDCA_AC0_CFG_CWMAX		FIELD32(0x000f0000)

/*
                
 */
#define EDCA_AC1_CFG			0x1304
#define EDCA_AC1_CFG_TX_OP		FIELD32(0x000000ff)
#define EDCA_AC1_CFG_AIFSN		FIELD32(0x00000f00)
#define EDCA_AC1_CFG_CWMIN		FIELD32(0x0000f000)
#define EDCA_AC1_CFG_CWMAX		FIELD32(0x000f0000)

/*
                
 */
#define EDCA_AC2_CFG			0x1308
#define EDCA_AC2_CFG_TX_OP		FIELD32(0x000000ff)
#define EDCA_AC2_CFG_AIFSN		FIELD32(0x00000f00)
#define EDCA_AC2_CFG_CWMIN		FIELD32(0x0000f000)
#define EDCA_AC2_CFG_CWMAX		FIELD32(0x000f0000)

/*
                
 */
#define EDCA_AC3_CFG			0x130c
#define EDCA_AC3_CFG_TX_OP		FIELD32(0x000000ff)
#define EDCA_AC3_CFG_AIFSN		FIELD32(0x00000f00)
#define EDCA_AC3_CFG_CWMIN		FIELD32(0x0000f000)
#define EDCA_AC3_CFG_CWMAX		FIELD32(0x000f0000)

/*
                   
 */
#define EDCA_TID_AC_MAP			0x1310

/*
              
 */
#define TX_PWR_CFG_RATE0		FIELD32(0x0000000f)
#define TX_PWR_CFG_RATE1		FIELD32(0x000000f0)
#define TX_PWR_CFG_RATE2		FIELD32(0x00000f00)
#define TX_PWR_CFG_RATE3		FIELD32(0x0000f000)
#define TX_PWR_CFG_RATE4		FIELD32(0x000f0000)
#define TX_PWR_CFG_RATE5		FIELD32(0x00f00000)
#define TX_PWR_CFG_RATE6		FIELD32(0x0f000000)
#define TX_PWR_CFG_RATE7		FIELD32(0xf0000000)

/*
                
 */
#define TX_PWR_CFG_0			0x1314
#define TX_PWR_CFG_0_1MBS		FIELD32(0x0000000f)
#define TX_PWR_CFG_0_2MBS		FIELD32(0x000000f0)
#define TX_PWR_CFG_0_55MBS		FIELD32(0x00000f00)
#define TX_PWR_CFG_0_11MBS		FIELD32(0x0000f000)
#define TX_PWR_CFG_0_6MBS		FIELD32(0x000f0000)
#define TX_PWR_CFG_0_9MBS		FIELD32(0x00f00000)
#define TX_PWR_CFG_0_12MBS		FIELD32(0x0f000000)
#define TX_PWR_CFG_0_18MBS		FIELD32(0xf0000000)

/*
                
 */
#define TX_PWR_CFG_1			0x1318
#define TX_PWR_CFG_1_24MBS		FIELD32(0x0000000f)
#define TX_PWR_CFG_1_36MBS		FIELD32(0x000000f0)
#define TX_PWR_CFG_1_48MBS		FIELD32(0x00000f00)
#define TX_PWR_CFG_1_54MBS		FIELD32(0x0000f000)
#define TX_PWR_CFG_1_MCS0		FIELD32(0x000f0000)
#define TX_PWR_CFG_1_MCS1		FIELD32(0x00f00000)
#define TX_PWR_CFG_1_MCS2		FIELD32(0x0f000000)
#define TX_PWR_CFG_1_MCS3		FIELD32(0xf0000000)

/*
                
 */
#define TX_PWR_CFG_2			0x131c
#define TX_PWR_CFG_2_MCS4		FIELD32(0x0000000f)
#define TX_PWR_CFG_2_MCS5		FIELD32(0x000000f0)
#define TX_PWR_CFG_2_MCS6		FIELD32(0x00000f00)
#define TX_PWR_CFG_2_MCS7		FIELD32(0x0000f000)
#define TX_PWR_CFG_2_MCS8		FIELD32(0x000f0000)
#define TX_PWR_CFG_2_MCS9		FIELD32(0x00f00000)
#define TX_PWR_CFG_2_MCS10		FIELD32(0x0f000000)
#define TX_PWR_CFG_2_MCS11		FIELD32(0xf0000000)

/*
                
 */
#define TX_PWR_CFG_3			0x1320
#define TX_PWR_CFG_3_MCS12		FIELD32(0x0000000f)
#define TX_PWR_CFG_3_MCS13		FIELD32(0x000000f0)
#define TX_PWR_CFG_3_MCS14		FIELD32(0x00000f00)
#define TX_PWR_CFG_3_MCS15		FIELD32(0x0000f000)
#define TX_PWR_CFG_3_UKNOWN1		FIELD32(0x000f0000)
#define TX_PWR_CFG_3_UKNOWN2		FIELD32(0x00f00000)
#define TX_PWR_CFG_3_UKNOWN3		FIELD32(0x0f000000)
#define TX_PWR_CFG_3_UKNOWN4		FIELD32(0xf0000000)

/*
                
 */
#define TX_PWR_CFG_4			0x1324
#define TX_PWR_CFG_4_UKNOWN5		FIELD32(0x0000000f)
#define TX_PWR_CFG_4_UKNOWN6		FIELD32(0x000000f0)
#define TX_PWR_CFG_4_UKNOWN7		FIELD32(0x00000f00)
#define TX_PWR_CFG_4_UKNOWN8		FIELD32(0x0000f000)

/*
              
 */
#define TX_PIN_CFG			0x1328
#define TX_PIN_CFG_PA_PE_DISABLE	0xfcfffff0
#define TX_PIN_CFG_PA_PE_A0_EN		FIELD32(0x00000001)
#define TX_PIN_CFG_PA_PE_G0_EN		FIELD32(0x00000002)
#define TX_PIN_CFG_PA_PE_A1_EN		FIELD32(0x00000004)
#define TX_PIN_CFG_PA_PE_G1_EN		FIELD32(0x00000008)
#define TX_PIN_CFG_PA_PE_A0_POL		FIELD32(0x00000010)
#define TX_PIN_CFG_PA_PE_G0_POL		FIELD32(0x00000020)
#define TX_PIN_CFG_PA_PE_A1_POL		FIELD32(0x00000040)
#define TX_PIN_CFG_PA_PE_G1_POL		FIELD32(0x00000080)
#define TX_PIN_CFG_LNA_PE_A0_EN		FIELD32(0x00000100)
#define TX_PIN_CFG_LNA_PE_G0_EN		FIELD32(0x00000200)
#define TX_PIN_CFG_LNA_PE_A1_EN		FIELD32(0x00000400)
#define TX_PIN_CFG_LNA_PE_G1_EN		FIELD32(0x00000800)
#define TX_PIN_CFG_LNA_PE_A0_POL	FIELD32(0x00001000)
#define TX_PIN_CFG_LNA_PE_G0_POL	FIELD32(0x00002000)
#define TX_PIN_CFG_LNA_PE_A1_POL	FIELD32(0x00004000)
#define TX_PIN_CFG_LNA_PE_G1_POL	FIELD32(0x00008000)
#define TX_PIN_CFG_RFTR_EN		FIELD32(0x00010000)
#define TX_PIN_CFG_RFTR_POL		FIELD32(0x00020000)
#define TX_PIN_CFG_TRSW_EN		FIELD32(0x00040000)
#define TX_PIN_CFG_TRSW_POL		FIELD32(0x00080000)
#define TX_PIN_CFG_PA_PE_A2_EN		FIELD32(0x01000000)
#define TX_PIN_CFG_PA_PE_G2_EN		FIELD32(0x02000000)
#define TX_PIN_CFG_PA_PE_A2_POL		FIELD32(0x04000000)
#define TX_PIN_CFG_PA_PE_G2_POL		FIELD32(0x08000000)
#define TX_PIN_CFG_LNA_PE_A2_EN		FIELD32(0x10000000)
#define TX_PIN_CFG_LNA_PE_G2_EN		FIELD32(0x20000000)
#define TX_PIN_CFG_LNA_PE_A2_POL	FIELD32(0x40000000)
#define TX_PIN_CFG_LNA_PE_G2_POL	FIELD32(0x80000000)

/*
                                                        
 */
#define TX_BAND_CFG			0x132c
#define TX_BAND_CFG_HT40_MINUS		FIELD32(0x00000001)
#define TX_BAND_CFG_A			FIELD32(0x00000002)
#define TX_BAND_CFG_BG			FIELD32(0x00000004)

/*
              
 */
#define TX_SW_CFG0			0x1330

/*
              
 */
#define TX_SW_CFG1			0x1334

/*
              
 */
#define TX_SW_CFG2			0x1338

/*
                  
 */
#define TXOP_THRES_CFG			0x133c

/*
                 
                                                          
                                                      
                                                                        
                                                                  
                                                                 
                             
                                                     
                                                                          
                                                   
                                                          
                                                 
                    
  
 */
#define TXOP_CTRL_CFG			0x1340
#define TXOP_CTRL_CFG_TIMEOUT_TRUN_EN	FIELD32(0x00000001)
#define TXOP_CTRL_CFG_AC_TRUN_EN	FIELD32(0x00000002)
#define TXOP_CTRL_CFG_TXRATEGRP_TRUN_EN	FIELD32(0x00000004)
#define TXOP_CTRL_CFG_USER_MODE_TRUN_EN	FIELD32(0x00000008)
#define TXOP_CTRL_CFG_MIMO_PS_TRUN_EN	FIELD32(0x00000010)
#define TXOP_CTRL_CFG_RESERVED_TRUN_EN	FIELD32(0x00000020)
#define TXOP_CTRL_CFG_LSIG_TXOP_EN	FIELD32(0x00000040)
#define TXOP_CTRL_CFG_EXT_CCA_EN	FIELD32(0x00000080)
#define TXOP_CTRL_CFG_EXT_CCA_DLY	FIELD32(0x0000ff00)
#define TXOP_CTRL_CFG_EXT_CWMIN		FIELD32(0x000f0000)

/*
              
                       
                                       
 */
#define TX_RTS_CFG			0x1344
#define TX_RTS_CFG_AUTO_RTS_RETRY_LIMIT	FIELD32(0x000000ff)
#define TX_RTS_CFG_RTS_THRES		FIELD32(0x00ffff00)
#define TX_RTS_CFG_RTS_FBK_EN		FIELD32(0x01000000)

/*
                  
                                                           
                                                   
                                                         
                                         
                                                                  
 */
#define TX_TIMEOUT_CFG			0x1348
#define TX_TIMEOUT_CFG_MPDU_LIFETIME	FIELD32(0x000000f0)
#define TX_TIMEOUT_CFG_RX_ACK_TIMEOUT	FIELD32(0x0000ff00)
#define TX_TIMEOUT_CFG_TX_OP_TIMEOUT	FIELD32(0x00ff0000)

/*
              
                                     
                                   
                                       
                                                  
                                                                            
                                          
                                                                        
                                                            
 */
#define TX_RTY_CFG			0x134c
#define TX_RTY_CFG_SHORT_RTY_LIMIT	FIELD32(0x000000ff)
#define TX_RTY_CFG_LONG_RTY_LIMIT	FIELD32(0x0000ff00)
#define TX_RTY_CFG_LONG_RTY_THRE	FIELD32(0x0fff0000)
#define TX_RTY_CFG_NON_AGG_RTY_MODE	FIELD32(0x10000000)
#define TX_RTY_CFG_AGG_RTY_MODE		FIELD32(0x20000000)
#define TX_RTY_CFG_TX_AUTO_FB_ENABLE	FIELD32(0x40000000)

/*
               
                                                        
                                           
                                                   
                                                                   
                                   
                           
                                        
                                  
                                                  
 */
#define TX_LINK_CFG			0x1350
#define TX_LINK_CFG_REMOTE_MFB_LIFETIME	FIELD32(0x000000ff)
#define TX_LINK_CFG_MFB_ENABLE		FIELD32(0x00000100)
#define TX_LINK_CFG_REMOTE_UMFS_ENABLE	FIELD32(0x00000200)
#define TX_LINK_CFG_TX_MRQ_EN		FIELD32(0x00000400)
#define TX_LINK_CFG_TX_RDG_EN		FIELD32(0x00000800)
#define TX_LINK_CFG_TX_CF_ACK_EN	FIELD32(0x00001000)
#define TX_LINK_CFG_REMOTE_MFB		FIELD32(0x00ff0000)
#define TX_LINK_CFG_REMOTE_MFS		FIELD32(0xff000000)

/*
               
 */
#define HT_FBK_CFG0			0x1354
#define HT_FBK_CFG0_HTMCS0FBK		FIELD32(0x0000000f)
#define HT_FBK_CFG0_HTMCS1FBK		FIELD32(0x000000f0)
#define HT_FBK_CFG0_HTMCS2FBK		FIELD32(0x00000f00)
#define HT_FBK_CFG0_HTMCS3FBK		FIELD32(0x0000f000)
#define HT_FBK_CFG0_HTMCS4FBK		FIELD32(0x000f0000)
#define HT_FBK_CFG0_HTMCS5FBK		FIELD32(0x00f00000)
#define HT_FBK_CFG0_HTMCS6FBK		FIELD32(0x0f000000)
#define HT_FBK_CFG0_HTMCS7FBK		FIELD32(0xf0000000)

/*
               
 */
#define HT_FBK_CFG1			0x1358
#define HT_FBK_CFG1_HTMCS8FBK		FIELD32(0x0000000f)
#define HT_FBK_CFG1_HTMCS9FBK		FIELD32(0x000000f0)
#define HT_FBK_CFG1_HTMCS10FBK		FIELD32(0x00000f00)
#define HT_FBK_CFG1_HTMCS11FBK		FIELD32(0x0000f000)
#define HT_FBK_CFG1_HTMCS12FBK		FIELD32(0x000f0000)
#define HT_FBK_CFG1_HTMCS13FBK		FIELD32(0x00f00000)
#define HT_FBK_CFG1_HTMCS14FBK		FIELD32(0x0f000000)
#define HT_FBK_CFG1_HTMCS15FBK		FIELD32(0xf0000000)

/*
               
 */
#define LG_FBK_CFG0			0x135c
#define LG_FBK_CFG0_OFDMMCS0FBK		FIELD32(0x0000000f)
#define LG_FBK_CFG0_OFDMMCS1FBK		FIELD32(0x000000f0)
#define LG_FBK_CFG0_OFDMMCS2FBK		FIELD32(0x00000f00)
#define LG_FBK_CFG0_OFDMMCS3FBK		FIELD32(0x0000f000)
#define LG_FBK_CFG0_OFDMMCS4FBK		FIELD32(0x000f0000)
#define LG_FBK_CFG0_OFDMMCS5FBK		FIELD32(0x00f00000)
#define LG_FBK_CFG0_OFDMMCS6FBK		FIELD32(0x0f000000)
#define LG_FBK_CFG0_OFDMMCS7FBK		FIELD32(0xf0000000)

/*
               
 */
#define LG_FBK_CFG1			0x1360
#define LG_FBK_CFG0_CCKMCS0FBK		FIELD32(0x0000000f)
#define LG_FBK_CFG0_CCKMCS1FBK		FIELD32(0x000000f0)
#define LG_FBK_CFG0_CCKMCS2FBK		FIELD32(0x00000f00)
#define LG_FBK_CFG0_CCKMCS3FBK		FIELD32(0x0000f000)

/*
                               
                                                                        
                                                         
                                                 
                                                                    
                                                                  
                                                  
                                                   
                                                   
                                                   
                                                   
                                                   
                                            
 */
#define CCK_PROT_CFG			0x1364
#define CCK_PROT_CFG_PROTECT_RATE	FIELD32(0x0000ffff)
#define CCK_PROT_CFG_PROTECT_CTRL	FIELD32(0x00030000)
#define CCK_PROT_CFG_PROTECT_NAV_SHORT	FIELD32(0x00040000)
#define CCK_PROT_CFG_PROTECT_NAV_LONG	FIELD32(0x00080000)
#define CCK_PROT_CFG_TX_OP_ALLOW_CCK	FIELD32(0x00100000)
#define CCK_PROT_CFG_TX_OP_ALLOW_OFDM	FIELD32(0x00200000)
#define CCK_PROT_CFG_TX_OP_ALLOW_MM20	FIELD32(0x00400000)
#define CCK_PROT_CFG_TX_OP_ALLOW_MM40	FIELD32(0x00800000)
#define CCK_PROT_CFG_TX_OP_ALLOW_GF20	FIELD32(0x01000000)
#define CCK_PROT_CFG_TX_OP_ALLOW_GF40	FIELD32(0x02000000)
#define CCK_PROT_CFG_RTS_TH_EN		FIELD32(0x04000000)

/*
                                 
 */
#define OFDM_PROT_CFG			0x1368
#define OFDM_PROT_CFG_PROTECT_RATE	FIELD32(0x0000ffff)
#define OFDM_PROT_CFG_PROTECT_CTRL	FIELD32(0x00030000)
#define OFDM_PROT_CFG_PROTECT_NAV_SHORT	FIELD32(0x00040000)
#define OFDM_PROT_CFG_PROTECT_NAV_LONG	FIELD32(0x00080000)
#define OFDM_PROT_CFG_TX_OP_ALLOW_CCK	FIELD32(0x00100000)
#define OFDM_PROT_CFG_TX_OP_ALLOW_OFDM	FIELD32(0x00200000)
#define OFDM_PROT_CFG_TX_OP_ALLOW_MM20	FIELD32(0x00400000)
#define OFDM_PROT_CFG_TX_OP_ALLOW_MM40	FIELD32(0x00800000)
#define OFDM_PROT_CFG_TX_OP_ALLOW_GF20	FIELD32(0x01000000)
#define OFDM_PROT_CFG_TX_OP_ALLOW_GF40	FIELD32(0x02000000)
#define OFDM_PROT_CFG_RTS_TH_EN		FIELD32(0x04000000)

/*
                                 
 */
#define MM20_PROT_CFG			0x136c
#define MM20_PROT_CFG_PROTECT_RATE	FIELD32(0x0000ffff)
#define MM20_PROT_CFG_PROTECT_CTRL	FIELD32(0x00030000)
#define MM20_PROT_CFG_PROTECT_NAV_SHORT	FIELD32(0x00040000)
#define MM20_PROT_CFG_PROTECT_NAV_LONG	FIELD32(0x00080000)
#define MM20_PROT_CFG_TX_OP_ALLOW_CCK	FIELD32(0x00100000)
#define MM20_PROT_CFG_TX_OP_ALLOW_OFDM	FIELD32(0x00200000)
#define MM20_PROT_CFG_TX_OP_ALLOW_MM20	FIELD32(0x00400000)
#define MM20_PROT_CFG_TX_OP_ALLOW_MM40	FIELD32(0x00800000)
#define MM20_PROT_CFG_TX_OP_ALLOW_GF20	FIELD32(0x01000000)
#define MM20_PROT_CFG_TX_OP_ALLOW_GF40	FIELD32(0x02000000)
#define MM20_PROT_CFG_RTS_TH_EN		FIELD32(0x04000000)

/*
                                 
 */
#define MM40_PROT_CFG			0x1370
#define MM40_PROT_CFG_PROTECT_RATE	FIELD32(0x0000ffff)
#define MM40_PROT_CFG_PROTECT_CTRL	FIELD32(0x00030000)
#define MM40_PROT_CFG_PROTECT_NAV_SHORT	FIELD32(0x00040000)
#define MM40_PROT_CFG_PROTECT_NAV_LONG	FIELD32(0x00080000)
#define MM40_PROT_CFG_TX_OP_ALLOW_CCK	FIELD32(0x00100000)
#define MM40_PROT_CFG_TX_OP_ALLOW_OFDM	FIELD32(0x00200000)
#define MM40_PROT_CFG_TX_OP_ALLOW_MM20	FIELD32(0x00400000)
#define MM40_PROT_CFG_TX_OP_ALLOW_MM40	FIELD32(0x00800000)
#define MM40_PROT_CFG_TX_OP_ALLOW_GF20	FIELD32(0x01000000)
#define MM40_PROT_CFG_TX_OP_ALLOW_GF40	FIELD32(0x02000000)
#define MM40_PROT_CFG_RTS_TH_EN		FIELD32(0x04000000)

/*
                                 
 */
#define GF20_PROT_CFG			0x1374
#define GF20_PROT_CFG_PROTECT_RATE	FIELD32(0x0000ffff)
#define GF20_PROT_CFG_PROTECT_CTRL	FIELD32(0x00030000)
#define GF20_PROT_CFG_PROTECT_NAV_SHORT	FIELD32(0x00040000)
#define GF20_PROT_CFG_PROTECT_NAV_LONG	FIELD32(0x00080000)
#define GF20_PROT_CFG_TX_OP_ALLOW_CCK	FIELD32(0x00100000)
#define GF20_PROT_CFG_TX_OP_ALLOW_OFDM	FIELD32(0x00200000)
#define GF20_PROT_CFG_TX_OP_ALLOW_MM20	FIELD32(0x00400000)
#define GF20_PROT_CFG_TX_OP_ALLOW_MM40	FIELD32(0x00800000)
#define GF20_PROT_CFG_TX_OP_ALLOW_GF20	FIELD32(0x01000000)
#define GF20_PROT_CFG_TX_OP_ALLOW_GF40	FIELD32(0x02000000)
#define GF20_PROT_CFG_RTS_TH_EN		FIELD32(0x04000000)

/*
                                 
 */
#define GF40_PROT_CFG			0x1378
#define GF40_PROT_CFG_PROTECT_RATE	FIELD32(0x0000ffff)
#define GF40_PROT_CFG_PROTECT_CTRL	FIELD32(0x00030000)
#define GF40_PROT_CFG_PROTECT_NAV_SHORT	FIELD32(0x00040000)
#define GF40_PROT_CFG_PROTECT_NAV_LONG	FIELD32(0x00080000)
#define GF40_PROT_CFG_TX_OP_ALLOW_CCK	FIELD32(0x00100000)
#define GF40_PROT_CFG_TX_OP_ALLOW_OFDM	FIELD32(0x00200000)
#define GF40_PROT_CFG_TX_OP_ALLOW_MM20	FIELD32(0x00400000)
#define GF40_PROT_CFG_TX_OP_ALLOW_MM40	FIELD32(0x00800000)
#define GF40_PROT_CFG_TX_OP_ALLOW_GF20	FIELD32(0x01000000)
#define GF40_PROT_CFG_TX_OP_ALLOW_GF40	FIELD32(0x02000000)
#define GF40_PROT_CFG_RTS_TH_EN		FIELD32(0x04000000)

/*
                
 */
#define EXP_CTS_TIME			0x137c

/*
                
 */
#define EXP_ACK_TIME			0x1380

/*
                                            
 */
#define RX_FILTER_CFG			0x1400
#define RX_FILTER_CFG_DROP_CRC_ERROR	FIELD32(0x00000001)
#define RX_FILTER_CFG_DROP_PHY_ERROR	FIELD32(0x00000002)
#define RX_FILTER_CFG_DROP_NOT_TO_ME	FIELD32(0x00000004)
#define RX_FILTER_CFG_DROP_NOT_MY_BSSD	FIELD32(0x00000008)
#define RX_FILTER_CFG_DROP_VER_ERROR	FIELD32(0x00000010)
#define RX_FILTER_CFG_DROP_MULTICAST	FIELD32(0x00000020)
#define RX_FILTER_CFG_DROP_BROADCAST	FIELD32(0x00000040)
#define RX_FILTER_CFG_DROP_DUPLICATE	FIELD32(0x00000080)
#define RX_FILTER_CFG_DROP_CF_END_ACK	FIELD32(0x00000100)
#define RX_FILTER_CFG_DROP_CF_END	FIELD32(0x00000200)
#define RX_FILTER_CFG_DROP_ACK		FIELD32(0x00000400)
#define RX_FILTER_CFG_DROP_CTS		FIELD32(0x00000800)
#define RX_FILTER_CFG_DROP_RTS		FIELD32(0x00001000)
#define RX_FILTER_CFG_DROP_PSPOLL	FIELD32(0x00002000)
#define RX_FILTER_CFG_DROP_BA		FIELD32(0x00004000)
#define RX_FILTER_CFG_DROP_BAR		FIELD32(0x00008000)
#define RX_FILTER_CFG_DROP_CNTL		FIELD32(0x00010000)

/*
                
                                       
                                           
                                                  
                                                 
                                                                
                                                
                                                   
 */
#define AUTO_RSP_CFG			0x1404
#define AUTO_RSP_CFG_AUTORESPONDER	FIELD32(0x00000001)
#define AUTO_RSP_CFG_BAC_ACK_POLICY	FIELD32(0x00000002)
#define AUTO_RSP_CFG_CTS_40_MMODE	FIELD32(0x00000004)
#define AUTO_RSP_CFG_CTS_40_MREF	FIELD32(0x00000008)
#define AUTO_RSP_CFG_AR_PREAMBLE	FIELD32(0x00000010)
#define AUTO_RSP_CFG_DUAL_CTS_EN	FIELD32(0x00000040)
#define AUTO_RSP_CFG_ACK_CTS_PSM_BIT	FIELD32(0x00000080)

/*
                     
 */
#define LEGACY_BASIC_RATE		0x1408

/*
                 
 */
#define HT_BASIC_RATE			0x140c

/*
               
 */
#define HT_CTRL_CFG			0x1410

/*
                 
 */
#define SIFS_COST_CFG			0x1414

/*
                 
                                  
 */
#define RX_PARSER_CFG			0x1418

/*
               
 */
#define TX_SEC_CNT0			0x1500

/*
               
 */
#define RX_SEC_CNT0			0x1504

/*
                
 */
#define CCMP_FC_MUTE			0x1508

/*
                   
 */
#define TXOP_HLDR_ADDR0			0x1600

/*
                   
 */
#define TXOP_HLDR_ADDR1			0x1604

/*
                
 */
#define TXOP_HLDR_ET			0x1608

/*
                     
 */
#define QOS_CFPOLL_RA_DW0		0x160c

/*
                     
 */
#define QOS_CFPOLL_RA_DW1		0x1610

/*
                 
 */
#define QOS_CFPOLL_QC			0x1614

/*
                                                        
 */
#define RX_STA_CNT0			0x1700
#define RX_STA_CNT0_CRC_ERR		FIELD32(0x0000ffff)
#define RX_STA_CNT0_PHY_ERR		FIELD32(0xffff0000)

/*
                                                        
 */
#define RX_STA_CNT1			0x1704
#define RX_STA_CNT1_FALSE_CCA		FIELD32(0x0000ffff)
#define RX_STA_CNT1_PLCP_ERR		FIELD32(0xffff0000)

/*
               
 */
#define RX_STA_CNT2			0x1708
#define RX_STA_CNT2_RX_DUPLI_COUNT	FIELD32(0x0000ffff)
#define RX_STA_CNT2_RX_FIFO_OVERFLOW	FIELD32(0xffff0000)

/*
                               
 */
#define TX_STA_CNT0			0x170c
#define TX_STA_CNT0_TX_FAIL_COUNT	FIELD32(0x0000ffff)
#define TX_STA_CNT0_TX_BEACON_COUNT	FIELD32(0xffff0000)

/*
                           
 */
#define TX_STA_CNT1			0x1710
#define TX_STA_CNT1_TX_SUCCESS		FIELD32(0x0000ffff)
#define TX_STA_CNT1_TX_RETRANSMIT	FIELD32(0xffff0000)

/*
                           
 */
#define TX_STA_CNT2			0x1714
#define TX_STA_CNT2_TX_ZERO_LEN_COUNT	FIELD32(0x0000ffff)
#define TX_STA_CNT2_TX_UNDER_FLOW_COUNT	FIELD32(0xffff0000)

/*
                                                                
  
                                                                       
                                                                        
                                                                            
                                                             
  
                                    
                                                             
                                                                        
                                                                        
                               
                                                                    
                                                                          
                                                                          
                                                      
                                                                           
                                                                              
                                
                                                                          
                          
                                                  
 */
#define TX_STA_FIFO			0x1718
#define TX_STA_FIFO_VALID		FIELD32(0x00000001)
#define TX_STA_FIFO_PID_TYPE		FIELD32(0x0000001e)
#define TX_STA_FIFO_PID_QUEUE		FIELD32(0x00000006)
#define TX_STA_FIFO_PID_ENTRY		FIELD32(0x00000018)
#define TX_STA_FIFO_TX_SUCCESS		FIELD32(0x00000020)
#define TX_STA_FIFO_TX_AGGRE		FIELD32(0x00000040)
#define TX_STA_FIFO_TX_ACK_REQUIRED	FIELD32(0x00000080)
#define TX_STA_FIFO_WCID		FIELD32(0x0000ff00)
#define TX_STA_FIFO_SUCCESS_RATE	FIELD32(0xffff0000)
#define TX_STA_FIFO_MCS			FIELD32(0x007f0000)
#define TX_STA_FIFO_PHYMODE		FIELD32(0xc0000000)

/*
                            
 */
#define TX_AGG_CNT			0x171c
#define TX_AGG_CNT_NON_AGG_TX_COUNT	FIELD32(0x0000ffff)
#define TX_AGG_CNT_AGG_TX_COUNT		FIELD32(0xffff0000)

/*
               
 */
#define TX_AGG_CNT0			0x1720
#define TX_AGG_CNT0_AGG_SIZE_1_COUNT	FIELD32(0x0000ffff)
#define TX_AGG_CNT0_AGG_SIZE_2_COUNT	FIELD32(0xffff0000)

/*
               
 */
#define TX_AGG_CNT1			0x1724
#define TX_AGG_CNT1_AGG_SIZE_3_COUNT	FIELD32(0x0000ffff)
#define TX_AGG_CNT1_AGG_SIZE_4_COUNT	FIELD32(0xffff0000)

/*
               
 */
#define TX_AGG_CNT2			0x1728
#define TX_AGG_CNT2_AGG_SIZE_5_COUNT	FIELD32(0x0000ffff)
#define TX_AGG_CNT2_AGG_SIZE_6_COUNT	FIELD32(0xffff0000)

/*
               
 */
#define TX_AGG_CNT3			0x172c
#define TX_AGG_CNT3_AGG_SIZE_7_COUNT	FIELD32(0x0000ffff)
#define TX_AGG_CNT3_AGG_SIZE_8_COUNT	FIELD32(0xffff0000)

/*
               
 */
#define TX_AGG_CNT4			0x1730
#define TX_AGG_CNT4_AGG_SIZE_9_COUNT	FIELD32(0x0000ffff)
#define TX_AGG_CNT4_AGG_SIZE_10_COUNT	FIELD32(0xffff0000)

/*
               
 */
#define TX_AGG_CNT5			0x1734
#define TX_AGG_CNT5_AGG_SIZE_11_COUNT	FIELD32(0x0000ffff)
#define TX_AGG_CNT5_AGG_SIZE_12_COUNT	FIELD32(0xffff0000)

/*
               
 */
#define TX_AGG_CNT6			0x1738
#define TX_AGG_CNT6_AGG_SIZE_13_COUNT	FIELD32(0x0000ffff)
#define TX_AGG_CNT6_AGG_SIZE_14_COUNT	FIELD32(0xffff0000)

/*
               
 */
#define TX_AGG_CNT7			0x173c
#define TX_AGG_CNT7_AGG_SIZE_15_COUNT	FIELD32(0x0000ffff)
#define TX_AGG_CNT7_AGG_SIZE_16_COUNT	FIELD32(0xffff0000)

/*
                    
                                              
                                              
 */
#define MPDU_DENSITY_CNT		0x1740
#define MPDU_DENSITY_CNT_TX_ZERO_DEL	FIELD32(0x0000ffff)
#define MPDU_DENSITY_CNT_RX_ZERO_DEL	FIELD32(0xffff0000)

/*
                             
  
                                                                  
                                                               
                                                                   
                                
  
                                                
                                                
                                                
                                                
                                                
                                                
                                                
                                                
                                                
                             
                             
  
                                                        
                                               
                                           
                                              
                                            
                                          
 */
#define MAC_WCID_BASE			0x1800
#define PAIRWISE_KEY_TABLE_BASE		0x4000
#define MAC_IVEIV_TABLE_BASE		0x6000
#define MAC_WCID_ATTRIBUTE_BASE		0x6800
#define SHARED_KEY_TABLE_BASE		0x6c00
#define SHARED_KEY_MODE_BASE		0x7000

#define MAC_WCID_ENTRY(__idx) \
	(MAC_WCID_BASE + ((__idx) * sizeof(struct mac_wcid_entry)))
#define PAIRWISE_KEY_ENTRY(__idx) \
	(PAIRWISE_KEY_TABLE_BASE + ((__idx) * sizeof(struct hw_key_entry)))
#define MAC_IVEIV_ENTRY(__idx) \
	(MAC_IVEIV_TABLE_BASE + ((__idx) * sizeof(struct mac_iveiv_entry)))
#define MAC_WCID_ATTR_ENTRY(__idx) \
	(MAC_WCID_ATTRIBUTE_BASE + ((__idx) * sizeof(u32)))
#define SHARED_KEY_ENTRY(__idx) \
	(SHARED_KEY_TABLE_BASE + ((__idx) * sizeof(struct hw_key_entry)))
#define SHARED_KEY_MODE_ENTRY(__idx) \
	(SHARED_KEY_MODE_BASE + ((__idx) * sizeof(u32)))

struct mac_wcid_entry {
	u8 mac[6];
	u8 reserved[2];
} __packed;

struct hw_key_entry {
	u8 key[16];
	u8 tx_mic[8];
	u8 rx_mic[8];
} __packed;

struct mac_iveiv_entry {
	u8 iv[8];
} __packed;

/*
                      
 */
#define MAC_WCID_ATTRIBUTE_KEYTAB	FIELD32(0x00000001)
#define MAC_WCID_ATTRIBUTE_CIPHER	FIELD32(0x0000000e)
#define MAC_WCID_ATTRIBUTE_BSS_IDX	FIELD32(0x00000070)
#define MAC_WCID_ATTRIBUTE_RX_WIUDF	FIELD32(0x00000380)
#define MAC_WCID_ATTRIBUTE_CIPHER_EXT	FIELD32(0x00000400)
#define MAC_WCID_ATTRIBUTE_BSS_IDX_EXT	FIELD32(0x00000800)
#define MAC_WCID_ATTRIBUTE_WAPI_MCBC	FIELD32(0x00008000)
#define MAC_WCID_ATTRIBUTE_WAPI_KEY_IDX	FIELD32(0xff000000)

/*
                   
 */
#define SHARED_KEY_MODE_BSS0_KEY0	FIELD32(0x00000007)
#define SHARED_KEY_MODE_BSS0_KEY1	FIELD32(0x00000070)
#define SHARED_KEY_MODE_BSS0_KEY2	FIELD32(0x00000700)
#define SHARED_KEY_MODE_BSS0_KEY3	FIELD32(0x00007000)
#define SHARED_KEY_MODE_BSS1_KEY0	FIELD32(0x00070000)
#define SHARED_KEY_MODE_BSS1_KEY1	FIELD32(0x00700000)
#define SHARED_KEY_MODE_BSS1_KEY2	FIELD32(0x07000000)
#define SHARED_KEY_MODE_BSS1_KEY3	FIELD32(0x70000000)

/*
                         
 */

/*
                                        
                                                        
 */
#define H2M_MAILBOX_CSR			0x7010
#define H2M_MAILBOX_CSR_ARG0		FIELD32(0x000000ff)
#define H2M_MAILBOX_CSR_ARG1		FIELD32(0x0000ff00)
#define H2M_MAILBOX_CSR_CMD_TOKEN	FIELD32(0x00ff0000)
#define H2M_MAILBOX_CSR_OWNER		FIELD32(0xff000000)

/*
                   
                                                                               
                                                    
 */
#define H2M_MAILBOX_CID			0x7014
#define H2M_MAILBOX_CID_CMD0		FIELD32(0x000000ff)
#define H2M_MAILBOX_CID_CMD1		FIELD32(0x0000ff00)
#define H2M_MAILBOX_CID_CMD2		FIELD32(0x00ff0000)
#define H2M_MAILBOX_CID_CMD3		FIELD32(0xff000000)

/*
                      
                                                           
 */
#define H2M_MAILBOX_STATUS		0x701c

/*
               
 */
#define H2M_INT_SRC			0x7024

/*
                 
 */
#define H2M_BBP_AGENT			0x7028

/*
                                          
 */
#define MCU_LEDCS_LED_MODE		FIELD8(0x1f)
#define MCU_LEDCS_POLARITY		FIELD8(0x01)

/*
                  
                                        
                                                                        
 */
#define HW_CS_CTS_BASE			0x7700

/*
                   
                                                                       
 */
#define HW_DFS_CTS_BASE			0x7780

/*
                                               
 */

/*
             
                                                       
 */
#define TXRX_CSR1			0x77d0

/*
                         
                                                 
                                                    
 */
#define HW_DEBUG_SETTING_BASE		0x77f0
#define HW_DEBUG_SETTING_BASE2		0x7770

/*
                 
                                                            
                               
                                                          
                                     
                                               
                                                         
                                                        
                                                               
                     
  
                                                        
                                                             
 */
#define HW_BEACON_BASE0			0x7800
#define HW_BEACON_BASE1			0x7a00
#define HW_BEACON_BASE2			0x7c00
#define HW_BEACON_BASE3			0x7e00
#define HW_BEACON_BASE4			0x7200
#define HW_BEACON_BASE5			0x7400
#define HW_BEACON_BASE6			0x5dc0
#define HW_BEACON_BASE7			0x5bc0

#define HW_BEACON_OFFSET(__index) \
	(((__index) < 4) ? (HW_BEACON_BASE0 + (__index * 0x0200)) : \
	  (((__index) < 6) ? (HW_BEACON_BASE4 + ((__index - 4) * 0x0200)) : \
	  (HW_BEACON_BASE6 - ((__index - 6) * 0x0200))))

/*
                 
                                     
 */

/*
                                    
              
              
                             
                              
                                
 */
#define BBP1_TX_POWER_CTRL		FIELD8(0x03)
#define BBP1_TX_ANTENNA			FIELD8(0x18)

/*
                    
 */
#define BBP3_RX_ADC			FIELD8(0x03)
#define BBP3_RX_ANTENNA			FIELD8(0x18)
#define BBP3_HT40_MINUS			FIELD8(0x20)
#define BBP3_ADC_MODE_SWITCH		FIELD8(0x40)
#define BBP3_ADC_INIT_MODE		FIELD8(0x80)

/*
                   
 */
#define BBP4_TX_BF			FIELD8(0x01)
#define BBP4_BANDWIDTH			FIELD8(0x18)
#define BBP4_MAC_IF_CTRL		FIELD8(0x40)

/*       */
#define BBP27_RX_CHAIN_SEL		FIELD8(0x60)

/*
                    
 */
#define BBP47_TSSI_REPORT_SEL		FIELD8(0x03)
#define BBP47_TSSI_UPDATE_REQ		FIELD8(0x04)
#define BBP47_TSSI_TSSI_MODE		FIELD8(0x18)
#define BBP47_TSSI_ADC6			FIELD8(0x80)

/*
         
 */
#define BBP49_UPDATE_FLAG		FIELD8(0x01)

/*
           
                                                                  
                                                                  
                                                                             
             
                                                              
                              
 */
#define BBP105_DETECT_SIG_ON_PRIMARY	FIELD8(0x01)
#define BBP105_FEQ			FIELD8(0x02)
#define BBP105_MLD			FIELD8(0x04)
#define BBP105_SIG_REMODULATION		FIELD8(0x08)

/*
          
 */
#define BBP109_TX0_POWER		FIELD8(0x0f)
#define BBP109_TX1_POWER		FIELD8(0xf0)

/*
                   
 */
#define BBP138_RX_ADC1			FIELD8(0x02)
#define BBP138_RX_ADC2			FIELD8(0x04)
#define BBP138_TX_DAC1			FIELD8(0x20)
#define BBP138_TX_DAC2			FIELD8(0x40)

/*
                  
 */
#define BBP152_RX_DEFAULT_ANT		FIELD8(0x80)

/*
                   
 */
#define BBP254_BIT7			FIELD8(0x80)

/*
                  
                                       
 */

/*
           
 */
#define RFCSR1_RF_BLOCK_EN		FIELD8(0x01)
#define RFCSR1_PLL_PD			FIELD8(0x02)
#define RFCSR1_RX0_PD			FIELD8(0x04)
#define RFCSR1_TX0_PD			FIELD8(0x08)
#define RFCSR1_RX1_PD			FIELD8(0x10)
#define RFCSR1_TX1_PD			FIELD8(0x20)
#define RFCSR1_RX2_PD			FIELD8(0x40)
#define RFCSR1_TX2_PD			FIELD8(0x80)

/*
           
 */
#define RFCSR2_RESCAL_EN		FIELD8(0x80)

/*
           
 */
#define RFCSR3_K			FIELD8(0x0f)
/*                                                                   */
#define RFCSR3_PA1_BIAS_CCK		FIELD8(0x70)
#define RFCSR3_PA2_CASCODE_BIAS_CCKK	FIELD8(0x80)
/*                                                    */
#define RFCSR3_VCOCAL_EN		FIELD8(0x80)

/*
           
 */
#define RFCSR5_R1			FIELD8(0x0c)

/*
           
 */
#define RFCSR6_R1			FIELD8(0x03)
#define RFCSR6_R2			FIELD8(0x40)
#define RFCSR6_TXDIV		FIELD8(0x0c)

/*
           
 */
#define RFCSR7_RF_TUNING		FIELD8(0x01)
#define RFCSR7_BIT1			FIELD8(0x02)
#define RFCSR7_BIT2			FIELD8(0x04)
#define RFCSR7_BIT3			FIELD8(0x08)
#define RFCSR7_BIT4			FIELD8(0x10)
#define RFCSR7_BIT5			FIELD8(0x20)
#define RFCSR7_BITS67			FIELD8(0xc0)

/*
           
 */
#define RFCSR9_K			FIELD8(0x0f)
#define RFCSR9_N			FIELD8(0x10)
#define RFCSR9_UNKNOWN			FIELD8(0x60)
#define RFCSR9_MOD			FIELD8(0x80)

/*
            
 */
#define RFCSR11_R			FIELD8(0x03)
#define RFCSR11_MOD			FIELD8(0xc0)

/*
            
 */
#define RFCSR12_TX_POWER		FIELD8(0x1f)
#define RFCSR12_DR0				FIELD8(0xe0)

/*
            
 */
#define RFCSR13_TX_POWER		FIELD8(0x1f)
#define RFCSR13_DR0				FIELD8(0xe0)

/*
            
 */
#define RFCSR15_TX_LO2_EN		FIELD8(0x08)

/*
            
 */
#define RFCSR16_TXMIXER_GAIN		FIELD8(0x07)

/*
            
 */
#define RFCSR17_TXMIXER_GAIN		FIELD8(0x07)
#define RFCSR17_TX_LO1_EN		FIELD8(0x08)
#define RFCSR17_R			FIELD8(0x20)
#define RFCSR17_CODE                   FIELD8(0x7f)

/*
            
 */
#define RFCSR20_RX_LO1_EN		FIELD8(0x08)

/*
            
 */
#define RFCSR21_RX_LO2_EN		FIELD8(0x08)

/*
            
 */
#define RFCSR22_BASEBAND_LOOPBACK	FIELD8(0x01)

/*
            
 */
#define RFCSR23_FREQ_OFFSET		FIELD8(0x7f)

/*
            
 */
#define RFCSR24_TX_AGC_FC		FIELD8(0x1f)
#define RFCSR24_TX_H20M			FIELD8(0x20)
#define RFCSR24_TX_CALIB		FIELD8(0x7f)

/*
            
 */
#define RFCSR27_R1			FIELD8(0x03)
#define RFCSR27_R2			FIELD8(0x04)
#define RFCSR27_R3			FIELD8(0x30)
#define RFCSR27_R4			FIELD8(0x40)

/*
            
 */
#define RFCSR29_ADC6_TEST		FIELD8(0x01)
#define RFCSR29_ADC6_INT_TEST		FIELD8(0x02)
#define RFCSR29_RSSI_RESET		FIELD8(0x04)
#define RFCSR29_RSSI_ON			FIELD8(0x08)
#define RFCSR29_RSSI_RIP_CTRL		FIELD8(0x30)
#define RFCSR29_RSSI_GAIN		FIELD8(0xc0)

/*
            
 */
#define RFCSR30_TX_H20M			FIELD8(0x02)
#define RFCSR30_RX_H20M			FIELD8(0x04)
#define RFCSR30_RX_VCM			FIELD8(0x18)
#define RFCSR30_RF_CALIBRATION		FIELD8(0x80)

/*
            
 */
#define RFCSR31_RX_AGC_FC		FIELD8(0x1f)
#define RFCSR31_RX_H20M			FIELD8(0x20)
#define RFCSR31_RX_CALIB		FIELD8(0x7f)

/*
            
 */
#define RFCSR38_RX_LO1_EN		FIELD8(0x20)

/*
            
 */
#define RFCSR39_RX_LO2_EN		FIELD8(0x80)

/*
            
 */
#define RFCSR49_TX			FIELD8(0x3f)
#define RFCSR49_EP			FIELD8(0xc0)

/*
            
 */
#define RFCSR50_TX			FIELD8(0x3f)
#define RFCSR50_EP			FIELD8(0xc0)

/*
               
 */

/*
       
 */
#define RF2_ANTENNA_RX2			FIELD32(0x00000040)
#define RF2_ANTENNA_TX1			FIELD32(0x00004000)
#define RF2_ANTENNA_RX1			FIELD32(0x00020000)

/*
       
 */
#define RF3_TXPOWER_G			FIELD32(0x00003e00)
#define RF3_TXPOWER_A_7DBM_BOOST	FIELD32(0x00000200)
#define RF3_TXPOWER_A			FIELD32(0x00003c00)

/*
       
 */
#define RF4_TXPOWER_G			FIELD32(0x000007c0)
#define RF4_TXPOWER_A_7DBM_BOOST	FIELD32(0x00000040)
#define RF4_TXPOWER_A			FIELD32(0x00000780)
#define RF4_FREQ_OFFSET			FIELD32(0x001f8000)
#define RF4_HT40			FIELD32(0x00200000)

/*
                  
                                         
 */

/*
          
 */
#define EEPROM_CHIP_ID			0x0000

/*
                 
 */
#define EEPROM_VERSION			0x0001
#define EEPROM_VERSION_FAE		FIELD16(0x00ff)
#define EEPROM_VERSION_VERSION		FIELD16(0xff00)

/*
                  
 */
#define EEPROM_MAC_ADDR_0		0x0002
#define EEPROM_MAC_ADDR_BYTE0		FIELD16(0x00ff)
#define EEPROM_MAC_ADDR_BYTE1		FIELD16(0xff00)
#define EEPROM_MAC_ADDR_1		0x0003
#define EEPROM_MAC_ADDR_BYTE2		FIELD16(0x00ff)
#define EEPROM_MAC_ADDR_BYTE3		FIELD16(0xff00)
#define EEPROM_MAC_ADDR_2		0x0004
#define EEPROM_MAC_ADDR_BYTE4		FIELD16(0x00ff)
#define EEPROM_MAC_ADDR_BYTE5		FIELD16(0xff00)

/*
                             
                              
                              
                     
 */
#define	EEPROM_NIC_CONF0		0x001a
#define EEPROM_NIC_CONF0_RXPATH		FIELD16(0x000f)
#define EEPROM_NIC_CONF0_TXPATH		FIELD16(0x00f0)
#define EEPROM_NIC_CONF0_RF_TYPE		FIELD16(0x0f00)

/*
                             
                                  
                                         
                                         
                                         
                                       
                                     
                                     
                                 
                                  
                                  
                                           
                                             
                                          
                                         
                                    
                                  
 */
#define	EEPROM_NIC_CONF1		0x001b
#define EEPROM_NIC_CONF1_HW_RADIO		FIELD16(0x0001)
#define EEPROM_NIC_CONF1_EXTERNAL_TX_ALC		FIELD16(0x0002)
#define EEPROM_NIC_CONF1_EXTERNAL_LNA_2G		FIELD16(0x0004)
#define EEPROM_NIC_CONF1_EXTERNAL_LNA_5G		FIELD16(0x0008)
#define EEPROM_NIC_CONF1_CARDBUS_ACCEL		FIELD16(0x0010)
#define EEPROM_NIC_CONF1_BW40M_SB_2G		FIELD16(0x0020)
#define EEPROM_NIC_CONF1_BW40M_SB_5G		FIELD16(0x0040)
#define EEPROM_NIC_CONF1_WPS_PBC		FIELD16(0x0080)
#define EEPROM_NIC_CONF1_BW40M_2G		FIELD16(0x0100)
#define EEPROM_NIC_CONF1_BW40M_5G		FIELD16(0x0200)
#define EEPROM_NIC_CONF1_BROADBAND_EXT_LNA		FIELD16(0x400)
#define EEPROM_NIC_CONF1_ANT_DIVERSITY		FIELD16(0x1800)
#define EEPROM_NIC_CONF1_INTERNAL_TX_ALC		FIELD16(0x2000)
#define EEPROM_NIC_CONF1_BT_COEXIST		FIELD16(0x4000)
#define EEPROM_NIC_CONF1_DAC_TEST		FIELD16(0x8000)

/*
                   
 */
#define	EEPROM_FREQ			0x001d
#define EEPROM_FREQ_OFFSET		FIELD16(0x00ff)
#define EEPROM_FREQ_LED_MODE		FIELD16(0x7f00)
#define EEPROM_FREQ_LED_POLARITY	FIELD16(0x1000)

/*
             
                                          
                                          
                                      
                                           
                                           
                                           
                                           
                                           
                      
 */
#define EEPROM_LED_AG_CONF		0x001e
#define EEPROM_LED_ACT_CONF		0x001f
#define EEPROM_LED_POLARITY		0x0020
#define EEPROM_LED_POLARITY_RDY_BG	FIELD16(0x0001)
#define EEPROM_LED_POLARITY_RDY_A	FIELD16(0x0002)
#define EEPROM_LED_POLARITY_ACT		FIELD16(0x0004)
#define EEPROM_LED_POLARITY_GPIO_0	FIELD16(0x0008)
#define EEPROM_LED_POLARITY_GPIO_1	FIELD16(0x0010)
#define EEPROM_LED_POLARITY_GPIO_2	FIELD16(0x0020)
#define EEPROM_LED_POLARITY_GPIO_3	FIELD16(0x0040)
#define EEPROM_LED_POLARITY_GPIO_4	FIELD16(0x0080)
#define EEPROM_LED_LED_MODE		FIELD16(0x1f00)

/*
                             
                                                   
                                                   
                                                                        
 */
#define EEPROM_NIC_CONF2		0x0021
#define EEPROM_NIC_CONF2_RX_STREAM		FIELD16(0x000f)
#define EEPROM_NIC_CONF2_TX_STREAM		FIELD16(0x00f0)
#define EEPROM_NIC_CONF2_CRYSTAL		FIELD16(0x0600)

/*
             
 */
#define EEPROM_LNA			0x0022
#define EEPROM_LNA_BG			FIELD16(0x00ff)
#define EEPROM_LNA_A0			FIELD16(0xff00)

/*
                        
 */
#define EEPROM_RSSI_BG			0x0023
#define EEPROM_RSSI_BG_OFFSET0		FIELD16(0x00ff)
#define EEPROM_RSSI_BG_OFFSET1		FIELD16(0xff00)

/*
                         
 */
#define EEPROM_RSSI_BG2			0x0024
#define EEPROM_RSSI_BG2_OFFSET2		FIELD16(0x00ff)
#define EEPROM_RSSI_BG2_LNA_A1		FIELD16(0xff00)

/*
                                                                      
 */
#define EEPROM_TXMIXER_GAIN_BG		0x0024
#define EEPROM_TXMIXER_GAIN_BG_VAL	FIELD16(0x0007)

/*
                       
 */
#define EEPROM_RSSI_A			0x0025
#define EEPROM_RSSI_A_OFFSET0		FIELD16(0x00ff)
#define EEPROM_RSSI_A_OFFSET1		FIELD16(0xff00)

/*
                        
 */
#define EEPROM_RSSI_A2			0x0026
#define EEPROM_RSSI_A2_OFFSET2		FIELD16(0x00ff)
#define EEPROM_RSSI_A2_LNA_A2		FIELD16(0xff00)

/*
                                                                    
 */
#define EEPROM_TXMIXER_GAIN_A		0x0026
#define EEPROM_TXMIXER_GAIN_A_VAL	FIELD16(0x0007)

/*
                                                 
 */
#define EEPROM_EIRP_MAX_TX_POWER	0x0027
#define EEPROM_EIRP_MAX_TX_POWER_2GHZ	FIELD16(0x00ff)
#define EEPROM_EIRP_MAX_TX_POWER_5GHZ	FIELD16(0xff00)

/*
                                                              
                          
                                                
                                                          
                                                
 */
#define EEPROM_TXPOWER_DELTA		0x0028
#define EEPROM_TXPOWER_DELTA_VALUE_2G	FIELD16(0x003f)
#define EEPROM_TXPOWER_DELTA_TYPE_2G	FIELD16(0x0040)
#define EEPROM_TXPOWER_DELTA_ENABLE_2G	FIELD16(0x0080)
#define EEPROM_TXPOWER_DELTA_VALUE_5G	FIELD16(0x3f00)
#define EEPROM_TXPOWER_DELTA_TYPE_5G	FIELD16(0x4000)
#define EEPROM_TXPOWER_DELTA_ENABLE_5G	FIELD16(0x8000)

/*
                          
 */
#define	EEPROM_TXPOWER_BG1		0x0029
#define	EEPROM_TXPOWER_BG2		0x0030
#define EEPROM_TXPOWER_BG_SIZE		7
#define EEPROM_TXPOWER_BG_1		FIELD16(0x00ff)
#define EEPROM_TXPOWER_BG_2		FIELD16(0xff00)

/*
                                                      
                                                                          
                                     
                                                                          
                                     
 */
#define EEPROM_TSSI_BOUND_BG1		0x0037
#define EEPROM_TSSI_BOUND_BG1_MINUS4	FIELD16(0x00ff)
#define EEPROM_TSSI_BOUND_BG1_MINUS3	FIELD16(0xff00)

/*
                                                      
                                                                          
                                     
                                                                          
                                     
 */
#define EEPROM_TSSI_BOUND_BG2		0x0038
#define EEPROM_TSSI_BOUND_BG2_MINUS2	FIELD16(0x00ff)
#define EEPROM_TSSI_BOUND_BG2_MINUS1	FIELD16(0xff00)

/*
                                                      
                                                        
                                                                         
                                     
 */
#define EEPROM_TSSI_BOUND_BG3		0x0039
#define EEPROM_TSSI_BOUND_BG3_REF	FIELD16(0x00ff)
#define EEPROM_TSSI_BOUND_BG3_PLUS1	FIELD16(0xff00)

/*
                                                      
                                                                         
                                     
                                                                         
                                     
 */
#define EEPROM_TSSI_BOUND_BG4		0x003a
#define EEPROM_TSSI_BOUND_BG4_PLUS2	FIELD16(0x00ff)
#define EEPROM_TSSI_BOUND_BG4_PLUS3	FIELD16(0xff00)

/*
                                                      
                                                                         
                                     
                                           
 */
#define EEPROM_TSSI_BOUND_BG5		0x003b
#define EEPROM_TSSI_BOUND_BG5_PLUS4	FIELD16(0x00ff)
#define EEPROM_TSSI_BOUND_BG5_AGC_STEP	FIELD16(0xff00)

/*
                         
 */
#define EEPROM_TXPOWER_A1		0x003c
#define EEPROM_TXPOWER_A2		0x0053
#define EEPROM_TXPOWER_A_SIZE		6
#define EEPROM_TXPOWER_A_1		FIELD16(0x00ff)
#define EEPROM_TXPOWER_A_2		FIELD16(0xff00)

/*
                                                     
                                                                          
                                     
                                                                          
                                     
 */
#define EEPROM_TSSI_BOUND_A1		0x006a
#define EEPROM_TSSI_BOUND_A1_MINUS4	FIELD16(0x00ff)
#define EEPROM_TSSI_BOUND_A1_MINUS3	FIELD16(0xff00)

/*
                                                     
                                                                          
                                     
                                                                          
                                     
 */
#define EEPROM_TSSI_BOUND_A2		0x006b
#define EEPROM_TSSI_BOUND_A2_MINUS2	FIELD16(0x00ff)
#define EEPROM_TSSI_BOUND_A2_MINUS1	FIELD16(0xff00)

/*
                                                     
                                                        
                                                                         
                                     
 */
#define EEPROM_TSSI_BOUND_A3		0x006c
#define EEPROM_TSSI_BOUND_A3_REF	FIELD16(0x00ff)
#define EEPROM_TSSI_BOUND_A3_PLUS1	FIELD16(0xff00)

/*
                                                     
                                                                         
                                     
                                                                         
                                     
 */
#define EEPROM_TSSI_BOUND_A4		0x006d
#define EEPROM_TSSI_BOUND_A4_PLUS2	FIELD16(0x00ff)
#define EEPROM_TSSI_BOUND_A4_PLUS3	FIELD16(0xff00)

/*
                                                     
                                                                         
                                     
                                           
 */
#define EEPROM_TSSI_BOUND_A5		0x006e
#define EEPROM_TSSI_BOUND_A5_PLUS4	FIELD16(0x00ff)
#define EEPROM_TSSI_BOUND_A5_AGC_STEP	FIELD16(0xff00)

/*
                                                             
 */
#define EEPROM_TXPOWER_BYRATE		0x006f
#define EEPROM_TXPOWER_BYRATE_SIZE	9

#define EEPROM_TXPOWER_BYRATE_RATE0	FIELD16(0x000f)
#define EEPROM_TXPOWER_BYRATE_RATE1	FIELD16(0x00f0)
#define EEPROM_TXPOWER_BYRATE_RATE2	FIELD16(0x0f00)
#define EEPROM_TXPOWER_BYRATE_RATE3	FIELD16(0xf000)

/*
              
 */
#define	EEPROM_BBP_START		0x0078
#define EEPROM_BBP_SIZE			16
#define EEPROM_BBP_VALUE		FIELD16(0x00ff)
#define EEPROM_BBP_REG_ID		FIELD16(0xff00)

/*
                                                                        
 */

#define EEPROM_IQ_GAIN_CAL_TX0_2G			0x130
#define EEPROM_IQ_PHASE_CAL_TX0_2G			0x131
#define EEPROM_IQ_GROUPDELAY_CAL_TX0_2G			0x132
#define EEPROM_IQ_GAIN_CAL_TX1_2G			0x133
#define EEPROM_IQ_PHASE_CAL_TX1_2G			0x134
#define EEPROM_IQ_GROUPDELAY_CAL_TX1_2G			0x135
#define EEPROM_IQ_GAIN_CAL_RX0_2G			0x136
#define EEPROM_IQ_PHASE_CAL_RX0_2G			0x137
#define EEPROM_IQ_GROUPDELAY_CAL_RX0_2G			0x138
#define EEPROM_IQ_GAIN_CAL_RX1_2G			0x139
#define EEPROM_IQ_PHASE_CAL_RX1_2G			0x13A
#define EEPROM_IQ_GROUPDELAY_CAL_RX1_2G			0x13B
#define EEPROM_RF_IQ_COMPENSATION_CONTROL		0x13C
#define EEPROM_RF_IQ_IMBALANCE_COMPENSATION_CONTROL	0x13D
#define EEPROM_IQ_GAIN_CAL_TX0_CH36_TO_CH64_5G		0x144
#define EEPROM_IQ_PHASE_CAL_TX0_CH36_TO_CH64_5G		0x145
#define EEPROM_IQ_GAIN_CAL_TX0_CH100_TO_CH138_5G	0X146
#define EEPROM_IQ_PHASE_CAL_TX0_CH100_TO_CH138_5G	0x147
#define EEPROM_IQ_GAIN_CAL_TX0_CH140_TO_CH165_5G	0x148
#define EEPROM_IQ_PHASE_CAL_TX0_CH140_TO_CH165_5G	0x149
#define EEPROM_IQ_GAIN_CAL_TX1_CH36_TO_CH64_5G		0x14A
#define EEPROM_IQ_PHASE_CAL_TX1_CH36_TO_CH64_5G		0x14B
#define EEPROM_IQ_GAIN_CAL_TX1_CH100_TO_CH138_5G	0X14C
#define EEPROM_IQ_PHASE_CAL_TX1_CH100_TO_CH138_5G	0x14D
#define EEPROM_IQ_GAIN_CAL_TX1_CH140_TO_CH165_5G	0x14E
#define EEPROM_IQ_PHASE_CAL_TX1_CH140_TO_CH165_5G	0x14F
#define EEPROM_IQ_GROUPDELAY_CAL_TX0_CH36_TO_CH64_5G	0x150
#define EEPROM_IQ_GROUPDELAY_CAL_TX1_CH36_TO_CH64_5G	0x151
#define EEPROM_IQ_GROUPDELAY_CAL_TX0_CH100_TO_CH138_5G	0x152
#define EEPROM_IQ_GROUPDELAY_CAL_TX1_CH100_TO_CH138_5G	0x153
#define EEPROM_IQ_GROUPDELAY_CAL_TX0_CH140_TO_CH165_5G	0x154
#define EEPROM_IQ_GROUPDELAY_CAL_TX1_CH140_TO_CH165_5G	0x155
#define EEPROM_IQ_GAIN_CAL_RX0_CH36_TO_CH64_5G		0x156
#define EEPROM_IQ_PHASE_CAL_RX0_CH36_TO_CH64_5G		0x157
#define EEPROM_IQ_GAIN_CAL_RX0_CH100_TO_CH138_5G	0X158
#define EEPROM_IQ_PHASE_CAL_RX0_CH100_TO_CH138_5G	0x159
#define EEPROM_IQ_GAIN_CAL_RX0_CH140_TO_CH165_5G	0x15A
#define EEPROM_IQ_PHASE_CAL_RX0_CH140_TO_CH165_5G	0x15B
#define EEPROM_IQ_GAIN_CAL_RX1_CH36_TO_CH64_5G		0x15C
#define EEPROM_IQ_PHASE_CAL_RX1_CH36_TO_CH64_5G		0x15D
#define EEPROM_IQ_GAIN_CAL_RX1_CH100_TO_CH138_5G	0X15E
#define EEPROM_IQ_PHASE_CAL_RX1_CH100_TO_CH138_5G	0x15F
#define EEPROM_IQ_GAIN_CAL_RX1_CH140_TO_CH165_5G	0x160
#define EEPROM_IQ_PHASE_CAL_RX1_CH140_TO_CH165_5G	0x161
#define EEPROM_IQ_GROUPDELAY_CAL_RX0_CH36_TO_CH64_5G	0x162
#define EEPROM_IQ_GROUPDELAY_CAL_RX1_CH36_TO_CH64_5G	0x163
#define EEPROM_IQ_GROUPDELAY_CAL_RX0_CH100_TO_CH138_5G	0x164
#define EEPROM_IQ_GROUPDELAY_CAL_RX1_CH100_TO_CH138_5G	0x165
#define EEPROM_IQ_GROUPDELAY_CAL_RX0_CH140_TO_CH165_5G	0x166
#define EEPROM_IQ_GROUPDELAY_CAL_RX1_CH140_TO_CH165_5G	0x167

/*
                        
                                     
                                                                           
                                                     
                                                                      
                
                                                            
 */
#define MCU_SLEEP			0x30
#define MCU_WAKEUP			0x31
#define MCU_RADIO_OFF			0x35
#define MCU_CURRENT			0x36
#define MCU_LED				0x50
#define MCU_LED_STRENGTH		0x51
#define MCU_LED_AG_CONF		0x52
#define MCU_LED_ACT_CONF		0x53
#define MCU_LED_LED_POLARITY		0x54
#define MCU_RADAR			0x60
#define MCU_BOOT_SIGNAL			0x72
#define MCU_ANT_SELECT			0X73
#define MCU_BBP_SIGNAL			0x80
#define MCU_POWER_SAVE			0x83
#define MCU_BAND_SELECT		0x91

/*
                     
 */
#define TOKEN_SLEEP			1
#define TOKEN_RADIO_OFF			2
#define TOKEN_WAKEUP			3


/*
                          
 */
#define TXWI_DESC_SIZE			(4 * sizeof(__le32))
#define RXWI_DESC_SIZE			(4 * sizeof(__le32))

#define TXWI_DESC_SIZE_5592		(5 * sizeof(__le32))
#define RXWI_DESC_SIZE_5592		(6 * sizeof(__le32))
/*
                  
 */

/*
        
                                                    
                                                      
                                                       
                                                                      
                                             
                                                 
                                                                      
                                                                       
                                                                      
                                                                    
                                                                       
                                                                     
                                                                     
                              
 */
#define TXWI_W0_FRAG			FIELD32(0x00000001)
#define TXWI_W0_MIMO_PS			FIELD32(0x00000002)
#define TXWI_W0_CF_ACK			FIELD32(0x00000004)
#define TXWI_W0_TS			FIELD32(0x00000008)
#define TXWI_W0_AMPDU			FIELD32(0x00000010)
#define TXWI_W0_MPDU_DENSITY		FIELD32(0x000000e0)
#define TXWI_W0_TX_OP			FIELD32(0x00000300)
#define TXWI_W0_MCS			FIELD32(0x007f0000)
#define TXWI_W0_BW			FIELD32(0x00800000)
#define TXWI_W0_SHORT_GI		FIELD32(0x01000000)
#define TXWI_W0_STBC			FIELD32(0x06000000)
#define TXWI_W0_IFS			FIELD32(0x08000000)
#define TXWI_W0_PHYMODE			FIELD32(0xc0000000)

/*
        
                                       
                                                                         
                                                
                                                   
                                                
                                                                             
                                                                            
                                                                             
                                                                             
                                                                  
                                                                        
                                                                               
                                                            
 */
#define TXWI_W1_ACK			FIELD32(0x00000001)
#define TXWI_W1_NSEQ			FIELD32(0x00000002)
#define TXWI_W1_BW_WIN_SIZE		FIELD32(0x000000fc)
#define TXWI_W1_WIRELESS_CLI_ID		FIELD32(0x0000ff00)
#define TXWI_W1_MPDU_TOTAL_BYTE_COUNT	FIELD32(0x0fff0000)
#define TXWI_W1_PACKETID		FIELD32(0xf0000000)
#define TXWI_W1_PACKETID_QUEUE		FIELD32(0x30000000)
#define TXWI_W1_PACKETID_ENTRY		FIELD32(0xc0000000)

/*
        
 */
#define TXWI_W2_IV			FIELD32(0xffffffff)

/*
        
 */
#define TXWI_W3_EIV			FIELD32(0xffffffff)

/*
                  
 */

/*
        
 */
#define RXWI_W0_WIRELESS_CLI_ID		FIELD32(0x000000ff)
#define RXWI_W0_KEY_INDEX		FIELD32(0x00000300)
#define RXWI_W0_BSSID			FIELD32(0x00001c00)
#define RXWI_W0_UDF			FIELD32(0x0000e000)
#define RXWI_W0_MPDU_TOTAL_BYTE_COUNT	FIELD32(0x0fff0000)
#define RXWI_W0_TID			FIELD32(0xf0000000)

/*
        
 */
#define RXWI_W1_FRAG			FIELD32(0x0000000f)
#define RXWI_W1_SEQUENCE		FIELD32(0x0000fff0)
#define RXWI_W1_MCS			FIELD32(0x007f0000)
#define RXWI_W1_BW			FIELD32(0x00800000)
#define RXWI_W1_SHORT_GI		FIELD32(0x01000000)
#define RXWI_W1_STBC			FIELD32(0x06000000)
#define RXWI_W1_PHYMODE			FIELD32(0xc0000000)

/*
        
 */
#define RXWI_W2_RSSI0			FIELD32(0x000000ff)
#define RXWI_W2_RSSI1			FIELD32(0x0000ff00)
#define RXWI_W2_RSSI2			FIELD32(0x00ff0000)

/*
        
 */
#define RXWI_W3_SNR0			FIELD32(0x000000ff)
#define RXWI_W3_SNR1			FIELD32(0x0000ff00)

/*
                                                              
                                             
 */
#define MIN_G_TXPOWER	0
#define MIN_A_TXPOWER	-7
#define MAX_G_TXPOWER	31
#define MAX_A_TXPOWER	15
#define DEFAULT_TXPOWER	5

#define TXPOWER_G_FROM_DEV(__txpower) \
	((__txpower) > MAX_G_TXPOWER) ? DEFAULT_TXPOWER : (__txpower)

#define TXPOWER_G_TO_DEV(__txpower) \
	clamp_t(char, __txpower, MIN_G_TXPOWER, MAX_G_TXPOWER)

#define TXPOWER_A_FROM_DEV(__txpower) \
	((__txpower) > MAX_A_TXPOWER) ? DEFAULT_TXPOWER : (__txpower)

#define TXPOWER_A_TO_DEV(__txpower) \
	clamp_t(char, __txpower, MIN_A_TXPOWER, MAX_A_TXPOWER)

/*
                                       
 */
#define EIRP_MAX_TX_POWER_LIMIT	0x50

/*
                                                         
                       
 */
#define BCN_TBTT_OFFSET 64

/*
                               
 */
struct rt2800_drv_data {
	u8 calibration_bw20;
	u8 calibration_bw40;
	u8 bbp25;
	u8 bbp26;
	u8 txmixer_gain_24g;
	u8 txmixer_gain_5g;
	unsigned int tbtt_tick;
};

#endif /*          */
