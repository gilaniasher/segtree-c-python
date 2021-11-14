#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "segtree.h"

typedef struct {
  PyObject_HEAD
  int *tree;
  int length; // Input arr len, not tree len
  int (*op)(int,int); // Query operation (min,max, or sum)
} SegtreeObject;

static void Segtree_dealloc(SegtreeObject *self) {
  Py_XDECREF(self->tree);
  Py_TYPE(self)->tp_free((PyObject *) self);
}

static PyObject *Segtree_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
  SegtreeObject *self = (SegtreeObject *) type->tp_alloc(type, 0);

  if (self != NULL) {
    self->tree = NULL;
    self->length = 0;
  }

  return (PyObject *) self;
}

static int Segtree_init(SegtreeObject *self, PyObject *args, PyObject *kwds) {
  PyObject *pList;
  char *type;

  if (!PyArg_ParseTuple(args, "O!s", &PyList_Type, &pList, &type)) {
    PyErr_SetString(PyExc_TypeError, "Parameter must be a list");
    return -1;
  }

  // Set the query type (min/max/sum) and store it in self->op
  if (!strcmp(type, "min")) self->op = min;
  else if (!strcmp(type, "max")) self->op = max;
  else if (!strcmp(type, "sum")) self->op = sum;
  else {
    PyErr_SetString(PyExc_TypeError, "Query type must be either 'min', 'max', or 'sum'");
    return -1;
  }

  int n = PyList_Size(pList);
  self->length = n;
  self->tree = malloc(sizeof(int) * 4 * n);

  // Build input array which will be given to segtree for building the tree
  int *input = malloc(sizeof(int) * n);

  if (self->tree == NULL || input == NULL)
    return -1;

  for (int i = 0; i < n; i++) {
    PyObject *pItem = PyList_GetItem(pList, i);

    if (!PyLong_Check(pItem)) {
      PyErr_SetString(PyExc_TypeError, "List items must be integers");
      return -1;
    }

    input[i] = (int) PyLong_AsLong(pItem);
  }

  // Now that temp is initalized with our Python list, build the actual tree
  build(self->tree, self->op, input, 1, 0, n-1);
  free(input);

  return 0;
}

static PyObject *Segtree_sum(SegtreeObject *self, PyObject *args) {
  int idx1, idx2;

  if (self->op != sum) {
    PyErr_SetString(PyExc_TypeError, "Sum was called but this Segment Tree was not initialized for sum queries");
    return NULL;
  }

  if (!PyArg_ParseTuple(args, "ii", &idx1, &idx2))
    return NULL;

  if (!(0 <= idx1 && idx1 <= idx2 && idx2 < self->length)) {
    PyErr_SetString(PyExc_IndexError, "Invalid indexes provided");
    return NULL;
  }

  int ans = query(self->tree, self->op, 1, 0, self->length-1, idx1, idx2);
  return PyLong_FromLong((long) ans);
}

static PyObject *Segtree_min(SegtreeObject *self, PyObject *args) {
  int idx1, idx2;

  if (self->op != min) {
    PyErr_SetString(PyExc_TypeError, "Min was called but this Segment Tree was not initialized for min queries");
    return NULL;
  }

  if (!PyArg_ParseTuple(args, "ii", &idx1, &idx2))
    return NULL;

  if (!(0 <= idx1 && idx1 <= idx2 && idx2 < self->length)) {
    PyErr_SetString(PyExc_IndexError, "Invalid indexes provided");
    return NULL;
  }

  int ans = query(self->tree, self->op, 1, 0, self->length-1, idx1, idx2);
  return PyLong_FromLong((long) ans);
}

static PyObject *Segtree_max(SegtreeObject *self, PyObject *args) {
  int idx1, idx2;

  if (self->op != max) {
    PyErr_SetString(PyExc_TypeError, "Max was called but this Segment Tree was not initialized for max queries");
    return NULL;
  }

  if (!PyArg_ParseTuple(args, "ii", &idx1, &idx2))
    return NULL;

  if (!(0 <= idx1 && idx1 <= idx2 && idx2 < self->length)) {
    PyErr_SetString(PyExc_IndexError, "Invalid indexes provided");
    return NULL;
  }

  int ans = query(self->tree, self->op, 1, 0, self->length-1, idx1, idx2);
  return PyLong_FromLong((long) ans);
}

static PyObject *Segtree_update(SegtreeObject *self, PyObject *args, PyObject *kwds) {
  int idx, newVal;

  if (!PyArg_ParseTuple(args, "ii", &idx, &newVal))
    return NULL;

  if (!(0 <= idx && idx < self->length)) {
    PyErr_SetString(PyExc_IndexError, "Invalid index provided");
    return NULL;
  }

  update(self->tree, self->op, 1, 0, self->length-1, idx, newVal);

  Py_INCREF(Py_None);
  return Py_None;
}

static PyMethodDef Segtree_methods[] = {
  {"sum", (PyCFunction) Segtree_sum, METH_VARARGS, PyDoc_STR("sum(idx1, idx2) -> int")},
  {"min", (PyCFunction) Segtree_min, METH_VARARGS, PyDoc_STR("min(idx1, idx2) -> int")},
  {"max", (PyCFunction) Segtree_max, METH_VARARGS, PyDoc_STR("max(idx1, idx2) -> int")},
  {"update", (PyCFunction) Segtree_update, METH_VARARGS, PyDoc_STR("update(idx, newVal) -> None")},
  {NULL, NULL} 
};

static PyTypeObject SegtreeType = {
  PyVarObject_HEAD_INIT(NULL, 0)
  .tp_name = "segtree.Segtree",
  .tp_doc = "Segment Tree Object",
  .tp_basicsize = sizeof(SegtreeObject),
  .tp_itemsize = 0,
  .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
  .tp_new = Segtree_new,
  .tp_init = (initproc) Segtree_init,
  .tp_dealloc = (destructor) Segtree_dealloc,
  .tp_methods = Segtree_methods
};

static PyModuleDef segtreemodule = {
  PyModuleDef_HEAD_INIT,
  .m_name = "segtree",
  .m_doc = "Segment Tree Module",
  .m_size = -1
};

PyMODINIT_FUNC PyInit_segtree(void) {
  if (PyType_Ready(&SegtreeType) < 0)
    return NULL;

  PyObject *m = PyModule_Create(&segtreemodule);

  if (m == NULL)
    return NULL;

  Py_INCREF(&SegtreeType);

  if (PyModule_AddObject(m, "Segtree", (PyObject *) &SegtreeType) < 0) {
    Py_DECREF(&SegtreeType);
    Py_DECREF(m);
    return NULL;
  }

  return m;
}
