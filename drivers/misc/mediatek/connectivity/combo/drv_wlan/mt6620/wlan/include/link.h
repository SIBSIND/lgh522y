/*
                                                                                
*/

/*                
                                                                

                                                                               
                                          
*/



/*
                 
  
                        
       
                                                          
  
                      
  
                                                    
  
                   
  
                                                                               
  
                   
                                                    
                                                     
    
  
  
  
  
                      
                                                                
                                  
                                                             
                                     
                                                             
                            
                                                             
                                     
                                                             
                             
                                                  
             
  
*/

#ifndef _LINK_H
#define _LINK_H

/*                                                                              
                                                     
                                                                                
*/

/*                                                                              
                                                          
                                                                                
*/
#include "gl_typedef.h"


/*                                                                              
                                                
                                                                                
*/
#define INVALID_LINK_POISON1    ((VOID *) 0x00100101)	/*                                                       */
#define INVALID_LINK_POISON2    ((VOID *) 0x00100201)	/*                                                                */


/*                                                                              
                                                 
                                                                                
*/
/*                                                   */
typedef struct _LINK_ENTRY_T {
	struct _LINK_ENTRY_T *prNext, *prPrev;
} LINK_ENTRY_T, *P_LINK_ENTRY_T;

/*                                                  */
typedef struct _LINK_T {
	P_LINK_ENTRY_T prNext;
	P_LINK_ENTRY_T prPrev;
	UINT_32 u4NumElem;
} LINK_T, *P_LINK_T;

/*                                                                              
                                                  
                                                                                
*/

/*                                                                              
                                                   
                                                                                
*/

/*                                                                              
                                             
                                                                                
*/
#if 0				/*                                                          */
#define LINK_ADDR(rLink)        { (P_LINK_ENTRY_T)(&(rLink)), (P_LINK_ENTRY_T)(&(rLink)), 0 }

#define LINK_DECLARATION(rLink) \
    struct _LINK_T rLink = LINK_ADDR(rLink)
#endif

#define LINK_INITIALIZE(prLink) \
    do { \
	((P_LINK_T)(prLink))->prNext = (P_LINK_ENTRY_T)(prLink); \
	((P_LINK_T)(prLink))->prPrev = (P_LINK_ENTRY_T)(prLink); \
	((P_LINK_T)(prLink))->u4NumElem = 0; \
    } while (0)

#define LINK_ENTRY_INITIALIZE(prEntry) \
    do { \
	((P_LINK_ENTRY_T)(prEntry))->prNext = (P_LINK_ENTRY_T)NULL; \
	((P_LINK_ENTRY_T)(prEntry))->prPrev = (P_LINK_ENTRY_T)NULL; \
    } while (0)

#define LINK_ENTRY_INVALID(prEntry) \
    do { \
	((P_LINK_ENTRY_T)(prEntry))->prNext = (P_LINK_ENTRY_T)INVALID_LINK_POISON1; \
	((P_LINK_ENTRY_T)(prEntry))->prPrev = (P_LINK_ENTRY_T)INVALID_LINK_POISON2; \
    } while (0)

#define LINK_IS_EMPTY(prLink)           (((P_LINK_T)(prLink))->prNext == (P_LINK_ENTRY_T)(prLink))

/*                                                                               
                                          
 */
#define LINK_IS_INVALID(prLink)         (((P_LINK_T)(prLink))->prNext == (P_LINK_ENTRY_T)NULL)

#define LINK_IS_VALID(prLink)           (((P_LINK_T)(prLink))->prNext != (P_LINK_ENTRY_T)NULL)


#define LINK_ENTRY(ptr, type, member)   ENTRY_OF(ptr, type, member)

/*                                         */
#define LINK_INSERT_HEAD(prLink, prEntry) \
	{ \
	    linkAdd(prEntry, prLink); \
	    ((prLink)->u4NumElem)++; \
	}


/*                                         */
#define LINK_INSERT_TAIL(prLink, prEntry) \
	{ \
	    linkAddTail(prEntry, prLink); \
	    ((prLink)->u4NumElem)++; \
	}

/*                                              */
#define LINK_PEEK_HEAD(prLink, _type, _member) \
	( \
	    LINK_IS_EMPTY(prLink) ? \
	    NULL : LINK_ENTRY((prLink)->prNext, _type, _member) \
	)

/*                                              */
#define LINK_PEEK_TAIL(prLink, _type, _member) \
	( \
	    LINK_IS_EMPTY(prLink) ? \
	    NULL : LINK_ENTRY((prLink)->prPrev, _type, _member) \
	)

/*                                  */
/*                                                                           
                                                                        
                                                                       
 */
#define LINK_REMOVE_HEAD(prLink, prEntry, _P_TYPE) \
	{ \
	    ASSERT(prLink); \
	    if (LINK_IS_EMPTY(prLink)) { \
		prEntry = (_P_TYPE)NULL; \
	    } \
	    else { \
		prEntry = (_P_TYPE)(((P_LINK_T)(prLink))->prNext); \
		linkDel((P_LINK_ENTRY_T)prEntry); \
		((prLink)->u4NumElem)--; \
	    } \
	}

/*                                                                
                                           
 */
#define LINK_REMOVE_KNOWN_ENTRY(prLink, prEntry) \
	{ \
	    ASSERT(prLink); \
	    ASSERT(prEntry); \
	    linkDel((P_LINK_ENTRY_T)prEntry); \
	    ((prLink)->u4NumElem)--; \
	}

/*                          */
#define LINK_FOR_EACH(prEntry, prLink) \
    for (prEntry = (prLink)->prNext; \
	 prEntry != (P_LINK_ENTRY_T)(prLink); \
	 prEntry = (P_LINK_ENTRY_T)prEntry->prNext)

/*                                    */
#define LINK_FOR_EACH_PREV(prEntry, prLink) \
    for (prEntry = (prLink)->prPrev; \
	 prEntry != (P_LINK_ENTRY_T)(prLink); \
	 prEntry = (P_LINK_ENTRY_T)prEntry->prPrev)

/*                                                             */
#define LINK_FOR_EACH_SAFE(prEntry, prNextEntry, prLink) \
    for (prEntry = (prLink)->prNext, prNextEntry = prEntry->prNext; \
	 prEntry != (P_LINK_ENTRY_T)(prLink); \
	 prEntry = prNextEntry, prNextEntry = prEntry->prNext)

/*                                        */
#define LINK_FOR_EACH_ENTRY(prObj, prLink, rMember, _TYPE) \
    for (prObj = LINK_ENTRY((prLink)->prNext, _TYPE, rMember); \
	 &prObj->rMember != (P_LINK_ENTRY_T)(prLink); \
	 prObj = LINK_ENTRY(prObj->rMember.prNext, _TYPE, rMember))

/*                                                  */
#define LINK_FOR_EACH_ENTRY_PREV(prObj, prLink, rMember, _TYPE) \
    for (prObj = LINK_ENTRY((prLink)->prPrev, _TYPE, rMember);  \
	 &prObj->rMember != (P_LINK_ENTRY_T)(prLink); \
	 prObj = LINK_ENTRY(prObj->rMember.prPrev, _TYPE, rMember))

/*                                                                           */
#define LINK_FOR_EACH_ENTRY_SAFE(prObj, prNextObj, prLink, rMember, _TYPE) \
    for (prObj = LINK_ENTRY((prLink)->prNext, _TYPE, rMember),  \
	 prNextObj = LINK_ENTRY(prObj->rMember.prNext, _TYPE, rMember); \
	 &prObj->rMember != (P_LINK_ENTRY_T)(prLink); \
	 prObj = prNextObj, \
	 prNextObj = LINK_ENTRY(prNextObj->rMember.prNext, _TYPE, rMember))

/*                                                                              
                                                            
                                                                                
*/

/*                                                                              
                                                
                                                                                
*/
/*                                                                            */
/* 
                                                                   
 
                                            
                                                 
                                             
 
                
*/
/*                                                                            */
__KAL_INLINE__ VOID
__linkAdd(IN P_LINK_ENTRY_T prNew, IN P_LINK_ENTRY_T prPrev, IN P_LINK_ENTRY_T prNext)
{
	prNext->prPrev = prNew;
	prNew->prNext = prNext;
	prNew->prPrev = prPrev;
	prPrev->prNext = prNew;

	return;
}				/*                    */


/*                                                                            */
/* 
                                                                          
 
                                         
                                                       
 
                
*/
/*                                                                            */
__KAL_INLINE__ VOID linkAdd(IN P_LINK_ENTRY_T prNew, IN P_LINK_T prLink)
{
	__linkAdd(prNew, (P_LINK_ENTRY_T) prLink, prLink->prNext);

	return;
}				/*                  */


/*                                                                            */
/* 
                                                                           
 
                                         
                                                        
 
                
*/
/*                                                                            */
__KAL_INLINE__ VOID linkAddTail(IN P_LINK_ENTRY_T prNew, IN P_LINK_T prLink)
{
	__linkAdd(prNew, prLink->prPrev, (P_LINK_ENTRY_T) prLink);

	return;
}				/*                      */


/*                                                                            */
/* 
                                                                   
 
                                                 
                                             
 
                
*/
/*                                                                            */
__KAL_INLINE__ VOID __linkDel(IN P_LINK_ENTRY_T prPrev, IN P_LINK_ENTRY_T prNext)
{
	prNext->prPrev = prPrev;
	prPrev->prNext = prNext;

	return;
}				/*                    */


/*                                                                            */
/* 
                                                                    
                                                
 
                                              
 
                
*/
/*                                                                            */
__KAL_INLINE__ VOID linkDel(IN P_LINK_ENTRY_T prEntry)
{
	__linkDel(prEntry->prPrev, prEntry->prNext);

	LINK_ENTRY_INITIALIZE(prEntry);

	return;
}				/*                  */


/*                                                                            */
/* 
                                                                                   
                                       
 
                                                      
                                                             
 
                
*/
/*                                                                            */
__KAL_INLINE__ VOID linkMove(IN P_LINK_ENTRY_T prEntry, IN P_LINK_T prLink)
{
	__linkDel(prEntry->prPrev, prEntry->prNext);
	linkAdd(prEntry, prLink);

	return;
}				/*                   */


/*                                                                            */
/* 
                                                                                   
                                        
 
                                                      
                                                              
 
                
*/
/*                                                                            */
__KAL_INLINE__ VOID linkMoveTail(IN P_LINK_ENTRY_T prEntry, IN P_LINK_T prLink)
{
	__linkDel(prEntry->prPrev, prEntry->prNext);
	linkAddTail(prEntry, prLink);

	return;
}				/*                       */

#endif				/*         */
