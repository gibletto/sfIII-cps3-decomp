#ifndef PLCNTSET_2_H
#define PLCNTSET_2_H

#include "structs.h"

void setup_settle_rno();
s32 check_sa_resurrection(PLW* wk);
void reset_char_disp_work(WORK* wk);
void check_damage_hosei(void);
void add_next_position(PLW* wk);
s32 check_sa_type_rebirth(PLW* wk);
s32 footwork_check(char pl);
s32 nekorobi_check(char pl);
void plcnt_die(void);
void plcnt_move(void);
void set_quake(PLW* wk);
void settle_check(void);
void settle_type_00000(void);
void settle_type_10000(void);
void settle_type_20000(void);
void settle_type_30000(void);
s32 time_over_check(void);
s32 will_die(void);
void init_app_10000(void);
void init_app_20000(void);
void init_app_30000(void);
void pli_0000(void);
void pli_1000(void);

#endif
