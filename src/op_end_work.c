/*
 * OP_END_WORK.C  ending tables and opening/ending work
 *
 * The ending routine tables and the panel and cell pointer tables of the endings (end_4.c, end_8.c, end_10.c,
 * end_11.c, end_main_c.c): initialised work RAM (section D). The opening and ending work (section B): op_w, end_w
 * and their flags.
 */

#include "types.h"
#include "structs.h"

extern void (*end_main_jp[])(s16);
extern const s16* end_map_tbl[];
extern const PANEL* end_4_panel_p[];
extern const PANEL* end_8_panel_p[];
extern const PANEL* end_10_panel_p[];
extern void (*end_10_jp[])();
extern const s32* end_11_cell_ptr0[];
extern const s32* end_11_cell_ptr1[];
extern const s32* end_11_cell_ptr1_tail[];
extern const PANEL end_10_panel_tbl_0[];
extern const PANEL end_10_panel_tbl_1[];
extern const PANEL end_400_panel0[];
extern const PANEL end_400_panel1[];
extern const PANEL end_800_panel0[];
extern const PANEL end_800_panel1[];
extern const s16 end_map_data_0[];
extern const s16 end_map_data_1[];
extern const s16 end_map_data_2[];
extern const s16 end_map_data_3[];
extern const s32 end_1100_cell0[];
extern const s32 end_1100_cell1[];
extern const s32 end_1100_cell2[];
extern const s32 end_1100_cell3[];
extern const s32 end_1100_cell4[];
extern const s32 end_1100_cell5[];
extern const s32 end_1100_cell6[];
extern const s32 end_1100_cell7[];
extern void end_00000();
extern void end_01000();
extern void end_02000();
extern void end_03000();
extern void end_04000();
extern void end_05000();
extern void end_06000();
extern void end_07000();
extern void end_08000();
extern void end_09000();
extern void end_10000();
extern void end_1000_0000();
extern void end_1000_1000();
extern void end_1000_2000();
extern void end_1000_3000();
extern void end_1000_4000();
extern void end_1000_5000();
extern void end_1000_6000();
extern void end_11000();

/* 020066D4 */
void (*end_main_jp[13])(s16) = {
    end_00000, end_01000, end_02000, end_03000, end_04000, end_05000, end_06000, end_07000,
    end_08000, end_09000, end_03000, end_10000, end_11000,
};

/* 02006708 */
const s16* end_map_tbl[4] = {
    end_map_data_0, end_map_data_1, end_map_data_2, end_map_data_3,
};

/* 02006718 */
const PANEL* end_4_panel_p[2] = {
    end_400_panel0, end_400_panel1,
};

/* 02006720 */
const PANEL* end_8_panel_p[2] = {
    end_800_panel0, end_800_panel1,
};

/* 02006728 */
const PANEL* end_10_panel_p[2] = {
    end_10_panel_tbl_0, end_10_panel_tbl_1,
};

/* 02006730 */
void (*end_10_jp[7])() = {
    end_1000_0000, end_1000_1000, end_1000_2000, end_1000_3000,
    end_1000_4000, end_1000_5000, end_1000_6000,
};

/* 0200674C */
const s32* end_11_cell_ptr0[9] = {
    end_1100_cell0, end_1100_cell1, end_1100_cell2, end_1100_cell3,
    end_1100_cell3, end_1100_cell4, end_1100_cell3, end_1100_cell5,
    end_1100_cell0,
};

/* 02006770 */
const s32* end_11_cell_ptr1[9] = {
    end_1100_cell6, end_1100_cell7, end_1100_cell7, end_1100_cell7,
    end_1100_cell6, end_1100_cell6, end_1100_cell7, end_1100_cell6,
    end_1100_cell6,
};

/* 02006794 */
/* one more cell list pointer after end_11_cell_ptr1; nothing in the program refers to it by name or
   address */
const s32* end_11_cell_ptr1_tail[1] = {
    end_1100_cell6,
};

OP_W op_w;  /* 0201D6D8 */
s16 op_end_flag;  /* 0201D6E2 */
s16 op_obj_disp;  /* 0201D6E4 */
s8 effE1_end_flag;  /* 0201D6E6, provisional name */
s8 op_fade_flag;  /* 0201D6E7 */
END_W end_w;  /* 0201D6E8 */
s16 ls_rate1;  /* 0201D6F4 */
s8 end_etc_flag;  /* 0201D6F6 */
s8 ending_all_end;  /* 0201D6F7 */
s8 end_fade_flag;  /* 0201D6F8 */
s8 end_no_cut;  /* 0201D6F9 */
s16 end_fade_timer;  /* 0201D6FA */
s8 end_name_cut;  /* 0201D6FC */
s8 end_staff_flag;  /* 0201D6FD */
u8 end_cont_coin;  /* 0201D6FE */
s32 staff_r_no;  /* 0201D700 */
/* after staff_r_no: nothing refers to it by name or address */
u8 staff_r_no_tail[4];  /* 0201D704 */
s32 end_2_bg0_step;  /* 0201D708 */
s32 end_2_bg1_step;  /* 0201D70C */
s32 end_2_timer;  /* 0201D710 */
