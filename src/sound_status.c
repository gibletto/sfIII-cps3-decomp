/*
 * SOUND_STATUS.C  Sound driver status
 *
 * sound_status_read returns the driver's status byte, the first byte of sound_sample_submit_work7.
 */

#include "structs.h"
#include "work.h"
#include "textsound_2.h"

u8 sound_status_read(void) {
    return *(s8*)&sound_sample_submit_work7;
}
