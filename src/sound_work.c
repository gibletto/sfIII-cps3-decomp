/*
 * SOUND_WORK.C  sound driver work
 *
 * The sound driver's voices, envelopes and settings: cleared work RAM (section B), the last of it.
 * sound_init sets the table pointers, the sample and bank tables and the volumes; the 16 music voices
 * (bgm_voice) and 16 effect voices (se_voice) hold each voice's sequence position, note, envelope and LFO
 * state; se_pan_ramp is the pan ramp of each effect voice, snd_ctrl the chip's control word.
 */

#include "types.h"
#include "structs.h"

const u16* snd_attack_ptr;  /* 0206CDF8 */
const u16* snd_decay_ptr;  /* 0206CDFC */
const u16* snd_lfo_rate_ptr;  /* 0206CE00 */
const u16* snd_pitch_lfo_ptr;  /* 0206CE04 */
const u16* snd_vol_lfo_ptr;  /* 0206CE08 */
SNDSAMPLE* snd_sample_tbl;  /* 0206CE0C */
u8** snd_bank_tbl;  /* 0206CE10 */
u32 snd_fade_level;  /* 0206CE14 */
u32 snd_fade_speed;  /* 0206CE18 */
SNDVOICE bgm_voice[16];  /* 0206CE1C */
SNDVOICE se_voice[16];  /* 0206D51C */
SNDRAMP se_pan_ramp[16];  /* 0206DC1C */
/* added to every music voice's pitch (sound_reg_level_set) */
s16 bgm_pitch_offset;  /* 0206DC9C */
u16 snd_wave_bias;  /* 0206DC9E */
SOUND_CTRL snd_ctrl;  /* 0206DCA0 */
u16 bgm_tick_step;  /* 0206DCA4 */
u16 se_tick_step[16];  /* 0206DCA6 */
/* the music's volume offset; -128 silences it (sound_reg_level_set) */
s8 bgm_volume_offset;  /* 0206DCC6 */
u8 bgm_master_vol;  /* 0206DCC7 */
u8 snd_master_vol;  /* 0206DCC8 */
u8 snd_stereo;  /* 0206DCC9 */
