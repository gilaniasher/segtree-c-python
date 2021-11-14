#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <structmember.h>

// https://docs.python.org/3/extending/newtypes_tutorial.html

typedef struct {
  PyObject_HEAD
  int *data;
  int cnt;
} CustomObject;

static void Custom_dealloc(CustomObject *self) {
  Py_XDECREF(self->data);
  Py_TYPE(self)->tp_free((PyObject *) self);
}

static PyObject *Custom_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
  CustomObject *self = (CustomObject *) type->tp_alloc(type, 0);

  if (self != NULL) {
    self->data = NULL;
    self->cnt = 0;
  }

  return (PyObject *) self;
}

static int Custom_init(CustomObject *self, PyObject *args, PyObject *kwds) {
  static char *kwlist[] = {"count", NULL};
  int init_cnt = 0;

  if (!PyArg_ParseTupleAndKeywords(args, kwds, "|i", kwlist, &init_cnt))
    return -1;

  self->cnt = init_cnt;  

  return 0;
}

static PyMemberDef Custom_members[] = {
  {"cnt", T_INT, offsetof(CustomObject, cnt), 0, "count"},
  {NULL}
};

static PyObject *Custom_increment(CustomObject *self, PyObject *args) {
  int increment;

  if (!PyArg_ParseTuple(args, "i", &increment))
    return NULL;

  self->cnt += increment;

  return PyLong_FromLong((long) self->cnt);
}

static PyObject *Custom_get_cnt(CustomObject *self, PyObject *args) {
  return PyLong_FromLong((long) self->cnt);
}

static PyMethodDef Custom_methods[] = {
  {"increment", (PyCFunction) Custom_increment, METH_VARARGS, PyDoc_STR("increment(inc) -> int")},
  {"get_cnt", (PyCFunction) Custom_get_cnt, METH_VARARGS, PyDoc_STR("get_cnt() -> int")},
  {NULL, NULL} 
};

static PyTypeObject CustomType = {
  PyVarObject_HEAD_INIT(NULL, 0)
  .tp_name = "custom.Custom",
  .tp_doc = "Custom objects",
  .tp_basicsize = sizeof(CustomObject),
  .tp_itemsize = 0,
  .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
  .tp_new = Custom_new,
  .tp_init = (initproc) Custom_init,
  .tp_dealloc = (destructor) Custom_dealloc,
  .tp_members = Custom_members,
  .tp_methods = Custom_methods
};

static PyModuleDef custommodule = {
  PyModuleDef_HEAD_INIT,
  .m_name = "custom",
  .m_doc = "Example module that creates an object with a counter",
  .m_size = -1
};

PyMODINIT_FUNC PyInit_custom(void) {
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
