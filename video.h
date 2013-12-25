#ifndef __6502_VIDEO__

#include "cpu.h"

#define IO_VWIDTH       160
#define IO_VHEIGHT      100

#define IO_VMODE        0xFF02
#define IO_VFLAG_ENABLE 0x01
#define IO_VFLAG_FLIP   0x02

#define IO_VSTART       0xD000
#define IO_VSIZE        0x1F40
#define IO_VEND         0xEF40
#define IO_VPIXELS      (IO_VWIDTH * IO_VHEIGHT)

#define IO_VCOLORS      16
// start address of color table
#define IO_VCTABS       0xEF40
// end address of color table
#define IO_VCTABE       0xEF50
// bits of red in encoded 8-bit coor
#define IO_VRBITS       0xE0
// bits of green in encoded 8-bit coor
#define IO_VGBITS       0x1C
// bits of blue in encoded 8-bit coor
#define IO_VBBITS       0x03

void init_video(cpu *m);
void finish_video();
int handle_video(cpu *m);

#endif
