#include <Python.h>
#include <uart/usf.h>
#include "usf_obj.h"
#include "header_obj.h"
#include "sample_obj.h"
#include "access_obj.h"
#include "dangling_obj.h"
#include "burst_obj.h"
#include "trace_obj.h"
#include "stride_obj.h"
#include "smptrace_obj.h"

static PyObject *
pyusf_strcompr(PyObject *self, PyObject *args)
{
    int compression;

    if (!PyArg_ParseTuple(args, "i", &compression))
        return NULL;
    
    return Py_BuildValue("s", usf_strcompr(compression));
}

static PyObject *
pyusf_stratype(PyObject *self, PyObject *args)
{
    int type;

    if (!PyArg_ParseTuple(args, "i", &type))
        return NULL;
    
    return Py_BuildValue("s", usf_stratype(type));
}

static PyMethodDef usf_mod_funcs[] = {
    {"strcompr", pyusf_strcompr, METH_VARARGS, "XXX"},
    {"stratype", pyusf_stratype, METH_VARARGS, "XXX"},
    {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC
initpyusf(void)
{
    PyObject *m;

    m = Py_InitModule3("pyusf", usf_mod_funcs, "XXX");
    if (!m) {
        return;
    }

    if (PyType_Ready(&usf_obj_type) < 0) {
        return;
    }
    Py_INCREF(&usf_obj_type);
    PyModule_AddObject(m, "Usf", (PyObject *)&usf_obj_type);
 
    if (PyType_Ready(&header_obj_type) < 0) {
        return;
    }
    Py_INCREF(&header_obj_type);
    PyModule_AddObject(m, "Header", (PyObject *)&header_obj_type);

    if (PyType_Ready(&sample_obj_type) < 0) {
        return;
    }
    Py_INCREF(&sample_obj_type);
    PyModule_AddObject(m, "Sample", (PyObject *)&sample_obj_type);

    if (PyType_Ready(&stride_obj_type) < 0) {
        return;
    }
    Py_INCREF(&stride_obj_type);
    PyModule_AddObject(m, "Stride", (PyObject *)&stride_obj_type);

    if (PyType_Ready(&smptrace_obj_type) < 0) {
        return;
    }
    Py_INCREF(&smptrace_obj_type);
    PyModule_AddObject(m, "Smptrace", (PyObject *)&smptrace_obj_type);

    if (PyType_Ready(&access_obj_type) < 0) {
        return;
    }
    Py_INCREF(&access_obj_type);
    PyModule_AddObject(m, "Access", (PyObject *)&access_obj_type);

    if (PyType_Ready(&dangling_obj_type) < 0) {
        return;
    }
    Py_INCREF(&dangling_obj_type);
    PyModule_AddObject(m, "Dangling", (PyObject *)&dangling_obj_type);

    if (PyType_Ready(&burst_obj_type) < 0) {
        return;
    }
    Py_INCREF(&burst_obj_type);
    PyModule_AddObject(m, "Burst", (PyObject *)&burst_obj_type);
 
    if (PyType_Ready(&trace_obj_type) < 0) {
        return;
    }
    Py_INCREF(&trace_obj_type);
    PyModule_AddObject(m, "Trace", (PyObject *)&trace_obj_type);


    PyModule_AddObject(m, "USF_VERSION_CURRENT", Py_BuildValue("i", USF_VERSION_CURRENT));
    PyModule_AddObject(m, "USF_COMPRESSION_NONE", Py_BuildValue("i", USF_COMPRESSION_NONE));
    PyModule_AddObject(m, "USF_COMPRESSION_BZIP2", Py_BuildValue("i", USF_COMPRESSION_BZIP2));
    PyModule_AddObject(m, "USF_FLAG_TRACE", Py_BuildValue("i", USF_FLAG_TRACE));
    PyModule_AddObject(m, "USF_FLAG_BURST", Py_BuildValue("i", USF_FLAG_BURST));
    PyModule_AddObject(m, "USF_FLAG_DELTA", Py_BuildValue("i", USF_FLAG_DELTA));
    PyModule_AddObject(m, "USF_FLAG_INSTRUCTIONS", Py_BuildValue("i", USF_FLAG_INSTRUCTIONS));
    PyModule_AddObject(m, "USF_FLAG_NATIVE_ENDIAN", Py_BuildValue("i", USF_FLAG_NATIVE_ENDIAN));
    PyModule_AddObject(m, "USF_FLAG_FOREIGN_ENDIAN", Py_BuildValue("i",USF_FLAG_FOREIGN_ENDIAN));
    PyModule_AddObject(m, "USF_EVENT_SAMPLE", Py_BuildValue("i",USF_EVENT_SAMPLE));
    PyModule_AddObject(m, "USF_EVENT_STRIDE", Py_BuildValue("i",USF_EVENT_STRIDE));
    PyModule_AddObject(m, "USF_EVENT_SMPTRACE", Py_BuildValue("i",USF_EVENT_SMPTRACE));
    PyModule_AddObject(m, "USF_EVENT_DANGLING", Py_BuildValue("i",USF_EVENT_DANGLING));
    PyModule_AddObject(m, "USF_EVENT_BURST", Py_BuildValue("i",USF_EVENT_BURST));
    PyModule_AddObject(m, "USF_EVENT_TRACE", Py_BuildValue("i",USF_EVENT_TRACE));
}

