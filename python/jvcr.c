#include <jvcr_ecm_01/display.h>
#include <jvcr_ecm_01/render.h>
#include <jvcr_ecm_01/input.h>
#include <jvcr_ecm_01_python/jvcr.h>
#include <jvcr_ecm_01_python/py_display.h>
#include <jvcr_ecm_01_python/py_input.h>

static PyMethodDef JvcrMethods[] = {
    {"cls", jvcr_cls, METH_VARARGS, NULL},
    {"print", jvcr_print, METH_VARARGS, NULL},
    {"print_symbol", jvcr_print_symbol, METH_VARARGS, NULL},
    {"pget", jvcr_pget, METH_VARARGS, NULL},
    {"pset", jvcr_pset, METH_VARARGS, NULL},
    {"print", jvcr_print, METH_VARARGS, NULL},
    {"rectfill", jvcr_rectfill, METH_VARARGS, NULL},
    {"line", jvcr_line, METH_VARARGS, NULL},
    {"btn", jvcr_btn, METH_VARARGS, NULL},
    {NULL, NULL, 0, NULL}
};

static PyModuleDef JvcrModule = {
    PyModuleDef_HEAD_INIT, "jvcr", NULL, -1, JvcrMethods,
    NULL, NULL, NULL, NULL
};

PyObject *PyInit_jvcr(void) {
  PyObject *module = PyModule_Create(&JvcrModule);
  PyModule_AddIntConstant(module, "DISPLAY_WIDTH", DISPLAY_WIDTH);
  PyModule_AddIntConstant(module, "DISPLAY_HEIGHT", DISPLAY_HEIGHT);
  PyModule_AddIntConstant(module, "PALETTE_LEN", PALETTE_LEN);
  PyModule_AddIntConstant(module, "BTN_UP", BTN_UP);
  PyModule_AddIntConstant(module, "BTN_DOWN", BTN_DOWN);
  PyModule_AddIntConstant(module, "BTN_LEFT", BTN_LEFT);
  PyModule_AddIntConstant(module, "BTN_RIGHT", BTN_RIGHT);
  PyModule_AddIntConstant(module, "BTN_A", BTN_A);
  PyModule_AddIntConstant(module, "BTN_B", BTN_B);
  PyModule_AddIntConstant(module, "BTN_X", BTN_X);
  PyModule_AddIntConstant(module, "BTN_Y", BTN_Y);
  return module;
}

void RunMachine(void (*update)(Jvcr *, double)) {
  machine = NewJvcr();
  machine->onDraw = update;
  set_default_pallet(machine);
  set_default_font(machine);
  rendering_init(machine);
  input_init(machine);
  RunLoop(machine);
  rendering_stop(machine);
  DestroyJvcr(machine);
}

