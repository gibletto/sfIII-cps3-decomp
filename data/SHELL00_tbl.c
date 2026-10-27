/*
 * SHELL00_TBL.C  CPU anti-projectile pattern table 00 (Gill)
 *
 * Shell00_Tbl lists the pattern scripts Shell00_0000 .. Shell00_0010, indexed by
 * Pattern_Index. Read by SHELL00.C; Com_VS_Shell in COM_PL.C gives Gill SHELL11's patterns, so
 * nothing calls SHELL00 and these patterns are not run.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern void (*const Shell00_Tbl[])(PLW*);
extern void Shell00_0000();
extern void Shell00_0001();
extern void Shell00_0002();
extern void Shell00_0003();
extern void Shell00_0004();
extern void Shell00_0005();
extern void Shell00_0006();
extern void Shell00_0007();
extern void Shell00_0008();
extern void Shell00_0009();
extern void Shell00_0010();

void (*const Shell00_Tbl[11])(PLW*) = {
    Shell00_0000, Shell00_0001, Shell00_0002, Shell00_0003, Shell00_0004, Shell00_0005, Shell00_0006, Shell00_0007,
    Shell00_0008, Shell00_0009, Shell00_0010,
};
