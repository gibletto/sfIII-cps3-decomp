/*
 * SEQOP.H  sound sequence event codes, shared by the sequence data (sndseq.h) and the driver
 * (sound_voice.c). A byte below SEQ_CONTROL starts a note: SEQ_NOTE | velocity, then the key.
 */

#ifndef SEQOP_H
#define SEQOP_H

#define SEQ_NOTE        0x80        /* | velocity 0-63 */
#define SEQ_CONTROL     0xC0        /* first control event */
#define SEQ_NOP         0xC0        /* no effect */
#define SEQ_TEMPO       0xC1        /* 2 bytes: ticks per frame x 256 */
#define SEQ_BANK        0xC2        /* instrument bank */
#define SEQ_BEND        0xC3        /* coarse pitch bend */
#define SEQ_PROG        0xC4        /* program in the bank */
#define SEQ_PLFO        0xC5        /* pitch LFO depth */
#define SEQ_VOL         0xC6        /* volume */
#define SEQ_PAN         0xC7        /* pan when the patch has none */
#define SEQ_EXPR        0xC8        /* expression */
#define SEQ_PORTA       0xC9        /* portamento speed (0 off) */
#define SEQ_REPEAT      0xCA        /* play the track again, once */
#define SEQ_END_REPEAT  0xCB        /* on the repeat, stop here */
#define SEQ_JUMP1       0xCC        /* jump the first time through */
#define SEQ_JUMP2       0xCD        /* jump on the repeat */
#define SEQ_JUMP        0xCE        /* jump */
#define SEQ_JUMP_TRACK  0xCF        /* go to the start of a music track */
#define SEQ_LOOP_START  0xD0        /* + loop 0-3 */
#define SEQ_LOOP        0xD4        /* + loop 0-3, then the count */
#define SEQ_LOOP_EXIT   0xD8        /* + loop 0-3: jump out on the last pass */
#define SEQ_KEY         0xDC        /* transpose */
#define SEQ_KEY_ADD     0xDD        /* transpose by */
#define SEQ_TUNE        0xDE        /* fine tune */
#define SEQ_TUNE_ADD    0xDF        /* fine tune by */
#define SEQ_LFO_SYNC    0xE0        /* restart the LFO with every note */
#define SEQ_LFO_RATE    0xE1        /* LFO speed */
#define SEQ_VLFO        0xE2        /* volume LFO depth */
#define SEQ_PRIO        0xE3        /* the effect's priority */
#define SEQ_E4          0xE4        /* 2 bytes read past */
#define SEQ_E5          0xE5        /* 2 bytes read past */
#define SEQ_E6          0xE6        /* 1 byte read past */
#define SEQ_FINE        0xE7        /* fine pitch */
#define SEQ_STATUS      0xE8        /* gSeqStatus[i] = v */
#define SEQ_END         0xFF        /* the end of the track */

#endif
