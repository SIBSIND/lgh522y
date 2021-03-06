/*
 * Copyright 2008 Stuart Bennett
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef __NOUVEAU_HW_H__
#define __NOUVEAU_HW_H__

#include <drm/drmP.h>
#include "disp.h"
#include "nvreg.h"

#include <subdev/bios/pll.h>

#define MASK(field) ( \
	(0xffffffff >> (31 - ((1 ? field) - (0 ? field)))) << (0 ? field))

#define XLATE(src, srclowbit, outfield) ( \
	(((src) >> (srclowbit)) << (0 ? outfield)) & MASK(outfield))

void NVWriteVgaSeq(struct drm_device *, int head, uint8_t index, uint8_t value);
uint8_t NVReadVgaSeq(struct drm_device *, int head, uint8_t index);
void NVWriteVgaGr(struct drm_device *, int head, uint8_t index, uint8_t value);
uint8_t NVReadVgaGr(struct drm_device *, int head, uint8_t index);
void NVSetOwner(struct drm_device *, int owner);
void NVBlankScreen(struct drm_device *, int head, bool blank);
int nouveau_hw_get_pllvals(struct drm_device *, enum nvbios_pll_type plltype,
			   struct nouveau_pll_vals *pllvals);
int nouveau_hw_pllvals_to_clk(struct nouveau_pll_vals *pllvals);
int nouveau_hw_get_clock(struct drm_device *, enum nvbios_pll_type plltype);
void nouveau_hw_save_vga_fonts(struct drm_device *, bool save);
void nouveau_hw_save_state(struct drm_device *, int head,
			   struct nv04_mode_state *state);
void nouveau_hw_load_state(struct drm_device *, int head,
			   struct nv04_mode_state *state);
void nouveau_hw_load_state_palette(struct drm_device *, int head,
				   struct nv04_mode_state *state);

/*                */
extern void nouveau_calc_arb(struct drm_device *, int vclk, int bpp,
			     int *burst, int *lwm);

static inline uint32_t NVReadCRTC(struct drm_device *dev,
					int head, uint32_t reg)
{
	struct nouveau_device *device = nouveau_dev(dev);
	uint32_t val;
	if (head)
		reg += NV_PCRTC0_SIZE;
	val = nv_rd32(device, reg);
	return val;
}

static inline void NVWriteCRTC(struct drm_device *dev,
					int head, uint32_t reg, uint32_t val)
{
	struct nouveau_device *device = nouveau_dev(dev);
	if (head)
		reg += NV_PCRTC0_SIZE;
	nv_wr32(device, reg, val);
}

static inline uint32_t NVReadRAMDAC(struct drm_device *dev,
					int head, uint32_t reg)
{
	struct nouveau_device *device = nouveau_dev(dev);
	uint32_t val;
	if (head)
		reg += NV_PRAMDAC0_SIZE;
	val = nv_rd32(device, reg);
	return val;
}

static inline void NVWriteRAMDAC(struct drm_device *dev,
					int head, uint32_t reg, uint32_t val)
{
	struct nouveau_device *device = nouveau_dev(dev);
	if (head)
		reg += NV_PRAMDAC0_SIZE;
	nv_wr32(device, reg, val);
}

static inline uint8_t nv_read_tmds(struct drm_device *dev,
					int or, int dl, uint8_t address)
{
	int ramdac = (or & DCB_OUTPUT_C) >> 2;

	NVWriteRAMDAC(dev, ramdac, NV_PRAMDAC_FP_TMDS_CONTROL + dl * 8,
	NV_PRAMDAC_FP_TMDS_CONTROL_WRITE_DISABLE | address);
	return NVReadRAMDAC(dev, ramdac, NV_PRAMDAC_FP_TMDS_DATA + dl * 8);
}

static inline void nv_write_tmds(struct drm_device *dev,
					int or, int dl, uint8_t address,
					uint8_t data)
{
	int ramdac = (or & DCB_OUTPUT_C) >> 2;

	NVWriteRAMDAC(dev, ramdac, NV_PRAMDAC_FP_TMDS_DATA + dl * 8, data);
	NVWriteRAMDAC(dev, ramdac, NV_PRAMDAC_FP_TMDS_CONTROL + dl * 8, address);
}

static inline void NVWriteVgaCrtc(struct drm_device *dev,
					int head, uint8_t index, uint8_t value)
{
	struct nouveau_device *device = nouveau_dev(dev);
	nv_wr08(device, NV_PRMCIO_CRX__COLOR + head * NV_PRMCIO_SIZE, index);
	nv_wr08(device, NV_PRMCIO_CR__COLOR + head * NV_PRMCIO_SIZE, value);
}

static inline uint8_t NVReadVgaCrtc(struct drm_device *dev,
					int head, uint8_t index)
{
	struct nouveau_device *device = nouveau_dev(dev);
	uint8_t val;
	nv_wr08(device, NV_PRMCIO_CRX__COLOR + head * NV_PRMCIO_SIZE, index);
	val = nv_rd08(device, NV_PRMCIO_CR__COLOR + head * NV_PRMCIO_SIZE);
	return val;
}

/*                                                                              
                                                                          
                            
  
              
             
                                                                
                                                    
                                                              
                            
                                                                
                                        
 */

static inline void
NVWriteVgaCrtc5758(struct drm_device *dev, int head, uint8_t index, uint8_t value)
{
	NVWriteVgaCrtc(dev, head, NV_CIO_CRE_57, index);
	NVWriteVgaCrtc(dev, head, NV_CIO_CRE_58, value);
}

static inline uint8_t NVReadVgaCrtc5758(struct drm_device *dev, int head, uint8_t index)
{
	NVWriteVgaCrtc(dev, head, NV_CIO_CRE_57, index);
	return NVReadVgaCrtc(dev, head, NV_CIO_CRE_58);
}

static inline uint8_t NVReadPRMVIO(struct drm_device *dev,
					int head, uint32_t reg)
{
	struct nouveau_device *device = nouveau_dev(dev);
	struct nouveau_drm *drm = nouveau_drm(dev);
	uint8_t val;

	/*                                                               
                                                      */
	if (head && nv_device(drm->device)->card_type == NV_40)
		reg += NV_PRMVIO_SIZE;

	val = nv_rd08(device, reg);
	return val;
}

static inline void NVWritePRMVIO(struct drm_device *dev,
					int head, uint32_t reg, uint8_t value)
{
	struct nouveau_device *device = nouveau_dev(dev);
	struct nouveau_drm *drm = nouveau_drm(dev);

	/*                                                               
                                                      */
	if (head && nv_device(drm->device)->card_type == NV_40)
		reg += NV_PRMVIO_SIZE;

	nv_wr08(device, reg, value);
}

static inline void NVSetEnablePalette(struct drm_device *dev, int head, bool enable)
{
	struct nouveau_device *device = nouveau_dev(dev);
	nv_rd08(device, NV_PRMCIO_INP0__COLOR + head * NV_PRMCIO_SIZE);
	nv_wr08(device, NV_PRMCIO_ARX + head * NV_PRMCIO_SIZE, enable ? 0 : 0x20);
}

static inline bool NVGetEnablePalette(struct drm_device *dev, int head)
{
	struct nouveau_device *device = nouveau_dev(dev);
	nv_rd08(device, NV_PRMCIO_INP0__COLOR + head * NV_PRMCIO_SIZE);
	return !(nv_rd08(device, NV_PRMCIO_ARX + head * NV_PRMCIO_SIZE) & 0x20);
}

static inline void NVWriteVgaAttr(struct drm_device *dev,
					int head, uint8_t index, uint8_t value)
{
	struct nouveau_device *device = nouveau_dev(dev);
	if (NVGetEnablePalette(dev, head))
		index &= ~0x20;
	else
		index |= 0x20;

	nv_rd08(device, NV_PRMCIO_INP0__COLOR + head * NV_PRMCIO_SIZE);
	nv_wr08(device, NV_PRMCIO_ARX + head * NV_PRMCIO_SIZE, index);
	nv_wr08(device, NV_PRMCIO_AR__WRITE + head * NV_PRMCIO_SIZE, value);
}

static inline uint8_t NVReadVgaAttr(struct drm_device *dev,
					int head, uint8_t index)
{
	struct nouveau_device *device = nouveau_dev(dev);
	uint8_t val;
	if (NVGetEnablePalette(dev, head))
		index &= ~0x20;
	else
		index |= 0x20;

	nv_rd08(device, NV_PRMCIO_INP0__COLOR + head * NV_PRMCIO_SIZE);
	nv_wr08(device, NV_PRMCIO_ARX + head * NV_PRMCIO_SIZE, index);
	val = nv_rd08(device, NV_PRMCIO_AR__READ + head * NV_PRMCIO_SIZE);
	return val;
}

static inline void NVVgaSeqReset(struct drm_device *dev, int head, bool start)
{
	NVWriteVgaSeq(dev, head, NV_VIO_SR_RESET_INDEX, start ? 0x1 : 0x3);
}

static inline void NVVgaProtect(struct drm_device *dev, int head, bool protect)
{
	uint8_t seq1 = NVReadVgaSeq(dev, head, NV_VIO_SR_CLOCK_INDEX);

	if (protect) {
		NVVgaSeqReset(dev, head, true);
		NVWriteVgaSeq(dev, head, NV_VIO_SR_CLOCK_INDEX, seq1 | 0x20);
	} else {
		/*                                         */
		NVWriteVgaSeq(dev, head, NV_VIO_SR_CLOCK_INDEX, seq1 & ~0x20);   /*                  */
		NVVgaSeqReset(dev, head, false);
	}
	NVSetEnablePalette(dev, head, protect);
}

static inline bool
nv_heads_tied(struct drm_device *dev)
{
	struct nouveau_device *device = nouveau_dev(dev);
	struct nouveau_drm *drm = nouveau_drm(dev);

	if (nv_device(drm->device)->chipset == 0x11)
		return !!(nv_rd32(device, NV_PBUS_DEBUG_1) & (1 << 28));

	return NVReadVgaCrtc(dev, 0, NV_CIO_CRE_44) & 0x4;
}

/*                                             */
static inline bool
nv_lock_vga_crtc_base(struct drm_device *dev, int head, bool lock)
{
	uint8_t cr11 = NVReadVgaCrtc(dev, head, NV_CIO_CR_VRE_INDEX);
	bool waslocked = cr11 & 0x80;

	if (lock)
		cr11 |= 0x80;
	else
		cr11 &= ~0x80;
	NVWriteVgaCrtc(dev, head, NV_CIO_CR_VRE_INDEX, cr11);

	return waslocked;
}

static inline void
nv_lock_vga_crtc_shadow(struct drm_device *dev, int head, int lock)
{
	/*                                                         
                                              
                                                                
                     
                     
                                                          
                                   
                                   
  */

	uint8_t cr21 = lock;

	if (lock < 0)
		/*                                   */
		cr21 = NVReadVgaCrtc(dev, head, NV_CIO_CRE_21) | 0xfa;

	NVWriteVgaCrtc(dev, head, NV_CIO_CRE_21, cr21);
}

/*                                                                
                           
 */
static inline bool
NVLockVgaCrtcs(struct drm_device *dev, bool lock)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	bool waslocked = !NVReadVgaCrtc(dev, 0, NV_CIO_SR_LOCK_INDEX);

	NVWriteVgaCrtc(dev, 0, NV_CIO_SR_LOCK_INDEX,
		       lock ? NV_CIO_SR_LOCK_VALUE : NV_CIO_SR_UNLOCK_RW_VALUE);
	/*                                                                  */
	if (nv_device(drm->device)->chipset == 0x11 && !nv_heads_tied(dev))
		NVWriteVgaCrtc(dev, 1, NV_CIO_SR_LOCK_INDEX,
			       lock ? NV_CIO_SR_LOCK_VALUE :
				      NV_CIO_SR_UNLOCK_RW_VALUE);

	return waslocked;
}

/*                                                */
#define NV04_CURSOR_SIZE 32
/*                                                             */
#define NV10_CURSOR_SIZE 64

static inline int nv_cursor_width(struct drm_device *dev)
{
	struct nouveau_drm *drm = nouveau_drm(dev);

	return nv_device(drm->device)->card_type >= NV_10 ? NV10_CURSOR_SIZE : NV04_CURSOR_SIZE;
}

static inline void
nv_fix_nv40_hw_cursor(struct drm_device *dev, int head)
{
	/*                                                                    
                                                                       
                                                                        
                                                          
  */
	uint32_t curpos = NVReadRAMDAC(dev, head, NV_PRAMDAC_CU_START_POS);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_CU_START_POS, curpos);
}

static inline void
nv_set_crtc_base(struct drm_device *dev, int head, uint32_t offset)
{
	struct nouveau_drm *drm = nouveau_drm(dev);

	NVWriteCRTC(dev, head, NV_PCRTC_START, offset);

	if (nv_device(drm->device)->card_type == NV_04) {
		/*
                                                     
                   
   */
		int cre_heb = NVReadVgaCrtc(dev, head, NV_CIO_CRE_HEB__INDEX);

		NVWriteVgaCrtc(dev, head, NV_CIO_CRE_HEB__INDEX,
			       (cre_heb & ~0x40) | ((offset >> 18) & 0x40));
	}
}

static inline void
nv_show_cursor(struct drm_device *dev, int head, bool show)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	uint8_t *curctl1 =
		&nv04_display(dev)->mode_reg.crtc_reg[head].CRTC[NV_CIO_CRE_HCUR_ADDR1_INDEX];

	if (show)
		*curctl1 |= MASK(NV_CIO_CRE_HCUR_ADDR1_ENABLE);
	else
		*curctl1 &= ~MASK(NV_CIO_CRE_HCUR_ADDR1_ENABLE);
	NVWriteVgaCrtc(dev, head, NV_CIO_CRE_HCUR_ADDR1_INDEX, *curctl1);

	if (nv_device(drm->device)->card_type == NV_40)
		nv_fix_nv40_hw_cursor(dev, head);
}

static inline uint32_t
nv_pitch_align(struct drm_device *dev, uint32_t width, int bpp)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	int mask;

	if (bpp == 15)
		bpp = 16;
	if (bpp == 24)
		bpp = 8;

	/*                                                    */
	if (nv_device(drm->device)->card_type == NV_04)
		mask = 128 / bpp - 1;
	else
		mask = 512 / bpp - 1;

	return (width + mask) & ~mask;
}

#endif	/*                  */
