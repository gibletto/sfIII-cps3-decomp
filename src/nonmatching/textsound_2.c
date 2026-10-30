/*
 * TEXTSOUND_2.C  Sound driver interface (reconstructed C, not built)
 *
 * These routines are built from assembler: src/textsound_2_x1.src and src/textsound_2_x2.src give the
 * arcade's bytes. This is the C they were compiled from, as far as it has been reconstructed.
 * The sound driver was built with an SHC release older than any that has been found; with a modelled
 * profile of that release this C compiles to most of the same instructions, but not to the exact bytes.
 * NONMATCHING selects the routines.
 *
 * sound_init resets the sound chip and the driver; sound_request and sound_seq_start start a music or
 * effect sequence on the voices; sound_request_pan starts one with a pan ramp; bgm_stop, bgm_pause and
 * bgm_resume stop, hold and continue the music; sound_fade_in_submit and bgm_fade_out fade the master level
 * in and out; sound_reg_level_set sets the music's pitch and level offsets; sound_driver_init and
 * se_voice_stop / se_voice_stop_all stop voices; sound_driver_tick, run once a frame, runs the fades and
 * every voice through sound_voice.c and sound_voice_2.c. The other routines of the module are C that builds
 * the arcade's bytes: sound_driver_version and sound_sample_bank_set (src/textsound_2.c, with the driver's
 * work) and sound_status_read (src/sound_status.c).
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "cps3.h"

u16 sound_envelope_rate(u16 level, u8 index, const u16* table);
void voice_process_null(SNDVOICE* voice, u8 voice_index);
void voice_process_primary(SNDVOICE* voice, u8 is_bgm, u8 voice_index);
s32 sound_note_to_pitch(s32 note);
void sound_reg_write_verify(s16 *reg, u16 value);
u16 sound_voice_volume_compute(u16 level, u32 pan_scale, s8 vol_offset, SNDVOICE* v);
void voice_process_secondary(SNDVOICE* voice, u8 voice_index, u8 is_bgm);
s32 midi_vlq_decode_leading();
s32 midi_vlq_decode_while();

s32 sound_request(u16 code);
s32 sound_seq_start(u16 code, s16 ramp);
void bgm_stop(void);
void se_voice_stop(u8 ch);

#ifdef NONMATCHING

void sound_init(u8* data, SNDSAMPLE* bank_a, u8** bank_b, u8 stereo, u8 volume, u8 flag) {
    u16 init[21] = {
        3, 1, 3, 1, 3, 1, 3, 0, 2, 1, 3, 0, 2, 0, 2, 0, 2, 2, 6, 6, 2
    };
    s32 i;
    s32 n;
    volatile u16* reg;
    snd_attack_ptr = snd_attack_rate_tbl;
    snd_decay_ptr = snd_decay_rate_tbl;
    snd_lfo_rate_ptr = snd_lfo_rate_tbl;
    snd_pitch_lfo_ptr = snd_pitch_lfo_tbl;
    snd_vol_lfo_ptr = snd_vol_lfo_tbl;
    snd_sample_tbl = bank_a;
    snd_bank_tbl = bank_b;
    snd_stereo = flag;
    for (i = 0; i < 21; i++) {
        *(u16*)(EXT_SW + 0x202) = init[i];
        n = 0x100;
        while (n--) {
        }
    }
    reg = (volatile u16*)SOUND_REG;
    for (n = 0x100; n != 0; n--) {
        *reg++ = 0;
    }
    snd_ctrl.w.hi = (u16)(stereo & 1) | volume << 8 | 0x22;
    *(SOUND_CTRL*)(SOUND_REG + 0x210) = snd_ctrl;
    *(u16*)(SOUND_REG + 0x200) = 0;
    snd_seq_data = (u32*)data;
    snd_seq_max = *data++;
    snd_seq_max <<= 8;
    snd_seq_max += *data++;
    bgm_master_vol = *data++;
    bgm_master_vol_init = bgm_master_vol;
    snd_master_vol = *data;
    bgm_state = 1;
    bgm_pitch_offset = 0;
    bgm_volume_offset = 0;
    snd_fade_level = 0;
    snd_fade_speed = snd_fade_level;
    for (n = 0; n < 16; n++) {
        bgm_voice[n].status = 0xC0;
        bgm_status_save[n] = 0xC0;
    }
    for (n = 0; n < 16; n++) {
        se_voice[n].status = 0xC0;
    }
}



s32 sound_request(u16 code) {
    return sound_seq_start(code, -1);
}



s32 sound_seq_start(u16 code, s16 ramp) {
    u8* seq;
    u8* p;
    u8* track;
    u8** bank_table;
    SNDVOICE* v;
    u32 ofs;
    s32 ticks;
    s32 n;
    u16 off;
    u8 hdr;
    u8 ch;
    u8 i;
    while (code >= snd_seq_max) {
        code -= snd_seq_max;
    }
    ofs = snd_seq_data[code + 1];
    if (ofs == 0) {
        return;
    }
    seq = (u8*)snd_seq_data + ofs;
    p = seq;
    hdr = *p++;
    if (hdr == 0) {
        bgm_stop();
        for (i = 0; i < 16; i++) {
            off = *p++ << 8;
            off += *p++;
            if (off) {
                track = seq + off;
                v = &bgm_voice[i];
                v->origin = track;
                n = midi_vlq_decode_while(track, &ticks);
                ticks <<= 8;
                v->event_ticks = ticks;
                v->cursor = &track[n];
                v->status = 0x20;
                bank_table = snd_bank_tbl;
                v->patch = (SNDPATCH*)(*bank_table + *(u16*)*bank_table);
                v->sample = &snd_sample_tbl[v->patch->sample_index];
                v->note_ticks = 0;
                v->decoded_pitch = 0;
                v->target_pitch = 0;
                v->current_pitch = 0;
                v->pitch_lfo = 0;
                v->volume_lfo = 0;
                v->pitch_lfo_depth = 0;
                v->volume_lfo_depth = 0;
                v->lfo_rate = 0;
                v->envelope_level = 0;
                v->saved_portamento_step = 0;
                v->portamento_step = 0;
                v->program_index = 0;
                v->attack_peak = 0;
                v->attack_rate = 0;
                v->sustain_level = 0;
                v->decay_rate = 0;
                v->release_rate = 0;
                v->forced_release_rate = 0;
                v->loop_count[0] = 0;
                v->loop_count[1] = 0;
                v->loop_count[2] = 0;
                v->loop_count[3] = 0;
                v->loop_latch = 0;
                v->envelope_phase = 0;
                v->lfo_phase_flags = 0;
                v->priority_flags = hdr;
                v->volume = 0;
                v->velocity = 0;
                v->expression = 0x40;
                v->volume_offset = 0;
                v->transpose = 0;
                v->coarse_pitch_bend = 0;
                v->fine_pitch_control = 0x40;
                v->key_on_pending = 0;
                v->duration_enabled = 0;
                v->note_event_pending = 0;
                v->tie = 0;
                v->restart_pending = 0;
                v->pan_override = 0x40;
            } else {
                bgm_voice[i].status = 0xC0;
            }
        }
        if (!(bgm_state & 8)) {
            snd_fade_level = 0x8000;
        }
        bgm_tick_step = 0;
        bgm_state |= 2;
        return;
    } else if (!(hdr & 0x80)) {
        for (i = 0; i < 16; i++) {
            off = *p++ << 8;
            off += *p++;
            if (off) {
                if (hdr >= se_voice[i].priority_flags & 0x7F || se_voice[i].status & 0x80) {
                    track = seq + off;
                    n = midi_vlq_decode_while(track, &ticks);
                    ticks <<= 8;
                    se_voice[i].event_ticks = ticks;
                    se_voice[i].cursor = &track[n];
                    se_voice[i].status = 0;
                    bank_table = snd_bank_tbl;
                    se_voice[i].patch = (SNDPATCH*)(*bank_table + *(u16*)*bank_table);
                    se_voice[i].sample = &snd_sample_tbl[se_voice[i].patch->sample_index];
                    se_voice[i].decoded_pitch = 0;
                    se_voice[i].target_pitch = 0;
                    se_voice[i].current_pitch = 0;
                    se_voice[i].pitch_lfo = 0;
                    se_voice[i].volume_lfo = 0;
                    se_voice[i].pitch_lfo_depth = 0;
                    se_voice[i].volume_lfo_depth = 0;
                    se_voice[i].lfo_rate = 0;
                    se_voice[i].envelope_level = 0;
                    se_voice[i].saved_portamento_step = 0;
                    se_voice[i].portamento_step = 0;
                    se_voice[i].program_index = 0;
                    se_voice[i].attack_peak = 0;
                    se_voice[i].attack_rate = 0;
                    se_voice[i].sustain_level = 0;
                    se_voice[i].decay_rate = 0;
                    se_voice[i].release_rate = 0;
                    se_voice[i].forced_release_rate = 0;
                    se_voice[i].loop_count[0] = 0;
                    se_voice[i].loop_count[1] = 0;
                    se_voice[i].loop_count[2] = 0;
                    se_voice[i].loop_count[3] = 0;
                    se_voice[i].loop_latch = 0;
                    se_voice[i].envelope_phase = 0;
                    se_voice[i].pan_override = 0x40;
                    se_voice[i].lfo_phase_flags = 0;
                    se_voice[i].priority_flags = hdr;
                    se_voice[i].volume = 0;
                    bgm_voice[i].velocity = 0x7F;
                    se_voice[i].expression = 0x7F;
                    se_voice[i].volume_offset = 0;
                    se_voice[i].transpose = 0;
                    se_voice[i].coarse_pitch_bend = 0;
                    se_voice[i].fine_pitch_control = 0x40;
                    se_voice[i].key_on_pending = 0;
                    se_voice[i].duration_enabled = 0;
                    se_voice[i].note_event_pending = 0;
                    se_voice[i].tie = 0;
                    se_voice[i].pan_override = 0x40;
                    if (ramp != -1) {
                        se_pan_ramp[i].current = se_ramp_req.current;
                        se_pan_ramp[i].target = se_ramp_req.target;
                        se_pan_ramp[i].step = se_ramp_req.step;
                        se_pan_ramp[i].mode = se_ramp_req.mode;
                    } else {
                        se_pan_ramp[i].current = 0;
                        se_pan_ramp[i].target = 0;
                        se_pan_ramp[i].step = 0;
                        se_pan_ramp[i].mode = -1;
                    }
                    se_tick_step[i] = 0;
                }
            }
        }
        return;
    }
    ch = hdr & 15;
    if ((*p & 0x7F) < (se_voice[ch].priority_flags & 0x7F) && !(se_voice[ch].status & 0x80)) {
        return;
    }
    se_voice[ch].cursor = p;
    bank_table = snd_bank_tbl;
    se_voice[ch].patch = (SNDPATCH*)(*bank_table + *(u16*)*bank_table);
    se_voice[ch].sample = &snd_sample_tbl[se_voice[ch].patch->sample_index];
    se_voice[ch].envelope_level = 0;
    se_voice[ch].program_index = 0;
    se_voice[ch].attack_peak = 0;
    se_voice[ch].attack_rate = 0;
    se_voice[ch].sustain_level = 0;
    se_voice[ch].decay_rate = 0;
    se_voice[ch].release_rate = 0;
    se_voice[ch].forced_release_rate = 0;
    se_voice[ch].volume = 0;
    se_voice[ch].velocity = 0x7F;
    se_voice[ch].expression = 0x7F;
    se_voice[ch].volume_offset = 0;
    se_voice[ch].transpose = 0;
    se_voice[ch].coarse_pitch_bend = 0;
    se_voice[ch].fine_pitch_control = 0x40;
    se_voice[ch].priority_flags = *p | 0x80;
    se_voice[ch].pan_override = 0x40;
    if (ramp != -1) {
        se_pan_ramp[ch].current = se_ramp_req.current;
        se_pan_ramp[ch].target = se_ramp_req.target;
        se_pan_ramp[ch].step = se_ramp_req.step;
        se_pan_ramp[ch].mode = se_ramp_req.mode;
    } else {
        se_pan_ramp[ch].current = 0;
        se_pan_ramp[ch].target = 0;
        se_pan_ramp[ch].step = 0;
        se_pan_ramp[ch].mode = -1;
    }
    se_voice[ch].status = 0;
}



void sound_request_pan(u16 code, s16 vol_l, s16 vol_r, s16 time, s16 ramp) {
    se_ramp_req.current = vol_l << 8;
    se_ramp_req.target = vol_r << 8;
    se_ramp_req.step = (se_ramp_req.target - se_ramp_req.current) / time;
    se_ramp_req.mode = ramp;
    sound_seq_start(code, ramp);
}



void bgm_stop(void) {
    u8 i;
    if (!(bgm_state & 2)) {
        return;
    }
    for (i = 0; i < 16; i++) {
        bgm_voice[i].status = 0xC0;
    }
    bgm_state = 1;
    snd_reg_save = 0;
}



void bgm_pause(void) {
    u8 i;
    if (!(bgm_state & 2) || (bgm_state & 4)) {
        return;
    }
    snd_reg_save = *(u16*)(SOUND_REG + 0x200);
    for (i = 0; i < 16; i++) {
        bgm_status_save[i] = bgm_voice[i].status;
        bgm_voice[i].status = 0xC0;
    }
    bgm_state |= 4;
}



void bgm_resume(void) {
    u8 i;
    if (!(bgm_state & 2) || !(bgm_state & 4)) {
        return;
    }
    for (i = 0; i < 16; i++) {
        bgm_voice[i].status = bgm_status_save[i];
    }
    bgm_state &= ~4;
    *(u16*)(SOUND_REG + 0x200) |= snd_reg_save;
}



void sound_fade_in_submit(u16 code_no, u16 speed)
{
    snd_fade_level = 0;
    snd_fade_speed = speed & 0x7FFF;
    bgm_state |= 8;
    sound_request(code_no);
}



void bgm_fade_out(u16 speed)
{
    if (bgm_state & 2) {
        snd_fade_speed = speed & 0x7FFF;
        bgm_state &= ~8;
        bgm_state |= 0x10;
    }
}



void sound_reg_level_set(s16 pitch, s8 volume) {
    bgm_pitch_offset = pitch;
    bgm_volume_offset = volume;
}



void sound_driver_init(void) {
    u8 i;
    for (i = 0; i < 16; i++) {
        bgm_voice[i].status = 0xC0;
        se_voice[i].status = 0xC0;
    }
    bgm_state = 1;
    *(u16*)(SOUND_REG + 0x200) = 0;
    snd_reg_save = 0;
}



void se_voice_stop(u8 ch) {
    se_voice[ch].status = 0xC0;
}



void se_voice_stop_all(void) {
    u8 i;
    for (i = 0; i < 16; i++) {
        se_voice[i].status = 0xC0;
    }
}



void sound_driver_tick(void) {
    u32 i;
    if ((bgm_state & 8) && !(bgm_state & 4)) {
        snd_fade_level += snd_fade_speed;
        if (snd_fade_level >= 0x8000) {
            snd_fade_level = 0x8000;
            bgm_state &= ~8;
        }
    }
    if ((bgm_state & 0x10) && !(bgm_state & 4)) {
        if (snd_fade_speed >= snd_fade_level) {
            bgm_stop();
            snd_fade_level = 0;
            bgm_state &= ~0x10;
        } else {
            snd_fade_level -= snd_fade_speed;
        }
    }
    for (i = 0; i < 16; i++) {
        voice_process_primary(&bgm_voice[i], 1, i);
    }
    for (i = 0; i < 16; i++) {
        if (se_voice[i].priority_flags & 0x80) {
            voice_process_null(&se_voice[i], i);
        } else {
            voice_process_primary(&se_voice[i], 0, i);
        }
    }
    for (i = 0; i < 16; i++) {
        voice_process_secondary(&bgm_voice[i], i, 1);
    }
    for (i = 0; i < 16; i++) {
        if (!(se_voice[i].priority_flags & 0x80)) {
            voice_process_secondary(&se_voice[i], i, 0);
        }
    }
}

#endif
