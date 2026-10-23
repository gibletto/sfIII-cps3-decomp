#ifndef EXTERN_H
#define EXTERN_H

#include "structs.h"

void task_exit_to_system(void);
void bios_vector_restart(s32 mode, s32 arg);
char * _builtin_strcpy(char* dst, const char* src);
void cpu_hang_forever(void);
void damage_atemi_setup(PLW* wk, PLW* ek);
void task_sleep(s32 frames);
void task_wait(void);
void task_dispatch(TCB* task);

#endif
