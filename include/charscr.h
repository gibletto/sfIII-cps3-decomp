/*
 * CHARSCR.H  Character animation scripts: line layouts and command codes
 *
 * A script (see the <fighter>_char tables) starts with a four-word header and continues with lines
 * of cgd_type long words. check_cgd_patdat (CHARMOVE) copies a frame line into the work's cg_* fields;
 * these macros take each field as the engine uses it and pack it into the words the tables store.
 *
 * HEAD(cgd_type, pat_status, kind_of_waza, hit_range, total_paring, total_att_set, sp_tech_id)
 *
 * frame line: ctr    frames the line is shown
 *             type   line type (0xFF: keep the type; bit 7: the low bits go to cg_wca_ix, the type is 0)
 *             se     sound request (sound_effect_request[se]; 0: none), prio, flip
 *             olc    sprite parts row (olc_ix_table), jphos jump correction (jphos_table)
 *             number sprite number
 * L4 adds:    att    attack attribute row (catt_table; 0: none; negative: a new hit), hit hit_ix_table
 *             row, extdat, cancel, effect/eftype effect started on this line (effinitjptbl)
 * L6 adds:    zoom, rival caught opponent's position (rival_catch_tbl row rival - 16 + tsukami_num),
 *             add_xy step (stepxy_table offset), next_ix, status (bit 7: the pattern status is the low
 *             bits)
 *
 * CMD(code, koc, ix, pat): a command line, run through comm_jmp_tbl; the arguments are the kind,
 * index and line of a jump target, or a count, value or flag, as each command reads them.
 *
 * koc, the kind of script (the char_table index set_char_base_data fills; the debug viewer's kind):
 *   0 nmca  NORMAL     1 dmca  DAMAGE     2 caca  CATCH      3 cuca  CAUGHT     4 atca  ATTACK
 *   5 saca  SP AT      6 btca  BUTTOBI    7 exca  UNION      8 cbca  ETC        9 yuca  ETC
 * The fighters' _char.c files hold kinds 0-8, their _yuca.c files kind 9.
 */

/*
 * Script names. The debug character viewer names every script index of every kind (dbg_act_name_tbl); the
 * fighters' tables carry those names as comments. The names are the development team's romanised Japanese:
 *   S / M / L        light / medium / heavy (LP MP HP; classic: jab / strong / fierce, short / forward /
 *                    roundhouse; S PUNCH = jab)                        SP  two buttons (EX)
 *   A / B / C        a normal's far / close / lever version (waza_select: B when the opponent is
 *                    within asstbl_lv_0000's range, C for its lever command)
 *   KAGAMI           crouching (KAGAMU: crouch)
 *   V / F / B JUMP   vertical / forward / back jump                    SP JUMP  super (high) jump
 *   KAMAE            stance                   HURIMUKI  turn around    JUNBI    preparation (pre-jump etc.)
 *   DASH HUMIKOMI    forward dash (step in)   DASH TOBINOKI  back dash
 *   PARING           parry                    GUARD     block          ZUJOU    overhead
 *   TUKAMIKAKARI     throw attempt            TUKAMIHAZUSI / HAZUSARE  throw escape / escaped
 *   NOUTEN           crown of the head        TATAKI    slam           NOBASITA TE  extended arm
 *   NEKOROBI         lying down               OKIAGARI  getting up     UKEMI    recovery roll
 *   PIYO             dizzy                    TOUKETU   frozen         DENGEKI  electrocuted
 *   MOE              burning                  ASHIBARAI sweep          NOKEZORI bent back
 *   KUNOJI           doubled over             KIRIMOMI  spinning       HANEAGARI bounce
 *   ATTACK n S/M/L/SP  special move n by strength (SP AT kind)
 *   APPEAR (JUNBI)   intro (preparation)      WIN       win pose       ZANNEN   lose pose
 * Entries the viewer leaves blank say which named moves' scripts jump to them ("follow-up of"; target combos
 * and similar register the jump with CM_RJA / CM_RMJA), or "no name" when no script does (code may still
 * start them from a table).
 */

#ifndef CHARSCR_H
#define CHARSCR_H

#define HEAD(cgd, pst, kow, hrng, tpar, tatt, spt) \
    (u16)(cgd), (u16)(((pst) << 8) | (kow)), (u16)(((hrng) << 8) | (tpar)), (u16)(((tatt) << 8) | (spt))

#define L2(ctr, type, se, prio, flip, olc, jphos, number) \
    (u16)(((ctr) << 8) | (type)), (u16)(((se) << 4) | ((prio) << 2) | (flip)), \
    (u16)(((olc) << 4) | (jphos)), (u16)(number)

#define L4(ctr, type, se, prio, flip, olc, jphos, number, att, hit, extdat, cancel, effect, eftype) \
    L2(ctr, type, se, prio, flip, olc, jphos, number), \
    (u16)(att), (u16)(hit), (u16)(((extdat) << 8) | (cancel)), (u16)(((effect) << 8) | (eftype))

#define L6(ctr, type, se, prio, flip, olc, jphos, number, att, hit, extdat, cancel, effect, eftype, \
           zoom, rival, add_xy, next_ix, status) \
    L4(ctr, type, se, prio, flip, olc, jphos, number, att, hit, extdat, cancel, effect, eftype), \
    (u16)(zoom), (u16)(rival), (u16)(add_xy), (u16)(((next_ix) << 8) | (status))

#define CMD(code, koc, ix, pat) (u16)(code), (u16)(koc), (u16)(ix), (u16)(pat)

/*
 * ATTR: one attack attribute (ATTACK_ATTR, a fighter's catt_table row), each field as set_new_attnum unpacks it.
 * A frame line's att picks the row: a negative att starts a new hit (new attack number, super meter), a positive
 * one continues the current attack with that row.
 *   reaction  hit reaction of the opponent       zu       zu_flag             attr     at_attribute
 *   kezuri    chip damage class (kezuri_pow)     mkh_ix   hit effect          dipsw    option switches
 *   zuru      att_zuru                           free4    flags: bit 7 lets the hit reach the opponent's
 *             push box; bits 7 and 6 rank throws landing on the same frame (bit 6 also picks the air
 *             special damage reaction); bit 5 sets the opponent's dm_fushin; bits 0-4 divide the damage
 *             checked against a guard
 *   dir       knock-back direction               vs_id    which kinds of work the hit can reach
 *   guard     how it must be blocked             nodeath  cannot kill         buttobi  blow-away type
 *   pow       damage                             impact   hit impact          piyo     stun
 *   arts      super art gauge gain               ng_type  what the hit cannot do
 *   hs_me     hit stop of the attacker           hs_you   hit stop of the opponent
 *   hit_mark  hit spark                          dmg_mark damage mark
 */
#define ATTR(reaction, zu, attr, kezuri, mkh_ix, dipsw, zuru, free4, dir, vs_id, guard, nodeath, buttobi, \
             pow, impact, piyo, arts, ng_type, hs_me, hs_you, hit_mark, dmg_mark) \
    { (((reaction) << 8) | ((kezuri) << 4) | ((attr) << 1) | (zu)), (mkh_ix), (((zuru) << 4) | (dipsw)), (free4), \
      (((vs_id) << 4) | (dir)), (((buttobi) << 7) | ((nodeath) << 6) | (guard)), (pow), (impact), \
      (((arts) << 4) | (piyo)), (ng_type), (hs_me), (hs_you), (hit_mark), (dmg_mark) }

/* command codes: the order of comm_jmp_tbl */
#define CM_DUMMY      0   /* comm_dummy */
#define CM_ROA        1   /* comm_roa */
#define CM_END        2   /* comm_end */
#define CM_JMP        3   /* comm_jmp */
#define CM_JPSS       4   /* comm_jpss */
#define CM_JSR        5   /* comm_jsr */
#define CM_RET        6   /* comm_ret */
#define CM_SPS        7   /* comm_sps */
#define CM_SETR       8   /* comm_setr */
#define CM_ADDR       9   /* comm_addr */
#define CM_IF_L      10   /* comm_if_l */
#define CM_DJMP      11   /* comm_djmp */
#define CM_FOR       12   /* comm_for */
#define CM_NEX       13   /* comm_nex */
#define CM_FOR2      14   /* comm_for2 */
#define CM_NEX2      15   /* comm_nex2 */
#define CM_RJA       16   /* comm_rja */
#define CM_UJA       17   /* comm_uja */
#define CM_RJA2      18   /* comm_rja2 */
#define CM_UJA2      19   /* comm_uja2 */
#define CM_RJA3      20   /* comm_rja3 */
#define CM_UJA3      21   /* comm_uja3 */
#define CM_RJA4      22   /* comm_rja4 */
#define CM_UJA4      23   /* comm_uja4 */
#define CM_RJA5      24   /* comm_rja5 */
#define CM_UJA5      25   /* comm_uja5 */
#define CM_RJA6      26   /* comm_rja6 */
#define CM_UJA6      27   /* comm_uja6 */
#define CM_RJA7      28   /* comm_rja7 */
#define CM_UJA7      29   /* comm_uja7 */
#define CM_RMJA      30   /* comm_rmja */
#define CM_UMJA      31   /* comm_umja */
#define CM_MDAT      32   /* comm_mdat */
#define CM_YDAT      33   /* comm_ydat */
#define CM_MPOS      34   /* comm_mpos */
#define CM_CAFR      35   /* comm_cafr */
#define CM_CARE      36   /* comm_care */
#define CM_PSXY      37   /* comm_psxy */
#define CM_PS_X      38   /* comm_ps_x */
#define CM_PS_Y      39   /* comm_ps_y */
#define CM_PAXY      40   /* comm_paxy */
#define CM_PA_X      41   /* comm_pa_x */
#define CM_PA_Y      42   /* comm_pa_y */
#define CM_EXEC      43   /* comm_exec */
#define CM_RNGC      44   /* comm_rngc */
#define CM_MXYT      45   /* comm_mxyt */
#define CM_PJMP      46   /* comm_pjmp */
#define CM_HJMP      47   /* comm_hjmp */
#define CM_HCLR      48   /* comm_hclr */
#define CM_IXFW      49   /* comm_ixfw */
#define CM_IXBW      50   /* comm_ixbw */
#define CM_QUAX      51   /* comm_quax */
#define CM_QUAY      52   /* comm_quay */
#define CM_IF_S      53   /* comm_if_s */
#define CM_RAPP      54   /* comm_rapp */
#define CM_RAPK      55   /* comm_rapk */
#define CM_GETS      56   /* comm_gets */
#define CM_S123      57   /* comm_s123 */
#define CM_S456      58   /* comm_s456 */
#define CM_A123      59   /* comm_a123 */
#define CM_A456      60   /* comm_a456 */
#define CM_STOP      61   /* comm_stop */
#define CM_SMHF      62   /* comm_smhf */
#define CM_NGME      63   /* comm_ngme */
#define CM_NGEM      64   /* comm_ngem */
#define CM_IFLB      65   /* comm_iflb */
#define CM_ASXY      66   /* comm_asxy */
#define CM_SCHX      67   /* comm_schx */
#define CM_SCHY      68   /* comm_schy */
#define CM_BACK      69   /* comm_back */
#define CM_MVIX      70   /* comm_mvix */
#define CM_SAJP      71   /* comm_sajp */
#define CM_CCCH      72   /* comm_ccch */
#define CM_WSET      73   /* comm_wset */
#define CM_WSWK      74   /* comm_wswk */
#define CM_WADD      75   /* comm_wadd */
#define CM_WCEQ      76   /* comm_wceq */
#define CM_WCNE      77   /* comm_wcne */
#define CM_WCGT      78   /* comm_wcgt */
#define CM_WCLT      79   /* comm_wclt */
#define CM_WADD2     80   /* comm_wadd2 */
#define CM_WCEQ2     81   /* comm_wceq2 */
#define CM_WCNE2     82   /* comm_wcne2 */
#define CM_WCGT2     83   /* comm_wcgt2 */
#define CM_WCLT2     84   /* comm_wclt2 */
#define CM_RAPP2     85   /* comm_rapp2 */
#define CM_RAPK2     86   /* comm_rapk2 */
#define CM_IFLG      87   /* comm_iflg */
#define CM_MPCY      88   /* comm_mpcy */
#define CM_EPCY      89   /* comm_epcy */
#define CM_IMGS      90   /* comm_imgs */
#define CM_IMGC      91   /* comm_imgc */
#define CM_RVXY      92   /* comm_rvxy */
#define CM_RV_X      93   /* comm_rv_x */
#define CM_RV_Y      94   /* comm_rv_y */
#define CM_CCFL      95   /* comm_ccfl */
#define CM_MYHP      96   /* comm_myhp */
#define CM_EMHP      97   /* comm_emhp */
#define CM_EXBGS     98   /* comm_exbgs */
#define CM_EXBGC     99   /* comm_exbgc */
#define CM_ATMF     100   /* comm_atmf */
#define CM_CHKWF    101   /* comm_chkwf */
/* 102-114 run the routines of codes above them again; no script uses them */
#define CM_DUMMY_2  102   /* comm_dummy */
#define CM_RET_2    103   /* comm_ret */
#define CM_UJA_2    104   /* comm_uja */
#define CM_UJA2_2   105   /* comm_uja2 */
#define CM_UJA3_2   106   /* comm_uja3 */
#define CM_UJA4_2   107   /* comm_uja4 */
#define CM_UJA5_2   108   /* comm_uja5 */
#define CM_UJA6_2   109   /* comm_uja6 */
#define CM_UJA7_2   110   /* comm_uja7 */
#define CM_UMJA_2   111   /* comm_umja */
#define CM_BACK_2   112   /* comm_back */
#define CM_NEX_2    113   /* comm_nex */
#define CM_NEX2_2   114   /* comm_nex2 */
#define CM_WCA      115   /* comm_wca */

#endif
