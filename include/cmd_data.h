/*
 * CMD_DATA.H  Command records: the format of the pl_cmd_list tables
 *
 * Each fighter has 48 command slots (pl_cmd_list).  A slot's record is an array of s16:
 *
 *   header (CMD_HEAD_WORDS words, copied into WORK_CP by cmd_data_set)
 *     reset         frames a completed command stays set in waza_flag, waiting for its move to
 *                   start (command_ok_move counts it down); CMD_RESET for most records
 *     dead, dead2   input words (sw_new: the lever and buttons held this frame) which abandon
 *                   the command while it is entered (dead_lvr_check); 0: none.  CMD_LV_UP:
 *                   holding up (a jump) drops a special move
 *     rno[4]        routine_no[2] of the move started by each strength
 *     btix          the WORK_CP switch word tested for the buttons, CMD_BT_*
 *     exdt[4]       the buttons of each strength: a mask of CMD_SW_* buttons, any one of which will
 *                   do; with CMD_EX_ALL, all of them together
 *
 *   steps (4 words each; check_init and check_next load them into the slot's WAZA_WORK)
 *     ck            the check routine, CK_*: an index into chk_move_jp
 *     time          w_int: frames allowed (counted down before each test)
 *     prm           free1 and free2: a count or time, as each check routine reads it
 *     sw            w_lvr: the lever or button word the step waits for
 *
 *   CMD_END after the last step.
 *
 * Lever words are relative to the facing direction (pl_lvr_set swaps left and right).
 * CMD_LV_EXACT asks for exactly the low four lever bits; without it a step accepts any of the
 * given bits (CK_LEVER: on a new lever press), and 0 asks for neutral.  An exact diagonal is a
 * valid request.
 */

#ifndef CMD_DATA_H
#define CMD_DATA_H

#define CMD_SLOTS       48          /* command slots per fighter */
#define CMD_HEAD_WORDS  12
#define CMD_RESET       12          /* reset: the usual wait for the move to start */

/* lever bits of the command input words */
#define CMD_LV_NEUTRAL  0x0000
#define CMD_LV_UP       0x0001
#define CMD_LV_DOWN     0x0002
#define CMD_LV_FORWARD  0x0004
#define CMD_LV_BACK     0x0008
#define CMD_LV_MASK     0xF
#define CMD_LV_EXACT    0x8000      /* step word: the lever must be exactly the low four bits */

/* button bits of the command input words (SHOT1-SHOT6, as the lever and button word has them) */
#define CMD_SW_LP       0x0010
#define CMD_SW_MP       0x0020
#define CMD_SW_HP       0x0040
#define CMD_SW_LK       0x0080
#define CMD_SW_MK       0x0100
#define CMD_SW_HK       0x0200
#define CMD_SW_PUNCH    0x70
#define CMD_SW_KICK     0x380
#define CMD_SW_SHOT     0x3F0       /* all six buttons */
#define CMD_LVSW_ALL    0x3FF   /* the lever and all six buttons */

/* check routines (chk_move_jp) */
#define CK_INIT          0  /* check_init: reload the first step */
#define CK_LEVER         1  /* check_0: the lever word within time */
#define CK_CHARGE        2  /* check_1: hold the lever prm frames, then let go */
#define CK_HOLD          3  /* check_2: hold all the buttons prm frames, then let go */
#define CK_SHOT_HOLD     4  /* check_3: let go of sw buttons, each held time frames */
#define CK_RENDA         5  /* check_4: one punch (sw = CMD_SW_LP) or kick five times */
#define CK_PRESS         6  /* check_5: press exactly sw */
#define CK_TURN          7  /* check_6: the four directions in turn, either way round (rot_lvr_tbl_r/_l) */
#define CK_SHOT_P        8  /* check_7 for the punches */
#define CK_SHOT_K        9  /* check_7 for the kicks */
#define CK_LEVER_CHANGE 10  /* check_9: the next lever change must be sw */
#define CK_PARRY        11  /* check_10: tap the lever to sw (parry) */
#define CK_BACK_DOWN    12  /* check_11: back, then down */
#define CK_PARRY_CHANGE 13  /* check_12: as CK_PARRY, on any lever change rather than a new press */
#define CK_UKEMI        14  /* check_13: recovery (ukemi) input; command_ok keeps it active */
#define CK_RENDA3       15  /* check_14: three punch (sw = CMD_SW_LP) or kick presses in time */
#define CK_LEVER_COUNT  16  /* check_15: the lever word on prm frames within time */
#define CK_PRESS_P      17  /* check_16 for the punches: sw of them pressed */
#define CK_PRESS_K      18  /* check_16 for the kicks */
#define CK_LEVER_REPEAT 19  /* check_18: set the command each time the lever is moved to sw */
#define CK_LEVER_SET    20  /* check_19: set the command and go on to the next step */
#define CK_NONE         21  /* check_20: never completes */
#define CK_LEVER_PRESS  22  /* check_21: the lever moved to sw within time */
#define CK_ROTATE       23  /* check_22: all eight directions within time; completes the command */
#define CK_PARRY_STRICT 24  /* check_23: parry tap which a wrong direction abandons */
#define CK_LEVER_NEW    25  /* check_24: newly pressed lever bits within time */
#define CK_LEVER_HELD   26  /* check_25: the lever word within time, no new press needed */
#define CMD_END         27

/* btix: the WORK_CP switch word (as a u16 index) */
#define CMD_BT_NOW      3           /* sw_now */
#define CMD_BT_CHG      5           /* sw_chg */
#define CMD_BT_NONE     0x4000      /* no buttons */

/* exdt */
#define CMD_EX_ALL      0x1000      /* all the masked buttons together (a chord), not any one */

/* the usual strength sets: S, M, L and all three together */
#define CMD_EX_PUNCHES  CMD_SW_LP, CMD_SW_MP, CMD_SW_HP, CMD_EX_ALL | CMD_SW_PUNCH
#define CMD_EX_KICKS    CMD_SW_LK, CMD_SW_MK, CMD_SW_HK, CMD_EX_ALL | CMD_SW_KICK

/* rno[4] when every strength starts the same routine (each fighter's routine names are in cmd_data.c) */
#define CMD_WAZA(rno)           (rno), (rno), (rno), (rno)

#define CMD_EXACT(lv)           (s16)(CMD_LV_EXACT | (lv))
#define CMD_STEP(ck, time, prm, sw)     (ck), (time), (prm), (sw)
#define CMD_LEVER(time, lv)     CK_LEVER, (time), 0, CMD_EXACT(lv)
#define CMD_LEVER_ANY(time, lv) CK_LEVER, (time), 0, (lv)

#endif
