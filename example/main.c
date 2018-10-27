#include <jvcr_ecm_01/consts.h>
#include <jvcr_ecm_01/machine.h>
#include <jvcr_ecm_01/render.h>
#include <jvcr_ecm_01/display.h>
#include <jvcr_ecm_01/math.h>
#include <stdio.h>

static void random_noice_draw(Jvcr *machine, double delta) {
  for (u32 x = 0; x < DISPLAY_WIDTH; x++) {
    for (u32 y = 0; y < DISPLAY_HEIGHT; y++) {
      byte color = (byte) rnd(16);
      pset(machine, x, y, color);
    }
  }
}

static void random_fade_draw(Jvcr *machine, double delta) {
  for (u32 i = 0; i < 3000; i++) {
    u32 x = rnd(DISPLAY_WIDTH);
    u32 y = rnd(DISPLAY_HEIGHT);
    byte color = (byte)((long)(machine->time) % 16);
    pset(machine, x, y, color);
  }

  if (machine->time > 10) { // after 10 seconds enable another demo
    machine->onDraw = &random_noice_draw;
  }
}

int main(void) {
  Jvcr* machine = NewJvcr();
  machine->onDraw = &random_fade_draw;
  set_default_pallet(machine);
  rendering_init(machine);
  RunLoop(machine);
  rendering_stop(machine);
  DestroyJvcr(machine);

  return 0;
}