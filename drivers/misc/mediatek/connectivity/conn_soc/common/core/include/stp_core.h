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



#ifndef _STP_CORE_H
#define _STP_CORE_H

#include "osal_typedef.h"
#include "osal.h"
#include "stp_exp.h"
#include "psm_core.h"
#include "btm_core.h"
#include "stp_btif.h"
/*                                                                              
                                                     
                                                                                
*/
#define CFG_STP_CORE_CTX_SPIN_LOCK (0)

#define WMT_LTE_COEX_FLAG (0x16)

/*                                                      */
/*                                                                              
                                             
                                                                                
*/

#define CONFIG_POWER_SAVING_SUPPORT


#define PFX                         "[STP] "
#define STP_LOG_DBG                  4
#define STP_LOG_PKHEAD               3
#define STP_LOG_INFO                 2
#define STP_LOG_WARN                 1
#define STP_LOG_ERR                  0

extern unsigned int gStpDbgLvl;

#define STP_DBG_FUNC(fmt, arg...)    if(gStpDbgLvl >= STP_LOG_DBG){  osal_dbg_print(PFX "%s: "  fmt, __FUNCTION__ ,##arg);}
#define STP_INFO_FUNC(fmt, arg...)   if(gStpDbgLvl >= STP_LOG_INFO){ osal_dbg_print(PFX "%s:[I] "  fmt, __FUNCTION__ ,##arg);}
#define STP_WARN_FUNC(fmt, arg...)   if(gStpDbgLvl >= STP_LOG_WARN){ osal_dbg_print(PFX "%s:[W] "  fmt, __FUNCTION__ ,##arg);}
#define STP_ERR_FUNC(fmt, arg...)    if(gStpDbgLvl >= STP_LOG_ERR){  osal_dbg_print(PFX "%s:[E] "   fmt, __FUNCTION__ ,##arg);}
#define STP_TRC_FUNC(f)              if(gStpDbgLvl >= STP_LOG_DBG){  osal_dbg_print(PFX "<%s> <%d>\n", __FUNCTION__, __LINE__);}

#define STP_DUMP_PACKET_HEAD(a, b, c)     if(gStpDbgLvl >= STP_LOG_PKHEAD){stp_dump_data(a, b, c);}
#define STP_TRACE_FUNC(fmt, arg...)        if(gStpDbgLvl >= STP_LOG_DBG){  osal_dbg_print(PFX "%s: "  fmt, __FUNCTION__ ,##arg);}

#define STP_MODE_BIT(x) (0x1UL << x)
#define MTKSTP_UART_FULL_MODE 	  STP_MODE_BIT(0)
#define MTKSTP_UART_MAND_MODE 	  STP_MODE_BIT(1)
#define MTKSTP_BTIF_FULL_MODE 	  STP_MODE_BIT(2)
#define MTKSTP_BTIF_MAND_MODE 	  STP_MODE_BIT(3)
#define MTKSTP_SDIO_MODE          STP_MODE_BIT(4)

#define MTKSTP_BUFFER_SIZE  (16384)

/*                                                      */
/*                    */
#define OP_FUNCTION_ACTIVE         0

/*               */
#define STATUS_OP_INVALID          0
#define STATUS_FUNCTION_INVALID    1

#define STATUS_FUNCTION_ACTIVE     31
#define STATUS_FUNCTION_INACTIVE   32

#define MTKSTP_CRC_SIZE     (2)
#define MTKSTP_HEADER_SIZE  (4)
#define MTKSTP_SEQ_SIZE     (8)

/*                               */
#define MTKSTP_WINSIZE      (7)
#define MTKSTP_TX_TIMEOUT   (180) /*                             */
#define MTKSTP_RETRY_LIMIT  (10)

#define INDEX_INC(idx)  \
{                       \
    idx++;              \
    idx &= 0x7;         \
}

#define INDEX_DEC(idx)  \
{                       \
    idx--;              \
    idx &= 0x7;         \
}

/*                                                                              
                                                          
                                                                                
*/



/*                                                                              
                                                
                                                                                
*/

/*                                                                              
                                                 
                                                                                
*/
typedef INT32 (*IF_TX)(const UINT8 *data, const UINT32 size, UINT32 *written_size);
/*              */
typedef INT32 (*EVENT_SET)(UINT8 function_type);
typedef INT32 (*EVENT_TX_RESUME)(UINT8 winspace);
typedef INT32 (*FUNCTION_STATUS)(UINT8 type, UINT8 op);
typedef INT32   (*WMT_NOTIFY_FUNC_T)(UINT32 action);
typedef INT32   (*BTM_NOTIFY_WMT_FUNC_T)(INT32);

#if CFG_STP_CORE_CTX_SPIN_LOCK
typedef OSAL_UNSLEEPABLE_LOCK STP_CTX_LOCK, *PSTP_CTX_LOCK;
#else
typedef OSAL_SLEEPABLE_LOCK STP_CTX_LOCK, *PSTP_CTX_LOCK;
#endif


typedef struct
{
    /*                  */
    IF_TX           cb_if_tx;
    /*              */
    EVENT_SET       cb_event_set;
    EVENT_TX_RESUME cb_event_tx_resume;
    FUNCTION_STATUS cb_check_funciton_status;
}mtkstp_callback;

typedef enum
{
    MTKSTP_SYNC = 0,
    MTKSTP_SEQ,
    MTKSTP_ACK,
    MTKSTP_NAK,
    MTKSTP_TYPE,
    MTKSTP_LENGTH,
    MTKSTP_CHECKSUM,
    MTKSTP_DATA,
    MTKSTP_CRC1,
    MTKSTP_CRC2,
    MTKSTP_RESYNC1,
    MTKSTP_RESYNC2,
    MTKSTP_RESYNC3,
    MTKSTP_RESYNC4,
    MTKSTP_FW_MSG,
} mtkstp_parser_state;

typedef struct
{
    mtkstp_parser_state  state;
    UINT8            seq;
    UINT8            ack;
    UINT8            nak;
    UINT8            type;
    UINT16           length;
    UINT8            checksum;
    UINT16           crc;
#if 1
	UINT8			 wmtsubtype;
#endif
} mtkstp_parser_context_struct;

typedef struct
{
    UINT8           txseq;  //                      
    UINT8           txack;  //                  
    UINT8           rxack;  //                  
    UINT8           winspace;   //                            
    UINT8           expected_rxseq;  //                      
    UINT8           retry_times;
} mtkstp_sequence_context_struct;

typedef struct
{
    //                            
    OSAL_UNSLEEPABLE_LOCK  mtx;
    UINT8           buffer[MTKSTP_BUFFER_SIZE];
    UINT32          read_p;
    UINT32          write_p;
} mtkstp_ring_buffer_struct;

typedef struct
{
    UINT8  inband_rst_set;
    UINT32 rx_counter;  //                                           
    UINT8  rx_buf[MTKSTP_BUFFER_SIZE];  //                                                     
    UINT32 tx_read;     //                     
    UINT32 tx_write;    //                      
    UINT8  tx_buf[MTKSTP_BUFFER_SIZE];  //                     
    UINT32 tx_start_addr[MTKSTP_SEQ_SIZE];  //                            
    UINT32 tx_length[MTKSTP_SEQ_SIZE];      //                               
    mtkstp_ring_buffer_struct ring[MTKSTP_MAX_TASK_NUM];    //                                      
    mtkstp_parser_context_struct parser;        //                         
    mtkstp_sequence_context_struct sequence;    //                               
    //                        
    //                                
    STP_CTX_LOCK stp_mutex;
    //                                                        
    OSAL_TIMER tx_timer;

    MTKSTP_PSM_T *psm;
    MTKSTP_BTM_T *btm;
    UINT8 f_enable; /*                  */
    UINT8 f_ready; /*                   */
    UINT8 f_pending_type;
    UINT8 f_coredump; /*                                                                             */
    UINT8 en_coredump;
    /*                                                  */
    MTK_WCN_BOOL f_bluez;
    MTK_WCN_BOOL f_dbg_en;
    MTK_WCN_BOOL f_autorst_en;

    

    /*                                      */
    UINT32 f_mode;
    
    /*                                    */
    UINT32 f_wmt_last_close;

	/*                                                     */
	UINT32 f_evt_err_assert;
}mtkstp_context_struct;

/*                                                                              
                                                  
                                                                                
*/

/*                                                                              
                                                   
                                                                                
*/


/*                                                                              
                                                            
                                                                                
*/

INT32 stp_send_data_no_ps(UINT8 *buffer, UINT32 length, UINT8 type);

/*                                                                            
          
                   
             
                  
            
                                                     
         
                                         
                                                                            */
extern INT32 mtk_wcn_stp_init(const mtkstp_callback * const cb_func);

/*                                                                            
          
                     
             
                    
            
       
         
                                         
                                                                            */
extern INT32 mtk_wcn_stp_deinit(void);

/*                                                                            
          
                     
             
                     
            
                                                        
         
                                       
                                                                            */
extern INT32 mtk_wcn_stp_enable(INT32 value);

/*                                                                            
          
                    
             
                      
            
                                                         
         
                                       
                                                                            */
extern INT32 mtk_wcn_stp_ready(INT32 value);


/*                                                                            
          
                                  
             
                                     
            
                                                              
         
                                   
                                                                            */
extern INT32 mtk_wcn_stp_coredump_start_ctrl(UINT32 value);

/*                                                                            
          
                                 
             
                                     
            
       
         
                                                                        
                                                                            */
extern INT32 mtk_wcn_stp_coredump_start_get(VOID);


/*                                                                            
          
                            
             
                                                
            
                                      
                                             
                                           
         
                              
                                                                            */
extern INT32 mtk_wcn_stp_send_data_raw(const PUINT8 buffer, const UINT32 length, const UINT8 type);

/*                                                                            
          
                            
             
                        
            
                                                                          
         
       
                                                                            */
extern void mtk_wcn_stp_set_mode(UINT32 sdio_flag);

/*                                                                            
          
                                   
             
                                 
            
        
         
                                                        
                                                                            */
extern MTK_WCN_BOOL mtk_wcn_stp_is_uart_fullset_mode(void);

/*                                                                            
          
                                
             
                                   
            
        
         
                                                            
                                                                            */
extern MTK_WCN_BOOL mtk_wcn_stp_is_uart_mand_mode(void);
/*                                                                            
          
                                   
             
                                 
            
        
         
                                                        
                                                                            */
extern MTK_WCN_BOOL mtk_wcn_stp_is_btif_fullset_mode(void);

/*                                                                            
          
                                
             
                                   
            
        
         
                                                            
                                                                            */
extern MTK_WCN_BOOL mtk_wcn_stp_is_btif_mand_mode(void);

/*                                                                            
          
                           
             
                        
            
        
         
                                                  
                                                                            */
extern MTK_WCN_BOOL mtk_wcn_stp_is_sdio_mode(void);


/*                                                                            
          
                        
             
                                             
            
        
         
       
                                                                            */
extern void mtk_wcn_stp_inband_reset(void);

/*                                                                            
          
                        
             
                                  
            
        
         
       
                                                                            */
extern void mtk_wcn_stp_test_cmd(INT32 no);

/*                                                                            
          
                        
             
                                    
            
                                                                                     
         
       
                                                                            */
extern void mtk_wcn_stp_debug_ctrl(INT32 func_no, INT32 func_op, INT32 func_param);
/*                                                                            
          
                    
             
                        
            
        
         
       
                                                                            */
extern void mtk_wcn_stp_flush_context(void);

/*                                                                            
          
                       
             
                         
            
        
         
       
                                                                            */
extern void mtk_wcn_stp_flush_rx_queue(UINT32 type);

/*                                                                            
          
                         
             
                         
            
                                
         
       
                                                                            */
extern void mtk_wcn_stp_set_dbg_mode(MTK_WCN_BOOL dbg_mode);

/*                                                                            
          
                          
             
                          
            
                                       
         
       
                                                                            */
extern void mtk_wcn_stp_set_auto_rst(MTK_WCN_BOOL auto_rst);

/*               */

/*                                                                            
          
                             
             
                                                               
            
 
         
                                   
                                                                            */
extern int mtk_wcn_stp_psm_notify_stp(const UINT32 action);

extern int mtk_wcn_stp_set_psm_state(MTKSTP_PSM_STATE_T state);

/*                                                                            
          
                         
             
                 
            
                                             
         
                                   
                                                                            */
extern int mtk_wcn_stp_psm_enable(int idle_time_to_sleep);

/*                                                                            
          
                          
             
                  
            
       
         
                                   
                                                                            */
extern int mtk_wcn_stp_psm_disable(void);

/*                                                                            
          
                        
             
                                           
            
       
         
                                   
                                                                            */
extern int mtk_wcn_stp_psm_reset(void);
extern void stp_do_tx_timeout(void);

/*                                                                            
          
                          
             
                                   
            
                                         
         
                                   
                                                                            */
extern int mtk_wcn_stp_btm_get_dmp(char *buf, int *len);

extern int mtk_wcn_stp_dbg_enable(void);

extern int mtk_wcn_stp_dbg_disable(void);

extern void mtk_wcn_stp_set_if_tx_type (ENUM_STP_TX_IF_TYPE stp_if_type);

extern int mtk_wcn_sys_if_rx(UINT8 *data, INT32 size);

extern MTK_WCN_BOOL mtk_wcn_stp_dbg_level(UINT32 dbglevel);

extern INT32 mtk_wcn_stp_dbg_dump_package(VOID);

extern int  stp_drv_init(void);

extern void stp_drv_exit(void);

extern INT32 mtk_wcn_stp_dbg_log_ctrl(UINT32 on);

extern INT32 mtk_wcn_stp_coredump_flag_ctrl(UINT32 on);

extern INT32 mtk_wcn_stp_coredump_flag_get(VOID);
extern INT32 mtk_wcn_stp_notify_sleep_for_thermal(void);


extern INT32 mtk_wcn_stp_set_wmt_last_close(UINT32 value);

/*                     */
extern INT32 mtk_wcn_stp_open_btif(VOID);
extern INT32 mtk_wcn_stp_close_btif(VOID);
extern INT32 mtk_wcn_stp_rxcb_register(MTK_WCN_BTIF_RX_CB rx_cb);
extern INT32 mtk_wcn_stp_tx(UINT8 *pBuf,UINT32 len,UINT32 *written_len);
extern INT32 mtk_wcn_stp_wakeup_consys(VOID);
extern INT32 mtk_wcn_stp_dpidle_ctrl(ENUM_BTIF_DPIDLE_CTRL en_flag);
extern INT32 mtk_wcn_stp_lpbk_ctrl(ENUM_BTIF_LPBK_MODE mode);
extern INT32 mtk_wcn_stp_logger_ctrl(ENUM_BTIF_DBG_ID flag);
extern VOID mtk_wcn_stp_ctx_save(VOID);
extern VOID mtk_wcn_stp_ctx_restore(VOID);
extern INT32 mtk_wcn_stp_wmt_evt_err_trg_assert(VOID);
extern VOID mtk_wcn_stp_set_wmt_evt_err_trg_assert(UINT32 value);
extern UINT32 mtk_wcn_stp_get_wmt_evt_err_trg_assert(VOID);
/*                                                                              
                                                
                                                                                
*/

#endif /*              */
