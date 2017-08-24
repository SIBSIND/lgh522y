/* 
        
                       
  
                
          
  
                    
                                                              
  
               
                           
  
                       
                  
              
  
 */

#ifndef _VAL_TYPES_PUBLIC_H_
#define _VAL_TYPES_PUBLIC_H_

//                      
//                      

#ifdef __cplusplus
extern "C" {
#endif

#define IRQ_STATUS_MAX_NUM 16                   //                                                     

#define VCODEC_THREAD_MAX_NUM 16                //                                           

/*                                                                             
                                               
                                                                             */

typedef void                VAL_VOID_T;         //                       
typedef char                VAL_BOOL_T;         //                       
typedef char                VAL_CHAR_T;         //                       
typedef signed char         VAL_INT8_T;         //                              
typedef signed short        VAL_INT16_T;        //                               
typedef signed int         VAL_INT32_T;        //                             
typedef unsigned char       VAL_UCHAR_T;        //                                
typedef unsigned char       VAL_UINT8_T;        //                                
typedef unsigned short      VAL_UINT16_T;       //                            
typedef unsigned int       VAL_UINT32_T;       //                               
typedef unsigned long long  VAL_UINT64_T;       //                                     
typedef long long           VAL_INT64_T;        //                            
typedef unsigned long       VAL_HANDLE_T;       //                                        
typedef signed long         VAL_LONG_T;       // 
typedef unsigned long       VAL_ULONG_T;       // 

#define VAL_NULL        (0)                     //               
#define VAL_TRUE        (1)                     //               
#define VAL_FALSE       (0)                     //                

#define VAL_RESOLUTION_CHANGED       (2)        //                                                                               


/* 
                   
                    
                   
                                                                             
 */
typedef enum _VAL_MEM_CODEC_T
{
    VAL_MEM_CODEC_FOR_VENC = 0,                 //                           
    VAL_MEM_CODEC_FOR_VDEC,                     //                           
    VAL_MEM_CODEC_MAX = 0xFFFFFFFF              //            
} VAL_MEM_CODEC_T;


/* 
                   
                    
                   
                                                           
 */
typedef enum _VAL_CHIP_NAME_T
{
    VAL_CHIP_NAME_MT6516 = 0,                   //         
    VAL_CHIP_NAME_MT6571,                       //         
    VAL_CHIP_NAME_MT6572,                       //         
    VAL_CHIP_NAME_MT6573,                       //         
    VAL_CHIP_NAME_MT6575,                       //         
    VAL_CHIP_NAME_MT6577,                       //         
    VAL_CHIP_NAME_MT6589,                       //         
    VAL_CHIP_NAME_MT6582,                       //         
    VAL_CHIP_NAME_MT8135,                       //         
    VAL_CHIP_NAME_ROME,                         //       
    VAL_CHIP_NAME_MT6592,                       //         
    VAL_CHIP_NAME_MT8127,                       //         
    VAL_CHIP_NAME_MT6752,                       //        
    VAL_CHIP_NAME_MAX = 0xFFFFFFFF              //            
} VAL_CHIP_NAME_T;

/* 
                   
                       
                   
                                                              
 */
typedef enum _VAL_CHIP_VARIANT_T
{
    VAL_CHIP_VARIANT_MT6571L = 0,       //          
    VAL_CHIP_VARIANT_MAX = 0xFFFFFFFF  //            
} VAL_CHIP_VARIANT_T;

/* 
                   
                      
                   
                                     
 */
typedef enum _VAL_DRIVER_TYPE_T
{
    VAL_DRIVER_TYPE_NONE = 0,                   //       
    VAL_DRIVER_TYPE_MP4_ENC,                    //              
    VAL_DRIVER_TYPE_MP4_DEC,                    //              
    VAL_DRIVER_TYPE_H263_ENC,                   //                
    VAL_DRIVER_TYPE_H263_DEC,                   //                
    VAL_DRIVER_TYPE_H264_ENC,                   //                
    VAL_DRIVER_TYPE_H264_DEC,                   //                
    VAL_DRIVER_TYPE_SORENSON_SPARK_DEC,         //                         
    VAL_DRIVER_TYPE_VC1_SP_DEC,                 //                              
    VAL_DRIVER_TYPE_RV9_DEC,                    //              
    VAL_DRIVER_TYPE_MP1_MP2_DEC,                //                  
    VAL_DRIVER_TYPE_XVID_DEC,                   //               
    VAL_DRIVER_TYPE_DIVX4_DIVX5_DEC,            //                  
    VAL_DRIVER_TYPE_VC1_MP_WMV9_DEC,            //                                   
    VAL_DRIVER_TYPE_RV8_DEC,                    //              
    VAL_DRIVER_TYPE_WMV7_DEC,                   //               
    VAL_DRIVER_TYPE_WMV8_DEC,                   //               
    VAL_DRIVER_TYPE_AVS_DEC,                    //              
    VAL_DRIVER_TYPE_DIVX_3_11_DEC,              //                   
    VAL_DRIVER_TYPE_H264_DEC_MAIN,              //                                                             
    VAL_DRIVER_TYPE_H264_DEC_MAIN_CABAC,        //                                                                                     
    VAL_DRIVER_TYPE_VP8_DEC,                    //              
    VAL_DRIVER_TYPE_MP2_DEC,                    //                
    VAL_DRIVER_TYPE_VP9_DEC,                    //              
    VAL_DRIVER_TYPE_VP8_ENC,                    //              
    VAL_DRIVER_TYPE_VC1_ADV_DEC,                //                      
    VAL_DRIVER_TYPE_VC1_DEC,                    //                                  
    VAL_DRIVER_TYPE_JPEG_ENC,                   //               
    VAL_DRIVER_TYPE_HEVC_ENC,                   //               
    VAL_DRIVER_TYPE_HEVC_DEC,                   //               
    VAL_DRIVER_TYPE_H264_ENC_LIVEPHOTO,         //               
    VAL_DRIVER_TYPE_MAX = 0xFFFFFFFF            //                  
} VAL_DRIVER_TYPE_T;


/* 
                   
                 
                   
                                                    
 */
typedef enum _VAL_RESULT_T
{
    VAL_RESULT_NO_ERROR = 0,                    //                                 
    VAL_RESULT_INVALID_DRIVER,                  //                              
    VAL_RESULT_INVALID_PARAMETER,               //                                 
    VAL_RESULT_INVALID_MEMORY,                  //                              
    VAL_RESULT_INVALID_ISR,                     //                                   
    VAL_RESULT_ISR_TIMEOUT,                     //                                   
    VAL_RESULT_UNKNOWN_ERROR,                   //                
    VAL_RESULT_RESTARTSYS,                      //              
    VAL_RESULT_MAX = 0xFFFFFFFF                 //             
} VAL_RESULT_T;


/* 
                   
                    
                   
                                                          
 */
typedef enum _VAL_MEM_ALIGN_T
{
    VAL_MEM_ALIGN_1 = 1,                        //                   
    VAL_MEM_ALIGN_2 = (1 << 1),                 //                   
    VAL_MEM_ALIGN_4 = (1 << 2),                 //                   
    VAL_MEM_ALIGN_8 = (1 << 3),                 //                   
    VAL_MEM_ALIGN_16 = (1 << 4),                //                    
    VAL_MEM_ALIGN_32 = (1 << 5),                //                    
    VAL_MEM_ALIGN_64 = (1 << 6),                //                    
    VAL_MEM_ALIGN_128 = (1 << 7),               //                     
    VAL_MEM_ALIGN_256 = (1 << 8),               //                     
    VAL_MEM_ALIGN_512 = (1 << 9),               //                     
    VAL_MEM_ALIGN_1K = (1 << 10),               //                    
    VAL_MEM_ALIGN_2K = (1 << 11),               //                    
    VAL_MEM_ALIGN_4K = (1 << 12),               //                    
    VAL_MEM_ALIGN_8K = (1 << 13),               //                    
    VAL_MEM_ALIGN_MAX = 0xFFFFFFFF              //                            
} VAL_MEM_ALIGN_T;


/* 
                   
                   
                   
                                                
 */
typedef enum _VAL_MEM_TYPE_T
{
    VAL_MEM_TYPE_FOR_SW = 0,                    //                         
    VAL_MEM_TYPE_FOR_HW_CACHEABLE,              //                                   
    VAL_MEM_TYPE_FOR_HW_CACHEABLE_MCI,          //                                                         
    VAL_MEM_TYPE_FOR_HW_NONCACHEABLE,           //                                       
    VAL_MEM_TYPE_MAX = 0xFFFFFFFF               //                  
} VAL_MEM_TYPE_T;


/* 
                 
                  
                   
                                          
 */
typedef struct _VAL_MEM_ADDR_T
{
    VAL_ULONG_T    u4VA;                       //                           
    VAL_ULONG_T    u4PA;                       //                            
    VAL_ULONG_T    u4Size;                     //                
} VAL_MEM_ADDR_T;


/* 
                 
                          
                   
                                       
 */
typedef struct _VAL_VCODEC_THREAD_ID_T
{
    VAL_UINT32_T    u4tid1; //                                     
    VAL_UINT32_T    u4tid2; //                                     
    VAL_UINT32_T    u4VCodecThreadNum;                          //                      
    VAL_UINT32_T    u4VCodecThreadID[VCODEC_THREAD_MAX_NUM];    //                                     
} VAL_VCODEC_THREAD_ID_T;


/* 
                 
                                 
                   
                                            
 */
typedef struct _VAL_VCODEC_CPU_LOADING_INFO_T
{
    unsigned long long  _cpu_idle_time;         //                      
    unsigned long long  _thread_cpu_time;       //                        
    unsigned long long  _sched_clock;           //                    
    unsigned int        _inst_count;            //                   
} VAL_VCODEC_CPU_LOADING_INFO_T;


/* 
                 
                              
                   
                                              
 */
typedef struct _VAL_VCODEC_CPU_OPP_LIMIT_T
{
    int limited_freq;                           //                    
    int limited_cpu;                            //                   
    int enable;                                 //              
} VAL_VCODEC_CPU_OPP_LIMIT_T;


/* 
                 
                                  
                   
                                             
 */
typedef struct _VAL_VCODEC_M4U_BUFFER_CONFIG_T
{
    VAL_MEM_CODEC_T eMemCodec;                  //                                           
    VAL_UINT32_T    cache_coherent;             //                             
    VAL_UINT32_T    security;                   //                       
} VAL_VCODEC_M4U_BUFFER_CONFIG_T;


/* 
                 
                
                   
                                                  
 */
typedef struct _VAL_MEMORY_T
{
    VAL_MEM_TYPE_T  eMemType;                   //                                      
    VAL_ULONG_T     u4MemSize;                  //                                         
    VAL_VOID_T      *pvMemVa;                   //                                      
    VAL_VOID_T      *pvMemPa;                   //                                       
    VAL_MEM_ALIGN_T eAlignment;                 //                                             
    VAL_VOID_T      *pvAlignMemVa;              //                                            
    VAL_VOID_T      *pvAlignMemPa;              //                                             
    VAL_MEM_CODEC_T eMemCodec;                  //                                             
    VAL_UINT32_T    i4IonShareFd;
    struct ion_handle *pIonBufhandle;
    VAL_VOID_T      *pvReserved;                //                                  
    VAL_ULONG_T     u4ReservedSize;             //                                                    
#ifdef __EARLY_PORTING__
    VAL_VOID_T      *pvReservedPmem;            //                                  
#endif
} VAL_MEMORY_T;

/* 
                 
                     
                   
                                                                 
 */
typedef struct __VAL_RECORD_SIZE_T
{
    VAL_UINT32_T    u4FrmWidth;                 //                                            
    VAL_UINT32_T    u4FrmHeight;                //                                             
    VAL_UINT32_T    u4BufWidth;                 //                                          
    VAL_UINT32_T    u4BufHeight;                //                                           
} VAL_RECORD_SIZE_T;


/* 
                 
              
                   
                                        
 */
typedef struct _VAL_ATOI_T
{
    VAL_VOID_T      *pvStr;                     //                                                  
    VAL_INT32_T     i4Result;                   //                                                                                            
    VAL_VOID_T      *pvReserved;                //                                  
    VAL_UINT32_T    u4ReservedSize;             //                                                    
} VAL_ATOI_T;


/* 
                 
                
                   
                                          
 */
typedef struct _VAL_STRSTR_T
{
    VAL_VOID_T      *pvStr;                     //                                             
    VAL_VOID_T      *pvStrSearch;               //                                                
    VAL_VOID_T      *pvStrResult;               //                                                                                                                       
    VAL_VOID_T      *pvReserved;                //                                  
    VAL_UINT32_T    u4ReservedSize;             //                                                    
} VAL_STRSTR_T;


/* 
                 
             
                   
                                                
 */
typedef struct _VAL_ISR_T
{
    VAL_VOID_T          *pvHandle;              //                                         
    VAL_UINT32_T        u4HandleSize;           //                                                 
    VAL_DRIVER_TYPE_T   eDriverType;            //                           
    VAL_VOID_T          *pvIsrFunction;         //                            
    VAL_VOID_T          *pvReserved;            //                                  
    VAL_UINT32_T        u4ReservedSize;         //                                                    
    VAL_UINT32_T        u4TimeoutMs;            //                             
    VAL_UINT32_T        u4IrqStatusNum;                     //                                                    
    VAL_UINT32_T        u4IrqStatus[IRQ_STATUS_MAX_NUM];    //                                                      
} VAL_ISR_T;


/* 
                 
                 
                   
                                                           
 */
typedef struct _VAL_HW_LOCK_T
{
    VAL_VOID_T          *pvHandle;              //                                         
    VAL_UINT32_T        u4HandleSize;           //                                                 
    VAL_VOID_T          *pvLock;                //                               
    VAL_UINT32_T        u4TimeoutMs;            //                          
    VAL_VOID_T          *pvReserved;            //                                  
    VAL_UINT32_T        u4ReservedSize;         //                                                    
    VAL_DRIVER_TYPE_T   eDriverType;            //                           
    VAL_BOOL_T          bSecureInst;            //                                                                           
} VAL_HW_LOCK_T;


/* 
                 
              
                   
                                        
 */
typedef struct _VAL_TIME_T
{
    VAL_UINT32_T    u4Sec;                      //                  
    VAL_UINT32_T    u4uSec;                     //                        
} VAL_TIME_T;


/* 
                   
                   
                   
                                               
 */
typedef enum _VAL_SET_TYPE_T
{
    VAL_SET_TYPE_CURRENT_SCENARIO,              //                       
    VAL_SET_TYPE_MCI_PORT_CONFIG,                //                      
    VAL_SET_TYPE_M4U_PORT_CONFIG                //                      
} VAL_SET_TYPE_T;

/* 
                   
                   
                   
                                               
 */
typedef enum _VAL_GET_TYPE_T
{
    VAL_GET_TYPE_CURRENT_SCENARIO_CNT,          //                                       
    VAL_GET_TYPE_LCM_INFO,                      //               
} VAL_GET_TYPE_T;

/* 
                   
                        
                   
                                                             
 */
typedef enum _VAL_VCODEC_SCENARIO_T
{
    VAL_VCODEC_SCENARIO_VENC_1080P  = 0x1,          //                         
    VAL_VCODEC_SCENARIO_VDEC_1080P  = 0x2,          //                 
    VAL_VCODEC_SCENARIO_VENC_WFD    = 0x4,          //                        
} VAL_VCODEC_SCENARIO_T;

/* 
                 
                          
                   
                                                    
 */
typedef struct _VAL_CURRENT_SCENARIO_T
{
    VAL_UINT32_T    u4Scenario;             //                                    
    VAL_UINT32_T    u4OnOff;                //                                                         
} VAL_CURRENT_SCENARIO_T;

/* 
                 
                              
                   
                                                                    
 */
typedef struct _VAL_CURRENT_SCENARIO_CNT_T
{
    VAL_UINT32_T    u4Scenario;             //                             
    VAL_UINT32_T    u4ScenarioRefCount;     //                                         
} VAL_CURRENT_SCENARIO_CNT_T;


/* 
                 
                         
                   
                                                   
 */
typedef struct _VAL_MCI_PORT_CONFIG_T
{
    VAL_MEM_CODEC_T    eMemCodecType;       //                                     
    VAL_UINT32_T       u4Config;            //                       
} VAL_MCI_PORT_CONFIG_T;

/* 
                 
                  
                   
                                        
 */
typedef struct _VAL_LCM_INFO_T
{
    VAL_UINT32_T        u4Width;            //              
    VAL_UINT32_T        u4Height;           //               
} VAL_LCM_INFO_T;

#define VAL_M4U_PORT_ALL       (-1)        //                                                                    

/* 
                 
                          
                   
                                                            
 */
typedef struct _VAL_M4U_MPORT_CONFIG_T
{
    VAL_MEM_CODEC_T eMemCodec;                  //                                          
    VAL_UINT32_T        i4M4UPortID;                     //                                                                        
    VAL_BOOL_T          bSecurity;                           //                             
    VAL_BOOL_T          bVirtuality;                           //                               
} VAL_M4U_MPORT_CONFIG_T;


/*                            */
#define META_HANDLE_LIST_MAX    50

typedef struct _VAL_MetaBufInfo
{
    void               *pNativeHandle;
    VAL_ULONG_T         u4VA;
    VAL_ULONG_T         u4PA;
    VAL_UINT32_T        u4BuffSize;
    VAL_BOOL_T          bUseION;
    int                 fd;
    struct ion_handle  *pIonBufhandle;
} VAL_MetaBufInfo;

typedef struct _VAL_MetaHandleList
{
    int                 mIonDevFd;
    VAL_MetaBufInfo     rMetaBufInfo[META_HANDLE_LIST_MAX];
    VAL_BOOL_T          fgSeqHdrEncoded;
} VAL_MetaHandleList;

typedef struct _VAL_BufInfo
{
    VAL_UINT8_T         fgIsConfigData;
    VAL_ULONG_T         u4BSVA;
    VAL_UINT8_T         fgBSStatus;
    VAL_UINT8_T         fgIsKeyFrame;
    VAL_UINT32_T        u4BSSize;
} VAL_BufInfo;
/*                            */


#ifdef __cplusplus
}
#endif

#endif //                             
