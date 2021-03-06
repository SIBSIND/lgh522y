#ifndef BATTERY_COMMON_H
#define BATTERY_COMMON_H

#include <linux/ioctl.h>
#include <mach/mt_typedefs.h>
#include "charging.h"


/*                                                                            
                   
                                                                            */
#define PRE_CHARGE_VOLTAGE                  3200
#define SYSTEM_OFF_VOLTAGE                  3300
#define CONSTANT_CURRENT_CHARGE_VOLTAGE     4100
#define CONSTANT_VOLTAGE_CHARGE_VOLTAGE     4200
#define CV_DROPDOWN_VOLTAGE                 4000
#define CHARGER_THRESH_HOLD                 4300
#define BATTERY_UVLO_VOLTAGE                2700

/*                                                                            
                 
                                                                            */
/*                                                              */
/*                                                              */
/*                                                               */
#define MAX_CHARGING_TIME                   24*60*60	/*      */

#define MAX_POSTFULL_SAFETY_TIME		1*30*60	/*        */
#define MAX_PreCC_CHARGING_TIME		1*30*60	/*       */

/*                                                                        */
#define MAX_CV_CHARGING_TIME			3*60*60	/*     */


#define MUTEX_TIMEOUT                       5000
#define BAT_TASK_PERIOD                     10	/*       */
#define g_free_bat_temp					1000	/*     */

/*                                                                            
                      
                                                                            */
#define Battery_Percent_100    100
#define charger_OVER_VOL	    1
#define BATTERY_UNDER_VOL		2
#define BATTERY_OVER_TEMP		3
#define ADC_SAMPLE_TIMES        5

/*                                                                            
                        
                                                                            */
#define  CHR_PRE                        0x1000
#define  CHR_CC                         0x1001
#define  CHR_TOP_OFF                    0x1002
#define  CHR_POST_FULL                  0x1003
#define  CHR_BATFULL                    0x1004
#define  CHR_ERROR                      0x1005
#define  CHR_HOLD						0x1006

/*                                                                            
             
                                                                            */
#define CALL_IDLE 0
#define CALL_ACTIVE 1

#ifdef CONFIG_LGE_PM_PSEUDO_BATTERY
/*                                                                            
                  
                                                                            */
#define PSEUDO_BATTERY_LEVEL	80
#define PSEUDO_BATTERY_TEMP		40
#endif

/*                                                                            
        
                                                                            */
typedef unsigned int WORD;


typedef enum {
	PMU_STATUS_OK = 0,
	PMU_STATUS_FAIL = 1,
} PMU_STATUS;


typedef enum {
	USB_SUSPEND = 0,
	USB_UNCONFIGURED,
	USB_CONFIGURED
} usb_state_enum;

/*                                                                            
                                      
                                                                                                                
                                      
                    
                                                                                               
                                                                                                    
                                                                                                       
                                                                                                      
                                                                                                        
                                                                                                       
                                                                                                  
                                                                           */
typedef enum {
	TEMP_BELOW_NEG_10 = 0,
	TEMP_NEG_10_TO_POS_0,
	TEMP_POS_0_TO_POS_10,
	TEMP_POS_10_TO_POS_45,
	TEMP_POS_45_TO_POS_60,
	TEMP_ABOVE_POS_60
} temp_state_enum;


#define TEMP_POS_60_THRESHOLD  50
#define TEMP_POS_60_THRES_MINUS_X_DEGREE 47

#define TEMP_POS_45_THRESHOLD  45
#define TEMP_POS_45_THRES_MINUS_X_DEGREE 39

#define TEMP_POS_10_THRESHOLD  10
#define TEMP_POS_10_THRES_PLUS_X_DEGREE 16

#define TEMP_POS_0_THRESHOLD  0
#define TEMP_POS_0_THRES_PLUS_X_DEGREE 6

#ifdef CONFIG_MTK_FAN5405_SUPPORT
#define TEMP_NEG_10_THRESHOLD  0
#define TEMP_NEG_10_THRES_PLUS_X_DEGREE  0
#elif defined(CONFIG_MTK_BQ24158_SUPPORT)
#define TEMP_NEG_10_THRESHOLD  0
#define TEMP_NEG_10_THRES_PLUS_X_DEGREE  0
#else
#define TEMP_NEG_10_THRESHOLD  0
#define TEMP_NEG_10_THRES_PLUS_X_DEGREE  0
#endif

/*                                                                            
                                    
                                                                            */
typedef enum {
	TEMP_POS_LOW = 0,
	TEMP_POS_NORMAL,
	TEMP_POS_HIGH
} batt_temp_state_enum;

/*                                                                            
             
                                                                            */
typedef struct {
	kal_bool bat_exist;
	kal_bool bat_full;
	INT32 bat_charging_state;
	UINT32 bat_vol;
	kal_bool bat_in_recharging_state;
	kal_uint32 Vsense;
	kal_bool charger_exist;
	UINT32 charger_vol;
	INT32 charger_protect_status;
	INT32 ICharging;
	INT32 IBattery;
	INT32 temperature;
	INT32 temperatureR;
	INT32 temperatureV;
	UINT32 total_charging_time;
	UINT32 PRE_charging_time;
	UINT32 CC_charging_time;
	UINT32 TOPOFF_charging_time;
	UINT32 POSTFULL_charging_time;
	UINT32 charger_type;
	INT32 SOC;
	INT32 UI_SOC;
	UINT32 nPercent_ZCV;
	UINT32 nPrecent_UI_SOC_check_point;
	UINT32 ZCV;
#ifdef CONFIG_MTK_EXTERNAL_CHARGER_SUPPORT
	INT32 voltage_now;
	INT32 current_now;
#endif
#ifdef CONFIG_LGE_PM_AT_CMD_SUPPORT
	kal_bool AtCmdChargingModeOff;
#endif
#ifdef CONFIG_LGE_CABLE_ID_DETECT
	kal_bool		factory_cable;
#endif
#ifdef CONFIG_LGE_PM_PSEUDO_BATTERY
	kal_bool pseudo_batt_enabled;
#endif
#ifdef CONFIG_LGE_PM_USB_CURRENT_MAX
	kal_bool usb_current_max_enabled;
#endif

} PMU_ChargerStruct;

/*                                                                            
                   
                                                                            */
extern PMU_ChargerStruct BMT_status;
extern CHARGING_CONTROL battery_charging_control;
extern kal_bool g_ftm_battery_flag;
extern int charging_level_data[1];
extern kal_bool g_call_state;
extern kal_bool g_charging_full_reset_bat_meter;
#if defined(CONFIG_MTK_PUMP_EXPRESS_SUPPORT) || defined(CONFIG_MTK_PUMP_EXPRESS_PLUS_SUPPORT)
extern kal_bool ta_check_chr_type;
extern kal_bool ta_cable_out_occur;
extern kal_bool is_ta_connect;
extern struct wake_lock TA_charger_suspend_lock;
#endif


/*                                                                            
                   
                                                                            */
extern void charging_suspend_enable(void);
extern void charging_suspend_disable(void);
extern kal_bool bat_is_charger_exist(void);
extern kal_bool bat_is_charging_full(void);
extern kal_uint32 bat_get_ui_percentage(void);
extern kal_uint32 get_charging_setting_current(void);
extern kal_uint32 bat_is_recharging_phase(void);
extern void do_chrdet_int_task(void);
extern void set_usb_current_unlimited(bool enable);
extern bool get_usb_current_unlimited(void);
extern CHARGER_TYPE mt_get_charger_type(void);

#ifdef CONFIG_MTK_SMART_BATTERY
extern void wake_up_bat(void);
extern unsigned long BAT_Get_Battery_Voltage(int polling_mode);
extern void mt_battery_charging_algorithm(void);
#if defined(CONFIG_MTK_JEITA_STANDARD_SUPPORT)
extern PMU_STATUS do_jeita_state_machine(void);
#endif

#else

#define wake_up_bat()			do {} while (0)
#define BAT_Get_Battery_Voltage(polling_mode)	({ 0; })

#endif

#ifdef CONFIG_MTK_POWER_EXT_DETECT
extern kal_bool bat_is_ext_power(void);
#endif



#endif				/*                          */
