
#include <jvcr_ecm_01/machine.h>
#include <jvcr_ecm_01/math.h>
#include <jvcr_ecm_01/display.h>
#include <jvcr_ecm_01/render.h>
#include <math.h>
#include <jvcr_ecm_01/input.h>

#define DRAW_TIME 20
static void empty_draw(Jvcr *, double);

static void random_noice_draw(Jvcr *machine, double delta) {
  for (u32 x = 0; x < DISPLAY_WIDTH; x++) {
    for (u32 y = 0; y < DISPLAY_HEIGHT; y++) {
      byte color = (byte) rnd(16);
      pset(machine, x, y, color);
    }
  }

  if (machine->time > DRAW_TIME) { // after 10 seconds enable another demo
    machine->time = 0;
    machine->onDraw = &empty_draw;
  }
}

static void random_fade_draw(Jvcr *machine, double delta) {
  for (u32 i = 0; i < 3000; i++) {
    u32 x = rnd(DISPLAY_WIDTH);
    u32 y = rnd(DISPLAY_HEIGHT);
    byte color = (byte) ((long) (machine->time) % 16);
    pset(machine, x, y, color);
  }

  if (machine->time > DRAW_TIME) { // after 10 seconds enable another demo
    machine->time = 0;
    machine->onDraw = &random_noice_draw;
  }
}

static void lines_draw(Jvcr *machine, double delta) {
  u32 x0 = rnd(DISPLAY_WIDTH);
  u32 y0 = rnd(DISPLAY_HEIGHT);

  u32 x1 = rnd(DISPLAY_WIDTH);
  u32 y1 = rnd(DISPLAY_HEIGHT);

  byte color = (byte) ((long) (machine->time) % 16);

  line(machine, x0, y0, x1, y1, color);

  if (machine->time > DRAW_TIME) { // after 10 seconds enable another demo
    machine->time = 0;
    machine->onDraw = &random_fade_draw;
  }
}

static void lines_prisma_draw(Jvcr *machine, double delta) {
  const u32 base = 143;
  const double pi8 = M_PI / 8;
  const double pi2 = M_PI * 2;
  cls(machine, 0);
  static double t = 0;

  for (double i = fmod(t, 8.0); i < base; i += 8) {
    line(machine, (u32) i, 0, 0, (u32) (base - i), 8);
    line(machine, (u32) i, base, base, (u32) (135 - i), 6);
    t += 0.005;
  }

  for (double i = fmod(t / 16, pi8); i < pi2; i += pi8) {
    u32 x = (u32) (base / 2 + (base / 4) * cos(i));
    u32 y = (u32) (base / 2 + (base / 4) * cos(i));
    line(machine, base, 0, x, y, 11);
    line(machine, 0, base, x, y, 11);
  }

  line(machine, 0, 0, base, 0, 8);
  line(machine, 0, 0, 0, base, 8);
  line(machine, base, 0, base, base, 6);
  line(machine, 0, base, base, base, 6);

  if (machine->time > DRAW_TIME) { // after 10 seconds enable another demo
    machine->time = 0;
    machine->onDraw = &lines_draw;
  }
}

static void rect_pallet_draw(Jvcr *machine, double delta) {
  const u32 w = DISPLAY_WIDTH / PALETTE_LEN;
  for (byte i = 0; i < PALETTE_LEN; i++) {
    rectfill(machine, i * w, 0, w, DISPLAY_HEIGHT, i);
  }

  if (machine->time > DRAW_TIME) { // after 10 seconds enable another demo
    machine->time = 0;
    machine->onDraw = &lines_prisma_draw;
  }
}

static void print_hello_world(Jvcr *machine, double delta) {
  cls(machine, 0);

  print(machine, "Hello World!", 1, 1, 8);
  print(machine, "JVCR_ECM_01\nLOL\nWAT\rOMG", 1, 10, 10);

  if (machine->time > DRAW_TIME) { // after 10 seconds enable another demo
    machine->time = 0;
    machine->onDraw = &rect_pallet_draw;
  }
}

static void gamepad(Jvcr *machine, double delta) {
  cls(machine, 0);
  if (btn(machine, BTN_UP, 0)) print_symbol(machine, 'W', 10, 1, 8);
  if (btn(machine, BTN_DOWN, 0)) print_symbol(machine, 'S', 10, 10, 8);
  if (btn(machine, BTN_LEFT, 0)) print_symbol(machine, 'A', 1, 10, 8);
  if (btn(machine, BTN_RIGHT, 0)) print_symbol(machine, 'D', 20, 10, 8);
  if (btn(machine, BTN_A, 0)) print_symbol(machine, 'Z', 1, 30, 8);
  if (btn(machine, BTN_B, 0)) print_symbol(machine, 'X', 10, 30, 8);
  if (btn(machine, BTN_X, 0)) print_symbol(machine, 'C', 20, 30, 8);
  if (btn(machine, BTN_Y, 0)) print_symbol(machine, 'V', 30, 30, 8);
}

void empty_draw(Jvcr *machine, double delta) {
  if (machine->time > 1) { // after 10 seconds enable another demo
    machine->time = 0;
    machine->onDraw = &gamepad;
  }
}

int main(void) {
  Jvcr *machine = NewJvcr();
  machine->onDraw = &empty_draw;
  set_default_pallet(machine);
  set_default_font(machine);
  rendering_init(machine);
  input_init(machine);
  RunLoop(machine);
  rendering_stop(machine);
  DestroyJvcr(machine);

  return 0;
}