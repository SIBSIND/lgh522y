/*
 * This file is part of wl1271
 *
 * Copyright (C) 2009 Nokia Corporation
 *
 * Contact: Luciano Coelho <luciano.coelho@nokia.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 *
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>

#include "debug.h"
#include "init.h"
#include "wl12xx_80211.h"
#include "acx.h"
#include "cmd.h"
#include "tx.h"
#include "io.h"
#include "hw_ops.h"

int wl1271_init_templates_config(struct wl1271 *wl)
{
	int ret, i;
	size_t max_size;

	/*                                                */
	ret = wl1271_cmd_template_set(wl, WL12XX_INVALID_ROLE_ID,
				      wl->scan_templ_id_2_4, NULL,
				      WL1271_CMD_TEMPL_MAX_SIZE,
				      0, WL1271_RATE_AUTOMATIC);
	if (ret < 0)
		return ret;

	ret = wl1271_cmd_template_set(wl, WL12XX_INVALID_ROLE_ID,
				      wl->scan_templ_id_5,
				      NULL, WL1271_CMD_TEMPL_MAX_SIZE, 0,
				      WL1271_RATE_AUTOMATIC);
	if (ret < 0)
		return ret;

	if (wl->quirks & WLCORE_QUIRK_DUAL_PROBE_TMPL) {
		ret = wl1271_cmd_template_set(wl, WL12XX_INVALID_ROLE_ID,
					      wl->sched_scan_templ_id_2_4,
					      NULL,
					      WL1271_CMD_TEMPL_MAX_SIZE,
					      0, WL1271_RATE_AUTOMATIC);
		if (ret < 0)
			return ret;

		ret = wl1271_cmd_template_set(wl, WL12XX_INVALID_ROLE_ID,
					      wl->sched_scan_templ_id_5,
					      NULL,
					      WL1271_CMD_TEMPL_MAX_SIZE,
					      0, WL1271_RATE_AUTOMATIC);
		if (ret < 0)
			return ret;
	}

	ret = wl1271_cmd_template_set(wl, WL12XX_INVALID_ROLE_ID,
				      CMD_TEMPL_NULL_DATA, NULL,
				      sizeof(struct wl12xx_null_data_template),
				      0, WL1271_RATE_AUTOMATIC);
	if (ret < 0)
		return ret;

	ret = wl1271_cmd_template_set(wl, WL12XX_INVALID_ROLE_ID,
				      CMD_TEMPL_PS_POLL, NULL,
				      sizeof(struct wl12xx_ps_poll_template),
				      0, WL1271_RATE_AUTOMATIC);
	if (ret < 0)
		return ret;

	ret = wl1271_cmd_template_set(wl, WL12XX_INVALID_ROLE_ID,
				      CMD_TEMPL_QOS_NULL_DATA, NULL,
				      sizeof
				      (struct ieee80211_qos_hdr),
				      0, WL1271_RATE_AUTOMATIC);
	if (ret < 0)
		return ret;

	ret = wl1271_cmd_template_set(wl, WL12XX_INVALID_ROLE_ID,
				      CMD_TEMPL_PROBE_RESPONSE, NULL,
				      WL1271_CMD_TEMPL_DFLT_SIZE,
				      0, WL1271_RATE_AUTOMATIC);
	if (ret < 0)
		return ret;

	ret = wl1271_cmd_template_set(wl, WL12XX_INVALID_ROLE_ID,
				      CMD_TEMPL_BEACON, NULL,
				      WL1271_CMD_TEMPL_DFLT_SIZE,
				      0, WL1271_RATE_AUTOMATIC);
	if (ret < 0)
		return ret;

	max_size = sizeof(struct wl12xx_arp_rsp_template) +
		   WL1271_EXTRA_SPACE_MAX;
	ret = wl1271_cmd_template_set(wl, WL12XX_INVALID_ROLE_ID,
				      CMD_TEMPL_ARP_RSP, NULL,
				      max_size,
				      0, WL1271_RATE_AUTOMATIC);
	if (ret < 0)
		return ret;

	/*
                                                              
                             
  */
	ret = wl1271_cmd_template_set(wl, WL12XX_INVALID_ROLE_ID,
				      CMD_TEMPL_AP_PROBE_RESPONSE, NULL,
				      WL1271_CMD_TEMPL_MAX_SIZE,
				      0, WL1271_RATE_AUTOMATIC);
	if (ret < 0)
		return ret;

	ret = wl1271_cmd_template_set(wl, WL12XX_INVALID_ROLE_ID,
				      CMD_TEMPL_AP_BEACON, NULL,
				      WL1271_CMD_TEMPL_MAX_SIZE,
				      0, WL1271_RATE_AUTOMATIC);
	if (ret < 0)
		return ret;

	ret = wl1271_cmd_template_set(wl, WL12XX_INVALID_ROLE_ID,
				      CMD_TEMPL_DEAUTH_AP, NULL,
				      sizeof
				      (struct wl12xx_disconn_template),
				      0, WL1271_RATE_AUTOMATIC);
	if (ret < 0)
		return ret;

	for (i = 0; i < WLCORE_MAX_KLV_TEMPLATES; i++) {
		ret = wl1271_cmd_template_set(wl, WL12XX_INVALID_ROLE_ID,
					      CMD_TEMPL_KLV, NULL,
					      sizeof(struct ieee80211_qos_hdr),
					      i, WL1271_RATE_AUTOMATIC);
		if (ret < 0)
			return ret;
	}

	return 0;
}

static int wl1271_ap_init_deauth_template(struct wl1271 *wl,
					  struct wl12xx_vif *wlvif)
{
	struct wl12xx_disconn_template *tmpl;
	int ret;
	u32 rate;

	tmpl = kzalloc(sizeof(*tmpl), GFP_KERNEL);
	if (!tmpl) {
		ret = -ENOMEM;
		goto out;
	}

	tmpl->header.frame_ctl = cpu_to_le16(IEEE80211_FTYPE_MGMT |
					     IEEE80211_STYPE_DEAUTH);

	rate = wl1271_tx_min_rate_get(wl, wlvif->basic_rate_set);
	ret = wl1271_cmd_template_set(wl, wlvif->role_id,
				      CMD_TEMPL_DEAUTH_AP,
				      tmpl, sizeof(*tmpl), 0, rate);

out:
	kfree(tmpl);
	return ret;
}

static int wl1271_ap_init_null_template(struct wl1271 *wl,
					struct ieee80211_vif *vif)
{
	struct wl12xx_vif *wlvif = wl12xx_vif_to_data(vif);
	struct ieee80211_hdr_3addr *nullfunc;
	int ret;
	u32 rate;

	nullfunc = kzalloc(sizeof(*nullfunc), GFP_KERNEL);
	if (!nullfunc) {
		ret = -ENOMEM;
		goto out;
	}

	nullfunc->frame_control = cpu_to_le16(IEEE80211_FTYPE_DATA |
					      IEEE80211_STYPE_NULLFUNC |
					      IEEE80211_FCTL_FROMDS);

	/*                                 */

	memcpy(nullfunc->addr2, vif->addr, ETH_ALEN);
	memcpy(nullfunc->addr3, vif->addr, ETH_ALEN);

	rate = wl1271_tx_min_rate_get(wl, wlvif->basic_rate_set);
	ret = wl1271_cmd_template_set(wl, wlvif->role_id,
				      CMD_TEMPL_NULL_DATA, nullfunc,
				      sizeof(*nullfunc), 0, rate);

out:
	kfree(nullfunc);
	return ret;
}

static int wl1271_ap_init_qos_null_template(struct wl1271 *wl,
					    struct ieee80211_vif *vif)
{
	struct wl12xx_vif *wlvif = wl12xx_vif_to_data(vif);
	struct ieee80211_qos_hdr *qosnull;
	int ret;
	u32 rate;

	qosnull = kzalloc(sizeof(*qosnull), GFP_KERNEL);
	if (!qosnull) {
		ret = -ENOMEM;
		goto out;
	}

	qosnull->frame_control = cpu_to_le16(IEEE80211_FTYPE_DATA |
					     IEEE80211_STYPE_QOS_NULLFUNC |
					     IEEE80211_FCTL_FROMDS);

	/*                                */

	memcpy(qosnull->addr2, vif->addr, ETH_ALEN);
	memcpy(qosnull->addr3, vif->addr, ETH_ALEN);

	rate = wl1271_tx_min_rate_get(wl, wlvif->basic_rate_set);
	ret = wl1271_cmd_template_set(wl, wlvif->role_id,
				      CMD_TEMPL_QOS_NULL_DATA, qosnull,
				      sizeof(*qosnull), 0, rate);

out:
	kfree(qosnull);
	return ret;
}

static int wl12xx_init_rx_config(struct wl1271 *wl)
{
	int ret;

	ret = wl1271_acx_rx_msdu_life_time(wl);
	if (ret < 0)
		return ret;

	return 0;
}

static int wl12xx_init_phy_vif_config(struct wl1271 *wl,
					    struct wl12xx_vif *wlvif)
{
	int ret;

	ret = wl1271_acx_slot(wl, wlvif, DEFAULT_SLOT_TIME);
	if (ret < 0)
		return ret;

	ret = wl1271_acx_service_period_timeout(wl, wlvif);
	if (ret < 0)
		return ret;

	ret = wl1271_acx_rts_threshold(wl, wlvif, wl->hw->wiphy->rts_threshold);
	if (ret < 0)
		return ret;

	return 0;
}

static int wl1271_init_sta_beacon_filter(struct wl1271 *wl,
					 struct wl12xx_vif *wlvif)
{
	int ret;

	ret = wl1271_acx_beacon_filter_table(wl, wlvif);
	if (ret < 0)
		return ret;

	/*                         */
	ret = wl1271_acx_beacon_filter_opt(wl, wlvif, true);
	if (ret < 0)
		return ret;

	return 0;
}

int wl1271_init_pta(struct wl1271 *wl)
{
	int ret;

	ret = wl12xx_acx_sg_cfg(wl);
	if (ret < 0)
		return ret;

	ret = wl1271_acx_sg_enable(wl, wl->sg_enabled);
	if (ret < 0)
		return ret;

	return 0;
}

int wl1271_init_energy_detection(struct wl1271 *wl)
{
	int ret;

	ret = wl1271_acx_cca_threshold(wl);
	if (ret < 0)
		return ret;

	return 0;
}

static int wl1271_init_beacon_broadcast(struct wl1271 *wl,
					struct wl12xx_vif *wlvif)
{
	int ret;

	ret = wl1271_acx_bcn_dtim_options(wl, wlvif);
	if (ret < 0)
		return ret;

	return 0;
}

static int wl12xx_init_fwlog(struct wl1271 *wl)
{
	int ret;

	if (wl->quirks & WLCORE_QUIRK_FWLOG_NOT_IMPLEMENTED)
		return 0;

	ret = wl12xx_cmd_config_fwlog(wl);
	if (ret < 0)
		return ret;

	return 0;
}

/*                                               */
static int wl1271_sta_hw_init(struct wl1271 *wl, struct wl12xx_vif *wlvif)
{
	int ret;

	/*           */
	ret = wl12xx_acx_config_ps(wl, wlvif);
	if (ret < 0)
		return ret;

	/*                     */
	ret = wl1271_acx_fm_coex(wl);
	if (ret < 0)
		return ret;

	ret = wl1271_acx_sta_rate_policies(wl, wlvif);
	if (ret < 0)
		return ret;

	return 0;
}

static int wl1271_sta_hw_init_post_mem(struct wl1271 *wl,
				       struct ieee80211_vif *vif)
{
	struct wl12xx_vif *wlvif = wl12xx_vif_to_data(vif);
	int ret;

	/*                                */
	ret = wl1271_acx_keep_alive_mode(wl, wlvif, false);
	if (ret < 0)
		return ret;

	return 0;
}

/*                                              */
static int wl1271_ap_hw_init(struct wl1271 *wl, struct wl12xx_vif *wlvif)
{
	int ret;

	ret = wl1271_init_ap_rates(wl, wlvif);
	if (ret < 0)
		return ret;

	return 0;
}

int wl1271_ap_init_templates(struct wl1271 *wl, struct ieee80211_vif *vif)
{
	struct wl12xx_vif *wlvif = wl12xx_vif_to_data(vif);
	int ret;

	ret = wl1271_ap_init_deauth_template(wl, wlvif);
	if (ret < 0)
		return ret;

	ret = wl1271_ap_init_null_template(wl, vif);
	if (ret < 0)
		return ret;

	ret = wl1271_ap_init_qos_null_template(wl, vif);
	if (ret < 0)
		return ret;

	/*
                                                                
                               
  */
	ret = wl1271_acx_beacon_filter_opt(wl, wlvif, false);
	if (ret < 0)
		return ret;

	return 0;
}

static int wl1271_ap_hw_init_post_mem(struct wl1271 *wl,
				      struct ieee80211_vif *vif)
{
	return wl1271_ap_init_templates(wl, vif);
}

int wl1271_init_ap_rates(struct wl1271 *wl, struct wl12xx_vif *wlvif)
{
	int i, ret;
	struct conf_tx_rate_class rc;
	u32 supported_rates;

	wl1271_debug(DEBUG_AP, "AP basic rate set: 0x%x",
		     wlvif->basic_rate_set);

	if (wlvif->basic_rate_set == 0)
		return -EINVAL;

	rc.enabled_rates = wlvif->basic_rate_set;
	rc.long_retry_limit = 10;
	rc.short_retry_limit = 10;
	rc.aflags = 0;
	ret = wl1271_acx_ap_rate_policy(wl, &rc, wlvif->ap.mgmt_rate_idx);
	if (ret < 0)
		return ret;

	/*                                                   */
	rc.enabled_rates = wl1271_tx_min_rate_get(wl, wlvif->basic_rate_set);
	rc.short_retry_limit = 10;
	rc.long_retry_limit = 10;
	rc.aflags = 0;
	ret = wl1271_acx_ap_rate_policy(wl, &rc, wlvif->ap.bcast_rate_idx);
	if (ret < 0)
		return ret;

	/*
                                                        
                                                               
  */
	if ((wlvif->basic_rate_set & CONF_TX_OFDM_RATES))
		supported_rates = CONF_TX_OFDM_RATES;
	else
		supported_rates = CONF_TX_ENABLED_RATES;

	/*                                 */
	supported_rates |= CONF_TX_MCS_RATES;

	/*                                                            */
	supported_rates |= wlcore_hw_ap_get_mimo_wide_rate_mask(wl, wlvif);

	/*                                   */
	for (i = 0; i < wl->conf.tx.ac_conf_count; i++) {
		rc.enabled_rates = supported_rates;
		rc.short_retry_limit = 10;
		rc.long_retry_limit = 10;
		rc.aflags = 0;
		ret = wl1271_acx_ap_rate_policy(wl, &rc,
						wlvif->ap.ucast_rate_idx[i]);
		if (ret < 0)
			return ret;
	}

	return 0;
}

static int wl1271_set_ba_policies(struct wl1271 *wl, struct wl12xx_vif *wlvif)
{
	/*                            */
	wlvif->ba_allowed = true;
	wl->ba_rx_session_count = 0;

	/*                                 */
	if (wlvif->bss_type != BSS_TYPE_AP_BSS &&
	    wlvif->bss_type != BSS_TYPE_STA_BSS) {
		wlvif->ba_support = false;
		return 0;
	}

	wlvif->ba_support = true;

	/*                                      */
	return wl12xx_acx_set_ba_initiator_policy(wl, wlvif);
}

/*                            */
static int wl12xx_init_sta_role(struct wl1271 *wl, struct wl12xx_vif *wlvif)
{
	int ret;

	ret = wl1271_acx_group_address_tbl(wl, wlvif, true, NULL, 0);
	if (ret < 0)
		return ret;

	/*                                             */
	ret = wl1271_acx_conn_monit_params(wl, wlvif, false);
	if (ret < 0)
		return ret;

	/*                  */
	ret = wl1271_init_sta_beacon_filter(wl, wlvif);
	if (ret < 0)
		return ret;

	/*                                */
	ret = wl1271_init_beacon_broadcast(wl, wlvif);
	if (ret < 0)
		return ret;

	/*                                      */
	ret = wl1271_acx_rssi_snr_avg_weights(wl, wlvif);
	if (ret < 0)
		return ret;

	return 0;
}

/*                            */
static int wl12xx_init_ap_role(struct wl1271 *wl, struct wl12xx_vif *wlvif)
{
	int ret;

	ret = wl1271_acx_ap_max_tx_retry(wl, wlvif);
	if (ret < 0)
		return ret;

	/*                     */
	ret = wl1271_acx_tx_power(wl, wlvif, wlvif->power_level);
	if (ret < 0)
		return ret;

	return 0;
}

int wl1271_init_vif_specific(struct wl1271 *wl, struct ieee80211_vif *vif)
{
	struct wl12xx_vif *wlvif = wl12xx_vif_to_data(vif);
	struct conf_tx_ac_category *conf_ac;
	struct conf_tx_tid *conf_tid;
	bool is_ap = (wlvif->bss_type == BSS_TYPE_AP_BSS);
	int ret, i;

	/*                                                     */

	if (wl->ap_count == 0 && is_ap) { /*          */
		/*                               */
		ret = wl1271_acx_sleep_auth(wl, WL1271_PSM_CAM);
		if (ret < 0)
			return ret;
	/*                   */
	} else if (wl->sta_count == 0 && wl->ap_count == 0 && !is_ap) {
		u8 sta_auth = wl->conf.conn.sta_sleep_auth;
		/*                                          */
		if (sta_auth != WL1271_PSM_ILLEGAL)
			ret = wl1271_acx_sleep_auth(wl, sta_auth);
		/*                                */
		else
			ret = wl1271_acx_sleep_auth(wl, WL1271_PSM_ELP);

		if (ret < 0)
			return ret;
	}

	/*                    */
	if (is_ap) {
		ret = wl1271_ap_hw_init(wl, wlvif);
		if (ret < 0)
			return ret;

		ret = wl12xx_init_ap_role(wl, wlvif);
		if (ret < 0)
			return ret;
	} else {
		ret = wl1271_sta_hw_init(wl, wlvif);
		if (ret < 0)
			return ret;

		ret = wl12xx_init_sta_role(wl, wlvif);
		if (ret < 0)
			return ret;
	}

	wl12xx_init_phy_vif_config(wl, wlvif);

	/*                              */
	BUG_ON(wl->conf.tx.tid_conf_count != wl->conf.tx.ac_conf_count);
	for (i = 0; i < wl->conf.tx.tid_conf_count; i++) {
		conf_ac = &wl->conf.tx.ac_conf[i];
		ret = wl1271_acx_ac_cfg(wl, wlvif, conf_ac->ac,
					conf_ac->cw_min, conf_ac->cw_max,
					conf_ac->aifsn, conf_ac->tx_op_limit);
		if (ret < 0)
			return ret;

		conf_tid = &wl->conf.tx.tid_conf[i];
		ret = wl1271_acx_tid_cfg(wl, wlvif,
					 conf_tid->queue_id,
					 conf_tid->channel_type,
					 conf_tid->tsid,
					 conf_tid->ps_scheme,
					 conf_tid->ack_policy,
					 conf_tid->apsd_conf[0],
					 conf_tid->apsd_conf[1]);
		if (ret < 0)
			return ret;
	}

	/*                         */
	ret = wl1271_acx_feature_cfg(wl, wlvif);
	if (ret < 0)
		return ret;

	/*                                    */
	if (is_ap)
		ret = wl1271_ap_hw_init_post_mem(wl, vif);
	else
		ret = wl1271_sta_hw_init_post_mem(wl, vif);

	if (ret < 0)
		return ret;

	/*                                          */
	ret = wl1271_set_ba_policies(wl, wlvif);
	if (ret < 0)
		return ret;

	ret = wlcore_hw_init_vif(wl, wlvif);
	if (ret < 0)
		return ret;

	return 0;
}

int wl1271_hw_init(struct wl1271 *wl)
{
	int ret;

	/*                       */
	ret = wl->ops->hw_init(wl);
	if (ret < 0)
		return ret;

	/*                */
	ret = wl1271_init_templates_config(wl);
	if (ret < 0)
		return ret;

	ret = wl12xx_acx_mem_cfg(wl);
	if (ret < 0)
		return ret;

	/*                         */
	ret = wl12xx_init_fwlog(wl);
	if (ret < 0)
		return ret;

	ret = wlcore_cmd_regdomain_config_locked(wl);
	if (ret < 0)
		return ret;

	/*                            */
	ret = wl1271_init_pta(wl);
	if (ret < 0)
		return ret;

	/*                              */
	ret = wl1271_acx_init_mem_config(wl);
	if (ret < 0)
		return ret;

	/*           */
	ret = wl12xx_init_rx_config(wl);
	if (ret < 0)
		goto out_free_memmap;

	ret = wl1271_acx_dco_itrim_params(wl);
	if (ret < 0)
		goto out_free_memmap;

	/*                                                */
	ret = wl1271_acx_tx_config_options(wl);
	if (ret < 0)
		goto out_free_memmap;

	/*                              */
	ret = wl1271_acx_init_rx_interrupt(wl);
	if (ret < 0)
		goto out_free_memmap;

	/*                  */
	ret = wl1271_init_energy_detection(wl);
	if (ret < 0)
		goto out_free_memmap;

	/*                                 */
	ret = wl1271_acx_frag_threshold(wl, wl->hw->wiphy->frag_threshold);
	if (ret < 0)
		goto out_free_memmap;

	/*                  */
	ret = wl1271_cmd_data_path(wl, 1);
	if (ret < 0)
		goto out_free_memmap;

	/*              */
	ret = wl1271_acx_pm_config(wl);
	if (ret < 0)
		goto out_free_memmap;

	ret = wl12xx_acx_set_rate_mgmt_params(wl);
	if (ret < 0)
		goto out_free_memmap;

	/*                    */
	ret = wl12xx_acx_config_hangover(wl);
	if (ret < 0)
		goto out_free_memmap;

	return 0;

 out_free_memmap:
	kfree(wl->target_mem_map);
	wl->target_mem_map = NULL;

	return ret;
}
