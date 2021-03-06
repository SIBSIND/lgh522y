/*
                                                                                   
*/

/*                 
                              

                       
*/



/*
                
  
                        
                                                            
              
  
                   
                                                                             
                                                   
                                                  
  
                      
                                                         
                               
  
                      
                                                         
                                      
                 
                                                            
  
                        
                                                         
                                                   
  
                      
                                                         
    
  
                          
                                        
                                        
  
                        
                                                
    
  
                      
                                                             
                                                  
                                                                      
  
                      
       
                                              
  
                          
                                                                                     
                                              
  
                   
                                                                             
                                                   
  
                   
                                                                                                                                       
                                                                    
                               
  
                   
                                                                                                                                                        
                                                          
  
                   
                                                                                                                                                        
                                                      
  
                      
                                                                           
                                     
  
                      
                                                                                                      
    
  
                        
                                                                                               
                                       
  
                           
                                                                                
    
  
                        
                                                                                              
                                                 
  
                        
                                                                                              
                                                  
  
                   
                                                                                                   
                                      
  
                   
                                                                                                     
                                          
  
                   
                                                                                      
                                                                          
  
                      
       
                                   
  
                        
       
                         
                                 
  
                   
  
                                                                               
  
                        
                                                    
                        
  
                        
                                                    
                                           
  
                   
                                                    
               
  
                         
                                                
                                   
  
                         
                                                          
                          
                                                                           
                                                          
                                                                           
                    
  
*/

#ifndef _MAC_H
#define _MAC_H

/*                                                                              
                                                     
                                                                                
*/

/*                                                                              
                                                          
                                                                                
*/

/*                                                                              
                                                
                                                                                
*/
/*                                                                     */
/*             */
#define MAC_ADDR_LEN                            6

#define MAC_ADDR_LOCAL_ADMIN                    BIT(1)

#define ETH_P_IPV4                              0x0800
#define ETH_P_IPX                               0x8137	/*            */
#define ETH_P_AARP                              0x80F3	/*                                              */
#define ETH_P_IPV6                              0x86DD
#define ETH_P_VLAN                              0x8100

#define ETH_P_1X                                0x888E
#define ETH_P_PRE_1X                            0x88C7
#if CFG_SUPPORT_WAPI
#define ETH_WPI_1X                              0x88B4
#endif

/*                                       */
#define ETH_802_3_MAX_LEN                       1500

/*                      */
#define IP_VERSION_MASK                         BITS(4, 7)
#define IP_VERSION_OFFSET                       4
#define IP_VERSION_4                            4
#define IP_VERSION_6                            6

#define IP_PROTOCOL_TCP                         6
#define IP_PROTOCOL_UDP                         17

/*                        */
#define IPV4_HDR_TOS_OFFSET                     1
#define IPV4_HDR_TOS_PREC_MASK                  BITS(5, 7)
#define IPV4_HDR_TOS_PREC_OFFSET                5
#define IPV4_HDR_IP_IDENTIFICATION_OFFSET       4
#define IPV4_HDR_IP_PROTOCOL_OFFSET             9
#define IPV4_HDR_IP_CSUM_OFFSET                 10
#define IPV4_HDR_IP_SRC_ADDR_OFFSET             12
#define IPV4_HDR_IP_DST_ADDR_OFFSET             16

#define IPV4_HDR_LEN                            20
#define IPV4_ADDR_LEN                           4

#define IPV6_HDR_IP_PROTOCOL_OFFSET             6
#define IPV6_HDR_IP_SRC_ADDR_OFFSET             8
#define IPV6_HDR_IP_DST_ADDR_OFFSET             24
#define IPV6_HDR_IP_DST_ADDR_MAC_HIGH_OFFSET    32
#define IPV6_HDR_IP_DST_ADDR_MAC_LOW_OFFSET     37
#define IPV6_PROTOCOL_ICMPV6                    0x3A

#define IPV6_HDR_TC_PREC_OFFSET                 1
#define IPV6_HDR_TC_PREC_MASK                   BITS(1, 3)
#define IPV6_HDR_PROTOCOL_OFFSET                6
#define IPV6_HDR_LEN                            40

#define IPV6_ADDR_LEN                           16

#define ICMPV6_TYPE_OFFSET                      0
#define ICMPV6_FLAG_OFFSET                      4
#define ICMPV6_TARGET_ADDR_OFFSET				8
#define ICMPV6_TARGET_LL_ADDR_TYPE_OFFSET		24
#define ICMPV6_TARGET_LL_ADDR_LEN_OFFSET		25
#define ICMPV6_TARGET_LL_ADDR_TA_OFFSET			26

#define ICMPV6_FLAG_ROUTER_BIT                  BIT(7)
#define ICMPV6_FLAG_SOLICITED_BIT               BIT(6)
#define ICMPV6_FLAG_OVERWRITE_BIT               BIT(5)
#define ICMPV6_TYPE_NEIGHBOR_SOLICITATION       0x87
#define ICMPV6_TYPE_NEIGHBOR_ADVERTISEMENT      0x88

#define TCP_HDR_TCP_CSUM_OFFSET                 16

#define UDP_HDR_SRC_PORT_OFFSET                 0
#define UDP_HDR_DST_PORT_OFFSET                 2
#define UDP_HDR_UDP_CSUM_OFFSET                 6

#define ARP_OPERATION_OFFSET                    6
#define ARP_SNEDER_MAC_OFFSET                   8
#define ARP_SENDER_IP_OFFSET                    14
#define ARP_TARGET_MAC_OFFSET                   18
#define ARP_TARGET_IP_OFFSET                    24
#define ARP_OPERATION_REQUEST                   0x0001
#define ARP_OPERATION_RESPONSE                  0x0002

#define LLC_LEN                                 8	/*                                 */

#define NULL_MAC_ADDR                           {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
#define BC_MAC_ADDR                             {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}


#if 1

#define ETH_HLEN                                14
#define ETH_TYPE_LEN_OFFSET                     12


#define IPVERSION                               4
#define IP_HEADER_LEN                           20

#define IPVH_VERSION_OFFSET                     4 //                  
#define IPVH_VERSION_MASK                       0xF0
#define IPTOS_PREC_OFFSET                       5
#define IPTOS_PREC_MASK                         0xE0

#define SOURCE_PORT_LEN                         2

#define LOOK_AHEAD_LEN                          (ETH_HLEN + IP_HEADER_LEN + SOURCE_PORT_LEN)



#endif 


/*                                    */
#define ETHER_HEADER_LEN                        14
#define ETHER_TYPE_LEN                          2
#define ETHER_MIN_PKT_SZ                        60
#define ETHER_MAX_PKT_SZ                        1514

#define ETHER_TYPE_LEN_OFFSET                   12

/*               */
#define ETH_802_1Q_HEADER_LEN                   4

/*                */
#define ETH_LLC_OFFSET                          (ETHER_HEADER_LEN)
#define ETH_LLC_LEN                             3
#define ETH_LLC_DSAP_SNAP                       0xAA
#define ETH_LLC_SSAP_SNAP                       0xAA
#define ETH_LLC_CONTROL_UNNUMBERED_INFORMATION  0x03
#define ETH_LLC                                 {ETH_LLC_DSAP_SNAP, ETH_LLC_SSAP_SNAP, ETH_LLC_CONTROL_UNNUMBERED_INFORMATION}

/*                */
#define ETH_SNAP_OFFSET                         (ETHER_HEADER_LEN + ETH_LLC_LEN)
#define ETH_SNAP_LEN                            5
#define ETH_SNAP_OUI_LEN                        3
#define ETH_SNAP_BT_SIG_OUI_0                   0x00
#define ETH_SNAP_BT_SIG_OUI_1                   0x19
#define ETH_SNAP_BT_SIG_OUI_2                   0x58
#define ETH_SNAP_BT_SIG_OUI                     {ETH_SNAP_BT_SIG_OUI_0 , ETH_SNAP_BT_SIG_OUI_1, ETH_SNAP_BT_SIG_OUI_2}

#define BOW_PROTOCOL_ID_SECURITY_FRAME          0x0003

/*                                            */
#define WLAN_MAC_HEADER_LEN                     24	/*                    */
#define WLAN_MAC_HEADER_A4_LEN                  30	/*                    */
#define WLAN_MAC_HEADER_QOS_LEN                 26	/*                      */
#define WLAN_MAC_HEADER_QOS_HTC_LEN             30	/*                              */
#define WLAN_MAC_HEADER_A4_QOS_LEN              32	/*                                    */
#define WLAN_MAC_HEADER_A4_QOS_HTC_LEN          36	/*                                         */
#define WLAN_MAC_MGMT_HEADER_LEN                24	/*                    */
#define WLAN_MAC_MGMT_HEADER_HTC_LEN            28	/*              */

#define QOS_CTRL_LEN                            2
#define HT_CTRL_LEN                             4

#define WLAN_MAC_CTS_ACK_LEN         WLAN_MAC_CTS_ACK_FRAME_HEADER_LEN + FCS_LEN

/*                                              */
#define MSDU_MAX_LENGTH                         2304

/*                           */
#define BC_BSSID                                BC_MAC_ADDR

/*                   */
#define FCS_LEN                                 4

/*                               */
#define DEFAULT_LISTEN_INTERVAL_BY_DTIM_PERIOD  2	/*                                */
#define DEFAULT_LISTEN_INTERVAL                 10

/*                                  */
#define BC_SSID                                 ""
#define BC_SSID_LEN                             0

/*                         */
#define RATE_1M                                 2	/*                       */
#define RATE_2M                                 4	/*    */
#define RATE_5_5M                               11	/*      */
#define RATE_11M                                22	/*     */
#define RATE_22M                                44	/*     */
#define RATE_33M                                66	/*     */
#define RATE_6M                                 12	/*    */
#define RATE_9M                                 18	/*    */
#define RATE_12M                                24	/*     */
#define RATE_18M                                36	/*     */
#define RATE_24M                                48	/*     */
#define RATE_36M                                72	/*     */
#define RATE_48M                                96	/*     */
#define RATE_54M                                108	/*     */
/*                                  */

#define RATE_VHT_PHY                            126	/*                                  */
#define RATE_HT_PHY                             127	/*                                  */
#define RATE_MASK                               BITS(0, 6)	/*                        */
#define RATE_BASIC_BIT                          BIT(7)	/*                                                        */

/*                           */
#define TKIP_MIC_LEN                            8

/*             */
#define DIFS                                    2	/*               */

/*                                         */
#define STA_STATE_1                             0	/*                       */
#define STA_STATE_2                             1	/*                           */
#define STA_STATE_3                             2	/*                             */

/*                                  */
#define NDBM_LOW_BOUND_FOR_RCPI                 110
#define RCPI_LOW_BOUND                          0
#define RCPI_HIGH_BOUND                         220
#define RCPI_MEASUREMENT_NOT_AVAILABLE          255


/*                     */
/*                                            */
#define SLOT_TIME_LONG                          20	/*                */
#define SLOT_TIME_SHORT                         9	/*                 */

#define SLOT_TIME_HR_DSSS                       SLOT_TIME_LONG	/*                   */
#define SLOT_TIME_OFDM                          SLOT_TIME_SHORT	/*                                */
#define SLOT_TIME_OFDM_10M_SPACING              13	/*                                */
#define SLOT_TIME_ERP_LONG                      SLOT_TIME_LONG	/*                         */
#define SLOT_TIME_ERP_SHORT                     SLOT_TIME_SHORT	/*                          */

/*                                                          */
#define CWMIN_OFDM                              15	/*                */
#define CWMAX_OFDM                              1023	/*                */

#define CWMIN_HR_DSSS                           31	/*                */
#define CWMAX_HR_DSSS                           1023	/*                */

#define CWMIN_ERP_0                             31	/*                                                      */
#define CWMIN_ERP_1                             15	/*                   */
#define CWMAX_ERP                               1023	/*                */

/*                                     */
/*                          */
#define SIFS_TIME_HR_DSSS                       10
/*                          */
#define SIFS_TIME_OFDM                          16
/*                          */
#define SIFS_TIME_ERP                           10

/*                                       */
#define CH_1                                    0x1
#define CH_2                                    0x2
#define CH_3                                    0x3
#define CH_4                                    0x4
#define CH_5                                    0x5
#define CH_6                                    0x6
#define CH_7                                    0x7
#define CH_8                                    0x8
#define CH_9                                    0x9
#define CH_10                                   0xa
#define CH_11                                   0xb
#define CH_12                                   0xc
#define CH_13                                   0xd
#define CH_14                                   0xe

#define MAXIMUM_OPERATION_CHANNEL_LIST          32


/*                                                    */
/*                                 */
#define DOT11_RTS_THRESHOLD_MIN                 0
#define DOT11_RTS_THRESHOLD_MAX                 2347	/*                  */
/*                                                                      */

#define DOT11_RTS_THRESHOLD_DEFAULT             \
	    DOT11_RTS_THRESHOLD_MAX

/*                                 */
#define DOT11_FRAGMENTATION_THRESHOLD_MIN       256
#define DOT11_FRAGMENTATION_THRESHOLD_MAX       2346	/*                  */
/*                                                                      */

#define DOT11_FRAGMENTATION_THRESHOLD_DEFAULT   \
	    DOT11_FRAGMENTATION_THRESHOLD_MAX

/*                                 */
#define DOT11_TRANSMIT_MSDU_LIFETIME_TU_MIN     1
#define DOT11_TRANSMIT_MSDU_LIFETIME_TU_MAX     0xFFFFffff
#define DOT11_TRANSMIT_MSDU_LIFETIME_TU_DEFAULT 4095	/*                   */
						     /*                              */

/*                                 */
#define DOT11_RECEIVE_LIFETIME_TU_MIN           1
#define DOT11_RECEIVE_LIFETIME_TU_MAX           0xFFFFffff
#define DOT11_RECEIVE_LIFETIME_TU_DEFAULT       4096	/*                   */

/*                                      */
#define DOT11_BEACON_PERIOD_MIN                 1	/*     */
#define DOT11_BEACON_PERIOD_MAX                 0xffff	/*     */
#define DOT11_BEACON_PERIOD_DEFAULT             100	/*     */

/*                                      */
#define DOT11_DTIM_PERIOD_MIN                   1	/*     */
#define DOT11_DTIM_PERIOD_MAX                   255	/*     */
#define DOT11_DTIM_PERIOD_DEFAULT               1	/*     */

/*                                       */
#define REGULATION_DOMAIN_FCC                   0x10	/*          */
#define REGULATION_DOMAIN_IC                    0x20	/*                    */
#define REGULATION_DOMAIN_ETSI                  0x30	/*               */
#define REGULATION_DOMAIN_SPAIN                 0x31	/*       */
#define REGULATION_DOMAIN_FRANCE                0x32	/*        */
#define REGULATION_DOMAIN_JAPAN                 0x40	/*             */
#define REGULATION_DOMAIN_CHINA                 0x50	/*       */
#define REGULATION_DOMAIN_OTHER                 0x00	/*       */



/*                                                                 */
/*                                                            */
#define MASK_FC_PROTOCOL_VER                    BITS(0, 1)
#define MASK_FC_TYPE                            BITS(2, 3)
#define MASK_FC_SUBTYPE                         BITS(4, 7)
#define MASK_FC_SUBTYPE_QOS_DATA                BIT(7)
#define MASK_FC_TO_DS                           BIT(8)
#define MASK_FC_FROM_DS                         BIT(9)
#define MASK_FC_MORE_FRAG                       BIT(10)
#define MASK_FC_RETRY                           BIT(11)
#define MASK_FC_PWR_MGT                         BIT(12)
#define MASK_FC_MORE_DATA                       BIT(13)
#define MASK_FC_PROTECTED_FRAME                 BIT(14)
#define MASK_FC_ORDER                           BIT(15)

#define MASK_FRAME_TYPE                         (MASK_FC_TYPE | MASK_FC_SUBTYPE)
#define MASK_TO_DS_FROM_DS                      (MASK_FC_TO_DS | MASK_FC_FROM_DS)

#define MAX_NUM_OF_FC_SUBTYPES                  16
#define OFFSET_OF_FC_SUBTYPE                    4


/*                                        */
#define MAC_FRAME_TYPE_MGT                      0
#define MAC_FRAME_TYPE_CTRL                     BIT(2)
#define MAC_FRAME_TYPE_DATA                     BIT(3)
#define MAC_FRAME_TYPE_QOS_DATA                 (MAC_FRAME_TYPE_DATA | MASK_FC_SUBTYPE_QOS_DATA)

#define MAC_FRAME_ASSOC_REQ                     (MAC_FRAME_TYPE_MGT | 0x0000)
#define MAC_FRAME_ASSOC_RSP                     (MAC_FRAME_TYPE_MGT | 0x0010)
#define MAC_FRAME_REASSOC_REQ                   (MAC_FRAME_TYPE_MGT | 0x0020)
#define MAC_FRAME_REASSOC_RSP                   (MAC_FRAME_TYPE_MGT | 0x0030)
#define MAC_FRAME_PROBE_REQ                     (MAC_FRAME_TYPE_MGT | 0x0040)
#define MAC_FRAME_PROBE_RSP                     (MAC_FRAME_TYPE_MGT | 0x0050)
#define MAC_FRAME_BEACON                        (MAC_FRAME_TYPE_MGT | 0x0080)
#define MAC_FRAME_ATIM                          (MAC_FRAME_TYPE_MGT | 0x0090)
#define MAC_FRAME_DISASSOC                      (MAC_FRAME_TYPE_MGT | 0x00A0)
#define MAC_FRAME_AUTH                          (MAC_FRAME_TYPE_MGT | 0x00B0)
#define MAC_FRAME_DEAUTH                        (MAC_FRAME_TYPE_MGT | 0x00C0)
#define MAC_FRAME_ACTION                        (MAC_FRAME_TYPE_MGT | 0x00D0)
#define MAC_FRAME_ACTION_NO_ACK                 (MAC_FRAME_TYPE_MGT | 0x00E0)


#define MAC_FRAME_CONTRL_WRAPPER                (MAC_FRAME_TYPE_CTRL | 0x0070)
#define MAC_FRAME_BLOCK_ACK_REQ                 (MAC_FRAME_TYPE_CTRL | 0x0080)
#define MAC_FRAME_BLOCK_ACK                     (MAC_FRAME_TYPE_CTRL | 0x0090)
#define MAC_FRAME_PS_POLL                       (MAC_FRAME_TYPE_CTRL | 0x00A0)
#define MAC_FRAME_RTS                           (MAC_FRAME_TYPE_CTRL | 0x00B0)
#define MAC_FRAME_CTS                           (MAC_FRAME_TYPE_CTRL | 0x00C0)
#define MAC_FRAME_ACK                           (MAC_FRAME_TYPE_CTRL | 0x00D0)
#define MAC_FRAME_CF_END                        (MAC_FRAME_TYPE_CTRL | 0x00E0)
#define MAC_FRAME_CF_END_CF_ACK                 (MAC_FRAME_TYPE_CTRL | 0x00F0)

#define MAC_FRAME_DATA                          (MAC_FRAME_TYPE_DATA | 0x0000)
#define MAC_FRAME_DATA_CF_ACK                   (MAC_FRAME_TYPE_DATA | 0x0010)
#define MAC_FRAME_DATA_CF_POLL                  (MAC_FRAME_TYPE_DATA | 0x0020)
#define MAC_FRAME_DATA_CF_ACK_CF_POLL           (MAC_FRAME_TYPE_DATA | 0x0030)
#define MAC_FRAME_NULL                          (MAC_FRAME_TYPE_DATA | 0x0040)
#define MAC_FRAME_CF_ACK                        (MAC_FRAME_TYPE_DATA | 0x0050)
#define MAC_FRAME_CF_POLL                       (MAC_FRAME_TYPE_DATA | 0x0060)
#define MAC_FRAME_CF_ACK_CF_POLL                (MAC_FRAME_TYPE_DATA | 0x0070)
#define MAC_FRAME_QOS_DATA                      (MAC_FRAME_TYPE_DATA | 0x0080)
#define MAC_FRAME_QOS_DATA_CF_ACK               (MAC_FRAME_TYPE_DATA | 0x0090)
#define MAC_FRAME_QOS_DATA_CF_POLL              (MAC_FRAME_TYPE_DATA | 0x00A0)
#define MAC_FRAME_QOS_DATA_CF_ACK_CF_POLL       (MAC_FRAME_TYPE_DATA | 0x00B0)
#define MAC_FRAME_QOS_NULL                      (MAC_FRAME_TYPE_DATA | 0x00C0)
#define MAC_FRAME_QOS_CF_POLL                   (MAC_FRAME_TYPE_DATA | 0x00E0)
#define MAC_FRAME_QOS_CF_ACK_CF_POLL            (MAC_FRAME_TYPE_DATA | 0x00F0)

/*                                                         */
#define MASK_DI_DURATION                        BITS(0, 14)
#define MASK_DI_AID                             BITS(0, 13)
#define MASK_DI_AID_MSB                         BITS(14, 15)
#define MASK_DI_CFP_FIXED_VALUE                 BIT(15)

/*                                                               */
#define MASK_SC_SEQ_NUM                         BITS(4, 15)
#define MASK_SC_SEQ_NUM_OFFSET                  4
#define MASK_SC_FRAG_NUM                        BITS(0, 3)
#define INVALID_SEQ_CTRL_NUM                    0x000F	/*                       
                                    
        */

/*                           */
#define TID_NUM                                 16
#define TID_MASK                                BITS(0, 3)
#define EOSP                                    BIT(4)
#define ACK_POLICY                              BITS(5, 6)
#define A_MSDU_PRESENT                          BIT(7)

#define MASK_QC_TID                  BITS(0, 3)
#define MASK_QC_EOSP                 BIT(4)
#define MASK_QC_EOSP_OFFSET          4
#define MASK_QC_ACK_POLICY           BITS(5, 6)
#define MASK_QC_ACK_POLICY_OFFSET    5
#define MASK_QC_A_MSDU_PRESENT       BIT(7)

/*                           */
#define HT_CTRL_LINK_ADAPTATION_CTRL            BITS(0, 15)
#define HT_CTRL_CALIBRATION_POSITION            BITS(16, 17)
#define HT_CTRL_CALIBRATION_SEQUENCE            BITS(18, 19)
#define HT_CTRL_CSI_STEERING                    BITS(22, 23)
#define HT_CTRL_NDP_ANNOUNCEMENT                BIT(24)
#define HT_CTRL_AC_CONSTRAINT                   BIT(30)
#define HT_CTRL_RDG_MORE_PPDU                   BIT(31)

#define LINK_ADAPTATION_CTRL_TRQ                BIT(1)
#define LINK_ADAPTATION_CTRL_MAI_MRQ            BIT(2)
#define LINK_ADAPTATION_CTRL_MAI_MSI            BITS(3, 5)
#define LINK_ADAPTATION_CTRL_MFSI               BITS(6, 8)
#define LINK_ADAPTATION_CTRL_MFB_ASELC_CMD      BITS(9, 11)
#define LINK_ADAPTATION_CTRL_MFB_ASELC_DATA     BITS(12, 15)

/*                              */
#define ACK_POLICY_NORMAL_ACK_IMPLICIT_BA_REQ 0
#define ACK_POLICY_NO_ACK 1
#define ACK_POLICY_NO_EXPLICIT_ACK_PSMP_ACK 2
#define ACK_POLICY_BA 3

/*                   */
#define FCS_LEN                                 4

/*                                            */
#define PSPOLL_FRAME_LEN                        16	/*         */

/*             */
#define OFFSET_BAR_SSC_SN                       4

/*                           */
#define TKIP_MIC_LEN                            8


#define BA_POLICY_IMMEDIATE                     BIT(1)

/*                                           */
#define BA_START_SEQ_CTL_FRAG_NUM               BITS(0, 3)
#define BA_START_SEQ_CTL_SSN                    BITS(4, 15)

/*                   */
#define BAR_CONTROL_NO_ACK_POLICY               BIT(0)
#define BAR_CONTROL_MULTI_TID                   BIT(1)
#define BAR_CONTROL_COMPRESSED_BA               BIT(2)
#define BAR_CONTROL_TID_INFO                    BITS(12, 15)
#define BAR_CONTROL_TID_INFO_OFFSET             12

/*           */
#define BAR_INFO_TID_VALUE                      BITS(12, 15)

#define BAR_COMPRESSED_VARIANT_FRAME_LEN        (16 + 4)

/*                                                                 */
/*                                                       */
/*                                               */
#define AUTH_ALGORITHM_NUM_FIELD_LEN                2

#define AUTH_ALGORITHM_NUM_OPEN_SYSTEM              0	/*             */
#define AUTH_ALGORITHM_NUM_SHARED_KEY               1	/*            */
#define AUTH_ALGORITHM_NUM_FAST_BSS_TRANSITION      2	/*                     */

/*                                                          */
#define AUTH_TRANSACTION_SEQENCE_NUM_FIELD_LEN      2
#define AUTH_TRANSACTION_SEQ_1                      1
#define AUTH_TRANSACTION_SEQ_2                      2
#define AUTH_TRANSACTION_SEQ_3                      3
#define AUTH_TRANSACTION_SEQ_4                      4

/*                               */
#define BEACON_INTERVAL_FIELD_LEN                   2

/*                                      */
#define CAP_INFO_FIELD_LEN                          2
#define CAP_INFO_ESS                                BIT(0)
#define CAP_INFO_IBSS                               BIT(1)
#define CAP_INFO_BSS_TYPE                           (CAP_INFO_ESS | CAP_INFO_IBSS)
#define CAP_INFO_CF_POLLABLE                        BIT(2)
#define CAP_INFO_CF_POLL_REQ                        BIT(3)
#define CAP_INFO_CF                                 (CAP_INFO_CF_POLLABLE | CAP_INFO_CF_POLL_REQ)
#define CAP_INFO_PRIVACY                            BIT(4)
#define CAP_INFO_SHORT_PREAMBLE                     BIT(5)
#define CAP_INFO_PBCC                               BIT(6)
#define CAP_INFO_CH_AGILITY                         BIT(7)
#define CAP_INFO_SPEC_MGT                           BIT(8)
#define CAP_INFO_QOS                                BIT(9)
#define CAP_INFO_SHORT_SLOT_TIME                    BIT(10)
#define CAP_INFO_APSD                               BIT(11)
#define CAP_INFO_RESERVED                           BIT(12)
#define CAP_INFO_DSSS_OFDM                          BIT(13)
#define CAP_INFO_DELAYED_BLOCK_ACK                  BIT(14)
#define CAP_INFO_IMM_BLOCK_ACK                      BIT(15)
/*                                                        */
/*                      */
#define CAP_CF_STA_NOT_POLLABLE                     0x0000
/*                                                         */
#define CAP_CF_STA_NOT_ON_LIST                      CAP_INFO_CF_POLL_REQ
/*                                                     */
#define CAP_CF_STA_ON_LIST                          CAP_INFO_CF_POLLABLE
/*                                                 */
#define CAP_CF_STA_NEVER_POLLED                     (CAP_INFO_CF_POLLABLE | CAP_INFO_CF_POLL_REQ)

/*                                                       */
/*                               */
#define CAP_CF_AP_NO_PC                             0x0000
/*                                             */
#define CAP_CF_AP_DELIVERY_ONLY                     CAP_INFO_CF_POLL_REQ
/*                                       */
#define CAP_CF_AP_DELIVERY_POLLING                  CAP_INFO_CF_POLLABLE

/*                                  */
#define CURR_AP_ADDR_FIELD_LEN                      MAC_ADDR_LEN

/*                               */
#define LISTEN_INTERVAL_FIELD_LEN                   2

/*                           */
#define REASON_CODE_FIELD_LEN                       2

#define REASON_CODE_RESERVED                        0	/*         */
#define REASON_CODE_UNSPECIFIED                     1	/*                    */
#define REASON_CODE_PREV_AUTH_INVALID               2	/*                               */
#define REASON_CODE_DEAUTH_LEAVING_BSS              3	/*                                           */
#define REASON_CODE_DISASSOC_INACTIVITY             4	/*                            */
#define REASON_CODE_DISASSOC_AP_OVERLOAD            5	/*                                                        */
#define REASON_CODE_CLASS_2_ERR                     6	/*                                   */
#define REASON_CODE_CLASS_3_ERR                     7	/*                                    */
#define REASON_CODE_DISASSOC_LEAVING_BSS            8	/*                                             */
#define REASON_CODE_ASSOC_BEFORE_AUTH               9	/*                                                          */
#define REASON_CODE_DISASSOC_PWR_CAP_UNACCEPTABLE   10	/*                                                               */
#define REASON_CODE_DISASSOC_SUP_CHS_UNACCEPTABLE   11	/*                                                                 */
#define REASON_CODE_INVALID_INFO_ELEM               13	/*                             */
#define REASON_CODE_MIC_FAILURE                     14	/*             */
#define REASON_CODE_4_WAY_HANDSHAKE_TIMEOUT         15	/*                         */
#define REASON_CODE_GROUP_KEY_UPDATE_TIMEOUT        16	/*                          */
#define REASON_CODE_DIFFERENT_INFO_ELEM             17	/*                                                                                             */
#define REASON_CODE_MULTICAST_CIPHER_NOT_VALID      18	/*                               */
#define REASON_CODE_UNICAST_CIPHER_NOT_VALID        19	/*                             */
#define REASON_CODE_AKMP_NOT_VALID                  20	/*                   */
#define REASON_CODE_UNSUPPORTED_RSNE_VERSION        21	/*                          */
#define REASON_CODE_INVALID_RSNE_CAPABILITIES       22	/*                           */
#define REASON_CODE_IEEE_802_1X_AUTH_FAILED         23	/*                                   */
#define REASON_CODE_CIPHER_REJECT_SEC_POLICY        24	/*                                                      */
#define REASON_CODE_DISASSOC_UNSPECIFIED_QOS        32	/*                                              */
#define REASON_CODE_DISASSOC_LACK_OF_BANDWIDTH      33	/*                                                               */
#define REASON_CODE_DISASSOC_ACK_LOST_POOR_CHANNEL  34	/*                                                                                            */
#define REASON_CODE_DISASSOC_TX_OUTSIDE_TXOP_LIMIT  35	/*                                                                       */
#define REASON_CODE_PEER_WHILE_LEAVING              36	/*                                       */
#define REASON_CODE_PEER_REFUSE_DLP                 37	/*                                          */
#define REASON_CODE_PEER_SETUP_REQUIRED             38	/*                                        */
#define REASON_CODE_PEER_TIME_OUT                   39	/*          */
#define REASON_CODE_PEER_CIPHER_UNSUPPORTED         45	/*                                                  */
#define REASON_CODE_BEACON_TIMEOUT					100 /*                                         */
/*                   */
#define AID_FIELD_LEN                               2
#define AID_MASK                                    BITS(0, 13)
#define AID_MSB                                     BITS(14, 15)
#define AID_MIN_VALUE                               1
#define AID_MAX_VALUE                               2007

/*                           */
#define STATUS_CODE_FIELD_LEN                       2

#define STATUS_CODE_RESERVED                        0	/*                            */
#define STATUS_CODE_SUCCESSFUL                      0	/*            */
#define STATUS_CODE_UNSPECIFIED_FAILURE             1	/*                     */
#define STATUS_CODE_CAP_NOT_SUPPORTED               10	/*                                                        */
#define STATUS_CODE_REASSOC_DENIED_WITHOUT_ASSOC    11	/*                                                              */
#define STATUS_CODE_ASSOC_DENIED_OUTSIDE_STANDARD   12	/*                                                           */
#define STATUS_CODE_AUTH_ALGORITHM_NOT_SUPPORTED    13	/*                                                              */
#define STATUS_CODE_AUTH_OUT_OF_SEQ                 14	/*                                                                    */
#define STATUS_CODE_AUTH_REJECTED_CHAL_FAIL         15	/*                                            */
#define STATUS_CODE_AUTH_REJECTED_TIMEOUT           16	/*                                                                 */
#define STATUS_CODE_ASSOC_DENIED_AP_OVERLOAD        17	/*                                                                   */
#define STATUS_CODE_ASSOC_DENIED_RATE_NOT_SUPPORTED 18	/*                                                                      */
#define STATUS_CODE_ASSOC_DENIED_NO_SHORT_PREAMBLE  19	/*                                                                  */
#define STATUS_CODE_ASSOC_DENIED_NO_PBCC            20	/*                                                        */
#define STATUS_CODE_ASSOC_DENIED_NO_CH_AGILITY      21	/*                                                                   */
#define STATUS_CODE_ASSOC_REJECTED_NO_SPEC_MGT      22	/*                                                            */
#define STATUS_CODE_ASSOC_REJECTED_PWR_CAP          23	/*                                                                     */
#define STATUS_CODE_ASSOC_REJECTED_SUP_CHS          24	/*                                                                       */
#define STATUS_CODE_ASSOC_DENIED_NO_SHORT_SLOT_TIME 25	/*                                                                   */
#define STATUS_CODE_ASSOC_DENIED_NO_DSSS_OFDM       26	/*                                                             */
#if CFG_SUPPORT_802_11W
#define STATUS_CODE_ASSOC_REJECTED_TEMPORARILY      30	/*                                                 */
#define STATUS_CODE_ROBUST_MGMT_FRAME_POLICY_VIOLATION 31	/*                                                         */
#endif
#define STATUS_CODE_UNSPECIFIED_QOS_FAILURE         32	/*                                  */
#define STATUS_CODE_ASSOC_DENIED_BANDWIDTH          33	/*                                                                   */
#define STATUS_CODE_ASSOC_DENIED_POOR_CHANNEL       34	/*                                                                               */
#define STATUS_CODE_ASSOC_DENIED_NO_QOS_FACILITY    35	/*                                                                */
#define STATUS_CODE_REQ_DECLINED                    37	/*                           */
#define STATUS_CODE_REQ_INVALID_PARAMETER_VALUE     38	/*                                                                               */
#define STATUS_CODE_REQ_NOT_HONORED_TSPEC           39	/*                                                                             */
#define STATUS_CODE_INVALID_INFO_ELEMENT            40	/*                             */
#define STATUS_CODE_INVALID_GROUP_CIPHER            41	/*                      */
#define STATUS_CODE_INVALID_PAIRWISE_CIPHER         42	/*                         */
#define STATUS_CODE_INVALID_AKMP                    43	/*              */
#define STATUS_CODE_UNSUPPORTED_RSN_IE_VERSION      44	/*                                             */
#define STATUS_CODE_INVALID_RSN_IE_CAP              45	/*                                              */
#define STATUS_CODE_CIPHER_SUITE_REJECTED           46	/*                                                  */
#define STATUS_CODE_REQ_NOT_HONORED_TS_DELAY        47	/*                                                                                 */
#define STATUS_CODE_DIRECT_LINK_NOT_ALLOWED         48	/*                                                 */
#define STATUS_CODE_DESTINATION_STA_NOT_PRESENT     49	/*                                                 */
#define STATUS_CODE_DESTINATION_STA_NOT_QSTA        50	/*                               */
#define STATUS_CODE_ASSOC_DENIED_LARGE_LIS_INTERVAL 51	/*                                                            */

/*                                                         */
#define STATUS_CODE_JOIN_FAILURE                    0xFFF0	/*              */
#define STATUS_CODE_JOIN_TIMEOUT                    0xFFF1	/*              */
#define STATUS_CODE_AUTH_TIMEOUT                    0xFFF2	/*                        */
#define STATUS_CODE_ASSOC_TIMEOUT                   0xFFF3	/*                         */
#define STATUS_CODE_CCX_CCKM_REASSOC_FAILURE        0xFFF4	/*                                */


/*                          */
#define TIMESTAMP_FIELD_LEN                         8

/*                                   */
#define CATEGORY_SPEC_MGT                           0
#define CATEGORY_QOS_ACTION                         1	/*            */
#define CATEGORY_DLS_ACTION                         2	/*                                   */
#define CATEGORY_BLOCK_ACK_ACTION                   3	/*                  */
#define CATEGORY_PUBLIC_ACTION                      4	/*               */
#define CATEGORY_RM_ACTION                          5	/*                          */
#define CATEGORY_HT_ACTION                          7
#if CFG_SUPPORT_802_11W
#define CATEGORY_SA_QUERY_ACTION                    8
#define CATEGORY_PROTECTED_DUAL_OF_PUBLIC_ACTION    9
#endif
#define CATEGORY_WNM_ACTION                         10  /*                                     */
#define CATEGORY_UNPROTECTED_WNM_ACTION             11  /*                                     */
#define CATEGORY_WME_MGT_NOTIFICATION               17  /*                             */

#define CATEGORY_VHT_ACTION                         21  /*           */                         


#if CFG_SUPPORT_802_11W
#define CATEGORY_VENDOR_SPECIFIC_ACTION_PROTECTED   126
#endif
#define CATEGORY_VENDOR_SPECIFIC_ACTION             127


/*                                        */
#define BA_PARAM_SET_ACK_POLICY_MASK                BIT(1)
#define BA_PARAM_SET_ACK_POLICY_MASK_OFFSET         1
#define BA_PARAM_SET_TID_MASK                       BITS(2, 5)
#define BA_PARAM_SET_TID_MASK_OFFSET                2
#define BA_PARAM_SET_BUFFER_SIZE_MASK               BITS(6, 15)
#define BA_PARAM_SET_BUFFER_SIZE_MASK_OFFSET        6

#define BA_PARAM_SET_ACK_POLICY_IMMEDIATE_BA        1
#define BA_PARAM_SET_ACK_POLICY_DELAYED_BA          0


/*                                                                */
/*                                           */
#define ELEM_HDR_LEN                                2

#define ELEM_ID_SSID                                0	/*      */
#define ELEM_ID_SUP_RATES                           1	/*                 */
#define ELEM_ID_FH_PARAM_SET                        2	/*                  */
#define ELEM_ID_DS_PARAM_SET                        3	/*                  */
#define ELEM_ID_CF_PARAM_SET                        4	/*                  */
#define ELEM_ID_TIM                                 5	/*     */
#define ELEM_ID_IBSS_PARAM_SET                      6	/*                    */
#define ELEM_ID_COUNTRY_INFO                        7	/*                     */
#define ELEM_ID_HOPPING_PATTERN_PARAM               8	/*                            */
#define ELEM_ID_HOPPING_PATTERN_TABLE               9	/*                       */
#define ELEM_ID_REQUEST                             10	/*         */
#define ELEM_ID_BSS_LOAD                            11	/*          */
#define ELEM_ID_EDCA_PARAM_SET                      12	/*                    */
#define ELEM_ID_TSPEC                               13	/*                               */
#define ELEM_ID_TCLAS                               14	/*                                */
#define ELEM_ID_SCHEDULE                            15	/*          */
#define ELEM_ID_CHALLENGE_TEXT                      16	/*                */

#define ELEM_ID_PWR_CONSTRAINT                      32	/*                  */
#define ELEM_ID_PWR_CAP                             33	/*                  */
#define ELEM_ID_TPC_REQ                             34	/*             */
#define ELEM_ID_TPC_REPORT                          35	/*            */
#define ELEM_ID_SUP_CHS                             36	/*                    */
#define ELEM_ID_CH_SW_ANNOUNCEMENT                  37	/*                             */
#define ELEM_ID_MEASUREMENT_REQ                     38	/*                     */
#define ELEM_ID_MEASUREMENT_REPORT                  39	/*                    */
#define ELEM_ID_QUIET                               40	/*       */
#define ELEM_ID_IBSS_DFS                            41	/*          */
#define ELEM_ID_ERP_INFO                            42	/*                 */
#define ELEM_ID_TS_DELAY                            43	/*          */
#define ELEM_ID_TCLAS_PROCESSING                    44	/*                  */
#define ELEM_ID_HT_CAP                              45	/*                            */
#define ELEM_ID_QOS_CAP                             46	/*                */
#define ELEM_ID_RSN                                 48	/*        */
#define ELEM_ID_EXTENDED_SUP_RATES                  50	/*                          */
#if CFG_SUPPORT_802_11W
#define ELEM_ID_TIMEOUT_INTERVAL                    56	/*                             */
#endif
#define ELEM_ID_SUP_OPERATING_CLASS					59	/*                             */



#define ELEM_ID_HT_OP                               61	/*              */
#define ELEM_ID_SCO                                 62	/*                          */
#define ELEM_ID_RRM_ENABLED_CAP                     70	/*                                                */
#define ELEM_ID_20_40_BSS_COEXISTENCE               72	/*                       */
#define ELEM_ID_20_40_INTOLERANT_CHNL_REPORT        73	/*                                     */
#define ELEM_ID_OBSS_SCAN_PARAMS                    74	/*                                 */
#define ELEM_ID_EXTENDED_CAP                        127	/*                       */

#define ELEM_ID_INTERWORKING                        107	/*                                    */
#define ELEM_ID_ADVERTISEMENT_PROTOCOL              108	/*                        */
#define ELEM_ID_ROAMING_CONSORTIUM                  111	/*                    */
#define ELEM_ID_EXTENDED_CAP                        127	/*                       */

#define ELEM_ID_VENDOR                              221	/*                    */
#define ELEM_ID_WPA                                 ELEM_ID_VENDOR	/*        */
#define ELEM_ID_WMM                                 ELEM_ID_VENDOR	/*        */
#define ELEM_ID_P2P                                 ELEM_ID_VENDOR	/*             */
#define ELEM_ID_WSC                                 ELEM_ID_VENDOR	/*        */

#define ELEM_ID_VHT_CAP                             191  /*                             */
#define ELEM_ID_VHT_OP                              192  /*                          */
#define ELEM_ID_WIDE_BAND_CHANNEL_SWITCH            194  /*                             */
#define ELEM_ID_OP_MODE                             199  /*                             */
#define ELEM_ID_RESERVED                            255 /*          */


/*                      */
#define ELEM_MAX_LEN_SSID                           32

/*                         */
#define ELEM_MAX_LEN_SUP_RATES                      8

/*                          */
#define ELEM_MAX_LEN_DS_PARAMETER_SET               1

/*                          */
#define ELEM_CF_PARM_LEN                            8

/*             */
#define ELEM_MIX_LEN_TIM                            4
#define ELEM_MAX_LEN_TIM                            254

/*                                    */
#define ELEM_MAX_LEN_IBSS_PARAMETER_SET             2

/*                                */
#define ELEM_MIN_LEN_CHALLENGE_TEXT                 1
#define ELEM_MAX_LEN_CHALLENGE_TEXT                 253

/*                                     */
/*                                                                                         */
#define ELEM_MIN_LEN_COUNTRY_INFO                   6

#define ELEM_ID_COUNTRY_INFO_TRIPLET_LEN_FIXED              3
#define ELEM_ID_COUNTRY_INFO_SUBBAND_TRIPLET_LEN_FIXED      3
#define ELEM_ID_COUNTRY_INFO_REGULATORY_TRIPLET_LEN_FIXED   3


/*                                  */
#define ELEM_MAX_LEN_ERP                            1
/*                                        */
#define ERP_INFO_NON_ERP_PRESENT                    BIT(0)	/*                    */
#define ERP_INFO_USE_PROTECTION                     BIT(1)	/*                    */
#define ERP_INFO_BARKER_PREAMBLE_MODE               BIT(2)	/*                          */



#define ELEM_MAX_LEN_SUPPPORTED_CHANNELS            9

/*                                   */
#define ELEM_MAX_LEN_EXTENDED_SUP_RATES             255

/*                                      */
#define ELEM_RM_TYPE_BASIC_REQ                      0
#define ELEM_RM_TYPE_CCA_REQ                        1
#define ELEM_RM_TYPE_RPI_HISTOGRAM_REQ              2
#define ELEM_RM_TYPE_CHNL_LOAD_REQ                  3
#define ELEM_RM_TYPE_NOISE_HISTOGRAM_REQ            4
#define ELEM_RM_TYPE_BEACON_REQ                     5
#define ELEM_RM_TYPE_FRAME_REQ                      6
#define ELEM_RM_TYPE_STA_STATISTICS_REQ             7
#define ELEM_RM_TYPE_LCI_REQ                        8
#define ELEM_RM_TYPE_TS_REQ                         9
#define ELEM_RM_TYPE_MEASURE_PAUSE_REQ              255

/*                                     */
#define ELEM_RM_TYPE_BASIC_REPORT                   0
#define ELEM_RM_TYPE_CCA_REPORT                     1
#define ELEM_RM_TYPE_RPI_HISTOGRAM_REPORT           2
#define ELEM_RM_TYPE_CHNL_LOAD_REPORT               3
#define ELEM_RM_TYPE_NOISE_HISTOGRAM_REPORT         4
#define ELEM_RM_TYPE_BEACON_REPORT                  5
#define ELEM_RM_TYPE_FRAME_REPORT                   6
#define ELEM_RM_TYPE_STA_STATISTICS_REPORT          7
#define ELEM_RM_TYPE_LCI_REPORT                     8
#define ELEM_RM_TYPE_TS_REPORT                      9

/*                                  */
#define ELEM_MAX_LEN_WPA                            34	/*                                        */
#define ELEM_MAX_LEN_RSN                            38	/*                                        */
#define ELEM_MAX_LEN_WAPI                           38	/*                                       */
#define ELEM_MAX_LEN_WSC                            200	/*                                       */

#if CFG_SUPPORT_802_11W
#define ELEM_WPA_CAP_MFPR                           BIT(6)
#define ELEM_WPA_CAP_MFPC                           BIT(7)
#endif

/*                                                    */
#define ELEM_EXT_CAP_20_40_COEXIST_SUPPORT          BIT(0)
#define ELEM_EXT_CAP_PSMP_CAP                       BIT(4)
#define ELEM_EXT_CAP_SERVICE_INTERVAL_GRANULARITY   BIT(5)
#define ELEM_EXT_CAP_SCHEDULE_PSMP                  BIT(6)

#define ELEM_EXT_CAP_BSS_TRANSITION_BIT             19
#define ELEM_EXT_CAP_UTC_TSF_OFFSET_BIT             27
#define ELEM_EXT_CAP_INTERWORKING_BIT               31
#define ELEM_EXT_CAP_WNM_NOTIFICATION_BIT           46
#define ELEM_EXT_CAP_OP_MODE_NOTIFICATION_BIT       62

#define ELEM_MAX_LEN_EXT_CAP                        (8)

/*                        */
#define TS_INFO_TRAFFIC_TYPE_MASK                   BIT(0)	/*                                             */
#define TS_INFO_TID_OFFSET                          1
#define TS_INFO_TID_MASK                            BITS(1, 4)
#define TS_INFO_DIRECTION_OFFSET                    5
#define TS_INFO_DIRECTION_MASK                      BITS(5, 6)
#define TS_INFO_ACCESS_POLICY_OFFSET                7
#define TS_INFO_ACCESS_POLICY_MASK                  BITS(7, 8)
#define TS_INFO_AGGREGATION_MASK                    BIT(9)	/*        */
#define TS_INFO_APSD_MASK                           BIT(10)
#define TS_INFO_UP_OFFSET                           11
#define TS_INFO_UP_MASK                             BITS(11, 13)
#define TS_INFO_ACK_POLICY_OFFSET                   14
#define TS_INFO_ACK_POLICY_MASK                     BITS(14, 15)
#define TS_INFO_SCHEDULE_MASK                       16

/*                                  */
#define ELEM_MAX_LEN_HT_CAP                         (28 - ELEM_HDR_LEN)	/*                       */

/*                                       */
#define HT_CAP_INFO_LDPC_CAP                        BIT(0)
#define HT_CAP_INFO_SUP_CHNL_WIDTH                  BIT(1)
#define HT_CAP_INFO_SM_POWER_SAVE                   BITS(2, 3)
#define HT_CAP_INFO_HT_GF                           BIT(4)
#define HT_CAP_INFO_SHORT_GI_20M                    BIT(5)
#define HT_CAP_INFO_SHORT_GI_40M                    BIT(6)
#define HT_CAP_INFO_TX_STBC                         BIT(7)
#define HT_CAP_INFO_RX_STBC                         BITS(8, 9)
#define HT_CAP_INFO_HT_DELAYED_BA                   BIT(10)
#define HT_CAP_INFO_MAX_AMSDU_LEN                   BIT(11)
#define HT_CAP_INFO_DSSS_CCK_IN_40M                 BIT(12)
#define HT_CAP_INFO_40M_INTOLERANT                  BIT(14)
#define HT_CAP_INFO_LSIG_TXOP_SUPPORT               BIT(15)

#define HT_CAP_INFO_RX_STBC_NO_SUPPORTED            0
#define HT_CAP_INFO_RX_STBC_1_SS                    BIT(8)
#define HT_CAP_INFO_RX_STBC_2_SS                    BIT(9)
#define HT_CAP_INFO_RX_STBC_3_SS                    HT_CAP_INFO_RX_STBC


#define ELEM_MAX_LEN_VHT_CAP                         (14 - ELEM_HDR_LEN)	/*                        */
/*                                 */
#define ELEM_MAX_LEN_VHT_OP                          (7 - ELEM_HDR_LEN)	/*                       */

/*                                       */

/*                                       */
#define VHT_CAP_INFO_MAX_MPDU_LEN_3K							0
#define VHT_CAP_INFO_MAX_MPDU_LEN_8K							BIT(0)
#define VHT_CAP_INFO_MAX_MPDU_LEN_11K						    BIT(1)

#define VHT_CAP_INFO_MAX_SUP_CHANNEL_WIDTH_SET_NONE			0
#define VHT_CAP_INFO_MAX_SUP_CHANNEL_WIDTH_SET_160				BIT(2)
#define VHT_CAP_INFO_MAX_SUP_CHANNEL_WIDTH_SET_160_80P80		BIT(3)

#define VHT_CAP_INFO_RX_LDPC									BIT(4)
#define VHT_CAP_INFO_SHORT_GI_80								BIT(5)
#define VHT_CAP_INFO_SHORT_GI_160_80P80							BIT(6)
#define VHT_CAP_INFO_TX_STBC									BIT(7)

#define VHT_CAP_INFO_RX_STBC_NONE								0
#define VHT_CAP_INFO_RX_STBC_ONE_STREAM							BIT(8)
#define VHT_CAP_INFO_RX_STBC_TWO_STREAM							BIT(9)
#define VHT_CAP_INFO_RX_STBC_THREE_STREAM						BITS(8, 9)
#define VHT_CAP_INFO_RX_STBC_FOUR_STREAM						BIT(10)

#define VHT_CAP_INFO_SU_BEAMFORMER_CAPABLE						BIT(11)
#define VHT_CAP_INFO_SU_BEAMFORMEE_CAPABLE						BIT(12)

#define VHT_CAP_INFO_COMPRESSED_STEERING_NUMBER_OF_BEAMFORMER_ANTENNAS_SUPPOERTED BITS(13, 15)
#define VHT_CAP_INFO_COMPRESSED_STEERING_NUMBER_OF_BEAMFORMER_ANTENNAS_4_SUPPOERTED BITS(13, 14)

#define VHT_CAP_INFO_NUMBER_OF_SOUNDING_DIMENSIONS				BITS(16, 18)

#define	VHT_CAP_INFO_MU_BEAMFOMER_CAPABLE						BIT(19)
#define VHT_CAP_INFO_MU_BEAMFOMEE_CAPABLE						BIT(20)
#define VHT_CAP_INFO_VHT_TXOP_PS								BIT(21)
#define VHT_CAP_INFO_HTC_VHT_CAPABLE							BIT(22)

#define VHT_CAP_INFO_MAX_AMPDU_LENGTH_OFFSET                    23

#define VHT_CAP_INFO_VHT_LINK_ADAPTATION_CAPABLE_NOFEEDBACK				0
#define VHT_CAP_INFO_VHT_LINK_ADAPTATION_CAPABLE_UNSOLICITED				BITS(27)
#define VHT_CAP_INFO_VHT_LINK_ADAPTATION_CAPABLE_BOTH						BITS(26, 27)

#define VHT_CAP_INFO_RX_ANTENNA_PATTERN_CONSISTENCY			BIT(28)
#define VHT_CAP_INFO_TX_ANTENNA_PATTERN_CONSISTENCY			BIT(29)

#define VHT_CAP_INFO_MCS_MAP_MCS7								0
#define VHT_CAP_INFO_MCS_MAP_MCS8								BIT(0)
#define VHT_CAP_INFO_MCS_MAP_MCS9								(BIT(1) | ~BIT(0))
#define VHT_CPA_INFO_MCS_NOT_SUPPORTED							BITS(0, 1)

#define VHT_CAP_INFO_MCS_1SS_OFFSET						0
#define VHT_CAP_INFO_MCS_2SS_OFFSET						2
#define VHT_CAP_INFO_MCS_3SS_OFFSET						4
#define VHT_CAP_INFO_MCS_4SS_OFFSET						6
#define VHT_CAP_INFO_MCS_5SS_OFFSET						8
#define VHT_CAP_INFO_MCS_6SS_OFFSET						10
#define VHT_CAP_INFO_MCS_7SS_OFFSET						12
#define VHT_CAP_INFO_MCS_8SS_OFFSET						14

#define VHT_OP_CHANNEL_WIDTH_20_40						0
#define VHT_OP_CHANNEL_WIDTH_80							1
#define VHT_OP_CHANNEL_WIDTH_160						2
#define VHT_OP_CHANNEL_WIDTH_80P80						3

/*                             */
#define VHT_OP_MODE_CHANNEL_WIDTH                   BITS(0, 1)
#define VHT_OP_MODE_RX_NSS                          BITS(4, 6)
#define VHT_OP_MODE_RX_NSS_TYPE                     BIT(7)

#define VHT_OP_MODE_CHANNEL_WIDTH_20                0
#define VHT_OP_MODE_CHANNEL_WIDTH_40                1
#define VHT_OP_MODE_CHANNEL_WIDTH_80                2
#define VHT_OP_MODE_CHANNEL_WIDTH_160_80P80         3


/*                                    */
#define AMPDU_PARAM_MAX_AMPDU_LEN_EXP               BITS(0, 1)
#define AMPDU_PARAM_MIN_START_SPACING               BITS(2, 4)

#define AMPDU_PARAM_MAX_AMPDU_LEN_8K                0
#define AMPDU_PARAM_MAX_AMPDU_LEN_16K               BIT(0)
#define AMPDU_PARAM_MAX_AMPDU_LEN_32K               BIT(1)
#define AMPDU_PARAM_MAX_AMPDU_LEN_64K               BITS(0, 1)
#define AMPDU_PARAM_MAX_AMPDU_LEN_128K              BIT(2)
#define AMPDU_PARAM_MAX_AMPDU_LEN_256K              (BIT(2) | BIT(0))
#define AMPDU_PARAM_MAX_AMPDU_LEN_512K              BITS(1, 2)
#define AMPDU_PARAM_MAX_AMPDU_LEN_1024K             BITS(0, 2)

#define AMPDU_PARAM_MSS_NO_RESTRICIT                0
#define AMPDU_PARAM_MSS_1_4_US                      BIT(2)
#define AMPDU_PARAM_MSS_1_2_US                      BIT(3)
#define AMPDU_PARAM_MSS_1_US                        BITS(2, 3)
#define AMPDU_PARAM_MSS_2_US                        BIT(4)
#define AMPDU_PARAM_MSS_4_US                        (BIT(4) | BIT(2))
#define AMPDU_PARAM_MSS_8_US                        (BIT(4) | BIT(3))
#define AMPDU_PARAM_MSS_16_US                       BITS(2, 4)

/*                                                             */
#define SUP_MCS_TX_SET_DEFINED                      BIT(0)
#define SUP_MCS_TX_RX_SET_NOT_EQUAL                 BIT(1)
#define SUP_MCS_TX_MAX_NUM_SS                       BITS(2, 3)
#define SUP_MCS_TX_UNEQUAL_MODULATION               BIT(4)

#define SUP_MCS_TX_MAX_NUM_1_SS                     0
#define SUP_MCS_TX_MAX_NUM_2_SS                     BIT(2)
#define SUP_MCS_TX_MAX_NUM_3_SS                     BIT(3)
#define SUP_MCS_TX_MAX_NUM_4_SS                     BITS(2, 3)

#define SUP_MCS_RX_BITMASK_OCTET_NUM                10
#define SUP_MCS_RX_DEFAULT_HIGHEST_RATE             0	/*             */

/*                                           */
#define HT_EXT_CAP_PCO                              BIT(0)
#define HT_EXT_CAP_PCO_TRANSITION_TIME              BITS(1, 2)
#define HT_EXT_CAP_MCS_FEEDBACK                     BITS(8, 9)
#define HT_EXT_CAP_HTC_SUPPORT                      BIT(10)
#define HT_EXT_CAP_RD_RESPONDER                     BIT(11)

#define HT_EXT_CAP_PCO_TRANS_TIME_NONE              0
#define HT_EXT_CAP_PCO_TRANS_TIME_400US             BIT(1)
#define HT_EXT_CAP_PCO_TRANS_TIME_1_5MS             BIT(2)
#define HT_EXT_CAP_PCO_TRANS_TIME_5MS               BITS(1, 2)

#define HT_EXT_CAP_MCS_FEEDBACK_NO_FB               0
#define HT_EXT_CAP_MCS_FEEDBACK_UNSOLICITED         BIT(9)
#define HT_EXT_CAP_MCS_FEEDBACK_BOTH                BITS(8, 9)

/*                                                    */
#define TXBF_IMPLICIT_RX_CAPABLE                    BIT(0)
#define TXBF_RX_STAGGERED_SOUNDING_CAPABLE          BIT(1)
#define TXBF_TX_STAGGERED_SOUNDING_CAPABLE          BIT(2)
#define TXBF_RX_NDP_CAPABLE                         BIT(3)
#define TXBF_TX_NDP_CAPABLE                         BIT(4)
#define TXBF_IMPLICIT_TX_CAPABLE                    BIT(5)
#define TXBF_CALIBRATION_CAPABLE                    BITS(6, 7)
#define TXBF_EXPLICIT_CSI_TX_CAPABLE                BIT(8)
#define TXBF_EXPLICIT_NONCOMPRESSED_TX_CAPABLE      BIT(9)
#define TXBF_EXPLICIT_COMPRESSED_TX_CAPAB           BIT(10)
#define TXBF_EXPLICIT_CSI_FEEDBACK_CAPABLE          BITS(11, 12)
#define TXBF_EXPLICIT_NONCOMPRESSED_FEEDBACK_CAPABLE BITS(13, 14)

#define TXBF_EXPLICIT_COMPRESSED_FEEDBACK_CAPABLE   BITS(15, 16)
#define TXBF_EXPLICIT_COMPRESSED_FEEDBACK_IMMEDIATE_CAPABLE BIT(16)

#define TXBF_MINIMAL_GROUPING_CAPABLE               BITS(17, 18)
#define TXBF_MINIMAL_GROUPING_1_2_3_CAPABLE         BITS(17, 18)

#define TXBF_CSI_BFER_ANTENNANUM_SUPPORTED          BITS(19, 20)
#define TXBF_NONCOMPRESSED_TX_ANTENNANUM_SUPPORTED  BITS(21, 22)

#define TXBF_COMPRESSED_TX_ANTENNANUM_SUPPORTED     BITS(23, 24)
#define TXBF_COMPRESSED_TX_ANTENNANUM_4_SUPPORTED   BITS(23, 24)

#define TXBF_CSI_MAX_ROWS_BFER_SUPPORTED            BITS(25, 26)

#define TXBF_CHANNEL_ESTIMATION_CAPABILITY          BITS(27, 28)
#define TXBF_CHANNEL_ESTIMATION_4STS_CAPABILITY     BITS(27, 28)

/*                                               */
#define ASEL_CAP_CAPABLE                            BIT(0)
#define ASEL_CAP_CSI_FB_BY_TX_ASEL_CAPABLE          BIT(1)
#define ASEL_CAP_ANT_INDICES_FB_BY_TX_ASEL_CAPABLE  BIT(2)
#define ASEL_CAP_EXPLICIT_CSI_FB_CAPABLE            BIT(3)
#define ASEL_CAP_ANT_INDICES_CAPABLE                BIT(4)
#define ASEL_CAP_RX_ASEL_CAPABLE                    BIT(5)
#define ASEL_CAP_TX_SOUNDING_CAPABLE                BIT(6)

/*                               */
#define ELEM_MAX_LEN_HT_OP                          (24 - ELEM_HDR_LEN)	/*                      */

#define HT_OP_INFO1_SCO                             BITS(0, 1)
#define HT_OP_INFO1_STA_CHNL_WIDTH                  BIT(2)
#define HT_OP_INFO1_RIFS_MODE                       BIT(3)

#define HT_OP_INFO2_HT_PROTECTION                   BITS(0, 1)
#define HT_OP_INFO2_NON_GF_HT_STA_PRESENT           BIT(2)
#define HT_OP_INFO2_OBSS_NON_HT_STA_PRESENT         BIT(4)

#define HT_OP_INFO3_DUAL_BEACON                     BIT(6)
#define HT_OP_INFO3_DUAL_CTS_PROTECTION             BIT(7)
#define HT_OP_INFO3_STBC_BEACON                     BIT(8)
#define HT_OP_INFO3_LSIG_TXOP_FULL_SUPPORT          BIT(9)
#define HT_OP_INFO3_PCO_ACTIVE                      BIT(10)
#define HT_OP_INFO3_PCO_PHASE                       BIT(11)

/*                                      */
#define ELEM_MAX_LEN_OBSS_SCAN                      (16 - ELEM_HDR_LEN)

/*                                        */
#define ELEM_MAX_LEN_20_40_BSS_COEXIST              (3 - ELEM_HDR_LEN)

#define BSS_COEXIST_INFO_REQ                        BIT(0)
#define BSS_COEXIST_40M_INTOLERANT                  BIT(1)
#define BSS_COEXIST_20M_REQ                         BIT(2)
#define BSS_COEXIST_OBSS_SCAN_EXEMPTION_REQ         BIT(3)
#define BSS_COEXIST_OBSS_SCAN_EXEMPTION_GRANT       BIT(4)


/*                                  */
#define ELEM_MAX_LEN_INTERWORKING                   (11 - ELEM_HDR_LEN)

/*                                            */
#define ELEM_MAX_LEN_ADV_PROTOCOL                   (4 - ELEM_HDR_LEN)

/*                                        */
#define ELEM_MAX_LEN_ROAMING_CONSORTIUM             (19 - ELEM_HDR_LEN)

#define IW_IE_LENGTH_ANO                            1
#define IW_IE_LENGTH_ANO_VENUE                      3
#define IW_IE_LENGTH_ANO_HESSID                     7
#define IW_IE_LENGTH_ANO_VENUE_HESSID               9


#if CFG_SUPPORT_PASSPOINT
/*                          */
#define ELEM_MAX_LEN_HS20_INDICATION                5
#define ELEM_MIN_LEN_HS20_INDICATION                4

/*                      */
#define ELEM_HS_CONFIG_DGAF_DISABLED_MASK           BIT(0)	/*                                       */
#endif				/*                       */

/*                         */
#define ELEM_MIN_LEN_MTK_OUI                        7
#define VENDOR_OUI_MTK                              { 0x00, 0x0C, 0xE7 }
#define MTK_SYNERGY_CAP_SUPPORT_24G_MCS89           BIT(3)
#define MTK_SYNERGY_CAP0                            (MTK_SYNERGY_CAP_SUPPORT_24G_MCS89)
#define MTK_SYNERGY_CAP1                            0x0
#define MTK_SYNERGY_CAP2                            0x0
#define MTK_SYNERGY_CAP3                            0x0

/*                                                                            */
/*                                                 */
#define ACTION_MEASUREMENT_REQ                      0	/*                              */
#define ACTION_MEASUREMENT_REPORT                   1	/*                             */
#define ACTION_TPC_REQ                              2	/*             */
#define ACTION_TPC_REPORT                           3	/*            */
#define ACTION_CHNL_SWITCH                          4	/*                             */

/*                                */
#define ACTION_ADDTS_REQ                            0	/*               */
#define ACTION_ADDTS_RSP                            1	/*                */
#define ACTION_DELTS                                2	/*       */
#define ACTION_SCHEDULE                             3	/*          */

#define ACTION_ADDTS_REQ_FRAME_LEN                  (24+3+63)	/*                  */
#define ACTION_ADDTS_RSP_FRAME_LEN                  (24+4+63)	/*                                      */

/*                                */
#define ACTION_DLS_REQ                              0	/*             */
#define ACTION_DLS_RSP                              1	/*              */
#define ACTION_DLS_TEARDOWN                         2	/*              */

/*                                       */
#define ACTION_ADDBA_REQ                            0	/*               */
#define ACTION_ADDBA_RSP                            1	/*                */
#define ACTION_DELBA                                2	/*       */

#define ACTION_ADDBA_REQ_FRAME_LEN                  (24+9)
#define ACTION_ADDBA_RSP_FRAME_LEN                  (24+9)

#define ACTION_DELBA_INITIATOR_MASK                 BIT(11)
#define ACTION_DELBA_TID_MASK                       BITS(12, 15)
#define ACTION_DELBA_TID_OFFSET                     12
#define ACTION_DELBA_FRAME_LEN                      (24+6)

/*                                              */
#define ACTION_RM_REQ                               0	/*                           */
#define ACTION_RM_REPORT                            1	/*                          */
#define ACTION_LM_REQ                               2	/*                          */
#define ACTION_LM_REPORT                            3	/*                         */
#define ACTION_NEIGHBOR_REPORT_REQ                  4	/*                         */
#define ACTION_NEIGHBOR_REPORT_RSP                  5	/*                          */

/*                                   */
#define ACTION_PUBLIC_20_40_COEXIST                 0	/*                       */

#if CFG_SUPPORT_802_11W
/*                                                  */
#define ACTION_SA_QUERY_REQUEST                     0
#define ACTION_SA_QUERY_RESPONSE                    1

#define ACTION_SA_QUERY_TR_ID_LEN                   2

/*                       */
#define ACTION_SA_TIMEOUT_REASSOC_DEADLINE          1
#define ACTION_SA_TIMEOUT_KEY_LIFETIME              2
#define ACTION_SA_TIMEOUT_ASSOC_COMEBACK            3
#endif

/*                                  */
#define ACTION_HT_NOTIFY_CHANNEL_WIDTH              0	/*                      */
#define ACTION_HT_SM_POWER_SAVE                     1	/*               */
#define ACTION_HT_PSMP                              2	/*      */
#define ACTION_HT_SET_PCO_PHASE                     3	/*               */
#define ACTION_HT_CSI                               4	/*     */
#define ACTION_HT_NON_COMPRESSED_BEAMFORM           5	/*                            */
#define ACTION_HT_COMPRESSED_BEAMFORM               6	/*                        */
#define ACTION_HT_ANT_SEL_INDICES_FB                7	/*                                    */

/*                                     */
#define ACTION_WNM_TIMING_MEASUREMENT_REQUEST       27

#define ACTION_UNPROTECTED_WNM_TIM                  0
#define ACTION_UNPROTECTED_WNM_TIMING_MEASUREMENT   1

#define ACTION_UNPROTECTED_WNM_TIMING_MEAS_LEN      12

/*                     */
#define ACTION_VHT_COMPRESSED_BFEAMFORMING          0
#define ACTION_GROUP_ID_MANAGEMENT                  1
#define ACTION_OPERATING_MODE_NOTIFICATION          2


//                                                              
#define VENDOR_OUI_WFA                              { 0x00, 0x50, 0xF2 }
#define VENDOR_OUI_WFA_SPECIFIC                     { 0x50, 0x6F, 0x9A }
#define VENDOR_OUI_TYPE_WPA                         1
#define VENDOR_OUI_TYPE_WMM                         2
#define VENDOR_OUI_TYPE_WPS                         4
#define VENDOR_OUI_TYPE_P2P                         9
#define VENDOR_OUI_TYPE_WFD                         10

#if CFG_SUPPORT_PASSPOINT
#define VENDOR_OUI_TYPE_HS20                        16
#endif				/*                       */

#define VENDOR_OUI_TYPE_LEN                         4	/*                        */

/*                                                                                        */
#define VERSION_WPA                                 0x0001	/*                      */
#define VENDOR_OUI_SUBTYPE_VERSION_WMM_INFO         0x0100
#define VENDOR_OUI_SUBTYPE_VERSION_WMM_PARAM        0x0101

/*                          */
#define VENDOR_OUI_SUBTYPE_WMM_INFO                 0x00	/*                      */
#define VENDOR_OUI_SUBTYPE_WMM_PARAM                0x01
#define VENDOR_OUI_SUBTYPE_WMM_TSPEC                0x02

/*                          */
#define VERSION_WMM                                 0x01	/*                      */

/*                             */
#define WMM_QC_UP_MASK                              BITS(0, 2)
#define WMM_QC_EOSP                                 BIT(4)
#define WMM_QC_ACK_POLICY_MASK                      BITS(5, 6)
#define WMM_QC_ACK_POLICY_OFFSET                    5
#define WMM_QC_ACK_POLICY_ACKNOWLEDGE               0
#define WMM_QC_ACK_POLICY_NOT_ACKNOWLEDGE           (1 << WMM_QC_ACK_POLICY_OFFSET)


/*                                   */
#define ELEM_MIN_LEN_WFA_OUI_TYPE_SUBTYPE           6


/*                      */
/*                     */
#define CTRL_BAR_BAR_CONTROL_OFFSET                 16
#define CTRL_BAR_BAR_CONTROL_TID_OFFSET             12
#define CTRL_BAR_BAR_INFORMATION_OFFSET             18
#define CTRL_BAR_BAR_INFORMATION_SSN_OFFSET         4


/*                                                                              
                                                 
                                                                                
*/
#if defined(WINDOWS_DDK) || defined(WINDOWS_CE)
#pragma pack(1)
#endif

typedef struct _LLC_SNAP_HEADER_T {
	UINT_8 ucDSAP;
	UINT_8 ucSSAP;
	UINT_8 ucControl;
	UINT_8 aucCode[3];
	UINT_16 u2Type;
} __KAL_ATTRIB_PACKED__ LLC_SNAP_HEADER_T, *P_LLC_SNAP_HEADER_T;

/*               */
/*                       */
typedef struct _ETH_FRAME_HEADER_T {
	UINT_8 aucDestAddr[MAC_ADDR_LEN];
	UINT_8 aucSrcAddr[MAC_ADDR_LEN];
	UINT_16 u2TypeLen;
} __KAL_ATTRIB_PACKED__ ETH_FRAME_HEADER_T, *P_ETH_FRAME_HEADER_T;

/*                          */
typedef struct _ETH_FRAME_T {
	UINT_8 aucDestAddr[MAC_ADDR_LEN];
	UINT_8 aucSrcAddr[MAC_ADDR_LEN];
	UINT_16 u2TypeLen;
	UINT_8 aucData[1];
} __KAL_ATTRIB_PACKED__ ETH_FRAME_T, *P_ETH_FRAME_T;


/*                                  */
/*                                                            */
typedef struct _WLAN_MAC_HEADER_T {
	UINT_16 u2FrameCtrl;
	UINT_16 u2DurationID;
	UINT_8 aucAddr1[MAC_ADDR_LEN];
	UINT_8 aucAddr2[MAC_ADDR_LEN];
	UINT_8 aucAddr3[MAC_ADDR_LEN];
	UINT_16 u2SeqCtrl;
} __KAL_ATTRIB_PACKED__ WLAN_MAC_HEADER_T, *P_WLAN_MAC_HEADER_T;


/*                                               */
typedef struct _WLAN_MAC_HEADER_QOS_T {
	UINT_16 u2FrameCtrl;
	UINT_16 u2DurationID;
	UINT_8 aucAddr1[MAC_ADDR_LEN];
	UINT_8 aucAddr2[MAC_ADDR_LEN];
	UINT_8 aucAddr3[MAC_ADDR_LEN];
	UINT_16 u2SeqCtrl;
	UINT_16 u2QosCtrl;
} __KAL_ATTRIB_PACKED__ WLAN_MAC_HEADER_QOS_T, *P_WLAN_MAC_HEADER_QOS_T;


/*                                              */
typedef struct _WLAN_MAC_HEADER_HT_T {
	UINT_16 u2FrameCtrl;
	UINT_16 u2DurationID;
	UINT_8 aucAddr1[MAC_ADDR_LEN];
	UINT_8 aucAddr2[MAC_ADDR_LEN];
	UINT_8 aucAddr3[MAC_ADDR_LEN];
	UINT_16 u2SeqCtrl;
	UINT_16 u2QosCtrl;
	UINT_32 u4HtCtrl;
} __KAL_ATTRIB_PACKED__ WLAN_MAC_HEADER_HT_T, *P_WLAN_MAC_HEADER_HT_T;


/*                                      */
typedef struct _WLAN_MAC_HEADER_A4_T {
	UINT_16 u2FrameCtrl;
	UINT_16 u2DurationID;
	UINT_8 aucAddr1[MAC_ADDR_LEN];
	UINT_8 aucAddr2[MAC_ADDR_LEN];
	UINT_8 aucAddr3[MAC_ADDR_LEN];
	UINT_16 u2SeqCtrl;
	UINT_8 aucAddr4[MAC_ADDR_LEN];
} __KAL_ATTRIB_PACKED__ WLAN_MAC_HEADER_A4_T, *P_WLAN_MAC_HEADER_A4_T;


/*                                                             */
typedef struct _WLAN_MAC_HEADER_A4_QOS_T {
	UINT_16 u2FrameCtrl;
	UINT_16 u2DurationID;
	UINT_8 aucAddr1[MAC_ADDR_LEN];
	UINT_8 aucAddr2[MAC_ADDR_LEN];
	UINT_8 aucAddr3[MAC_ADDR_LEN];
	UINT_16 u2SeqCtrl;
	UINT_8 aucAddr4[MAC_ADDR_LEN];
	UINT_16 u2QosCtrl;
} __KAL_ATTRIB_PACKED__ WLAN_MAC_HEADER_A4_QOS_T, *P_WLAN_MAC_HEADER_A4_QOS_T;


typedef struct _WLAN_MAC_HEADER_A4_HT_T {
	UINT_16 u2FrameCtrl;
	UINT_16 u2DurationID;
	UINT_8 aucAddr1[MAC_ADDR_LEN];
	UINT_8 aucAddr2[MAC_ADDR_LEN];
	UINT_8 aucAddr3[MAC_ADDR_LEN];
	UINT_16 u2SeqCtrl;
	UINT_8 aucAddr4[MAC_ADDR_LEN];
	UINT_16 u2QosCtrl;
	UINT_32 u4HtCtrl;
} __KAL_ATTRIB_PACKED__ WLAN_MAC_HEADER_A4_HT_T, *P_WLAN_MAC_HEADER_A4_HT_T;


/*                                                    */
typedef struct _WLAN_MAC_MGMT_HEADER_T {
	UINT_16 u2FrameCtrl;
	UINT_16 u2Duration;
	UINT_8 aucDestAddr[MAC_ADDR_LEN];
	UINT_8 aucSrcAddr[MAC_ADDR_LEN];
	UINT_8 aucBSSID[MAC_ADDR_LEN];
	UINT_16 u2SeqCtrl;
} __KAL_ATTRIB_PACKED__ WLAN_MAC_MGMT_HEADER_T, *P_WLAN_MAC_MGMT_HEADER_T;


/*                                                                   */
typedef struct _WLAN_MAC_MGMT_HEADER_HT_T {
	UINT_16 u2FrameCtrl;
	UINT_16 u2DurationID;
	UINT_8 aucAddr1[MAC_ADDR_LEN];
	UINT_8 aucAddr2[MAC_ADDR_LEN];
	UINT_8 aucAddr3[MAC_ADDR_LEN];
	UINT_16 u2SeqCtrl;
	UINT_32 u4HtCtrl;
} __KAL_ATTRIB_PACKED__ WLAN_MAC_MGMT_HEADER_HT_T, *P_WLAN_MAC_MGMT_HEADER_HT_T;

/*                      */
/*                                            */
typedef struct _CTRL_PSPOLL_FRAME_T {
	UINT_16 u2FrameCtrl;	/*               */
	UINT_16 u2AID;		/*     */
	UINT_8 aucBSSID[MAC_ADDR_LEN];	/*       */
	UINT_8 aucTA[MAC_ADDR_LEN];	/*    */
} __KAL_ATTRIB_PACKED__ CTRL_PSPOLL_FRAME_T, *P_CTRL_PSPOLL_FRAME_T;


/*     */
typedef struct _CTRL_BAR_FRAME_T {
	UINT_16 u2FrameCtrl;	/*               */
	UINT_16 u2DurationID;	/*          */
	UINT_8 aucDestAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucSrcAddr[MAC_ADDR_LEN];	/*    */
	UINT_16 u2BarControl;
	UINT_8 aucBarInfo[2];	/*               */
} __KAL_ATTRIB_PACKED__ CTRL_BAR_FRAME_T, *P_CTRL_BAR_FRAME_T;

/*                          */
/*                                              */
typedef struct _WLAN_BEACON_FRAME_T {
	/*               */
	UINT_16 u2FrameCtrl;	/*               */
	UINT_16 u2DurationID;	/*          */
	UINT_8 aucDestAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucSrcAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucBSSID[MAC_ADDR_LEN];	/*       */
	UINT_16 u2SeqCtrl;	/*                  */
	/*                   */
	UINT_32 au4Timestamp[2];	/*           */
	UINT_16 u2BeaconInterval;	/*                 */
	UINT_16 u2CapInfo;	/*            */
	UINT_8 aucInfoElem[1];	/*                              */
} __KAL_ATTRIB_PACKED__ WLAN_BEACON_FRAME_T, *P_WLAN_BEACON_FRAME_T;

typedef struct _WLAN_BEACON_FRAME_BODY_T {
	/*                   */
	UINT_32 au4Timestamp[2];	/*           */
	UINT_16 u2BeaconInterval;	/*                 */
	UINT_16 u2CapInfo;	/*            */
	UINT_8 aucInfoElem[1];	/*                              */
} __KAL_ATTRIB_PACKED__ WLAN_BEACON_FRAME_BODY_T, *P_WLAN_BEACON_FRAME_BODY_T;


/*                                                      */
typedef struct _WLAN_DISASSOC_FRAME_T {
	/*                           */
	UINT_16 u2FrameCtrl;	/*               */
	UINT_16 u2DurationID;	/*          */
	UINT_8 aucDestAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucSrcAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucBSSID[MAC_ADDR_LEN];	/*       */
	UINT_16 u2SeqCtrl;	/*                  */
	/*                           */
	UINT_16 u2ReasonCode;	/*             */
	UINT_8 aucInfoElem[1];	/*                           */
} __KAL_ATTRIB_PACKED__ WLAN_DISASSOC_FRAME_T, *P_WLAN_DISASSOC_FRAME_T;


/*                                                           */
typedef struct _WLAN_ASSOC_REQ_FRAME_T {
	/*                                */
	UINT_16 u2FrameCtrl;	/*               */
	UINT_16 u2DurationID;	/*          */
	UINT_8 aucDestAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucSrcAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucBSSID[MAC_ADDR_LEN];	/*       */
	UINT_16 u2SeqCtrl;	/*                  */
	/*                                */
	UINT_16 u2CapInfo;	/*                        */
	UINT_16 u2ListenInterval;	/*                 */
	UINT_8 aucInfoElem[1];	/*                                      */
} __KAL_ATTRIB_PACKED__ WLAN_ASSOC_REQ_FRAME_T, *P_WLAN_ASSOC_REQ_FRAME_T;


/*                                                            */
typedef struct _WLAN_ASSOC_RSP_FRAME_T {
	/*                                 */
	UINT_16 u2FrameCtrl;	/*               */
	UINT_16 u2DurationID;	/*          */
	UINT_8 aucDestAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucSrcAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucBSSID[MAC_ADDR_LEN];	/*       */
	UINT_16 u2SeqCtrl;	/*                  */
	/*                                 */
	UINT_16 u2CapInfo;	/*                        */
	UINT_16 u2StatusCode;	/*             */
	UINT_16 u2AssocId;	/*                */
	UINT_8 aucInfoElem[1];	/*                              
                                 */
} __KAL_ATTRIB_PACKED__ WLAN_ASSOC_RSP_FRAME_T, *P_WLAN_ASSOC_RSP_FRAME_T;


/*                                                             */
typedef struct _WLAN_REASSOC_REQ_FRAME_T {
	/*                                  */
	UINT_16 u2FrameCtrl;	/*               */
	UINT_16 u2DurationID;	/*          */
	UINT_8 aucDestAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucSrcAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucBSSID[MAC_ADDR_LEN];	/*       */
	UINT_16 u2SeqCtrl;	/*                  */
	/*                                  */
	UINT_16 u2CapInfo;	/*                        */
	UINT_16 u2ListenInterval;	/*                 */
	UINT_8 aucCurrentAPAddr[MAC_ADDR_LEN];	/*                    */
	UINT_8 aucInfoElem[1];	/*                                      */
} __KAL_ATTRIB_PACKED__ WLAN_REASSOC_REQ_FRAME_T, *P_WLAN_REASSOC_REQ_FRAME_T;


/*                                                             
                                            */
typedef WLAN_ASSOC_RSP_FRAME_T WLAN_REASSOC_RSP_FRAME_T, *P_WLAN_REASSOC_RSP_FRAME_T;

/*                                                      */
typedef WLAN_BEACON_FRAME_T WLAN_PROBE_RSP_FRAME_T, *P_WLAN_PROBE_RSP_FRAME_T;

/*                                                       */
typedef struct _WLAN_AUTH_FRAME_T {
	/*                           */
	UINT_16 u2FrameCtrl;	/*               */
	UINT_16 u2DurationID;	/*          */
	UINT_8 aucDestAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucSrcAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucBSSID[MAC_ADDR_LEN];	/*       */
	UINT_16 u2SeqCtrl;	/*                  */
	/*                           */
	UINT_16 u2AuthAlgNum;	/*                                 */
	UINT_16 u2AuthTransSeqNo;	/*                                            */
	UINT_16 u2StatusCode;	/*             */
	UINT_8 aucInfoElem[1];	/*                                     */
} __KAL_ATTRIB_PACKED__ WLAN_AUTH_FRAME_T, *P_WLAN_AUTH_FRAME_T;


/*                                                         */
typedef struct _WLAN_DEAUTH_FRAME_T {
	/*                           */
	UINT_16 u2FrameCtrl;	/*               */
	UINT_16 u2DurationID;	/*          */
	UINT_8 aucDestAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucSrcAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucBSSID[MAC_ADDR_LEN];	/*       */
	UINT_16 u2SeqCtrl;	/*                  */
	/*                             */
	UINT_16 u2ReasonCode;	/*             */
	UINT_8 aucInfoElem[1];	/*                           */
} __KAL_ATTRIB_PACKED__ WLAN_DEAUTH_FRAME_T, *P_WLAN_DEAUTH_FRAME_T;



/*                         */
/*                              */
typedef struct _IE_HDR_T {
	UINT_8 ucId;
	UINT_8 ucLength;
	UINT_8 aucInfo[1];
} __KAL_ATTRIB_PACKED__ IE_HDR_T, *P_IE_HDR_T;

/*                      */
typedef struct _IE_SSID_T {
	UINT_8 ucId;
	UINT_8 ucLength;
	UINT_8 aucSSID[ELEM_MAX_LEN_SSID];
} __KAL_ATTRIB_PACKED__ IE_SSID_T, *P_IE_SSID_T;

/*                                 */
typedef struct _IE_SUPPORTED_RATE_T {
	UINT_8 ucId;
	UINT_8 ucLength;
	UINT_8 aucSupportedRates[ELEM_MAX_LEN_SUP_RATES];
} __KAL_ATTRIB_PACKED__ IE_SUPPORTED_RATE_T, *P_IE_SUPPORTED_RATE_T;

/*                                  */
typedef struct _IE_DS_PARAM_SET_T {
	UINT_8 ucId;
	UINT_8 ucLength;
	UINT_8 ucCurrChnl;
} __KAL_ATTRIB_PACKED__ IE_DS_PARAM_SET_T, *P_IE_DS_PARAM_SET_T;


/*                                  */
typedef struct _IE_CF_PARAM_SET_T {
	UINT_8 ucId;
	UINT_8 ucLength;
	UINT_8 ucCFPCount;
	UINT_8 ucCFPPeriod;
	UINT_16 u2CFPMaxDur;
	UINT_16 u2DurRemaining;
} __KAL_ATTRIB_PACKED__ IE_CF_PARAM_SET_T, *P_IE_CF_PARAM_SET_T;


/*             */
typedef struct _IE_TIM_T {
	UINT_8 ucId;
	UINT_8 ucLength;
	UINT_8 ucDTIMCount;
	UINT_8 ucDTIMPeriod;
	UINT_8 ucBitmapControl;
	UINT_8 aucPartialVirtualMap[1];
} __KAL_ATTRIB_PACKED__ IE_TIM_T, *P_IE_TIM_T;

/*                                    */
typedef struct _IE_IBSS_PARAM_SET_T {
	UINT_8 ucId;
	UINT_8 ucLength;
	UINT_16 u2ATIMWindow;
} __KAL_ATTRIB_PACKED__ IE_IBSS_PARAM_SET_T, *P_IE_IBSS_PARAM_SET_T;

/*                                */
typedef struct _IE_CHALLENGE_TEXT_T {
	UINT_8 ucId;
	UINT_8 ucLength;
	UINT_8 aucChallengeText[ELEM_MAX_LEN_CHALLENGE_TEXT];
} __KAL_ATTRIB_PACKED__ IE_CHALLENGE_TEXT_T, *P_IE_CHALLENGE_TEXT_T;

/*                                     */
#if CFG_SUPPORT_802_11D
/*                                                                              */
typedef struct _COUNTRY_INFO_TRIPLET_T {
	UINT_8 ucParam1;	/*                                                   
                                      */
	UINT_8 ucParam2;
	UINT_8 ucParam3;
} __KAL_ATTRIB_PACKED__ COUNTRY_INFO_TRIPLET_T, *P_COUNTRY_INFO_TRIPLET_T;

typedef struct _COUNTRY_INFO_SUBBAND_TRIPLET_T {
	UINT_8 ucFirstChnlNum;	/*                        */
	UINT_8 ucNumOfChnl;	/*                      */
	INT_8 cMaxTxPwrLv;	/*                                */
} __KAL_ATTRIB_PACKED__ COUNTRY_INFO_SUBBAND_TRIPLET_T, *P_COUNTRY_INFO_SUBBAND_TRIPLET_T;

typedef struct _COUNTRY_INFO_REGULATORY_TRIPLET_T {
	UINT_8 ucRegExtId;	/*                                          
                                       */
	UINT_8 ucRegClass;	/*                    */
	UINT_8 ucCoverageClass;	/*                                              
                         */
} __KAL_ATTRIB_PACKED__ COUNTRY_INFO_REGULATORY_TRIPLET_T, *P_COUNTRY_INFO_REGULATORY_TRIPLET_T;

typedef struct _IE_COUNTRY_T {
	UINT_8 ucId;
	UINT_8 ucLength;
	UINT_8 aucCountryStr[3];
	COUNTRY_INFO_SUBBAND_TRIPLET_T arCountryStr[1];
} __KAL_ATTRIB_PACKED__ IE_COUNTRY_T, *P_IE_COUNTRY_T;
#endif				/*                     */

/*                      */
typedef struct _IE_ERP_T {
	UINT_8 ucId;
	UINT_8 ucLength;
	UINT_8 ucERP;
} __KAL_ATTRIB_PACKED__ IE_ERP_T, *P_IE_ERP_T;

/*                                           */
typedef struct _IE_EXT_SUPPORTED_RATE_T {
	UINT_8 ucId;
	UINT_8 ucLength;
	UINT_8 aucExtSupportedRates[ELEM_MAX_LEN_EXTENDED_SUP_RATES];
} __KAL_ATTRIB_PACKED__ IE_EXT_SUPPORTED_RATE_T, *P_IE_EXT_SUPPORTED_RATE_T;

/*                                   */
typedef struct _IE_POWER_CONSTRAINT_T {
	UINT_8 ucId;
	UINT_8 ucLength;
	UINT_8 ucLocalPowerConstraint;	/*           */
} __KAL_ATTRIB_PACKED__ IE_POWER_CONSTRAINT_T, *P_IE_POWER_CONSTRAINT_T;

/*                                   */
typedef struct _IE_POWER_CAP_T {
	UINT_8 ucId;
	UINT_8 ucLength;
	INT_8 cMinTxPowerCap;	/*           */
	INT_8 cMaxTxPowerCap;	/*           */
} __KAL_ATTRIB_PACKED__ IE_POWER_CAP_T, *P_IE_POWER_CAP_T;

/*                              */
typedef struct _IE_TPC_REQ_T {
	UINT_8 ucId;
	UINT_8 ucLength;
} __KAL_ATTRIB_PACKED__ IE_TPC_REQ_T, *P_IE_TPC_REQ_T;

/*                             */
typedef struct _IE_TPC_REPORT_T {
	UINT_8 ucId;
	UINT_8 ucLength;
	INT_8 cTxPower;		/*           */
	INT_8 cLinkMargin;	/*          */
} __KAL_ATTRIB_PACKED__ IE_TPC_REPORT_T, *P_IE_TPC_REPORT_T;


/*                                    */
typedef struct _IE_SUPPORTED_CHANNELS_T {
	UINT_8 ucId;
	UINT_8 ucLength;
	UINT_8 ucChannelNum[ELEM_MAX_LEN_SUPPPORTED_CHANNELS * 2];
} __KAL_ATTRIB_PACKED__ IE_SUPPORTED_CHANNELS_T, *P_IE_SUPPORTED_CHANNELS_T;

/*                                             */
typedef struct _IE_CHANNEL_SWITCH_T {
	UINT_8 ucId;
	UINT_8 ucLength;
	UINT_8 ucChannelSwitchMode;
	UINT_8 ucNewChannelNum;
	UINT_8 ucChannelSwitchCount;
} __KAL_ATTRIB_PACKED__ IE_CHANNEL_SWITCH_T, *P_IE_CHANNEL_SWITCH_T;

typedef struct _IE_TIMEOUT_INTERVAL_T {
	UINT_8 ucId;
	UINT_8 ucLength;
#define IE_TIMEOUT_INTERVAL_TYPE_RESERVED			0
#define IE_TIMEOUT_INTERVAL_TYPE_REASSOC			1
#define IE_TIMEOUT_INTERVAL_TYPE_KEY_LIFETIME		43200
#define IE_TIMEOUT_INTERVAL_TYPE_ASSOC_COMEBACK		3
	UINT_8 ucType;
	UINT_32 u4Value;
} __KAL_ATTRIB_PACKED__ IE_TIMEOUT_INTERVAL_T;




/*                                              */
typedef struct _IE_CHNL_SWITCH_T {
	UINT_8 ucId;
	UINT_8 ucLength;
	UINT_8 ucSwitchMode;
	UINT_8 ucNewChannel;
	UINT_8 ucSwitchCount;
} __KAL_ATTRIB_PACKED__ IE_CHNL_SWITCH_T, *P_IE_CHNL_SWITCH_T;

/*                                      */
typedef struct _IE_MEASUREMENT_REQ_T {
	UINT_8 ucId;
	UINT_8 ucLength;
	UINT_8 ucToken;
	UINT_8 ucRequestMode;
	UINT_8 ucMeasurementType;
	UINT_8 aucRequestFields[1];
} __KAL_ATTRIB_PACKED__ IE_MEASUREMENT_REQ_T, *P_IE_MEASUREMENT_REQ_T;


/*                                        */
typedef struct _IE_SUP_OPERATING_CLASS_T {
	UINT_8 ucId;
	UINT_8 ucLength;
	UINT_8 ucCur;
	UINT_8 ucSup[255];
} __KAL_ATTRIB_PACKED__ IE_SUP_OPERATING_CLASS_T, *P_IE_SUP_OPERATING_CLASS_T;


typedef struct _SM_BASIC_REQ_T {
	UINT_8 ucChannel;
	UINT_32 au4StartTime[2];
	UINT_16 u2Duration;
} __KAL_ATTRIB_PACKED__ SM_BASIC_REQ_T, *P_SM_BASIC_REQ_T;

/*                                                                            */
typedef SM_BASIC_REQ_T SM_REQ_COMMON_T, *P_SM_REQ_COMMON_T;
typedef SM_BASIC_REQ_T SM_CCA_REQ_T, *P_SM_CCA_REQ_T;
typedef SM_BASIC_REQ_T SM_RPI_HISTOGRAM_REQ_T, *P_SM_RPI_HISTOGRAM_REQ_T;

typedef struct _RM_CHNL_LOAD_REQ_T {
	UINT_8 ucRegulatoryClass;
	UINT_8 ucChannel;
	UINT_16 u2RandomInterval;
	UINT_16 u2Duration;
	UINT_8 aucSubElements[1];
} __KAL_ATTRIB_PACKED__ RM_CHNL_LOAD_REQ_T, *P_RM_CHNL_LOAD_REQ_T;

typedef RM_CHNL_LOAD_REQ_T RM_NOISE_HISTOGRAM_REQ_T, *P_RM_NOISE_HISTOGRAM_REQ_T;

typedef struct _RM_BCN_REQ_T {
	UINT_8 ucRegulatoryClass;
	UINT_8 ucChannel;
	UINT_16 u2RandomInterval;
	UINT_16 u2Duration;
	UINT_8 ucMeasurementMode;
	UINT_8 aucBssid[6];
	UINT_8 aucSubElements[1];
} __KAL_ATTRIB_PACKED__ RM_BCN_REQ_T, *P_RM_BCN_REQ_T;

typedef struct _RM_FRAME_REQ_T {
	UINT_8 ucRegulatoryClass;
	UINT_8 ucChannel;
	UINT_16 u2RandomInterval;
	UINT_16 u2Duration;
	UINT_8 ucFrameReqType;
	UINT_8 aucMacAddr[6];
	UINT_8 aucSubElements[1];
} __KAL_ATTRIB_PACKED__ RM_FRAME_REQ_T, *P_RM_FRAME_REQ_T;

typedef struct _RM_STA_STATS_REQ_T {
	UINT_8 aucPeerMacAddr[6];
	UINT_16 u2RandomInterval;
	UINT_16 u2Duration;
	UINT_8 ucGroupID;
	UINT_8 aucSubElements[1];
} __KAL_ATTRIB_PACKED__ RM_STA_STATS_REQ_T, *P_RM_STA_STATS_REQ_T;

typedef struct _RM_LCI_REQ_T {
	UINT_8 ucLocationSubject;
	UINT_8 ucLatitudeResolution;
	UINT_8 ucLongitudeResolution;
	UINT_8 ucAltitudeResolution;
	UINT_8 aucSubElements[1];
} __KAL_ATTRIB_PACKED__ RM_LCI_REQ_T, *P_RM_LCI_REQ_T;

typedef struct _RM_TS_MEASURE_REQ_T {
	UINT_16 u2RandomInterval;
	UINT_16 u2Duration;
	UINT_8 aucPeerStaAddr[6];
	UINT_8 ucTrafficID;
	UINT_8 ucBin0Range;
	UINT_8 aucSubElements[1];
} __KAL_ATTRIB_PACKED__ RM_TS_MEASURE_REQ_T, *P_RM_TS_MEASURE_REQ_T;

typedef struct _RM_MEASURE_PAUSE_REQ_T {
	UINT_16 u2PauseTime;
	UINT_8 aucSubElements[1];
} __KAL_ATTRIB_PACKED__ RM_MEASURE_PAUSE_REQ_T, *P_RM_MEASURE_PAUSE_REQ_T;

/*                                     */
typedef struct _IE_MEASUREMENT_REPORT_T {
	UINT_8 ucId;
	UINT_8 ucLength;
	UINT_8 ucToken;
	UINT_8 ucReportMode;
	UINT_8 ucMeasurementType;
	UINT_8 aucReportFields[1];
} __KAL_ATTRIB_PACKED__ IE_MEASUREMENT_REPORT_T, *P_IE_MEASUREMENT_REPORT_T;

typedef struct _SM_BASIC_REPORT_T {
	UINT_8 ucChannel;
	UINT_32 u4StartTime[2];
	UINT_16 u2Duration;
	UINT_8 ucMap;
} __KAL_ATTRIB_PACKED__ SM_BASIC_REPORT_T, *P_SM_BASIC_REPORT_T;

typedef struct _SM_CCA_REPORT_T {
	UINT_8 ucChannel;
	UINT_32 u4StartTime[2];
	UINT_16 u2Duration;
	UINT_8 ucCcaBusyFraction;
} __KAL_ATTRIB_PACKED__ SM_CCA_REPORT_T, *P_SM_CCA_REPORT_T;

typedef struct _SM_RPI_REPORT_T {
	UINT_8 ucChannel;
	UINT_32 u4StartTime[2];
	UINT_16 u2Duration;
	UINT_8 aucRPI[8];
} __KAL_ATTRIB_PACKED__ SM_RPI_REPORT_T, *P_SM_RPI_REPORT_T;

typedef struct _RM_CHNL_LOAD_REPORT_T {
	UINT_8 ucRegulatoryClass;
	UINT_8 ucChannel;
	UINT_32 u4StartTime[2];
	UINT_16 u2Duration;
	UINT_8 ucChnlLoad;
} __KAL_ATTRIB_PACKED__ RM_CHNL_LOAD_REPORT_T, *P_RM_CHNL_LOAD_REPORT_T;

typedef struct _RM_IPI_REPORT_T {
	UINT_8 ucRegulatoryClass;
	UINT_8 ucChannel;
	UINT_32 u4StartTime[2];
	UINT_16 u2Duration;
	UINT_8 ucAntennaId;
	INT_8 cANPI;
	UINT_8 aucIPI[11];
} __KAL_ATTRIB_PACKED__ RM_IPI_REPORT_T, *P_RM_IPI_REPORT_T;

/*                        */
typedef struct _IE_QUIET_T {
	UINT_8 ucId;
	UINT_8 ucLength;
	UINT_8 ucCount;
	UINT_8 ucPeriod;
	UINT_16 u2Duration;
	UINT_16 u2Offset;
} __KAL_ATTRIB_PACKED__ IE_QUIET_T, *P_IE_QUIET_T;

/*                                        */
typedef struct _IE_EXT_CAP_T {
	UINT_8 ucId;
	UINT_8 ucLength;
	UINT_8 aucCapabilities[1];
} __KAL_ATTRIB_PACKED__ IE_EXT_CAP_T, *P_EXT_CAP_T;

/*                                        */
typedef struct _IE_RRM_ENABLED_CAP_T {
	UINT_8 ucId;
	UINT_8 ucLength;
	UINT_8 aucCap[5];
} __KAL_ATTRIB_PACKED__ IE_RRM_ENABLED_CAP_T, *P_IE_RRM_ENABLED_CAP_T;

/*                                  */
typedef struct _SUP_MCS_SET_FIELD {
	UINT_8 aucRxMcsBitmask[SUP_MCS_RX_BITMASK_OCTET_NUM];
	UINT_16 u2RxHighestSupportedRate;
	UINT_32 u4TxRateInfo;
} __KAL_ATTRIB_PACKED__ SUP_MCS_SET_FIELD, *P_SUP_MCS_SET_FIELD;

typedef struct _IE_HT_CAP_T {
	UINT_8 ucId;
	UINT_8 ucLength;
	UINT_16 u2HtCapInfo;
	UINT_8 ucAmpduParam;
	SUP_MCS_SET_FIELD rSupMcsSet;
	UINT_16 u2HtExtendedCap;
	UINT_32 u4TxBeamformingCap;
	UINT_8 ucAselCap;
} __KAL_ATTRIB_PACKED__ IE_HT_CAP_T, *P_IE_HT_CAP_T;

/*                               */
typedef struct _IE_HT_OP_T {
	UINT_8 ucId;
	UINT_8 ucLength;
	UINT_8 ucPrimaryChannel;
	UINT_8 ucInfo1;
	UINT_16 u2Info2;
	UINT_16 u2Info3;
	UINT_8 aucBasicMcsSet[16];
} __KAL_ATTRIB_PACKED__ IE_HT_OP_T, *P_IE_HT_OP_T;

/*                                       */
typedef struct _VHT_SUPPORTED_MCS_FIELD {
	UINT_16 u2RxMcsMap;
	UINT_16 u2RxHighestSupportedDataRate;
	UINT_16 u2TxMcsMap;
	UINT_16 u2TxHighestSupportedDataRate;
} __KAL_ATTRIB_PACKED__ VHT_SUPPORTED_MCS_FIELD, *P_VHT_SUPPORTED_MCS_FIELD;

typedef struct _IE_VHT_CAP_T {
	UINT_8 ucId;
	UINT_8 ucLength;
	UINT_32 u4VhtCapInfo;
	VHT_SUPPORTED_MCS_FIELD rVhtSupportedMcsSet;
} __KAL_ATTRIB_PACKED__ IE_VHT_CAP_T, *P_IE_VHT_CAP_T;

/*                               */
typedef struct _IE_VHT_OP_T {
	UINT_8 ucId;
	UINT_8 ucLength;
	UINT_8 ucVhtOperation[3];
	UINT_16 u2VhtBasicMcsSet;
} __KAL_ATTRIB_PACKED__ IE_VHT_OP_T, *P_IE_VHT_OP_T;

/*                                         */
typedef struct _IE_SECONDARY_OFFSET_T {
	UINT_8              ucId;
	UINT_8              ucLength;
	UINT_8              ucSecondaryOffset;
}__KAL_ATTRIB_PACKED__ IE_SECONDARY_OFFSET_T, *P_IE_SECONDARY_OFFSET_T;

/*                                                */
typedef struct _IE_MESH_CHANNEL_T {
	UINT_8              ucId;
	UINT_8              ucLength;
	UINT_8              ucTimetoLive;
	UINT_8              ucFlags;
	UINT_16             u2ReasonCodes;
	UINT_16             u2ProcedenceValue;
}__KAL_ATTRIB_PACKED__ IE_MESH_CHANNEL_T, *P_IE_MESH_CHANNEL_T;


/*                                               */
typedef struct _IE_WIDE_BAND_CHANNEL_T {
	UINT_8              ucId;
	UINT_8              ucLength;
	UINT_8              ucNewChannelWidth;
	UINT_8              ucChannelS1;
	UINT_8              ucChannelS2;
}__KAL_ATTRIB_PACKED__ IE_WIDE_BAND_CHANNEL_T, *P_IE_WIDE_BAND_CHANNEL_T;


/*                                             */
typedef struct _IE_OP_MODE_NOTIFICATION_T {
	UINT_8 ucId;
	UINT_8 ucLength;
	UINT_8 ucOpMode;
} __KAL_ATTRIB_PACKED__ IE_OP_MODE_NOTIFICATION_T, *P_IE_OP_MODE_NOTIFICATION_T;


/*                                         */
typedef struct _RSN_INFO_ELEM_T {
	UCHAR ucElemId;
	UCHAR ucLength;
	UINT_16 u2Version;
	UINT_32 u4GroupKeyCipherSuite;
	UINT_16 u2PairwiseKeyCipherSuiteCount;
	UCHAR aucPairwiseKeyCipherSuite1[4];
} __KAL_ATTRIB_PACKED__ RSN_INFO_ELEM_T, *P_RSN_INFO_ELEM_T;

/*                                         */
typedef struct _WPA_INFO_ELEM_T {
	UCHAR ucElemId;
	UCHAR ucLength;
	UCHAR aucOui[3];
	UCHAR ucOuiType;
	UINT_16 u2Version;
	UINT_32 u4GroupKeyCipherSuite;
	UINT_16 u2PairwiseKeyCipherSuiteCount;
	UCHAR aucPairwiseKeyCipherSuite1[4];
} __KAL_ATTRIB_PACKED__ WPA_INFO_ELEM_T, *P_WPA_INFO_ELEM_T;

/*                                                      */
typedef struct _IE_INTOLERANT_CHNL_REPORT_T {
	UINT_8 ucId;
	UINT_8 ucLength;
	UINT_8 ucRegulatoryClass;
	UINT_8 aucChannelList[1];
} __KAL_ATTRIB_PACKED__ IE_INTOLERANT_CHNL_REPORT_T, *P_IE_INTOLERANT_CHNL_REPORT_T;

/*                                       */
typedef struct _IE_OBSS_SCAN_PARAM_T {
	UINT_8 ucId;
	UINT_8 ucLength;
	UINT_16 u2ScanPassiveDwell;
	UINT_16 u2ScanActiveDwell;
	UINT_16 u2TriggerScanInterval;
	UINT_16 u2ScanPassiveTotalPerChnl;
	UINT_16 u2ScanActiveTotalPerChnl;
	UINT_16 u2WidthTransDelayFactor;
	UINT_16 u2ScanActivityThres;
} __KAL_ATTRIB_PACKED__ IE_OBSS_SCAN_PARAM_T, *P_IE_OBSS_SCAN_PARAM_T;

/*                                        */
typedef struct _IE_20_40_COEXIST_T {
	UINT_8 ucId;
	UINT_8 ucLength;
	UINT_8 ucData;
} __KAL_ATTRIB_PACKED__ IE_20_40_COEXIST_T, *P_IE_20_40_COEXIST_T;


/*                     */
/*                         */
typedef struct _WLAN_ACTION_FRAME {
	/*                   */
	UINT_16 u2FrameCtrl;	/*               */
	UINT_16 u2DurationID;	/*          */
	UINT_8 aucDestAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucSrcAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucBSSID[MAC_ADDR_LEN];	/*       */
	UINT_16 u2SeqCtrl;	/*                  */
	/*                   */
	UINT_8 ucCategory;	/*          */
	UINT_8 ucAction;	/*              */
	UINT_8 ucActionDetails[1];	/*                */
} __KAL_ATTRIB_PACKED__ WLAN_ACTION_FRAME, *P_WLAN_ACTION_FRAME;

/*                                                   */
typedef struct _ACTION_SM_REQ_FRAME {
	/*                          */
	UINT_16 u2FrameCtrl;	/*               */
	UINT_16 u2Duration;	/*          */
	UINT_8 aucDestAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucSrcAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucBSSID[MAC_ADDR_LEN];	/*       */
	UINT_16 u2SeqCtrl;	/*                  */
	/*                          */
	UINT_8 ucCategory;	/*          */
	UINT_8 ucAction;	/*              */
	UINT_8 ucDialogToken;	/*              */
	UINT_8 aucInfoElem[1];	/*                       */
} __KAL_ATTRIB_PACKED__ ACTION_SM_REQ_FRAME, *P_ACTION_SM_REQ_FRAME;

/*                                                  */
typedef ACTION_SM_REQ_FRAME ACTION_SM_REPORT_FRAME, *P_ACTION_SM_REPORT_FRAME;

/*                                                  */
typedef struct _ACTION_CHANNEL_SWITCH_FRAME {
    /*                          */
    UINT_16     u2FrameCtrl;                /*               */
    UINT_16     u2Duration;                 /*          */
    UINT_8      aucDestAddr[MAC_ADDR_LEN];  /*    */
    UINT_8      aucSrcAddr[MAC_ADDR_LEN];   /*    */
    UINT_8      aucBSSID[MAC_ADDR_LEN];     /*       */
    UINT_16     u2SeqCtrl;                  /*                  */
    /*                          */
    UINT_8      ucCategory;                 /*          */
    UINT_8      ucAction;                   /*              */
    UINT_8      aucInfoElem[1];             /*                      */
} __KAL_ATTRIB_PACKED__ ACTION_CHANNEL_SWITCH_FRAME, *P_ACTION_CHANNEL_SWITCH_FRAME;


/*                                    */
typedef struct _ACTION_ADDTS_REQ_FRAME {
	/*                          */
	UINT_16 u2FrameCtrl;	/*               */
	UINT_16 u2Duration;	/*          */
	UINT_8 aucDestAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucSrcAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucBSSID[MAC_ADDR_LEN];	/*       */
	UINT_16 u2SeqCtrl;	/*                  */
	/*                          */
	UINT_8 ucCategory;	/*          */
	UINT_8 ucAction;	/*              */
	UINT_8 ucDialogToken;	/*              */
	UINT_8 aucInfoElem[1];	/*                              
                          */
} __KAL_ATTRIB_PACKED__ ACTION_ADDTS_REQ_FRAME, *P_ACTION_ADDTS_REQ_FRAME;


/*                                     */
typedef struct _ACTION_ADDTS_RSP_FRAME {
	/*                           */
	UINT_16 u2FrameCtrl;	/*               */
	UINT_16 u2Duration;	/*          */
	UINT_8 aucDestAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucSrcAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucBSSID[MAC_ADDR_LEN];	/*       */
	UINT_16 u2SeqCtrl;	/*                  */
	/*                           */
	UINT_8 ucCategory;	/*          */
	UINT_8 ucAction;	/*              */
	UINT_8 ucDialogToken;	/*              */
	UINT_8 ucStatusCode;	/*                                */
	UINT_8 aucInfoElem[1];	/*                              
                          */
} __KAL_ATTRIB_PACKED__ ACTION_ADDTS_RSP_FRAME, *P_ACTION_ADDTS_RSP_FRAME;


/*                            */
typedef struct _ACTION_DELTS_FRAME {
	/*                  */
	UINT_16 u2FrameCtrl;	/*               */
	UINT_16 u2DurationID;	/*          */
	UINT_8 aucDestAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucSrcAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucBSSID[MAC_ADDR_LEN];	/*       */
	UINT_16 u2SeqCtrl;	/*                  */
	/*                  */
	UINT_8 ucCategory;	/*          */
	UINT_8 ucAction;	/*              */
	UINT_8 aucTsInfo[3];	/*         */
} __KAL_ATTRIB_PACKED__ ACTION_DELTS_FRAME, *P_ACTION_DELTS_FRAME;


/*                                    */
typedef struct _ACTION_ADDBA_REQ_FRAME_T {
	/*                   */
	UINT_16 u2FrameCtrl;	/*               */
	UINT_16 u2DurationID;	/*          */
	UINT_8 aucDestAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucSrcAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucBSSID[MAC_ADDR_LEN];	/*       */
	UINT_16 u2SeqCtrl;	/*                  */
	/*                   */
	UINT_8 ucCategory;	/*          */
	UINT_8 ucAction;	/*              */
	UINT_8 ucDialogToken;	/*                                   */
	UINT_8 aucBAParameterSet[2];	/*                             */
	UINT_8 aucBATimeoutValue[2];
	UINT_8 aucBAStartSeqCtrl[2];	/*     */
} __KAL_ATTRIB_PACKED__ ACTION_ADDBA_REQ_FRAME_T, *P_ACTION_ADDBA_REQ_FRAME_T;

typedef struct _ACTION_ADDBA_REQ_BODY_T {
	UINT_16 u2BAParameterSet;	/*                             */
	UINT_16 u2BATimeoutValue;
	UINT_16 u2BAStartSeqCtrl;	/*     */
} __KAL_ATTRIB_PACKED__ ACTION_ADDBA_REQ_BODY_T, *P_ACTION_ADDBA_REQ_BODY_T;

/*                                     */
typedef struct _ACTION_ADDBA_RSP_FRAME_T {
	/*                   */
	UINT_16 u2FrameCtrl;	/*               */
	UINT_16 u2DurationID;	/*          */
	UINT_8 aucDestAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucSrcAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucBSSID[MAC_ADDR_LEN];	/*       */
	UINT_16 u2SeqCtrl;	/*                  */
	/*                   */
	UINT_8 ucCategory;	/*          */
	UINT_8 ucAction;	/*              */
	UINT_8 ucDialogToken;	/*                                   */
	UINT_8 aucStatusCode[2];
	UINT_8 aucBAParameterSet[2];	/*                             */
	UINT_8 aucBATimeoutValue[2];
} __KAL_ATTRIB_PACKED__ ACTION_ADDBA_RSP_FRAME_T, *P_ACTION_ADDBA_RSP_FRAME_T;

typedef struct _ACTION_ADDBA_RSP_BODY_T {
	UINT_16 u2StatusCode;
	UINT_16 u2BAParameterSet;	/*                             */
	UINT_16 u2BATimeoutValue;
} __KAL_ATTRIB_PACKED__ ACTION_ADDBA_RSP_BODY_T, *P_ACTION_ADDBA_RSP_BODY_T;

/*                            */
typedef struct _ACTION_DELBA_FRAME_T {
	/*                   */
	UINT_16 u2FrameCtrl;	/*               */
	UINT_16 u2DurationID;	/*          */
	UINT_8 aucDestAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucSrcAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucBSSID[MAC_ADDR_LEN];	/*       */
	UINT_16 u2SeqCtrl;	/*                  */
	/*                   */
	UINT_8 ucCategory;	/*          */
	UINT_8 ucAction;	/*              */
	UINT_16 u2DelBaParameterSet;	/*                                  */
	UINT_16 u2ReasonCode;	/*         */
} __KAL_ATTRIB_PACKED__ ACTION_DELBA_FRAME_T, *P_ACTION_DELBA_FRAME_T;

/*                                                */
typedef struct _ACTION_RM_REQ_FRAME {
	/*            */
	UINT_16 u2FrameCtrl;	/*               */
	UINT_16 u2Duration;	/*          */
	UINT_8 aucDestAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucSrcAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucBSSID[MAC_ADDR_LEN];	/*       */
	UINT_16 u2SeqCtrl;	/*                  */
	/*                                      */
	UINT_8 ucCategory;	/*          */
	UINT_8 ucAction;	/*              */
	UINT_8 ucDialogToken;	/*              */
	UINT_16 u2Repetitions;	/*                       */
	UINT_8 aucInfoElem[1];	/*                                      
                                      */
} __KAL_ATTRIB_PACKED__ ACTION_RM_REQ_FRAME, *P_ACTION_RM_REQ_FRAME;

/*                                               */
typedef struct _ACTION_RM_REPORT_FRAME {
	/*            */
	UINT_16 u2FrameCtrl;	/*               */
	UINT_16 u2Duration;	/*          */
	UINT_8 aucDestAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucSrcAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucBSSID[MAC_ADDR_LEN];	/*       */
	UINT_16 u2SeqCtrl;	/*                  */
	/*                                     */
	UINT_8 ucCategory;	/*          */
	UINT_8 ucAction;	/*              */
	UINT_8 ucDialogToken;	/*              */
	UINT_8 aucInfoElem[1];	/*                                     
                                     */
} __KAL_ATTRIB_PACKED__ ACTION_RM_REPORT_FRAME, *P_ACTION_RM_REPORT_FRAME;

/*                                                        */
typedef struct _ACTION_20_40_COEXIST_FRAME {
	/*            */
	UINT_16 u2FrameCtrl;	/*               */
	UINT_16 u2Duration;	/*          */
	UINT_8 aucDestAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucSrcAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucBSSID[MAC_ADDR_LEN];	/*       */
	UINT_16 u2SeqCtrl;	/*                  */
	/*                                       */
	UINT_8 ucCategory;	/*          */
	UINT_8 ucAction;	/*              */

	IE_20_40_COEXIST_T rBssCoexist;	/*                               */
	IE_INTOLERANT_CHNL_REPORT_T rChnlReport;	/*                           */

} __KAL_ATTRIB_PACKED__ ACTION_20_40_COEXIST_FRAME, *P_ACTION_20_40_COEXIST_FRAME;


#if CFG_SUPPORT_802_11W
/*                                        */
typedef struct _ACTION_SA_QUERY_FRAME {
	/*            */
	UINT_16 u2FrameCtrl;	/*               */
	UINT_16 u2Duration;	/*          */
	UINT_8 aucDestAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucSrcAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucBSSID[MAC_ADDR_LEN];	/*       */
	UINT_16 u2SeqCtrl;	/*                  */
	/*                                       */
	UINT_8 ucCategory;	/*          */
	UINT_8 ucAction;	/*              */

	UINT_8 ucTransId[ACTION_SA_QUERY_TR_ID_LEN];	/*                */

} __KAL_ATTRIB_PACKED__ ACTION_SA_QUERY_FRAME, *P_ACTION_SA_QUERY_FRAME;
#endif

/*                                                     */
typedef struct _ACTION_NOTIFY_CHNL_WIDTH_FRAME {
	/*            */
	UINT_16 u2FrameCtrl;	/*               */
	UINT_16 u2Duration;	/*          */
	UINT_8 aucDestAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucSrcAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucBSSID[MAC_ADDR_LEN];	/*       */
	UINT_16 u2SeqCtrl;	/*                  */
	/*                                       */
	UINT_8 ucCategory;	/*          */
	UINT_8 ucAction;	/*              */
	UINT_8 ucChannelWidth;	/*               */
} __KAL_ATTRIB_PACKED__ ACTION_NOTIFY_CHNL_WIDTH_FRAME, *P_ACTION_NOTIFY_CHNL_WIDTH_FRAME;

/*                                                                 */
typedef struct _ACTION_WNM_TIMING_MEAS_REQ_FRAME {
	/*            */
	UINT_16 u2FrameCtrl;	/*               */
	UINT_16 u2Duration;	/*          */
	UINT_8 aucDestAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucSrcAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucBSSID[MAC_ADDR_LEN];	/*       */
	UINT_16 u2SeqCtrl;	/*                  */
	/*                                                  */
	UINT_8 ucCategory;	/*          */
	UINT_8 ucAction;	/*              */
	UINT_8 ucTrigger;	/*         */
} __KAL_ATTRIB_PACKED__ ACTION_WNM_TIMING_MEAS_REQ_FRAME, *P_ACTION_WNM_TIMING_MEAS_REQ_FRAME;

/*                                                         */
typedef struct _ACTION_UNPROTECTED_WNM_TIMING_MEAS_FRAME {
	/*            */
	UINT_16 u2FrameCtrl;	/*               */
	UINT_16 u2Duration;	/*          */
	UINT_8 aucDestAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucSrcAddr[MAC_ADDR_LEN];	/*    */
	UINT_8 aucBSSID[MAC_ADDR_LEN];	/*       */
	UINT_16 u2SeqCtrl;	/*                  */
	/*                                          */
	UINT_8 ucCategory;	/*          */
	UINT_8 ucAction;	/*              */
	UINT_8 ucDialogToken;	/*              */
	UINT_8 ucFollowUpDialogToken;	/*                        */
	UINT_32 u4ToD;		/*                               */
	UINT_32 u4ToA;		/*                             */
	UINT_8 ucMaxToDErr;	/*                             */
	UINT_8 ucMaxToAErr;	/*                             */
} __KAL_ATTRIB_PACKED__ ACTION_UNPROTECTED_WNM_TIMING_MEAS_FRAME,
    *P_ACTION_UNPROTECTED_WNM_TIMING_MEAS_FRAME;

/*                                                   */
typedef struct _ACTION_OP_MODE_NOTIFICATION_FRAME {
    /*            */
    UINT_16     u2FrameCtrl;                /*               */
    UINT_16     u2Duration;                 /*          */
    UINT_8      aucDestAddr[MAC_ADDR_LEN];  /*    */
    UINT_8      aucSrcAddr[MAC_ADDR_LEN];   /*    */
    UINT_8      aucBSSID[MAC_ADDR_LEN];     /*       */
    UINT_16     u2SeqCtrl;                  /*                  */
    /*                                        */
    UINT_8      ucCategory;                 /*          */
    UINT_8      ucAction;                   /*              */
    UINT_8      ucOperatingMode;            /*                */
} __KAL_ATTRIB_PACKED__ ACTION_OP_MODE_NOTIFICATION_FRAME, *P_ACTION_OP_MODE_NOTIFICATION_FRAME;

//                                
typedef struct _IE_WFA_T {
	UINT_8 ucId;
	UINT_8 ucLength;
	UINT_8 aucOui[3];
	UINT_8 ucOuiType;
	UINT_8 aucOuiSubTypeVersion[2];
	/*                                                      
                                                       */
} __KAL_ATTRIB_PACKED__ IE_WFA_T, *P_IE_WFA_T;

#if CFG_SUPPORT_PASSPOINT
/*                                                  */
typedef struct _IE_HS20_INDICATION_T {
	UINT_8 ucId;		/*            */
	UINT_8 ucLength;	/*        */
	UINT_8 aucOui[3];	/*     */
	UINT_8 ucType;		/*      */
	UINT_8 ucHotspotConfig;	/*                       */
} __KAL_ATTRIB_PACKED__ IE_HS20_INDICATION_T, *P_IE_HS20_INDICATION_T;
#endif				/*                       */

/*                                 */
typedef struct _WAPI_INFO_ELEM_T {
	UCHAR ucElemId;
	UCHAR ucLength;
	UINT_16 u2Version;
	UINT_16 u2AuthKeyMgtSuiteCount;
	UCHAR aucAuthKeyMgtSuite1[4];
} __KAL_ATTRIB_PACKED__ WAPI_INFO_ELEM_T, *P_WAPI_INFO_ELEM_T;

/*                                         */
typedef struct _IE_MTK_OUI_T {
	UINT_8 ucId;
	UINT_8 ucLength;
	UINT_8 aucOui[3];
	UINT_8 aucCapability[4];
	UINT_8 aucInfoElem[1];
} __KAL_ATTRIB_PACKED__ IE_MTK_OUI_T, *P_IE_MTK_OUI_T;

#if defined(WINDOWS_DDK) || defined(WINDOWS_CE)
#pragma pack()
#endif

/*                                                                              
                                                  
                                                                                
*/

/*                                                                              
                                                   
                                                                                
*/

/*                                                                              
                                             
                                                                                
*/
/*                                       */
#define ECW_TO_CW(_ECW)         ((1 << (_ECW)) - 1)

/*                         */
#define RCPI_TO_dBm(_rcpi)                          \
    ((PARAM_RSSI)(((_rcpi) > RCPI_HIGH_BOUND ? RCPI_HIGH_BOUND : (_rcpi)) >> 1) - NDBM_LOW_BOUND_FOR_RCPI)

/*                         */
#define dBm_TO_RCPI(_dbm)                           \
    (RCPI)(((((PARAM_RSSI)(_dbm) + NDBM_LOW_BOUND_FOR_RCPI) << 1) > RCPI_HIGH_BOUND) ? RCPI_HIGH_BOUND : \
	    ((((PARAM_RSSI)(_dbm) + NDBM_LOW_BOUND_FOR_RCPI) << 1) < RCPI_LOW_BOUND ? RCPI_LOW_BOUND : \
	     (((PARAM_RSSI)(_dbm) + NDBM_LOW_BOUND_FOR_RCPI) << 1)))

/*                                                                    */
#define IE_ID(fp)               (((P_IE_HDR_T) fp)->ucId)
#define IE_LEN(fp)              (((P_IE_HDR_T) fp)->ucLength)
#define IE_SIZE(fp)             (ELEM_HDR_LEN + IE_LEN(fp))

#define SSID_IE(fp)             ((P_IE_SSID_T) fp)

#define SUP_RATES_IE(fp)        ((P_IE_SUPPORTED_RATE_T) fp)

#define DS_PARAM_IE(fp)         ((P_IE_DS_PARAM_SET_T) fp)

#define TIM_IE(fp)              ((P_IE_TIM_T) fp)

#define IBSS_PARAM_IE(fp)       ((P_IE_IBSS_PARAM_SET_T) fp)

#define ERP_INFO_IE(fp)         ((P_IE_ERP_T) fp)

#define EXT_SUP_RATES_IE(fp)    ((P_IE_EXT_SUPPORTED_RATE_T) fp)

#define WFA_IE(fp)              ((P_IE_WFA_T) fp)

#if CFG_SUPPORT_802_11D
#define COUNTRY_IE(fp)          ((P_IE_COUNTRY_T) fp)
#endif

#define EXT_CAP_IE(fp)          ((P_EXT_CAP_T) fp)

#define HT_CAP_IE(fp)           ((P_IE_HT_CAP_T) fp)

#define HT_OP_IE(fp)            ((P_IE_HT_OP_T) fp)

#define VHT_CAP_IE(fp)           ((P_IE_VHT_CAP_T) fp)

#define VHT_OP_IE(fp)            ((P_IE_VHT_OP_T) fp)

#define OBSS_SCAN_PARAM_IE(fp)  ((P_IE_OBSS_SCAN_PARAM_T) fp)

#define BSS_20_40_COEXIST_IE(fp) ((P_IE_20_40_COEXIST_T) fp)

#define SUP_OPERATING_CLASS_IE(fp) ((P_IE_SUP_OPERATING_CLASS_T) fp)

#define QUIET_IE(fp)            ((P_IE_QUIET_T) fp)

#define MTK_OUI_IE(fp)          ((P_IE_MTK_OUI_T) fp)

#define SUPPORTED_CHANNELS_IE(fp) ((P_IE_SUPPORTED_CHANNELS_T)fp)
#define TIMEOUT_INTERVAL_IE(fp)	((IE_TIMEOUT_INTERVAL_T *)fp)


/*                                                          */
#define IS_BMCAST_MAC_ADDR(_pucDestAddr)            \
    ((BOOLEAN) (((PUINT_8)(_pucDestAddr))[0] & BIT(0)))

/*                                                        */
#define IS_UCAST_MAC_ADDR(_pucDestAddr)             \
    ((BOOLEAN) !(((PUINT_8)(_pucDestAddr))[0] & BIT(0)))

/*                                   */
#define COPY_MAC_ADDR(_pucDestAddr, _pucSrcAddr)    \
    kalMemCopy(_pucDestAddr, _pucSrcAddr, MAC_ADDR_LEN)

/*                                                   */
#define EQUAL_MAC_ADDR(_pucDestAddr, _pucSrcAddr)   \
    (!kalMemCmp(_pucDestAddr, _pucSrcAddr, MAC_ADDR_LEN))

/*                                                       */
#define UNEQUAL_MAC_ADDR(_pucDestAddr, _pucSrcAddr) \
    (kalMemCmp(_pucDestAddr, _pucSrcAddr, MAC_ADDR_LEN))


/*                                                */
#define EQUAL_SSID(pucSsid1, ucSsidLen1, pucSsid2, ucSsidLen2) \
    ((ucSsidLen1 <= ELEM_MAX_LEN_SSID) && \
	(ucSsidLen2 <= ELEM_MAX_LEN_SSID) && \
	((ucSsidLen1) == (ucSsidLen2)) && \
	!kalMemCmp(pucSsid1, pucSsid2, ucSsidLen1))

/*                                                */
#define UNEQUAL_SSID(pucSsid1, ucSsidLen1, pucSsid2, ucSsidLen2) \
    ((ucSsidLen1 > ELEM_MAX_LEN_SSID) || \
	(ucSsidLen2 > ELEM_MAX_LEN_SSID) || \
	((ucSsidLen1) != (ucSsidLen2)) || \
	kalMemCmp(pucSsid1, pucSsid2, ucSsidLen1))

/*                                                                                     */
#define COPY_SSID(pucDestSsid, ucDestSsidLen, pucSrcSsid, ucSrcSsidLen) \
    do { \
	ucDestSsidLen = ucSrcSsidLen; \
	if (ucSrcSsidLen) { \
	    ASSERT(ucSrcSsidLen <= ELEM_MAX_LEN_SSID); \
	    kalMemCopy(pucDestSsid, pucSrcSsid, ((ucSrcSsidLen > ELEM_MAX_LEN_SSID) ? ELEM_MAX_LEN_SSID : ucSrcSsidLen)); \
	} \
    } while (FALSE)

/*                          */
#define COPY_IE(pucDestIE, pucSrcIE) \
    do { \
	kalMemCopy((PUINT_8)pucDestIE, \
		   (PUINT_8)pucSrcIE,\
		   IE_SIZE(pucSrcIE)); \
    } while (FALSE)


#define IE_FOR_EACH(_pucIEsBuf, _u2IEsBufLen, _u2Offset) \
    for ((_u2Offset) = 0; ((((_u2Offset) + 2) <= (_u2IEsBufLen)) && (((_u2Offset) + IE_SIZE(_pucIEsBuf)) <= (_u2IEsBufLen))); \
	(_u2Offset) += IE_SIZE(_pucIEsBuf), (_pucIEsBuf) += IE_SIZE(_pucIEsBuf))


#define SET_EXT_CAP(_aucField, _ucFieldLength, _ucBit) \
			do { \
				if ((_ucBit) < ((_ucFieldLength) * 8)) { \
					PUINT_8 aucExtCap = (PUINT_8)(_aucField); \
					((aucExtCap)[(_ucBit) / 8]) |= BIT((_ucBit) % 8); \
				} \
			} while (FALSE)


/*                                                                              
                                                             
                                                                                
*/

/*                                                                              
                                                
                                                                                
*/

#endif				/*        */
