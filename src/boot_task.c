/*
 * BOOT_TASK.C  First task of the system and the task request queue
 *
 * boot_task starts mode_init_task and then serves the task request queue; kill_mode_tasks
 * empties the queue and ends the mode tasks; text_clear_task_exit clears the text layer and
 * ends the calling task.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "Com_Sub.h"
#include "ACTIVE00.h"
#include "active01.h"
#include "active02.h"
#include "active03.h"
#include "active04.h"
#include "active05.h"
#include "active07.h"
#include "active08.h"
#include "active09.h"
#include "active11.h"
#include "active12.h"
#include "FOLLOW01.h"
#include "FOLLOW02.h"
#include "fifo.h"
#include "sys_test.h"
#include "sys_test_2.h"
#include "sys_test_2b.h"
#include "sys_test_2c.h"
#include "sys_test_3.h"
#include "sys_test_4.h"
#include "sys_test_5.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "pass00.h"
#include "PASS01.h"
#include "PASS02.h"
#include "PASS03.h"
#include "PASS04.h"
#include "PASS05.h"
#include "PASS07.h"
#include "PASS08.h"
#include "PASS09.h"
#include "PASS11.h"
#include "PASS12.h"
#include "SHELL00.h"
#include "SHELL01.h"
#include "SHELL03.h"
#include "SHELL04.h"
#include "SHELL11.h"
#include "SHELL12.h"
#include "Entry.h"
#include "entry_2.h"
#include "CMD_MAIN.h"
#include "cmd_main_2.h"
#include "sys_config.h"
#include "sys_config_2.h"
#include "sys_config_3.h"
#include "PLS02.h"
#include "SE.h"
#include "se_2.h"
#include "se_3.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "end_sub.h"
#include "end_sub_2.h"
#include "color3rd.h"
#include "end_sub_8.h"
#include "sc_trans.h"
#include "Manage.h"
#include "manage_2.h"
#include "bg0001.h"
#include "Com_Pl.h"
#include "cps3.h"
#include "fighter.h"
#include "RANKING.h"

TASK_QUEUE task_req_queue;  /* 0200D9B4 */
u8 task_req_buff[716];  /* 0200D9C8 */

#pragma noregsave(boot_task)




/* First task of the system.  Set up the task request queue and start
   mode_init_task in task slot 0, retrying until a slot is free.  From then on
   serve the queue: whenever task slot 6 is free and a request is waiting, start
   the requested routine there at priority 4; otherwise give up the frame. */
/* provisional name */
void boot_task(void) {
    TASK_REQ* req;
    TCB* initial_task;
    void (*initial_entry)();

    task_sleep(3);
    fifo_init((u32*)&task_req_queue, (u32)task_req_buff, 200);
    initial_task = task_tbl;
    initial_entry = mode_init_task;
    req = 0;
    while (create_task(initial_entry, 0, initial_task, 1, (s32)req) == 0) {
    }
    do {
        if (task_tbl[6].status == 0) {
            req = (TASK_REQ*)fifo_get((FIFO32*)&task_req_queue);
            if (req == 0) {
            } else {
                create_task(req->func, 2, &task_tbl[6], 4, req->arg);
                continue;
            }
        }
        task_wait();
        if (0) {
            create_task(req->func, 2, &task_tbl[6], 4, req->arg);
        }
    } while (1);
}



/* provisional name */
void kill_mode_tasks(void) {
    fifo_init(&task_req_queue, task_req_buff, 200);
    kill_tasks_by_priority(4, 2);
}



/* provisional name */
void text_clear_task_exit(void) {
    tilemap_fill_all(0, 32);
    destroy_current_task();
}
