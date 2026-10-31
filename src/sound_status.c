/*
 * SOUND_STATUS.C  Sound driver status
 *
 * sound_status_read returns the music state byte, bgm_state.
 */

#include "structs.h"
#include "work.h"
#include "textsound_2.h"

/* provisional name */
u8 sound_status_read(void) {
    return *(s8*)&bgm_state;
}
