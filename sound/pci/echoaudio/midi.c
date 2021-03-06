/****************************************************************************

   Copyright Echo Digital Audio Corporation (c) 1998 - 2004
   All rights reserved
   www.echoaudio.com

   This file is part of Echo Digital Audio's generic driver library.

   Echo Digital Audio's generic driver library is free software;
   you can redistribute it and/or modify it under the terms of
   the GNU General Public License as published by the Free Software
   Foundation.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston,
   MA  02111-1307, USA.

   *************************************************************************

 Translation from C++ and adaptation for use in ALSA-Driver
 were made by Giuliano Pochini <pochini@shiny.it>

****************************************************************************/


/*                                                                             
                   
                                                                             */

/*                           */
static int enable_midi_input(struct echoaudio *chip, char enable)
{
	DE_MID(("enable_midi_input(%d)\n", enable));

	if (wait_handshake(chip))
		return -EIO;

	if (enable) {
		chip->mtc_state = MIDI_IN_STATE_NORMAL;
		chip->comm_page->flags |=
			cpu_to_le32(DSP_FLAG_MIDI_INPUT);
	} else
		chip->comm_page->flags &=
			~cpu_to_le32(DSP_FLAG_MIDI_INPUT);

	clear_handshake(chip);
	return send_vector(chip, DSP_VC_UPDATE_FLAGS);
}



/*                                           
                                                  */
static int write_midi(struct echoaudio *chip, u8 *data, int bytes)
{
	if (snd_BUG_ON(bytes <= 0 || bytes >= MIDI_OUT_BUFFER_SIZE))
		return -EINVAL;

	if (wait_handshake(chip))
		return -EIO;

	/*                                                         */
	if (! (get_dsp_register(chip, CHI32_STATUS_REG) & CHI32_STATUS_REG_HF4))
		return 0;

	chip->comm_page->midi_output[0] = bytes;
	memcpy(&chip->comm_page->midi_output[1], data, bytes);
	chip->comm_page->midi_out_free_count = 0;
	clear_handshake(chip);
	send_vector(chip, DSP_VC_MIDI_WRITE);
	DE_MID(("write_midi: %d\n", bytes));
	return bytes;
}



/*                                          
                                                                              
                                                                              
                                                                          
                                                                          
                                                                            
                                                             */
static inline int mtc_process_data(struct echoaudio *chip, short midi_byte)
{
	switch (chip->mtc_state) {
	case MIDI_IN_STATE_NORMAL:
		if (midi_byte == 0xF1)
			chip->mtc_state = MIDI_IN_STATE_TS_HIGH;
		break;
	case MIDI_IN_STATE_TS_HIGH:
		chip->mtc_state = MIDI_IN_STATE_TS_LOW;
		return MIDI_IN_SKIP_DATA;
		break;
	case MIDI_IN_STATE_TS_LOW:
		chip->mtc_state = MIDI_IN_STATE_F1_DATA;
		return MIDI_IN_SKIP_DATA;
		break;
	case MIDI_IN_STATE_F1_DATA:
		chip->mtc_state = MIDI_IN_STATE_NORMAL;
		break;
	}
	return 0;
}



/*                                                                        
                                                                 */
static int midi_service_irq(struct echoaudio *chip)
{
	short int count, midi_byte, i, received;

	/*                                                  */
	count = le16_to_cpu(chip->comm_page->midi_input[0]);

	if (snd_BUG_ON(count >= MIDI_IN_BUFFER_SIZE))
		return 0;

	/*                                      */
	i = 1;
	received = 0;
	for (i = 1; i <= count; i++) {
		/*                   */
		midi_byte = le16_to_cpu(chip->comm_page->midi_input[i]);

		/*                                                       
                                                              
                                                               
                                                            
                                                              
                            */
		if (mtc_process_data(chip, midi_byte) == MIDI_IN_SKIP_DATA)
			continue;

		chip->midi_buffer[received++] = (u8)midi_byte;
	}

	return received;
}




/*                                                                             
               
                                                                             */

static int snd_echo_midi_input_open(struct snd_rawmidi_substream *substream)
{
	struct echoaudio *chip = substream->rmidi->private_data;

	chip->midi_in = substream;
	DE_MID(("rawmidi_iopen\n"));
	return 0;
}



static void snd_echo_midi_input_trigger(struct snd_rawmidi_substream *substream,
					int up)
{
	struct echoaudio *chip = substream->rmidi->private_data;

	if (up != chip->midi_input_enabled) {
		spin_lock_irq(&chip->lock);
		enable_midi_input(chip, up);
		spin_unlock_irq(&chip->lock);
		chip->midi_input_enabled = up;
	}
}



static int snd_echo_midi_input_close(struct snd_rawmidi_substream *substream)
{
	struct echoaudio *chip = substream->rmidi->private_data;

	chip->midi_in = NULL;
	DE_MID(("rawmidi_iclose\n"));
	return 0;
}



static int snd_echo_midi_output_open(struct snd_rawmidi_substream *substream)
{
	struct echoaudio *chip = substream->rmidi->private_data;

	chip->tinuse = 0;
	chip->midi_full = 0;
	chip->midi_out = substream;
	DE_MID(("rawmidi_oopen\n"));
	return 0;
}



static void snd_echo_midi_output_write(unsigned long data)
{
	struct echoaudio *chip = (struct echoaudio *)data;
	unsigned long flags;
	int bytes, sent, time;
	unsigned char buf[MIDI_OUT_BUFFER_SIZE - 1];

	DE_MID(("snd_echo_midi_output_write\n"));
	/*                                                                  
                                                    */
	sent = bytes = 0;
	spin_lock_irqsave(&chip->lock, flags);
	chip->midi_full = 0;
	if (!snd_rawmidi_transmit_empty(chip->midi_out)) {
		bytes = snd_rawmidi_transmit_peek(chip->midi_out, buf,
						  MIDI_OUT_BUFFER_SIZE - 1);
		DE_MID(("Try to send %d bytes...\n", bytes));
		sent = write_midi(chip, buf, bytes);
		if (sent < 0) {
			snd_printk(KERN_ERR "write_midi() error %d\n", sent);
			/*             */
			sent = 9000;
			chip->midi_full = 1;
		} else if (sent > 0) {
			DE_MID(("%d bytes sent\n", sent));
			snd_rawmidi_transmit_ack(chip->midi_out, sent);
		} else {
			/*                                                    
                                                      */
			DE_MID(("Full\n"));
			sent = 32;
			chip->midi_full = 1;
		}
	}

	/*                                                              */
	if (!snd_rawmidi_transmit_empty(chip->midi_out) && chip->tinuse) {
		/*                                                       
          */
		time = (sent << 3) / 25 + 1;	/*                            */
		mod_timer(&chip->timer, jiffies + (time * HZ + 999) / 1000);
		DE_MID(("Timer armed(%d)\n", ((time * HZ + 999) / 1000)));
	}
	spin_unlock_irqrestore(&chip->lock, flags);
}



static void snd_echo_midi_output_trigger(struct snd_rawmidi_substream *substream,
					 int up)
{
	struct echoaudio *chip = substream->rmidi->private_data;

	DE_MID(("snd_echo_midi_output_trigger(%d)\n", up));
	spin_lock_irq(&chip->lock);
	if (up) {
		if (!chip->tinuse) {
			init_timer(&chip->timer);
			chip->timer.function = snd_echo_midi_output_write;
			chip->timer.data = (unsigned long)chip;
			chip->tinuse = 1;
		}
	} else {
		if (chip->tinuse) {
			chip->tinuse = 0;
			spin_unlock_irq(&chip->lock);
			del_timer_sync(&chip->timer);
			DE_MID(("Timer removed\n"));
			return;
		}
	}
	spin_unlock_irq(&chip->lock);

	if (up && !chip->midi_full)
		snd_echo_midi_output_write((unsigned long)chip);
}



static int snd_echo_midi_output_close(struct snd_rawmidi_substream *substream)
{
	struct echoaudio *chip = substream->rmidi->private_data;

	chip->midi_out = NULL;
	DE_MID(("rawmidi_oclose\n"));
	return 0;
}



static struct snd_rawmidi_ops snd_echo_midi_input = {
	.open = snd_echo_midi_input_open,
	.close = snd_echo_midi_input_close,
	.trigger = snd_echo_midi_input_trigger,
};

static struct snd_rawmidi_ops snd_echo_midi_output = {
	.open = snd_echo_midi_output_open,
	.close = snd_echo_midi_output_close,
	.trigger = snd_echo_midi_output_trigger,
};



/*                     */
static int snd_echo_midi_create(struct snd_card *card,
				struct echoaudio *chip)
{
	int err;

	if ((err = snd_rawmidi_new(card, card->shortname, 0, 1, 1,
				   &chip->rmidi)) < 0)
		return err;

	strcpy(chip->rmidi->name, card->shortname);
	chip->rmidi->private_data = chip;

	snd_rawmidi_set_ops(chip->rmidi, SNDRV_RAWMIDI_STREAM_INPUT,
			    &snd_echo_midi_input);
	snd_rawmidi_set_ops(chip->rmidi, SNDRV_RAWMIDI_STREAM_OUTPUT,
			    &snd_echo_midi_output);

	chip->rmidi->info_flags |= SNDRV_RAWMIDI_INFO_OUTPUT |
		SNDRV_RAWMIDI_INFO_INPUT | SNDRV_RAWMIDI_INFO_DUPLEX;
	DE_INIT(("MIDI ok\n"));
	return 0;
}
