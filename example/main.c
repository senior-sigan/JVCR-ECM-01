#include <jvcr_ecm_01/consts.h>
#include <jvcr_ecm_01/machine.h>
#include <jvcr_ecm_01/render.h>
#include <jvcr_ecm_01/display.h>

static void draw(Jvcr *machine) {
  for (u32 x = 0; x < DISPLAY_WIDTH; x++) {
    for (u32 y = 0; y < DISPLAY_HEIGHT; y++) {
      pset(machine, x, y, (byte) (7*((x+1)*(y+1)%2)));
    }
  }
}

int main(void) {
  Jvcr* machine = NewJvcr();
  set_default_pallet(machine);
  rendering_init(machine);
  RunLoop(machine, &draw);
  rendering_stop(machine);
  DestroyJvcr(machine);

  return 0;
}