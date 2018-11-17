#ifndef PROJECT_JVCR_H
#define PROJECT_JVCR_H

#include <Python.h>
#include <jvcr_ecm_01/machine.h>

Jvcr *machine;

PyObject* PyInit_jvcr(void);
void RunMachine(void (*update)(Jvcr *, double));

#endif //PROJECT_JVCR_H
