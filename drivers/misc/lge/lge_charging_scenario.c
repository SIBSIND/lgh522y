/*
 * LGE charging scenario.
 *
 * Copyright (C) 2013 LG Electronics
 * mansu.lee <mansu.lee@lge.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <mach/lge_charging_scenario.h>
#include <linux/string.h>
/*                                 */
#ifdef DEBUG_LCS
/*                              */
#ifdef DEBUG_LCS_DUMMY_TEMP
static int dummy_temp = 25;
static int time_order = 1;
#endif
#endif

#define CHG_MAXIDX	7

static struct batt_temp_table chg_temp_table[CHG_MAXIDX] = {
	{ INT_MIN,       -11,    CHG_BATTEMP_BL_M11,  "under -10" },	//                
	{    -10,         -5,    CHG_BATTEMP_M10_M5,  "-10 ~ -5"  },	//                       
	{     -4,         41,     CHG_BATTEMP_M4_41,   "-4 ~ 41"  },	//                    
	{     42,         45,     CHG_BATTEMP_42_45,   "42 ~ 45"  },	//                      
	{     46,         52,     CHG_BATTEMP_46_52,   "46 ~ 52"  },	//                     
	{     53,         55,     CHG_BATTEMP_53_55,   "53 ~ 55"  },	//                     
	{     56,    INT_MAX,     CHG_BATTEMP_AB_OT,   "over 55"  },	//               
};

static enum lge_charging_states charging_state = 0;
static enum lge_states_changes states_change;
static int change_charger;
static int pseudo_chg_ui;
static int last_pseudo_chg_ui;

#ifdef CONFIG_LGE_PM_THERMAL
static int last_thermal_current;
#endif
static enum lge_battemp_states determine_batt_temp_state(int batt_temp)
{
	int cnt;

	/*                */
	for (cnt = (CHG_MAXIDX-1); 0 <= cnt; cnt--) {
		if (chg_temp_table[cnt].min <= batt_temp &&
			batt_temp <= chg_temp_table[cnt].max)
			break;
	}

	/*                                                  */
	if (cnt < 0)
		cnt = 2;

	return chg_temp_table[cnt].battemp_state;
}

static enum lge_charging_states
determine_lge_charging_state(enum lge_battemp_states battemp_st, int batt_volt)
{
	enum lge_charging_states next_state = charging_state;
	states_change = STS_CHE_NONE;

	/*                                                         */
	switch (charging_state) {
	case CHG_BATT_NORMAL_STATE:
		if (battemp_st >= CHG_BATTEMP_AB_OT ||
			battemp_st <= CHG_BATTEMP_BL_M11) {
			states_change = STS_CHE_NORMAL_TO_STPCHG;
			pseudo_chg_ui = 0;
			next_state = CHG_BATT_STPCHG_STATE;
		} else if (battemp_st == CHG_BATTEMP_46_52 || battemp_st == CHG_BATTEMP_53_55) {
			if (batt_volt > DC_IUSB_VOLTUV) {
				states_change = STS_CHE_NORMAL_TO_STPCHG;
				pseudo_chg_ui = 1;
				next_state = CHG_BATT_STPCHG_STATE;
			} else {
				states_change = STS_CHE_NORMAL_TO_DECCUR;
				pseudo_chg_ui = 0;
				next_state = CHG_BATT_DECCUR_STATE;
			}
		}
		break;
	case CHG_BATT_DECCUR_STATE:
		if (battemp_st >= CHG_BATTEMP_AB_OT ||
			battemp_st <= CHG_BATTEMP_BL_M11) {
			states_change = STS_CHE_DECCUR_TO_STPCHG;
			pseudo_chg_ui = 0;
			next_state = CHG_BATT_STPCHG_STATE;
		} else if (batt_volt > DC_IUSB_VOLTUV) {
			states_change = STS_CHE_DECCUR_TO_STPCHG;
			pseudo_chg_ui = 1;
			next_state = CHG_BATT_STPCHG_STATE;
		} else if (battemp_st <= CHG_BATTEMP_M4_41) {
			states_change = STS_CHE_DECCUR_TO_NORAML;
			pseudo_chg_ui = 0;
			next_state = CHG_BATT_NORMAL_STATE;
		}
		break;
	case CHG_BATT_WARNIG_STATE:
		break;
	case CHG_BATT_STPCHG_STATE:
		if (battemp_st == CHG_BATTEMP_M4_41) {
			states_change = STS_CHE_STPCHG_TO_NORMAL;
			pseudo_chg_ui = 0;
			next_state = CHG_BATT_NORMAL_STATE;
		}
		else if (battemp_st == CHG_BATTEMP_42_45 || battemp_st == CHG_BATTEMP_46_52) {
			if (batt_volt > DC_IUSB_VOLTUV) {
				pseudo_chg_ui = 1;
				next_state = CHG_BATT_STPCHG_STATE;
			} else {
				states_change = STS_CHE_STPCHG_TO_DECCUR;
				pseudo_chg_ui = 0;
				next_state = CHG_BATT_DECCUR_STATE;
			}
		}
		else if (battemp_st >= CHG_BATTEMP_AB_OT) {
			pseudo_chg_ui = 0;
			next_state = CHG_BATT_STPCHG_STATE;
		}
		break;
	default:
		pr_err("unknown charging status. %d\n", charging_state);
		break;
	}

	return next_state;
}

void lge_monitor_batt_temp(struct charging_info req, struct charging_rsp *res)
{
	enum lge_battemp_states battemp_state;
	enum lge_charging_states pre_state;
#ifdef DEBUG_LCS
#ifdef DEBUG_LCS_DUMMY_TEMP
	if (time_order == 1) {
		dummy_temp++;
		if (dummy_temp > 65)
			time_order = 0;
	} else {
		dummy_temp--;
		if (dummy_temp < -15)
			time_order = 1;
	}

	req.batt_temp = dummy_temp;
#endif
	pr_err("DLCS ==============================================\n");
	pr_err("DLCS : battery voltage     = %d\n", req.batt_volt);
	pr_err("DLCS : battery temperature = %d\n", req.batt_temp);
	pr_err("DLCS : charger connected   = %s\n", (req.is_charger ? "Yes" : "No"));
#ifdef CONFIG_LGE_PM_THERMAL
	pr_err("DLCS : current (normal)    = %d\n", req.chg_current_ma);
	pr_err("DLCS : current (thermal)   = %d\n", req.chg_current_te);
#endif
	pr_err("DLCS : charger changed     = %s\n", (req.is_charger_changed ? "Yes" : "No"));
#endif

	if (change_charger ^ req.is_charger || req.is_charger_changed ) {
		change_charger = req.is_charger;
		if (req.is_charger) {
			charging_state = CHG_BATT_NORMAL_STATE;
			res->force_update = true;
		} else
			res->force_update = false;
	} else
		res->force_update = false;

	pre_state = charging_state;

	battemp_state =
		determine_batt_temp_state(req.batt_temp);
	charging_state =
		determine_lge_charging_state(battemp_state, req.batt_volt);

	res->state = charging_state;
	res->change_lvl = states_change;
	res->disable_chg =
		charging_state == CHG_BATT_STPCHG_STATE ? true : false;
#ifdef CONFIG_LGE_PM_THERMAL
	if (charging_state == CHG_BATT_NORMAL_STATE) {
	    if (req.chg_current_te <= req.chg_current_ma)
			res->dc_current = req.chg_current_te;
		else
			res->dc_current = req.chg_current_ma;
	} else if (charging_state == CHG_BATT_DECCUR_STATE) {
		if (req.chg_current_te <= DC_IUSB_CURRENT)
			res->dc_current = req.chg_current_te;
		else
			res->dc_current = DC_IUSB_CURRENT;
	} else {
		res->dc_current = DC_CURRENT_DEF;
	}

	if (last_thermal_current ^ res->dc_current) {
		last_thermal_current = res->dc_current;
		res->force_update = true;
	}
#else
	res->dc_current =
		charging_state == CHG_BATT_DECCUR_STATE ? DC_IUSB_CURRENT : DC_CURRENT_DEF;
#endif

	res->btm_state = BTM_HEALTH_GOOD;

	if (battemp_state >= CHG_BATTEMP_AB_OT)
		res->btm_state = BTM_HEALTH_OVERHEAT;
	else if (battemp_state <= CHG_BATTEMP_BL_M11)
		res->btm_state = BTM_HEALTH_COLD;
	else
		res->btm_state = BTM_HEALTH_GOOD;

	res->pseudo_chg_ui = pseudo_chg_ui;
	if (last_pseudo_chg_ui ^ pseudo_chg_ui){
		last_pseudo_chg_ui = pseudo_chg_ui;
		res->force_update = true;
	}

#ifdef DEBUG_LCS
#ifdef DEBUG_LCS_DUMMY_TEMP
	pr_err("DLCS : dummy battery temperature  = %d\n", dummy_temp);
#endif
	pr_err("DLCS : battery temperature states = %s\n", chg_temp_table[battemp_state].str);
	pr_err("DLCS : res -> state        = %d\n", res->state);
	pr_err("DLCS : res -> change_lvl   = %d\n", res->change_lvl);
	pr_err("DLCS : res -> force_update = %d\n", res->force_update ? 1 : 0);
	pr_err("DLCS : res -> chg_disable  = %d\n", res->disable_chg ? 1 : 0);
	pr_err("DLCS : res -> dc_current   = %d\n", res->dc_current);
	pr_err("DLCS : res -> btm_state    = %d\n", res->btm_state);
	pr_err("DLCS : res -> is_charger   = %d\n", req.is_charger);
	pr_err("DLCS : res -> pseudo_chg_ui= %d\n", res->pseudo_chg_ui);
	pr_err("DLCS ==============================================\n");
#endif

#ifdef CONFIG_LGE_PM_THERMAL
	pr_err("LGE charging scenario : state %d -> %d(%d-%d),"\
		" temp=%d, volt=%d, BTM=%d, charger=%d, cur_set=%d/%d\n",
		pre_state, charging_state, res->change_lvl, res->force_update ? 1 : 0,
		req.batt_temp, req.batt_volt / 1000, res->btm_state, req.is_charger,
		req.chg_current_te, res->dc_current);
#else
	pr_err("LGE charging scenario : Change state "\
		"%d -> %d(%d-%d), temp=%d, volt=%d, BTM=%d, charger=%d\n",
		pre_state, charging_state, states_change,
		res->force_update ? 1 : 0, req.batt_temp, req.batt_volt / 1000,
		res->btm_state, req.is_charger);
#endif
}


