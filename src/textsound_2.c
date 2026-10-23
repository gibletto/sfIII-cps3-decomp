/*
 * TEXTSOUND_2.C  Sound driver version, sample bank and the driver interface's work
 *
 * sound_driver_version returns the driver's version (0x145); sound_sample_bank_set selects the sample
 * bank (snd_wave_bias). The rest of the driver interface is built from assembler (textsound_2_x1.src,
 * textsound_2_x2.src; its C is nonmatching/textsound_2.c), with the work below: the sequence data and
 * count, the pending pan ramp, the music voices' saved states, the driver's status byte and the music's
 * starting master volume. sound_init_data holds the 21 set-up words sound_init writes to the chip's
 * control port (EXT_SW + 0x202).
 */

#include "structs.h"
#include "work.h"
#include "textsound_2.h"



u16 sound_init_data[21] = {  /* 02007398, provisional name */
    3, 1, 3, 1, 3, 1, 3, 0, 2, 1, 3, 0, 2, 0, 2, 0, 2, 2, 6, 6, 2
};

u32* snd_seq_data;  /* 0206CDCC */
SNDRAMP se_ramp_req;  /* 0206CDD0 */
u16 snd_reg_save;  /* 0206CDD8 */
u16 snd_seq_max;  /* 0206CDDA */
u8 bgm_status_save[16];  /* 0206CDDC */
u8 sound_sample_submit_work7;  /* 0206CDEC */
/* after sound_sample_submit_work7: nothing refers to it by name or address */
u8 sound_sample_submit_work7_tail[1];  /* 0206CDED */
u8 bgm_master_vol_init;  /* 0206CDEE */

s32 sound_driver_version(void) {
    return 0x145;
}

void sound_sample_bank_set(u16 bank) {
    snd_wave_bias = bank;
}
