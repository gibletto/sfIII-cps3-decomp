/*
 * n_input.c  Ranking name entry
 *
 * Name_Input is the per-player entry for entering initials after a ranked game: it works out
 * which ranking the player reached (ranking_state_check), sets up the name work and a time
 * limit, then runs the Name_Jmp_scs states (init, lever/button input, wait, finish).
 * Name_Input_comm and Name_Scs_Input_comm move the cursor through the character set and
 * commit letters, with a timeout that ends entry automatically. When the name is left blank or
 * matches an entry in slang_tbl (name_slang_check), define_name_input substitutes one of two
 * fixed names at random; ranking_name_entry then copies the letters into the ranking record.
 * The rest of the file draws the entered names and scores on the text layer and shows the
 * "thank you for playing" message.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "end_sub.h"
#include "end_sub_2.h"
#include "color3rd.h"
#include "end_sub_8.h"
#include "sc_trans.h"
#include "eff87.h"
#include "eff88.h"
#include "eff89.h"
#include "eff90.h"
#include "eff91.h"
#include "eff92_code.h"
#include "Eff93.h"
#include "EFFB6.h"
#include "EFFB8.h"
#include "PLS02.h"
#include "SE.h"
#include "se_2.h"
#include "se_3.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "n_input.h"

/* name_wk[pl].r_no_0: the name entry step (Name_Jmp_scs) */
#define NAME_INIT       0       /* set up the entry */
#define NAME_LETTER1    1       /* the first letter */
#define NAME_WAIT1      2       /* a short wait */
#define NAME_LETTER2    3       /* the second letter */
#define NAME_WAIT2      4       /* a short wait */
#define NAME_LETTER3    5       /* the third letter */
#define NAME_END        6       /* the name is in (or timed out) */
#define NAME_FINISH     7       /* finished */

/* nsc_ptr->r_no_0: a letter cell (Scs_move_sub) */
#define NSC_EDIT        0       /* until this letter is entered */
#define NSC_SET         1       /* entered; back to NSC_EDIT if it is erased */
#define NSC_DONE        2       /* the name is finished */

/* nsc_ptr->r_no_1 in current_sc_move2 */
#define NSC1_INIT       0       /* show the letter */
#define NSC1_BLINK      1       /* blink it until it is entered */



s16 Name_00[2];  /* 0201D5D8 */
NAME_WK name_wk[2];  /* 0201D5DC */
NAME_WK * name_ptr;  /* 0201D648 */
SC_NAME_WK sc_name_wk[2][4];  /* 0201D64C */
SC_NAME_WK * nsc_ptr;  /* 0201D69C */
RANK_NAME_W rank_name_w[2];  /* 0201D6A0 */
s16 Name_Input_f;  /* 0201D6A8 */
s16 naming_cnt;  /* one counter for both players */
s16 n_disp_flag;  /* 0201D6AC */


/* 02006694 */
/* The name entry states of the plain name entry; the game only runs Name_Jmp_scs. */
void (*Name_Jmp_Tbl[8])() = {
    Name_Input_init,
    Name_Input_comm,
    Name_Input_wait,
    Name_Input_comm,
    Name_Input_wait,
    Name_Input_comm,
    Name_Input_end,
    Name_Finish,
};
/* 020066B4 */
void (*Name_Jmp_scs[8])() = {
    Name_Scs_Input_init,
    Name_Scs_Input_comm,
    Name_Input_wait,
    Name_Scs_Input_comm,
    Name_Input_wait,
    Name_Scs_Input_comm,
    Name_Scs_Input_end,
    Name_Scs_Finish,
};


s32 Name_Input(s16 pl_id) {
    end_no_cut = 1;
    Name_Input_f = 0;
    name_ptr = &name_wk[pl_id];
    name_ptr->id = pl_id;
    start_cut_check(pl_id);
    switch (Name_00[pl_id]) {
    case 0:
        Name_00[pl_id]++;
        if (E_No0 != E0_GAME_OVER) {
            name_ptr->type = 0;
        } else {
            name_ptr->type = 1;
        }
        name_work_init(pl_id);
        ranking_state_check();
        all_name_display();
        break;
    default:
        if (E_No0 != E0_GAME_OVER) {
            if (name_ptr->type) {
                name_ptr->type = 0;
                break;
            }
            Name_Jmp_scs[name_ptr->r_no_0]();
        } else {
            Name_Jmp_Tbl[name_ptr->r_no_0]();
        }
        break;
    }
    return Name_Input_f;
}



/* provisional name */
void Name_Input_init(void) {
    name_ptr->r_no_0++;
    load_any_color(4);
    if (end_name_cut == 0) {
        name_ptr->timer = 1200;
    }
    name_ptr->index = 0;
    effect_B7_init(name_ptr->id);
    effect_B5_init(name_ptr->id);
}

/* provisional name */
void Name_Input_comm(void) {
    s16 cmd;
    s16 i;
    name_ptr->timer--;
    if (name_ptr->timer < 0) {
        name_ptr->r_no_0 = NAME_END;
        for (i = name_ptr->index; i < 4; i++) {
            name_ptr->code[i] = 0x2C;
        }
    } else {
        cmd = Name_Input_sub();
        switch (cmd) {
        case 1:
            name_ptr->r_no_0++;
            name_ptr->timer += 420;
            name_ptr->end_flag[name_ptr->index] = 1;
            name_ptr->index++;
            name_ptr->index &= 3;
            name_ptr->wait_cnt = 10;
            *(s16*)(name_ptr->code + name_ptr->index) = name_ptr->code[name_ptr->index - 1];
            break;
        case 2:
            name_ptr->timer += 420;
            name_ptr->index--;
            name_ptr->r_no_0 -= 2;
            if (name_ptr->index < 0) {
                name_ptr->index = 0;
                name_ptr->r_no_0 = NAME_INIT;
            } else {
                name_ptr->code[name_ptr->index + 1] = 0x2F;
            }
            name_ptr->end_flag[name_ptr->index] = 0;
            break;
        case 3:
            name_ptr->r_no_0 = NAME_END;
            for (i = name_ptr->index; i < 4; i++) {
                name_ptr->code[i] = 0x2C;
            }
            break;
        }
    }
}



void Name_Input_wait(void) {
    name_ptr->wait_cnt--;
    if (name_ptr->wait_cnt < 0) {
        name_ptr->r_no_0++;
    }
}



/* provisional name */
void Name_Input_end(void) {
    register s16 i;
    name_ptr->r_no_0++;
    if (name_ptr->index > 0) {
        if (name_slang_check() != 0) {
            define_name_input();
        }
    } else {
        define_name_input();
    }
    ranking_name_entry();
    i = 0;
    while (i < 4) {
        name_ptr->end_flag[i++] = 1;
    }
    name_ptr->index = 3;
}

/* provisional name */
void Name_Finish(void)
{
    Sound_SE(0x62);
    end_no_cut = 0;
    Name_Input_f = 1;
}



/* provisional name */
void show_thank_you_for_playing(void) {
    tilemap_print_string_attr(20, 22, 18, thank_you_str);
    tilemap_print_string_attr(19, 23, 18, for_playing_str);
}



void Name_Scs_Input_init(void) {
    name_ptr->r_no_0++;
    if (end_name_cut == 0) {
        name_ptr->timer = 1200;
    }
    name_ptr->index = 0;
    rank_display_set(name_ptr->id, Text_Page_Y);
    Scs_char_move();
}



void Name_Scs_Input_comm(void) {
    s16 work;
    s16 i;
    name_ptr->timer--;
    if (name_ptr->timer < 0) {
        name_ptr->r_no_0 = NAME_END;
        for (i = name_ptr->index; i < 4; i++) {
            name_ptr->code[i] = 44;
        }
    } else {
        work = Name_Input_sub();
        switch (work) {
        case 1:
            name_ptr->r_no_0 += 1;
            name_ptr->timer += 420;
            name_ptr->end_flag[name_ptr->index] = 1;
            naming_set(name_ptr->id, name_ptr->index, name_ptr->code[name_ptr->index]);
            name_ptr->index += 1;
            name_ptr->index &= 3;
            name_ptr->wait_cnt = 10;
            if (name_ptr->index != 3) {
                *(s16*)(name_ptr->code + name_ptr->index) = name_ptr->code[name_ptr->index - 1];
            } else {
                name_ptr->code[name_ptr->index] = 46;
            }
            sc_name_wk[name_ptr->id][name_ptr->index].n_disp_flag = 0;
            sc_name_wk[name_ptr->id][name_ptr->index].f_cnt = 0;
            break;
        case 2:
            name_ptr->timer += 420;
            sc_name_wk[name_ptr->id][name_ptr->index].n_disp_flag = 0;
            sc_name_wk[name_ptr->id][name_ptr->index].f_cnt = 0;
            name_ptr->index--;
            name_ptr->r_no_0 -= 2;
            if (name_ptr->index < 0) {
                name_ptr->index = 0;
                name_ptr->r_no_0 = NAME_INIT;
            } else {
                name_ptr->code[name_ptr->index + 1] = 47;
                naming_set(name_ptr->id, name_ptr->index, name_ptr->code[name_ptr->index]);
            }
            name_ptr->end_flag[name_ptr->index] = 0;
            break;
        case 3:
            name_ptr->r_no_0 = NAME_END;
            naming_set(name_ptr->id, name_ptr->index, name_ptr->code[name_ptr->index]);
            for (i = name_ptr->index; i < 4; i++) {
                name_ptr->code[i] = 44;
            }
            break;
        }
    }
    Scs_char_move();
}



void Name_Scs_Input_end(void) {
    s16 i;
    name_ptr->r_no_0++;
    naming_cnt = 120;
    n_disp_flag = 0;
    if (name_ptr->index != 0) {
        if (name_slang_check() != 0) {
            define_name_input();
        }
    } else {
        define_name_input();
    }
    for (i = 0; i < 4; i++) {
        name_ptr->end_flag[i] = 1;
    }
    ranking_name_entry();
    name_ptr->index = 3;
    if (Game_setting.Screen_Mode) {
        if (name_ptr->id) {
            effect_89_init(8, DE_X[3] + 38, Text_Page_Y, 8, 1);
        } else {
            effect_89_init(8, DE_X[3] + 13, Text_Page_Y, 8, 1);
        }
    } else {
        if (name_ptr->id) {
            effect_89_init(8, DE_X[3] + 36, Text_Page_Y, 8, 1);
        } else {
            effect_89_init(8, DE_X[3] + 13, Text_Page_Y, 8, 1);
        }
    }
}



void Name_Scs_Finish(void) {
    naming_cnt--;
    if (naming_cnt < 0) {
        Name_Input_f = 1;
        end_no_cut = 0;
    }
    Scs_char_move();
}



s32 Name_Input_sub(void) {
    u16 sw_up_w;
    u16 sw_data;
    (&name_ptr->old_code[0])[name_ptr->index] = name_ptr->code[name_ptr->index];
    if (name_ptr->id) {
        sw_data = p2sw_0;
        sw_up_w = ~p2sw_1 & p2sw_0;
    } else {
        sw_data = p1sw_0;
        sw_up_w = ~p1sw_1 & p1sw_0;
    }
    if (sw_up_w & BUTTON_SHOTS) {
        switch (name_ptr->code[name_ptr->index]) {
        case 45:
            return 2;
        case 46:
            return 3;
        default:
            return 1;
        }
    } else {
        if (sw_data & LEVER_LR) {
            if (auto_n_check(4, 0, sw_data, sw_up_w)) {
                name_ptr->code[name_ptr->index]--;
                if (name_ptr->code[name_ptr->index] < 0) {
                    name_ptr->code[name_ptr->index] = 46;
                }
            }
            if (auto_n_check(8, 1, sw_data, sw_up_w)) {
                name_ptr->code[name_ptr->index]++;
                if (name_ptr->code[name_ptr->index] > 46) {
                    name_ptr->code[name_ptr->index] = 0;
                }
            }
        }
        return 0;
    }
}



s32 auto_n_check(chk_lvr, index, sw_data, sw_up_w)
u16 chk_lvr;
s16 index;
u16 sw_data;
u16 sw_up_w;
{
    if (sw_up_w & chk_lvr) {
        name_ptr->count1[index] = 0;
        name_ptr->count2[index] = 0;
        return 1;
    }
    if (sw_data & chk_lvr) {
        if (name_ptr->count1[index] > 12) {
            name_ptr->count2[index]++;
            if (name_ptr->count2[index] > 4) {
                name_ptr->count2[index] = 0;
                return 1;
            }
        } else {
            name_ptr->count1[index]++;
            name_ptr->count2[index] = 0;
        }
    } else {
        name_ptr->count1[index] = 0;
        name_ptr->count2[index] = 0;
    }
    return 0;
}



s32 name_slang_check(void) {
    const s16* slang_ptr = &slang_tbl[0][0];
    s16 i;
    s16 j;
    s16 slang_cnt;
    for (i = 0; i < 17; i++) {
        slang_cnt = 0;
        for (j = 0; j < 3; j++) {
            if (*slang_ptr == name_ptr->code[j]) {
                slang_cnt++;
            }
            slang_ptr++;
        }
        if (slang_cnt == 3) {
            return 1;
        }
    }
    return 0;
}



void define_name_input(void) {
    s16 work = random_16_com();
    if (work & 1) {
        name_ptr->code[0] = 2;
        name_ptr->code[1] = 0;
        name_ptr->code[2] = 15;
    } else {
        name_ptr->code[0] = 2;
        name_ptr->code[1] = 14;
        name_ptr->code[2] = 12;
    }
}



void ranking_state_check(void) {
    name_ptr->rank = -1;
    name_ptr->rank_sub = -1;
    if (Rank_In[name_ptr->id][RANK_SCORE] >= 0) {
        name_ptr->rank = Rank_In[name_ptr->id][RANK_SCORE];
        name_ptr->status = 0;
        if (Rank_In[name_ptr->id][RANK_WINS] >= 0) {
            if (Rank_In[name_ptr->id][RANK_SCORE] > Rank_In[name_ptr->id][RANK_WINS]) {
                name_ptr->rank_status = 6;
                name_ptr->rank_in = Rank_In[name_ptr->id][RANK_WINS];
                name_ptr->status_sub = 6;
                name_ptr->rank_sub = Rank_In[name_ptr->id][RANK_WINS];
            } else {
                name_ptr->rank_status = 0;
                name_ptr->rank_in = Rank_In[name_ptr->id][RANK_SCORE];
            }
        } else {
            name_ptr->rank_status = 0;
            name_ptr->rank_in = Rank_In[name_ptr->id][RANK_SCORE];
        }
    } else if (Rank_In[name_ptr->id][RANK_WINS] >= 0) {
        name_ptr->rank_status = 6;
        name_ptr->rank_in = Rank_In[name_ptr->id][RANK_WINS];
        name_ptr->status_sub = 6;
        name_ptr->rank_sub = Rank_In[name_ptr->id][RANK_WINS];
    }
}



void ranking_name_entry(void) {
    RANK_NAME_W* ptr = &rank_name_w[name_ptr->id];
    ptr->code[0] = name_code_tbl[name_ptr->code[0]];
    ptr->code[1] = name_code_tbl[name_ptr->code[1]];
    ptr->code[2] = name_code_tbl[name_ptr->code[2]];
    ptr->code[3] = name_code_tbl[name_ptr->code[3]];
}



void name_work_init(pl_id)
s16 pl_id;
{
    s16 j;
    name_wk[pl_id].r_no_0 = 0;
    name_wk[pl_id].r_no_1 = 0;
    name_wk[pl_id].dmm = 0;
    name_wk[pl_id].end_flag[0] = 0;
    name_wk[pl_id].code[0] = 46;
    name_wk[pl_id].old_code[0] = 46;
    name_wk[pl_id].end_flag[3] = 0;
    name_wk[pl_id].old_code[3] = name_wk[pl_id].code[3] = 44;
    sc_name_wk[pl_id][0].c_cnt = 0;
    sc_name_wk[pl_id][0].type = 0;
    sc_name_wk[pl_id][0].r_no_0 = 0;
    sc_name_wk[pl_id][0].r_no_1 = 0;
    for (j = 1; j < 3; j++) {
        name_wk[pl_id].end_flag[j] = 0;
        name_wk[pl_id].code[j] = 0x2F;
        name_wk[pl_id].old_code[j] = 0x2F;
        sc_name_wk[pl_id][j].c_cnt = j;
        sc_name_wk[pl_id][j].type = j;
        sc_name_wk[pl_id][j].r_no_0 = 0;
        sc_name_wk[pl_id][j].r_no_1 = 0;
    }
}



void rank_display_set(s16 pl_id, s16 pos_y) {
    u16 pos_x;
    if (!Game_setting.Screen_Mode) {
    } else {
    }
    if (pl_id) {
        if (Game_setting.Screen_Mode) {
            pos_x = 9;
        } else {
            pos_x = 0;
        }
        pos_x += 33;
    } else {
        if (Game_setting.Screen_Mode) {
            pos_x = 7;
        } else {
            pos_x = 0;
        }
        pos_x += 10;
    }
    switch (name_ptr->rank_in) {
    case 0:
        tilemap_put_cell(pos_x, pos_y, 22, 106);
        tilemap_put_cell(pos_x + 1, pos_y, 22, 107);
        break;
    case 1:
        tilemap_put_cell(pos_x, pos_y, 22, 108);
        tilemap_put_cell(pos_x + 1, pos_y, 22, 109);
        break;
    case 2:
        tilemap_put_cell(pos_x, pos_y, 22, 122);
        tilemap_put_cell(pos_x + 1, pos_y, 22, 123);
        break;
    default:
        tilemap_put_cell(pos_x, pos_y, 22, 124);
        tilemap_put_cell(pos_x + 1, pos_y, 22, 125);
        break;
    }
    if (pl_id) {
        sc_celllist_put_pos(14, 0, pos_y);
    } else {
        sc_celllist_put_pos(13, 0, pos_y);
    }
}






void Scs_char_move(void) {
    s16 i;
    s8 ofs;
    ofs = 0;
    for (i = 0; i < 4; i++) {
        nsc_ptr = &sc_name_wk[name_ptr->id][ofs];
        Scs_move_sub();
        ofs++;
    }
}



s32 Scs_move_sub(void) {
    switch (nsc_ptr->r_no_0) {
    case NSC_EDIT:
    case_0:
        if (name_ptr->end_flag[nsc_ptr->type]) {
            nsc_ptr->r_no_0++;
            naming_set(name_ptr->id, nsc_ptr->type, name_ptr->code[nsc_ptr->type]);
        } else {
            current_sc_move2();
        }
        break;
    case NSC_SET:
        if (name_ptr->r_no_0 == NAME_FINISH) {
            nsc_ptr->r_no_0 = NSC_DONE;
        }
        if (name_ptr->end_flag[nsc_ptr->type] == 0) {
            nsc_ptr->r_no_0 = NSC_SET;
            goto case_0;
        }
        break;
    case NSC_DONE:
        break;
    }
    if (name_ptr->old_code[nsc_ptr->type] != name_ptr->code[nsc_ptr->type]) {
        nsc_ptr->n_disp_flag = 0;
        nsc_ptr->f_cnt = 0;
        naming_set(name_ptr->id, nsc_ptr->type, name_ptr->code[nsc_ptr->type]);
    }
}



void current_sc_move2(void) {
    if (name_ptr->index != nsc_ptr->c_cnt) {
        return;
    }
    switch (nsc_ptr->r_no_1) {
    case NSC1_INIT:
        nsc_ptr->r_no_1++;
        nsc_ptr->f_cnt = 0;
        nsc_ptr->n_disp_flag = 0;
        naming_set(name_ptr->id, nsc_ptr->type, name_ptr->code[nsc_ptr->type]);
        break;
    case NSC1_BLINK:
        if (name_ptr->r_no_0 > NAME_LETTER3) {
            nsc_ptr->r_no_0++;
        } else {
            nsc_ptr->f_cnt++;
            if (nsc_ptr->f_cnt > 16) {
                nsc_ptr->f_cnt = 0;
                nsc_ptr->n_disp_flag++;
                if (nsc_ptr->n_disp_flag > 2) {
                    nsc_ptr->n_disp_flag = 0;
                }
                if (nsc_ptr->n_disp_flag != 2) {
                    naming_set(name_ptr->id, nsc_ptr->type, name_ptr->code[nsc_ptr->type]);
                } else {
                    naming_set(name_ptr->id, nsc_ptr->type, 47);
                }
            }
        }
        break;
    }
}



void all_name_display(void) {
    s16 i;
    for (i = 0; i < 3; i++) {
        naming_set(name_ptr->id, (s8)i, name_ptr->code[i]);
    }
    naming_set(name_ptr->id, 3, 44);
    naming_set(name_ptr->id, 4, name_ptr->rank_in + 34);
    name_ptr->dmm = 1;
}



void start_cut_check(pl_id)
s16 pl_id;
{
    if (Naming_Cut[pl_id]) {
        if (name_ptr->r_no_0 < NAME_END) {
            name_ptr->r_no_0 = NAME_END;
        }
        pl_id = 0;
        do {
            if (name_ptr->end_flag[pl_id] == 0) {
                name_ptr->code[pl_id] = 44;
            }
        } while (++pl_id < 3);
    }
}
