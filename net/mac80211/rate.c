/*
 * Copyright 2002-2005, Instant802 Networks, Inc.
 * Copyright 2005-2006, Devicescape Software, Inc.
 * Copyright (c) 2006 Jiri Benc <jbenc@suse.cz>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/rtnetlink.h>
#include <linux/slab.h>
#include <linux/module.h>
#include "rate.h"
#include "ieee80211_i.h"
#include "debugfs.h"

struct rate_control_alg {
	struct list_head list;
	struct rate_control_ops *ops;
};

static LIST_HEAD(rate_ctrl_algs);
static DEFINE_MUTEX(rate_ctrl_mutex);

static char *ieee80211_default_rc_algo = CONFIG_MAC80211_RC_DEFAULT;
module_param(ieee80211_default_rc_algo, charp, 0644);
MODULE_PARM_DESC(ieee80211_default_rc_algo,
		 "Default rate control algorithm for mac80211 to use");

int ieee80211_rate_control_register(struct rate_control_ops *ops)
{
	struct rate_control_alg *alg;

	if (!ops->name)
		return -EINVAL;

	mutex_lock(&rate_ctrl_mutex);
	list_for_each_entry(alg, &rate_ctrl_algs, list) {
		if (!strcmp(alg->ops->name, ops->name)) {
			/*                                   */
			WARN_ON(1);
			mutex_unlock(&rate_ctrl_mutex);
			return -EALREADY;
		}
	}

	alg = kzalloc(sizeof(*alg), GFP_KERNEL);
	if (alg == NULL) {
		mutex_unlock(&rate_ctrl_mutex);
		return -ENOMEM;
	}
	alg->ops = ops;

	list_add_tail(&alg->list, &rate_ctrl_algs);
	mutex_unlock(&rate_ctrl_mutex);

	return 0;
}
EXPORT_SYMBOL(ieee80211_rate_control_register);

void ieee80211_rate_control_unregister(struct rate_control_ops *ops)
{
	struct rate_control_alg *alg;

	mutex_lock(&rate_ctrl_mutex);
	list_for_each_entry(alg, &rate_ctrl_algs, list) {
		if (alg->ops == ops) {
			list_del(&alg->list);
			kfree(alg);
			break;
		}
	}
	mutex_unlock(&rate_ctrl_mutex);
}
EXPORT_SYMBOL(ieee80211_rate_control_unregister);

static struct rate_control_ops *
ieee80211_try_rate_control_ops_get(const char *name)
{
	struct rate_control_alg *alg;
	struct rate_control_ops *ops = NULL;

	if (!name)
		return NULL;

	mutex_lock(&rate_ctrl_mutex);
	list_for_each_entry(alg, &rate_ctrl_algs, list) {
		if (!strcmp(alg->ops->name, name))
			if (try_module_get(alg->ops->module)) {
				ops = alg->ops;
				break;
			}
	}
	mutex_unlock(&rate_ctrl_mutex);
	return ops;
}

/*                                 */
static struct rate_control_ops *
ieee80211_rate_control_ops_get(const char *name)
{
	struct rate_control_ops *ops;
	const char *alg_name;

	kparam_block_sysfs_write(ieee80211_default_rc_algo);
	if (!name)
		alg_name = ieee80211_default_rc_algo;
	else
		alg_name = name;

	ops = ieee80211_try_rate_control_ops_get(alg_name);
	if (!ops) {
		request_module("rc80211_%s", alg_name);
		ops = ieee80211_try_rate_control_ops_get(alg_name);
	}
	if (!ops && name)
		/*                                                     */
		ops = ieee80211_try_rate_control_ops_get(ieee80211_default_rc_algo);

	/*                                                          */
	if (!ops && strlen(CONFIG_MAC80211_RC_DEFAULT))
		ops = ieee80211_try_rate_control_ops_get(CONFIG_MAC80211_RC_DEFAULT);
	kparam_unblock_sysfs_write(ieee80211_default_rc_algo);

	return ops;
}

static void ieee80211_rate_control_ops_put(struct rate_control_ops *ops)
{
	module_put(ops->module);
}

#ifdef CONFIG_MAC80211_DEBUGFS
static ssize_t rcname_read(struct file *file, char __user *userbuf,
			   size_t count, loff_t *ppos)
{
	struct rate_control_ref *ref = file->private_data;
	int len = strlen(ref->ops->name);

	return simple_read_from_buffer(userbuf, count, ppos,
				       ref->ops->name, len);
}

static const struct file_operations rcname_ops = {
	.read = rcname_read,
	.open = simple_open,
	.llseek = default_llseek,
};
#endif

static struct rate_control_ref *rate_control_alloc(const char *name,
					    struct ieee80211_local *local)
{
	struct dentry *debugfsdir = NULL;
	struct rate_control_ref *ref;

	ref = kmalloc(sizeof(struct rate_control_ref), GFP_KERNEL);
	if (!ref)
		goto fail_ref;
	ref->local = local;
	ref->ops = ieee80211_rate_control_ops_get(name);
	if (!ref->ops)
		goto fail_ops;

#ifdef CONFIG_MAC80211_DEBUGFS
	debugfsdir = debugfs_create_dir("rc", local->hw.wiphy->debugfsdir);
	local->debugfs.rcdir = debugfsdir;
	debugfs_create_file("name", 0400, debugfsdir, ref, &rcname_ops);
#endif

	ref->priv = ref->ops->alloc(&local->hw, debugfsdir);
	if (!ref->priv)
		goto fail_priv;
	return ref;

fail_priv:
	ieee80211_rate_control_ops_put(ref->ops);
fail_ops:
	kfree(ref);
fail_ref:
	return NULL;
}

static void rate_control_free(struct rate_control_ref *ctrl_ref)
{
	ctrl_ref->ops->free(ctrl_ref->priv);

#ifdef CONFIG_MAC80211_DEBUGFS
	debugfs_remove_recursive(ctrl_ref->local->debugfs.rcdir);
	ctrl_ref->local->debugfs.rcdir = NULL;
#endif

	ieee80211_rate_control_ops_put(ctrl_ref->ops);
	kfree(ctrl_ref);
}

static bool rc_no_data_or_no_ack_use_min(struct ieee80211_tx_rate_control *txrc)
{
	struct sk_buff *skb = txrc->skb;
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *) skb->data;
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	__le16 fc;

	fc = hdr->frame_control;

	return (info->flags & (IEEE80211_TX_CTL_NO_ACK |
			       IEEE80211_TX_CTL_USE_MINRATE)) ||
		!ieee80211_is_data(fc);
}

static void rc_send_low_broadcast(s8 *idx, u32 basic_rates,
				  struct ieee80211_supported_band *sband)
{
	u8 i;

	if (basic_rates == 0)
		return; /*                                            */
	if (*idx < 0)
		return;
	if (basic_rates & (1 << *idx))
		return; /*                               */

	for (i = *idx + 1; i <= sband->n_bitrates; i++) {
		if (basic_rates & (1 << i)) {
			*idx = i;
			return;
		}
	}

	/*                                                     */
}

static inline s8
rate_lowest_non_cck_index(struct ieee80211_supported_band *sband,
			  struct ieee80211_sta *sta)
{
	int i;

	for (i = 0; i < sband->n_bitrates; i++) {
		struct ieee80211_rate *srate = &sband->bitrates[i];
		if ((srate->bitrate == 10) || (srate->bitrate == 20) ||
		    (srate->bitrate == 55) || (srate->bitrate == 110))
			continue;

		if (rate_supported(sta, sband->band, i))
			return i;
	}

	/*                        */
	return 0;
}

static void __rate_control_send_low(struct ieee80211_hw *hw,
				    struct ieee80211_supported_band *sband,
				    struct ieee80211_sta *sta,
				    struct ieee80211_tx_info *info)
{
	if ((sband->band != IEEE80211_BAND_2GHZ) ||
	    !(info->flags & IEEE80211_TX_CTL_NO_CCK_RATE))
		info->control.rates[0].idx = rate_lowest_index(sband, sta);
	else
		info->control.rates[0].idx =
			rate_lowest_non_cck_index(sband, sta);

	info->control.rates[0].count =
		(info->flags & IEEE80211_TX_CTL_NO_ACK) ?
		1 : hw->max_rate_tries;

	info->control.skip_table = 1;
}


bool rate_control_send_low(struct ieee80211_sta *sta,
			   void *priv_sta,
			   struct ieee80211_tx_rate_control *txrc)
{
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(txrc->skb);
	struct ieee80211_supported_band *sband = txrc->sband;
	int mcast_rate;

	if (!sta || !priv_sta || rc_no_data_or_no_ack_use_min(txrc)) {
		__rate_control_send_low(txrc->hw, sband, sta, info);

		if (!sta && txrc->bss) {
			mcast_rate = txrc->bss_conf->mcast_rate[sband->band];
			if (mcast_rate > 0) {
				info->control.rates[0].idx = mcast_rate - 1;
				return true;
			}

			rc_send_low_broadcast(&info->control.rates[0].idx,
					      txrc->bss_conf->basic_rates,
					      sband);
		}
		return true;
	}
	return false;
}
EXPORT_SYMBOL(rate_control_send_low);

static bool rate_idx_match_legacy_mask(struct ieee80211_tx_rate *rate,
				       int n_bitrates, u32 mask)
{
	int j;

	/*                                                                */
	for (j = rate->idx; j >= 0; j--) {
		if (mask & (1 << j)) {
			/*                                      */
			rate->idx = j;
			return true;
		}
	}

	/*                                                 */
	for (j = rate->idx + 1; j < n_bitrates; j++) {
		if (mask & (1 << j)) {
			/*                                      */
			rate->idx = j;
			return true;
		}
	}
	return false;
}

static bool rate_idx_match_mcs_mask(struct ieee80211_tx_rate *rate,
				    u8 mcs_mask[IEEE80211_HT_MCS_MASK_LEN])
{
	int i, j;
	int ridx, rbit;

	ridx = rate->idx / 8;
	rbit = rate->idx % 8;

	/*              */
	if (ridx < 0 || ridx >= IEEE80211_HT_MCS_MASK_LEN)
		return false;

	/*                                                                */
	for (i = ridx; i >= 0; i--) {
		for (j = rbit; j >= 0; j--)
			if (mcs_mask[i] & BIT(j)) {
				rate->idx = i * 8 + j;
				return true;
			}
		rbit = 7;
	}

	/*                                                 */
	ridx = (rate->idx + 1) / 8;
	rbit = (rate->idx + 1) % 8;

	for (i = ridx; i < IEEE80211_HT_MCS_MASK_LEN; i++) {
		for (j = rbit; j < 8; j++)
			if (mcs_mask[i] & BIT(j)) {
				rate->idx = i * 8 + j;
				return true;
			}
		rbit = 0;
	}
	return false;
}



static void rate_idx_match_mask(struct ieee80211_tx_rate *rate,
				struct ieee80211_supported_band *sband,
				enum nl80211_chan_width chan_width,
				u32 mask,
				u8 mcs_mask[IEEE80211_HT_MCS_MASK_LEN])
{
	struct ieee80211_tx_rate alt_rate;

	/*                 */
	if (rate->flags & IEEE80211_TX_RC_MCS) {
		if (rate_idx_match_mcs_mask(rate, mcs_mask))
			return;

		/*                            */
		alt_rate.idx = 0;
		/*                       */
		alt_rate.flags = rate->flags &
				 (IEEE80211_TX_RC_USE_RTS_CTS |
				  IEEE80211_TX_RC_USE_CTS_PROTECT |
				  IEEE80211_TX_RC_USE_SHORT_PREAMBLE);
		alt_rate.count = rate->count;
		if (rate_idx_match_legacy_mask(&alt_rate,
					       sband->n_bitrates, mask)) {
			*rate = alt_rate;
			return;
		}
	} else {
		/*                     */
		if (rate_idx_match_legacy_mask(rate, sband->n_bitrates, mask))
			return;

		/*                                                          */
		if (chan_width == NL80211_CHAN_WIDTH_20_NOHT)
			return;

		alt_rate.idx = 0;
		/*                       */
		alt_rate.flags = rate->flags &
				 (IEEE80211_TX_RC_USE_RTS_CTS |
				  IEEE80211_TX_RC_USE_CTS_PROTECT |
				  IEEE80211_TX_RC_USE_SHORT_PREAMBLE);
		alt_rate.count = rate->count;

		alt_rate.flags |= IEEE80211_TX_RC_MCS;

		if (chan_width == NL80211_CHAN_WIDTH_40)
			alt_rate.flags |= IEEE80211_TX_RC_40_MHZ_WIDTH;

		if (rate_idx_match_mcs_mask(&alt_rate, mcs_mask)) {
			*rate = alt_rate;
			return;
		}
	}

	/*
                                                                    
                                                                       
                                                                   
                                                                    
             
  */
}

static void rate_fixup_ratelist(struct ieee80211_vif *vif,
				struct ieee80211_supported_band *sband,
				struct ieee80211_tx_info *info,
				struct ieee80211_tx_rate *rates,
				int max_rates)
{
	struct ieee80211_rate *rate;
	bool inval = false;
	int i;

	/*
                                                     
                                                      
                                                        
                                       
   
                                           
  */
	if (!(rates[0].flags & IEEE80211_TX_RC_MCS)) {
		u32 basic_rates = vif->bss_conf.basic_rates;
		s8 baserate = basic_rates ? ffs(basic_rates) - 1 : 0;

		rate = &sband->bitrates[rates[0].idx];

		for (i = 0; i < sband->n_bitrates; i++) {
			/*                      */
			if (!(basic_rates & BIT(i)))
				continue;
			/*                                       */
			if (sband->bitrates[i].bitrate > rate->bitrate)
				continue;
			/*         */
			if (sband->bitrates[baserate].bitrate <
			     sband->bitrates[i].bitrate)
				baserate = i;
		}

		info->control.rts_cts_rate_idx = baserate;
	}

	for (i = 0; i < max_rates; i++) {
		/*
                                              
                                               
                                          
   */
		if (inval) {
			rates[i].idx = -1;
			continue;
		}
		if (rates[i].idx < 0) {
			inval = true;
			continue;
		}

		/*
                                                         
                       
   */
		if (rates[i].flags & IEEE80211_TX_RC_MCS) {
			WARN_ON(rates[i].idx > 76);

			if (!(rates[i].flags & IEEE80211_TX_RC_USE_RTS_CTS) &&
			    info->control.use_cts_prot)
				rates[i].flags |=
					IEEE80211_TX_RC_USE_CTS_PROTECT;
			continue;
		}

		if (rates[i].flags & IEEE80211_TX_RC_VHT_MCS) {
			WARN_ON(ieee80211_rate_get_vht_mcs(&rates[i]) > 9);
			continue;
		}

		/*                                  */
		if (info->control.use_rts) {
			rates[i].flags |= IEEE80211_TX_RC_USE_RTS_CTS;
			info->control.use_cts_prot = false;
		}

		/*              */
		if (WARN_ON_ONCE(rates[i].idx >= sband->n_bitrates)) {
			rates[i].idx = -1;
			continue;
		}

		rate = &sband->bitrates[rates[i].idx];

		/*                       */
		if (info->control.short_preamble &&
		    rate->flags & IEEE80211_RATE_SHORT_PREAMBLE)
			rates[i].flags |= IEEE80211_TX_RC_USE_SHORT_PREAMBLE;

		/*                     */
		if (!(rates[i].flags & IEEE80211_TX_RC_USE_RTS_CTS) &&
		    info->control.use_cts_prot &&
		    rate->flags & IEEE80211_RATE_ERP_G)
			rates[i].flags |= IEEE80211_TX_RC_USE_CTS_PROTECT;
	}
}


static void rate_control_fill_sta_table(struct ieee80211_sta *sta,
					struct ieee80211_tx_info *info,
					struct ieee80211_tx_rate *rates,
					int max_rates)
{
	struct ieee80211_sta_rates *ratetbl = NULL;
	int i;

	if (sta && !info->control.skip_table)
		ratetbl = rcu_dereference(sta->rates);

	/*                                                              */
	max_rates = min_t(int, max_rates, IEEE80211_TX_RATE_TABLE_SIZE);
	for (i = 0; i < max_rates; i++) {
		if (i < ARRAY_SIZE(info->control.rates) &&
		    info->control.rates[i].idx >= 0 &&
		    info->control.rates[i].count) {
			if (rates != info->control.rates)
				rates[i] = info->control.rates[i];
		} else if (ratetbl) {
			rates[i].idx = ratetbl->rate[i].idx;
			rates[i].flags = ratetbl->rate[i].flags;
			if (info->control.use_rts)
				rates[i].count = ratetbl->rate[i].count_rts;
			else if (info->control.use_cts_prot)
				rates[i].count = ratetbl->rate[i].count_cts;
			else
				rates[i].count = ratetbl->rate[i].count;
		} else {
			rates[i].idx = -1;
			rates[i].count = 0;
		}

		if (rates[i].idx < 0 || !rates[i].count)
			break;
	}
}

static void rate_control_apply_mask(struct ieee80211_sub_if_data *sdata,
				    struct ieee80211_sta *sta,
				    struct ieee80211_supported_band *sband,
				    struct ieee80211_tx_info *info,
				    struct ieee80211_tx_rate *rates,
				    int max_rates)
{
	enum nl80211_chan_width chan_width;
	u8 mcs_mask[IEEE80211_HT_MCS_MASK_LEN];
	bool has_mcs_mask;
	u32 mask;
	int i;

	/*
                                                                     
                                                                      
                    
  */
	mask = sdata->rc_rateidx_mask[info->band];
	has_mcs_mask = sdata->rc_has_mcs_mask[info->band];
	if (mask == (1 << sband->n_bitrates) - 1 && !has_mcs_mask)
		return;

	if (has_mcs_mask)
		memcpy(mcs_mask, sdata->rc_rateidx_mcs_mask[info->band],
		       sizeof(mcs_mask));
	else
		memset(mcs_mask, 0xff, sizeof(mcs_mask));

	if (sta) {
		/*                                                */
		mask &= sta->supp_rates[info->band];
		for (i = 0; i < sizeof(mcs_mask); i++)
			mcs_mask[i] &= sta->ht_cap.mcs.rx_mask[i];
	}

	/*
                                                         
                                                               
              
  */
	chan_width = sdata->vif.bss_conf.chandef.width;
	for (i = 0; i < max_rates; i++) {
		/*                    */
		if (rates[i].idx < 0)
			break;

		rate_idx_match_mask(&rates[i], sband, chan_width, mask,
				    mcs_mask);
	}
}

void ieee80211_get_tx_rates(struct ieee80211_vif *vif,
			    struct ieee80211_sta *sta,
			    struct sk_buff *skb,
			    struct ieee80211_tx_rate *dest,
			    int max_rates)
{
	struct ieee80211_sub_if_data *sdata;
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *) skb->data;
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	struct ieee80211_supported_band *sband;

	rate_control_fill_sta_table(sta, info, dest, max_rates);

	if (!vif)
		return;

	sdata = vif_to_sdata(vif);
	sband = sdata->local->hw.wiphy->bands[info->band];

	if (ieee80211_is_data(hdr->frame_control))
		rate_control_apply_mask(sdata, sta, sband, info, dest, max_rates);

	if (dest[0].idx < 0)
		__rate_control_send_low(&sdata->local->hw, sband, sta, info);

	if (sta)
		rate_fixup_ratelist(vif, sband, info, dest, max_rates);
}
EXPORT_SYMBOL(ieee80211_get_tx_rates);

void rate_control_get_rate(struct ieee80211_sub_if_data *sdata,
			   struct sta_info *sta,
			   struct ieee80211_tx_rate_control *txrc)
{
	struct rate_control_ref *ref = sdata->local->rate_ctrl;
	void *priv_sta = NULL;
	struct ieee80211_sta *ista = NULL;
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(txrc->skb);
	int i;

	if (sta && test_sta_flag(sta, WLAN_STA_RATE_CONTROL)) {
		ista = &sta->sta;
		priv_sta = sta->rate_ctrl_priv;
	}

	for (i = 0; i < IEEE80211_TX_MAX_RATES; i++) {
		info->control.rates[i].idx = -1;
		info->control.rates[i].flags = 0;
		info->control.rates[i].count = 0;
	}

	if (sdata->local->hw.flags & IEEE80211_HW_HAS_RATE_CONTROL)
		return;

	ref->ops->get_rate(ref->priv, ista, priv_sta, txrc);

	if (sdata->local->hw.flags & IEEE80211_HW_SUPPORTS_RC_TABLE)
		return;

	ieee80211_get_tx_rates(&sdata->vif, ista, txrc->skb,
			       info->control.rates,
			       ARRAY_SIZE(info->control.rates));
}

int rate_control_set_rates(struct ieee80211_hw *hw,
			   struct ieee80211_sta *pubsta,
			   struct ieee80211_sta_rates *rates)
{
	struct ieee80211_sta_rates *old;

	/*
                                                             
                                                                   
                                                                 
                          
  */
	old = rcu_dereference_protected(pubsta->rates, true);
	rcu_assign_pointer(pubsta->rates, rates);
	if (old)
		kfree_rcu(old, rcu_head);

	return 0;
}
EXPORT_SYMBOL(rate_control_set_rates);

int ieee80211_init_rate_ctrl_alg(struct ieee80211_local *local,
				 const char *name)
{
	struct rate_control_ref *ref;

	ASSERT_RTNL();

	if (local->open_count)
		return -EBUSY;

	if (local->hw.flags & IEEE80211_HW_HAS_RATE_CONTROL) {
		if (WARN_ON(!local->ops->set_rts_threshold))
			return -EINVAL;
		return 0;
	}

	ref = rate_control_alloc(name, local);
	if (!ref) {
		wiphy_warn(local->hw.wiphy,
			   "Failed to select rate control algorithm\n");
		return -ENOENT;
	}

	WARN_ON(local->rate_ctrl);
	local->rate_ctrl = ref;

	wiphy_debug(local->hw.wiphy, "Selected rate control algorithm '%s'\n",
		    ref->ops->name);

	return 0;
}

void rate_control_deinitialize(struct ieee80211_local *local)
{
	struct rate_control_ref *ref;

	ref = local->rate_ctrl;

	if (!ref)
		return;

	local->rate_ctrl = NULL;
	rate_control_free(ref);
}

