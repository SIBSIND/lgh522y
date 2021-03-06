/***********************license start***************
 * Author: Cavium Networks
 *
 * Contact: support@caviumnetworks.com
 * This file is part of the OCTEON SDK
 *
 * Copyright (c) 2003-2008 Cavium Networks
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, Version 2, as
 * published by the Free Software Foundation.
 *
 * This file is distributed in the hope that it will be useful, but
 * AS-IS and WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, TITLE, or
 * NONINFRINGEMENT.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this file; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 * or visit http://www.gnu.org/licenses/.
 *
 * This file may also be available under a different license from Cavium.
 * Contact Cavium Networks for more information
 ***********************license end**************************************/

/*
                                                      
 */

#ifndef __CVMX_BOOTINFO_H__
#define __CVMX_BOOTINFO_H__

/*
                                                                      
                                                                    
                                                               
            
 */
#define CVMX_BOOTINFO_MAJ_VER 1
#define CVMX_BOOTINFO_MIN_VER 3

#if (CVMX_BOOTINFO_MAJ_VER == 1)
#define CVMX_BOOTINFO_OCTEON_SERIAL_LEN 20
/*
                                                             
                                                         
                                                            
                                              
                                                       
                                                             
        
 */
struct cvmx_bootinfo {
	uint32_t major_version;
	uint32_t minor_version;

	uint64_t stack_top;
	uint64_t heap_base;
	uint64_t heap_end;
	uint64_t desc_vaddr;

	uint32_t exception_base_addr;
	uint32_t stack_size;
	uint32_t flags;
	uint32_t core_mask;
	/*                        */
	uint32_t dram_size;
	/*                                                 */
	uint32_t phy_mem_desc_addr;
	/*                                         */
	uint32_t debugger_flags_base_addr;

	/*                        */
	uint32_t eclock_hz;

	/*                         */
	uint32_t dclock_hz;

	uint32_t reserved0;
	uint16_t board_type;
	uint8_t board_rev_major;
	uint8_t board_rev_minor;
	uint16_t reserved1;
	uint8_t reserved2;
	uint8_t reserved3;
	char board_serial_number[CVMX_BOOTINFO_OCTEON_SERIAL_LEN];
	uint8_t mac_addr_base[6];
	uint8_t mac_addr_count;
#if (CVMX_BOOTINFO_MIN_VER >= 1)
	/*
                                                           
                                                         
                                                          
                                                       
                                                          
                                                      
  */
	uint64_t compact_flash_common_base_addr;
	uint64_t compact_flash_attribute_base_addr;
	/*
                                                         
                                              
  */
	uint64_t led_display_base_addr;
#endif
#if (CVMX_BOOTINFO_MIN_VER >= 2)
	/*                                          */
	uint32_t dfa_ref_clock_hz;

	/*
                                                          
                                                           
                         
  */
	uint32_t config_flags;
#endif
#if (CVMX_BOOTINFO_MIN_VER >= 3)
	/*
                                                     
                         
  */
	uint64_t fdt_addr;
#endif
};

#define CVMX_BOOTINFO_CFG_FLAG_PCI_HOST			(1ull << 0)
#define CVMX_BOOTINFO_CFG_FLAG_PCI_TARGET		(1ull << 1)
#define CVMX_BOOTINFO_CFG_FLAG_DEBUG			(1ull << 2)
#define CVMX_BOOTINFO_CFG_FLAG_NO_MAGIC			(1ull << 3)
/*                                                              
                                            */
#define CVMX_BOOTINFO_CFG_FLAG_OVERSIZE_TLB_MAPPING	(1ull << 4)
#define CVMX_BOOTINFO_CFG_FLAG_BREAK			(1ull << 5)

#endif /*                                */

/*                                       */
enum cvmx_board_types_enum {
	CVMX_BOARD_TYPE_NULL = 0,
	CVMX_BOARD_TYPE_SIM = 1,
	CVMX_BOARD_TYPE_EBT3000 = 2,
	CVMX_BOARD_TYPE_KODAMA = 3,
	CVMX_BOARD_TYPE_NIAGARA = 4,
	CVMX_BOARD_TYPE_NAC38 = 5,	/*                */
	CVMX_BOARD_TYPE_THUNDER = 6,
	CVMX_BOARD_TYPE_TRANTOR = 7,
	CVMX_BOARD_TYPE_EBH3000 = 8,
	CVMX_BOARD_TYPE_EBH3100 = 9,
	CVMX_BOARD_TYPE_HIKARI = 10,
	CVMX_BOARD_TYPE_CN3010_EVB_HS5 = 11,
	CVMX_BOARD_TYPE_CN3005_EVB_HS5 = 12,
	CVMX_BOARD_TYPE_KBP = 13,
	/*                                                                */
	CVMX_BOARD_TYPE_CN3020_EVB_HS5 = 14,
	CVMX_BOARD_TYPE_EBT5800 = 15,
	CVMX_BOARD_TYPE_NICPRO2 = 16,
	CVMX_BOARD_TYPE_EBH5600 = 17,
	CVMX_BOARD_TYPE_EBH5601 = 18,
	CVMX_BOARD_TYPE_EBH5200 = 19,
	CVMX_BOARD_TYPE_BBGW_REF = 20,
	CVMX_BOARD_TYPE_NIC_XLE_4G = 21,
	CVMX_BOARD_TYPE_EBT5600 = 22,
	CVMX_BOARD_TYPE_EBH5201 = 23,
	CVMX_BOARD_TYPE_EBT5200 = 24,
	CVMX_BOARD_TYPE_CB5600	= 25,
	CVMX_BOARD_TYPE_CB5601	= 26,
	CVMX_BOARD_TYPE_CB5200	= 27,
	/*                                                    */
	CVMX_BOARD_TYPE_GENERIC = 28,
	CVMX_BOARD_TYPE_EBH5610 = 29,
	CVMX_BOARD_TYPE_LANAI2_A = 30,
	CVMX_BOARD_TYPE_LANAI2_U = 31,
	CVMX_BOARD_TYPE_EBB5600 = 32,
	CVMX_BOARD_TYPE_EBB6300 = 33,
	CVMX_BOARD_TYPE_NIC_XLE_10G = 34,
	CVMX_BOARD_TYPE_LANAI2_G = 35,
	CVMX_BOARD_TYPE_EBT5810 = 36,
	CVMX_BOARD_TYPE_NIC10E = 37,
	CVMX_BOARD_TYPE_EP6300C = 38,
	CVMX_BOARD_TYPE_EBB6800 = 39,
	CVMX_BOARD_TYPE_NIC4E = 40,
	CVMX_BOARD_TYPE_NIC2E = 41,
	CVMX_BOARD_TYPE_EBB6600 = 42,
	CVMX_BOARD_TYPE_REDWING = 43,
	CVMX_BOARD_TYPE_NIC68_4 = 44,
	CVMX_BOARD_TYPE_NIC10E_66 = 45,
	CVMX_BOARD_TYPE_MAX,

	/*
                                         
                                                           
            
  */

	/*
                                                                     
              
  */
	CVMX_BOARD_TYPE_CUST_DEFINED_MIN = 10000,
	CVMX_BOARD_TYPE_CUST_WSX16 = 10001,
	CVMX_BOARD_TYPE_CUST_NS0216 = 10002,
	CVMX_BOARD_TYPE_CUST_NB5 = 10003,
	CVMX_BOARD_TYPE_CUST_WMR500 = 10004,
	CVMX_BOARD_TYPE_CUST_ITB101 = 10005,
	CVMX_BOARD_TYPE_CUST_NTE102 = 10006,
	CVMX_BOARD_TYPE_CUST_AGS103 = 10007,
	CVMX_BOARD_TYPE_CUST_GST104 = 10008,
	CVMX_BOARD_TYPE_CUST_GCT105 = 10009,
	CVMX_BOARD_TYPE_CUST_AGS106 = 10010,
	CVMX_BOARD_TYPE_CUST_SGM107 = 10011,
	CVMX_BOARD_TYPE_CUST_GCT108 = 10012,
	CVMX_BOARD_TYPE_CUST_AGS109 = 10013,
	CVMX_BOARD_TYPE_CUST_GCT110 = 10014,
	CVMX_BOARD_TYPE_CUST_L2_AIR_SENDER = 10015,
	CVMX_BOARD_TYPE_CUST_L2_AIR_RECEIVER = 10016,
	CVMX_BOARD_TYPE_CUST_L2_ACCTON2_TX = 10017,
	CVMX_BOARD_TYPE_CUST_L2_ACCTON2_RX = 10018,
	CVMX_BOARD_TYPE_CUST_L2_WSTRNSNIC_TX = 10019,
	CVMX_BOARD_TYPE_CUST_L2_WSTRNSNIC_RX = 10020,
	CVMX_BOARD_TYPE_CUST_L2_ZINWELL = 10021,
	CVMX_BOARD_TYPE_CUST_DEFINED_MAX = 20000,

	/*
                                                             
                                  
  */
	CVMX_BOARD_TYPE_CUST_PRIVATE_MIN = 20001,
	CVMX_BOARD_TYPE_CUST_PRIVATE_MAX = 30000,

	/*                                                 */
};

enum cvmx_chip_types_enum {
	CVMX_CHIP_TYPE_NULL = 0,
	CVMX_CHIP_SIM_TYPE_DEPRECATED = 1,
	CVMX_CHIP_TYPE_OCTEON_SAMPLE = 2,
	CVMX_CHIP_TYPE_MAX,
};

/*                                                                 
                */
#define CVMX_BOARD_TYPE_NAO38	CVMX_BOARD_TYPE_NAC38

/*                                          */
#define ENUM_BRD_TYPE_CASE(x) \
	case x: return(#x + 16);	/*                       */
static inline const char *cvmx_board_type_to_string(enum
						    cvmx_board_types_enum type)
{
	switch (type) {
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_NULL)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_SIM)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_EBT3000)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_KODAMA)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_NIAGARA)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_NAC38)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_THUNDER)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_TRANTOR)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_EBH3000)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_EBH3100)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_HIKARI)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CN3010_EVB_HS5)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CN3005_EVB_HS5)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_KBP)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CN3020_EVB_HS5)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_EBT5800)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_NICPRO2)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_EBH5600)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_EBH5601)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_EBH5200)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_BBGW_REF)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_NIC_XLE_4G)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_EBT5600)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_EBH5201)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_EBT5200)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CB5600)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CB5601)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CB5200)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_GENERIC)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_EBH5610)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_LANAI2_A)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_LANAI2_U)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_EBB5600)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_EBB6300)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_NIC_XLE_10G)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_LANAI2_G)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_EBT5810)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_NIC10E)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_EP6300C)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_EBB6800)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_NIC4E)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_NIC2E)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_EBB6600)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_REDWING)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_NIC68_4)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_NIC10E_66)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_MAX)

			/*                             */
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_DEFINED_MIN)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_WSX16)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_NS0216)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_NB5)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_WMR500)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_ITB101)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_NTE102)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_AGS103)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_GST104)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_GCT105)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_AGS106)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_SGM107)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_GCT108)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_AGS109)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_GCT110)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_L2_AIR_SENDER)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_L2_AIR_RECEIVER)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_L2_ACCTON2_TX)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_L2_ACCTON2_RX)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_L2_WSTRNSNIC_TX)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_L2_WSTRNSNIC_RX)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_L2_ZINWELL)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_DEFINED_MAX)

		    /*                        */
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_PRIVATE_MIN)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_PRIVATE_MAX)
	}
	return "Unsupported Board";
}

#define ENUM_CHIP_TYPE_CASE(x) \
	case x: return(#x + 15);	/*                     */
static inline const char *cvmx_chip_type_to_string(enum
						   cvmx_chip_types_enum type)
{
	switch (type) {
		ENUM_CHIP_TYPE_CASE(CVMX_CHIP_TYPE_NULL)
		ENUM_CHIP_TYPE_CASE(CVMX_CHIP_SIM_TYPE_DEPRECATED)
		ENUM_CHIP_TYPE_CASE(CVMX_CHIP_TYPE_OCTEON_SAMPLE)
		ENUM_CHIP_TYPE_CASE(CVMX_CHIP_TYPE_MAX)
	}
	return "Unsupported Chip";
}

#endif /*                     */
