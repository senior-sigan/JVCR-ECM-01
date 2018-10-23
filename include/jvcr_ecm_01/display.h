#ifndef JVCR_ECM_01_VIDEO_H
#define JVCR_ECM_01_VIDEO_H

#include <jvcr_ecm_01/machine.h>

void cls(Jvcr *machine, i32 color); // clear screen; col = clear color
void camera(Jvcr *machine, i32 x, i32 y); // set camera position
void clip(Jvcr *machine, i32 x, i32 y, u32 w, u32 h); // set screen clipping region
void cursor(Jvcr *machine, i32 x, i32 y); // set cursor and CR/LF margin position

void print(Jvcr *machine, char* str, u32 x, u32 y, i32 color); // print string

i32 pget(Jvcr *machine, u32 x, u32 y); // get pixel colour
void pset(Jvcr *machine, u32 x, u32 y, i32 color); // set pixel colour

void line(Jvcr *machine, i32 x0, i32 y0, i32 x1, i32 y1, i32 color); // draw line

void circ(Jvcr *machine, i32 x, i32 y, u32 r, i32 color); // draw circle
void circfill(Jvcr *machine, i32 x, i32 y, u32 r, i32 color); // draw filled circle

void rect(Jvcr *machine, i32 x, i32 y, u32 w, u32 h, i32 color); // draw rectangle
void rectfill(Jvcr *machine, i32 x, i32 y, u32 w, u32 h, i32 color); // draw filled rectangle

#endif //JVCR_ECM_01_VIDEO_H
