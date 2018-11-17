#include <Python.h>
#include <stdlib.h>
#include <stdio.h>
#include "jvcr.h"

static PyObject *updateFunc;

static void update(Jvcr *machine, double delta) {
  PyObject* args = PyTuple_New(1);
  PyObject* value = PyFloat_FromDouble(delta);
  PyTuple_SetItem(args, 0, value);
  PyObject_CallObject(updateFunc, args);
  if (PyErr_Occurred()) PyErr_Print();
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: python dir_path\n");
    return 1;
  }

  char *name = "main";

  PyImport_AppendInittab("jvcr", &PyInit_jvcr);

  Py_Initialize();
  char *code = malloc(sizeof(char) * (33 + strlen(argv[1])));
  sprintf(code, "import sys\nsys.path.insert(0, \"%s\")", argv[1]);
  PyRun_SimpleString(code);

  PyObject *pName = PyUnicode_DecodeFSDefault(name);
  PyObject *pModule = PyImport_Import(pName);
  Py_DECREF(pName);

  if (pModule == NULL) {
    PyErr_Print();
    fprintf(stderr, "Failed to load \"%s\"\n", name);
    return 1;
  }

  updateFunc = PyObject_GetAttrString(pModule, "update");
  if (!updateFunc || !PyCallable_Check(updateFunc)) {
    if (PyErr_Occurred()) PyErr_Print();
    fprintf(stderr, "Cannot find function 'update'\n");
    return 1;
  }


  RunMachine(&update);

  Py_XDECREF(updateFunc);
  Py_DECREF(pModule);

  if (Py_FinalizeEx() < 0) {
    return 120;
  }
  return 0;
}