#ifndef SOUND_VOICE_2_H
#define SOUND_VOICE_2_H

#include "structs.h"

s32 sound_note_to_pitch(s32 note);
s32 midi_vlq_decode_leading();
s32 midi_vlq_decode_while();

#endif
