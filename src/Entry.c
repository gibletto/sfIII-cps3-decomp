/*
 * ENTRY.C  Task control
 *
 * The game's cooperative tasks. Game_Task is the scheduler: each frame it walks the eight task control
 * blocks (task_tbl) and runs every task that is due. task_sleep_tick counts down the sleep timer of
 * every waiting task (status 1) and marks the task ready (status 2) when it reaches zero.
 * init_task_stacks gives each block its stack in task_stack; create_task, destroy_current_task,
 * kill_task, suspend_task, post_task and kill_tasks_by_func start, end, suspend and wake tasks. The
 * exception record and the task stacks are defined here; vblank_user_hook is empty.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "sys_config.h"
#include "sys_config_2.h"
#include "sys_config_3.h"
#include "Game.h"
#include "vbl_hook.h"

TCB * current_task;  /* 02007EEC */
s32 task_sys_w1;  /* 02007EF0 */
s32 task_sys_w2;  /* 02007EF4 */
s32 task_sys_w3;  /* 02007EF8 */
s32 task_free_count;  /* 02007EFC */
u32 system_timer;  /* 02007F00 */
u32 task_tick_mask;  /* 02007F04 */
s8 system_ctrl_flag;  /* 02007F08 */
s8 task_tick_mode;  /* 02007F09 */
s8 vsync_flag;  /* 02007F0A */
u32 frame_pass_count;  /* 02007F0C */
s8 task_ran_flag;  /* 02007F10 */
u32 task_sched_context[3];  /* 02007F14 */
SETTINGS game_config_work;  /* 02007F20 */
EXC_REGS exception_regs;  /* 02007F30 */
u32 exception_code;  /* 02007F8C */
u8 boot_stack[4100];  /* the stack r15 starts on: vector 1 points at its end (task_stack); provisional name */
u8 task_stack[18][1024];  /* 02008F94 */
TCB task_tbl[8];  /* 0200D794 */
static u8 task_spare[32];  /* nothing in the program refers to it */

/* The vertical blank interrupt calls this once per frame when bit 1 of the
   frame flag byte is set; it does nothing in this build. */
void vblank_user_hook(void) {
}

#pragma noregsave(Game_Task)



/* The task scheduler; never returns.  Each pass walks the eight task control
   blocks with interrupts masked and runs every task that is due, then lets
   interrupts in again before the next block.  A new vertical blank (vsync_flag)
   restarts the walk from the first block.  After a full pass: clear the sprite
   buffer if this is the first pass of the frame (unless the timers are ticked
   here), tick the sleep timers on the first two passes when the scheduler owns
   them (tick mode 3), note whether any task ran, count the pass and flip the
   frame. */
void Game_Task(void) {
    s32 i;
    s32 mode;
    TCB* tp;

    _builtin_set_imask(1);
    while (1) {
        vsync_flag = 0;
        frame_pass_count = 0;
        task_ran_flag = 0;
        i = 0;
        while (1) {
            _builtin_set_imask(15);
            if (vsync_flag != 0) {
                break;
            }
            current_task = &task_tbl[i];
            tp = current_task;
            mode = task_tick_mode;
            switch (tp->status) {
            case 0:
            case 1:
            case 5:
                break;
            case 2:
                if (mode == 1) {
                    break;
                }
                if (mode == 2) {
                    if (task_tick_mask & system_timer) {
                        break;
                    }
                }
            case 4:
                tp->status = 3;
            default:
                task_ran_flag = 1;
                task_dispatch(tp);
                break;
            }
            _builtin_set_imask(1);
            i++;
            if (i == 8) {
                i = 0;
                if (task_tick_mode != 3 && frame_pass_count == 0) {
                    tilemap_fill_column0(0, 32);
                }
                if (task_tick_mode == 3) {
                    if (frame_pass_count < 2) {
                        task_sleep_tick();
                    }
                }
                if (task_ran_flag == 0) {
                    frame_ready = 0;
                } else {
                    frame_ready = 1;
                }
                frame_pass_count++;
                task_ran_flag = 0;
                poly_bank_flip();
            }
        }
    }
}



/* provisional name */
void task_sleep_tick(void) {
    s32 i;
    for (i = 0; i < 8; i++) {
        if (task_tbl[i].status == 1) {
            task_tbl[i].state--;
            if (task_tbl[i].state == 0) {
                task_tbl[i].status = 2;
            }
        }
    }
}

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "EFFA2_MAIN.h"
#include "win_2.h"
#include "continue.h"
#include "pow_pow.h"
#include "n_input.h"
#include "SYS_sub.h"
#include "cmb_win.h"
#include "eff87.h"
#include "eff88.h"
#include "eff89.h"
#include "eff90.h"
#include "eff91.h"
#include "eff92_code.h"
#include "Eff93.h"
#include "sys_test.h"
#include "sys_test_2.h"
#include "sys_test_2b.h"
#include "sys_test_2c.h"
#include "sys_test_3.h"
#include "sys_test_4.h"
#include "sys_test_5.h"
#include "eeprom.h"
#include "SE.h"
#include "se_2.h"
#include "se_3.h"
#include "end_sub.h"
#include "end_sub_2.h"
#include "color3rd.h"
#include "end_sub_8.h"
#include "meta_col_mem.h"
#include "meta_col_strcpy.h"
#include "meta_col_lib.h"
#include "meta_col_bcd.h"
#include "sc_trans.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "entry_2.h"
#include "Entry.h"
#include "cps3.h"



/* 02000064 */
/* stack sizes beside the interrupt stack pointers; nothing in the program reads them (provisional name) */
u32 task_stack_size[3] = {
    1024, 256, 256,
};
s32 task_stack_num = 8;  /* 02000070 */
u32* isp_vblank = (u32*)&task_stack[9][0];  /* 02000074 */
u32* isp_sprite_poly = (u32*)&task_stack[10][0];  /* 02000078 */
u32* isp_irq_spare = (u32*)&task_stack[11][0];  /* 0200007C */
/* 02000080 */
/* stack pointers for two interrupts the game does not take (provisional name) */
void* isp_unused[2] = {
    &task_stack[12][0],
    &task_stack[13][0],
};
u32* isp_exception = (u32*)&task_stack[14][0];  /* 02000088 */
u32* isp_frt_compare = (u32*)&task_stack[15][0];  /* 0200008C */
u32* isp_frt_overflow = (u32*)&task_stack[16][0];  /* 02000090 */
u8 test_flag = 0;  /* 02000094 */


/* provisional name */
void init_task_stacks(void) {
    current_task = 0;
    task_sys_w3 = 0;
    task_sys_w1 = 0;
    task_sys_w2 = 0;
    for (task_free_count = 0; task_free_count < task_stack_num; task_free_count++) {
        task_tbl[task_free_count].stack_top = (u32*)&task_stack[task_free_count][1024];
    }
}



/* provisional name */
TCB* create_task(void (*entry)(), s32 unused, TCB* task, s16 priority, u32 arg) {
    if (task->status != 0) {
        return 0;
    }
    task_free_count--;
    task->parent = current_task;
    task->priority = priority;
    task->status = 4;
    task->state = 0;
    task->entry = entry;
    task->func = entry;
    task->sp = task->stack_top;
    task->sr = 0x10;
    task->creator = current_task;
    task->arg = arg;
    task->wait = 0;
    task->timer = 0;
    return task;
}



/* provisional name */
void destroy_current_task(void) {
    _builtin_set_imask(15);
    current_task->status = 0;
    task_free_count++;
    task_exit_to_system();
}



/* provisional name: stop another task (1 = it is the running task, 2 = not active) */
s32 kill_task(TCB* task) {
    if (task == current_task) {
        return 1;
    }
    if (task->status == 0) {
        return 2;
    }
    task->status = 0;
    task_free_count++;
    return 0;
}



/* provisional name: put a task to sleep until woken (2 = not active) */
s32 suspend_task(TCB* task) {
    if (task->status == 0) {
        return 2;
    }
    task->status = 5;
    return 0;
}



/* provisional name: hand a task a value from the running task, mode 1 also sets it waiting */
s32 post_task(TCB* task, u32 arg, s32 mode) {
    if (task == current_task) {
        return 1;
    }
    if (task->status == 0) {
        return 2;
    }
    if (mode == 1) {
        task->status = 2;
    }
    task->creator = current_task;
    task->wait = arg;
    return 0;
}



/* provisional name */
void kill_tasks_by_func(void (*func)()) {
    s32 i;
    TCB* tp;
    for (i = 0; i < 8; i++) {
        if (task_tbl[i].status != 0) {
            if ((tp = &task_tbl[i])->func == func && current_task != tp) {
                task_tbl[i].status = 0;
                task_free_count++;
            }
        }
    }
}



/* provisional name */
void kill_tasks_by_priority(prio, mode)
s32 prio;
s32 mode;
{
    s32 i;
    for (i = 0; i < 8; i++) {
        if (&task_tbl[i] != current_task) {
            switch (mode) {
            case 0:
                if (task_tbl[i].priority <= prio) {
                    if (task_tbl[i].status != 0) {
                        task_tbl[i].status = 0;
                        task_free_count++;
                    }
                }
                break;
            case 2:
                if (task_tbl[i].priority >= prio) {
                    if (task_tbl[i].status != 0) {
                        task_tbl[i].status = 0;
                        task_free_count++;
                    }
                }
                break;
            default:
                if (task_tbl[i].priority == prio) {
                    if (task_tbl[i].status != 0) {
                        task_tbl[i].status = 0;
                        task_free_count++;
                    }
                }
                break;
            }
        }
    }
}
