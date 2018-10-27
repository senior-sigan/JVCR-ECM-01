#include <jvcr_ecm_01/display.h>
#include <stdlib.h>
#include <stdio.h>
#include <jvcr_ecm_01/ram.h>

void cls(Jvcr *machine, byte color) {
  jvcr_memset(machine->ram, SCREEN_START, 0, SCREEN_SIZE);
}

void pset(Jvcr *machine, u32 x, u32 y, byte color) {
  u32 index = x + y * DISPLAY_WIDTH;
  jvcr_poke(machine->ram, index + SCREEN_START, color);
}

byte pget(Jvcr *machine, u32 x, u32 y) {
  u32 index = x + y * DISPLAY_WIDTH;
  return jvcr_peek(machine->ram, index + SCREEN_START);
}

void set_pallet(Jvcr *machine, byte color, byte red, byte green, byte blue) {
  if (color > PALETTE_LEN) {
    printf("WARNING: cannot set color with id=%d, out of bound=[0, %d]", color, PALETTE_LEN);
    return;
  }

  ptr_t index = PALETTE_START + (ptr_t) color * PALETTE_UNIT;
  jvcr_poke(machine->ram, index, red);
  jvcr_poke(machine->ram, index + 1, green);
  jvcr_poke(machine->ram, index + 2, blue);
  jvcr_poke(machine->ram, index + 3, 0xFF);
}

/**
 * @link https://lospec.com/palette-list/pico-8
 * @param machine
 */
void set_default_pallet(Jvcr *machine) {
  set_pallet(machine, 0, 0, 0, 0);
  set_pallet(machine, 1, 29, 43, 83);
  set_pallet(machine, 2, 126, 37, 83);
  set_pallet(machine, 3, 0, 135, 81);
  set_pallet(machine, 4, 171, 82, 54);
  set_pallet(machine, 5, 95, 87, 79);
  set_pallet(machine, 6, 194, 195, 199);
  set_pallet(machine, 7, 255, 241, 232);
  set_pallet(machine, 8, 255, 0, 77);
  set_pallet(machine, 9, 255, 163, 0);
  set_pallet(machine, 10, 255, 240, 36);
  set_pallet(machine, 11, 0, 231, 86);
  set_pallet(machine, 12, 41, 173, 255);
  set_pallet(machine, 13, 131, 118, 156);
  set_pallet(machine, 14, 255, 119, 168);
  set_pallet(machine, 15, 255, 204, 170);
}

RGBA get_rgba(Jvcr *machine, byte color) {
  RGBA rgba = {0, 0, 0, 0};
  if (color > PALETTE_LEN) {
    printf("WARNING: color index should be between [0, %d], but %d", PALETTE_LEN, color);
    return rgba;
  }

  ptr_t index = PALETTE_START + (ptr_t) color * PALETTE_UNIT;
  rgba.red = jvcr_peek(machine->ram, index);
  rgba.green = jvcr_peek(machine->ram, index + 1);
  rgba.blue = jvcr_peek(machine->ram, index + 2);
  rgba.alpha = jvcr_peek(machine->ram, index + 3);
  return rgba;
}
void line(Jvcr *machine, i32 x0, i32 y0, i32 x1, i32 y1, byte color) {
  i32 dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
  i32 dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
  i32 err = (dx > dy ? dx : -dy) / 2;
  i32 e2;

  for (;;) {
    pset(machine, (u32) x0, (u32) y0, color); // TODO: may be not cast to u32?
    if (x0 == x1 && y0 == y1) break;
    e2 = err;
    if (e2 > -dx) {
      err -= dy;
      x0 += sx;
    }
    if (e2 < dy) {
      err += dx;
      y0 += sy;
    }
  }
}
