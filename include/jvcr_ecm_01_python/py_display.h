#ifndef PROJECT_PY_DISPLAY_H
#define PROJECT_PY_DISPLAY_H

#include <Python.h>

PyObject *jvcr_cls(PyObject *self, PyObject *args);
PyObject *jvcr_print(PyObject *self, PyObject *args);
PyObject *jvcr_print_symbol(PyObject *self, PyObject *args);
PyObject *jvcr_pget(PyObject *self, PyObject *args);
PyObject *jvcr_pset(PyObject *self, PyObject *args);
PyObject *jvcr_rectfill(PyObject *self, PyObject *args);
PyObject *jvcr_line(PyObject *self, PyObject *args);

#endif //PROJECT_PY_DISPLAY_H
