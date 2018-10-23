#include <jvcr_ecm_01/machine.h>
#include <jvcr_ecm_01/display.h>
#include <stdlib.h>

typedef struct RGBA {
  byte red;
  byte green;
  byte blue;
  byte alpha;
} RGBA;

RGBA GetRGBA(Jvcr *machine, i32 color) {
  // TODO: somehow get from the pallet the color
  RGBA rgba= {0,0,0,0};
  return rgba;
}

void Draw(Jvcr *machine) {
  for (u32 x = 0; x < DISPLAY_WIDTH; x++) {
    for (u32 y = 0; y < DISPLAY_HEIGHT; y++) {
      i32 color_index = pget(machine, x, y);
      RGBA color = GetRGBA(machine,color_index);

      size_t index = y * DISPLAY_WIDTH + x;
      byte* tex = machine->display->texture;
      tex[4 * index + 0] = color.red;
      tex[4 * index + 1] = color.green;
      tex[4 * index + 2] = color.blue;
      tex[4 * index + 3] = color.alpha;
    }
  }
}