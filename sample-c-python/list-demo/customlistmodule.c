#define PY_SSIZE_T_CLEAN
#include <Python.h>

// https://docs.python.org/3/extending/newtypes_tutorial.html

typedef struct {
  PyObject_HEAD
  int *data;
  int length;
} CustomObject;

static void Custom_dealloc(CustomObject *self) {
  Py_XDECREF(self->data);
  Py_TYPE(self)->tp_free((PyObject *) self);
}

static PyObject *Custom_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
  CustomObject *self = (CustomObject *) type->tp_alloc(type, 0);

  if (self != NULL) {
    self->data = NULL;
    self->length = 0;
  }

  return (PyObject *) self;
}

static int Custom_init(CustomObject *self, PyObject *args, PyObject *kwds) {
  PyObject *pList;

  if (!PyArg_ParseTuple(args, "O!", &PyList_Type, &pList)) {
    PyErr_SetString(PyExc_TypeError, "Parameter must be a list");
    return -1;
  }

  int n = PyList_Size(pList);
  self->length = n;
  self->data = malloc(sizeof(int) * n);

  if (self->data == NULL)
    return -1;

  for (int i = 0; i < n; i++) {
    PyObject *pItem = PyList_GetItem(pList, i);

    if (!PyLong_Check(pItem)) {
      PyErr_SetString(PyExc_TypeError, "List items must be integers");
      return -1;
    }

    (self->data)[i] = (int) PyLong_AsLong(pItem);
  }

  return 0;
}

static PyObject *Custom_increment(CustomObject *self, PyObject *args) {
  int idx, increment;

  if (!PyArg_ParseTuple(args, "ii", &idx, &increment))
    return NULL;

  if (idx >= self->length) {
    PyErr_SetString(PyExc_IndexError, "Index out of bounds");
    return NULL;
  }

  (self->data)[idx] += increment;
  return PyLong_FromLong((long) (self->data)[idx]);
}

static PyObject *Custom_get(CustomObject *self, PyObject *args) {
  int idx;

  if (!PyArg_ParseTuple(args, "i", &idx))
    return NULL;

  if (idx >= self->length) {
    PyErr_SetString(PyExc_IndexError, "Index out of bounds");
    return NULL;
  }

  return PyLong_FromLong((long) (self->data)[idx]);
}

static PyMethodDef Custom_methods[] = {
  {"increment", (PyCFunction) Custom_increment, METH_VARARGS, PyDoc_STR("increment(idx, inc) -> int")},
  {"get", (PyCFunction) Custom_get, METH_VARARGS, PyDoc_STR("get_cnt(idx) -> int")},
  {NULL, NULL} 
};

static PyTypeObject CustomType = {
  PyVarObject_HEAD_INIT(NULL, 0)
  .tp_name = "customlist.Custom",
  .tp_doc = "Custom objects",
  .tp_basicsize = sizeof(CustomObject),
  .tp_itemsize = 0,
  .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
  .tp_new = Custom_new,
  .tp_init = (initproc) Custom_init,
  .tp_dealloc = (destructor) Custom_dealloc,
  .tp_methods = Custom_methods
};

static PyModuleDef custommodule = {
  PyModuleDef_HEAD_INIT,
  .m_name = "customlist",
  .m_doc = "Example module that creates a list",
  .m_size = -1
};

PyMODINIT_FUNC PyInit_customlist(void) {
  if (PyType_Ready(&CustomType) < 0)
    return NULL;

  PyObject *m = PyModule_Create(&custommodule);

  if (m == NULL)
    return NULL;

  Py_INCREF(&CustomType);

  if (PyModule_AddObject(m, "Custom", (PyObject *) &CustomType) < 0) {
    Py_DECREF(&CustomType);
    Py_DECREF(m);
    return NULL;
  }

  return m;
}
