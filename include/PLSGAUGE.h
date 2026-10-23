#ifndef PLSGAUGE_H
#define PLSGAUGE_H

#include "structs.h"

void add_sp_arts_gauge_hit_dm(PLW* wk);
void add_sp_arts_gauge_init(PLW* wk);
void add_sp_arts_gauge_paring(PLW* wk);
s32 add_super_arts_gauge();
void cal_dm_vital_gauge_hosei(PLW* wk);
s16 check_buttobi_type(PLW* wk);
void dead_voice_request(void);
void dead_voice_request2(PLW* wk);
s32 check_buttobi_type2(WORK* wk);
void add_sp_arts_gauge_guard(PLW* wk);
void set_hit_stop_hit_quake(WORK* wk);
void setup_lvdir_after_autodir(PLW* wk);
void setup_saishin_lvdir();
void setup_vitality(WORK* wk, s16 pno);

s32 get_kind_of_head_dm(s16 dir, char rl);
s32 get_kind_of_trunk_dm(s16 dir, char rl);

s32 get_buttobi_attlv(PLW* wk);   /* provisional name */
s32 get_buttobi_attlv2(PLW* wk);  /* provisional name */
void pl_voice_request(s8 pl, u8 kind);  /* provisional name */
#endif
