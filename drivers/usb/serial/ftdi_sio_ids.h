/*
                                                                            
                                                                  
  
                                                                              
                     
  
 */


/*                                */
/*                                */
/*                                */


#define FTDI_VID	0x0403	/*           */


/*                                 */

#define FTDI_8U232AM_PID 0x6001 /*                             */
#define FTDI_8U232AM_ALT_PID 0x6006 /*                                */
#define FTDI_8U2232C_PID 0x6010 /*                     */
#define FTDI_4232H_PID 0x6011 /*                              */
#define FTDI_232H_PID  0x6014 /*                                */
#define FTDI_FTX_PID   0x6015 /*                                           */
#define FTDI_SIO_PID	0x8372	/*                                       */
#define FTDI_232RL_PID  0xFBFA  /*                        */


/*** third-party PIDs (using FTDI_VID) ***/
 
/*
 * Certain versions of the official Windows FTDI driver reprogrammed
 * counterfeit FTDI devices to PID 0. Support these devices anyway.
 */
#define FTDI_BRICK_PID		0x0000

#define FTDI_LUMEL_PD12_PID	0x6002

/*
                              
                         
                                     
 */
#define MARVELL_OPENRD_PID	0x9e90

/*                                                         */
#define FTDI_CANDAPTER_PID 0x9F80 /*            */

#define FTDI_BM_ATOM_NANO_PID	0xa559	/*                                  */

/*
                                                  
                                                 
                              
 */
#define TI_XDS100V2_PID		0xa6d0

#define FTDI_NXTCAM_PID		0xABB8 /*                           */
#define FTDI_EV3CON_PID		0xABB9 /*                                */

/*                                                      */
#define FTDI_USINT_CAT_PID	0xb810	/*                                 */
#define FTDI_USINT_WKEY_PID	0xb811	/*                              */
#define FTDI_USINT_RS232_PID	0xb812	/*                                  */

/*                                        
                                */
#define FTDI_OOCDLINK_PID	0xbaf8	/*                 */

/*                                                 */
/*                                                                           */
#define LMI_LM3S_DEVEL_BOARD_PID	0xbcd8
#define LMI_LM3S_EVAL_BOARD_PID		0xbcd9
#define LMI_LM3S_ICDI_BOARD_PID		0xbcda

#define FTDI_TURTELIZER_PID	0xBDC8 /*                                    */

/*                                     */
#define FTDI_OPENDCC_PID	0xBFD8
#define FTDI_OPENDCC_SNIFFER_PID	0xBFD9
#define FTDI_OPENDCC_THROTTLE_PID	0xBFDA
#define FTDI_OPENDCC_GATEWAY_PID	0xBFDB
#define FTDI_OPENDCC_GBM_PID	0xBFDC
#define FTDI_OPENDCC_GBM_BOOST_PID	0xBFDD

/*                                     */
#define FTDI_NZR_SEM_USB_PID	0xC1E0	/*                */

/*
                                                        
 */
#define FTDI_RRCIRKITS_LOCOBUFFER_PID	0xc7d0	/*                */

/*                        */
#define FTDI_DMX4ALL 0xC850

/*
                 
 */
#define FTDI_ASK_RDR400_PID	0xC991	/*                                */

/*                                                   */
#define FTDI_MICRO_CHAMELEON_PID	0xCAA0	/*            */

/*
                                  
                                              
                                                  
 */
#define FTDI_TACTRIX_OPENPORT_13M_PID	0xCC48	/*                         */
#define FTDI_TACTRIX_OPENPORT_13S_PID	0xCC49	/*                     */
#define FTDI_TACTRIX_OPENPORT_13U_PID	0xCC4A	/*                        */

#define FTDI_DISTORTEC_JTAG_LOCK_PICK_PID	0xCFF8

/*                                                    */
/*                                             */
#define FTDI_SCS_DEVICE_0_PID 0xD010    /*               */
#define FTDI_SCS_DEVICE_1_PID 0xD011    /*                       */
#define FTDI_SCS_DEVICE_2_PID 0xD012
#define FTDI_SCS_DEVICE_3_PID 0xD013
#define FTDI_SCS_DEVICE_4_PID 0xD014
#define FTDI_SCS_DEVICE_5_PID 0xD015
#define FTDI_SCS_DEVICE_6_PID 0xD016
#define FTDI_SCS_DEVICE_7_PID 0xD017

/*              */
#define FTDI_IPLUS_PID 0xD070 /*            */
#define FTDI_IPLUS2_PID 0xD071 /*            */

/*
                                                                      
 */
#define FTDI_GAMMA_SCOUT_PID		0xD678	/*                    */

/*                */
#define FTDI_PROPOX_JTAGCABLEII_PID	0xD738
#define FTDI_PROPOX_ISPCABLEIII_PID	0xD739

/*                                 */
#define FTDI_LENZ_LIUSB_PID	0xD780

/*                                                 */
#define FTDI_VARDAAN_PID	0xF070

/*
                                                         
 */
#define XSENS_VID		0x2639
#define XSENS_AWINDA_STATION_PID 0x0101
#define XSENS_AWINDA_DONGLE_PID 0x0102
#define XSENS_MTW_PID		0x0200	/* Xsens MTw */
#define XSENS_CONVERTER_PID	0xD00D	/* Xsens USB-serial converter */

/* Xsens devices using FTDI VID */
#define XSENS_CONVERTER_0_PID	0xD388	/* Xsens USB converter */
#define XSENS_CONVERTER_1_PID	0xD389	/* Xsens Wireless Receiver */
#define XSENS_CONVERTER_2_PID	0xD38A
#define XSENS_CONVERTER_3_PID	0xD38B	/*                            */
#define XSENS_CONVERTER_4_PID	0xD38C	/*                         */
#define XSENS_CONVERTER_5_PID	0xD38D	/*                      */
#define XSENS_CONVERTER_6_PID	0xD38E
#define XSENS_CONVERTER_7_PID	0xD38F

/* 
                                       
 */
#define FTDI_OMNI1509			0xD491	/*                              */

/*
                                     
 */
#define FTDI_NDI_HUC_PID		0xDA70	/*                        */
#define FTDI_NDI_SPECTRA_SCU_PID	0xDA71	/*                 */
#define FTDI_NDI_FUTURE_2_PID		0xDA72	/*                      */
#define FTDI_NDI_FUTURE_3_PID		0xDA73	/*                      */
#define FTDI_NDI_AURORA_SCU_PID		0xDA74	/*                */

/*
                                                                     
 */
#define FTDI_CHAMSYS_24_MASTER_WING_PID        0xDAF8
#define FTDI_CHAMSYS_PC_WING_PID       0xDAF9
#define FTDI_CHAMSYS_USB_DMX_PID       0xDAFA
#define FTDI_CHAMSYS_MIDI_TIMECODE_PID 0xDAFB
#define FTDI_CHAMSYS_MINI_WING_PID     0xDAFC
#define FTDI_CHAMSYS_MAXI_WING_PID     0xDAFD
#define FTDI_CHAMSYS_MEDIA_WING_PID    0xDAFE
#define FTDI_CHAMSYS_WING_PID  0xDAFF

/*
                                                      
 */
#define FTDI_WESTREX_MODEL_777_PID	0xDC00	/*           */
#define FTDI_WESTREX_MODEL_8900F_PID	0xDC01	/*             */

/*
                                                                      
                                            
 */
#define FTDI_ACG_HFDUAL_PID		0xDD20	/*                           */

/*
                                                         
                                           
 */
#define FTDI_ARTEMIS_PID	0xDF28	/*                     */

/*
                                                                  
                                               
 */
#define FTDI_ATIK_ATK16_PID	0xDF30	/*                              */
#define FTDI_ATIK_ATK16C_PID	0xDF32	/*                            */
#define FTDI_ATIK_ATK16HR_PID	0xDF31	/*                                */
#define FTDI_ATIK_ATK16HRC_PID	0xDF33	/*                              */
#define FTDI_ATIK_ATK16IC_PID   0xDF35  /*                                */

/*
                                                             
                                       
 */
#define FTDI_YEI_SERVOCENTER31_PID	0xE050	/*                        */

/*
                                                                  
                                                             
                                                
  
                                                                   
                                                                       
  
                                                               
 */
#define FTDI_ELV_VID	0x1B1F	/*        */
#define FTDI_ELV_WS300_PID	0xC006	/*                  */
#define FTDI_ELV_USR_PID	0xE000	/*                              */
#define FTDI_ELV_MSM1_PID	0xE001	/*                      */
#define FTDI_ELV_KL100_PID	0xE002	/*                                */
#define FTDI_ELV_WS550_PID	0xE004	/*        */
#define FTDI_ELV_EC3000_PID	0xE006	/*                         */
#define FTDI_ELV_WS888_PID	0xE008	/*        */
#define FTDI_ELV_TWS550_PID	0xE009	/*                   */
#define FTDI_ELV_FEM_PID	0xE00A	/*                      */
#define FTDI_ELV_FHZ1300PC_PID	0xE0E8	/*             */
#define FTDI_ELV_WS500_PID	0xE0E9	/*                           */
#define FTDI_ELV_HS485_PID	0xE0EA	/*                       */
#define FTDI_ELV_UMS100_PID	0xE0EB	/*                                              */
#define FTDI_ELV_TFD128_PID	0xE0EC	/*                                            */
#define FTDI_ELV_FM3RX_PID	0xE0ED	/*                                 */
#define FTDI_ELV_WS777_PID	0xE0EE	/*               */
#define FTDI_ELV_EM1010PC_PID	0xE0EF	/*                           */
#define FTDI_ELV_CSI8_PID	0xE0F0	/*                                   */
#define FTDI_ELV_EM1000DL_PID	0xE0F1	/*                                                 */
#define FTDI_ELV_PCK100_PID	0xE0F2	/*                          */
#define FTDI_ELV_RFP500_PID	0xE0F3	/*                              */
#define FTDI_ELV_FS20SIG_PID	0xE0F4	/*                         */
#define FTDI_ELV_UTP8_PID	0xE0F5	/*           */
#define FTDI_ELV_WS300PC_PID	0xE0F6	/*                              */
#define FTDI_ELV_WS444PC_PID	0xE0F7	/*                  */
#define FTDI_PHI_FISCO_PID      0xE40B  /*                               */
#define FTDI_ELV_UAD8_PID	0xF068	/*                        */
#define FTDI_ELV_UDA7_PID	0xF069	/*                        */
#define FTDI_ELV_USI2_PID	0xF06A	/*                                      */
#define FTDI_ELV_T1100_PID	0xF06B	/*                      */
#define FTDI_ELV_PCD200_PID	0xF06C	/*                          */
#define FTDI_ELV_ULA200_PID	0xF06D	/*                               */
#define FTDI_ELV_ALC8500_PID	0xF06E	/*                 */
#define FTDI_ELV_FHZ1000PC_PID	0xF06F	/*             */
#define FTDI_ELV_UR100_PID	0xFB58	/*                             */
#define FTDI_ELV_UM100_PID	0xFB5A	/*                  */
#define FTDI_ELV_UO100_PID	0xFB5B	/*                  */
/*                                                                   
                                                             
                                                                       
                                                          */
#define FTDI_ELV_CLI7000_PID	0xFB59	/*                                     */
#define FTDI_ELV_PPS7330_PID	0xFB5C	/*                                   */
#define FTDI_ELV_TFM100_PID	0xFB5D	/*                                         */
#define FTDI_ELV_UDF77_PID	0xFB5E	/*                          */
#define FTDI_ELV_UIO88_PID	0xFB5F	/*                            */

/*
                                             
 */

#define	EVER_ECO_PRO_CDS	0xe520	/*                  */

/*
                             
 */
#define FTDI_ACTIVE_ROBOTS_PID	0xE548	/*                 */

/*                       */
#define FTDI_PYRAMID_PID	0xE6C8	/*                           */

/*                                                           */
#define FTDI_ELSTER_UNICOM_PID		0xE700 /*            */

/*
                                       
 */
#define FTDI_GUDEADS_E808_PID    0xE808
#define FTDI_GUDEADS_E809_PID    0xE809
#define FTDI_GUDEADS_E80A_PID    0xE80A
#define FTDI_GUDEADS_E80B_PID    0xE80B
#define FTDI_GUDEADS_E80C_PID    0xE80C
#define FTDI_GUDEADS_E80D_PID    0xE80D
#define FTDI_GUDEADS_E80E_PID    0xE80E
#define FTDI_GUDEADS_E80F_PID    0xE80F
#define FTDI_GUDEADS_E888_PID    0xE888  /*                         */
#define FTDI_GUDEADS_E889_PID    0xE889  /*                       */
#define FTDI_GUDEADS_E88A_PID    0xE88A
#define FTDI_GUDEADS_E88B_PID    0xE88B
#define FTDI_GUDEADS_E88C_PID    0xE88C
#define FTDI_GUDEADS_E88D_PID    0xE88D
#define FTDI_GUDEADS_E88E_PID    0xE88E
#define FTDI_GUDEADS_E88F_PID    0xE88F

/*
                                          
                                        
 */
#define FTDI_ECLO_COM_1WIRE_PID	0xEA90	/*                           */

/*                                                                       */
#define FTDI_TNC_X_PID		0xEBE0

/*
                          
                                    
 */
#define FTDI_TERATRONIK_VCP_PID	 0xEC88	/*                                                      */
#define FTDI_TERATRONIK_D2XX_PID 0xEC89	/*                                                       */

/*                            */
#define FTDI_REU_TINY_PID		0xED22	/*                */

/*
                                                     
 */
#define HAMEG_HO820_PID			0xed74
#define HAMEG_HO730_PID			0xed73
#define HAMEG_HO720_PID			0xed72
#define HAMEG_HO870_PID			0xed71

/*
                                       
 */
#define FTDI_MAXSTREAM_PID	0xEE18	/*                   */

/*
                                                  
                                                       
                                                   
                                                                            
 */
#define FTDI_MHAM_KW_PID	0xEEE8	/*                  */
#define FTDI_MHAM_YS_PID	0xEEE9	/*                  */
#define FTDI_MHAM_Y6_PID	0xEEEA	/*                  */
#define FTDI_MHAM_Y8_PID	0xEEEB	/*                  */
#define FTDI_MHAM_IC_PID	0xEEEC	/*                  */
#define FTDI_MHAM_DB9_PID	0xEEED	/*                   */
#define FTDI_MHAM_RS232_PID	0xEEEE	/*                     */
#define FTDI_MHAM_Y9_PID	0xEEEF	/*                  */

/*                                              */
#define FTDI_DOMINTELL_DGQG_PID	0xEF50	/*        */
#define FTDI_DOMINTELL_DUSB_PID	0xEF51	/*               */

/*
                                                     
                                  
 */
#define FTDI_PERLE_ULTRAPORT_PID 0xF0C0	/*                            */

/*                                                    */
#define FTDI_SPROG_II		0xF0C8

/*
                                 
 */
#define FTDI_TAGSYS_LP101_PID	0xF0E9	/*                   */
#define FTDI_TAGSYS_P200X_PID	0xF0EE	/*                        */

/*                                                           */
#define FTDI_PIEGROUP_PID	0xF208	/*            */

/*                                      
                                                              */
#define FTDI_ACTZWAVE_PID	0xF2D0

/*
                                                                  
                                                                        
                                                     
 */
#define FTDI_4N_GALAXY_DE_1_PID	0xF3C0
#define FTDI_4N_GALAXY_DE_2_PID	0xF3C1
#define FTDI_4N_GALAXY_DE_3_PID	0xF3C2

/*
                                
 */
#define LINX_SDMUSBQSS_PID	0xF448	/*                   */
#define LINX_MASTERDEVEL2_PID   0xF449	/*                             */
#define LINX_FUTURE_0_PID   0xF44A	/*                    */
#define LINX_FUTURE_1_PID   0xF44B	/*                    */
#define LINX_FUTURE_2_PID   0xF44C	/*                    */

/*
                      
 */
#define FTDI_OCEANIC_PID	0xF460  /*                         */

/*
                     
 */
#define FTDI_SUUNTO_SPORTS_PID	0xF680	/*                          */

/*                                                                        */
/*                         */
#define FTDI_USB_UIRT_PID	0xF850	/*            */

/*                                  
                                                                          */
#define FTDI_CCSICDU20_0_PID    0xF9D0
#define FTDI_CCSICDU40_1_PID    0xF9D1
#define FTDI_CCSMACHX_2_PID     0xF9D2
#define FTDI_CCSLOAD_N_GO_3_PID 0xF9D3
#define FTDI_CCSICDU64_4_PID    0xF9D4
#define FTDI_CCSPRIME8_5_PID    0xF9D5

/*
                                                                    
                                                   
 */
#define FTDI_MTXORB_0_PID      0xFA00  /*                           */
#define FTDI_MTXORB_1_PID      0xFA01  /*                           */
#define FTDI_MTXORB_2_PID      0xFA02  /*                           */
#define FTDI_MTXORB_3_PID      0xFA03  /*                           */
#define FTDI_MTXORB_4_PID      0xFA04  /*                           */
#define FTDI_MTXORB_5_PID      0xFA05  /*                           */
#define FTDI_MTXORB_6_PID      0xFA06  /*                           */

/*
                                                      
 */
#define FTDI_HE_TIRA1_PID	0xFA78	/*                       */

/*                                                                       */
#define INSIDE_ACCESSO		0xFAD0

/*
                             
 */
#define FTDI_THORLABS_PID		0xfaf0 /*                            */

/*
                      
 */
#define PROTEGO_SPECIAL_1	0xFC70	/*                        */
#define PROTEGO_R2X0		0xFC71	/*                                           */
#define PROTEGO_SPECIAL_3	0xFC72	/*                        */
#define PROTEGO_SPECIAL_4	0xFC73	/*                        */

/*
                            
 */
#define FTDI_DSS20_PID		0xFC82	/*                                            */
#define FTDI_URBAN_0_PID	0xFC8A	/*                              */
#define FTDI_URBAN_1_PID	0xFC8B	/*                              */

/*                       */
#define FTDI_IRTRANS_PID 0xFC60 /*            */

/*
                                                               
                                                                  
                                                      
 */
#define FTDI_RM_CANVIEW_PID	0xfd60	/*            */
/*                                                                     */
#define FTDI_TTUSB_PID 0xFF20 /*            */

#define FTDI_USBX_707_PID 0xF857	/*                                        */

#define FTDI_RELAIS_PID	0xFA10  /*                                  */

/*
                                                           
                                                              
                                                                           
 */
#define FTDI_PCDJ_DAC2_PID 0xFA88

#define FTDI_R2000KU_TRUE_RNG	0xFB80  /*                             */

/*
                               
 */
#define DIEBOLD_BCS_SE923_PID	0xfb99

/*                             
                                                      
                                                  
                                
 */
#define FTDI_XF_632_PID 0xFC08	/*                             */
#define FTDI_XF_634_PID 0xFC09	/*                             */
#define FTDI_XF_547_PID 0xFC0A	/*                       */
#define FTDI_XF_633_PID 0xFC0B	/*                                       */
#define FTDI_XF_631_PID 0xFC0C	/*                             */
#define FTDI_XF_635_PID 0xFC0D	/*                             */
#define FTDI_XF_640_PID 0xFC0E	/*                       */
#define FTDI_XF_642_PID 0xFC0F	/*                       */

/*
                                                                         
                                                                            
                                                                          
 */
#define FTDI_VNHCPCUSB_D_PID 0xfe38 /*            */

/*                                                      */
#define FTDI_AMC232_PID 0xFF00 /*            */

/*
                                        
                                  
 */
#define FTDI_IBS_US485_PID	0xff38  /*                                        */
#define FTDI_IBS_PICPRO_PID	0xff39  /*                    */
#define FTDI_IBS_PCMCIA_PID	0xff3a  /*                                       */
#define FTDI_IBS_PK1_PID	0xff3b  /*                            */
#define FTDI_IBS_RS232MON_PID	0xff3c  /*                     */
#define FTDI_IBS_APP70_PID	0xff3d  /*                                 */
#define FTDI_IBS_PEDO_PID	0xff3e  /*                                      */
#define FTDI_IBS_PROD_PID	0xff3f  /*               */
/*                                                 */
#define FTDI_CANUSB_PID 0xFFA8 /*            */

/*
                                   
 */
#define FTDI_TAVIR_STK500_PID	0xFA33	/*                       */

/*
                              
                                      
 */
#define FTDI_TIAO_UMPA_PID	0x8a98	/*                                           */

/*
                                  
 */
#define FTDI_NT_ORIONLXM_PID	0x7c90	/*                                         */


/*                              */
/*                              */
/*                              */



/*
               
 */
#define ATMEL_VID		0x03eb /*           */
#define STK541_PID		0x2109 /*                   */

/*
                      
                                                             
 */
#define ADI_VID			0x0456
#define ADI_GNICE_PID		0xF000
#define ADI_GNICEPLUS_PID	0xF001

/*
                             
  
                                                                  
                                                            
                                                            
                                  
                                                 
                                                
 */
#define MICROCHIP_VID		0x04D8
#define MICROCHIP_USB_BOARD_PID	0x000A /*                           */

/*
                   
 */
#define RATOC_VENDOR_ID		0x0584
#define RATOC_PRODUCT_ID_USB60F	0xb020

/*
                        
 */
#define INFINEON_VID		0x058b
#define INFINEON_TRIBOARD_PID	0x0028 /*                               */

/*
                       
 */
#define ACTON_VID		0x0647	/*           */
#define ACTON_SPECTRAPRO_PID	0x0100

/*
                                          
                                
 */
#define CONTEC_VID		0x06CE	/*           */
#define CONTEC_COM1USBH_PID	0x8311	/*             */

/*
                                                  
                                      
 */
#define MITSUBISHI_VID		0x06D3
#define MITSUBISHI_FXUSB_PID	0x0284 /*                                     */

/*
                                            
 */
#define BANDB_VID		0x0856	/*                           */
#define BANDB_USOTL4_PID	0xAC01	/*                                  */
#define BANDB_USTL4_PID		0xAC02	/*                        */
#define BANDB_USO9ML2_PID	0xAC03	/*                                   */
#define BANDB_USOPTL4_PID	0xAC11
#define BANDB_USPTL4_PID	0xAC12
#define BANDB_USO9ML2DR_2_PID	0xAC16
#define BANDB_USO9ML2DR_PID	0xAC17
#define BANDB_USOPTL4DR2_PID	0xAC18	/*                                             */
#define BANDB_USOPTL4DR_PID	0xAC19
#define BANDB_485USB9F_2W_PID	0xAC25
#define BANDB_485USB9F_4W_PID	0xAC26
#define BANDB_232USB9M_PID	0xAC27
#define BANDB_485USBTB_2W_PID	0xAC33
#define BANDB_485USBTB_4W_PID	0xAC34
#define BANDB_TTL5USB9M_PID	0xAC49
#define BANDB_TTL3USB9M_PID	0xAC50
#define BANDB_ZZ_PROG1_USB_PID	0xBA02

/*
                                                                           
 */
#define INTREPID_VID		0x093C
#define INTREPID_VALUECAN_PID	0x0601
#define INTREPID_NEOVI_PID	0x0701

/*
                                                    
 */
#define IDTECH_VID		0x0ACD	/*                   */
#define IDTECH_IDT1221U_PID	0x0300	/*                                */

/*
                                                                   
 */
#define OCT_VID			0x0B39	/*               */
/*                                                                        */
/*                                                      */
/*                                                            */
#define OCT_DK201_PID		0x0103	/*                               */
#define OCT_US101_PID		0x0421	/*                         */

/*
                                    
 */
#define ICOM_VID		0x0C26 /*                */
/*                                                                   */
#define ICOM_ID_1_PID		0x0004 /*                    */
/*                                                              */
#define ICOM_OPC_U_UC_PID	0x0018 /*                                    */
/*                                                              */
#define ICOM_ID_RP2C1_PID	0x0009 /*                           */
#define ICOM_ID_RP2C2_PID	0x000A /*                           */
#define ICOM_ID_RP2D_PID	0x000B /*                           */
#define ICOM_ID_RP2VT_PID	0x000C /*                              */
#define ICOM_ID_RP2VR_PID	0x000D /*                             */
#define ICOM_ID_RP4KVT_PID	0x0010 /*                                 */
#define ICOM_ID_RP4KVR_PID	0x0011 /*                                */
#define ICOM_ID_RP2KVT_PID	0x0012 /*                                 */
#define ICOM_ID_RP2KVR_PID	0x0013 /*                                */

/*
                                            
                               
 */
#define GN_OTOMETRICS_VID	0x0c33	/*           */
#define AURICAL_USB_PID		0x0010	/*                        */

/*
                                                                   
                                                                        
                                                                     
 */
#define SEALEVEL_VID		0x0c52	/*                    */
#define SEALEVEL_2101_PID	0x2101	/*                         */
#define SEALEVEL_2102_PID	0x2102	/*                    */
#define SEALEVEL_2103_PID	0x2103	/*                     */
#define SEALEVEL_2104_PID	0x2104	/*                     */
#define SEALEVEL_2106_PID	0x9020	/*                    */
#define SEALEVEL_2201_1_PID	0x2211	/*                             */
#define SEALEVEL_2201_2_PID	0x2221	/*                             */
#define SEALEVEL_2202_1_PID	0x2212	/*                             */
#define SEALEVEL_2202_2_PID	0x2222	/*                             */
#define SEALEVEL_2203_1_PID	0x2213	/*                         */
#define SEALEVEL_2203_2_PID	0x2223	/*                         */
#define SEALEVEL_2401_1_PID	0x2411	/*                             */
#define SEALEVEL_2401_2_PID	0x2421	/*                             */
#define SEALEVEL_2401_3_PID	0x2431	/*                             */
#define SEALEVEL_2401_4_PID	0x2441	/*                             */
#define SEALEVEL_2402_1_PID	0x2412	/*                             */
#define SEALEVEL_2402_2_PID	0x2422	/*                             */
#define SEALEVEL_2402_3_PID	0x2432	/*                             */
#define SEALEVEL_2402_4_PID	0x2442	/*                             */
#define SEALEVEL_2403_1_PID	0x2413	/*                         */
#define SEALEVEL_2403_2_PID	0x2423	/*                         */
#define SEALEVEL_2403_3_PID	0x2433	/*                         */
#define SEALEVEL_2403_4_PID	0x2443	/*                         */
#define SEALEVEL_2801_1_PID	0X2811	/*                             */
#define SEALEVEL_2801_2_PID	0X2821	/*                             */
#define SEALEVEL_2801_3_PID	0X2831	/*                             */
#define SEALEVEL_2801_4_PID	0X2841	/*                             */
#define SEALEVEL_2801_5_PID	0X2851	/*                             */
#define SEALEVEL_2801_6_PID	0X2861	/*                             */
#define SEALEVEL_2801_7_PID	0X2871	/*                             */
#define SEALEVEL_2801_8_PID	0X2881	/*                             */
#define SEALEVEL_2802_1_PID	0X2812	/*                             */
#define SEALEVEL_2802_2_PID	0X2822	/*                             */
#define SEALEVEL_2802_3_PID	0X2832	/*                             */
#define SEALEVEL_2802_4_PID	0X2842	/*                             */
#define SEALEVEL_2802_5_PID	0X2852	/*                             */
#define SEALEVEL_2802_6_PID	0X2862	/*                             */
#define SEALEVEL_2802_7_PID	0X2872	/*                             */
#define SEALEVEL_2802_8_PID	0X2882	/*                             */
#define SEALEVEL_2803_1_PID	0X2813	/*                         */
#define SEALEVEL_2803_2_PID	0X2823	/*                         */
#define SEALEVEL_2803_3_PID	0X2833	/*                         */
#define SEALEVEL_2803_4_PID	0X2843	/*                         */
#define SEALEVEL_2803_5_PID	0X2853	/*                         */
#define SEALEVEL_2803_6_PID	0X2863	/*                         */
#define SEALEVEL_2803_7_PID	0X2873	/*                         */
#define SEALEVEL_2803_8_PID	0X2883	/*                         */
#define SEALEVEL_2803R_1_PID	0Xa02a	/*                                */
#define SEALEVEL_2803R_2_PID	0Xa02b	/*                                */
#define SEALEVEL_2803R_3_PID	0Xa02c	/*                                */
#define SEALEVEL_2803R_4_PID	0Xa02d	/*                                */

/*
                                 
                                                                               
 */
#define JETI_VID		0x0c6c
#define JETI_SPC1201_PID	0x04b2

/*
                                                             
                                                         
 */
#define ELEKTOR_VID		0x0C7D
#define ELEKTOR_FT323R_PID	0x0005	/*                            */

/*
                                                             
 */
#define POSIFLEX_VID		0x0d3a  /*           */
#define POSIFLEX_PP7000_PID	0x0300  /*                           */

/*
                                                                 
 */
#define KOBIL_VID		0x0d46	/*                 */
#define KOBIL_CONV_B1_PID	0x2020	/*                        */
#define KOBIL_CONV_KAAN_PID	0x2021	/*                          */

#define FTDI_NF_RIC_VID	0x0DCD	/*           */
#define FTDI_NF_RIC_PID	0x0001	/*            */

/*
                                      
 */
#define FALCOM_VID		0x0F94	/*           */
#define FALCOM_TWIST_PID	0x0001	/*                             */
#define FALCOM_SAMBA_PID	0x0005	/*                             */

/*                                         */
#define LARSENBRUSGAARD_VID		0x0FD8
#define LB_ALTITRACK_PID		0x0001

/*
                                    
 */
#define TTI_VID			0x103E	/*           */
#define TTI_QL355P_PID		0x03E8	/*                         */

/*
                                        
 */
#define NEWPORT_VID			0x104D
#define NEWPORT_AGILIS_PID		0x3000
#define NEWPORT_CONEX_CC_PID		0x3002
#define NEWPORT_CONEX_AGP_PID		0x3006

/*                               */
/*                                                */
#define INTERBIOMETRICS_VID              0x1209
#define INTERBIOMETRICS_IOBOARD_PID      0x1002
#define INTERBIOMETRICS_MINI_IOBOARD_PID 0x1006

/*
                                         
                           
 */
#define TESTO_VID			0x128D
#define TESTO_1_PID			0x0001
#define TESTO_3_PID			0x0003

/*
                                 
 */
#define MOBILITY_VID			0x1342
#define MOBILITY_USB_SERIAL_PID		0x0202	/*                         */

/*
                                                                            
                                                   
 */
#define	FIC_VID			0x1457
#define	FIC_NEO1973_DEBUG_PID	0x5118

/*        */
#define OLIMEX_VID			0x15BA
#define OLIMEX_ARM_USB_OCD_PID		0x0003
#define OLIMEX_ARM_USB_OCD_H_PID	0x002b

/*
                       
 */
#define TELLDUS_VID			0x1781	/*           */
#define TELLDUS_TELLSTICK_PID		0x0C30	/* RF control dongle 433 MHz using FT232RL */

/*
 * NOVITUS printers
 */
#define NOVITUS_VID			0x1a28
#define NOVITUS_BONO_E_PID		0x6010

/*
 * RT Systems programming cables for various ham radios
 */
#define RTSYSTEMS_VID		0x2100	/* Vendor ID */
#define RTSYSTEMS_USB_S03_PID	0x9001	/*                              */
#define RTSYSTEMS_USB_59_PID	0x9e50	/*                          */
#define RTSYSTEMS_USB_57A_PID	0x9e51	/*                                */
#define RTSYSTEMS_USB_57B_PID	0x9e52	/*                                         */
#define RTSYSTEMS_USB_29A_PID	0x9e53	/*                                  */
#define RTSYSTEMS_USB_29B_PID	0x9e54	/*                               */
#define RTSYSTEMS_USB_29F_PID	0x9e55	/*                                   */
#define RTSYSTEMS_USB_62B_PID	0x9e56	/*                                   */
#define RTSYSTEMS_USB_S01_PID	0x9e57	/*                                    */
#define RTSYSTEMS_USB_63_PID	0x9e58	/*                           */
#define RTSYSTEMS_USB_29C_PID	0x9e59	/*                                  */
#define RTSYSTEMS_USB_81B_PID	0x9e5A	/*                                  */
#define RTSYSTEMS_USB_82B_PID	0x9e5B	/*                                 */
#define RTSYSTEMS_USB_K5D_PID	0x9e5C	/*                                  */
#define RTSYSTEMS_USB_K4Y_PID	0x9e5D	/*                                */
#define RTSYSTEMS_USB_K5G_PID	0x9e5E	/*                                  */
#define RTSYSTEMS_USB_S05_PID	0x9e5F	/*                                    */
#define RTSYSTEMS_USB_60_PID	0x9e60	/*                        */
#define RTSYSTEMS_USB_61_PID	0x9e61	/*                             */
#define RTSYSTEMS_USB_62_PID	0x9e62	/*                             */
#define RTSYSTEMS_USB_63B_PID	0x9e63	/*                           */
#define RTSYSTEMS_USB_64_PID	0x9e64	/*                         */
#define RTSYSTEMS_USB_65_PID	0x9e65	/*                                      */
#define RTSYSTEMS_USB_92_PID	0x9e66	/*                          */
#define RTSYSTEMS_USB_92D_PID	0x9e67	/*                                */
#define RTSYSTEMS_USB_W5R_PID	0x9e68	/*                                  */
#define RTSYSTEMS_USB_A5R_PID	0x9e69	/*                                  */
#define RTSYSTEMS_USB_PW1_PID	0x9e6A	/*                                  */

/*
                     
                                                
 */
/*                                       */
#define PI_C865_PID	0xe0a0  /*                                */
#define PI_C857_PID	0xe0a1  /*                        */

#define PI_VID              0x1a72  /*           */
#define PI_C866_PID	0x1000  /*                                */
#define PI_C663_PID	0x1001  /*                       */
#define PI_C725_PID	0x1002  /*                                */
#define PI_E517_PID	0x1005  /*                                                    */
#define PI_C863_PID	0x1007  /*          */
#define PI_E861_PID	0x1008  /*                                */
#define PI_C867_PID	0x1009  /*                                */
#define PI_E609_PID	0x100D  /*                                   */
#define PI_E709_PID	0x100E  /*                                   */
#define PI_100F_PID	0x100F  /*                             */
#define PI_1011_PID	0x1011  /*                             */
#define PI_1012_PID	0x1012  /*                      */
#define PI_1013_PID	0x1013  /*                      */
#define PI_1014_PID	0x1014  /*           */
#define PI_1015_PID	0x1015  /*           */
#define PI_1016_PID	0x1016  /*                         */

/*
                       
                                
 */
#define KONDO_VID 		0x165c
#define KONDO_USB_SERIAL_PID	0x0002

/*
                                                                  
                                   
 */
#define BAYER_VID                      0x1A79
#define BAYER_CONTOUR_CABLE_PID        0x6001

/*
                                                                 
                                              
 */
#define MTXORB_VID			0x1B3D
#define MTXORB_FTDI_RANGE_0100_PID	0x0100
#define MTXORB_FTDI_RANGE_0101_PID	0x0101
#define MTXORB_FTDI_RANGE_0102_PID	0x0102
#define MTXORB_FTDI_RANGE_0103_PID	0x0103
#define MTXORB_FTDI_RANGE_0104_PID	0x0104
#define MTXORB_FTDI_RANGE_0105_PID	0x0105
#define MTXORB_FTDI_RANGE_0106_PID	0x0106
#define MTXORB_FTDI_RANGE_0107_PID	0x0107
#define MTXORB_FTDI_RANGE_0108_PID	0x0108
#define MTXORB_FTDI_RANGE_0109_PID	0x0109
#define MTXORB_FTDI_RANGE_010A_PID	0x010A
#define MTXORB_FTDI_RANGE_010B_PID	0x010B
#define MTXORB_FTDI_RANGE_010C_PID	0x010C
#define MTXORB_FTDI_RANGE_010D_PID	0x010D
#define MTXORB_FTDI_RANGE_010E_PID	0x010E
#define MTXORB_FTDI_RANGE_010F_PID	0x010F
#define MTXORB_FTDI_RANGE_0110_PID	0x0110
#define MTXORB_FTDI_RANGE_0111_PID	0x0111
#define MTXORB_FTDI_RANGE_0112_PID	0x0112
#define MTXORB_FTDI_RANGE_0113_PID	0x0113
#define MTXORB_FTDI_RANGE_0114_PID	0x0114
#define MTXORB_FTDI_RANGE_0115_PID	0x0115
#define MTXORB_FTDI_RANGE_0116_PID	0x0116
#define MTXORB_FTDI_RANGE_0117_PID	0x0117
#define MTXORB_FTDI_RANGE_0118_PID	0x0118
#define MTXORB_FTDI_RANGE_0119_PID	0x0119
#define MTXORB_FTDI_RANGE_011A_PID	0x011A
#define MTXORB_FTDI_RANGE_011B_PID	0x011B
#define MTXORB_FTDI_RANGE_011C_PID	0x011C
#define MTXORB_FTDI_RANGE_011D_PID	0x011D
#define MTXORB_FTDI_RANGE_011E_PID	0x011E
#define MTXORB_FTDI_RANGE_011F_PID	0x011F
#define MTXORB_FTDI_RANGE_0120_PID	0x0120
#define MTXORB_FTDI_RANGE_0121_PID	0x0121
#define MTXORB_FTDI_RANGE_0122_PID	0x0122
#define MTXORB_FTDI_RANGE_0123_PID	0x0123
#define MTXORB_FTDI_RANGE_0124_PID	0x0124
#define MTXORB_FTDI_RANGE_0125_PID	0x0125
#define MTXORB_FTDI_RANGE_0126_PID	0x0126
#define MTXORB_FTDI_RANGE_0127_PID	0x0127
#define MTXORB_FTDI_RANGE_0128_PID	0x0128
#define MTXORB_FTDI_RANGE_0129_PID	0x0129
#define MTXORB_FTDI_RANGE_012A_PID	0x012A
#define MTXORB_FTDI_RANGE_012B_PID	0x012B
#define MTXORB_FTDI_RANGE_012C_PID	0x012C
#define MTXORB_FTDI_RANGE_012D_PID	0x012D
#define MTXORB_FTDI_RANGE_012E_PID	0x012E
#define MTXORB_FTDI_RANGE_012F_PID	0x012F
#define MTXORB_FTDI_RANGE_0130_PID	0x0130
#define MTXORB_FTDI_RANGE_0131_PID	0x0131
#define MTXORB_FTDI_RANGE_0132_PID	0x0132
#define MTXORB_FTDI_RANGE_0133_PID	0x0133
#define MTXORB_FTDI_RANGE_0134_PID	0x0134
#define MTXORB_FTDI_RANGE_0135_PID	0x0135
#define MTXORB_FTDI_RANGE_0136_PID	0x0136
#define MTXORB_FTDI_RANGE_0137_PID	0x0137
#define MTXORB_FTDI_RANGE_0138_PID	0x0138
#define MTXORB_FTDI_RANGE_0139_PID	0x0139
#define MTXORB_FTDI_RANGE_013A_PID	0x013A
#define MTXORB_FTDI_RANGE_013B_PID	0x013B
#define MTXORB_FTDI_RANGE_013C_PID	0x013C
#define MTXORB_FTDI_RANGE_013D_PID	0x013D
#define MTXORB_FTDI_RANGE_013E_PID	0x013E
#define MTXORB_FTDI_RANGE_013F_PID	0x013F
#define MTXORB_FTDI_RANGE_0140_PID	0x0140
#define MTXORB_FTDI_RANGE_0141_PID	0x0141
#define MTXORB_FTDI_RANGE_0142_PID	0x0142
#define MTXORB_FTDI_RANGE_0143_PID	0x0143
#define MTXORB_FTDI_RANGE_0144_PID	0x0144
#define MTXORB_FTDI_RANGE_0145_PID	0x0145
#define MTXORB_FTDI_RANGE_0146_PID	0x0146
#define MTXORB_FTDI_RANGE_0147_PID	0x0147
#define MTXORB_FTDI_RANGE_0148_PID	0x0148
#define MTXORB_FTDI_RANGE_0149_PID	0x0149
#define MTXORB_FTDI_RANGE_014A_PID	0x014A
#define MTXORB_FTDI_RANGE_014B_PID	0x014B
#define MTXORB_FTDI_RANGE_014C_PID	0x014C
#define MTXORB_FTDI_RANGE_014D_PID	0x014D
#define MTXORB_FTDI_RANGE_014E_PID	0x014E
#define MTXORB_FTDI_RANGE_014F_PID	0x014F
#define MTXORB_FTDI_RANGE_0150_PID	0x0150
#define MTXORB_FTDI_RANGE_0151_PID	0x0151
#define MTXORB_FTDI_RANGE_0152_PID	0x0152
#define MTXORB_FTDI_RANGE_0153_PID	0x0153
#define MTXORB_FTDI_RANGE_0154_PID	0x0154
#define MTXORB_FTDI_RANGE_0155_PID	0x0155
#define MTXORB_FTDI_RANGE_0156_PID	0x0156
#define MTXORB_FTDI_RANGE_0157_PID	0x0157
#define MTXORB_FTDI_RANGE_0158_PID	0x0158
#define MTXORB_FTDI_RANGE_0159_PID	0x0159
#define MTXORB_FTDI_RANGE_015A_PID	0x015A
#define MTXORB_FTDI_RANGE_015B_PID	0x015B
#define MTXORB_FTDI_RANGE_015C_PID	0x015C
#define MTXORB_FTDI_RANGE_015D_PID	0x015D
#define MTXORB_FTDI_RANGE_015E_PID	0x015E
#define MTXORB_FTDI_RANGE_015F_PID	0x015F
#define MTXORB_FTDI_RANGE_0160_PID	0x0160
#define MTXORB_FTDI_RANGE_0161_PID	0x0161
#define MTXORB_FTDI_RANGE_0162_PID	0x0162
#define MTXORB_FTDI_RANGE_0163_PID	0x0163
#define MTXORB_FTDI_RANGE_0164_PID	0x0164
#define MTXORB_FTDI_RANGE_0165_PID	0x0165
#define MTXORB_FTDI_RANGE_0166_PID	0x0166
#define MTXORB_FTDI_RANGE_0167_PID	0x0167
#define MTXORB_FTDI_RANGE_0168_PID	0x0168
#define MTXORB_FTDI_RANGE_0169_PID	0x0169
#define MTXORB_FTDI_RANGE_016A_PID	0x016A
#define MTXORB_FTDI_RANGE_016B_PID	0x016B
#define MTXORB_FTDI_RANGE_016C_PID	0x016C
#define MTXORB_FTDI_RANGE_016D_PID	0x016D
#define MTXORB_FTDI_RANGE_016E_PID	0x016E
#define MTXORB_FTDI_RANGE_016F_PID	0x016F
#define MTXORB_FTDI_RANGE_0170_PID	0x0170
#define MTXORB_FTDI_RANGE_0171_PID	0x0171
#define MTXORB_FTDI_RANGE_0172_PID	0x0172
#define MTXORB_FTDI_RANGE_0173_PID	0x0173
#define MTXORB_FTDI_RANGE_0174_PID	0x0174
#define MTXORB_FTDI_RANGE_0175_PID	0x0175
#define MTXORB_FTDI_RANGE_0176_PID	0x0176
#define MTXORB_FTDI_RANGE_0177_PID	0x0177
#define MTXORB_FTDI_RANGE_0178_PID	0x0178
#define MTXORB_FTDI_RANGE_0179_PID	0x0179
#define MTXORB_FTDI_RANGE_017A_PID	0x017A
#define MTXORB_FTDI_RANGE_017B_PID	0x017B
#define MTXORB_FTDI_RANGE_017C_PID	0x017C
#define MTXORB_FTDI_RANGE_017D_PID	0x017D
#define MTXORB_FTDI_RANGE_017E_PID	0x017E
#define MTXORB_FTDI_RANGE_017F_PID	0x017F
#define MTXORB_FTDI_RANGE_0180_PID	0x0180
#define MTXORB_FTDI_RANGE_0181_PID	0x0181
#define MTXORB_FTDI_RANGE_0182_PID	0x0182
#define MTXORB_FTDI_RANGE_0183_PID	0x0183
#define MTXORB_FTDI_RANGE_0184_PID	0x0184
#define MTXORB_FTDI_RANGE_0185_PID	0x0185
#define MTXORB_FTDI_RANGE_0186_PID	0x0186
#define MTXORB_FTDI_RANGE_0187_PID	0x0187
#define MTXORB_FTDI_RANGE_0188_PID	0x0188
#define MTXORB_FTDI_RANGE_0189_PID	0x0189
#define MTXORB_FTDI_RANGE_018A_PID	0x018A
#define MTXORB_FTDI_RANGE_018B_PID	0x018B
#define MTXORB_FTDI_RANGE_018C_PID	0x018C
#define MTXORB_FTDI_RANGE_018D_PID	0x018D
#define MTXORB_FTDI_RANGE_018E_PID	0x018E
#define MTXORB_FTDI_RANGE_018F_PID	0x018F
#define MTXORB_FTDI_RANGE_0190_PID	0x0190
#define MTXORB_FTDI_RANGE_0191_PID	0x0191
#define MTXORB_FTDI_RANGE_0192_PID	0x0192
#define MTXORB_FTDI_RANGE_0193_PID	0x0193
#define MTXORB_FTDI_RANGE_0194_PID	0x0194
#define MTXORB_FTDI_RANGE_0195_PID	0x0195
#define MTXORB_FTDI_RANGE_0196_PID	0x0196
#define MTXORB_FTDI_RANGE_0197_PID	0x0197
#define MTXORB_FTDI_RANGE_0198_PID	0x0198
#define MTXORB_FTDI_RANGE_0199_PID	0x0199
#define MTXORB_FTDI_RANGE_019A_PID	0x019A
#define MTXORB_FTDI_RANGE_019B_PID	0x019B
#define MTXORB_FTDI_RANGE_019C_PID	0x019C
#define MTXORB_FTDI_RANGE_019D_PID	0x019D
#define MTXORB_FTDI_RANGE_019E_PID	0x019E
#define MTXORB_FTDI_RANGE_019F_PID	0x019F
#define MTXORB_FTDI_RANGE_01A0_PID	0x01A0
#define MTXORB_FTDI_RANGE_01A1_PID	0x01A1
#define MTXORB_FTDI_RANGE_01A2_PID	0x01A2
#define MTXORB_FTDI_RANGE_01A3_PID	0x01A3
#define MTXORB_FTDI_RANGE_01A4_PID	0x01A4
#define MTXORB_FTDI_RANGE_01A5_PID	0x01A5
#define MTXORB_FTDI_RANGE_01A6_PID	0x01A6
#define MTXORB_FTDI_RANGE_01A7_PID	0x01A7
#define MTXORB_FTDI_RANGE_01A8_PID	0x01A8
#define MTXORB_FTDI_RANGE_01A9_PID	0x01A9
#define MTXORB_FTDI_RANGE_01AA_PID	0x01AA
#define MTXORB_FTDI_RANGE_01AB_PID	0x01AB
#define MTXORB_FTDI_RANGE_01AC_PID	0x01AC
#define MTXORB_FTDI_RANGE_01AD_PID	0x01AD
#define MTXORB_FTDI_RANGE_01AE_PID	0x01AE
#define MTXORB_FTDI_RANGE_01AF_PID	0x01AF
#define MTXORB_FTDI_RANGE_01B0_PID	0x01B0
#define MTXORB_FTDI_RANGE_01B1_PID	0x01B1
#define MTXORB_FTDI_RANGE_01B2_PID	0x01B2
#define MTXORB_FTDI_RANGE_01B3_PID	0x01B3
#define MTXORB_FTDI_RANGE_01B4_PID	0x01B4
#define MTXORB_FTDI_RANGE_01B5_PID	0x01B5
#define MTXORB_FTDI_RANGE_01B6_PID	0x01B6
#define MTXORB_FTDI_RANGE_01B7_PID	0x01B7
#define MTXORB_FTDI_RANGE_01B8_PID	0x01B8
#define MTXORB_FTDI_RANGE_01B9_PID	0x01B9
#define MTXORB_FTDI_RANGE_01BA_PID	0x01BA
#define MTXORB_FTDI_RANGE_01BB_PID	0x01BB
#define MTXORB_FTDI_RANGE_01BC_PID	0x01BC
#define MTXORB_FTDI_RANGE_01BD_PID	0x01BD
#define MTXORB_FTDI_RANGE_01BE_PID	0x01BE
#define MTXORB_FTDI_RANGE_01BF_PID	0x01BF
#define MTXORB_FTDI_RANGE_01C0_PID	0x01C0
#define MTXORB_FTDI_RANGE_01C1_PID	0x01C1
#define MTXORB_FTDI_RANGE_01C2_PID	0x01C2
#define MTXORB_FTDI_RANGE_01C3_PID	0x01C3
#define MTXORB_FTDI_RANGE_01C4_PID	0x01C4
#define MTXORB_FTDI_RANGE_01C5_PID	0x01C5
#define MTXORB_FTDI_RANGE_01C6_PID	0x01C6
#define MTXORB_FTDI_RANGE_01C7_PID	0x01C7
#define MTXORB_FTDI_RANGE_01C8_PID	0x01C8
#define MTXORB_FTDI_RANGE_01C9_PID	0x01C9
#define MTXORB_FTDI_RANGE_01CA_PID	0x01CA
#define MTXORB_FTDI_RANGE_01CB_PID	0x01CB
#define MTXORB_FTDI_RANGE_01CC_PID	0x01CC
#define MTXORB_FTDI_RANGE_01CD_PID	0x01CD
#define MTXORB_FTDI_RANGE_01CE_PID	0x01CE
#define MTXORB_FTDI_RANGE_01CF_PID	0x01CF
#define MTXORB_FTDI_RANGE_01D0_PID	0x01D0
#define MTXORB_FTDI_RANGE_01D1_PID	0x01D1
#define MTXORB_FTDI_RANGE_01D2_PID	0x01D2
#define MTXORB_FTDI_RANGE_01D3_PID	0x01D3
#define MTXORB_FTDI_RANGE_01D4_PID	0x01D4
#define MTXORB_FTDI_RANGE_01D5_PID	0x01D5
#define MTXORB_FTDI_RANGE_01D6_PID	0x01D6
#define MTXORB_FTDI_RANGE_01D7_PID	0x01D7
#define MTXORB_FTDI_RANGE_01D8_PID	0x01D8
#define MTXORB_FTDI_RANGE_01D9_PID	0x01D9
#define MTXORB_FTDI_RANGE_01DA_PID	0x01DA
#define MTXORB_FTDI_RANGE_01DB_PID	0x01DB
#define MTXORB_FTDI_RANGE_01DC_PID	0x01DC
#define MTXORB_FTDI_RANGE_01DD_PID	0x01DD
#define MTXORB_FTDI_RANGE_01DE_PID	0x01DE
#define MTXORB_FTDI_RANGE_01DF_PID	0x01DF
#define MTXORB_FTDI_RANGE_01E0_PID	0x01E0
#define MTXORB_FTDI_RANGE_01E1_PID	0x01E1
#define MTXORB_FTDI_RANGE_01E2_PID	0x01E2
#define MTXORB_FTDI_RANGE_01E3_PID	0x01E3
#define MTXORB_FTDI_RANGE_01E4_PID	0x01E4
#define MTXORB_FTDI_RANGE_01E5_PID	0x01E5
#define MTXORB_FTDI_RANGE_01E6_PID	0x01E6
#define MTXORB_FTDI_RANGE_01E7_PID	0x01E7
#define MTXORB_FTDI_RANGE_01E8_PID	0x01E8
#define MTXORB_FTDI_RANGE_01E9_PID	0x01E9
#define MTXORB_FTDI_RANGE_01EA_PID	0x01EA
#define MTXORB_FTDI_RANGE_01EB_PID	0x01EB
#define MTXORB_FTDI_RANGE_01EC_PID	0x01EC
#define MTXORB_FTDI_RANGE_01ED_PID	0x01ED
#define MTXORB_FTDI_RANGE_01EE_PID	0x01EE
#define MTXORB_FTDI_RANGE_01EF_PID	0x01EF
#define MTXORB_FTDI_RANGE_01F0_PID	0x01F0
#define MTXORB_FTDI_RANGE_01F1_PID	0x01F1
#define MTXORB_FTDI_RANGE_01F2_PID	0x01F2
#define MTXORB_FTDI_RANGE_01F3_PID	0x01F3
#define MTXORB_FTDI_RANGE_01F4_PID	0x01F4
#define MTXORB_FTDI_RANGE_01F5_PID	0x01F5
#define MTXORB_FTDI_RANGE_01F6_PID	0x01F6
#define MTXORB_FTDI_RANGE_01F7_PID	0x01F7
#define MTXORB_FTDI_RANGE_01F8_PID	0x01F8
#define MTXORB_FTDI_RANGE_01F9_PID	0x01F9
#define MTXORB_FTDI_RANGE_01FA_PID	0x01FA
#define MTXORB_FTDI_RANGE_01FB_PID	0x01FB
#define MTXORB_FTDI_RANGE_01FC_PID	0x01FC
#define MTXORB_FTDI_RANGE_01FD_PID	0x01FD
#define MTXORB_FTDI_RANGE_01FE_PID	0x01FE
#define MTXORB_FTDI_RANGE_01FF_PID	0x01FF



/*
                         
                               
 */
#define TML_VID			0x1B91	/*           */
#define TML_USB_SERIAL_PID	0x0064	/*                        */

/*                                        */
#define ALTI2_VID	0x1BC9
#define ALTI2_N3_PID	0x6001	/*           */

/*
                      
 */
#define IONICS_VID			0x1c0c
#define IONICS_PLUGCOMPUTER_PID		0x0102

/*
                                           
 */
#define DE_VID			0x1cf1 /*           */
#define STB_PID			0x0001 /*                       */
#define WHT_PID			0x0004 /*                            */

/*
                    
 */
#define ST_VID			0x0483
#define ST_STMCLT_2232_PID	0x3746
#define ST_STMCLT_4232_PID	0x3747

/*
                                             
                                   
 */

#define PAPOUCH_VID			0x5050	/*           */
#define PAPOUCH_SB485_PID		0x0100	/*                                     */
#define PAPOUCH_AP485_PID		0x0101	/*                           */
#define PAPOUCH_SB422_PID		0x0102	/*                                    */
#define PAPOUCH_SB485_2_PID		0x0103	/*                                     */
#define PAPOUCH_AP485_2_PID		0x0104	/*                           */
#define PAPOUCH_SB422_2_PID		0x0105	/*                                    */
#define PAPOUCH_SB485S_PID		0x0106	/*                                      */
#define PAPOUCH_SB485C_PID		0x0107	/*                                      */
#define PAPOUCH_LEC_PID			0x0300	/*                   */
#define PAPOUCH_SB232_PID		0x0301	/*                                   */
#define PAPOUCH_TMU_PID			0x0400	/*                     */
#define PAPOUCH_IRAMP_PID		0x0500	/*                      */
#define PAPOUCH_DRAK5_PID		0x0700	/*               */
#define PAPOUCH_QUIDO8x8_PID		0x0800	/*                          */
#define PAPOUCH_QUIDO4x4_PID		0x0900	/*                          */
#define PAPOUCH_QUIDO2x2_PID		0x0a00	/*                          */
#define PAPOUCH_QUIDO10x1_PID		0x0b00	/*                           */
#define PAPOUCH_QUIDO30x3_PID		0x0c00	/*                           */
#define PAPOUCH_QUIDO60x3_PID		0x0d00	/*                                */
#define PAPOUCH_QUIDO2x16_PID		0x0e00	/*                           */
#define PAPOUCH_QUIDO3x32_PID		0x0f00	/*                           */
#define PAPOUCH_DRAK6_PID		0x1000	/*               */
#define PAPOUCH_UPSUSB_PID		0x8000	/*                         */
#define PAPOUCH_MU_PID			0x8001	/*               */
#define PAPOUCH_SIMUKEY_PID		0x8002	/*                 */
#define PAPOUCH_AD4USB_PID		0x8003	/*                           */
#define PAPOUCH_GMUX_PID		0x8004	/*                     */
#define PAPOUCH_GMSR_PID		0x8005	/*                     */

/*
                     
 */
#define MARVELL_VID		0x9e88
#define MARVELL_SHEEVAPLUG_PID	0x9e8f

/*
                                                           
                                 
 */
#define EVOLUTION_VID		0xDEEE	/*           */
#define EVOLUTION_ER1_PID	0x0300	/*                    */
#define EVO_8U232AM_PID		0x02FF	/*                                  */
#define EVO_HYBRID_PID		0x0302	/*                                      */
#define EVO_RCM4_PID		0x0303	/*                             */

/*
                                                                               
 */
#define MJSG_GENERIC_PID	0x9378
#define MJSG_SR_RADIO_PID	0x9379
#define MJSG_XM_RADIO_PID	0x937A
#define MJSG_HD_RADIO_PID	0x937C

/*
                                             
 */
#define FTDI_DOTEC_PID 0x9868

/*
                                                       
 */
#define XVERVE_SIGNALYZER_ST_PID	0xBCA0
#define XVERVE_SIGNALYZER_SLITE_PID	0xBCA1
#define XVERVE_SIGNALYZER_SH2_PID	0xBCA2
#define XVERVE_SIGNALYZER_SH4_PID	0xBCA4

/*
                                                                    
                              
 */
#define SEGWAY_RMP200_PID	0xe729


/*
                                                                  
 */
#define ACCESIO_COM4SM_PID 	0xD578

/*                                                */
#define FTDI_SCIENCESCOPE_LOGBOOKML_PID		0xFF18
#define FTDI_SCIENCESCOPE_LS_LOGBOOK_PID	0xFF1C
#define FTDI_SCIENCESCOPE_HS_LOGBOOK_PID	0xFF1D

/*
                            
 */
#define QIHARDWARE_VID			0x20B7
#define MILKYMISTONE_JTAGSERIAL_PID	0x0713

/*
                                                    
 */
/*             */
#define FTDI_CTI_MINI_PID	0xF608
/*             */
#define FTDI_CTI_NANO_PID	0xF60B

/*
                                                                 
 */
/*                 */
#define FTDI_ZEITCONTROL_TAGTRACE_MIFARE_PID	0xF7C0

/*
                        
 */
/*                   */
#define FTDI_RF_R106		0x8A28

/*
                              
                           
                                      
 */
#define FTDI_CINTERION_MC55I_PID	0xA951

/*
                                   
                                      
 */
#define FTDI_CT_COMET_PID	0x8e08

/*
                   
                               
 */
#define FTDI_Z3X_PID		0x0011

/*
                               
                       
 */
#define FTDI_CRESSI_PID		0x87d0

/*
                     
 */
#define BRAINBOXES_VID			0x05d1
#define BRAINBOXES_VX_001_PID		0x1001 /*                                 */
#define BRAINBOXES_VX_012_PID		0x1002 /*                                 */
#define BRAINBOXES_VX_023_PID		0x1003 /*                                     */
#define BRAINBOXES_VX_034_PID		0x1004 /*                                     */
#define BRAINBOXES_US_101_PID		0x1011 /*                */
#define BRAINBOXES_US_324_PID		0x1013 /*                           */
#define BRAINBOXES_US_606_1_PID		0x2001 /*                                         */
#define BRAINBOXES_US_606_2_PID		0x2002 /*                                         */
#define BRAINBOXES_US_606_3_PID		0x2003 /*                                         */
#define BRAINBOXES_US_701_1_PID		0x2011 /*                                    */
#define BRAINBOXES_US_701_2_PID		0x2012 /*                                    */
#define BRAINBOXES_US_279_1_PID		0x2021 /*                                    */
#define BRAINBOXES_US_279_2_PID		0x2022 /*                                    */
#define BRAINBOXES_US_279_3_PID		0x2023 /*                                    */
#define BRAINBOXES_US_279_4_PID		0x2024 /*                                    */
#define BRAINBOXES_US_346_1_PID		0x3011 /*                                        */
#define BRAINBOXES_US_346_2_PID		0x3012 /*                                        */
#define BRAINBOXES_US_257_PID		0x5001 /*                       */
#define BRAINBOXES_US_313_PID		0x6001 /*                           */
#define BRAINBOXES_US_357_PID		0x7001 /*                        */
#define BRAINBOXES_US_842_1_PID		0x8001 /*                                        */
#define BRAINBOXES_US_842_2_PID		0x8002 /*                                        */
#define BRAINBOXES_US_842_3_PID		0x8003 /*                                        */
#define BRAINBOXES_US_842_4_PID		0x8004 /*                                        */
#define BRAINBOXES_US_160_1_PID		0x9001 /*                                     */
#define BRAINBOXES_US_160_2_PID		0x9002 /*                                     */
#define BRAINBOXES_US_160_3_PID		0x9003 /*                                     */
#define BRAINBOXES_US_160_4_PID		0x9004 /*                                     */
#define BRAINBOXES_US_160_5_PID		0x9005 /*                                      */
#define BRAINBOXES_US_160_6_PID		0x9006 /*                                       */
#define BRAINBOXES_US_160_7_PID		0x9007 /*                                       */
#define BRAINBOXES_US_160_8_PID		0x9008 /*                                       */

/*
                                                 
 */
#define FTDI_EKEY_CONV_USB_PID		0xCB08	/*               */
