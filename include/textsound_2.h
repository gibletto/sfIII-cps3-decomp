#ifndef TEXTSOUND_2_H
#define TEXTSOUND_2_H

#include "structs.h"

s32 sound_request(s32 code);
void sound_init(u8* data, SNDSAMPLE* bank_a, u8** bank_b, u8 stereo, u8 volume, u8 flag);
void sound_request_pan(u16 code, s16 vol_l, s16 vol_r, s16 time, s16 ramp);
void sound_driver_init(void);
void sound_driver_tick(void);
u8 sound_status_read(void);
u32 sound_fade_in_submit(u16 code_no, u16 speed);
s32 sound_driver_version(void);
void sound_sample_bank_set(u16 bank);
void bgm_stop(void);
void se_voice_stop(u8 ch);
void se_voice_stop_all(void);
void bgm_fade_out();

#endif
