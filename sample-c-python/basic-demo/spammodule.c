#define PY_SSIZE_T_CLEAN
#include "Python.h"

static PyObject *ErrorObject;

/*
typedef struct {
  PyObject_HEAD PyObject *spam_attr;
} CanObject;

static PyTypeObject Can_Type;

#define SpamObject_Check(v) Py_IS_TYPE(v, &Can_Type)

static CanObject *newCanObject(PyObject *arg) {
  CanObject *self = PyObject_New(CanObject, &Can_Type);

  if (self == NULL)
    return NULL;

  self->spam_attr = NULL;
  return self;
}

static void Can_dealloc(CanObject *self) {
  Py_XDECREF(self->spam_attr);
  PyObject_Free(self);
}
*/

static PyObject *Can_demo(PyObject *self, PyObject *args) {
  const char *command;
  int sts;

  if (!PyArg_ParseTuple(args, "s", &command))
    return NULL;

  sts = system(command);

  if (sts < 0) {
    PyErr_SetString(ErrorObject, "System command failed");
    return NULL;
  }

  return PyLong_FromLong(sts);
}

static PyMethodDef Can_methods[] = {
  {"demo", (PyCFunction) Can_demo,  METH_VARARGS, PyDoc_STR("demo() -> int")},
  {NULL, NULL} 
};

static struct PyModuleDef spammodule = {
  PyModuleDef_HEAD_INIT, "spam", NULL, -1, Can_methods
};

PyMODINIT_FUNC PyInit_spam(void) {
  return PyModule_Create(&spammodule);
}

int main(int argc, char *argv[]) {
  wchar_t *program = Py_DecodeLocale(argv[0], NULL);

  if (program == NULL) {
    fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
    exit(1);
  }

  // Add a built-in module, before Py_Initialize
  if (PyImport_AppendInittab("spam", PyInit_spam) == -1) {
    fprintf(stderr, "Error: could not extend in-built modules table\n");
    exit(1);
  }

  // Pass argv[0] to the Python interpreter
  Py_SetProgramName(program);

  // Initialize the Python interpreter. Required. If this step fails, it will be a fatal error.
  Py_Initialize();

  // Optionally import the module; alternatively, import can be deferred until the embedded script imports it.
  PyObject *pmodule = PyImport_ImportModule("spam");

  if (!pmodule) {
    PyErr_Print();
    fprintf(stderr, "Error: could not import module 'spam'\n");
  }

  PyMem_RawFree(program);
  return 0;
}
