#ifndef _M32102_H_
#define _M32102_H_

/*
 * Renesas M32R 32102 group
 *
 * Copyright (c) 2001  Hitoshi Yamamoto
 * Copyright (c) 2003, 2004  Renesas Technology Corp.
 */

/*                                                                       
                            
                                                                        */
#if !defined(CONFIG_CHIP_M32104)
#define M32R_SFR_OFFSET  (0x00E00000)  /*                             */
#else
#define M32R_SFR_OFFSET  (0x00700000)  /*                             */
#endif

/*
                                        
 */
#define M32R_CPM_OFFSET          (0x000F4000+M32R_SFR_OFFSET)

#define M32R_CPM_CPUCLKCR_PORTL  (0x00+M32R_CPM_OFFSET)
#define M32R_CPM_CLKMOD_PORTL    (0x04+M32R_CPM_OFFSET)
#define M32R_CPM_PLLCR_PORTL     (0x08+M32R_CPM_OFFSET)

/*
                            
 */
#define M32R_DMA_OFFSET		(0x000F8000+M32R_SFR_OFFSET)

#define M32R_DMAEN_PORTL	(0x000+M32R_DMA_OFFSET)
#define M32R_DMAISTS_PORTL	(0x004+M32R_DMA_OFFSET)
#define M32R_DMAEDET_PORTL	(0x008+M32R_DMA_OFFSET)
#define M32R_DMAASTS_PORTL	(0x00c+M32R_DMA_OFFSET)

#define M32R_DMA0CR0_PORTL	(0x100+M32R_DMA_OFFSET)
#define M32R_DMA0CR1_PORTL	(0x104+M32R_DMA_OFFSET)
#define M32R_DMA0CSA_PORTL	(0x108+M32R_DMA_OFFSET)
#define M32R_DMA0RSA_PORTL	(0x10c+M32R_DMA_OFFSET)
#define M32R_DMA0CDA_PORTL	(0x110+M32R_DMA_OFFSET)
#define M32R_DMA0RDA_PORTL	(0x114+M32R_DMA_OFFSET)
#define M32R_DMA0CBCUT_PORTL	(0x118+M32R_DMA_OFFSET)
#define M32R_DMA0RBCUT_PORTL	(0x11c+M32R_DMA_OFFSET)

#define M32R_DMA1CR0_PORTL	(0x200+M32R_DMA_OFFSET)
#define M32R_DMA1CR1_PORTL	(0x204+M32R_DMA_OFFSET)
#define M32R_DMA1CSA_PORTL	(0x208+M32R_DMA_OFFSET)
#define M32R_DMA1RSA_PORTL	(0x20c+M32R_DMA_OFFSET)
#define M32R_DMA1CDA_PORTL	(0x210+M32R_DMA_OFFSET)
#define M32R_DMA1RDA_PORTL	(0x214+M32R_DMA_OFFSET)
#define M32R_DMA1CBCUT_PORTL	(0x218+M32R_DMA_OFFSET)
#define M32R_DMA1RBCUT_PORTL	(0x21c+M32R_DMA_OFFSET)

/*
                                  
 */
#define M32R_MFT_OFFSET        (0x000FC000+M32R_SFR_OFFSET)

#define M32R_MFTCR_PORTL       (0x000+M32R_MFT_OFFSET)  /*             */
#define M32R_MFTRPR_PORTL      (0x004+M32R_MFT_OFFSET)  /*               */

#define M32R_MFT0_OFFSET       (0x100+M32R_MFT_OFFSET)
#define M32R_MFT0MOD_PORTL     (0x00+M32R_MFT0_OFFSET)  /*           */
#define M32R_MFT0BOS_PORTL     (0x04+M32R_MFT0_OFFSET)  /*                           */
#define M32R_MFT0CUT_PORTL     (0x08+M32R_MFT0_OFFSET)  /*            */
#define M32R_MFT0RLD_PORTL     (0x0C+M32R_MFT0_OFFSET)  /*             */
#define M32R_MFT0CMPRLD_PORTL  (0x10+M32R_MFT0_OFFSET)  /*                     */

#define M32R_MFT1_OFFSET       (0x200+M32R_MFT_OFFSET)
#define M32R_MFT1MOD_PORTL     (0x00+M32R_MFT1_OFFSET)  /*           */
#define M32R_MFT1BOS_PORTL     (0x04+M32R_MFT1_OFFSET)  /*                           */
#define M32R_MFT1CUT_PORTL     (0x08+M32R_MFT1_OFFSET)  /*            */
#define M32R_MFT1RLD_PORTL     (0x0C+M32R_MFT1_OFFSET)  /*             */
#define M32R_MFT1CMPRLD_PORTL  (0x10+M32R_MFT1_OFFSET)  /*                     */

#define M32R_MFT2_OFFSET       (0x300+M32R_MFT_OFFSET)
#define M32R_MFT2MOD_PORTL     (0x00+M32R_MFT2_OFFSET)  /*           */
#define M32R_MFT2BOS_PORTL     (0x04+M32R_MFT2_OFFSET)  /*                           */
#define M32R_MFT2CUT_PORTL     (0x08+M32R_MFT2_OFFSET)  /*            */
#define M32R_MFT2RLD_PORTL     (0x0C+M32R_MFT2_OFFSET)  /*             */
#define M32R_MFT2CMPRLD_PORTL  (0x10+M32R_MFT2_OFFSET)  /*                     */

#define M32R_MFT3_OFFSET       (0x400+M32R_MFT_OFFSET)
#define M32R_MFT3MOD_PORTL     (0x00+M32R_MFT3_OFFSET)  /*           */
#define M32R_MFT3BOS_PORTL     (0x04+M32R_MFT3_OFFSET)  /*                           */
#define M32R_MFT3CUT_PORTL     (0x08+M32R_MFT3_OFFSET)  /*            */
#define M32R_MFT3RLD_PORTL     (0x0C+M32R_MFT3_OFFSET)  /*             */
#define M32R_MFT3CMPRLD_PORTL  (0x10+M32R_MFT3_OFFSET)  /*                     */

#define M32R_MFT4_OFFSET       (0x500+M32R_MFT_OFFSET)
#define M32R_MFT4MOD_PORTL     (0x00+M32R_MFT4_OFFSET)  /*           */
#define M32R_MFT4BOS_PORTL     (0x04+M32R_MFT4_OFFSET)  /*                           */
#define M32R_MFT4CUT_PORTL     (0x08+M32R_MFT4_OFFSET)  /*            */
#define M32R_MFT4RLD_PORTL     (0x0C+M32R_MFT4_OFFSET)  /*             */
#define M32R_MFT4CMPRLD_PORTL  (0x10+M32R_MFT4_OFFSET)  /*                     */

#define M32R_MFT5_OFFSET       (0x600+M32R_MFT_OFFSET)
#define M32R_MFT5MOD_PORTL     (0x00+M32R_MFT5_OFFSET)  /*           */
#define M32R_MFT5BOS_PORTL     (0x04+M32R_MFT5_OFFSET)  /*                           */
#define M32R_MFT5CUT_PORTL     (0x08+M32R_MFT5_OFFSET)  /*            */
#define M32R_MFT5RLD_PORTL     (0x0C+M32R_MFT5_OFFSET)  /*             */
#define M32R_MFT5CMPRLD_PORTL  (0x10+M32R_MFT5_OFFSET)  /*                     */

#if (defined(CONFIG_CHIP_M32700) && !defined(CONFIG_PLAT_MAPPI2)) \
	|| defined(CONFIG_CHIP_M32104)
#define M32R_MFTCR_MFT0MSK  (1UL<<31)  /*    */
#define M32R_MFTCR_MFT1MSK  (1UL<<30)  /*    */
#define M32R_MFTCR_MFT2MSK  (1UL<<29)  /*    */
#define M32R_MFTCR_MFT3MSK  (1UL<<28)  /*    */
#define M32R_MFTCR_MFT4MSK  (1UL<<27)  /*    */
#define M32R_MFTCR_MFT5MSK  (1UL<<26)  /*    */
#define M32R_MFTCR_MFT0EN   (1UL<<23)  /*    */
#define M32R_MFTCR_MFT1EN   (1UL<<22)  /*    */
#define M32R_MFTCR_MFT2EN   (1UL<<21)  /*     */
#define M32R_MFTCR_MFT3EN   (1UL<<20)  /*     */
#define M32R_MFTCR_MFT4EN   (1UL<<19)  /*     */
#define M32R_MFTCR_MFT5EN   (1UL<<18)  /*     */
#else
#define M32R_MFTCR_MFT0MSK  (1UL<<15)  /*     */
#define M32R_MFTCR_MFT1MSK  (1UL<<14)  /*     */
#define M32R_MFTCR_MFT2MSK  (1UL<<13)  /*     */
#define M32R_MFTCR_MFT3MSK  (1UL<<12)  /*     */
#define M32R_MFTCR_MFT4MSK  (1UL<<11)  /*     */
#define M32R_MFTCR_MFT5MSK  (1UL<<10)  /*     */
#define M32R_MFTCR_MFT0EN   (1UL<<7)   /*     */
#define M32R_MFTCR_MFT1EN   (1UL<<6)   /*     */
#define M32R_MFTCR_MFT2EN   (1UL<<5)   /*     */
#define M32R_MFTCR_MFT3EN   (1UL<<4)   /*     */
#define M32R_MFTCR_MFT4EN   (1UL<<3)   /*     */
#define M32R_MFTCR_MFT5EN   (1UL<<2)   /*     */
#endif

#define M32R_MFTMOD_CC_MASK    (1UL<<15)  /*     */
#define M32R_MFTMOD_TCCR       (1UL<<13)  /*     */
#define M32R_MFTMOD_GTSEL000   (0UL<<8)   /*              */
#define M32R_MFTMOD_GTSEL001   (1UL<<8)   /*              */
#define M32R_MFTMOD_GTSEL010   (2UL<<8)   /*              */
#define M32R_MFTMOD_GTSEL011   (3UL<<8)   /*              */
#define M32R_MFTMOD_GTSEL110   (6UL<<8)   /*              */
#define M32R_MFTMOD_GTSEL111   (7UL<<8)   /*              */
#define M32R_MFTMOD_CMSEL      (1UL<<3)   /*     */
#define M32R_MFTMOD_CSSEL000   (0UL<<0)   /*               */
#define M32R_MFTMOD_CSSEL001   (1UL<<0)   /*               */
#define M32R_MFTMOD_CSSEL010   (2UL<<0)   /*               */
#define M32R_MFTMOD_CSSEL011   (3UL<<0)   /*               */
#define M32R_MFTMOD_CSSEL100   (4UL<<0)   /*               */
#define M32R_MFTMOD_CSSEL110   (6UL<<0)   /*               */

/*
                        
 */
#define M32R_SIO_OFFSET  (0x000FD000+M32R_SFR_OFFSET)

#define M32R_SIO0_CR_PORTL    (0x000+M32R_SIO_OFFSET)
#define M32R_SIO0_MOD0_PORTL  (0x004+M32R_SIO_OFFSET)
#define M32R_SIO0_MOD1_PORTL  (0x008+M32R_SIO_OFFSET)
#define M32R_SIO0_STS_PORTL   (0x00C+M32R_SIO_OFFSET)
#define M32R_SIO0_TRCR_PORTL  (0x010+M32R_SIO_OFFSET)
#define M32R_SIO0_BAUR_PORTL  (0x014+M32R_SIO_OFFSET)
#define M32R_SIO0_RBAUR_PORTL (0x018+M32R_SIO_OFFSET)
#define M32R_SIO0_TXB_PORTL   (0x01C+M32R_SIO_OFFSET)
#define M32R_SIO0_RXB_PORTL   (0x020+M32R_SIO_OFFSET)

/*
                                    
 */
#define M32R_ICU_OFFSET       (0x000FF000+M32R_SFR_OFFSET)
#define M32R_ICU_ISTS_PORTL   (0x004+M32R_ICU_OFFSET)
#define M32R_ICU_IREQ0_PORTL  (0x008+M32R_ICU_OFFSET)
#define M32R_ICU_IREQ1_PORTL  (0x00C+M32R_ICU_OFFSET)
#define M32R_ICU_SBICR_PORTL  (0x018+M32R_ICU_OFFSET)
#define M32R_ICU_IMASK_PORTL  (0x01C+M32R_ICU_OFFSET)
#define M32R_ICU_CR1_PORTL    (0x200+M32R_ICU_OFFSET)  /*      */
#define M32R_ICU_CR2_PORTL    (0x204+M32R_ICU_OFFSET)  /*      */
#define M32R_ICU_CR3_PORTL    (0x208+M32R_ICU_OFFSET)  /*      */
#define M32R_ICU_CR4_PORTL    (0x20C+M32R_ICU_OFFSET)  /*      */
#define M32R_ICU_CR5_PORTL    (0x210+M32R_ICU_OFFSET)  /*      */
#define M32R_ICU_CR6_PORTL    (0x214+M32R_ICU_OFFSET)  /*      */
#define M32R_ICU_CR7_PORTL    (0x218+M32R_ICU_OFFSET)  /*      */
#define M32R_ICU_CR8_PORTL    (0x219+M32R_ICU_OFFSET)  /*      */
#define M32R_ICU_CR16_PORTL   (0x23C+M32R_ICU_OFFSET)  /*      */
#define M32R_ICU_CR17_PORTL   (0x240+M32R_ICU_OFFSET)  /*      */
#define M32R_ICU_CR18_PORTL   (0x244+M32R_ICU_OFFSET)  /*      */
#define M32R_ICU_CR19_PORTL   (0x248+M32R_ICU_OFFSET)  /*      */
#define M32R_ICU_CR20_PORTL   (0x24C+M32R_ICU_OFFSET)  /*      */
#define M32R_ICU_CR21_PORTL   (0x250+M32R_ICU_OFFSET)  /*      */
#define M32R_ICU_CR32_PORTL   (0x27C+M32R_ICU_OFFSET)  /*      */
#define M32R_ICU_CR33_PORTL   (0x280+M32R_ICU_OFFSET)  /*      */
#define M32R_ICU_CR48_PORTL   (0x2BC+M32R_ICU_OFFSET)  /*      */
#define M32R_ICU_CR49_PORTL   (0x2C0+M32R_ICU_OFFSET)  /*      */
#define M32R_ICU_CR50_PORTL   (0x2C4+M32R_ICU_OFFSET)  /*      */
#define M32R_ICU_CR51_PORTL   (0x2C8+M32R_ICU_OFFSET)  /*      */
#define M32R_ICU_CR52_PORTL   (0x2CC+M32R_ICU_OFFSET)  /*      */
#define M32R_ICU_CR53_PORTL   (0x2D0+M32R_ICU_OFFSET)  /*      */
#define M32R_ICU_CR54_PORTL   (0x2D4+M32R_ICU_OFFSET)  /*      */
#define M32R_ICU_CR55_PORTL   (0x2D8+M32R_ICU_OFFSET)  /*      */
#define M32R_ICU_CR56_PORTL   (0x2DC+M32R_ICU_OFFSET)  /*      */
#define M32R_ICU_CR57_PORTL   (0x2E0+M32R_ICU_OFFSET)  /*      */

#ifdef CONFIG_SMP
#define M32R_ICU_IPICR0_PORTL (0x2dc+M32R_ICU_OFFSET)  /*      */
#define M32R_ICU_IPICR1_PORTL (0x2e0+M32R_ICU_OFFSET)  /*      */
#define M32R_ICU_IPICR2_PORTL (0x2e4+M32R_ICU_OFFSET)  /*      */
#define M32R_ICU_IPICR3_PORTL (0x2e8+M32R_ICU_OFFSET)  /*      */
#define M32R_ICU_IPICR4_PORTL (0x2ec+M32R_ICU_OFFSET)  /*      */
#define M32R_ICU_IPICR5_PORTL (0x2f0+M32R_ICU_OFFSET)  /*      */
#define M32R_ICU_IPICR6_PORTL (0x2f4+M32R_ICU_OFFSET)  /*      */
#define M32R_ICU_IPICR7_PORTL (0x2f8+M32R_ICU_OFFSET)  /*      */
#endif /*            */

#define M32R_ICUIMASK_IMSK0  (0UL<<16)  /*                            */
#define M32R_ICUIMASK_IMSK1  (1UL<<16)  /*                                   */
#define M32R_ICUIMASK_IMSK2  (2UL<<16)  /*                                     */
#define M32R_ICUIMASK_IMSK3  (3UL<<16)  /*                                     */
#define M32R_ICUIMASK_IMSK4  (4UL<<16)  /*                                     */
#define M32R_ICUIMASK_IMSK5  (5UL<<16)  /*                                     */
#define M32R_ICUIMASK_IMSK6  (6UL<<16)  /*                                     */
#define M32R_ICUIMASK_IMSK7  (7UL<<16)  /*                                     */

#define M32R_ICUCR_IEN      (1UL<<12)  /*                       */
#define M32R_ICUCR_IRQ      (1UL<<8)   /*                        */
#define M32R_ICUCR_ISMOD00  (0UL<<4)   /*                                         */
#define M32R_ICUCR_ISMOD01  (1UL<<4)   /*                                       */
#define M32R_ICUCR_ISMOD10  (2UL<<4)   /*                                        */
#define M32R_ICUCR_ISMOD11  (3UL<<4)   /*                                       */
#define M32R_ICUCR_ILEVEL0  (0UL<<0)   /*                                     */
#define M32R_ICUCR_ILEVEL1  (1UL<<0)   /*                                     */
#define M32R_ICUCR_ILEVEL2  (2UL<<0)   /*                                     */
#define M32R_ICUCR_ILEVEL3  (3UL<<0)   /*                                     */
#define M32R_ICUCR_ILEVEL4  (4UL<<0)   /*                                     */
#define M32R_ICUCR_ILEVEL5  (5UL<<0)   /*                                     */
#define M32R_ICUCR_ILEVEL6  (6UL<<0)   /*                                     */
#define M32R_ICUCR_ILEVEL7  (7UL<<0)   /*                            */

#define M32R_IRQ_INT0    (1)   /*      */
#define M32R_IRQ_INT1    (2)   /*      */
#define M32R_IRQ_INT2    (3)   /*      */
#define M32R_IRQ_INT3    (4)   /*      */
#define M32R_IRQ_INT4    (5)   /*      */
#define M32R_IRQ_INT5    (6)   /*      */
#define M32R_IRQ_INT6    (7)   /*      */
#define M32R_IRQ_MFT0    (16)  /*      */
#define M32R_IRQ_MFT1    (17)  /*      */
#define M32R_IRQ_MFT2    (18)  /*      */
#define M32R_IRQ_MFT3    (19)  /*      */
#ifdef CONFIG_CHIP_M32104
#define M32R_IRQ_MFTX0   (24)  /*       */
#define M32R_IRQ_MFTX1   (25)  /*       */
#define M32R_IRQ_DMA0    (32)  /*      */
#define M32R_IRQ_DMA1    (33)  /*      */
#define M32R_IRQ_DMA2    (34)  /*      */
#define M32R_IRQ_DMA3    (35)  /*      */
#define M32R_IRQ_SIO0_R  (40)  /*              */
#define M32R_IRQ_SIO0_S  (41)  /*              */
#define M32R_IRQ_SIO1_R  (42)  /*              */
#define M32R_IRQ_SIO1_S  (43)  /*              */
#define M32R_IRQ_SIO2_R  (44)  /*              */
#define M32R_IRQ_SIO2_S  (45)  /*              */
#define M32R_IRQ_SIO3_R  (46)  /*              */
#define M32R_IRQ_SIO3_S  (47)  /*              */
#define M32R_IRQ_ADC     (56)  /*     */
#define M32R_IRQ_PC      (57)  /*    */
#else /*          */
#define M32R_IRQ_DMA0    (32)  /*      */
#define M32R_IRQ_DMA1    (33)  /*      */
#define M32R_IRQ_SIO0_R  (48)  /*              */
#define M32R_IRQ_SIO0_S  (49)  /*              */
#define M32R_IRQ_SIO1_R  (50)  /*              */
#define M32R_IRQ_SIO1_S  (51)  /*              */
#define M32R_IRQ_SIO2_R  (52)  /*              */
#define M32R_IRQ_SIO2_S  (53)  /*              */
#define M32R_IRQ_SIO3_R  (54)  /*              */
#define M32R_IRQ_SIO3_S  (55)  /*              */
#define M32R_IRQ_SIO4_R  (56)  /*              */
#define M32R_IRQ_SIO4_S  (57)  /*              */
#endif /*          */

#ifdef CONFIG_SMP
#define M32R_IRQ_IPI0    (56)
#define M32R_IRQ_IPI1    (57)
#define M32R_IRQ_IPI2    (58)
#define M32R_IRQ_IPI3    (59)
#define M32R_IRQ_IPI4    (60)
#define M32R_IRQ_IPI5    (61)
#define M32R_IRQ_IPI6    (62)
#define M32R_IRQ_IPI7    (63)
#define M32R_CPUID_PORTL (0xffffffe0)

#define M32R_FPGA_TOP (0x000F0000+M32R_SFR_OFFSET)

#define M32R_FPGA_NUM_OF_CPUS_PORTL (0x00+M32R_FPGA_TOP)
#define M32R_FPGA_CPU_NAME0_PORTL   (0x10+M32R_FPGA_TOP)
#define M32R_FPGA_CPU_NAME1_PORTL   (0x14+M32R_FPGA_TOP)
#define M32R_FPGA_CPU_NAME2_PORTL   (0x18+M32R_FPGA_TOP)
#define M32R_FPGA_CPU_NAME3_PORTL   (0x1c+M32R_FPGA_TOP)
#define M32R_FPGA_MODEL_ID0_PORTL   (0x20+M32R_FPGA_TOP)
#define M32R_FPGA_MODEL_ID1_PORTL   (0x24+M32R_FPGA_TOP)
#define M32R_FPGA_MODEL_ID2_PORTL   (0x28+M32R_FPGA_TOP)
#define M32R_FPGA_MODEL_ID3_PORTL   (0x2c+M32R_FPGA_TOP)
#define M32R_FPGA_VERSION0_PORTL    (0x30+M32R_FPGA_TOP)
#define M32R_FPGA_VERSION1_PORTL    (0x34+M32R_FPGA_TOP)

#endif /*            */

#ifndef __ASSEMBLY__
typedef struct {
	unsigned long icucr;	/*                      */
} icu_data_t;
#endif

#endif /*            */
