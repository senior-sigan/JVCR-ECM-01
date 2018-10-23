#include <jvcr_ecm_01/display.h>
#include <stdlib.h>

void cls(Jvcr *machine, i32 color) {
  for (u32 x = 0; x < DISPLAY_WIDTH; x++) {
    for (u32 y = 0; y < DISPLAY_HEIGHT; y++) {
      pset(machine, x, y, color);
    }
  }
}

void pset(Jvcr *machine, u32 x, u32 y, i32 color) {
//  size_t index = y * DISPLAY_WIDTH + x;
  //TODO: somehow set a VRAM. But a pixel is 4 bites. I cannot address 0.5 byte.
//  machine->ram->memory[index] = ???;
}

i32 pget(Jvcr *machine, u32 x, u32 y) {
  // TODO: somehow get 4 bites of color from the VRAM
  return -1;
}