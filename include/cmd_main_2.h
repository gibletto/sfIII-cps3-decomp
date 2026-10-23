#ifndef CMD_MAIN_2_H
#define CMD_MAIN_2_H

#include "structs.h"

void basic_waza_flag_clear(s16 pl_id);
void check_0(void);
void check_1(void);
void check_10(void);
void check_11(void);
void check_12(void);
void check_13(void);
void check_14(void);
void check_15(void);
void check_16(void);
void check_18(void);
void check_19(void);
void check_2(void);
void check_20(void);
void check_21(void);
void check_22(void);
void check_23(void);
void check_24(void);
void check_25(void);
void check_3(void);
void check_4(void);
void check_5(void);
void check_6(void);
void check_7(void);
void check_9(void);
void check_init(void);
void check_next(void);
void cmd_data_set(PLW* , s16 i);
void cmd_init(PLW* pl);
void cmd_move(void);
void command_ok(void);
void command_ok_move(s16 waza_num);
void dash_flag_clear(s16 pl_id);
s8 dead_lvr_check(void);
void hi_jump_flag_clear(s16 pl_id);
s32 paring_miss_init(void);
void pl_lvr_set(void);
void sw_pick_up(void);
void waza_check(PLW* pl);
void waza_compel_all_init(PLW* pl);
void waza_compel_init();
void waza_compel_all_init2(PLW* pl);

#endif
