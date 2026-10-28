/*
 * PLPATUNI.C  Shared special-move routines for all characters
 *
 * Special attack routines used by several characters' attack tables (the "universal" set).
 * They cover the fireball family (Att_HADOUKEN, Att_HADOUKEN2), rising uppercuts
 * (Att_SHOURYUUKEN, Att_SHOURYUUREPPA, Att_SHINSHOURYUUKEN), spinning and hopping kicks
 * (Att_SENPUUKYAKU, Att_ABISEGERI, Att_TENSHINSENKYUUTAI), air specials (Att_KUUCHUU...),
 * leaping jumps (Att_JINNCHUUWATARI, Att_SLIDE_and_JUMP) and Att_CHOUCHUURENGEKI. Each steps its
 * animation and mvxy movement data by cg_type marks. Att_NM_OKIAGARI is a get-up; Att_DUMMY fills
 * unused slots. Att_JINNCHUUWATARI takes its jump from the move data, and the moves keep the height
 * on their first frame.
 * cal_initial_speed_y is declared here without a prototype.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "PLS02.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "PLPAT.h"
#include "PLS01.h"
#include "PLPATUNI.h"
#include "cmd_data.h"
#include "CALDIR.h"

/* routine_no[3], Att_HADOUKEN2 */
#define HADOUKEN2_RUN   1       /* run the animation */

/* routine_no[3], Att_NM_OKIAGARI */
#define NM_OKIAGARI_RUN 1       /* run the animation */

/* routine_no[3], Att_SHOURYUUKEN */
#define SHOURYUUKEN_MOVE 1      /* move and run the animation */
#define SHOURYUUKEN_AIR 3       /* in the air until it lands */
#define SHOURYUUKEN_LAND 4      /* the landing */

/* routine_no[3], Att_SENPUUKYAKU */
#define SENPUUKYAKU_MOVE 1      /* move and run the animation to cue 20 */
#define SENPUUKYAKU_MOVE2 2     /* move and run the animation */
#define SENPUUKYAKU_RUN 3       /* run the animation */

/* routine_no[3], Att_SENPUUKYAKU2 */
#define SENPUUKYAKU2_MOVE 1     /* move and run the animation to cue 20 */
#define SENPUUKYAKU2_AIR 2      /* in the air until it lands */
#define SENPUUKYAKU2_LAND 3     /* the landing */

/* routine_no[3], Att_ABISEGERI */
#define ABISEGERI_MOVE  1       /* move and run the animation to cue 20 */
#define ABISEGERI_AIR   2       /* in the air until it lands */
#define ABISEGERI_END   3       /* run the animation to its end */

/* routine_no[3], Att_SHOURYUUREPPA */
#define SHOURYUUREPPA_CUE 1     /* run the animation to cue 20 */
#define SHOURYUUREPPA_AIR 2     /* in the air until it lands */
#define SHOURYUUREPPA_AIR2 3    /* in the air until it lands */
#define SHOURYUUREPPA_LAND 4    /* the landing */

/* routine_no[3], Att_SHINSHOURYUUKEN */
#define SHINSHOURYUUKE_CUE 1    /* run the animation to cue 20 */
#define SHINSHOURYUUKE_AIR 2    /* in the air until it lands */

/* routine_no[3], Att_KUUCHUUNICHIRINSHOU */
#define KUUCHUUNICHIRI_MOVE 1   /* move and run the animation */
#define KUUCHUUNICHIRI_RUN 2    /* run the animation */

/* routine_no[3], Att_KUUCHUUJINNCHUUWATARI */
#define KUUCHUUJINNCHU_CUE 1    /* run the animation to cue 1 */
#define KUUCHUUJINNCHU_MOVE 2   /* move and run the animation */
#define KUUCHUUJINNCHU_RUN 3    /* run the animation */

/* routine_no[3], Att_TENSHINSENKYUUTAI_OLD */
#define TENSHINSENKYUU_MOVE 1   /* move and run the animation */
#define TENSHINSENKYUU_AIR 2    /* in the air until it lands */
#define TENSHINSENKYUU_LAND 3   /* the landing */

/* routine_no[3], Att_TENSHINSENKYUUTAI */
#define TENSHINSENKYUU2_MOVE 1  /* move and run the animation */
#define TENSHINSENKYUU2_AIR 2   /* in the air until it lands */
#define TENSHINSENKYUU2_LAND 3  /* the landing */
#define TENSHINSENKYUU2_MOVE2 4 /* move and run the animation */

/* routine_no[3], Att_SLIDE_and_JUMP */
#define SLIDE_AND_JUMP_CUE 1    /* run the animation to cue 20 */
#define SLIDE_AND_JUMP_AIR 2    /* in the air until it lands */
#define SLIDE_AND_JUMP_MOVE 3   /* move and run the animation to cue 20 */

/* routine_no[3], Att_JINNCHUUWATARI */
#define JINNCHUUWATARI_CUE 1    /* run the animation to cue 20 */
#define JINNCHUUWATARI_AIR 2    /* in the air until it lands */
#define JINNCHUUWATARI_CUE2 3   /* run the animation to cue 1 */




void Att_DUMMY(PLW* wk) {}



void Att_HADOUKEN(PLW* wk) {
    wk->scr_pos_set_flag = 0;
    Att_HADOUKEN2(wk);
}



void Att_HADOUKEN2(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->wu.rl_flag = wk->wu.rl_waza;
        set_char_move_init(&wk->wu, 5, wk->as->char_ix);
        break;
    case HADOUKEN2_RUN:
        char_move(&wk->wu);
        break;
    }
}



void Att_NM_OKIAGARI(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        set_char_move_init(&wk->wu, 5, wk->as->char_ix);
        break;
    case NM_OKIAGARI_RUN:
        char_move(&wk->wu);
        break;
    }
}



void Att_SHOURYUUKEN(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->wu.rl_flag = wk->wu.rl_waza;
        set_char_move_init(&wk->wu, 5, wk->as->char_ix);
        reset_mvxy_data(&wk->wu);
        wk->wu.mvxy.index = wk->as->r_no;
        break;
    case SHOURYUUKEN_MOVE:
        char_move(&wk->wu);
        add_mvxy_speed(&wk->wu);
        cal_mvxy_speed(&wk->wu);
        switch (wk->wu.cg_type) {
        case 20:
            setup_mvxy_data(&wk->wu, wk->wu.mvxy.index);
            wk->wu.mvxy.index++;
            wk->wu.cg_type = 0;
            break;
        case 25:
            add_to_mvxy_data(&wk->wu, wk->wu.mvxy.index);
            wk->wu.mvxy.index++;
            wk->wu.cg_type = 0;
            break;
        case 30:
            setup_mvxy_data(&wk->wu, wk->as->data_ix);
            wk->wu.routine_no[3] = SHOURYUUKEN_AIR;
            wk->wu.cg_type = 0;
        }
        return;
    case SHOURYUUKEN_AIR:
        jumping_union_process(&wk->wu, 4);
        break;
    case SHOURYUUKEN_LAND:
        char_move(&wk->wu);
        break;
    }
}



void Att_SENPUUKYAKU(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->wu.rl_flag = wk->wu.rl_waza;
        set_char_move_init(&wk->wu, 5, wk->as->char_ix);
        reset_mvxy_data(&wk->wu);
        wk->wu.mvxy.index = wk->as->data_ix;
        break;
    case SENPUUKYAKU_MOVE:
        char_move(&wk->wu);
        if (wk->wu.cg_type == 20) {
            setup_mvxy_data(&wk->wu, wk->wu.mvxy.index);
            wk->wu.mvxy.index++;
            wk->wu.routine_no[3]++;
            wk->wu.cg_type = 0;
            add_mvxy_speed(&wk->wu);
        }
        break;
    case SENPUUKYAKU_MOVE2:
        jumping_union_process(&wk->wu, 3);
        if (wk->wu.routine_no[3] != SENPUUKYAKU_RUN && wk->wu.cg_type == 20) {
            add_to_mvxy_data(&wk->wu, wk->wu.mvxy.index);
            wk->wu.mvxy.index++;
            wk->wu.cg_type = 0;
        }
        break;
    case SENPUUKYAKU_RUN:
        char_move(&wk->wu);
        break;
    }
}



void Att_SENPUUKYAKU2(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->wu.rl_flag = wk->wu.rl_waza;
        set_char_move_init(&wk->wu, 5, wk->as->char_ix);
        setup_mvxy_data(&wk->wu, wk->as->data_ix);
        cal_initial_speed_y(&wk->wu, wk->as->r_no, 0);
        break;
    case SENPUUKYAKU2_MOVE:
        char_move(&wk->wu);
        if (wk->wu.cg_type == 20) {
            wk->wu.routine_no[3]++;
            wk->wu.cg_type = 0;
            add_mvxy_speed(&wk->wu);
        }
        break;
    case SENPUUKYAKU2_AIR:
        jumping_union_process(&wk->wu, 3);
        break;
    case SENPUUKYAKU2_LAND:
        char_move(&wk->wu);
        break;
    }
}



void Att_ABISEGERI(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->wu.rl_flag = wk->wu.rl_waza;
        set_char_move_init(&wk->wu, 5, wk->as->char_ix);
        setup_mvxy_data(&wk->wu, wk->as->r_no);
        break;
    case ABISEGERI_MOVE:
        char_move(&wk->wu);
        if (wk->wu.cg_type == 20) {
            wk->wu.routine_no[3]++;
            wk->wu.cg_type = 0;
            add_mvxy_speed(&wk->wu);
        }
        break;
    case ABISEGERI_AIR:
        jumping_union_process(&wk->wu, 3);
        if (wk->wu.routine_no[3] == ABISEGERI_END) {
            if (wk->wu.mvxy.kop[0] == 2) {
                wk->wu.mvxy.kop[0] = 1;
            }
            wk->wu.mvxy.d[1].sp = 0;
            wk->wu.mvxy.a[1].sp = 0;
        }
        break;
    case ABISEGERI_END:
        cal_mvxy_speed(&wk->wu);
        add_mvxy_speed(&wk->wu);
        char_move(&wk->wu);
        if (wk->wu.cg_type == 64 || wk->wu.cg_type == 0xFF) {
            wk->wu.routine_no[3]++;
            wk->wu.mvxy.d[0].sp = 0;
            wk->wu.mvxy.a[0].sp = 0;
        }
        break;
    default:
        char_move(&wk->wu);
        break;
    }
}



void Att_SHOURYUUREPPA(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->wu.rl_flag = wk->wu.rl_waza;
        set_char_move_init(&wk->wu, 5, wk->as->char_ix);
        reset_mvxy_data(&wk->wu);
        wk->wu.mvxy.index = wk->as->r_no;
        break;
    case SHOURYUUREPPA_CUE:
        char_move(&wk->wu);
        if (wk->wu.cg_type == 20) {
            setup_mvxy_data(&wk->wu, wk->wu.mvxy.index);
            wk->wu.mvxy.index++;
            wk->wu.routine_no[3] = SHOURYUUREPPA_AIR;
            wk->wu.cg_type = 0;
        }
        if (wk->wu.cg_type == 30) {
            setup_mvxy_data(&wk->wu, wk->as->data_ix);
            wk->wu.routine_no[3] = SHOURYUUREPPA_AIR2;
            wk->wu.cg_type = 0;
        }
        if (wk->wu.cg_type == 40) {
            if ((wk->cp->sw_new & CMD_SW_SHOT) == CMD_SW_PUNCH) {
                wk->wu.routine_no[1] = PLAYER_NORMAL;
                wk->wu.routine_no[2] = 6;
                wk->wu.routine_no[3] = RN3_START;
                wk->wu.cg_type = 0;
            }
        }
        break;
    case SHOURYUUREPPA_AIR:
        jumping_union_process(&wk->wu, 1);
        if (wk->wu.cg_type == 30) {
            setup_mvxy_data(&wk->wu, wk->as->data_ix);
            wk->wu.routine_no[3] = SHOURYUUREPPA_AIR2;
            wk->wu.cg_type = 0;
        }
        break;
    case SHOURYUUREPPA_AIR2:
        jumping_union_process(&wk->wu, 4);
        break;
    case SHOURYUUREPPA_LAND:
        char_move(&wk->wu);
        break;
    }
}



void Att_SHINSHOURYUUKEN(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->wu.rl_flag = wk->wu.rl_waza;
        set_char_move_init(&wk->wu, 5, wk->as->char_ix);
        reset_mvxy_data(&wk->wu);
        break;
    case SHINSHOURYUUKE_CUE:
        char_move(&wk->wu);
        if (wk->wu.cg_type == 20) {
            setup_mvxy_data(&wk->wu, wk->wu.mvxy.index);
            wk->wu.mvxy.index++;
            wk->wu.routine_no[3] = SHINSHOURYUUKE_AIR;
            wk->wu.cg_type = 0;
        }
        break;
    case SHINSHOURYUUKE_AIR:
        jumping_union_process(&wk->wu, 1);
        if (wk->wu.cg_type == 30) {
            setup_mvxy_data(&wk->wu, wk->wu.mvxy.index);
            wk->wu.cg_type = 0;
        }
        break;
    }
}



void Att_KUUCHUUNICHIRINSHOU(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        set_char_move_init(&wk->wu, 5, wk->as->char_ix);
    case KUUCHUUNICHIRI_MOVE:
        jumping_union_process(&wk->wu, 2);
        if (wk->wu.routine_no[3] != KUUCHUUNICHIRI_RUN) {
            if (wk->wu.cg_type == 20) {
                add_to_mvxy_data(&wk->wu, wk->as->data_ix);
                wk->wu.cg_type = 0;
            }
            if (wk->wu.cg_type == 30) {
                add_to_mvxy_data(&wk->wu, wk->as->r_no);
                wk->wu.cg_type = 0;
            }
        }
        break;
    case KUUCHUUNICHIRI_RUN:
        char_move(&wk->wu);
        break;
    }
}



void Att_KUUCHUUJINNCHUUWATARI(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        set_char_move_init(&wk->wu, 5, wk->as->char_ix);
        wk->wu.mvxy.index = wk->as->r_no;
        break;
    case KUUCHUUJINNCHU_CUE:
        char_move(&wk->wu);
        if (wk->wu.cg_type == 1) {
            wk->wu.routine_no[3]++;
        }
        if (wk->wu.cg_type == 20) {
            setup_mvxy_data(&wk->wu, wk->wu.mvxy.index);
            wk->wu.cg_type = 0;
            wk->wu.mvxy.index++;
        }
        break;
    case KUUCHUUJINNCHU_MOVE:
        jumping_union_process(&wk->wu, 3);
        if (wk->wu.routine_no[3] == KUUCHUUJINNCHU_RUN) {
            break;
        }
        if (wk->wu.cg_type == 20) {
            add_to_mvxy_data(&wk->wu, wk->wu.mvxy.index);
            wk->wu.cg_type = 0;
            wk->wu.mvxy.index++;
        }
        if (wk->wu.cg_type == 30) {
            setup_mvxy_data(&wk->wu, wk->as->data_ix);
            wk->wu.cg_type = 0;
        }
        break;
    case KUUCHUUJINNCHU_RUN:
        char_move(&wk->wu);
        break;
    }
}



/* provisional name */
void Att_TENSHINSENKYUUTAI_OLD(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->wu.rl_flag = wk->wu.rl_waza;
        set_char_move_init(&wk->wu, 5, wk->as->char_ix);
        reset_mvxy_data(&wk->wu);
        wk->wu.mvxy.index = wk->as->r_no;
        break;
    case TENSHINSENKYUU_MOVE:
        char_move(&wk->wu);
        switch (wk->wu.cg_type) {
        case 20:
            setup_mvxy_data(&wk->wu, wk->wu.mvxy.index);
            wk->wu.mvxy.index++;
            wk->wu.cg_type = 0;
            break;
        case 40:
            reset_mvxy_data(&wk->wu);
            wk->wu.cg_type = 0;
            break;
        case 30:
            wk->wu.mvxy.index = wk->as->data_ix;
            setup_mvxy_data(&wk->wu, wk->wu.mvxy.index);
            wk->wu.mvxy.index++;
            wk->wu.routine_no[3]++;
            wk->wu.cg_type = 0;
            break;
        }
        add_mvxy_speed(&wk->wu);
        cal_mvxy_speed(&wk->wu);
        break;
    case TENSHINSENKYUU_AIR:
        jumping_union_process(&wk->wu, 3);
        if (wk->wu.routine_no[3] != TENSHINSENKYUU_LAND && wk->wu.cg_type == 30) {
            setup_mvxy_data(&wk->wu, wk->wu.mvxy.index);
            wk->wu.mvxy.index++;
            wk->wu.cg_type = 0;
        }
        break;
    case TENSHINSENKYUU_LAND:
        char_move(&wk->wu);
        break;
    }
}



void Att_TENSHINSENKYUUTAI(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->wu.rl_flag = wk->wu.rl_waza;
        set_char_move_init(&wk->wu, 5, wk->as->char_ix);
        reset_mvxy_data(&wk->wu);
        wk->wu.mvxy.index = wk->as->r_no;
        break;
    case TENSHINSENKYUU2_MOVE:
        char_move(&wk->wu);
        switch (wk->wu.cg_type) {
        case 20:
            setup_mvxy_data(&wk->wu, wk->wu.mvxy.index);
            wk->wu.mvxy.index++;
            wk->wu.cg_type = 0;
            break;
        case 40:
            reset_mvxy_data(&wk->wu);
            wk->wu.cg_type = 0;
            break;
        case 50:
            wk->wu.routine_no[3] = TENSHINSENKYUU2_MOVE2;
            wk->wu.cg_type = 0;
            break;
        case 30:
            wk->wu.mvxy.index = wk->as->data_ix;
            setup_mvxy_data(&wk->wu, wk->wu.mvxy.index);
            wk->wu.mvxy.index++;
            wk->wu.routine_no[3] = TENSHINSENKYUU2_AIR;
            wk->wu.cg_type = 0;
            break;
        }
        add_mvxy_speed(&wk->wu);
        cal_mvxy_speed(&wk->wu);
        if (wk->wu.routine_no[3] != TENSHINSENKYUU2_MOVE2 && wk->hos_fi_flag | wk->hos_em_flag) {
            char_move_cmj4(&wk->wu);
            wk->wu.routine_no[3] = TENSHINSENKYUU2_MOVE2;
        }
        break;
    case TENSHINSENKYUU2_AIR:
        jumping_union_process(&wk->wu, 3);
        if (wk->wu.routine_no[3] != TENSHINSENKYUU2_LAND && wk->wu.cg_type == 30) {
            setup_mvxy_data(&wk->wu, wk->wu.mvxy.index);
            wk->wu.mvxy.index++;
            wk->wu.cg_type = 0;
        }
        break;
    case TENSHINSENKYUU2_LAND:
        char_move(&wk->wu);
        break;
    case TENSHINSENKYUU2_MOVE2:
        char_move(&wk->wu);
        switch (wk->wu.cg_type) {
        case 20:
            setup_mvxy_data(&wk->wu, wk->wu.mvxy.index);
            wk->wu.mvxy.index++;
            wk->wu.cg_type = 0;
            break;
        case 40:
            reset_mvxy_data(&wk->wu);
            wk->wu.cg_type = 0;
            break;
        case 30:
            wk->wu.mvxy.index = wk->as->data_ix;
            setup_mvxy_data(&wk->wu, wk->wu.mvxy.index);
            wk->wu.mvxy.index++;
            wk->wu.routine_no[3] = TENSHINSENKYUU2_AIR;
            wk->wu.cg_type = 0;
            break;
        }
        add_mvxy_speed(&wk->wu);
        cal_mvxy_speed(&wk->wu);
        break;
    }
}



void Att_CHOUCHUURENGEKI(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->wu.xyz[1].cal = 0;
        wk->wu.rl_flag = wk->wu.rl_waza;
        reset_mvxy_data(&wk->wu);
        wk->wu.mvxy.index = wk->as->r_no;
        set_char_move_init(&wk->wu, 5, wk->as->char_ix);
        break;
    default:
        char_move(&wk->wu);
        cal_mvxy_speed(&wk->wu);
        add_mvxy_speed(&wk->wu);
        switch (wk->wu.cg_type) {
        case 20:
            setup_mvxy_data(&wk->wu, wk->wu.mvxy.index);
            wk->wu.mvxy.index++;
            wk->wu.cg_type = 0;
            break;
        case 21:
            reset_mvxy_data(&wk->wu);
            wk->wu.cg_type = 0;
        default:
            break;
        }
    }
}



void Att_SLIDE_and_JUMP(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->wu.xyz[1].cal = 0;
        wk->wu.rl_flag = wk->wu.rl_waza;
        reset_mvxy_data(&wk->wu);
        wk->wu.mvxy.index = wk->as->r_no;
        set_char_move_init(&wk->wu, 5, wk->as->char_ix);
        break;
    case SLIDE_AND_JUMP_CUE:
        char_move(&wk->wu);
        if (wk->wu.cg_type == 20) {
            setup_mvxy_data(&wk->wu, wk->wu.mvxy.index);
            wk->wu.mvxy.index++;
            wk->wu.routine_no[3] = SLIDE_AND_JUMP_AIR;
            wk->wu.cg_type = 0;
        }
        if (wk->wu.cg_type == 30) {
            setup_mvxy_data(&wk->wu, wk->wu.mvxy.index);
            wk->wu.mvxy.index++;
            wk->wu.routine_no[3] = SLIDE_AND_JUMP_MOVE;
            wk->wu.cg_type = 0;
        }
        break;
    case SLIDE_AND_JUMP_AIR:
        jumping_union_process(&wk->wu, 1);
        if ((wk->wu.routine_no[3] != SLIDE_AND_JUMP_CUE) && (wk->wu.cg_type == 20)) {
            setup_mvxy_data(&wk->wu, wk->wu.mvxy.index);
            wk->wu.mvxy.index++;
            wk->wu.cg_type = 0;
        }
        break;
    case SLIDE_AND_JUMP_MOVE:
        char_move(&wk->wu);
        cal_mvxy_speed(&wk->wu);
        add_mvxy_speed(&wk->wu);
        if (wk->wu.cg_type == 20) {
            setup_mvxy_data(&wk->wu, wk->wu.mvxy.index);
            wk->wu.mvxy.index++;
            wk->wu.routine_no[3] = SLIDE_AND_JUMP_AIR;
            wk->wu.cg_type = 0;
        }
        if (wk->wu.cg_type == 21) {
            reset_mvxy_data(&wk->wu);
            wk->wu.cg_type = 0;
            wk->wu.routine_no[3] = SLIDE_AND_JUMP_CUE;
        }
        if (wk->wu.cg_type == 30) {
            setup_mvxy_data(&wk->wu, wk->wu.mvxy.index);
            wk->wu.mvxy.index++;
            wk->wu.cg_type = 0;
        }
        break;
    }
}



void Att_JINNCHUUWATARI(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->wu.rl_flag = wk->wu.rl_waza;
        set_char_move_init(&wk->wu, 5, wk->as->char_ix);
        wk->wu.mvxy.index = wk->as->data_ix;
        break;
    case JINNCHUUWATARI_CUE:
        char_move(&wk->wu);
        if (wk->wu.cg_type == 20) {
            setup_mvxy_data(&wk->wu, wk->wu.mvxy.index);
            wk->wu.cg_type = 0;
            wk->wu.mvxy.index++;
            wk->wu.routine_no[3]++;
        }
        break;
    case JINNCHUUWATARI_AIR:
        jumping_union_process(&wk->wu, 3);
        if (wk->wu.routine_no[3] != JINNCHUUWATARI_CUE2 && wk->wu.cg_type == 1) {
            wk->wu.cg_type = 0;
            wk->wu.routine_no[3] = JINNCHUUWATARI_CUE2;
        }
        break;
    case JINNCHUUWATARI_CUE2:
        char_move(&wk->wu);
        if (wk->wu.cg_type == 1) {
            wk->wu.cg_type = 0;
            wk->wu.routine_no[3] = JINNCHUUWATARI_AIR;
        }
        break;
    }
}
