/*
 * SOUND_VOICE_2.C  Sound voice output (reconstructed C, not built)
 *
 * These routines are built from assembler: src/sound_voice_2.src gives the arcade's bytes. This is the C
 * they were compiled from, as far as it has been reconstructed.
 * The sound driver was built with an SHC release older than any that has been found; with a modelled
 * profile of that release this C compiles to most of the same instructions, but not to the exact bytes.
 * NONMATCHING selects the routines.
 *
 * sound_note_to_pitch turns a pitch in 1/256 semitones into the chip's pitch word (snd_pitch_tbl holds one
 * octave). sound_voice_volume_compute scales an envelope level by the voice's volume, expression and level
 * offsets and the master volumes (the music also by the fade), with the chip's output curve in mono.
 * voice_process_secondary counts the voice's delays down, keys notes on (the sample's addresses into the
 * voice's chip registers) and off, runs the portamento, the envelope (attack, decay, sustain, release), the
 * LFOs and the effect pan ramps, and writes the voice's levels and pitch to the chip. sound_reg_write_verify
 * writes a chip register until it reads back the value.
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
s32 sound_note_to_pitch(s32 note) {
    s8 oct = 0;

    while (note >= 3072) {
        note -= 3072;
        oct++;
    }
    while (note < 0) {
        note += 3072;
        oct--;
    }
    note = *(s16*)((s32)snd_pitch_tbl + (note << 1));
    note++;
    while (oct > 0) {
        note <<= 1;
        oct--;
    }
    while (oct < 0) {
        note &= 0xFFFF;
        note = (u32)note >> 1;
        oct++;
    }
    note--;
    return note;
}



/* provisional name */
u16 sound_voice_volume_compute(u16 level, u32 pan_scale, s8 pan, SNDVOICE* v) {
    s32 a;
    s32 t;
    u32 vol;
    u16 out;
    s32 comp;
    SOUND_CTRL ctrl;
    a = v->volume * ((vol = v->expression) ? vol + 1 : vol) * 2;
    a = (a * ((v->volume_offset + 64) & 127)) >> 6;
    a = (a * ((v->patch->volume_bias + 64) & 127)) >> 6;
    t = a * ((snd_master_vol + 64) & 127);
    t >>= 6;
    if (!v->priority_flags) {
        t = (t * ((bgm_master_vol + 64) & 127)) >> 6;
    }
    out = (level * (t + 1)) >> 15;
    t = (s16)((out * pan_scale) >> 16) + (pan * 256) + out;
    if (t > 0x7FFF) {
        out = 0x7FFF;
    } else if (t < 0) {
        out = 0;
    } else {
        out = t;
    }
    ctrl = snd_ctrl;
    if (ctrl.bit.stereo) {
        if (!v->priority_flags) {
            out = (out * (u16)((u32)snd_fade_level >> 8)) >> 7;
        }
        return out;
    } else {
        if (out <= 0x1000) {
            comp = out << 2;
        } else if (out <= 0x2000) {
            comp = (out << 1) + 0x2000;
        } else if (out <= 0x4000) {
            comp = (out >> 1) + 0x5000;
        } else {
            comp = (out >> 2) + 0x6000;
        }
        if (comp >= 0x8000) {
            comp = 0x7FFF;
        }
        return comp << 1;
    }
}



/* loads the voice's sample addresses into its hardware voice */
#define VOICE_LOAD_SAMPLE(regs, voice) \
    do { \
        u32 bias; \
        sound_reg_write_verify((volatile s16*)&(regs)->sample_control, 0); \
        bias = snd_wave_bias; \
        sound_reg_write_verify((volatile s16*)&(regs)->sample_start_low, (u16)(voice)->sample->start); \
        sound_reg_write_verify((volatile s16*)&(regs)->sample_start_high, (u16)((voice)->sample->start >> 16) + bias); \
        sound_reg_write_verify((volatile s16*)&(regs)->sample_loop_low, (u16)(voice)->sample->loop); \
        sound_reg_write_verify((volatile s16*)&(regs)->sample_loop_high, (u16)((voice)->sample->loop >> 16) + bias); \
        sound_reg_write_verify((volatile s16*)&(regs)->sample_end_low_a, (u16)(voice)->sample->end); \
        sound_reg_write_verify((volatile s16*)&(regs)->sample_end_low_b, (u16)(voice)->sample->end); \
        sound_reg_write_verify((volatile s16*)&(regs)->sample_end_high_a, (u16)((voice)->sample->end >> 16) + bias); \
        sound_reg_write_verify((volatile s16*)&(regs)->sample_end_high_b, (u16)((voice)->sample->end >> 16) + bias); \
        sound_reg_write_verify((volatile s16*)&(regs)->sample_control, 0); \
        sound_reg_write_verify((volatile s16*)&(regs)->sample_start_low, (u16)(voice)->sample->start); \
        sound_reg_write_verify((volatile s16*)&(regs)->sample_start_high, (u16)((voice)->sample->start >> 16) + bias); \
        if ((voice)->sample->loop == (voice)->sample->end) { \
            sound_reg_write_verify((volatile s16*)&(regs)->sample_loop_enable, 0); \
        } else { \
            sound_reg_write_verify((volatile s16*)&(regs)->sample_loop_enable, 1); \
        } \
    } while (0)

/* provisional name */
void voice_process_secondary(SNDVOICE* voice, u8 voice_index, u8 is_bgm) {
    u8 owns_hardware_voice = 1;
    SNDREGS* regs;
    s32 next;
    u32 depth;
    s32 step;
    u8 pan;
    u32 patch_pan;
    s32 inverse;
    s8 output_pan;
    s8 key_state_changed = 0;
    if (is_bgm && !(se_voice[voice_index].status & 0x80)) {
        owns_hardware_voice = 0;
    }
    regs = &((SNDREGS*)SOUND_REG)[voice_index];
    if (voice->status & 0x80) {
        if (is_bgm && owns_hardware_voice) {
            snd_key_on_reg &= ~(u16)(1 << voice_index);
        }
        return;
    }
    if (is_bgm) {
        voice->event_ticks -= bgm_tick_step;
    } else {
        voice->event_ticks -= se_tick_step[voice_index];
    }
    if (voice->duration_enabled) {
        if (is_bgm) {
            voice->note_ticks -= bgm_tick_step;
        } else {
            voice->note_ticks -= se_tick_step[voice_index];
        }
    }
    if (voice->event_ticks <= 0) {
        voice->status &= ~0x20;
    }
    if (voice->note_ticks <= 0 && voice->duration_enabled) {
        voice->duration_enabled = 0;
        if (owns_hardware_voice) {
            sound_reg_write_verify(
                (volatile s16*)&regs->sample_loop_enable, 0);
        }
        if (voice->envelope_phase != 4) {
            voice->envelope_phase = 4;
            voice->forced_release_rate =
                (u16)sound_envelope_rate(voice->envelope_level,
                                   (u8)voice->patch->forced_release_curve,
                                   snd_decay_ptr);
        }
    }
    if (voice->note_event_pending) {
        voice->note_event_pending = 0;
        voice->current_pitch = voice->target_pitch;
        voice->target_pitch = voice->decoded_pitch;
        if (voice->key_on_pending) {
            voice->key_on_pending = 0;
            voice->envelope_level = 0;
            if (owns_hardware_voice) {
                snd_key_on_reg &= ~(u16)(1 << voice_index);
                VOICE_LOAD_SAMPLE(regs, voice);
            }
            if (voice->portamento_step) {
                voice->status |= 0x02;
            } else {
                voice->status &= ~0x02;
                voice->current_pitch = voice->target_pitch;
            }
            voice->envelope_phase = 1;
            if (voice->status & 0x01) {
                voice->lfo_phase_flags &= 0xfc;
                voice->pitch_lfo = 0;
                voice->volume_lfo = 0;
            }
        } else {
            if (voice->portamento_step) {
                voice->status |= 0x02;
            } else {
                voice->status &= ~0x02;
                voice->current_pitch = voice->target_pitch;
            }
            voice->envelope_phase = 3;
        }
        key_state_changed = 1;
    }
    if (is_bgm && voice->restart_pending && owns_hardware_voice) {
        voice->restart_pending = 0;
        snd_key_on_reg &= ~(u16)(1 << voice_index);
        VOICE_LOAD_SAMPLE(regs, voice);
        key_state_changed = 1;
    }
    if (voice->status & 0x40) {
        if (!voice->envelope_level) {
            voice->status |= 0x80;
            voice->priority_flags = 0;
            return;
        } else {
            voice->envelope_phase = 4;
            if (owns_hardware_voice) {
                sound_reg_write_verify(
                    (volatile s16*)&regs->sample_loop_enable, 0);
            }
        }
    }
    if ((voice->status & 0x02) &&
        voice->current_pitch != voice->target_pitch) {
        if (voice->current_pitch > voice->target_pitch) {
            voice->current_pitch -= voice->portamento_step;
            if (voice->current_pitch <= voice->target_pitch) {
                voice->current_pitch = voice->target_pitch;
            }
        } else {
            voice->current_pitch += voice->portamento_step;
            if (voice->current_pitch >= voice->target_pitch) {
                voice->current_pitch = voice->target_pitch;
            }
        }
    }
    switch (voice->envelope_phase) {
    case 0:
        break;
    case 1: {
        u32 level = voice->envelope_level + voice->attack_rate;
        u32 peak = voice->attack_peak;
        if (level < peak) {
            voice->envelope_level = level;
        } else {
            voice->envelope_level = peak;
            voice->envelope_phase = 2;
        }
        break;
    }
    case 2: {
        u32 sustain = voice->sustain_level;
        u32 decay = voice->decay_rate;
        if (sustain + decay < voice->envelope_level) {
            voice->envelope_level = voice->envelope_level - decay;
        } else {
            voice->envelope_level = sustain;
            voice->envelope_phase = 3;
        }
        break;
    }
    case 3: {
        u32 rate = voice->release_rate;
        u32 level = voice->envelope_level;
        if (level > rate) {
            level = level - rate;
            voice->envelope_level = level;
        } else {
            voice->envelope_level = 0;
            voice->envelope_phase = 0;
        }
        break;
    }
    case 4: {
        u32 level;
        u32 rate = voice->forced_release_rate;
        if ((level = voice->envelope_level) > rate) {
            voice->envelope_level = (u16)(level - rate);
        } else {
            voice->envelope_level = 0;
            voice->envelope_phase = 0;
            if (is_bgm && owns_hardware_voice) {
                snd_key_on_reg &= ~(u16)(1 << voice_index);
            }
        }
    }
    }
    if (voice->lfo_rate) {
        if (voice->pitch_lfo_depth) {
            depth = voice->pitch_lfo_depth;
            step = (s32)(depth * voice->lfo_rate);
            depth <<= 16;
            if (voice->lfo_phase_flags & 0x01) {
                if ((s32)(step - depth) < voice->pitch_lfo) {
                    voice->pitch_lfo -= step;
                } else {
                    voice->pitch_lfo = -(s32)depth;
                    voice->lfo_phase_flags &= ~0x01;
                }
            } else if ((s32)(depth - step) > voice->pitch_lfo) {
                voice->pitch_lfo += step;
            } else {
                    voice->pitch_lfo = (s32)depth;
                voice->lfo_phase_flags |= 0x01;
            }
        }
        if (voice->volume_lfo_depth) {
            step = (s16)((voice->volume_lfo_depth * voice->lfo_rate) >> 16);
            depth = voice->volume_lfo_depth;
            if (voice->lfo_phase_flags & 0x02) {
                if ((s32)(step - depth) < voice->volume_lfo) {
                    voice->volume_lfo -= step;
                } else {
                    voice->volume_lfo = -(s32)depth;
                    voice->lfo_phase_flags &= ~0x02;
                }
            } else if ((s32)(depth - step) > voice->volume_lfo) {
                voice->volume_lfo += step;
            } else {
                voice->volume_lfo = (s32)depth;
                voice->lfo_phase_flags |= 0x02;
            }
        }
    } else {
        voice->pitch_lfo = 0;
        voice->volume_lfo = 0;
    }
    if (!is_bgm && se_pan_ramp[voice_index].mode != -1 && se_pan_ramp[voice_index].mode != 0) {
        next = se_pan_ramp[voice_index].current + se_pan_ramp[voice_index].step;
        if (se_pan_ramp[voice_index].step < 0) {
            if (se_pan_ramp[voice_index].target < next) {
                se_pan_ramp[voice_index].current = (s16)next;
            } else {
                se_pan_ramp[voice_index].current = se_pan_ramp[voice_index].target;
                if (se_pan_ramp[voice_index].mode == 1) {
                    se_voice[voice_index].status |= 0x40;
                }
                se_pan_ramp[voice_index].mode = 0;
            }
        } else if (next < se_pan_ramp[voice_index].target) {
            se_pan_ramp[voice_index].current = (s16)next;
        } else {
            se_pan_ramp[voice_index].current = se_pan_ramp[voice_index].target;
            if (se_pan_ramp[voice_index].mode == 1) {
                se_voice[voice_index].status |= 0x40;
            }
            se_pan_ramp[voice_index].mode = 0;
        }
    }
    if (!owns_hardware_voice) {
        return;
    }
    output_pan = ((u8)sound_sample_submit_work4);
    if (snd_stereo) {
        if (!is_bgm && se_pan_ramp[voice_index].mode != -1) {
            pan = se_pan_ramp[voice_index].current >> 8;
        } else {
            patch_pan = voice->patch->pan;
            pan = (patch_pan == 0xff) ? voice->pan_override : patch_pan;
        }
        inverse = (0x7f - pan) & 0xffff;
        if (is_bgm) {
            if (pan < 0x40) {
                *(u16*)&regs->volume_right = (u16)sound_voice_volume_compute(
                    (pan * voice->envelope_level) >> 6,
                    voice->volume_lfo, output_pan, voice);
                *(u16*)&regs->volume_left = (u16)sound_voice_volume_compute(
                    voice->envelope_level, voice->volume_lfo,
                    ((u8)sound_sample_submit_work4), voice);
            } else {
                *(u16*)&regs->volume_left = (u16)sound_voice_volume_compute(
                    (inverse * voice->envelope_level) >> 6,
                    voice->volume_lfo, output_pan, voice);
                *(u16*)&regs->volume_right = (u16)sound_voice_volume_compute(
                    voice->envelope_level, voice->volume_lfo,
                    ((u8)sound_sample_submit_work4), voice);
            }
        } else {
            if (pan < 0x40) {
                *(u16*)&regs->volume_right = (u16)sound_voice_volume_compute(
                    (pan * voice->envelope_level) >> 6,
                    voice->volume_lfo, 0, voice);
                *(u16*)&regs->volume_left = (u16)sound_voice_volume_compute(
                    voice->envelope_level, voice->volume_lfo, 0, voice);
            } else {
                *(u16*)&regs->volume_left = (u16)sound_voice_volume_compute(
                    (inverse * voice->envelope_level) >> 6,
                    voice->volume_lfo, 0, voice);
                *(u16*)&regs->volume_right = (u16)sound_voice_volume_compute(
                    voice->envelope_level, voice->volume_lfo, 0, voice);
            }
        }
    } else {
        if (is_bgm) {
            *(u16*)&regs->volume_right = (u16)sound_voice_volume_compute(
                voice->envelope_level, voice->volume_lfo, output_pan, voice);
            *(u16*)&regs->volume_left = (u16)sound_voice_volume_compute(
                voice->envelope_level, voice->volume_lfo,
                ((u8)sound_sample_submit_work4), voice);
        } else {
            *(u16*)&regs->volume_left = (u16)sound_voice_volume_compute(
                voice->envelope_level, voice->volume_lfo, 0, voice);
            *(u16*)&regs->volume_right = (u16)sound_voice_volume_compute(
                voice->envelope_level, voice->volume_lfo, 0, voice);
        }
    }
    if (is_bgm) {
        *(u16*)&regs->pitch = (u16)sound_note_to_pitch(
            (s16)((u32)voice->pitch_lfo >> 16) + voice->current_pitch +
            ((voice->coarse_pitch_bend * 0xc00) >> 7) +
            (((voice->fine_pitch_control - 0x40) * 0x100) >> 6) +
            voice_state_init_pair_work);
    } else {
        *(u16*)&regs->pitch = (u16)sound_note_to_pitch(
            (s16)((u32)voice->pitch_lfo >> 16) + voice->current_pitch +
            ((voice->coarse_pitch_bend * 0xc00) >> 7) +
            (((voice->fine_pitch_control - 0x40) * 0x100) >> 6));
    }
    if (key_state_changed && owns_hardware_voice) {
        snd_key_on_reg |= (u16)(1u << voice_index);
    }
}

/* provisional name */
void sound_reg_write_verify(s16 *reg, u16 value)
{
    *reg = value;
    while (1) {
        if (value == (u16)*reg) {
            break;
        } else {
            *reg = value;
        }
    }
}

#endif
