#ifndef SEC_BOOT_CORE_H
#define SEC_BOOT_CORE_H

/*                                                                         
                  
                                                                          */
extern int masp_boot_init (void);

/*                            */
extern int sec_boot_enabled (void);
extern int sec_modem_auth_enabled (void);
extern int sec_sds_enabled (void);
extern int sec_schip_enabled (void);

/*                */
extern bool sec_boot_check_part_enabled (char* part_name);

/*              */
extern unsigned int sec_boot_hacc_init (void);

#endif /*                 */

