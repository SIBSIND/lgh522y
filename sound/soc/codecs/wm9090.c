/*
 * ALSA SoC WM9090 driver
 *
 * Copyright 2009-12 Wolfson Microelectronics
 *
 * Author: Mark Brown <broonie@opensource.wolfsonmicro.com>
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
 */

#include <linux/module.h>
#include <linux/errno.h>
#include <linux/device.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/regmap.h>
#include <linux/slab.h>
#include <sound/initval.h>
#include <sound/soc.h>
#include <sound/tlv.h>
#include <sound/wm9090.h>

#include "wm9090.h"

static const struct reg_default wm9090_reg_defaults[] = {
	{ 1,  0x0006 },     /*                             */
	{ 2,  0x6000 },     /*                             */
	{ 3,  0x0000 },     /*                             */
	{ 6,  0x01C0 },     /*                   */
	{ 22, 0x0003 },     /*                         */
	{ 23, 0x0003 },     /*                         */
	{ 24, 0x0083 },     /*                                */
	{ 25, 0x0083 },     /*                                 */
	{ 26, 0x0083 },     /*                                */
	{ 27, 0x0083 },     /*                                */
	{ 28, 0x002D },     /*                           */
	{ 29, 0x002D },     /*                            */
	{ 34, 0x0100 },     /*                            */
	{ 35, 0x0010 },     /*                      */
	{ 37, 0x0140 },     /*                */
	{ 38, 0x0039 },     /*                            */
	{ 45, 0x0000 },     /*                      */
	{ 46, 0x0000 },     /*                      */
	{ 47, 0x0100 },     /*                      */
	{ 48, 0x0100 },     /*                      */
	{ 54, 0x0000 },     /*                      */
	{ 57, 0x000D },     /*                 */
	{ 70, 0x0000 },     /*                          */
	{ 71, 0x0000 },     /*                          */
	{ 72, 0x0000 },     /*                          */
	{ 73, 0x0000 },     /*                          */
	{ 74, 0x0000 },     /*                          */
	{ 75, 0x0000 },     /*                          */
	{ 76, 0x1F25 },     /*                      */
	{ 85, 0x054A },     /*                   */
	{ 87, 0x0000 },     /*                   */
	{ 96, 0x0100 },     /*                      */
	{ 98, 0x8640 },     /*                      */
	{ 99, 0xC000 },     /*                      */
	{ 100, 0x0200 },     /*                      */
};

/*                                         */
struct wm9090_priv {
	struct wm9090_platform_data pdata;
	struct regmap *regmap;
};

static bool wm9090_volatile(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case WM9090_SOFTWARE_RESET:
	case WM9090_DC_SERVO_0:
	case WM9090_DC_SERVO_READBACK_0:
	case WM9090_DC_SERVO_READBACK_1:
	case WM9090_DC_SERVO_READBACK_2:
		return true;

	default:
		return false;
	}
}

static bool wm9090_readable(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case WM9090_SOFTWARE_RESET:
	case WM9090_POWER_MANAGEMENT_1:
	case WM9090_POWER_MANAGEMENT_2:
	case WM9090_POWER_MANAGEMENT_3:
	case WM9090_CLOCKING_1:
	case WM9090_IN1_LINE_CONTROL:
	case WM9090_IN2_LINE_CONTROL:
	case WM9090_IN1_LINE_INPUT_A_VOLUME:
	case WM9090_IN1_LINE_INPUT_B_VOLUME:
	case WM9090_IN2_LINE_INPUT_A_VOLUME:
	case WM9090_IN2_LINE_INPUT_B_VOLUME:
	case WM9090_LEFT_OUTPUT_VOLUME:
	case WM9090_RIGHT_OUTPUT_VOLUME:
	case WM9090_SPKMIXL_ATTENUATION:
	case WM9090_SPKOUT_MIXERS:
	case WM9090_CLASSD3:
	case WM9090_SPEAKER_VOLUME_LEFT:
	case WM9090_OUTPUT_MIXER1:
	case WM9090_OUTPUT_MIXER2:
	case WM9090_OUTPUT_MIXER3:
	case WM9090_OUTPUT_MIXER4:
	case WM9090_SPEAKER_MIXER:
	case WM9090_ANTIPOP2:
	case WM9090_WRITE_SEQUENCER_0:
	case WM9090_WRITE_SEQUENCER_1:
	case WM9090_WRITE_SEQUENCER_2:
	case WM9090_WRITE_SEQUENCER_3:
	case WM9090_WRITE_SEQUENCER_4:
	case WM9090_WRITE_SEQUENCER_5:
	case WM9090_CHARGE_PUMP_1:
	case WM9090_DC_SERVO_0:
	case WM9090_DC_SERVO_1:
	case WM9090_DC_SERVO_3:
	case WM9090_DC_SERVO_READBACK_0:
	case WM9090_DC_SERVO_READBACK_1:
	case WM9090_DC_SERVO_READBACK_2:
	case WM9090_ANALOGUE_HP_0:
	case WM9090_AGC_CONTROL_0:
	case WM9090_AGC_CONTROL_1:
	case WM9090_AGC_CONTROL_2:
		return true;

	default:
		return false;
	}
}

static void wait_for_dc_servo(struct snd_soc_codec *codec)
{
	unsigned int reg;
	int count = 0;

	dev_dbg(codec->dev, "Waiting for DC servo...\n");
	do {
		count++;
		msleep(1);
		reg = snd_soc_read(codec, WM9090_DC_SERVO_READBACK_0);
		dev_dbg(codec->dev, "DC servo status: %x\n", reg);
	} while ((reg & WM9090_DCS_CAL_COMPLETE_MASK)
		 != WM9090_DCS_CAL_COMPLETE_MASK && count < 1000);

	if ((reg & WM9090_DCS_CAL_COMPLETE_MASK)
	    != WM9090_DCS_CAL_COMPLETE_MASK)
		dev_err(codec->dev, "Timed out waiting for DC Servo\n");
}

static const unsigned int in_tlv[] = {
	TLV_DB_RANGE_HEAD(3),
	0, 0, TLV_DB_SCALE_ITEM(-600, 0, 0),
	1, 3, TLV_DB_SCALE_ITEM(-350, 350, 0),
	4, 6, TLV_DB_SCALE_ITEM(600, 600, 0),
};
static const unsigned int mix_tlv[] = {
	TLV_DB_RANGE_HEAD(2),
	0, 2, TLV_DB_SCALE_ITEM(-1200, 300, 0),
	3, 3, TLV_DB_SCALE_ITEM(0, 0, 0),
};
static const DECLARE_TLV_DB_SCALE(out_tlv, -5700, 100, 0);
static const unsigned int spkboost_tlv[] = {
	TLV_DB_RANGE_HEAD(2),
	0, 6, TLV_DB_SCALE_ITEM(0, 150, 0),
	7, 7, TLV_DB_SCALE_ITEM(1200, 0, 0),
};

static const struct snd_kcontrol_new wm9090_controls[] = {
SOC_SINGLE_TLV("IN1A Volume", WM9090_IN1_LINE_INPUT_A_VOLUME, 0, 6, 0,
	       in_tlv),
SOC_SINGLE("IN1A Switch", WM9090_IN1_LINE_INPUT_A_VOLUME, 7, 1, 1),
SOC_SINGLE("IN1A ZC Switch", WM9090_IN1_LINE_INPUT_A_VOLUME, 6, 1, 0),

SOC_SINGLE_TLV("IN2A Volume", WM9090_IN2_LINE_INPUT_A_VOLUME, 0, 6, 0,
	       in_tlv),
SOC_SINGLE("IN2A Switch", WM9090_IN2_LINE_INPUT_A_VOLUME, 7, 1, 1),
SOC_SINGLE("IN2A ZC Switch", WM9090_IN2_LINE_INPUT_A_VOLUME, 6, 1, 0),

SOC_SINGLE("MIXOUTL Switch", WM9090_OUTPUT_MIXER3, 8, 1, 1),
SOC_SINGLE_TLV("MIXOUTL IN1A Volume", WM9090_OUTPUT_MIXER3, 6, 3, 1,
	       mix_tlv),
SOC_SINGLE_TLV("MIXOUTL IN2A Volume", WM9090_OUTPUT_MIXER3, 2, 3, 1,
	       mix_tlv),

SOC_SINGLE("MIXOUTR Switch", WM9090_OUTPUT_MIXER4, 8, 1, 1),
SOC_SINGLE_TLV("MIXOUTR IN1A Volume", WM9090_OUTPUT_MIXER4, 6, 3, 1,
	       mix_tlv),
SOC_SINGLE_TLV("MIXOUTR IN2A Volume", WM9090_OUTPUT_MIXER4, 2, 3, 1,
	       mix_tlv),

SOC_SINGLE("SPKMIX Switch", WM9090_SPKMIXL_ATTENUATION, 8, 1, 1),
SOC_SINGLE_TLV("SPKMIX IN1A Volume", WM9090_SPKMIXL_ATTENUATION, 6, 3, 1,
	       mix_tlv),
SOC_SINGLE_TLV("SPKMIX IN2A Volume", WM9090_SPKMIXL_ATTENUATION, 2, 3, 1,
	       mix_tlv),

SOC_DOUBLE_R_TLV("Headphone Volume", WM9090_LEFT_OUTPUT_VOLUME,
		 WM9090_RIGHT_OUTPUT_VOLUME, 0, 63, 0, out_tlv),
SOC_DOUBLE_R("Headphone Switch", WM9090_LEFT_OUTPUT_VOLUME,
	     WM9090_RIGHT_OUTPUT_VOLUME, 6, 1, 1),
SOC_DOUBLE_R("Headphone ZC Switch", WM9090_LEFT_OUTPUT_VOLUME,
	     WM9090_RIGHT_OUTPUT_VOLUME, 7, 1, 0),

SOC_SINGLE_TLV("Speaker Volume", WM9090_SPEAKER_VOLUME_LEFT, 0, 63, 0,
	       out_tlv),
SOC_SINGLE("Speaker Switch", WM9090_SPEAKER_VOLUME_LEFT, 6, 1, 1),
SOC_SINGLE("Speaker ZC Switch", WM9090_SPEAKER_VOLUME_LEFT, 7, 1, 0),
SOC_SINGLE_TLV("Speaker Boost Volume", WM9090_CLASSD3, 3, 7, 0, spkboost_tlv),
};

static const struct snd_kcontrol_new wm9090_in1_se_controls[] = {
SOC_SINGLE_TLV("IN1B Volume", WM9090_IN1_LINE_INPUT_B_VOLUME, 0, 6, 0,
	       in_tlv),
SOC_SINGLE("IN1B Switch", WM9090_IN1_LINE_INPUT_B_VOLUME, 7, 1, 1),
SOC_SINGLE("IN1B ZC Switch", WM9090_IN1_LINE_INPUT_B_VOLUME, 6, 1, 0),

SOC_SINGLE_TLV("SPKMIX IN1B Volume", WM9090_SPKMIXL_ATTENUATION, 4, 3, 1,
	       mix_tlv),
SOC_SINGLE_TLV("MIXOUTL IN1B Volume", WM9090_OUTPUT_MIXER3, 4, 3, 1,
	       mix_tlv),
SOC_SINGLE_TLV("MIXOUTR IN1B Volume", WM9090_OUTPUT_MIXER4, 4, 3, 1,
	       mix_tlv),
};

static const struct snd_kcontrol_new wm9090_in2_se_controls[] = {
SOC_SINGLE_TLV("IN2B Volume", WM9090_IN2_LINE_INPUT_B_VOLUME, 0, 6, 0,
	       in_tlv),
SOC_SINGLE("IN2B Switch", WM9090_IN2_LINE_INPUT_B_VOLUME, 7, 1, 1),
SOC_SINGLE("IN2B ZC Switch", WM9090_IN2_LINE_INPUT_B_VOLUME, 6, 1, 0),

SOC_SINGLE_TLV("SPKMIX IN2B Volume", WM9090_SPKMIXL_ATTENUATION, 0, 3, 1,
	       mix_tlv),
SOC_SINGLE_TLV("MIXOUTL IN2B Volume", WM9090_OUTPUT_MIXER3, 0, 3, 1,
	       mix_tlv),
SOC_SINGLE_TLV("MIXOUTR IN2B Volume", WM9090_OUTPUT_MIXER4, 0, 3, 1,
	       mix_tlv),
};

static int hp_ev(struct snd_soc_dapm_widget *w,
		 struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;
	unsigned int reg = snd_soc_read(codec, WM9090_ANALOGUE_HP_0);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		snd_soc_update_bits(codec, WM9090_CHARGE_PUMP_1,
				    WM9090_CP_ENA, WM9090_CP_ENA);

		msleep(5);

		snd_soc_update_bits(codec, WM9090_POWER_MANAGEMENT_1,
				    WM9090_HPOUT1L_ENA | WM9090_HPOUT1R_ENA,
				    WM9090_HPOUT1L_ENA | WM9090_HPOUT1R_ENA);

		reg |= WM9090_HPOUT1L_DLY | WM9090_HPOUT1R_DLY;
		snd_soc_write(codec, WM9090_ANALOGUE_HP_0, reg);

		/*                                                
                                                       
                                                      
                                                        
              
   */
		snd_soc_write(codec, WM9090_DC_SERVO_0,
			      WM9090_DCS_ENA_CHAN_0 |
			      WM9090_DCS_ENA_CHAN_1 |
			      WM9090_DCS_TRIG_STARTUP_1 |
			      WM9090_DCS_TRIG_STARTUP_0);
		wait_for_dc_servo(codec);

		reg |= WM9090_HPOUT1R_OUTP | WM9090_HPOUT1R_RMV_SHORT |
			WM9090_HPOUT1L_OUTP | WM9090_HPOUT1L_RMV_SHORT;
		snd_soc_write(codec, WM9090_ANALOGUE_HP_0, reg);
		break;

	case SND_SOC_DAPM_PRE_PMD:
		reg &= ~(WM9090_HPOUT1L_RMV_SHORT |
			 WM9090_HPOUT1L_DLY |
			 WM9090_HPOUT1L_OUTP |
			 WM9090_HPOUT1R_RMV_SHORT |
			 WM9090_HPOUT1R_DLY |
			 WM9090_HPOUT1R_OUTP);

		snd_soc_write(codec, WM9090_ANALOGUE_HP_0, reg);

		snd_soc_write(codec, WM9090_DC_SERVO_0, 0);

		snd_soc_update_bits(codec, WM9090_POWER_MANAGEMENT_1,
				    WM9090_HPOUT1L_ENA | WM9090_HPOUT1R_ENA,
				    0);

		snd_soc_update_bits(codec, WM9090_CHARGE_PUMP_1,
				    WM9090_CP_ENA, 0);
		break;
	}

	return 0;
}

static const struct snd_kcontrol_new spkmix[] = {
SOC_DAPM_SINGLE("IN1A Switch", WM9090_SPEAKER_MIXER, 6, 1, 0),
SOC_DAPM_SINGLE("IN1B Switch", WM9090_SPEAKER_MIXER, 4, 1, 0),
SOC_DAPM_SINGLE("IN2A Switch", WM9090_SPEAKER_MIXER, 2, 1, 0),
SOC_DAPM_SINGLE("IN2B Switch", WM9090_SPEAKER_MIXER, 0, 1, 0),
};

static const struct snd_kcontrol_new spkout[] = {
SOC_DAPM_SINGLE("Mixer Switch", WM9090_SPKOUT_MIXERS, 4, 1, 0),
};

static const struct snd_kcontrol_new mixoutl[] = {
SOC_DAPM_SINGLE("IN1A Switch", WM9090_OUTPUT_MIXER1, 6, 1, 0),
SOC_DAPM_SINGLE("IN1B Switch", WM9090_OUTPUT_MIXER1, 4, 1, 0),
SOC_DAPM_SINGLE("IN2A Switch", WM9090_OUTPUT_MIXER1, 2, 1, 0),
SOC_DAPM_SINGLE("IN2B Switch", WM9090_OUTPUT_MIXER1, 0, 1, 0),
};

static const struct snd_kcontrol_new mixoutr[] = {
SOC_DAPM_SINGLE("IN1A Switch", WM9090_OUTPUT_MIXER2, 6, 1, 0),
SOC_DAPM_SINGLE("IN1B Switch", WM9090_OUTPUT_MIXER2, 4, 1, 0),
SOC_DAPM_SINGLE("IN2A Switch", WM9090_OUTPUT_MIXER2, 2, 1, 0),
SOC_DAPM_SINGLE("IN2B Switch", WM9090_OUTPUT_MIXER2, 0, 1, 0),
};

static const struct snd_soc_dapm_widget wm9090_dapm_widgets[] = {
SND_SOC_DAPM_INPUT("IN1+"),
SND_SOC_DAPM_INPUT("IN1-"),
SND_SOC_DAPM_INPUT("IN2+"),
SND_SOC_DAPM_INPUT("IN2-"),

SND_SOC_DAPM_SUPPLY("OSC", WM9090_POWER_MANAGEMENT_1, 3, 0, NULL, 0),

SND_SOC_DAPM_PGA("IN1A PGA", WM9090_POWER_MANAGEMENT_2, 7, 0, NULL, 0),
SND_SOC_DAPM_PGA("IN1B PGA", WM9090_POWER_MANAGEMENT_2, 6, 0, NULL, 0),
SND_SOC_DAPM_PGA("IN2A PGA", WM9090_POWER_MANAGEMENT_2, 5, 0, NULL, 0),
SND_SOC_DAPM_PGA("IN2B PGA", WM9090_POWER_MANAGEMENT_2, 4, 0, NULL, 0),

SND_SOC_DAPM_MIXER("SPKMIX", WM9090_POWER_MANAGEMENT_3, 3, 0,
		   spkmix, ARRAY_SIZE(spkmix)),
SND_SOC_DAPM_MIXER("MIXOUTL", WM9090_POWER_MANAGEMENT_3, 5, 0,
		   mixoutl, ARRAY_SIZE(mixoutl)),
SND_SOC_DAPM_MIXER("MIXOUTR", WM9090_POWER_MANAGEMENT_3, 4, 0,
		   mixoutr, ARRAY_SIZE(mixoutr)),

SND_SOC_DAPM_PGA_E("HP PGA", SND_SOC_NOPM, 0, 0, NULL, 0,
		   hp_ev, SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),

SND_SOC_DAPM_PGA("SPKPGA", WM9090_POWER_MANAGEMENT_3, 8, 0, NULL, 0),
SND_SOC_DAPM_MIXER("SPKOUT", WM9090_POWER_MANAGEMENT_1, 12, 0,
		   spkout, ARRAY_SIZE(spkout)),

SND_SOC_DAPM_OUTPUT("HPR"),
SND_SOC_DAPM_OUTPUT("HPL"),
SND_SOC_DAPM_OUTPUT("Speaker"),
};

static const struct snd_soc_dapm_route audio_map[] = {
	{ "IN1A PGA", NULL, "IN1+" },
	{ "IN2A PGA", NULL, "IN2+" },

	{ "SPKMIX", "IN1A Switch", "IN1A PGA" },
	{ "SPKMIX", "IN2A Switch", "IN2A PGA" },

	{ "MIXOUTL", "IN1A Switch", "IN1A PGA" },
	{ "MIXOUTL", "IN2A Switch", "IN2A PGA" },

	{ "MIXOUTR", "IN1A Switch", "IN1A PGA" },
	{ "MIXOUTR", "IN2A Switch", "IN2A PGA" },

	{ "HP PGA", NULL, "OSC" },
	{ "HP PGA", NULL, "MIXOUTL" },
	{ "HP PGA", NULL, "MIXOUTR" },

	{ "HPL", NULL, "HP PGA" },
	{ "HPR", NULL, "HP PGA" },

	{ "SPKPGA", NULL, "OSC" },
	{ "SPKPGA", NULL, "SPKMIX" },

	{ "SPKOUT", "Mixer Switch", "SPKPGA" },

	{ "Speaker", NULL, "SPKOUT" },
};

static const struct snd_soc_dapm_route audio_map_in1_se[] = {
	{ "IN1B PGA", NULL, "IN1-" },	

	{ "SPKMIX", "IN1B Switch", "IN1B PGA" },
	{ "MIXOUTL", "IN1B Switch", "IN1B PGA" },
	{ "MIXOUTR", "IN1B Switch", "IN1B PGA" },
};

static const struct snd_soc_dapm_route audio_map_in1_diff[] = {
	{ "IN1A PGA", NULL, "IN1-" },	
};

static const struct snd_soc_dapm_route audio_map_in2_se[] = {
	{ "IN2B PGA", NULL, "IN2-" },	

	{ "SPKMIX", "IN2B Switch", "IN2B PGA" },
	{ "MIXOUTL", "IN2B Switch", "IN2B PGA" },
	{ "MIXOUTR", "IN2B Switch", "IN2B PGA" },
};

static const struct snd_soc_dapm_route audio_map_in2_diff[] = {
	{ "IN2A PGA", NULL, "IN2-" },	
};

static int wm9090_add_controls(struct snd_soc_codec *codec)
{
	struct wm9090_priv *wm9090 = snd_soc_codec_get_drvdata(codec);
	struct snd_soc_dapm_context *dapm = &codec->dapm;
	int i;

	snd_soc_dapm_new_controls(dapm, wm9090_dapm_widgets,
				  ARRAY_SIZE(wm9090_dapm_widgets));

	snd_soc_dapm_add_routes(dapm, audio_map, ARRAY_SIZE(audio_map));

	snd_soc_add_codec_controls(codec, wm9090_controls,
			     ARRAY_SIZE(wm9090_controls));

	if (wm9090->pdata.lin1_diff) {
		snd_soc_dapm_add_routes(dapm, audio_map_in1_diff,
					ARRAY_SIZE(audio_map_in1_diff));
	} else {
		snd_soc_dapm_add_routes(dapm, audio_map_in1_se,
					ARRAY_SIZE(audio_map_in1_se));
		snd_soc_add_codec_controls(codec, wm9090_in1_se_controls,
				     ARRAY_SIZE(wm9090_in1_se_controls));
	}

	if (wm9090->pdata.lin2_diff) {
		snd_soc_dapm_add_routes(dapm, audio_map_in2_diff,
					ARRAY_SIZE(audio_map_in2_diff));
	} else {
		snd_soc_dapm_add_routes(dapm, audio_map_in2_se,
					ARRAY_SIZE(audio_map_in2_se));
		snd_soc_add_codec_controls(codec, wm9090_in2_se_controls,
				     ARRAY_SIZE(wm9090_in2_se_controls));
	}

	if (wm9090->pdata.agc_ena) {
		for (i = 0; i < ARRAY_SIZE(wm9090->pdata.agc); i++)
			snd_soc_write(codec, WM9090_AGC_CONTROL_0 + i,
				      wm9090->pdata.agc[i]);
		snd_soc_update_bits(codec, WM9090_POWER_MANAGEMENT_3,
				    WM9090_AGC_ENA, WM9090_AGC_ENA);
	} else {
		snd_soc_update_bits(codec, WM9090_POWER_MANAGEMENT_3,
				    WM9090_AGC_ENA, 0);
	}

	return 0;

}

/*
                                                                          
                                                                      
 */
static int wm9090_set_bias_level(struct snd_soc_codec *codec,
				 enum snd_soc_bias_level level)
{
	struct wm9090_priv *wm9090 = snd_soc_codec_get_drvdata(codec);

	switch (level) {
	case SND_SOC_BIAS_ON:
		break;

	case SND_SOC_BIAS_PREPARE:
		snd_soc_update_bits(codec, WM9090_ANTIPOP2, WM9090_VMID_ENA,
				    WM9090_VMID_ENA);
		snd_soc_update_bits(codec, WM9090_POWER_MANAGEMENT_1,
				    WM9090_BIAS_ENA |
				    WM9090_VMID_RES_MASK,
				    WM9090_BIAS_ENA |
				    1 << WM9090_VMID_RES_SHIFT);
		msleep(1);  /*                          */
		break;

	case SND_SOC_BIAS_STANDBY:
		if (codec->dapm.bias_level == SND_SOC_BIAS_OFF) {
			/*                            */
			regcache_sync(wm9090->regmap);
		}

		/*                                                         
                                                            
                             
   */
		snd_soc_update_bits(codec, WM9090_POWER_MANAGEMENT_1,
				    WM9090_BIAS_ENA | WM9090_VMID_RES_MASK, 0);
		snd_soc_update_bits(codec, WM9090_ANTIPOP2,
				    WM9090_VMID_ENA, 0);
		break;

	case SND_SOC_BIAS_OFF:
		break;
	}

	codec->dapm.bias_level = level;

	return 0;
}

static int wm9090_probe(struct snd_soc_codec *codec)
{
	struct wm9090_priv *wm9090 = dev_get_drvdata(codec->dev);
	int ret;

	codec->control_data = wm9090->regmap;
	ret = snd_soc_codec_set_cache_io(codec, 8, 16, SND_SOC_REGMAP);
	if (ret != 0) {
		dev_err(codec->dev, "Failed to set cache I/O: %d\n", ret);
		return ret;
	}

	/*                                                          
                      
  */
	snd_soc_update_bits(codec, WM9090_IN1_LINE_INPUT_A_VOLUME,
			    WM9090_IN1_VU | WM9090_IN1A_ZC,
			    WM9090_IN1_VU | WM9090_IN1A_ZC);
	snd_soc_update_bits(codec, WM9090_IN1_LINE_INPUT_B_VOLUME,
			    WM9090_IN1_VU | WM9090_IN1B_ZC,
			    WM9090_IN1_VU | WM9090_IN1B_ZC);
	snd_soc_update_bits(codec, WM9090_IN2_LINE_INPUT_A_VOLUME,
			    WM9090_IN2_VU | WM9090_IN2A_ZC,
			    WM9090_IN2_VU | WM9090_IN2A_ZC);
	snd_soc_update_bits(codec, WM9090_IN2_LINE_INPUT_B_VOLUME,
			    WM9090_IN2_VU | WM9090_IN2B_ZC,
			    WM9090_IN2_VU | WM9090_IN2B_ZC);
	snd_soc_update_bits(codec, WM9090_SPEAKER_VOLUME_LEFT,
			    WM9090_SPKOUT_VU | WM9090_SPKOUTL_ZC,
			    WM9090_SPKOUT_VU | WM9090_SPKOUTL_ZC);
	snd_soc_update_bits(codec, WM9090_LEFT_OUTPUT_VOLUME,
			    WM9090_HPOUT1_VU | WM9090_HPOUT1L_ZC,
			    WM9090_HPOUT1_VU | WM9090_HPOUT1L_ZC);
	snd_soc_update_bits(codec, WM9090_RIGHT_OUTPUT_VOLUME,
			    WM9090_HPOUT1_VU | WM9090_HPOUT1R_ZC,
			    WM9090_HPOUT1_VU | WM9090_HPOUT1R_ZC);

	snd_soc_update_bits(codec, WM9090_CLOCKING_1,
			    WM9090_TOCLK_ENA, WM9090_TOCLK_ENA);

	wm9090_set_bias_level(codec, SND_SOC_BIAS_STANDBY);

	wm9090_add_controls(codec);

	return 0;
}

#ifdef CONFIG_PM
static int wm9090_suspend(struct snd_soc_codec *codec)
{
	wm9090_set_bias_level(codec, SND_SOC_BIAS_OFF);

	return 0;
}

static int wm9090_resume(struct snd_soc_codec *codec)
{
	wm9090_set_bias_level(codec, SND_SOC_BIAS_STANDBY);

	return 0;
}
#else
#define wm9090_suspend NULL
#define wm9090_resume NULL
#endif

static int wm9090_remove(struct snd_soc_codec *codec)
{
	wm9090_set_bias_level(codec, SND_SOC_BIAS_OFF);

	return 0;
}

static struct snd_soc_codec_driver soc_codec_dev_wm9090 = {
	.probe = 	wm9090_probe,
	.remove = 	wm9090_remove,
	.suspend = 	wm9090_suspend,
	.resume =	wm9090_resume,
	.set_bias_level = wm9090_set_bias_level,
};

static const struct regmap_config wm9090_regmap = {
	.reg_bits = 8,
	.val_bits = 16,

	.max_register = WM9090_MAX_REGISTER,
	.volatile_reg = wm9090_volatile,
	.readable_reg = wm9090_readable,

	.cache_type = REGCACHE_RBTREE,
	.reg_defaults = wm9090_reg_defaults,
	.num_reg_defaults = ARRAY_SIZE(wm9090_reg_defaults),
};


static int wm9090_i2c_probe(struct i2c_client *i2c,
			    const struct i2c_device_id *id)
{
	struct wm9090_priv *wm9090;
	unsigned int reg;
	int ret;

	wm9090 = devm_kzalloc(&i2c->dev, sizeof(*wm9090), GFP_KERNEL);
	if (wm9090 == NULL) {
		dev_err(&i2c->dev, "Can not allocate memory\n");
		return -ENOMEM;
	}

	wm9090->regmap = devm_regmap_init_i2c(i2c, &wm9090_regmap);
	if (IS_ERR(wm9090->regmap)) {
		ret = PTR_ERR(wm9090->regmap);
		dev_err(&i2c->dev, "Failed to allocate regmap: %d\n", ret);
		return ret;
	}

	ret = regmap_read(wm9090->regmap, WM9090_SOFTWARE_RESET, &reg);
	if (ret < 0)
		return ret;

	if (reg != 0x9093) {
		dev_err(&i2c->dev, "Device is not a WM9090, ID=%x\n", reg);
		return -ENODEV;
	}

	ret = regmap_write(wm9090->regmap, WM9090_SOFTWARE_RESET, 0);
	if (ret < 0)
		return ret;

	if (i2c->dev.platform_data)
		memcpy(&wm9090->pdata, i2c->dev.platform_data,
		       sizeof(wm9090->pdata));

	i2c_set_clientdata(i2c, wm9090);

	ret =  snd_soc_register_codec(&i2c->dev,
			&soc_codec_dev_wm9090,  NULL, 0);
	if (ret != 0) {
		dev_err(&i2c->dev, "Failed to register CODEC: %d\n", ret);
		return ret;
	}

	return 0;
}

static int wm9090_i2c_remove(struct i2c_client *i2c)
{
	snd_soc_unregister_codec(&i2c->dev);
	return 0;
}

static const struct i2c_device_id wm9090_id[] = {
	{ "wm9090", 0 },
	{ "wm9093", 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, wm9090_id);

static struct i2c_driver wm9090_i2c_driver = {
	.driver = {
		.name = "wm9090",
		.owner = THIS_MODULE,
	},
	.probe = wm9090_i2c_probe,
	.remove = wm9090_i2c_remove,
	.id_table = wm9090_id,
};

module_i2c_driver(wm9090_i2c_driver);

MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_DESCRIPTION("WM9090 ASoC driver");
MODULE_LICENSE("GPL");
