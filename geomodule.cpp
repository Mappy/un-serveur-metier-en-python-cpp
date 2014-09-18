#include "Python.h"
#include "geo.hpp"

static PyObject * geocoord2string_py(PyObject *self, PyObject *args)
{
    double angle = 0;

    if (!PyArg_ParseTuple(args, "d", &angle))
        return NULL;
        
    string res = geocoord2string(angle);
    return Py_BuildValue("s", res.c_str());
}

// La liste des fonctions qu'on expose en Python
static PyMethodDef geoMethods[] = {
    {"geocoord2string",  geocoord2string_py, METH_VARARGS,
     "Conver a latitude or a longitude as an angle in a string in the form : d° m' s''."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

// La fonction initnomdumodule est appelée par l'interpreteur Python 
// à l'import du module
PyMODINIT_FUNC initgeo(void)
{
    (void) Py_InitModule("geo", geoMethods);
}
