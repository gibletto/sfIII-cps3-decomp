/*
 * SNDSEQ.H  the sound sequence language (snd_seq.c), as the sound driver reads it (sound_voice.c)
 *
 * A sequence starts with a byte: 0 for music, otherwise a sound effect's priority. Then TRK: the offset of
 * each of the 16 tracks from the sequence's start (0: no track). A track is a delay, then events, each but
 * the unconditional jumps followed by the delay to the next event (W: 0 to 3 bytes of 7 bits, most
 * significant first; no bytes for none), in ticks at the tempo.
 *
 *   N(vel, key), L(dur)   a note: velocity 0-63, key 0-127 (NT: tied into the next note), then its length
 *                         (L1-L3: 1 to 3 bytes, a continued number, bit 7 on all but the last)
 *   TEMPO(t)              ticks per frame (x 1/256)          BANK(b)   instrument bank (snd_bank_rom_tbl)
 *   PROG(p)               program in the bank                VOL(v) EXPR(v)  volume, expression
 *   PAN(p)                pan when the patch has none (0 left, 0x40 centre, 0x7F right)
 *   BEND(s)               coarse pitch bend                  PORTA(n)  portamento speed (0 off)
 *   PLFO(d) VLFO(d)       pitch / volume LFO depth           LFO_RATE(r)  LFO speed
 *   LFO_SYNC(on)          restart the LFO with every note    FINE(v)   fine pitch (0x40 = none)
 *   KEY(s) KEY_ADD(s)     transpose in semitones             TUNE(s) TUNE_ADD(s)  fine tune
 *   PRIO(p)               the effect's priority              STATUS(i, v)  gSeqStatus[i] = v, for the game
 *   REPEAT                play the track again from its start, once; END_REPEAT: on that repeat, stop here
 *   JUMP(r)               jump r bytes from after it         JUMP_TRACK(n)  go to the start of music track n
 *   JUMP1(r) JUMP2(r)     jump the first time through / on the repeat (see sound_voice.c for the offsets)
 *   LOOP_START(n), LOOP(n, count), LOOP_EXIT(n, r)   loops 0-3: play back to LOOP_START count times; LOOP_EXIT
 *                         jumps out on the last pass
 *   END                   the end of the track
 */

#ifndef SNDSEQ_H
#define SNDSEQ_H

#include "seqop.h"

#define SEQ_MUSIC           0x00
#define TRK(off)            (u8)((off) >> 8), (u8)(off)

#define N(vel, key)         (u8)(SEQ_NOTE | (vel)), (u8)(key)
#define NT(vel, key)        (u8)(SEQ_NOTE | (vel)), (u8)(0x80 | (key))
#define L1(d)               (u8)(d)
#define L2(d)               (u8)(0x80 | ((d) >> 7)), (u8)((d) & 0x7F)
#define L3(d)               (u8)(0x80 | ((d) >> 14)), (u8)(0x80 | (((d) >> 7) & 0x7F)), (u8)((d) & 0x7F)
#define W1(t)               (u8)(t)
#define W2(t)               (u8)((t) >> 7), (u8)((t) & 0x7F)
#define W3(t)               (u8)((t) >> 14), (u8)(((t) >> 7) & 0x7F), (u8)((t) & 0x7F)

#define NOP                 SEQ_NOP
#define TEMPO(t)            SEQ_TEMPO, (u8)((t) >> 8), (u8)(t)
#define BANK(b)             SEQ_BANK, (u8)(b)
#define BEND(s)             SEQ_BEND, (u8)(s)
#define PROG(p)             SEQ_PROG, (u8)(p)
#define PLFO(d)             SEQ_PLFO, (u8)(d)
#define VOL(v)              SEQ_VOL, (u8)(v)
#define PAN(p)              SEQ_PAN, (u8)(p)
#define EXPR(v)             SEQ_EXPR, (u8)(v)
#define PORTA(n)            SEQ_PORTA, (u8)(n)
#define REPEAT              SEQ_REPEAT
#define END_REPEAT          SEQ_END_REPEAT
#define JUMP1(r)            SEQ_JUMP1, (u8)((r) >> 8), (u8)(r)
#define JUMP2(r)            SEQ_JUMP2, (u8)((r) >> 8), (u8)(r)
#define JUMP(r)             SEQ_JUMP, (u8)((r) >> 8), (u8)(r)
#define JUMP_TRACK(n)       SEQ_JUMP_TRACK, (u8)(n)
#define LOOP_START(n)       (u8)(SEQ_LOOP_START + (n))
#define LOOP(n, count)      (u8)(SEQ_LOOP + (n)), (u8)(count)
#define LOOP_EXIT(n, r)     (u8)(SEQ_LOOP_EXIT + (n)), (u8)((r) >> 8), (u8)(r)
#define KEY(s)              SEQ_KEY, (u8)(s)
#define KEY_ADD(s)          SEQ_KEY_ADD, (u8)(s)
#define TUNE(s)             SEQ_TUNE, (u8)(s)
#define TUNE_ADD(s)         SEQ_TUNE_ADD, (u8)(s)
#define LFO_SYNC(on)        SEQ_LFO_SYNC, (u8)(on)
#define LFO_RATE(r)         SEQ_LFO_RATE, (u8)(r)
#define VLFO(d)             SEQ_VLFO, (u8)(d)
#define PRIO(p)             SEQ_PRIO, (u8)(p)
#define CMD_E4(a, b)        SEQ_E4, (u8)(a), (u8)(b)      /* read past, no effect */
#define CMD_E5(a, b)        SEQ_E5, (u8)(a), (u8)(b)      /* read past, no effect */
#define CMD_E6(a)           SEQ_E6, (u8)(a)               /* read past, no effect */
#define FINE(v)             SEQ_FINE, (u8)(v)
#define STATUS(i, v)        SEQ_STATUS, (u8)(i), (u8)(v)
#define CMD(c)              (u8)(c)                     /* E9-FE: no effect */
#define END                 SEQ_END

#endif
