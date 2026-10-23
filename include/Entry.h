#ifndef ENTRY_H
#define ENTRY_H

#include "structs.h"

void dbg_memory_dump_rows(u16* tbl);
TCB* create_task(void (*entry)(), s32 unused, TCB* task, s16 priority, u32 arg);
void dbg_disasm_rows(u16* tbl);
void destroy_current_task(void);
s32 kill_task(TCB* task);
s32 suspend_task(TCB* task);
s32 post_task(TCB* task, u32 arg, s32 mode);
void init_task_stacks(void);
void kill_tasks_by_func(void (*func)());
void disasm_sh_opcode(u16 code, char* str);
void kill_tasks_by_priority();

#endif
