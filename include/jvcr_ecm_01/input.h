#ifndef PROJECT_INPUT_H
#define PROJECT_INPUT_H

#include <jvcr_ecm_01/types.h>
#include <jvcr_ecm_01/machine.h>

#define BTN_UP 0
#define BTN_DOWN 1
#define BTN_LEFT 2
#define BTN_RIGHT 3
#define BTN_A 4
#define BTN_B 5
#define BTN_X 6
#define BTN_Y 7

typedef struct {
  char up:1;
  char down:1;
  char left:1;
  char right:1;
  char btn_a:1;
  char btn_b:1;
  char btn_x:1;
  char btn_y:1;
} BTN_MAP;

bool btn(Jvcr *machine, byte btn_id, byte player_num); // get button btn_id state for player player_num
bool btnp(byte button,
          byte player_num); // only true when the button was not pressed the last frame; repeats every 4 frames after button held for 15 frames

void input_init(Jvcr *machine);

#endif //PROJECT_INPUT_H
