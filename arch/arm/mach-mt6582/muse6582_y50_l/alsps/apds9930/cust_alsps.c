#include <linux/types.h>
#include <mach/mt_pm_ldo.h>
#include <cust_alsps.h>
#include <mach/upmu_common.h>

static struct alsps_hw cust_alsps_hw = {
	.i2c_num    = 2,
	.polling_mode_ps = 0,
	.polling_mode_als = 1,
	.power_id   = MT65XX_POWER_NONE,	/*               */
	.power_vol  = VOL_DEFAULT,			/*               */
	.i2c_addr[0]   = 0x39,
};

struct alsps_hw *get_cust_alsps_hw(void) {
	return &cust_alsps_hw;
}

int pmic_ldo_suspend_enable(int enable)
{
	//                                           
	upmu_set_vio18_lp_sel(enable);
	upmu_set_vio28_lp_sel(enable);
	return 0;
}
