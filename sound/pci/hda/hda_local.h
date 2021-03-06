/*
 * Universal Interface for Intel High Definition Audio Codec
 *
 * Local helper functions
 *
 * Copyright (c) 2004 Takashi Iwai <tiwai@suse.de>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by the Free
 *  Software Foundation; either version 2 of the License, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *  more details.
 *
 *  You should have received a copy of the GNU General Public License along with
 *  this program; if not, write to the Free Software Foundation, Inc., 59
 *  Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#ifndef __SOUND_HDA_LOCAL_H
#define __SOUND_HDA_LOCAL_H

/*                                                                    
                                                                           
                                                                     
   
                                                                              
                                                                        
 */
#define HDA_SUBDEV_NID_FLAG	(1U << 31)
#define HDA_SUBDEV_AMP_FLAG	(1U << 30)

/*
                     
 */
#define HDA_COMPOSE_AMP_VAL_OFS(nid,chs,idx,dir,ofs)		\
	((nid) | ((chs)<<16) | ((dir)<<18) | ((idx)<<19) | ((ofs)<<23))
#define HDA_AMP_VAL_MIN_MUTE (1<<29)
#define HDA_COMPOSE_AMP_VAL(nid,chs,idx,dir) \
	HDA_COMPOSE_AMP_VAL_OFS(nid, chs, idx, dir, 0)
/*                                                      */
#define HDA_CODEC_VOLUME_MONO_IDX(xname, xcidx, nid, channel, xindex, dir, flags) \
	{ .iface = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xcidx,  \
	  .subdevice = HDA_SUBDEV_AMP_FLAG, \
	  .access = SNDRV_CTL_ELEM_ACCESS_READWRITE | \
	  	    SNDRV_CTL_ELEM_ACCESS_TLV_READ | \
	  	    SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK, \
	  .info = snd_hda_mixer_amp_volume_info, \
	  .get = snd_hda_mixer_amp_volume_get, \
	  .put = snd_hda_mixer_amp_volume_put, \
	  .tlv = { .c = snd_hda_mixer_amp_tlv },		\
	  .private_value = HDA_COMPOSE_AMP_VAL(nid, channel, xindex, dir) | flags }
/*                          */
#define HDA_CODEC_VOLUME_IDX(xname, xcidx, nid, xindex, direction) \
	HDA_CODEC_VOLUME_MONO_IDX(xname, xcidx, nid, 3, xindex, direction, 0)
/*             */
#define HDA_CODEC_VOLUME_MONO(xname, nid, channel, xindex, direction) \
	HDA_CODEC_VOLUME_MONO_IDX(xname, 0, nid, channel, xindex, direction, 0)
/*               */
#define HDA_CODEC_VOLUME(xname, nid, xindex, direction) \
	HDA_CODEC_VOLUME_MONO(xname, nid, 3, xindex, direction)
/*                             */
#define HDA_CODEC_VOLUME_MIN_MUTE(xname, nid, xindex, direction) \
	HDA_CODEC_VOLUME_MONO_IDX(xname, 0, nid, 3, xindex, direction, \
				  HDA_AMP_VAL_MIN_MUTE)
/*                                                           */
#define HDA_CODEC_MUTE_MONO_IDX(xname, xcidx, nid, channel, xindex, direction) \
	{ .iface = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xcidx, \
	  .subdevice = HDA_SUBDEV_AMP_FLAG, \
	  .info = snd_hda_mixer_amp_switch_info, \
	  .get = snd_hda_mixer_amp_switch_get, \
	  .put = snd_hda_mixer_amp_switch_put, \
	  .private_value = HDA_COMPOSE_AMP_VAL(nid, channel, xindex, direction) }
/*                               */
#define HDA_CODEC_MUTE_IDX(xname, xcidx, nid, xindex, direction) \
	HDA_CODEC_MUTE_MONO_IDX(xname, xcidx, nid, 3, xindex, direction)
/*                  */
#define HDA_CODEC_MUTE_MONO(xname, nid, channel, xindex, direction) \
	HDA_CODEC_MUTE_MONO_IDX(xname, 0, nid, channel, xindex, direction)
/*                    */
#define HDA_CODEC_MUTE(xname, nid, xindex, direction) \
	HDA_CODEC_MUTE_MONO(xname, nid, 3, xindex, direction)
#ifdef CONFIG_SND_HDA_INPUT_BEEP
/*                                                                        */
#define HDA_CODEC_MUTE_BEEP_MONO_IDX(xname, xcidx, nid, channel, xindex, direction) \
	{ .iface = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xcidx, \
	  .subdevice = HDA_SUBDEV_AMP_FLAG, \
	  .info = snd_hda_mixer_amp_switch_info, \
	  .get = snd_hda_mixer_amp_switch_get_beep, \
	  .put = snd_hda_mixer_amp_switch_put_beep, \
	  .private_value = HDA_COMPOSE_AMP_VAL(nid, channel, xindex, direction) }
#else
/*                                         */
#define HDA_CODEC_MUTE_BEEP_MONO_IDX(xname, xcidx, nid, ch, xidx, dir) \
	HDA_CODEC_MUTE_MONO_IDX(xname, xcidx, nid, ch, xidx, dir)
#endif /*                           */
/*                               */
#define HDA_CODEC_MUTE_BEEP_MONO(xname, nid, channel, xindex, direction) \
	HDA_CODEC_MUTE_BEEP_MONO_IDX(xname, 0, nid, channel, xindex, direction)
/*                                 */
#define HDA_CODEC_MUTE_BEEP(xname, nid, xindex, direction) \
	HDA_CODEC_MUTE_BEEP_MONO(xname, nid, 3, xindex, direction)

extern const char *snd_hda_pcm_type_name[];

int snd_hda_mixer_amp_volume_info(struct snd_kcontrol *kcontrol,
				  struct snd_ctl_elem_info *uinfo);
int snd_hda_mixer_amp_volume_get(struct snd_kcontrol *kcontrol,
				 struct snd_ctl_elem_value *ucontrol);
int snd_hda_mixer_amp_volume_put(struct snd_kcontrol *kcontrol,
				 struct snd_ctl_elem_value *ucontrol);
int snd_hda_mixer_amp_tlv(struct snd_kcontrol *kcontrol, int op_flag,
			  unsigned int size, unsigned int __user *tlv);
int snd_hda_mixer_amp_switch_info(struct snd_kcontrol *kcontrol,
				  struct snd_ctl_elem_info *uinfo);
int snd_hda_mixer_amp_switch_get(struct snd_kcontrol *kcontrol,
				 struct snd_ctl_elem_value *ucontrol);
int snd_hda_mixer_amp_switch_put(struct snd_kcontrol *kcontrol,
				 struct snd_ctl_elem_value *ucontrol);
#ifdef CONFIG_SND_HDA_INPUT_BEEP
int snd_hda_mixer_amp_switch_get_beep(struct snd_kcontrol *kcontrol,
				      struct snd_ctl_elem_value *ucontrol);
int snd_hda_mixer_amp_switch_put_beep(struct snd_kcontrol *kcontrol,
				      struct snd_ctl_elem_value *ucontrol);
#endif
/*                                               */
int snd_hda_codec_amp_read(struct hda_codec *codec, hda_nid_t nid, int ch,
			   int direction, int index);
int snd_hda_codec_amp_update(struct hda_codec *codec, hda_nid_t nid, int ch,
			     int direction, int idx, int mask, int val);
int snd_hda_codec_amp_stereo(struct hda_codec *codec, hda_nid_t nid,
			     int dir, int idx, int mask, int val);
int snd_hda_codec_amp_init(struct hda_codec *codec, hda_nid_t nid, int ch,
			   int direction, int idx, int mask, int val);
int snd_hda_codec_amp_init_stereo(struct hda_codec *codec, hda_nid_t nid,
				  int dir, int idx, int mask, int val);
void snd_hda_codec_resume_amp(struct hda_codec *codec);

void snd_hda_set_vmaster_tlv(struct hda_codec *codec, hda_nid_t nid, int dir,
			     unsigned int *tlv);
struct snd_kcontrol *snd_hda_find_mixer_ctl(struct hda_codec *codec,
					    const char *name);
int __snd_hda_add_vmaster(struct hda_codec *codec, char *name,
			  unsigned int *tlv, const char * const *slaves,
			  const char *suffix, bool init_slave_vol,
			  struct snd_kcontrol **ctl_ret);
#define snd_hda_add_vmaster(codec, name, tlv, slaves, suffix) \
	__snd_hda_add_vmaster(codec, name, tlv, slaves, suffix, true, NULL)
int snd_hda_codec_reset(struct hda_codec *codec);

enum {
	HDA_VMUTE_OFF,
	HDA_VMUTE_ON,
	HDA_VMUTE_FOLLOW_MASTER,
};

struct hda_vmaster_mute_hook {
	/*                                                 
                                         
  */
	struct snd_kcontrol *sw_kctl;
	void (*hook)(void *, int);
	/*                                     */
	unsigned int mute_mode; /*               */
	struct hda_codec *codec;
};

int snd_hda_add_vmaster_hook(struct hda_codec *codec,
			     struct hda_vmaster_mute_hook *hook,
			     bool expose_enum_ctl);
void snd_hda_sync_vmaster_hook(struct hda_vmaster_mute_hook *hook);

/*                */
#define HDA_AMP_MUTE	0x80
#define HDA_AMP_UNMUTE	0x00
#define HDA_AMP_VOLMASK	0x7f

/*                                     */
#define HDA_BIND_MUTE_MONO(xname, nid, channel, indices, direction) \
	{ .iface = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = 0,  \
	  .info = snd_hda_mixer_amp_switch_info, \
	  .get = snd_hda_mixer_bind_switch_get, \
	  .put = snd_hda_mixer_bind_switch_put, \
	  .private_value = HDA_COMPOSE_AMP_VAL(nid, channel, indices, direction) }

/*                                       */
#define HDA_BIND_MUTE(xname,nid,indices,dir) \
	HDA_BIND_MUTE_MONO(xname,nid,3,indices,dir)

int snd_hda_mixer_bind_switch_get(struct snd_kcontrol *kcontrol,
				  struct snd_ctl_elem_value *ucontrol);
int snd_hda_mixer_bind_switch_put(struct snd_kcontrol *kcontrol,
				  struct snd_ctl_elem_value *ucontrol);

/*                             */
struct hda_ctl_ops {
	snd_kcontrol_info_t *info;
	snd_kcontrol_get_t *get;
	snd_kcontrol_put_t *put;
	snd_kcontrol_tlv_rw_t *tlv;
};

extern struct hda_ctl_ops snd_hda_bind_vol;	/*                          */
extern struct hda_ctl_ops snd_hda_bind_sw;	/*                 */

struct hda_bind_ctls {
	struct hda_ctl_ops *ops;
	unsigned long values[];
};

int snd_hda_mixer_bind_ctls_info(struct snd_kcontrol *kcontrol,
				 struct snd_ctl_elem_info *uinfo);
int snd_hda_mixer_bind_ctls_get(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol);
int snd_hda_mixer_bind_ctls_put(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol);
int snd_hda_mixer_bind_tlv(struct snd_kcontrol *kcontrol, int op_flag,
			   unsigned int size, unsigned int __user *tlv);

#define HDA_BIND_VOL(xname, bindrec) \
	{ .iface = SNDRV_CTL_ELEM_IFACE_MIXER, \
	  .name = xname, \
	  .access = SNDRV_CTL_ELEM_ACCESS_READWRITE |\
			  SNDRV_CTL_ELEM_ACCESS_TLV_READ |\
			  SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK,\
	  .info = snd_hda_mixer_bind_ctls_info,\
	  .get =  snd_hda_mixer_bind_ctls_get,\
	  .put = snd_hda_mixer_bind_ctls_put,\
	  .tlv = { .c = snd_hda_mixer_bind_tlv },\
	  .private_value = (long) (bindrec) }
#define HDA_BIND_SW(xname, bindrec) \
	{ .iface = SNDRV_CTL_ELEM_IFACE_MIXER,\
	  .name = xname, \
	  .info = snd_hda_mixer_bind_ctls_info,\
	  .get =  snd_hda_mixer_bind_ctls_get,\
	  .put = snd_hda_mixer_bind_ctls_put,\
	  .private_value = (long) (bindrec) }

/*
            
 */
int snd_hda_create_dig_out_ctls(struct hda_codec *codec,
				hda_nid_t associated_nid,
				hda_nid_t cvt_nid, int type);
#define snd_hda_create_spdif_out_ctls(codec, anid, cnid) \
	snd_hda_create_dig_out_ctls(codec, anid, cnid, HDA_PCM_TYPE_SPDIF)
int snd_hda_create_spdif_in_ctls(struct hda_codec *codec, hda_nid_t nid);

/*
                   
 */
#define HDA_MAX_NUM_INPUTS	16
struct hda_input_mux_item {
	char label[32];
	unsigned int index;
};
struct hda_input_mux {
	unsigned int num_items;
	struct hda_input_mux_item items[HDA_MAX_NUM_INPUTS];
};

int snd_hda_input_mux_info(const struct hda_input_mux *imux,
			   struct snd_ctl_elem_info *uinfo);
int snd_hda_input_mux_put(struct hda_codec *codec,
			  const struct hda_input_mux *imux,
			  struct snd_ctl_elem_value *ucontrol, hda_nid_t nid,
			  unsigned int *cur_val);
int snd_hda_add_imux_item(struct hda_input_mux *imux, const char *label,
			  int index, int *type_index_ret);

/*
                      
 */
struct hda_channel_mode {
	int channels;
	const struct hda_verb *sequence;
};

int snd_hda_ch_mode_info(struct hda_codec *codec,
			 struct snd_ctl_elem_info *uinfo,
			 const struct hda_channel_mode *chmode,
			 int num_chmodes);
int snd_hda_ch_mode_get(struct hda_codec *codec,
			struct snd_ctl_elem_value *ucontrol,
			const struct hda_channel_mode *chmode,
			int num_chmodes,
			int max_channels);
int snd_hda_ch_mode_put(struct hda_codec *codec,
			struct snd_ctl_elem_value *ucontrol,
			const struct hda_channel_mode *chmode,
			int num_chmodes,
			int *max_channelsp);

/*
                                         
 */

enum { HDA_FRONT, HDA_REAR, HDA_CLFE, HDA_SIDE }; /*                    */
enum { HDA_DIG_NONE, HDA_DIG_EXCLUSIVE, HDA_DIG_ANALOG_DUP }; /*              */

#define HDA_MAX_OUTS	5

struct hda_multi_out {
	int num_dacs;		/*                                */
	const hda_nid_t *dac_nids;	/*          */
	hda_nid_t hp_nid;	/*                                        */
	hda_nid_t hp_out_nid[HDA_MAX_OUTS];	/*                       */
	hda_nid_t extra_out_nid[HDA_MAX_OUTS];	/*                           */
	hda_nid_t dig_out_nid;	/*                          */
	const hda_nid_t *slave_dig_outs;
	int max_channels;	/*                                     */
	int dig_out_used;	/*                                            */
	int no_share_stream;	/*                                         */
	int share_spdif;	/*                 */
	/*                                                */
	unsigned int analog_rates;
	unsigned int analog_maxbps;
	u64 analog_formats;
	unsigned int spdif_rates;
	unsigned int spdif_maxbps;
	u64 spdif_formats;
};

int snd_hda_create_spdif_share_sw(struct hda_codec *codec,
				  struct hda_multi_out *mout);
int snd_hda_multi_out_dig_open(struct hda_codec *codec,
			       struct hda_multi_out *mout);
int snd_hda_multi_out_dig_close(struct hda_codec *codec,
				struct hda_multi_out *mout);
int snd_hda_multi_out_dig_prepare(struct hda_codec *codec,
				  struct hda_multi_out *mout,
				  unsigned int stream_tag,
				  unsigned int format,
				  struct snd_pcm_substream *substream);
int snd_hda_multi_out_dig_cleanup(struct hda_codec *codec,
				  struct hda_multi_out *mout);
int snd_hda_multi_out_analog_open(struct hda_codec *codec,
				  struct hda_multi_out *mout,
				  struct snd_pcm_substream *substream,
				  struct hda_pcm_stream *hinfo);
int snd_hda_multi_out_analog_prepare(struct hda_codec *codec,
				     struct hda_multi_out *mout,
				     unsigned int stream_tag,
				     unsigned int format,
				     struct snd_pcm_substream *substream);
int snd_hda_multi_out_analog_cleanup(struct hda_codec *codec,
				     struct hda_multi_out *mout);

/*
                       
 */
#ifdef CONFIG_SND_HDA_GENERIC
int snd_hda_parse_generic_codec(struct hda_codec *codec);
#else
static inline int snd_hda_parse_generic_codec(struct hda_codec *codec)
{
	return -ENODEV;
}
#endif

/*
                         
 */
#ifdef CONFIG_PROC_FS
int snd_hda_codec_proc_new(struct hda_codec *codec);
#else
static inline int snd_hda_codec_proc_new(struct hda_codec *codec) { return 0; }
#endif

#define SND_PRINT_BITS_ADVISED_BUFSIZE	16
void snd_print_pcm_bits(int pcm, char *buf, int buflen);

/*
       
 */
int snd_hda_check_board_config(struct hda_codec *codec, int num_configs,
			       const char * const *modelnames,
			       const struct snd_pci_quirk *pci_list);
int snd_hda_check_board_codec_sid_config(struct hda_codec *codec,
                               int num_configs, const char * const *models,
                               const struct snd_pci_quirk *tbl);
int snd_hda_add_new_ctls(struct hda_codec *codec,
			 const struct snd_kcontrol_new *knew);

/*
                                                          
 */

struct hda_pintbl {
	hda_nid_t nid;
	u32 val;
};

struct hda_model_fixup {
	const int id;
	const char *name;
};

struct hda_fixup {
	int type;
	bool chained:1;		/*                                      */
	bool chained_before:1;	/*                                       */
	int chain_id;
	union {
		const struct hda_pintbl *pins;
		const struct hda_verb *verbs;
		void (*func)(struct hda_codec *codec,
			     const struct hda_fixup *fix,
			     int action);
	} v;
};

/*             */
enum {
	HDA_FIXUP_INVALID,
	HDA_FIXUP_PINS,
	HDA_FIXUP_VERBS,
	HDA_FIXUP_FUNC,
	HDA_FIXUP_PINCTLS,
};

/*                          */
enum {
	HDA_FIXUP_ACT_PRE_PROBE,
	HDA_FIXUP_ACT_PROBE,
	HDA_FIXUP_ACT_INIT,
	HDA_FIXUP_ACT_BUILD,
};

int snd_hda_add_verbs(struct hda_codec *codec, const struct hda_verb *list);
void snd_hda_apply_verbs(struct hda_codec *codec);
void snd_hda_apply_pincfgs(struct hda_codec *codec,
			   const struct hda_pintbl *cfg);
void snd_hda_apply_fixup(struct hda_codec *codec, int action);
void snd_hda_pick_fixup(struct hda_codec *codec,
			const struct hda_model_fixup *models,
			const struct snd_pci_quirk *quirk,
			const struct hda_fixup *fixlist);

/*
                            
 */

#define HDA_UNSOL_QUEUE_SIZE	64

struct hda_bus_unsolicited {
	/*             */
	u32 queue[HDA_UNSOL_QUEUE_SIZE * 2];
	unsigned int rp, wp;

	/*           */
	struct work_struct work;
	struct hda_bus *bus;
};

/*                                                     */
#define get_defcfg_connect(cfg) \
	((cfg & AC_DEFCFG_PORT_CONN) >> AC_DEFCFG_PORT_CONN_SHIFT)
#define get_defcfg_association(cfg) \
	((cfg & AC_DEFCFG_DEF_ASSOC) >> AC_DEFCFG_ASSOC_SHIFT)
#define get_defcfg_location(cfg) \
	((cfg & AC_DEFCFG_LOCATION) >> AC_DEFCFG_LOCATION_SHIFT)
#define get_defcfg_sequence(cfg) \
	(cfg & AC_DEFCFG_SEQUENCE)
#define get_defcfg_device(cfg) \
	((cfg & AC_DEFCFG_DEVICE) >> AC_DEFCFG_DEVICE_SHIFT)
#define get_defcfg_misc(cfg) \
	((cfg & AC_DEFCFG_MISC) >> AC_DEFCFG_MISC_SHIFT)

/*            */
#define AMP_IN_MUTE(idx)	(0x7080 | ((idx)<<8))
#define AMP_IN_UNMUTE(idx)	(0x7000 | ((idx)<<8))
#define AMP_OUT_MUTE		0xb080
#define AMP_OUT_UNMUTE		0xb000
#define AMP_OUT_ZERO		0xb000
/*               */
#define PIN_IN			(AC_PINCTL_IN_EN)
#define PIN_VREFHIZ		(AC_PINCTL_IN_EN | AC_PINCTL_VREF_HIZ)
#define PIN_VREF50		(AC_PINCTL_IN_EN | AC_PINCTL_VREF_50)
#define PIN_VREFGRD		(AC_PINCTL_IN_EN | AC_PINCTL_VREF_GRD)
#define PIN_VREF80		(AC_PINCTL_IN_EN | AC_PINCTL_VREF_80)
#define PIN_VREF100		(AC_PINCTL_IN_EN | AC_PINCTL_VREF_100)
#define PIN_OUT			(AC_PINCTL_OUT_EN)
#define PIN_HP			(AC_PINCTL_OUT_EN | AC_PINCTL_HP_EN)
#define PIN_HP_AMP		(AC_PINCTL_HP_EN)

unsigned int snd_hda_get_default_vref(struct hda_codec *codec, hda_nid_t pin);
unsigned int snd_hda_correct_pin_ctl(struct hda_codec *codec,
				     hda_nid_t pin, unsigned int val);
int _snd_hda_set_pin_ctl(struct hda_codec *codec, hda_nid_t pin,
			 unsigned int val, bool cached);

/* 
                                                        
                             
                                       
                                                 
  
                                                                 
                                                                    
                                                                       
                                              
  
                                                                     
                                                           
                                                                  
 */
static inline int
snd_hda_set_pin_ctl(struct hda_codec *codec, hda_nid_t pin, unsigned int val)
{
	return _snd_hda_set_pin_ctl(codec, pin, val, false);
}

/* 
                                                             
                             
                                       
                                                 
  
                                                              
 */
static inline int
snd_hda_set_pin_ctl_cache(struct hda_codec *codec, hda_nid_t pin,
			  unsigned int val)
{
	return _snd_hda_set_pin_ctl(codec, pin, val, true);
}

int snd_hda_codec_get_pin_target(struct hda_codec *codec, hda_nid_t nid);
int snd_hda_codec_set_pin_target(struct hda_codec *codec, hda_nid_t nid,
				 unsigned int val);

/*
                          
 */
static inline u32 get_wcaps(struct hda_codec *codec, hda_nid_t nid)
{
	if (nid < codec->start_nid ||
	    nid >= codec->start_nid + codec->num_nodes)
		return 0;
	return codec->wcaps[nid - codec->start_nid];
}

/*                                                 */
static inline int get_wcaps_type(unsigned int wcaps)
{
	if (!wcaps)
		return -1; /*              */
	return (wcaps & AC_WCAP_TYPE) >> AC_WCAP_TYPE_SHIFT;
}

static inline unsigned int get_wcaps_channels(u32 wcaps)
{
	unsigned int chans;

	chans = (wcaps & AC_WCAP_CHAN_CNT_EXT) >> 13;
	chans = ((chans << 1) | 1) + 1;

	return chans;
}

static inline void snd_hda_override_wcaps(struct hda_codec *codec,
					  hda_nid_t nid, u32 val)
{
	if (nid >= codec->start_nid &&
	    nid < codec->start_nid + codec->num_nodes)
		codec->wcaps[nid - codec->start_nid] = val;
}

u32 query_amp_caps(struct hda_codec *codec, hda_nid_t nid, int direction);
int snd_hda_override_amp_caps(struct hda_codec *codec, hda_nid_t nid, int dir,
			      unsigned int caps);
u32 snd_hda_query_pin_caps(struct hda_codec *codec, hda_nid_t nid);
int snd_hda_override_pin_caps(struct hda_codec *codec, hda_nid_t nid,
			      unsigned int caps);

/*                        */
#define HDA_NID_ITEM_AMP	(1<<0)

struct hda_nid_item {
	struct snd_kcontrol *kctl;
	unsigned int index;
	hda_nid_t nid;
	unsigned short flags;
};

int snd_hda_ctl_add(struct hda_codec *codec, hda_nid_t nid,
		    struct snd_kcontrol *kctl);
int snd_hda_add_nid(struct hda_codec *codec, struct snd_kcontrol *kctl,
		    unsigned int index, hda_nid_t nid);
void snd_hda_ctls_clear(struct hda_codec *codec);

/*
                  
 */
#ifdef CONFIG_SND_HDA_HWDEP
int snd_hda_create_hwdep(struct hda_codec *codec);
#else
static inline int snd_hda_create_hwdep(struct hda_codec *codec) { return 0; }
#endif

#if defined(CONFIG_PM) && defined(CONFIG_SND_HDA_HWDEP)
int snd_hda_hwdep_add_power_sysfs(struct hda_codec *codec);
#else
static inline int snd_hda_hwdep_add_power_sysfs(struct hda_codec *codec)
{
	return 0;
}
#endif

#ifdef CONFIG_SND_HDA_RECONFIG
int snd_hda_hwdep_add_sysfs(struct hda_codec *codec);
#else
static inline int snd_hda_hwdep_add_sysfs(struct hda_codec *codec)
{
	return 0;
}
#endif

#ifdef CONFIG_SND_HDA_RECONFIG
const char *snd_hda_get_hint(struct hda_codec *codec, const char *key);
int snd_hda_get_bool_hint(struct hda_codec *codec, const char *key);
int snd_hda_get_int_hint(struct hda_codec *codec, const char *key, int *valp);
#else
static inline
const char *snd_hda_get_hint(struct hda_codec *codec, const char *key)
{
	return NULL;
}

static inline
int snd_hda_get_bool_hint(struct hda_codec *codec, const char *key)
{
	return -ENOENT;
}

static inline
int snd_hda_get_int_hint(struct hda_codec *codec, const char *key, int *valp)
{
	return -ENOENT;
}
#endif

/*
                   
 */

void snd_hda_schedule_power_save(struct hda_codec *codec);

struct hda_amp_list {
	hda_nid_t nid;
	unsigned char dir;
	unsigned char idx;
};

struct hda_loopback_check {
	const struct hda_amp_list *amplist;
	int power_on;
};

int snd_hda_check_amp_list_power(struct hda_codec *codec,
				 struct hda_loopback_check *check,
				 hda_nid_t nid);

/*                                                                    */
static inline bool
snd_hda_check_power_state(struct hda_codec *codec, hda_nid_t nid,
			  unsigned int target_state)
{
	unsigned int state = snd_hda_codec_read(codec, nid, 0,
						AC_VERB_GET_POWER_STATE, 0);
	if (state & AC_PWRST_ERROR)
		return true;
	state = (state >> 4) & 0x0f;
	return (state == target_state);
}

unsigned int snd_hda_codec_eapd_power_filter(struct hda_codec *codec,
					     hda_nid_t nid,
					     unsigned int power_state);

/*
                        
 */
/*                                        */
#define get_amp_nid_(pv)	((pv) & 0xffff)
#define get_amp_nid(kc)		get_amp_nid_((kc)->private_value)
#define get_amp_channels(kc)	(((kc)->private_value >> 16) & 0x3)
#define get_amp_direction_(pv)	(((pv) >> 18) & 0x1)
#define get_amp_direction(kc)	get_amp_direction_((kc)->private_value)
#define get_amp_index_(pv)	(((pv) >> 19) & 0xf)
#define get_amp_index(kc)	get_amp_index_((kc)->private_value)
#define get_amp_offset(kc)	(((kc)->private_value >> 23) & 0x3f)
#define get_amp_min_mute(kc)	(((kc)->private_value >> 29) & 0x1)

/*
                      
 */
int snd_hda_enum_helper_info(struct snd_kcontrol *kcontrol,
			     struct snd_ctl_elem_info *uinfo,
			     int num_entries, const char * const *texts);
#define snd_hda_enum_bool_helper_info(kcontrol, uinfo) \
	snd_hda_enum_helper_info(kcontrol, uinfo, 0, NULL)

/*
                                  
 */
struct cea_sad {
	int	channels;
	int	format;		/*                                     */
	int	rates;
	int	sample_bits;	/*          */
	int	max_bitrate;	/*                 */
	int	profile;	/*            */
};

#define ELD_FIXED_BYTES	20
#define ELD_MAX_SIZE    256
#define ELD_MAX_MNL	16
#define ELD_MAX_SAD	16

/*
                      
 */
struct parsed_hdmi_eld {
	/*
                                                  
  */
	int	baseline_len;
	int	eld_ver;
	int	cea_edid_ver;
	char	monitor_name[ELD_MAX_MNL + 1];
	int	manufacture_id;
	int	product_id;
	u64	port_id;
	int	support_hdcp;
	int	support_ai;
	int	conn_type;
	int	aud_synch_delay;
	int	spk_alloc;
	int	sad_count;
	struct cea_sad sad[ELD_MAX_SAD];
};

struct hdmi_eld {
	bool	monitor_present;
	bool	eld_valid;
	int	eld_size;
	char    eld_buffer[ELD_MAX_SIZE];
	struct parsed_hdmi_eld info;
	struct mutex lock;
#ifdef CONFIG_PROC_FS
	struct snd_info_entry *proc_entry;
#endif
};

int snd_hdmi_get_eld_size(struct hda_codec *codec, hda_nid_t nid);
int snd_hdmi_get_eld(struct hda_codec *codec, hda_nid_t nid,
		     unsigned char *buf, int *eld_size);
int snd_hdmi_parse_eld(struct parsed_hdmi_eld *e,
		       const unsigned char *buf, int size);
void snd_hdmi_show_eld(struct parsed_hdmi_eld *e);
void snd_hdmi_eld_update_pcm_info(struct parsed_hdmi_eld *e,
			      struct hda_pcm_stream *hinfo);

#ifdef CONFIG_PROC_FS
int snd_hda_eld_proc_new(struct hda_codec *codec, struct hdmi_eld *eld,
			 int index);
void snd_hda_eld_proc_free(struct hda_codec *codec, struct hdmi_eld *eld);
#else
static inline int snd_hda_eld_proc_new(struct hda_codec *codec,
				       struct hdmi_eld *eld,
				       int index)
{
	return 0;
}
static inline void snd_hda_eld_proc_free(struct hda_codec *codec,
					 struct hdmi_eld *eld)
{
}
#endif

#define SND_PRINT_CHANNEL_ALLOCATION_ADVISED_BUFSIZE 80
void snd_print_channel_allocation(int spk_alloc, char *buf, int buflen);

#endif /*                     */
