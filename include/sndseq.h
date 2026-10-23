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

#define SEQ_MUSIC           0x00
#define TRK(off)            (u8)((off) >> 8), (u8)(off)

#define N(vel, key)         (u8)(0x80 | (vel)), (u8)(key)
#define NT(vel, key)        (u8)(0x80 | (vel)), (u8)(0x80 | (key))
#define L1(d)               (u8)(d)
#define L2(d)               (u8)(0x80 | ((d) >> 7)), (u8)((d) & 0x7F)
#define L3(d)               (u8)(0x80 | ((d) >> 14)), (u8)(0x80 | (((d) >> 7) & 0x7F)), (u8)((d) & 0x7F)
#define W1(t)               (u8)(t)
#define W2(t)               (u8)((t) >> 7), (u8)((t) & 0x7F)
#define W3(t)               (u8)((t) >> 14), (u8)(((t) >> 7) & 0x7F), (u8)((t) & 0x7F)

#define NOP                 0xC0
#define TEMPO(t)            0xC1, (u8)((t) >> 8), (u8)(t)
#define BANK(b)             0xC2, (u8)(b)
#define BEND(s)             0xC3, (u8)(s)
#define PROG(p)             0xC4, (u8)(p)
#define PLFO(d)             0xC5, (u8)(d)
#define VOL(v)              0xC6, (u8)(v)
#define PAN(p)              0xC7, (u8)(p)
#define EXPR(v)             0xC8, (u8)(v)
#define PORTA(n)            0xC9, (u8)(n)
#define REPEAT              0xCA
#define END_REPEAT          0xCB
#define JUMP1(r)            0xCC, (u8)((r) >> 8), (u8)(r)
#define JUMP2(r)            0xCD, (u8)((r) >> 8), (u8)(r)
#define JUMP(r)             0xCE, (u8)((r) >> 8), (u8)(r)
#define JUMP_TRACK(n)       0xCF, (u8)(n)
#define LOOP_START(n)       (u8)(0xD0 + (n))
#define LOOP(n, count)      (u8)(0xD4 + (n)), (u8)(count)
#define LOOP_EXIT(n, r)     (u8)(0xD8 + (n)), (u8)((r) >> 8), (u8)(r)
#define KEY(s)              0xDC, (u8)(s)
#define KEY_ADD(s)          0xDD, (u8)(s)
#define TUNE(s)             0xDE, (u8)(s)
#define TUNE_ADD(s)         0xDF, (u8)(s)
#define LFO_SYNC(on)        0xE0, (u8)(on)
#define LFO_RATE(r)         0xE1, (u8)(r)
#define VLFO(d)             0xE2, (u8)(d)
#define PRIO(p)             0xE3, (u8)(p)
#define CMD_E4(a, b)        0xE4, (u8)(a), (u8)(b)      /* read past, no effect */
#define CMD_E5(a, b)        0xE5, (u8)(a), (u8)(b)      /* read past, no effect */
#define CMD_E6(a)           0xE6, (u8)(a)               /* read past, no effect */
#define FINE(v)             0xE7, (u8)(v)
#define STATUS(i, v)        0xE8, (u8)(i), (u8)(v)
#define CMD(c)              (u8)(c)                     /* E9-FE: no effect */
#define END                 0xFF

#endif
