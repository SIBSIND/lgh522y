/*
                                                                                                
*/

/*                       
                                                                    
*/



/*
                        
  
                   
                                                                             
                                        
  
                   
                                                                                              
                                            
                                                                   
                                                   
  
                   
                                                                       
                                                    
  
                      
                                                             
                                                  
                                                                      
  
                   
                                                                                
    
  
*/

#ifndef _GL_CFG80211_H
#define _GL_CFG80211_H

/*                                                                              
                                                     
                                                                                
*/

/*                                                                              
                                                          
                                                                                
*/
#include <linux/kernel.h>
#include <linux/netdevice.h>
#include <linux/wireless.h>
#include <linux/ieee80211.h>
#include <net/cfg80211.h>

#include "gl_os.h"

/*                                                                              
                                                
                                                                                
*/
#if CONFIG_NL80211_TESTMODE
#define NL80211_DRIVER_TESTMODE_VERSION 2
#endif

/*                                                                              
                                                 
                                                                                
*/

#if CFG_SUPPORT_NFC_BEAM_PLUS

typedef struct _NL80211_DRIVER_SET_NFC_PARAMS {
	NL80211_DRIVER_TEST_MODE_PARAMS hdr;
	UINT_32 NFC_Enable;

} NL80211_DRIVER_SET_NFC_PARAMS, *P_NL80211_DRIVER_SET_NFC_PARAMS;

#endif

#if CONFIG_NL80211_TESTMODE

typedef struct _NL80211_DRIVER_GET_STA_STATISTICS_PARAMS {
	NL80211_DRIVER_TEST_MODE_PARAMS hdr;
	UINT_32 u4Version;
	UINT_32 u4Flag;
	UINT_8 aucMacAddr[MAC_ADDR_LEN];
} NL80211_DRIVER_GET_STA_STATISTICS_PARAMS, *P_NL80211_DRIVER_GET_STA_STATISTICS_PARAMS;

typedef enum _ENUM_TESTMODE_STA_STATISTICS_ATTR {
	NL80211_TESTMODE_STA_STATISTICS_INVALID = 0,
	NL80211_TESTMODE_STA_STATISTICS_VERSION,
	NL80211_TESTMODE_STA_STATISTICS_MAC,
	NL80211_TESTMODE_STA_STATISTICS_LINK_SCORE,
	NL80211_TESTMODE_STA_STATISTICS_FLAG,

	NL80211_TESTMODE_STA_STATISTICS_PER,
	NL80211_TESTMODE_STA_STATISTICS_RSSI,
	NL80211_TESTMODE_STA_STATISTICS_PHY_MODE,
	NL80211_TESTMODE_STA_STATISTICS_TX_RATE,

	NL80211_TESTMODE_STA_STATISTICS_TOTAL_CNT,
	NL80211_TESTMODE_STA_STATISTICS_THRESHOLD_CNT,
	NL80211_TESTMODE_STA_STATISTICS_AVG_PROCESS_TIME,

	NL80211_TESTMODE_STA_STATISTICS_FAIL_CNT,
	NL80211_TESTMODE_STA_STATISTICS_TIMEOUT_CNT,
	NL80211_TESTMODE_STA_STATISTICS_AVG_AIR_TIME,

	NL80211_TESTMODE_STA_STATISTICS_TC_EMPTY_CNT_ARRAY,
	NL80211_TESTMODE_STA_STATISTICS_TC_QUE_LEN_ARRAY,

	NL80211_TESTMODE_STA_STATISTICS_TC_AVG_QUE_LEN_ARRAY,
	NL80211_TESTMODE_STA_STATISTICS_TC_CUR_QUE_LEN_ARRAY,

	NL80211_TESTMODE_STA_STATISTICS_RESERVED_ARRAY,

	NL80211_TESTMODE_STA_STATISTICS_NUM
} ENUM_TESTMODE_STA_STATISTICS_ATTR;
#if CFG_AUTO_CHANNEL_SEL_SUPPORT
typedef struct _NL80211_DRIVER_GET_LTE_PARAMS {
	NL80211_DRIVER_TEST_MODE_PARAMS hdr;
	UINT_32 u4Version;
	UINT_32 u4Flag;
} NL80211_DRIVER_GET_LTE_PARAMS, *P_NL80211_DRIVER_GET_LTE_PARAMS;

typedef enum _ENUM_TESTMODE_AVAILABLE_CHAN_ATTR {
	NL80211_TESTMODE_AVAILABLE_CHAN_INVALID = 0,
	NL80211_TESTMODE_AVAILABLE_CHAN_2G_BASE_1,
	NL80211_TESTMODE_AVAILABLE_CHAN_5G_BASE_34,
	NL80211_TESTMODE_AVAILABLE_CHAN_5G_BASE_149,
	NL80211_TESTMODE_AVAILABLE_CHAN_5G_BASE_184,
	NL80211_TESTMODE_AVAILABLE_CHAN_NUM,
} ENUM_TESTMODE_AVAILABLE_CHAN_ATTR;
#endif
#endif
/*                                                                              
                                                  
                                                                                
*/

/*                                                                              
                                                   
                                                                                
*/

/*                                                                              
                                             
                                                                                
*/

/*                                                                              
                                                            
                                                                                
*/
/*                */
int
mtk_cfg80211_change_iface(struct wiphy *wiphy,
			  struct net_device *ndev,
			  enum nl80211_iftype type, u32 *flags, struct vif_params *params);


int
mtk_cfg80211_add_key(struct wiphy *wiphy,
		     struct net_device *ndev,
		     u8 key_index, bool pairwise, const u8 *mac_addr, struct key_params *params);


int
mtk_cfg80211_get_key(struct wiphy *wiphy,
		     struct net_device *ndev,
		     u8 key_index,
		     bool pairwise,
		     const u8 *mac_addr,
		     void *cookie, void (*callback) (void *cookie, struct key_params *)
    );


int
mtk_cfg80211_del_key(struct wiphy *wiphy,
		     struct net_device *ndev, u8 key_index, bool pairwise, const u8 *mac_addr);


int
mtk_cfg80211_set_default_key(struct wiphy *wiphy,
			     struct net_device *ndev, u8 key_index, bool unicast, bool multicast);


int
mtk_cfg80211_get_station(struct wiphy *wiphy,
			 struct net_device *ndev, u8 *mac, struct station_info *sinfo);


int mtk_cfg80211_scan(struct wiphy *wiphy,
#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 8, 0)
		      struct net_device *ndev,
#endif
		      struct cfg80211_scan_request *request);


int
mtk_cfg80211_connect(struct wiphy *wiphy,
		     struct net_device *ndev, struct cfg80211_connect_params *sme);


int mtk_cfg80211_disconnect(struct wiphy *wiphy, struct net_device *ndev, u16 reason_code);


int
mtk_cfg80211_join_ibss(struct wiphy *wiphy,
		       struct net_device *ndev, struct cfg80211_ibss_params *params);


int mtk_cfg80211_leave_ibss(struct wiphy *wiphy, struct net_device *ndev);


int
mtk_cfg80211_set_power_mgmt(struct wiphy *wiphy,
			    struct net_device *ndev, bool enabled, int timeout);


int
mtk_cfg80211_set_pmksa(struct wiphy *wiphy, struct net_device *ndev, struct cfg80211_pmksa *pmksa);


int
mtk_cfg80211_del_pmksa(struct wiphy *wiphy, struct net_device *ndev, struct cfg80211_pmksa *pmksa);


int mtk_cfg80211_flush_pmksa(struct wiphy *wiphy, struct net_device *ndev);

int
mtk_cfg80211_set_rekey_data(struct wiphy *wiphy,
			    struct net_device *dev, struct cfg80211_gtk_rekey_data *data);

int mtk_cfg80211_remain_on_channel(struct wiphy *wiphy,
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3, 8, 0)
				   struct wireless_dev *wdev,
#else
				   struct net_device *ndev,
#endif
				   struct ieee80211_channel *chan,
#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 8, 0)
				   enum nl80211_channel_type channel_type,
#endif
				   unsigned int duration, u64 *cookie);


int mtk_cfg80211_cancel_remain_on_channel(struct wiphy *wiphy,
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3, 8, 0)
					  struct wireless_dev *wdev,
#else
					  struct net_device *ndev,
#endif
					  u64 cookie);


int mtk_cfg80211_mgmt_tx(struct wiphy *wiphy,
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3, 8, 0)
			 struct wireless_dev *wdev,
#else
			 struct net_device *ndev,
#endif
			 struct ieee80211_channel *channel, bool offscan,
#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 8, 0)
			 enum nl80211_channel_type channel_type, bool channel_type_valid,
#endif
			 unsigned int wait,
			 const u8 *buf,
			 size_t len, bool no_cck, bool dont_wait_for_ack, u64 *cookie);

void mtk_cfg80211_mgmt_frame_register(IN struct wiphy *wiphy,
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3, 8, 0)
				      IN struct wireless_dev *wdev,
#else
				      IN struct net_device *ndev,
#endif
				      IN u16 frame_type, IN bool reg);

int mtk_cfg80211_mgmt_tx_cancel_wait(struct wiphy *wiphy,
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3, 8, 0)
				     struct wireless_dev *wdev,
#else
				     struct net_device *ndev,
#endif
				     u64 cookie);

#if CONFIG_NL80211_TESTMODE
#if CFG_AUTO_CHANNEL_SEL_SUPPORT
WLAN_STATUS
wlanoidQueryACSChannelList(IN P_ADAPTER_T prAdapter,
			   IN PVOID pvQueryBuffer,
			   IN UINT_32 u4QueryBufferLen, OUT PUINT_32 pu4QueryInfoLen);

int
mtk_cfg80211_testmode_get_lte_channel(IN struct wiphy *wiphy,
				      IN void *data, IN int len, IN P_GLUE_INFO_T prGlueInfo);
#endif
int
mtk_cfg80211_testmode_get_sta_statistics(IN struct wiphy *wiphy,
					 IN void *data, IN int len, IN P_GLUE_INFO_T prGlueInfo);

int
mtk_cfg80211_testmode_get_scan_done(IN struct wiphy *wiphy,
				    IN void *data, IN int len, IN P_GLUE_INFO_T prGlueInfo);
int mtk_cfg80211_testmode_cmd(IN struct wiphy *wiphy, IN void *data, IN int len);

int mtk_cfg80211_testmode_sw_cmd(IN struct wiphy *wiphy, IN void *data, IN int len);

#if CFG_SUPPORT_PASSPOINT
int mtk_cfg80211_testmode_hs20_cmd(IN struct wiphy *wiphy, IN void *data, IN int len);
#endif				/*                       */

#if CFG_SUPPORT_WAPI
int mtk_cfg80211_testmode_set_key_ext(IN struct wiphy *wiphy, IN void *data, IN int len);
#endif
#if CFG_SUPPORT_NFC_BEAM_PLUS
int
mtk_cfg80211_testmode_get_scan_done(IN struct wiphy *wiphy,
				    IN void *data, IN int len, IN P_GLUE_INFO_T prGlueInfo);
#endif
#else
#error "Please ENABLE kernel config (CONFIG_NL80211_TESTMODE) to support Wi-Fi Direct"
#endif

int
mtk_cfg80211_sched_scan_start(IN struct wiphy *wiphy,
			      IN struct net_device *ndev,
			      IN struct cfg80211_sched_scan_request *request);

int mtk_cfg80211_sched_scan_stop(IN struct wiphy *wiphy, IN struct net_device *ndev);

int
mtk_cfg80211_assoc(struct wiphy *wiphy,
		   struct net_device *ndev, struct cfg80211_assoc_request *req);


int
mtk_cfg80211_change_station(struct wiphy *wiphy,
			    struct net_device *ndev, u8 *mac, struct station_parameters *params);


int
mtk_cfg80211_add_station(struct wiphy *wiphy,
			 struct net_device *ndev, u8 *mac, struct station_parameters *params);


int mtk_cfg80211_del_station(struct wiphy *wiphy, struct net_device *ndev, u8 *mac);

int
mtk_cfg80211_tdls_mgmt(struct wiphy *wiphy,
		       struct net_device *dev,
		       u8 *peer,
		       u8 action_code,
		       u8 dialog_token, u16 status_code, const u8 *buf, size_t len);

int
mtk_cfg80211_tdls_oper(struct wiphy *wiphy,
		       struct net_device *dev, u8 *peer, enum nl80211_tdls_operation oper);

/*                                                                              
                                                
                                                                                
*/

#endif				/*                */
