#ifndef END_SUB_2_H
#define END_SUB_2_H

#include "structs.h"

void cd_error_fatal_hang(s32 kind);
void cd_keep_spinning_tick(void);
void cd_selftest_periodic(void);
s32 staff_roll_main();
s32 staff_roll_skip_check(void);
void staff_roll_put();

#endif
