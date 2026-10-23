/*
 * CD_VOLUME.C  the CD-ROM's volume identifier (section CDVOL, 067FFFE0)
 *
 * The self test reads the CD's primary volume descriptor and compares its volume identifier with the copy at
 * 067FFFE0. The program holds it once, at the end of its 8 MB, and only its 12 characters: the rest of the last
 * 32 bytes is outside the link (holes.tsv).
 */

#include "types.h"

#pragma section CDVOL

const s8 game_volume_id[12] = "CAP-SF3-3   ";
