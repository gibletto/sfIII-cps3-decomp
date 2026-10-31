/*
 * SOUND_VOICE.C  Sound envelope rates and the idle voice handler
 *
 * sound_envelope_rate scales a level by an entry of a rate table (never less than 1);
 * voice_process_null is the handler of a voice with nothing to play.
 */

#include "structs.h"
#include "sound_voice.h"

u32 sound_envelope_rate(u16 level, u8 index, const u16* table) {
    u32 rate;
    u32 offset;

    offset = index;
    rate = level;
    table += offset;
    rate = (u32)(rate * (*table + 1)) >> 16;
    if (rate) {
        return (u16)rate;
    }
    return 1;
}

void voice_process_null(SNDVOICE* voice, u8 voice_index) {
}
