#ifndef PLCNTDAT_H
#define PLCNTDAT_H

#include "structs.h"

void debug_player_change(void);
void setup_base_and_other_data(void);
void clear_kizetsu_point(PLW* wk);
void set_base_data(PLW* wk, s16 ix);
void set_base_data_tiny(PLW* wk);
void set_player_shadow(PLW* wk);
void set_super_arts_status(s16 pl);
void setup_any_data(void);
void setup_other_data(PLW* wk);
void set_kizetsu_status();

#endif
