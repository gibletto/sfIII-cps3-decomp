/*
 * SHELL12_TBL.C  CPU anti-projectile pattern table 12 (Sean)
 *
 * Shell12_Tbl lists the pattern scripts Shell12_0000 .. Shell12_0010 the computer-controlled
 * Sean runs when the opponent fires a projectile, indexed by Pattern_Index. Read by SHELL12.C,
 * which Com_VS_Shell in COM_PL.C calls for Sean.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern void (*const Shell12_Tbl[])(PLW*);
extern void Shell12_0000();
extern void Shell12_0001();
extern void Shell12_0002();
extern void Shell12_0003();
extern void Shell12_0004();
extern void Shell12_0005();
extern void Shell12_0006();
extern void Shell12_0007();
extern void Shell12_0008();
extern void Shell12_0009();
extern void Shell12_0010();

void (*const Shell12_Tbl[11])(PLW*) = {
    Shell12_0000, Shell12_0001, Shell12_0002, Shell12_0003, Shell12_0004, Shell12_0005, Shell12_0006, Shell12_0007,
    Shell12_0008, Shell12_0009, Shell12_0010,
};
