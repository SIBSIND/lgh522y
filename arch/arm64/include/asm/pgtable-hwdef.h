/*
 * Copyright (C) 2012 ARM Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef __ASM_PGTABLE_HWDEF_H
#define __ASM_PGTABLE_HWDEF_H

#ifdef CONFIG_ARM64_64K_PAGES
#include <asm/pgtable-2level-hwdef.h>
#else
#include <asm/pgtable-3level-hwdef.h>
#endif

/*
                                   
  
                            
 */
#define PMD_TYPE_MASK		(_AT(pmdval_t, 3) << 0)
#define PMD_TYPE_FAULT		(_AT(pmdval_t, 0) << 0)
#define PMD_TYPE_TABLE		(_AT(pmdval_t, 3) << 0)
#define PMD_TYPE_SECT		(_AT(pmdval_t, 1) << 0)

/*
          
 */
#define PMD_SECT_S		(_AT(pmdval_t, 3) << 8)
#define PMD_SECT_AF		(_AT(pmdval_t, 1) << 10)
#define PMD_SECT_NG		(_AT(pmdval_t, 1) << 11)
#define PMD_SECT_PXN		(_AT(pmdval_t, 1) << 53)
#define PMD_SECT_UXN		(_AT(pmdval_t, 1) << 54)

/*
                                                                              
 */
#define PMD_ATTRINDX(t)		(_AT(pmdval_t, (t)) << 2)
#define PMD_ATTRINDX_MASK	(_AT(pmdval_t, 7) << 2)

/*
                            
 */
#define PTE_TYPE_MASK		(_AT(pteval_t, 3) << 0)
#define PTE_TYPE_FAULT		(_AT(pteval_t, 0) << 0)
#define PTE_TYPE_PAGE		(_AT(pteval_t, 3) << 0)
#define PTE_USER		(_AT(pteval_t, 1) << 6)		/*       */
#define PTE_RDONLY		(_AT(pteval_t, 1) << 7)		/*       */
#define PTE_SHARED		(_AT(pteval_t, 3) << 8)		/*                          */
#define PTE_AF			(_AT(pteval_t, 1) << 10)	/*             */
#define PTE_NG			(_AT(pteval_t, 1) << 11)	/*    */
#define PTE_PXN			(_AT(pteval_t, 1) << 53)	/*               */
#define PTE_UXN			(_AT(pteval_t, 1) << 54)	/*         */

/*
                                                                              
 */
#define PTE_ATTRINDX(t)		(_AT(pteval_t, (t)) << 2)
#define PTE_ATTRINDX_MASK	(_AT(pteval_t, 7) << 2)

/*
                                     
 */
#define PHYS_MASK_SHIFT		(40)
#define PHYS_MASK		((UL(1) << PHYS_MASK_SHIFT) - 1)

/*
             
 */
#define TCR_TxSZ(x)		(((UL(64) - (x)) << 16) | ((UL(64) - (x)) << 0))
#define TCR_IRGN_NC		((UL(0) << 8) | (UL(0) << 24))
#define TCR_IRGN_WBWA		((UL(1) << 8) | (UL(1) << 24))
#define TCR_IRGN_WT		((UL(2) << 8) | (UL(2) << 24))
#define TCR_IRGN_WBnWA		((UL(3) << 8) | (UL(3) << 24))
#define TCR_IRGN_MASK		((UL(3) << 8) | (UL(3) << 24))
#define TCR_ORGN_NC		((UL(0) << 10) | (UL(0) << 26))
#define TCR_ORGN_WBWA		((UL(1) << 10) | (UL(1) << 26))
#define TCR_ORGN_WT		((UL(2) << 10) | (UL(2) << 26))
#define TCR_ORGN_WBnWA		((UL(3) << 10) | (UL(3) << 26))
#define TCR_ORGN_MASK		((UL(3) << 10) | (UL(3) << 26))
#define TCR_SHARED		((UL(3) << 12) | (UL(3) << 28))
#define TCR_TG0_64K		(UL(1) << 14)
#define TCR_TG1_64K		(UL(1) << 30)
#define TCR_IPS_40BIT		(UL(2) << 32)
#define TCR_ASID16		(UL(1) << 36)
#define TCR_TBI0		(UL(1) << 37)

#endif
