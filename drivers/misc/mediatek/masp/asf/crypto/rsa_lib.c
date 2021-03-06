#include "sec_osal_light.h"
#include "sec_typedef.h"
#include "rsa_def.h"
#include "alg_sha1.h"
#include "bgn_export.h"
#include "sec_cust_struct.h"
#include "sec_auth.h"
#include "sec_error.h"
#include "sec_rom_info.h"
#include "sec_boot_lib.h"
#include "sec_sign_header.h"
#include "sec_key_util.h"
#include "sec_log.h"

/*                                                                         
               
                                                                          */
#define MOD                         "AUTHEN"

/*                                                                          
                  
                                                                         */
uchar                               bRsaKeyInit = false;
uchar                               bRsaImgKeyInit = false;

/*                                                                         
                     
                                                                          */
extern uchar                        sha1sum[];
extern rsa_ctx                      rsa;
extern uchar                        rsa_ci[];
extern AND_ROMINFO_T                rom_info;
CUST_SEC_INTER                      g_cus_inter;

/*                                                                         
                    
                                                                          */
int lib_init_key (uchar *nKey, uint32 nKey_len, uchar *eKey, uint32 eKey_len)
{
    int ret = SEC_OK;

    /*                                */
    /*                      
                                                               */
    /*                                */       
    if(true == bRsaKeyInit)
    {
        return ret;
    }

    bRsaKeyInit = true;        

    if(0 != mcmp(rom_info.m_id,RI_NAME,RI_NAME_LEN))
    {
        SMSG(true,"[%s] error. key not found\n",MOD);
        ret = ERR_RSA_KEY_NOT_FOUND;
        goto _end;
    }

    /*                                */
    /*                                */
    /*                                */
    memset( &rsa, 0, sizeof(rsa_ctx));

    /*                                */
    /*                                */
    /*                                */    
    rsa.len = RSA_KEY_SIZE;

    /*                                */
    /*                                */
    /*                                */    
    sec_decode_key( nKey, nKey_len, 
                    rom_info.m_SEC_KEY.crypto_seed, 
                    sizeof(rom_info.m_SEC_KEY.crypto_seed));

    /*                                */
    /*                                */
    /*                                */    
    bgn_read_str( &rsa.N , 16, (char*)nKey, nKey_len );    
    bgn_read_str( &rsa.E , 16, (char*)eKey, eKey_len );        

    /*                                */
    /*                                */
    /*                                */
    dump_buf(nKey,0x4);   

_end:

    return ret;

}

/*                                                                         
           
                                                                          */
int lib_sign(uchar* data_buf,  uint32 data_len, uchar* sig_buf, uint32 sig_len)
{

#if 0

    int i = 0;

    if (RSA_KEY_LEN != sig_len)
    {   
        SMSG(true,"signature length is wrong (%d)\n",sig_len);
        goto _err;
    }

    /*                     */
    sha1(data_buf, data_len, sha1sum );       
    
    /* 
                                                      

                            
                                                                    
    
                                        
                                                                   
                                                              
                                                
            
                                      
                                                            
                                            

    */
    /*                               */ 
    SMSG(true,"[%s] RSA padding : RAW \n",MOD);
    if( rsa_sign( &rsa, HASH_LEN, sha1sum, sig_buf ) != 0 )
    {
        SMSG(true, "failed\n" );
        goto _err;
    }   
    SMSG(true,"[%s] sign image ... pass\n\n",MOD);


    /*                  */
    SMSG(true,"[%s] output signature: \n",MOD);	
    SMSG(true," ------------------------------------\n");	
    for(i=0;i<RSA_KEY_LEN;i++)
    {
        if(i==RSA_KEY_LEN-1)
        {
            if(sig_buf[i]<0x10)
            {   
                SMSG(true,"0x0%x",sig_buf[i]);
            }
            else
            {   
                SMSG(true,"0x%x",sig_buf[i]);
            }
        }
        else
        {
            if(sig_buf[i]<0x10)
            {   
                SMSG(true,"0x0%x,",sig_buf[i]);
            }
            else
            {   
                SMSG(true,"0x%x,",sig_buf[i]);
            }
        }
    }
    SMSG(true,"\n");

    /*                                      */
    SMSG(true,"\n[%s] verify signature",MOD);
    if( rsa_verify( &rsa, HASH_LEN, sha1sum, sig_buf ) != 0 )
    {
        SMSG(true, "failed\n" );
        goto _err;
    }    
    SMSG(true,"... pass\n");

#endif

    return 0;    

#if 0

_err:

    return -1;
    
#endif    

}


/*                                                                         
           
                                                                          */
int lib_hash (uchar* data_buf,  uint32 data_len, uchar* hash_buf, uint32 hash_len)
{

    if (HASH_LEN != hash_len)
    {   
        SMSG(true,"hash length is wrong (%d)\n",hash_len);
        goto _err;
    }

    /*                     */
    sha1(data_buf, data_len, hash_buf );

    return 0;    

_err:

    return -1;

}


/*                                                                         
                    
                                                                          */
int lib_verify (uchar* data_buf,  uint32 data_len, uchar* sig_buf, uint32 sig_len)
{

    if (RSA_KEY_LEN != sig_len)
    {   
        SMSG(true,"signature length is wrong (%d)\n",sig_len);
        goto _err;
    }

    SMSG(true,"[%s] 0x%x,0x%x,0x%x,0x%x\n",MOD,data_buf[0],data_buf[1],data_buf[2],data_buf[3]);	

    /*                     */
    sha1(data_buf, data_len, sha1sum);

    /*                       */
    SMSG(true,"[%s] verify signature",MOD);
    if( rsa_verify( &rsa, HASH_LEN, sha1sum, sig_buf ) != 0 )
    {
        SMSG(true, " ... failed\n" );
        goto _err;
    }    
    SMSG(true," ... pass\n");

    return 0;

_err:

    return -1;
}

