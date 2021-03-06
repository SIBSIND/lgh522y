#include <cust_leds.h>
#include <cust_leds_def.h>

/*                                                                           
                        
                                                                           */
#define NLED_OFF 0
#define NLED_ON 1
#define NLED_BLINK 2
#define MIN_FRE_OLD_PWM 32 //                                               
#define PWM_DIV_NUM 8
#define ERROR_BL_LEVEL 0xFFFFFFFF

struct nled_setting
{
	u8 nled_mode; //                        
	u32 blink_on_time ;
	u32 blink_off_time;
};
 
typedef enum{  
    PMIC_PWM_0 = 0,  
    PMIC_PWM_1 = 1,  
    PMIC_PWM_2 = 2
} MT65XX_PMIC_PWM_NUMBER;

typedef enum{      
	ISINK_PWM_MODE = 0,      
	ISINK_BREATH_MODE = 1,      
	ISINK_REGISTER_MODE = 2
} MT65XX_PMIC_ISINK_MODE;

/*                                                                    */
//                                   
//                                                        
//                                                                       

/*                                                                           
             
                                                                           */
struct mt65xx_led_data {
	struct led_classdev cdev;
	struct cust_mt65xx_led cust;
	struct work_struct work;
	int level;
	int delay_on;
	int delay_off;
};

