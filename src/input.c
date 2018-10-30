#include <jvcr_ecm_01/input.h>
#include <jvcr_ecm_01/ram.h>

static bool is_pressed(BTN_MAP btn_map, byte btn_id) {
  switch (btn_id) {
    case BTN_UP: return btn_map.up;
    case BTN_DOWN: return btn_map.down;
    case BTN_LEFT: return btn_map.left;
    case BTN_RIGHT: return btn_map.right;
    case BTN_A: return btn_map.btn_a;
    case BTN_B: return btn_map.btn_b;
    case BTN_X: return btn_map.btn_x;
    case BTN_Y: return btn_map.btn_y;
    default:return false;
  }
}

bool btn(Jvcr *machine, byte btn_id, byte player_num) {
  byte btn = jvcr_peek(machine->ram, GAMEPADS_START + player_num);
  BTN_MAP btn_map = *(BTN_MAP *) &btn;
  return is_pressed(btn_map, btn_id);
}