#include "py_input.h"
#include "jvcr.h"
#include <jvcr_ecm_01/input.h>

PyObject *jvcr_btn(PyObject *self, PyObject *args) {
  byte btn_id;
  byte player_num;
  PyArg_ParseTuple(args, "bb", &btn_id, &player_num);
  bool isPressed = btn(machine, btn_id, player_num);
  return PyBool_FromLong(isPressed);
}