/*
                                                                                               
*/

/*                  
                                                                 

                                                                       
                                                

*/



/*
                 
  
 */

 /*                                                                              
                                                     
                                                                                
*/

/*                                                                              
                                                          
                                                                                
*/
#include "precomp.h"

#if CFG_SUPPORT_HOTSPOT_2_0

/*                                                                              
                                                
                                                                                
*/

/*                                                                              
                                                 
                                                                                
*/

/*                                                                              
                                                  
                                                                                
*/

/*                                                                              
                                                   
                                                                                
*/

/*                                                                              
                                             
                                                                                
*/

/*                                                                              
                                                             
                                                                                
*/

/*                                                                              
                                                
                                                                                
*/

/*                                                                            */
/* 
                                                                                                  
 
                                            
                                                  
 
              
*/
/*                                                                            */
VOID
hs20GenerateInterworkingIE (
    IN P_ADAPTER_T          prAdapter,
    OUT P_MSDU_INFO_T       prMsduInfo
    )
{
}

/*                                                                            */
/* 
                                                                                                        
 
                                            
                                                  
 
              
*/
/*                                                                            */
VOID
hs20GenerateRoamingConsortiumIE (
    IN P_ADAPTER_T          prAdapter,
    OUT P_MSDU_INFO_T       prMsduInfo
    )
{
}

/*                                                                            */
/* 
                                                                                           
 
                                            
                                                  
 
              
*/
/*                                                                            */
VOID
hs20GenerateHS20IE (
    IN P_ADAPTER_T          prAdapter,
    OUT P_MSDU_INFO_T       prMsduInfo
    )
{
    PUINT_8                 pucBuffer;

    ASSERT(prAdapter);
    ASSERT(prMsduInfo);

    if (prMsduInfo->ucNetworkType != NETWORK_TYPE_AIS_INDEX)
        return;

    pucBuffer = (PUINT_8)((ULONG)prMsduInfo->prPacket +
                          (UINT_32)prMsduInfo->u2FrameLength);

    /*                             */
    if (prAdapter->prGlueInfo->u2HS20AssocInfoIELen) {
        kalMemCopy(pucBuffer, &prAdapter->prGlueInfo->aucHS20AssocInfoIE, prAdapter->prGlueInfo->u2HS20AssocInfoIELen);
        prMsduInfo->u2FrameLength += prAdapter->prGlueInfo->u2HS20AssocInfoIELen;
    }

}


VOID
hs20FillExtCapIE (
    P_ADAPTER_T     prAdapter,
    P_BSS_INFO_T    prBssInfo,
    P_MSDU_INFO_T   prMsduInfo
    )
{
    P_EXT_CAP_T     prExtCap;

    ASSERT(prAdapter);
    ASSERT(prMsduInfo);

    /*                              */
    prExtCap = (P_EXT_CAP_T)
               (((PUINT_8) prMsduInfo->prPacket) + prMsduInfo->u2FrameLength);

    prExtCap->ucId = ELEM_ID_EXTENDED_CAP;
	if (prAdapter->prGlueInfo->fgConnectHS20AP == TRUE)
		prExtCap->ucLength = ELEM_MAX_LEN_EXT_CAP;
	else
		prExtCap->ucLength = 3 - ELEM_HDR_LEN;

	kalMemZero(prExtCap->aucCapabilities, prExtCap->ucLength);

    prExtCap->aucCapabilities[0] = ELEM_EXT_CAP_DEFAULT_VAL;

    if (prBssInfo->eCurrentOPMode != OP_MODE_INFRASTRUCTURE) {
        prExtCap->aucCapabilities[0] &= ~ELEM_EXT_CAP_PSMP_CAP;
    }

	if (prAdapter->prGlueInfo->fgConnectHS20AP == TRUE)	{
		SET_EXT_CAP(prExtCap->aucCapabilities, ELEM_MAX_LEN_EXT_CAP, ELEM_EXT_CAP_BSS_TRANSITION_BIT);
		SET_EXT_CAP(prExtCap->aucCapabilities, ELEM_MAX_LEN_EXT_CAP, ELEM_EXT_CAP_UTC_TSF_OFFSET_BIT);
		SET_EXT_CAP(prExtCap->aucCapabilities, ELEM_MAX_LEN_EXT_CAP, ELEM_EXT_CAP_INTERWORKING_BIT);

		/*                        */
		SET_EXT_CAP(prExtCap->aucCapabilities, ELEM_MAX_LEN_EXT_CAP, ELEM_EXT_CAP_WNM_NOTIFICATION_BIT);    
	}

    printk("IE_SIZE(prExtCap) = %d, %d %d\n", IE_SIZE(prExtCap), ELEM_HDR_LEN, ELEM_MAX_LEN_EXT_CAP);
    ASSERT(IE_SIZE(prExtCap) <= (ELEM_HDR_LEN + ELEM_MAX_LEN_EXT_CAP));

    prMsduInfo->u2FrameLength += IE_SIZE(prExtCap);
}


/*                                                                            */
/* 
                                                                                
 
                                            
                                             
 
              
*/
/*                                                                            */
VOID
hs20FillProreqExtCapIE(
    IN P_ADAPTER_T          prAdapter,
    OUT PUINT_8             pucIE
    )
{
    P_EXT_CAP_T     prExtCap;

    ASSERT(prAdapter);

    /*                              */
    prExtCap = (P_EXT_CAP_T)pucIE;

    prExtCap->ucId = ELEM_ID_EXTENDED_CAP;
	if (prAdapter->prGlueInfo->fgConnectHS20AP == TRUE)
		prExtCap->ucLength = ELEM_MAX_LEN_EXT_CAP;
	else
		prExtCap->ucLength = 3 - ELEM_HDR_LEN;

	kalMemZero(prExtCap->aucCapabilities, prExtCap->ucLength);

    prExtCap->aucCapabilities[0] = ELEM_EXT_CAP_DEFAULT_VAL;

	if (prAdapter->prGlueInfo->fgConnectHS20AP == TRUE) {
		SET_EXT_CAP(prExtCap->aucCapabilities, ELEM_MAX_LEN_EXT_CAP, ELEM_EXT_CAP_BSS_TRANSITION_BIT);
		SET_EXT_CAP(prExtCap->aucCapabilities, ELEM_MAX_LEN_EXT_CAP, ELEM_EXT_CAP_UTC_TSF_OFFSET_BIT);
		SET_EXT_CAP(prExtCap->aucCapabilities, ELEM_MAX_LEN_EXT_CAP, ELEM_EXT_CAP_INTERWORKING_BIT);

		/*                        */
		SET_EXT_CAP(prExtCap->aucCapabilities, ELEM_MAX_LEN_EXT_CAP, ELEM_EXT_CAP_WNM_NOTIFICATION_BIT);
	}

}


/*                                                                            */
/* 
                                                                       
 
                                            
                                             
 
              
*/
/*                                                                            */
VOID
hs20FillHS20IE(
    IN P_ADAPTER_T          prAdapter,
    OUT PUINT_8             pucIE
    )
{
    P_IE_HS20_INDICATION_T prHS20IndicationIe;
    //                         
    UINT_8 aucWfaOui[] = VENDOR_OUI_WFA_SPECIFIC;

    //                                              

    prHS20IndicationIe = (P_IE_HS20_INDICATION_T)pucIE;

    prHS20IndicationIe->ucId = ELEM_ID_VENDOR;
    prHS20IndicationIe->ucLength = sizeof(IE_HS20_INDICATION_T) - ELEM_HDR_LEN;
    prHS20IndicationIe->aucOui[0] = aucWfaOui[0];
    prHS20IndicationIe->aucOui[1] = aucWfaOui[1];
    prHS20IndicationIe->aucOui[2] = aucWfaOui[2];
    prHS20IndicationIe->ucType = VENDOR_OUI_TYPE_HS20;
    prHS20IndicationIe->ucHotspotConfig = 0x00;//                            
}


/*                                                                            */
/* 
                                                                                                            
 
                                            
                                                     
 
                                        
*/
/*                                                                            */
UINT_32
hs20CalculateHS20RelatedIEForProbeReq (
    IN P_ADAPTER_T          prAdapter,
    IN PUINT_8              pucTargetBSSID
    )
{
    UINT_32 u4IeLength;

    if (0) /*                     */
		return 0;
	
    u4IeLength = sizeof(IE_HS20_INDICATION_T) + /*                           */ + (ELEM_HDR_LEN + ELEM_MAX_LEN_EXT_CAP);

    if(!pucTargetBSSID) {
        //                           
    }

    return u4IeLength;
}


/*                                                                            */
/* 
                                                                                                
 
                                            
                                                     
                                            
 
                         
*/
/*                                                                            */
WLAN_STATUS
hs20GenerateHS20RelatedIEForProbeReq (
    IN P_ADAPTER_T          prAdapter,
    IN PUINT_8              pucTargetBSSID,
    OUT PUINT_8             prIE
    )
{
    if (0) /*                     */
	    return 0;
#if 0
    P_HS20_INFO_T prHS20Info;

    prHS20Info = &(prAdapter->rWifiVar.rHS20Info);


    /*
                                                
        */
    hs20FillInterworkingIE(prAdapter,
                            prHS20Info->ucAccessNetworkOptions,
                            prHS20Info->ucVenueGroup,
                            prHS20Info->ucVenueType,
                            pucTargetBSSID,
                            prIE);
    prIE += IE_SIZE(prIE);
#endif
    /*
                                   
        */
    hs20FillProreqExtCapIE(prAdapter, prIE);
    prIE += IE_SIZE(prIE);

    /*
                                            
        */
    hs20FillHS20IE(prAdapter, prIE);
    prIE += IE_SIZE(prIE);

    return WLAN_STATUS_SUCCESS;
}

BOOLEAN
hs20IsGratuitousArp(
	IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T  prCurrSwRfb
    )
{
    PUINT_8 pucSenderIP = prCurrSwRfb->pvHeader + ETHER_HEADER_LEN + ARP_SENDER_IP_OFFSET;
    PUINT_8 pucTargetIP = prCurrSwRfb->pvHeader + ETHER_HEADER_LEN + ARP_TARGET_IP_OFFSET;
    PUINT_8 pucSenderMac = ((PUINT_8)prCurrSwRfb->pvHeader + ETHER_HEADER_LEN + ARP_SNEDER_MAC_OFFSET);
#if CFG_HS20_DEBUG && 0
//                                    
//                                                     
	PUINT_8 pucTargetMac = ((PUINT_8)prCurrSwRfb->pvHeader + ETHER_HEADER_LEN + ARP_TARGET_MAC_OFFSET);
#endif

#if CFG_HS20_DEBUG && 0
    PUINT_16 pu2ArpOper = (PUINT_16)((PUINT_8)prCurrSwRfb->pvHeader + ETHER_HEADER_LEN + ARP_OPERATION_OFFSET);

    kalPrint("Recv ARP 0x%04X\n", htons(*pu2ArpOper));
    kalPrint("SENDER["MACSTR"] [%d:%d:%d:%d]\n", MAC2STR(pucSenderMac), *pucSenderIP, *(pucSenderIP+1), *(pucSenderIP+2), *(pucSenderIP+3));
    kalPrint("TARGET["MACSTR"] [%d:%d:%d:%d]\n", MAC2STR(pucTargetMac), *pucTargetIP, *(pucTargetIP+1), *(pucTargetIP+2), *(pucTargetIP+3));
#endif

	//                
    if(!kalMemCmp(pucSenderIP, pucTargetIP, 4)) {
        kalPrint("Drop Gratuitous ARP from ["MACSTR"] [%d:%d:%d:%d]\n", MAC2STR(pucSenderMac), *pucTargetIP, *(pucTargetIP+1), *(pucTargetIP+2), *(pucTargetIP+3));
        return TRUE;
    }
    return FALSE;
}

BOOLEAN
hs20IsUnsolicitedNeighborAdv(
	IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T  prCurrSwRfb
    )
{
    PUINT_8 pucIpv6Protocol = ((PUINT_8)prCurrSwRfb->pvHeader + ETHER_HEADER_LEN + IPV6_HDR_IP_PROTOCOL_OFFSET);	

    //                                                                                  
    if(*pucIpv6Protocol == IPV6_PROTOCOL_ICMPV6) {
        PUINT_8 pucICMPv6Type = ((PUINT_8)prCurrSwRfb->pvHeader + ETHER_HEADER_LEN + IPV6_HDR_LEN + ICMPV6_TYPE_OFFSET);
        //                                                                                            
        if(*pucICMPv6Type == ICMPV6_TYPE_NEIGHBOR_ADVERTISEMENT) {
            PUINT_8 pucICMPv6Flag = ((PUINT_8)prCurrSwRfb->pvHeader + ETHER_HEADER_LEN + IPV6_HDR_LEN + ICMPV6_FLAG_OFFSET);
            PUINT_8 pucSrcMAC = ((PUINT_8)prCurrSwRfb->pvHeader + MAC_ADDR_LEN);

#if CFG_HS20_DEBUG
            kalPrint("NAdv Flag [%02X] [R(%d)\\S(%d)\\O(%d)]\n",
                        *pucICMPv6Flag,
                        (UINT_8)(*pucICMPv6Flag & ICMPV6_FLAG_ROUTER_BIT) >> 7,
                        (UINT_8)(*pucICMPv6Flag & ICMPV6_FLAG_SOLICITED_BIT) >> 6,
                        (UINT_8)(*pucICMPv6Flag & ICMPV6_FLAG_OVERWRITE_BIT) >> 5);
#endif
            if(!(*pucICMPv6Flag & ICMPV6_FLAG_SOLICITED_BIT)) {
                kalPrint("Drop Unsolicited Neighbor Advertisement from ["MACSTR"] \n", MAC2STR(pucSrcMAC));
                return TRUE;
            }
        }
    }

    return FALSE;
}


#if CFG_ENABLE_GTK_FRAME_FILTER
BOOLEAN
hs20IsForgedGTKFrame(
    IN P_ADAPTER_T prAdapter,
    IN P_BSS_INFO_T prBssInfo,
    IN P_SW_RFB_T prCurrSwRfb
    )
{
    P_CONNECTION_SETTINGS_T prConnSettings = &prAdapter->rWifiVar.rConnSettings;
    PUINT_8                 pucEthDestAddr = prCurrSwRfb->pvHeader;

    //                                                     
    return FALSE;

    if((prConnSettings->eEncStatus != ENUM_ENCRYPTION_DISABLED) && IS_BMCAST_MAC_ADDR(pucEthDestAddr)) {
        UINT_8 ucIdx = 0;
        PUINT_32 prIpAddr, prPacketDA;
        PUINT_16 pu2PktIpVer = (PUINT_16)((PUINT_8)prCurrSwRfb->pvHeader + (ETHER_HEADER_LEN - ETHER_TYPE_LEN));

        if(*pu2PktIpVer == htons(ETH_P_IPV4)) {
            if(!prBssInfo->prIpV4NetAddrList) {
                return FALSE;
            }
            for(ucIdx = 0; ucIdx < prBssInfo->prIpV4NetAddrList->ucAddrCount; ucIdx++) {
                prIpAddr = (PUINT_32)&prBssInfo->prIpV4NetAddrList->arNetAddr[ucIdx].aucIpAddr[0];
                prPacketDA = (PUINT_32)((PUINT_8)prCurrSwRfb->pvHeader + ETHER_HEADER_LEN + IPV4_HDR_IP_DST_ADDR_OFFSET);

                if(kalMemCmp(prIpAddr, prPacketDA, 4) == 0) {
                    kalPrint("Drop FORGED IPv4 packet\n");
                    return TRUE;
                }
            }
        }
#ifdef  CONFIG_IPV6
        else if(*pu2PktIpVer == htons(ETH_P_IPV6)) {
            UINT_8 aucIPv6Mac[MAC_ADDR_LEN];
            PUINT_8 pucIdx = prCurrSwRfb->pvHeader + ETHER_HEADER_LEN + IPV6_HDR_IP_DST_ADDR_MAC_HIGH_OFFSET;

            kalMemCopy(&aucIPv6Mac[0], pucIdx, 3);
            pucIdx += 5;
            kalMemCopy(&aucIPv6Mac[3], pucIdx, 3);
            kalPrint("Get IPv6 frame Dst IP MAC part "MACSTR"\n", MAC2STR(aucIPv6Mac));
            if(EQUAL_MAC_ADDR(aucIPv6Mac, prBssInfo->aucOwnMacAddr)) {
                kalPrint("Drop FORGED IPv6 packet\n");
                return TRUE;
            }
        }
#endif
    }

    return FALSE;
}
#endif

BOOLEAN
hs20IsUnsecuredFrame(
    IN P_ADAPTER_T prAdapter,
    IN P_BSS_INFO_T prBssInfo,
    IN P_SW_RFB_T prCurrSwRfb
    )
{
    PUINT_16 pu2PktIpVer = (PUINT_16)((PUINT_8)prCurrSwRfb->pvHeader + (ETHER_HEADER_LEN - ETHER_TYPE_LEN));

    //                                               
#if CFG_HS20_DEBUG & 0
    UINT_8 i = 0;

    kalPrint("===============================================");
    for(i = 0; i < 96; i++) {
        if(!(i % 16)) {
            kalPrint("\n");
        }
        kalPrint("%02X ", *((PUINT_8)prCurrSwRfb->pvHeader + i));
    }
    kalPrint("\n");
#endif

#if CFG_ENABLE_GTK_FRAME_FILTER
    if(hs20IsForgedGTKFrame(prAdapter, prBssInfo, prCurrSwRfb)) {
        return TRUE;
    }
    else 
#endif
    if(*pu2PktIpVer == htons(ETH_P_ARP)) {
        return hs20IsGratuitousArp(prAdapter, prCurrSwRfb);
    }
    else if(*pu2PktIpVer == htons(ETH_P_IPV6)) {
        return hs20IsUnsolicitedNeighborAdv(prAdapter, prCurrSwRfb);
    }

    return FALSE;
}

BOOLEAN
hs20IsFrameFilterEnabled(
    IN P_ADAPTER_T prAdapter,
    IN P_BSS_INFO_T prBssInfo
    )
{
#if 1
    if (prAdapter->prGlueInfo->fgConnectHS20AP ) {
        return TRUE;
    }
#else
    PARAM_SSID_T rParamSsid;
    P_BSS_DESC_T prBssDesc;

    rParamSsid.u4SsidLen = prBssInfo->ucSSIDLen;
    COPY_SSID(rParamSsid.aucSsid, rParamSsid.u4SsidLen, prBssInfo->aucSSID, prBssInfo->ucSSIDLen);

    prBssDesc = scanSearchBssDescByBssidAndSsid(prAdapter, prBssInfo->aucBSSID, TRUE, &rParamSsid);
    if(!prBssDesc) {
        return FALSE;
    }

    if(prBssDesc->fgIsSupportHS20) {
      if(!(prBssDesc->ucHotspotConfig & ELEM_HS_CONFIG_DGAF_DISABLED_MASK)) {
        return TRUE;
      } else {
        //                                      
        return FALSE;
      }
    }
#endif

    //                                                                
    return TRUE;
}


WLAN_STATUS
hs20SetBssidPool (
    IN P_ADAPTER_T                  prAdapter,
    IN PVOID                        pvBuffer,
    IN ENUM_NETWORK_TYPE_INDEX_T    eNetTypeIdx
    )
{
    P_PARAM_HS20_SET_BSSID_POOL prParamBssidPool = (P_PARAM_HS20_SET_BSSID_POOL)pvBuffer;
    P_HS20_INFO_T prHS20Info;
    UINT_8 ucIdx;

    prHS20Info = &(prAdapter->rWifiVar.rHS20Info);

    printk("[%s]Set Bssid Pool! enable[%d] num[%d]\n", __func__, prParamBssidPool->fgIsEnable, prParamBssidPool->ucNumBssidPool);

    for(ucIdx = 0; ucIdx < prParamBssidPool->ucNumBssidPool; ucIdx++) {
        COPY_MAC_ADDR(prHS20Info->arBssidPool[ucIdx].aucBSSID, &prParamBssidPool->arBSSID[ucIdx]);
        printk("[%s][%d]["MACSTR"]\n", __func__, ucIdx, MAC2STR(prHS20Info->arBssidPool[ucIdx].aucBSSID));
    }
    prHS20Info->fgIsHS2SigmaMode = prParamBssidPool->fgIsEnable;
    prHS20Info->ucNumBssidPoolEntry = prParamBssidPool->ucNumBssidPool;

#if 0
	wlanClearScanningResult(prAdapter);
#endif

    return WLAN_STATUS_SUCCESS;
}


#endif

