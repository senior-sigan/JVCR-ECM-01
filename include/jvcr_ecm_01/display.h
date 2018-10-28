#ifndef JVCR_ECM_01_VIDEO_H
#define JVCR_ECM_01_VIDEO_H

#include <jvcr_ecm_01/machine.h>
#include <jvcr_ecm_01/fonts.h>

typedef struct RGBA {
  byte red;
  byte green;
  byte blue;
  byte alpha;
} RGBA;

void cls(Jvcr *machine, byte color); // clear screen; col = clear color
void camera(Jvcr *machine, i32 x, i32 y); // set camera position
void clip(Jvcr *machine, i32 x, i32 y, u32 w, u32 h); // set screen clipping region
void cursor(Jvcr *machine, i32 x, i32 y); // set cursor and CR/LF margin position

void print(Jvcr *machine, char* str, u32 x, u32 y, byte color); // print string
void print_symbol(Jvcr *machine, char symbol, u32 x, u32 y, byte color); // print single symbol

byte pget(Jvcr *machine, u32 x, u32 y); // get pixel colour
void pset(Jvcr *machine, u32 x, u32 y, byte color); // set pixel colour

void line(Jvcr *machine, i32 x0, i32 y0, i32 x1, i32 y1, byte color); // draw line

void circ(Jvcr *machine, i32 x, i32 y, u32 r, byte color); // draw circle
void circfill(Jvcr *machine, i32 x, i32 y, u32 r, byte color); // draw filled circle

void rect(Jvcr *machine, i32 x, i32 y, u32 w, u32 h, byte color); // draw rectangle
void rectfill(Jvcr *machine, i32 x, i32 y, u32 w, u32 h, byte color); // draw filled rectangle

void set_pallet(Jvcr *machine, byte color, byte red, byte green, byte blue);
void set_default_pallet(Jvcr *machine);

void set_font(Jvcr *machine, char symbol, Font font);
void set_default_font(Jvcr* machine);

RGBA get_rgba(Jvcr *machine, byte color);

#endif //JVCR_ECM_01_VIDEO_H
