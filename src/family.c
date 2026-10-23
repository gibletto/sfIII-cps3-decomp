/*
 * family.c  Scroll family position setters
 *
 * The scroll "family" helpers keep the fm_pos[] table of plane positions: Family_Init
 * zeroes all eight entries, Family_Set_R sets both the target and current position of a family
 * at once, and Family_Set_W sets only the target position (used by the BG, opening and ending code).
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "fifo.h"
#include "sys_test.h"
#include "cps3.h"
SCRLPOS fm_pos[8];  /* 0206A084 */


/* provisional name */
void Family_Init(void)
{
    s32 i;

    for (i = 0; i < 8; i++) {
        fm_pos[i].set_x.cal = 0;
        fm_pos[i].set_y.cal = 0;
        fm_pos[i].cur_x.cal = 0;
        fm_pos[i].cur_y.cal = 0;
    }
}



void Family_Set_R(n, x, y)
s32 n;
s16 x;
s16 y;
{
    fm_pos[n].set_x.disp.pos = x;
    fm_pos[n].set_y.disp.pos = y;
    fm_pos[n].cur_x.disp.pos = x;
    fm_pos[n].cur_y.disp.pos = y;
}



void Family_Set_W(plane, x, y)
s32 plane;
s16 x;
s16 y;
{
    fm_pos[plane].set_x.disp.pos = x;
    fm_pos[plane].set_y.disp.pos = y;
}



/* provisional name */
void Family_Add_W(n, dx, dy)
s32 n;
s32 dx;
s32 dy;
{
    fm_pos[n].set_x.cal += dx;
    fm_pos[n].set_y.cal += dy;
    fm_pos[n].set_x.disp.pos &= 0x3FF;
    fm_pos[n].set_y.disp.pos &= 0x3FF;
}



void Irl_Family(void) {
    volatile u16* reg;
    s32 i;
    u16 v;
    reg = (volatile u16*)VIDEO_REG;
    for (i = 0; i < 8; i++) {
        v = fm_pos[i].cur_x.disp.pos - zoom_adj_x + flip_obj_ofs_x;
        *reg = v & 0x3FF;
        reg++;
        v = fm_pos[i].cur_y.disp.pos + zoom_adj_y + flip_obj_ofs_y + 0xFFFE;
        *reg = v & 0x3FF;
        reg++;
        fm_pos[i].cur_x.cal = fm_pos[i].set_x.cal;
        fm_pos[i].cur_y.cal = fm_pos[i].set_y.cal;
    }
}
