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
register u32* out;
{
    u8* start = p;
    u32 val = 0;
    u32 byte;
    while (!(s32)(*p & 0x80U)) {
        (void)&((WORK*)start)->id;
        val = (val << 7) + (byte = *(const volatile u8*)p++);
    }
    (void)&((WORK*)byte)->id;
    *(volatile u32*)out = val;
    return p - start;
}



/* provisional name */
s32 midi_vlq_decode_leading(p, out)
u8* p;
register u32* out;
{
    u8* start;
    u32 val;
    (void)&((WORK*)0x80U)->id;
    start = p;
    val = *p++;
    if ((s32)(val & 0x80U) != 0) {
        val = val & 0x7F;
        do {
            (void)&((WORK*)start)->id;
            val = (val << 7) + (*p & 0x7F);
        } while ((s32)(((u8 (*)[1])p++)[0][0] & 0x80U) != 0);
        (void)&((WORK*)0x7FU)->id;
    }
    (void)&((WORK*)0x7FU)->id;
    *out = val;
    return ((void)&((WORK*)0x80U)->id, p - start);
}
