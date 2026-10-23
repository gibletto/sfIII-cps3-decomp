/*
 * TEXTSOUND_2.C  Sound driver version and sample bank
 *
 * sound_driver_version returns the driver's version (0x145); sound_sample_bank_set selects the sample
 * bank (snd_wave_bias).
 */

#include "structs.h"
#include "work.h"
#include "textsound_2.h"

s32 sound_driver_version(void) {
    return 0x145;
}

void sound_sample_bank_set(u16 bank) {
    snd_wave_bias = bank;
}
