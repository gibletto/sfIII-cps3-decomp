/*
 * EFFECT_TBL.C  effect routine jump tables
 *
 * effmovejptbl is the move routine of every effect, indexed by effect id (00 .. H9), called by
 * EFFECT.C, the effect work manager, each frame. effinitjptbl is the list of the 37 effect
 * starters and setters called from character scripts by CHARMOVE.C (comm_exec and the cg
 * effect field). jdb and jdb2 give, by the extra DIP switch setting, which judgement boxes are
 * shown and their cell count; read by EFF00.C, the judgement box display. parts_colmd_table
 * and parts_colcd_table give the colour mode and colour code of overlay parts; read by
 * EFF01_CODE.C, the overlay parts.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const void (*const effmovejptbl[])();
extern const s32 (*const effinitjptbl[])();
extern const u16 jdb[];
extern const u16 jdb2[];
extern const s16 parts_colmd_table[];
extern const s16 parts_colcd_table[];
extern void clear_caution_flag();
extern void effect_00_move();
extern void effect_01_move();
extern void effect_02_move();
extern void effect_03_init();
extern void effect_03_move();
extern void effect_04_move();
extern void effect_05_move();
extern void effect_06_move();
extern void effect_07_move();
extern void effect_08_move();
extern void effect_09_init();
extern void effect_09_init2();
extern void effect_09_move();
extern void effect_10_move();
extern void effect_11_move();
extern void effect_12_move();
extern void effect_13_init();
extern void effect_13_move();
extern void effect_14_move();
extern void effect_15_move();
extern void effect_16_move();
extern void effect_17_move();
extern void effect_18_move();
extern void effect_19_move();
extern void effect_20_move();
extern void effect_21_move();
extern void effect_22_move();
extern void effect_23_move();
extern void effect_24_move();
extern void effect_25_move();
extern void effect_26_move();
extern void effect_27_move();
extern void effect_28_move();
extern void effect_29_move();
extern void effect_30_init();
extern void effect_30_move();
extern void effect_31_move();
extern void effect_32_move();
extern void effect_33_move();
extern void effect_34_move();
extern void effect_35_move();
extern void effect_36_move();
extern void effect_37_init();
extern void effect_37_move();
extern void effect_38_move();
extern void effect_39_move();
extern void effect_40_move();
extern void effect_41_init();
extern void effect_41_move();
extern void effect_42_move();
extern void effect_43_move();
extern void effect_44_move();
extern void effect_45_move();
extern void effect_46_move();
extern void effect_47_move();
extern void effect_48_move();
extern void effect_49_move();
extern void effect_50_move();
extern void effect_51_move();
extern void effect_52_move();
extern void effect_53_move();
extern void effect_54_init();
extern void effect_54_move();
extern void effect_55_move();
extern void effect_56_move();
extern void effect_57_move();
extern void effect_58_move();
extern void effect_59_move();
extern void effect_60_move();
extern void effect_61_move();
extern void effect_62_move();
extern void effect_63_move();
extern void effect_64_move();
extern void effect_65_move();
extern void effect_66_move();
extern void effect_67_move();
extern void effect_68_move();
extern void effect_69_move();
extern void effect_70_move();
extern void effect_71_move();
extern void effect_72_move();
extern void effect_73_move();
extern void effect_74_move();
extern void effect_75_move();
extern void effect_76_move();
extern void effect_77_move();
extern void effect_78_move();
extern void effect_79_move();
extern void effect_80_move();
extern void effect_81_move();
extern void effect_82_move();
extern void effect_83_move();
extern void effect_84_move();
extern void effect_85_move();
extern void effect_86_move();
extern void effect_87_move();
extern void effect_88_move();
extern void effect_89_move();
extern void effect_90_move();
extern void effect_91_move();
extern void effect_92_move();
extern void effect_93_move();
extern void effect_94_move();
extern void effect_95_move();
extern void effect_96_move();
extern void effect_97_move();
extern void effect_98_move();
extern void effect_99_move();
extern void effect_A0_move();
extern void effect_A1_move();
extern void effect_A2_move();
extern void effect_A3_move();
extern void effect_A4_move();
extern void effect_A5_move();
extern void effect_A6_move();
extern void effect_A7_move();
extern void effect_A8_move();
extern void effect_A9_move();
extern void effect_B0_move();
extern void effect_B1_move();
extern void effect_B2_move();
extern void effect_B3_move();
extern void effect_B4_move();
extern void effect_B5_move();
extern void effect_B6_move();
extern void effect_B7_move();
extern void effect_B8_move();
extern void effect_B9_move();
extern void effect_C0_init();
extern void effect_C0_move();
extern void effect_C1_move();
extern void effect_C2_move();
extern void effect_C3_move();
extern void effect_C4_move();
extern void effect_C5_move();
extern void effect_C6_move();
extern void effect_C7_init();
extern void effect_C7_move();
extern void effect_C8_move();
extern void effect_C9_move();
extern void effect_D0_init();
extern void effect_D0_move();
extern void effect_D1_init();
extern void effect_D1_move();
extern void effect_D2_move();
extern void effect_D3_move();
extern void effect_D4_init();
extern void effect_D4_move();
extern void effect_D5_move();
extern void effect_D6_move();
extern void effect_D7_move();
extern void effect_D8_move();
extern void effect_D9_init();
extern void effect_D9_move();
extern void effect_E0_move();
extern void effect_E1_move();
extern void effect_E2_move();
extern void effect_E3_move();
extern void effect_E4_move();
extern void effect_E5_move();
extern void effect_E6_move();
extern void effect_E7_move();
extern void effect_E8_move();
extern void effect_E9_move();
extern void effect_F0_move();
extern void effect_F1_init();
extern void effect_F1_move();
extern void effect_F2_move();
extern void effect_F3_move();
extern void effect_F4_init();
extern void effect_F4_move();
extern void effect_F5_move();
extern void effect_F6_move();
extern void effect_F7_move();
extern void effect_F8_init();
extern void effect_F8_move();
extern void effect_F9_move();
extern void effect_G0_init();
extern void effect_G0_move();
extern void effect_G1_move();
extern void effect_G2_move();
extern void effect_G3_init();
extern void effect_G3_move();
extern void effect_G4_init();
extern void effect_G4_move();
extern void effect_G5_move();
extern void effect_G6_init();
extern void effect_G6_move();
extern void effect_G7_move();
extern void effect_G8_move();
extern void effect_G9_move();
extern void effect_H0_move();
extern void effect_H1_move();
extern void effect_H2_move();
extern void effect_H3_move();
extern void effect_H4_move();
extern void effect_H5_move();
extern void effect_H6_move();
extern void effect_H7_init();
extern void effect_H7_move();
extern void effect_H8_init();
extern void effect_H8_move();
extern void effect_H9_init();
extern void effect_H9_move();
extern void erase_after_images();
extern void exec_char_asxy();
extern void flip_my_rl_flag();
extern void reset_extra_bg_flag();
extern void set_caution_flag();
extern void set_tenguiwa();
extern void setup_accessories();
extern void setup_after_images();
extern void setup_ase_extra();
extern void setup_meoshi_hit_flag();
extern void setup_status_flag();

const void (*const effmovejptbl[180])() = {
    effect_00_move, effect_01_move, effect_02_move, effect_03_move,
    effect_04_move, effect_05_move, effect_06_move, effect_07_move,
    effect_08_move, effect_09_move, effect_10_move, effect_11_move,
    effect_12_move, effect_13_move, effect_14_move, effect_15_move,
    effect_16_move, effect_17_move, effect_18_move, effect_19_move,
    effect_20_move, effect_21_move, effect_22_move, effect_23_move,
    effect_24_move, effect_25_move, effect_26_move, effect_27_move,
    effect_28_move, effect_29_move, effect_30_move, effect_31_move,
    effect_32_move, effect_33_move, effect_34_move, effect_35_move,
    effect_36_move, effect_37_move, effect_38_move, effect_39_move,
    effect_40_move, effect_41_move, effect_42_move, effect_43_move,
    effect_44_move, effect_45_move, effect_46_move, effect_47_move,
    effect_48_move, effect_49_move, effect_50_move, effect_51_move,
    effect_52_move, effect_53_move, effect_54_move, effect_55_move,
    effect_56_move, effect_57_move, effect_58_move, effect_59_move,
    effect_60_move, effect_61_move, effect_62_move, effect_63_move,
    effect_64_move, effect_65_move, effect_66_move, effect_67_move,
    effect_68_move, effect_69_move, effect_70_move, effect_71_move,
    effect_72_move, effect_73_move, effect_74_move, effect_75_move,
    effect_76_move, effect_77_move, effect_78_move, effect_79_move,
    effect_80_move, effect_81_move, effect_82_move, effect_83_move,
    effect_84_move, effect_85_move, effect_86_move, effect_87_move,
    effect_88_move, effect_89_move, effect_90_move, effect_91_move,
    effect_92_move, effect_93_move, effect_94_move, effect_95_move,
    effect_96_move, effect_97_move, effect_98_move, effect_99_move,
    effect_A0_move, effect_A1_move, effect_A2_move, effect_A3_move,
    effect_A4_move, effect_A5_move, effect_A6_move, effect_A7_move,
    effect_A8_move, effect_A9_move, effect_B0_move, effect_B1_move,
    effect_B2_move, effect_B3_move, effect_B4_move, effect_B5_move,
    effect_B6_move, effect_B7_move, effect_B8_move, effect_B9_move,
    effect_C0_move, effect_C1_move, effect_C2_move, effect_C3_move,
    effect_C4_move, effect_C5_move, effect_C6_move, effect_C7_move,
    effect_C8_move, effect_C9_move, effect_D0_move, effect_D1_move,
    effect_D2_move, effect_D3_move, effect_D4_move, effect_D5_move,
    effect_D6_move, effect_D7_move, effect_D8_move, effect_D9_move,
    effect_E0_move, effect_E1_move, effect_E2_move, effect_E3_move,
    effect_E4_move, effect_E5_move, effect_E6_move, effect_E7_move,
    effect_E8_move, effect_E9_move, effect_F0_move, effect_F1_move,
    effect_F2_move, effect_F3_move, effect_F4_move, effect_F5_move,
    effect_F6_move, effect_F7_move, effect_F8_move, effect_F9_move,
    effect_G0_move, effect_G1_move, effect_G2_move, effect_G3_move,
    effect_G4_move, effect_G5_move, effect_G6_move, effect_G7_move,
    effect_G8_move, effect_G9_move, effect_H0_move, effect_H1_move,
    effect_H2_move, effect_H3_move, effect_H4_move, effect_H5_move,
    effect_H6_move, effect_H7_move, effect_H8_move, effect_H9_move,
};

const s32 (*const effinitjptbl[37])() = {
    0, effect_03_init, effect_13_init, effect_09_init,
    effect_54_init, effect_C0_init, effect_C7_init, effect_D0_init,
    effect_D1_init, effect_F4_init, effect_30_init, effect_37_init,
    effect_09_init2, effect_41_init, effect_D4_init, set_tenguiwa,
    effect_D9_init, setup_accessories, setup_after_images, erase_after_images,
    effect_F1_init, clear_caution_flag, setup_status_flag, reset_extra_bg_flag,
    flip_my_rl_flag, effect_F8_init, effect_G0_init, effect_G3_init,
    effect_G4_init, setup_ase_extra, effect_G6_init, setup_meoshi_hit_flag,
    exec_char_asxy, set_caution_flag, effect_H7_init, effect_H8_init,
    effect_H9_init,
};

const u16 jdb[16] = {
    0, 0x1F, 0xC0, 0xDF, 0x120, 0x13F, 0x1E0, 0x1FF, 0x200, 0x21F, 0x2C0, 0x2DF, 0x320, 0x33F, 0x3E0, 0x3FF,
};

const u16 jdb2[16] = {
    0, 0x14, 8, 0x1C, 8, 0x1C, 0x10, 0x24, 4, 0x18, 0xC, 0x20, 0xC, 0x20, 0x14, 0x28,
};

const s16 parts_colmd_table[2] = {
    16384, 0,
};

const s16 parts_colcd_table[6] = {
    8192, 0, 6, 8192, 4, 8224,
};
