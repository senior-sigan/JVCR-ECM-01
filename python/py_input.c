#include <jvcr_ecm_01/input.h>
#include <Python.h>
#include <jvcr_ecm_01_python/jvcr.h>

PyObject *jvcr_btn(PyObject *self, PyObject *args) {
  byte btn_id;
  byte player_num;
  PyArg_ParseTuple(args, "bb", &btn_id, &player_num);
  bool isPressed = btn(machine, btn_id, player_num);
  return PyBool_FromLong(isPressed);
}