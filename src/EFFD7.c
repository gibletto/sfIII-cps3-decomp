/*
 * EFFD7.C  Effect D7: super art selection plates
 *
 * effect_D7_init (from sel_pl.c) makes the plate of one of a player's three super arts in two layers,
 * by character and Country: type 0 the plate (pattern 27, coloured by its row from effD7_plate_col),
 * which starts effect 98 and effect E4 when it appears, and type 1 the art's name over it (pattern 28),
 * whose position is kept in Plate_X / Plate_Y for those effects. After its delay a plate slides in
 * from the player's side to its row in effD7_plate_pos. While the player chooses, Moving_Plate turns
 * the three plates round (effD7_setup_left / _right / _up / _down, effD7_move, effD7_move_back) so the
 * chosen art comes to the front. Once Sel_Arts_Complete is set the chosen plate waits for the flash
 * and the other player and rises to the top, and the others slide out. effect_D7_init2 places a plate
 * straight at its final place.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
extern const s16 effD7_plate_pos[2][6];
extern const s16 effD7_plate_col[2][3];
extern s8 eff98_arts_req[2][3];
extern s8 effE4_col_req[2][3];
void effD7_setup_pos(WORK_Other* ewk);
void effD7_init_common();
void effD7_pattern(WORK_Other* ewk, s16 step);

extern s16 eff98_plate_z[2][3];
void effD7_move(WORK_Other* ewk);
s32 effD7_check_move(WORK_Other* ewk);
void effD7_move_back(WORK_Other* ewk);
void effD7_setup_left(WORK_Other* ewk);
void effD7_setup_right(WORK_Other* ewk);
void effD7_setup_down(WORK_Other* ewk);
void effD7_setup_up(WORK_Other* ewk);
void effD7_move_x(WORK_Other* ewk);
s32 effD7_move_y(WORK_Other* ewk);
s32 effD7_select_end(WORK_Other* ewk);
s32 effect_98_init();
s32 effect_E4_init();
s32 Ck_Range_Out_S();

void effect_D7_move(WORK_Other* ewk) {
    s16 y;
    switch (ewk->wu.routine_no[0]) {
    case 0:
        if (--ewk->wu.dir_timer) {
            return;
        }
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index, ewk->wu.vital_new + 1, 0);
        if (ewk->wu.dm_vital == 0) {
            effect_98_init(ewk->master_id, ewk->master_player, ewk->master_priority);
            effect_E4_init(ewk->master_id, ewk->master_player, ewk->master_priority);
        }
        break;
    case 1:
        ewk->wu.xyz[0].cal += ewk->wu.mvxy.a[0].sp;
        ewk->wu.mvxy.a[0].sp += ewk->wu.mvxy.d[0].sp;
        if (ewk->wu.mvxy.a[0].sp > 0) {
            if (ewk->wu.hit_quake <= ewk->wu.xyz[0].disp.pos) {
                ewk->wu.routine_no[0]++;
                ewk->wu.xyz[0].disp.pos = ewk->wu.hit_quake;
                ewk->wu.mvxy.a[0].sp = -0x17FFF7;
                Move_Super_Arts[ewk->master_id]--;
                Select_Arts[ewk->master_id]--;
                if (Flash_Complete[ewk->master_id] == -1 || plw[ewk->master_id].wu.operator == 0) {
                    ewk->wu.routine_no[0] = 8;
                }
            }
        } else if (ewk->wu.hit_quake >= ewk->wu.xyz[0].disp.pos) {
            ewk->wu.routine_no[0]++;
            ewk->wu.xyz[0].disp.pos = ewk->wu.hit_quake;
            ewk->wu.mvxy.a[0].sp = 0x17FFF7;
            Move_Super_Arts[ewk->master_id]--;
            Select_Arts[ewk->master_id]--;
            if (Flash_Complete[ewk->master_id] == -1 || plw[ewk->master_id].wu.operator == 0) {
                ewk->wu.routine_no[0] = 8;
            }
        }
        break;
    case 2:
        switch (ewk->wu.routine_no[1]) {
        case 0:
            switch (Moving_Plate[ewk->master_id]) {
            case 1:
                if (ewk->wu.vital_old == 2) {
                    effD7_setup_right(ewk);
                } else {
                    effD7_setup_down(ewk);
                }
                break;
            case 2:
                if (ewk->wu.vital_old == 0) {
                    effD7_setup_left(ewk);
                } else {
                    effD7_setup_up(ewk);
                }
                break;
            default:
                if (effD7_select_end(ewk)) {
                    if (ewk->master_id) {
                        ewk->wu.mvxy.a[0].sp = 0x17FFF7;
                    } else {
                        ewk->wu.mvxy.a[0].sp = -0x17FFF7;
                    }
                }
                break;
            }
            break;
        case 1:
        case 2:
            effD7_move(ewk);
            break;
        case 3:
            effD7_move_back(ewk);
            break;
        }
        break;
    case 3:
        ewk->wu.xyz[0].cal += ewk->wu.mvxy.a[0].sp;
        if (Ck_Range_Out_S(ewk, 2, 0x50)) {
            ewk->wu.disp_flag = 0;
            ewk->wu.routine_no[0] = 9;
        }
        break;
    case 4:
        if (Flash_Complete[ewk->master_id] == 0) {
            break;
        }
        ewk->wu.dir_timer = 10;
        ewk->wu.routine_no[0]++;
        break;
    case 5:
        if (--ewk->wu.dir_timer) {
            break;
        }
        ewk->wu.routine_no[0]++;
        break;
    case 6:
        if (plw[ewk->master_id ^ 1].wu.operator == 0 || Sel_Arts_Complete[ewk->master_id ^ 1] < 0) {
            goto plate_ready;
        plate_ready:;
            ewk->wu.routine_no[0]++;
            if (ewk->wu.dm_vital == 0) {
                y = 16;
            } else {
                y = 0;
            }
            ewk->wu.hit_quake = y + 32;
        }
        break;
    case 7:
        ewk->wu.xyz[1].cal += -0xF0000;
        if (ewk->wu.hit_quake >= ewk->wu.xyz[1].disp.pos) {
            ewk->wu.xyz[1].disp.pos = ewk->wu.hit_quake;
            ewk->wu.routine_no[0]++;
        }
        break;
    case 8:
        break;
    case 9:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 0;
        return;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        return;
    }
    ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
    ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
    ewk->wu.position_z = ewk->wu.xyz[2].disp.pos & 0x3FF;
    if (ewk->wu.dm_vital == 1) {
        Plate_X[(s8)ewk->master_id][ewk->master_player] = ewk->wu.position_x;
        Plate_Y[(s8)ewk->master_id][ewk->master_player] = ewk->wu.position_y;
        eff98_plate_z[(s8)ewk->master_id][ewk->master_player] = ewk->wu.position_z;
        PP_Priority[(s8)ewk->master_id][ewk->master_player] = (s8)ewk->wu.dmcal_m;
    }
    sort_push_request4(&ewk->wu);
}

void effD7_setup_pos(WORK_Other* ewk) {
    s16 pos;
    s16 flag;
    s16 y;
    if (Sel_Arts_Complete[ewk->master_id] == -1 || plw[ewk->master_id].wu.operator == 0) {
        flag = 1;
        pos = 0;
    } else {
        flag = 0;
        pos = ewk->master_priority;
    }
    if (ewk->wu.dm_vital == 0) {
        y = 16;
    } else {
        y = 0;
    }
    ewk->wu.xyz[1].disp.pos = effD7_plate_pos[(s8)ewk->master_id][pos * 2 + 1] + y;
    if (ewk->master_id) {
        ewk->wu.xyz[0].disp.pos = DE_X[5] + 0x400;
        ewk->wu.mvxy.a[0].sp = -0x14FFFA;
        ewk->wu.mvxy.d[0].sp = -0x8000;
        ewk->wu.hit_quake = effD7_plate_pos[(s8)ewk->master_id][pos * 2] + DE_X[5];
    } else {
        ewk->wu.xyz[0].disp.pos = 0x1A0;
        ewk->wu.mvxy.a[0].sp = 0x14FFFA;
        ewk->wu.mvxy.d[0].sp = 0x8000;
        ewk->wu.hit_quake = effD7_plate_pos[(s8)ewk->master_id][pos * 2];
    }
    ewk->wu.xyz[2].disp.pos = pos * 5 + 35;
    if (flag) {
        ewk->wu.xyz[1].disp.pos = y + 32;
    }
}

void effD7_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[2]) {
    case 0:
        ewk->wu.xyz[0].cal += ewk->wu.mvxy.a[0].sp;
        if (effD7_move_y(ewk)) {
            ewk->wu.routine_no[2]++;
            ewk->wu.dir_timer = 2;
            if (ewk->wu.routine_no[1] == 1) {
                ewk->wu.xyz[2].disp.pos = 45;
                if (ewk->master_id == 0) {
                    ewk->wu.mvxy.a[0].sp = 0x40000;
                } else {
                    ewk->wu.mvxy.a[0].sp = -0x40000;
                }
            } else {
                ewk->wu.xyz[2].disp.pos = 35;
            }
        }
        break;
    case 1:
        if (--ewk->wu.dir_timer) {
            break;
        }
        goto plate_turn;
    plate_turn:;
        ewk->wu.routine_no[2]++;
        OK_Priority[ewk->master_id] = 1;
        eff98_arts_req[(s8)ewk->master_id][0] = 1;
        eff98_arts_req[(s8)ewk->master_id][1] = 1;
        eff98_arts_req[(s8)ewk->master_id][2] = 1;
        effE4_col_req[(s8)ewk->master_id][0] = 1;
        effE4_col_req[(s8)ewk->master_id][1] = 1;
        effE4_col_req[(s8)ewk->master_id][2] = 1;
        if (ewk->wu.dm_vital == 0) {
            ewk->wu.direction = effD7_plate_pos[(s8)ewk->master_id][ewk->wu.dmcal_m * 2 + 1] + 16;
        } else {
            ewk->wu.direction = effD7_plate_pos[(s8)ewk->master_id][ewk->wu.dmcal_m * 2 + 1];
        }
        if (ewk->wu.routine_no[1] == 1) {
            ewk->wu.mvxy.a[1].sp = 0xC0000;
        } else {
            ewk->wu.mvxy.a[1].sp = -0xE0000;
        }
        ewk->wu.mvxy.d[1].sp = 0;
        break;
    case 2:
        effD7_move_x(ewk);
        if (effD7_move_y(ewk)) {
            ewk->wu.routine_no[2]++;
            ewk->wu.vital_old = ewk->wu.dmcal_m;
            Moving_Plate_Counter[ewk->master_id]--;
        }
        break;
    default:
        if (effD7_check_move(ewk)) {
            ewk->wu.routine_no[1] = 0;
            Moving_Plate[ewk->master_id] = 0;
        }
        break;
    }
}

s32 effD7_check_move(WORK_Other* ewk) {
    if (Moving_Plate_Counter[ewk->master_id] <= 6) {
        ewk->wu.routine_no[1] = 0;
        ewk->wu.xyz[2].disp.pos = ewk->wu.vital_old * 5 + 35;
        Moving_Plate_Counter[ewk->master_id]--;
        effD7_pattern(ewk, ewk->wu.vital_old);
        return 1;
    }
    return 0;
}

void effD7_move_back(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[2]) {
    case 0:
        if (--ewk->wu.dir_timer == 0) {
            ewk->wu.routine_no[2]++;
        }
        break;
    case 1:
        if (OK_Priority[ewk->master_id]) {
            ewk->wu.xyz[2].disp.pos = ewk->wu.dmcal_m * 5 + 35;
        }
        effD7_move_x(ewk);
        if (effD7_move_y(ewk)) {
            ewk->wu.routine_no[2]++;
            ewk->wu.vital_old = ewk->wu.dmcal_m;
            Moving_Plate_Counter[ewk->master_id]--;
        }
        break;
    default:
        if (OK_Priority[ewk->master_id]) {
            ewk->wu.xyz[2].disp.pos = ewk->wu.dmcal_m * 5 + 35;
        }
        if (effD7_check_move(ewk)) {
            ewk->wu.routine_no[1] = 0;
        }
        break;
    }
}

void effD7_setup_left(WORK_Other* ewk) {
    s16 ofs;
    if (--Moving_Plate_Counter[ewk->master_id] == 6) {
        Moving_Plate[ewk->master_id] = 0;
    }
    if (ewk->master_id == 0) {
        ofs = 0;
        ewk->wu.mvxy.a[0].sp = -0x10000;
    } else {
        ofs = DE_X[5];
        ewk->wu.mvxy.a[0].sp = 0x10000;
    }
    ewk->wu.dmcal_m = 2;
    ewk->wu.routine_no[1] = 1;
    ewk->wu.routine_no[2] = 0;
    ewk->wu.hit_quake = ofs + effD7_plate_pos[(s8)ewk->master_id][ewk->wu.dmcal_m * 2];
    ewk->wu.direction = ewk->wu.xyz[1].disp.pos - 24;
    ewk->wu.mvxy.a[1].sp = -0xE0000;
    ewk->wu.mvxy.d[1].sp = 0;
}

void effD7_setup_right(WORK_Other* ewk) {
    s16 ofs;
    if (--Moving_Plate_Counter[ewk->master_id] == 6) {
        Moving_Plate[ewk->master_id] = 0;
    }
    if (ewk->master_id == 0) {
        ofs = 0;
        ewk->wu.mvxy.a[0].sp = -0x20000;
    } else {
        ofs = DE_X[5];
        ewk->wu.mvxy.a[0].sp = 0x20000;
    }
    ewk->wu.dmcal_m = 0;
    ewk->wu.routine_no[1] = 2;
    ewk->wu.routine_no[2] = 0;
    ewk->wu.hit_quake = ofs + effD7_plate_pos[(s8)ewk->master_id][ewk->wu.dmcal_m * 2];
    ewk->wu.direction = ewk->wu.xyz[1].disp.pos + 32;
    ewk->wu.mvxy.a[1].sp = 0xC0000;
    ewk->wu.mvxy.d[1].sp = 0;
}

void effD7_setup_down(WORK_Other* ewk) {
    s16 ofs;
    if (--Moving_Plate_Counter[ewk->master_id] == 6) {
        Moving_Plate[ewk->master_id] = 0;
    }
    if (ewk->master_id == 0) {
        ofs = 0;
        ewk->wu.mvxy.a[0].sp = 0x10000;
    } else {
        ofs = DE_X[5];
        ewk->wu.mvxy.a[0].sp = -0x10000;
    }
    ewk->wu.dmcal_m = ewk->wu.vital_old + 1;
    ewk->wu.routine_no[1] = 3;
    ewk->wu.routine_no[2] = 0;
    ewk->wu.hit_quake = effD7_plate_pos[(s8)ewk->master_id][ewk->wu.dmcal_m * 2] + ofs;
    if (ewk->wu.dm_vital == 0) {
        ewk->wu.direction = effD7_plate_pos[(s8)ewk->master_id][ewk->wu.dmcal_m * 2 + 1] + 16;
    } else {
        ewk->wu.direction = effD7_plate_pos[(s8)ewk->master_id][ewk->wu.dmcal_m * 2 + 1];
    }
    ewk->wu.dir_timer = 2;
    ewk->wu.mvxy.a[1].sp = 0x20000;
    ewk->wu.mvxy.d[1].sp = 0;
}

void effD7_setup_up(WORK_Other* ewk) {
    s16 ofs;
    if (--Moving_Plate_Counter[ewk->master_id] == 6) {
        Moving_Plate[ewk->master_id] = 0;
    }
    if (ewk->master_id == 0) {
        ofs = 0;
        ewk->wu.mvxy.a[0].sp = -0x10000;
    } else {
        ofs = DE_X[5];
        ewk->wu.mvxy.a[0].sp = 0x10000;
    }
    ewk->wu.dmcal_m = ewk->wu.vital_old - 1;
    ewk->wu.routine_no[1] = 3;
    ewk->wu.routine_no[2] = 0;
    ewk->wu.hit_quake = effD7_plate_pos[(s8)ewk->master_id][ewk->wu.dmcal_m * 2] + ofs;
    if (ewk->wu.dm_vital == 0) {
        ewk->wu.direction = effD7_plate_pos[(s8)ewk->master_id][ewk->wu.dmcal_m * 2 + 1] + 16;
    } else {
        ewk->wu.direction = effD7_plate_pos[(s8)ewk->master_id][ewk->wu.dmcal_m * 2 + 1];
    }
    ewk->wu.dir_timer = 2;
    ewk->wu.mvxy.a[1].sp = -0x20000;
    ewk->wu.mvxy.d[1].sp = 0;
}

void effD7_move_x(WORK_Other* ewk) {
    ewk->wu.xyz[0].cal += ewk->wu.mvxy.a[0].sp;
    if (ewk->wu.mvxy.a[0].sp < 0) {
        if (ewk->wu.hit_quake >= ewk->wu.xyz[0].disp.pos) {
            ewk->wu.xyz[0].disp.pos = ewk->wu.hit_quake;
        }
    } else if (ewk->wu.hit_quake <= ewk->wu.xyz[0].disp.pos) {
        ewk->wu.xyz[0].disp.pos = ewk->wu.hit_quake;
    }
}

s32 effD7_move_y(WORK_Other* ewk) {
    ewk->wu.xyz[1].cal += ewk->wu.mvxy.a[1].sp;
    ewk->wu.mvxy.a[1].sp += ewk->wu.mvxy.d[1].sp;
    if (ewk->wu.mvxy.a[1].sp < 0) {
        if (ewk->wu.direction >= ewk->wu.xyz[1].disp.pos) {
            ewk->wu.xyz[1].disp.pos = ewk->wu.direction;
            return 1;
        }
    } else if (ewk->wu.direction <= ewk->wu.xyz[1].disp.pos) {
        ewk->wu.xyz[1].disp.pos = ewk->wu.direction;
        return 1;
    }
    return 0;
}

void effD7_set_position(WORK_Other* ewk, s16 flag) {
    s16 y;
    if (flag) {
        ewk->wu.xyz[0].disp.pos = effD7_plate_pos[(s8)ewk->master_id][0] + DE_X[5];
    } else {
        ewk->wu.xyz[0].disp.pos = effD7_plate_pos[(s8)ewk->master_id][0];
    }
    if (ewk->wu.dm_vital == 0) {
        y = 32;
    } else {
        y = 16;
    }
    ewk->wu.xyz[1].disp.pos = y + 16;
    ewk->wu.xyz[2].disp.pos = Super_Arts[flag] * 5 + 35;
}

s32 effD7_select_end(WORK_Other* ewk) {
    s32 ret;
    if (Sel_Arts_Complete[ewk->master_id] == 0) {
        return 0;
    }
    ret = 1;
    if (Super_Arts[ewk->master_id] == ewk->master_player) {
        ewk->wu.routine_no[0] = 4;
    } else {
        ewk->wu.routine_no[0]++;
    }
    return ret;
}

s32 effect_D7_init(s16 pl_id, s16 plate_id, s16 pos_id, s16 time, s16 type) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    eff98_arts_req[(s8)pl_id][plate_id] = 0;
    effE4_col_req[(s8)pl_id][plate_id] = 0;
    ewk->master_player = plate_id;
    ewk->master_priority = pos_id;
    effD7_init_common(ewk, pl_id, plate_id, time, type, pos_id);
    ewk->wu.vital_old = pos_id;
    ewk->wu.dmcal_m = pos_id;
    effD7_setup_pos(ewk);
    return 0;
}

s32 effect_D7_init2(s16 pl_id, s16 plate_id, s16 type) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    eff98_arts_req[(s8)pl_id][plate_id] = 0;
    effE4_col_req[(s8)pl_id][plate_id] = 0;
    ewk->wu.routine_no[0] = 8;
    ewk->wu.disp_flag = 1;
    ewk->master_player = plate_id;
    effD7_init_common(ewk, pl_id, plate_id, 1, type, 0);
    effD7_set_position(ewk, pl_id);
    set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index, ewk->wu.vital_new + 1, 0);
}

void effD7_init_common(ewk, pl_id, plate_id, time, type, pos_id)
WORK_Other* ewk;
s16 pl_id;
s16 plate_id;
s16 time;
s16 type;
s16 pos_id;
{
    s16 country;
    s16 chr;
    ewk->wu.be_flag = 1;
    ewk->wu.id = 137;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_family = 3;
    ewk->wu.dir_timer = time;
    ewk->wu.char_table[0] = sel_pl_char_table;
    ewk->master_id = pl_id;
    if (Country == 1) {
        country = 0;
    } else {
        country = 1;
    }
    if (ewk->wu.dm_vital = type) {
        ewk->wu.char_index = 28;
        chr = (My_char[pl_id] & 0x7F) * 3;
        ewk->wu.vital_new = pl_id * 39 + country * 78 + plate_id + chr;
        if (pl_id != 0) {
            goto plate_color;
        plate_color:;
            ewk->wu.my_col_code = 0x204D;
        } else {
            ewk->wu.my_col_code = 0x2040;
        }
    } else {
        ewk->wu.char_index = 27;
        ewk->wu.vital_new = country * 39 + (My_char[pl_id] & 0x7F) * 3 + plate_id;
        if (plw[pl_id].wu.operator) {
            effD7_pattern(ewk, pos_id);
        } else {
            effD7_pattern(ewk, 0);
        }
    }
}

void effD7_pattern(WORK_Other* ewk, s16 step) {
    if (ewk->wu.dm_vital == 0) {
        if (Sel_Arts_Complete[ewk->master_id] < 0) {
            step = 0;
        }
        ewk->wu.my_col_code = effD7_plate_col[(s8)ewk->master_id][step];
    }
    set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index, ewk->wu.vital_new + 1, 0);
}
