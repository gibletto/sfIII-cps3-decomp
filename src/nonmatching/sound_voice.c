/*
 * SOUND_VOICE.C  Sound voice sequencer (reconstructed C, not built)
 *
 * voice_process_primary is built from assembler: src/sound_voice_x1.src gives the arcade's bytes. This is
 * the C it was compiled from, as far as it has been reconstructed.
 * The sound driver was built with an SHC release older than any that has been found; with a modelled
 * profile of that release this C compiles to most of the same instructions, but not to the exact bytes.
 * NONMATCHING selects the routine.
 *
 * voice_process_primary steps a voice's sequence (see sndseq.h for the events): unless the voice waits or
 * has ended, it reads events up to the next delay. A note takes the patch for its key from the voice's
 * instrument bank and sets the pitch, the envelope rates and the length or a tie; the other events set the
 * tempo, bank, program, pitch bend, fine tune, LFOs, volume, pan, expression, portamento, transposition, level
 * offsets and priority, or repeat, jump and loop. The end event stops the voice and lets the music voice
 * under an effect voice sound again. The module's first two routines, sound_envelope_rate and
 * voice_process_null, are C that builds the arcade's bytes (src/sound_voice.c).
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "cps3.h"

s32 sound_note_to_pitch(s32 note);
void sound_reg_write_verify(s16 *reg, u16 value);
u16 sound_voice_volume_compute(u16 level, u32 pan_scale, s8 pan, SNDVOICE* v);
void voice_process_secondary(SNDVOICE* voice, u8 voice_index, u8 is_bgm);
s32 midi_vlq_decode_leading();
s32 midi_vlq_decode_while();
u16 sound_envelope_rate(u16 level, u8 index, const u16* table);
void voice_process_null(SNDVOICE* voice, u8 voice_index);
void voice_process_primary(SNDVOICE* voice, u8 is_bgm, u8 voice_index);

#ifdef NONMATCHING

/* provisional name */
void voice_process_primary(SNDVOICE* voice, u8 is_bgm, u8 voice_index) {
    u8* argument;
    u8 event;
    u8 loop_index;
    u8 skip_index;
    s32 note;
    u32 event_mask;
    s16 note_resolved;
    s32 consumed;
    s32 ticks;
    s32 relative;
    SNDPATCH* patch;
    SNDVOICE* paired_bgm_voice;
    SNDRAMP* automation;
    u16* sfx_ticks;
    if (voice->status & 0x60) {
        return;
    }
    sfx_ticks = &se_tick_step[voice_index];
    paired_bgm_voice = &bgm_voice[voice_index];
    automation = &se_pan_ramp[voice_index];
    event_mask = 0x80;
next_event:
    argument = voice->cursor;
    event = *argument++;
    if (event >= 0xC0) {
control_event:;
        switch (event) {
        case 0xC0:
            break;
        case 0xC1:
            if (is_bgm) {
                bgm_tick_step = *argument++ << 8;
                bgm_tick_step += *argument++;
            } else {
                *sfx_ticks = *argument++ << 8;
                *sfx_ticks += *argument++;
            }
            break;
        case 0xC2:
            voice->instrument_bank = *argument++ & 0x0f;
            break;
        case 0xC3:
            voice->coarse_pitch_bend = *argument++;
            break;
        case 0xE7:
            voice->fine_pitch_control = *argument++;
            break;
        case 0xC4:
            voice->program_index = *argument++ & 0x7f;
            break;
        case 0xC5:
            event = *argument++;
            voice->pitch_lfo_depth = snd_pitch_lfo_ptr[event];
            break;
        case 0xC6:
            voice->volume = *argument++;
            break;
        case 0xC7:
            voice->pan_override = *argument++;
            break;
        case 0xC8:
            voice->expression = *argument++;
            break;
        case 0xC9:
            voice->saved_portamento_step = voice->portamento_step;
            event = *argument++;
            if (event) {
                voice->portamento_step = (event + 1) * 2;
                voice->saved_portamento_step = voice->portamento_step;
            } else {
                voice->status &= ~0x02;
                voice->portamento_step = 0;
            }
            break;
        case 0xCA:
            if (!voice->loop_latch) {
                argument = voice->origin;
                voice->loop_latch = 1;
            }
            break;
        case 0xCB:
            if (voice->loop_latch) {
                voice->status |= 0x40;
                return;
            }
            break;
        case 0xCD:
            if (voice->loop_latch) {
                relative = (s8)*argument++ * 0x100;
                relative += (s8)*argument++;
                argument += relative;
                voice->loop_latch = 1;
            } else {
                argument += 2;
            }
            break;
        case 0xCC:
            if (!voice->loop_latch) {
                relative = (s8)argument[0] * 0x100 + argument[1] + 2;
                argument += relative;
                voice->loop_latch = 1;
            } else {
                argument += 2;
            }
            break;
        case 0xCE:
            relative = (s8)*argument++;
            relative <<= 8;
            relative |= *argument++;
            argument += relative;
            break;
        case 0xCF:
            argument = bgm_voice[*argument].origin;
            break;
        case 0xD0:
        case 0xD1:
        case 0xD2:
        case 0xD3:
            voice->loop_cursor[event - 0xd0] = argument;
            break;
        case 0xD4:
        case 0xD5:
        case 0xD6:
        case 0xD7:
            loop_index = event - 0xd4;
            if (voice->loop_count[loop_index]) {
                voice->loop_count[loop_index]--;
                if (voice->loop_count[loop_index]) {
                    argument = voice->loop_cursor[loop_index];
                } else {
                    argument++;
                }
            } else {
                voice->loop_count[loop_index] = *argument;
                argument = voice->loop_cursor[loop_index];
            }
            break;
        case 0xD8:
        case 0xD9:
        case 0xDA:
        case 0xDB:
            skip_index = event - 0xd8;
            if (voice->loop_count[skip_index] == 1) {
                voice->loop_count[skip_index] = 0;
                relative = (argument[0] << 8) + argument[1];
                argument += 2;
                argument += relative;
            } else {
                argument += 2;
            }
            break;
        case 0xDC:
            voice->transpose = (s8)*argument++;
            break;
        case 0xDD:
            voice->transpose += (s8)*argument++;
            break;
        case 0xDE:
            voice->volume_offset = (s8)*argument++;
            break;
        case 0xDF:
            voice->volume_offset += (s8)*argument++;
            break;
        case 0xE0:
            if (*argument++) {
                voice->status |= 0x01;
            } else {
                voice->status &= ~0x01;
            }
            break;
        case 0xE1:
            event = *argument++;
            voice->lfo_rate = snd_lfo_rate_ptr[event];
            break;
        case 0xE2:
            event = *argument++;
            voice->volume_lfo_depth = snd_vol_lfo_ptr[event];
            break;
        case 0xE3:
            voice->priority_flags = *argument++;
            break;
        case 0xE4:
        case 0xE5:
            argument += 2;
            break;
        case 0xE6:
            argument++;
            break;
        case 0xFF:
            voice->status |= 0x40;
            if (!is_bgm) {
                if (!(paired_bgm_voice->status & event_mask)) {
                    paired_bgm_voice->restart_pending = 1;
                    if (!(paired_bgm_voice->patch->sample_index & 0x8000)) {
                        paired_bgm_voice->envelope_level = 0;
                        paired_bgm_voice->envelope_phase = 0;
                    }
                }
            }
            automation->mode = -1;
            return;
        default:
            break;
        }
    } else {
        u8** bank;
        u16* entry;
        note_resolved = 1;
        voice->velocity = (event & 0x3f) << 1;
        note = *argument & 0x7f;
        bank = snd_bank_tbl;
        bank = bank + voice->instrument_bank;
        if (*bank != 0) {
            entry = (u16*)*bank;
            entry = entry + voice->program_index;
            if (*entry) {
                patch = (SNDPATCH*)(*entry + *bank);
                for (;;) {
                    if (patch->note_ceiling == -1) {
                        patch = 0;
                        break;
                    } else if ((s16)note <= patch->note_ceiling) {
                        break;
                    }
                    patch++;
                }
                if (patch) {
                    voice->patch = patch;
                    voice->sample = snd_sample_tbl;
                    voice->sample += voice->patch->sample_index & 0x7FFF;
                    voice->decoded_pitch = (s16)(((note - voice->sample->base_pitch + voice->transpose + 7) << 8) + event_mask + voice->patch->pitch_bias);
                    voice->attack_peak = voice->velocity << 8;
                    voice->sustain_level = ((u16)(voice->patch->velocity_scale + 1) * voice->attack_peak) >> 7;
                    voice->attack_rate = sound_envelope_rate(voice->attack_peak, voice->patch->attack_curve, snd_attack_ptr);
                    voice->attack_rate = (voice->attack_rate * (u16)(voice->velocity + 1)) >> 7;
                    voice->decay_rate = sound_envelope_rate(voice->attack_peak, voice->patch->decay_curve, snd_decay_ptr);
                    voice->release_rate = sound_envelope_rate(voice->sustain_level, voice->patch->release_curve, snd_decay_ptr);
                    voice->note_event_pending = 1;
            } else {
                    note_resolved = 0;
                }
            } else {
                note_resolved = 0;
            }
        } else {
            note_resolved = 0;
        }
        if (note_resolved) {
            if (voice->tie) {
                voice->key_on_pending = 0;
            } else {
                voice->key_on_pending = 1;
            }
            if (*argument++ & event_mask) {
                voice->duration_enabled = 0;
                voice->tie = 1;
            } else {
                voice->duration_enabled = 1;
                voice->tie = 0;
            }
        } else {
            voice->note_event_pending = 0;
            argument++;
            voice->duration_enabled = 0;
            voice->key_on_pending = 0;
            voice->tie = 0;
        }
        consumed = midi_vlq_decode_leading(argument, &ticks);
        ticks <<= 8;
        voice->note_ticks = ticks;
        argument += consumed;
    }
    consumed = midi_vlq_decode_while(argument, &ticks);
    ticks <<= 8;
    voice->event_ticks = voice->event_ticks + ticks;
    argument += consumed;
    voice->cursor = argument;
    if (ticks <= 0) {
        goto next_event;
    }
    voice->status |= 0x20;
    return;
}

#endif
