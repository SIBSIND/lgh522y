#ifndef _SPARC64_PSTATE_H
#define _SPARC64_PSTATE_H

#include <linux/const.h>

/*                                                   
  
                                                                          
                                                                          
                                                                          
                                                                        
 */
#define PSTATE_IG   _AC(0x0000000000000800,UL) /*                    */
#define PSTATE_MG   _AC(0x0000000000000400,UL) /*               */
#define PSTATE_CLE  _AC(0x0000000000000200,UL) /*                       */
#define PSTATE_TLE  _AC(0x0000000000000100,UL) /*                     */
#define PSTATE_MM   _AC(0x00000000000000c0,UL) /*                */
#define PSTATE_TSO  _AC(0x0000000000000000,UL) /*                     */
#define PSTATE_PSO  _AC(0x0000000000000040,UL) /*                       */
#define PSTATE_RMO  _AC(0x0000000000000080,UL) /*                       */
#define PSTATE_RED  _AC(0x0000000000000020,UL) /*                    */
#define PSTATE_PEF  _AC(0x0000000000000010,UL) /*                       */
#define PSTATE_AM   _AC(0x0000000000000008,UL) /*                */
#define PSTATE_PRIV _AC(0x0000000000000004,UL) /*             */
#define PSTATE_IE   _AC(0x0000000000000002,UL) /*                   */
#define PSTATE_AG   _AC(0x0000000000000001,UL) /*                    */

/*                                                             
  
                                                                        
                                                                        
                                                                        
                                                                       
 */
#define TSTATE_GL	_AC(0x0000070000000000,UL) /*                   */
#define TSTATE_CCR	_AC(0x000000ff00000000,UL) /*                  */
#define TSTATE_XCC	_AC(0x000000f000000000,UL) /*                  */
#define TSTATE_XNEG	_AC(0x0000008000000000,UL) /*                */
#define TSTATE_XZERO	_AC(0x0000004000000000,UL) /*            */
#define TSTATE_XOVFL	_AC(0x0000002000000000,UL) /*                */
#define TSTATE_XCARRY	_AC(0x0000001000000000,UL) /*             */
#define TSTATE_ICC	_AC(0x0000000f00000000,UL) /*                  */
#define TSTATE_INEG	_AC(0x0000000800000000,UL) /*                */
#define TSTATE_IZERO	_AC(0x0000000400000000,UL) /*            */
#define TSTATE_IOVFL	_AC(0x0000000200000000,UL) /*                */
#define TSTATE_ICARRY	_AC(0x0000000100000000,UL) /*             */
#define TSTATE_ASI	_AC(0x00000000ff000000,UL) /*               */
#define TSTATE_PIL	_AC(0x0000000000f00000,UL) /*                   */
#define TSTATE_PSTATE	_AC(0x00000000000fff00,UL) /*          */
#define TSTATE_IG	_AC(0x0000000000080000,UL) /*                   */
#define TSTATE_MG	_AC(0x0000000000040000,UL) /*              */
#define TSTATE_CLE	_AC(0x0000000000020000,UL) /*                   */
#define TSTATE_TLE	_AC(0x0000000000010000,UL) /*                   */
#define TSTATE_MM	_AC(0x000000000000c000,UL) /*               */
#define TSTATE_TSO	_AC(0x0000000000000000,UL) /*          */
#define TSTATE_PSO	_AC(0x0000000000004000,UL) /*          */
#define TSTATE_RMO	_AC(0x0000000000008000,UL) /*          */
#define TSTATE_RED	_AC(0x0000000000002000,UL) /*                   */
#define TSTATE_PEF	_AC(0x0000000000001000,UL) /*             */
#define TSTATE_AM	_AC(0x0000000000000800,UL) /*               */
#define TSTATE_PRIV	_AC(0x0000000000000400,UL) /*            */
#define TSTATE_IE	_AC(0x0000000000000200,UL) /*                   */
#define TSTATE_AG	_AC(0x0000000000000100,UL) /*                   */
#define TSTATE_SYSCALL	_AC(0x0000000000000020,UL) /*                   */
#define TSTATE_CWP	_AC(0x000000000000001f,UL) /*                   */

/*                                         
  
                                   
                                   
                                   
                                
 */
#define FPRS_FEF	_AC(0x0000000000000004,UL) /*             */
#define FPRS_DU		_AC(0x0000000000000002,UL) /*              */
#define FPRS_DL		_AC(0x0000000000000001,UL) /*              */

/*                  
  
                                                         
                                                         
                                                         
                                                        
 */
#define VERS_MANUF	_AC(0xffff000000000000,UL) /*               */
#define VERS_IMPL	_AC(0x0000ffff00000000,UL) /*                 */
#define VERS_MASK	_AC(0x00000000ff000000,UL) /*                   */
#define VERS_MAXTL	_AC(0x000000000000ff00,UL) /*                 */
#define VERS_MAXWIN	_AC(0x000000000000001f,UL) /*                   */

/*                                                              */
#define CFR_AES		_AC(0x0000000000000001,UL) /*                          */
#define CFR_DES		_AC(0x0000000000000002,UL) /*                          */
#define CFR_KASUMI	_AC(0x0000000000000004,UL) /*                          */
#define CFR_CAMELLIA	_AC(0x0000000000000008,UL) /*                          */
#define CFR_MD5		_AC(0x0000000000000010,UL) /*                          */
#define CFR_SHA1	_AC(0x0000000000000020,UL) /*                          */
#define CFR_SHA256	_AC(0x0000000000000040,UL) /*                          */
#define CFR_SHA512	_AC(0x0000000000000080,UL) /*                          */
#define CFR_MPMUL	_AC(0x0000000000000100,UL) /*                          */
#define CFR_MONTMUL	_AC(0x0000000000000200,UL) /*                          */
#define CFR_MONTSQR	_AC(0x0000000000000400,UL) /*                          */
#define CFR_CRC32C	_AC(0x0000000000000800,UL) /*                          */

#endif /*                      */
