/*
* Copyright (C) 2011-2014 MediaTek Inc.
* 
* This program is free software: you can redistribute it and/or modify it under the terms of the 
* GNU General Public License version 2 as published by the Free Software Foundation.
* 
* This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
* without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
* See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along with this program.
* If not, see <http://www.gnu.org/licenses/>.
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


/*                                                                              
                                                
                                                                                
*/

#define P2P_MODE_INF_NAME "p2p%d";
#if CFG_TC1_FEATURE
#define AP_MODE_INF_NAME "wlan%d";
#else
#define AP_MODE_INF_NAME "ap%d";
#endif
//                           
//                          

#define RUNNING_P2P_MODE 0
#define RUNNING_AP_MODE 1

/*                                                                              
                                                 
                                                                                
*/

/*                                                                              
                                                  
                                                                                
*/



/*                                                                              
                                                   
                                                                                
*/

/*                                                                     
                                   
                                        
                                       
*/
static PUCHAR ifname = P2P_MODE_INF_NAME;
static UINT_16 mode = RUNNING_P2P_MODE;

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
p2pCheckInterfaceName(
    VOID
    )
{

    if(mode) {
        mode = RUNNING_AP_MODE;
        ifname = AP_MODE_INF_NAME;
    }
#if 0
    UINT_32 ifLen = 0;

    if(ifname) {
        ifLen = strlen(ifname);

        if(ifLen > MAX_INF_NAME_LEN) {
            ifname[MAX_INF_NAME_LEN] = '\0';
        }
        else if( ifLen < MIN_INF_NAME_LEN  ) {
            ifname = P2P_MODE_INF_NAME;
        }
    } else {
        ifname = P2P_MODE_INF_NAME;
    }
#endif
}


extern UINT_8 g_aucBufIpAddr[32];

void p2pHandleSystemSuspend(void)
{
    struct net_device *prDev = NULL;
    P_GLUE_INFO_T prGlueInfo = NULL;
    UINT_8  ip[4] = { 0 };
    UINT_32 u4NumIPv4 = 0;
#ifdef  CONFIG_IPV6
    UINT_8  ip6[16] = { 0 };     //                                                
    UINT_32 u4NumIPv6 = 0;
#endif
    UINT_32 i;
	P_PARAM_NETWORK_ADDRESS_IP prParamIpAddr;

    printk(KERN_INFO "*********p2pEarlySuspend************\n");

    if(!wlanExportGlueInfo(&prGlueInfo)) {
        printk(KERN_INFO "*********p2pEarlySuspend ignored************\n");
        return;
    }

    ASSERT(prGlueInfo);
    //                                            
    prDev = prGlueInfo->prP2PInfo->prDevHandler;
    ASSERT(prDev);

    //                         
    if(!prDev || !(prDev->ip_ptr)||\
        !((struct in_device *)(prDev->ip_ptr))->ifa_list||\
        !(&(((struct in_device *)(prDev->ip_ptr))->ifa_list->ifa_local))){
        printk(KERN_INFO "ip is not avaliable.\n");
        return;
    }

    //                          
    kalMemCopy(ip, &(((struct in_device *)(prDev->ip_ptr))->ifa_list->ifa_local), sizeof(ip));
    printk(KERN_INFO"ip is %d.%d.%d.%d\n",
            ip[0],ip[1],ip[2],ip[3]);

   //                                                                 
    if (!((ip[0] == 0) &&
         (ip[1] == 0) &&
         (ip[2] == 0) &&
         (ip[3] == 0))) {
        u4NumIPv4++;
    }

#ifdef  CONFIG_IPV6
    //                         
    if(!prDev || !(prDev->ip6_ptr)||\
        !((struct in_device *)(prDev->ip6_ptr))->ifa_list||\
        !(&(((struct in_device *)(prDev->ip6_ptr))->ifa_list->ifa_local))){
        printk(KERN_INFO "ipv6 is not avaliable.\n");
        return;
    }
    //                          
    kalMemCopy(ip6, &(((struct in_device *)(prDev->ip6_ptr))->ifa_list->ifa_local), sizeof(ip6));
    printk(KERN_INFO"ipv6 is %d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d\n",
            ip6[0],ip6[1],ip6[2],ip6[3],
            ip6[4],ip6[5],ip6[6],ip6[7],
            ip6[8],ip6[9],ip6[10],ip6[11],
            ip6[12],ip6[13],ip6[14],ip6[15]
            );
    //                                                                 

    if (!((ip6[0] == 0) &&
         (ip6[1] == 0) &&
         (ip6[2] == 0) &&
         (ip6[3] == 0) &&
         (ip6[4] == 0) &&
         (ip6[5] == 0))) {
    }

#endif
    //                          
    {
        WLAN_STATUS rStatus = WLAN_STATUS_FAILURE;
        UINT_32 u4SetInfoLen = 0;
//                                
        UINT_32 u4Len = OFFSET_OF(PARAM_NETWORK_ADDRESS_LIST, arAddress);
        P_PARAM_NETWORK_ADDRESS_LIST prParamNetAddrList = (P_PARAM_NETWORK_ADDRESS_LIST)g_aucBufIpAddr;//       
        P_PARAM_NETWORK_ADDRESS prParamNetAddr = prParamNetAddrList->arAddress;

        kalMemZero(g_aucBufIpAddr, sizeof(g_aucBufIpAddr));

        prParamNetAddrList->u4AddressCount = u4NumIPv4 + u4NumIPv6;
        prParamNetAddrList->u2AddressType = PARAM_PROTOCOL_ID_TCP_IP;
        for (i = 0; i < u4NumIPv4; i++) {
            prParamNetAddr->u2AddressLength = sizeof(PARAM_NETWORK_ADDRESS_IP);//   
            prParamNetAddr->u2AddressType = PARAM_PROTOCOL_ID_TCP_IP;;
#if 0
            kalMemCopy(prParamNetAddr->aucAddress, ip, sizeof(ip));
            prParamNetAddr = (P_PARAM_NETWORK_ADDRESS)((UINT_32)prParamNetAddr + sizeof(ip));
            u4Len += OFFSET_OF(PARAM_NETWORK_ADDRESS, aucAddress) + sizeof(ip);
#else
            prParamIpAddr = (P_PARAM_NETWORK_ADDRESS_IP)prParamNetAddr->aucAddress;
            kalMemCopy(&prParamIpAddr->in_addr, ip, sizeof(ip));

//                                                                                                                                                            

            prParamNetAddr = (P_PARAM_NETWORK_ADDRESS) ((ULONG) prParamNetAddr +
            (ULONG) (prParamNetAddr->u2AddressLength + OFFSET_OF(PARAM_NETWORK_ADDRESS, aucAddress)));

            u4Len += OFFSET_OF(PARAM_NETWORK_ADDRESS, aucAddress) + sizeof(PARAM_NETWORK_ADDRESS_IP);
#endif
        }
#ifdef  CONFIG_IPV6
        for (i = 0; i < u4NumIPv6; i++) {
            prParamNetAddr->u2AddressLength = 6;;
            prParamNetAddr->u2AddressType = PARAM_PROTOCOL_ID_TCP_IP;;
            kalMemCopy(prParamNetAddr->aucAddress, ip6, sizeof(ip6));
//                                                                                              

            prParamNetAddr = (P_PARAM_NETWORK_ADDRESS) ((ULONG) prParamNetAddr +
            (ULONG) (prParamNetAddr->u2AddressLength + OFFSET_OF(PARAM_NETWORK_ADDRESS, aucAddress)));

            u4Len += OFFSET_OF(PARAM_NETWORK_ADDRESS, aucAddress) + sizeof(ip6);
       }
#endif
        ASSERT(u4Len <= sizeof(g_aucBufIpAddr/*      */));

        rStatus = kalIoctl(prGlueInfo,
                wlanoidSetP2pSetNetworkAddress,
                (PVOID)prParamNetAddrList,
                u4Len,
                FALSE,
                FALSE,
                TRUE,
                TRUE,
                &u4SetInfoLen);

        if (rStatus != WLAN_STATUS_SUCCESS) {
            printk(KERN_INFO DRV_NAME"set HW pattern filter fail 0x%x\n", rStatus);
        }
    }
}


void p2pHandleSystemResume(void)
{
    struct net_device *prDev = NULL;
    P_GLUE_INFO_T prGlueInfo = NULL;
    UINT_8  ip[4] = { 0 };
#ifdef  CONFIG_IPV6
    UINT_8  ip6[16] = { 0 };     //                                                
#endif

    printk(KERN_INFO "*********wlanP2PLateResume************\n");
    if(!wlanExportGlueInfo(&prGlueInfo)) {
        printk(KERN_INFO "*********p2pLateResume ignored************\n");
        return;
    }

    ASSERT(prGlueInfo);
    //                                            
    prDev = prGlueInfo->prP2PInfo->prDevHandler;
    ASSERT(prDev);

   //                         
    if(!prDev || !(prDev->ip_ptr)||\
        !((struct in_device *)(prDev->ip_ptr))->ifa_list||\
        !(&(((struct in_device *)(prDev->ip_ptr))->ifa_list->ifa_local))){
        printk(KERN_INFO "ip is not avaliable.\n");
        return;
    }

    //                          
    kalMemCopy(ip, &(((struct in_device *)(prDev->ip_ptr))->ifa_list->ifa_local), sizeof(ip));
    printk(KERN_INFO"ip is %d.%d.%d.%d\n",
            ip[0],ip[1],ip[2],ip[3]);

#ifdef  CONFIG_IPV6
    //                         
    if(!prDev || !(prDev->ip6_ptr)||\
        !((struct in_device *)(prDev->ip6_ptr))->ifa_list||\
        !(&(((struct in_device *)(prDev->ip6_ptr))->ifa_list->ifa_local))){
        printk(KERN_INFO "ipv6 is not avaliable.\n");
        return;
    }
    //                          
    kalMemCopy(ip6, &(((struct in_device *)(prDev->ip6_ptr))->ifa_list->ifa_local), sizeof(ip6));
    printk(KERN_INFO"ipv6 is %d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d\n",
            ip6[0],ip6[1],ip6[2],ip6[3],
            ip6[4],ip6[5],ip6[6],ip6[7],
            ip6[8],ip6[9],ip6[10],ip6[11],
            ip6[12],ip6[13],ip6[14],ip6[15]
            );
#endif
    //                         
    {
        WLAN_STATUS rStatus = WLAN_STATUS_FAILURE;
        UINT_32 u4SetInfoLen = 0;
//                                
        UINT_32 u4Len = sizeof(PARAM_NETWORK_ADDRESS_LIST);
        P_PARAM_NETWORK_ADDRESS_LIST prParamNetAddrList = (P_PARAM_NETWORK_ADDRESS_LIST)g_aucBufIpAddr;//       

        kalMemZero(g_aucBufIpAddr, sizeof(g_aucBufIpAddr));

        prParamNetAddrList->u4AddressCount = 0;
        prParamNetAddrList->u2AddressType = PARAM_PROTOCOL_ID_TCP_IP;

        ASSERT(u4Len <= sizeof(g_aucBufIpAddr/*      */));
        rStatus = kalIoctl(prGlueInfo,
                wlanoidSetP2pSetNetworkAddress,
                (PVOID)prParamNetAddrList,
                u4Len,
                FALSE,
                FALSE,
                TRUE,
                TRUE,
                &u4SetInfoLen);

        if (rStatus != WLAN_STATUS_SUCCESS) {
            printk(KERN_INFO DRV_NAME"set HW pattern filter fail 0x%x\n", rStatus);
        }
    }
}

/*                                                                            */
/* 
        
                                                                
                                                                       
                                                                             
                       
*/
/*                                                                            */
BOOLEAN
p2pLaunch(
    P_GLUE_INFO_T prGlueInfo
    )
{

    printk("p2p Launch\n");

    if(prGlueInfo->prAdapter->fgIsP2PRegistered == TRUE) {
        printk("p2p already registered\n");
        return FALSE;
    }
    else if(glRegisterP2P(prGlueInfo, ifname, (BOOLEAN)mode)) {
        prGlueInfo->prAdapter->fgIsP2PRegistered = TRUE;

        printk("Launch success, fgIsP2PRegistered TRUE.\n");
        return TRUE;
    }
    else {
        printk("Launch Fail\n");
    }

    return FALSE;
}


VOID
p2pSetMode (
    IN BOOLEAN fgIsAPMOde
    ) 
{
    if (fgIsAPMOde) {
        mode = RUNNING_AP_MODE;
        ifname = AP_MODE_INF_NAME;
    }
    else {
        mode = RUNNING_P2P_MODE;
        ifname = P2P_MODE_INF_NAME;
    }

    return;
} /*            */


/*                                                                            */
/* 
        
                                                                  
                                                                         
                                                                             

                       
*/
/*                                                                            */
BOOLEAN
p2pRemove(
    P_GLUE_INFO_T prGlueInfo
    )
{
    if(prGlueInfo->prAdapter->fgIsP2PRegistered == FALSE) {
        printk("p2p is not Registered.\n");
        return FALSE;
    }
    else {
        /*                                                  */
        if(IS_P2P_ACTIVE(prGlueInfo->prAdapter)) {
            p2pStopImmediate(prGlueInfo);
        }
        prGlueInfo->prAdapter->fgIsP2PRegistered = FALSE;
        glUnregisterP2P(prGlueInfo);
        /*                           */
        return TRUE;
    }
    return FALSE;
}

#if 0
/*                                                                            */
/* 
                                                                                
                                                                       
                                         
 
                       
*/
/*                                                                            */
static int initP2P(void)
{
    P_GLUE_INFO_T prGlueInfo;

    /*                               */
    p2pCheckInterfaceName();

    printk( KERN_INFO DRV_NAME "InitP2P, Ifname: %s, Mode: %s\n", ifname, mode ? "AP":"P2P");

    /*                                                            */
    wlanSubModRegisterInitExit(p2pLaunch, p2pRemove, P2P_MODULE);

    /*                                    
                                                               
        */
    /*                                        */
    if(wlanExportGlueInfo(&prGlueInfo)) {
        wlanSubModInit(prGlueInfo);
        return ( prGlueInfo->prAdapter->fgIsP2PRegistered? 0: -EIO);
    }

    return 0;
} /*                  */


/*                                                                            */
/* 
                                                                               
                                                                              
                                                             
 
                
*/
/*                                                                            */
//                    
static VOID __exit exitP2P(void)
{
    P_GLUE_INFO_T prGlueInfo;

    printk( KERN_INFO DRV_NAME "ExitP2P\n");

    /*                                        */
    if(wlanExportGlueInfo(&prGlueInfo)) {
        wlanSubModExit(prGlueInfo);
    }
    /*                                                              */
    wlanSubModRegisterInitExit(NULL, NULL, P2P_MODULE);
} /*                  */
#endif

