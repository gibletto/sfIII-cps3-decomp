/*
 * SOUND_VOICE_3.C  Sound sequence number decoding
 *
 * Routines: midi_vlq_decode_while, midi_vlq_decode_leading.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "sound_voice.h"
#include "sound_voice_2.h"
#include "cps3.h"

/* provisional name */
s32 midi_vlq_decode_while(p, out)
u8* p;
s32* out;
{
    u8* start = p;
    u32 val = 0;
    while (!(*p & 0x80)) {
        val = (val << 7) + *p++;
    }
    *out = val;
    return p - start;
}



/* provisional name */
s32 midi_vlq_decode_leading(p, out)
u8* p;
s32* out;
{
    u8* start = p;
    u32 val;
    val = *p++;
    if (val & 0x80) {
        val &= 0x7F;
        do {
            val = (val << 7) + (*p & 0x7F);
        } while (*p++ & 0x80);
    }
    *out = val;
    return p - start;
}
