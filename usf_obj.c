#include <Python.h>
#include "structmember.h"
#include <assert.h>
#include <uart/usf.h>
#include "usf_obj.h"
#include "sample_obj.h"
#include "stride_obj.h"
#include "smptrace_obj.h"
#include "dangling_obj.h"
#include "burst_obj.h"
#include "trace_obj.h"

static int
usf_obj_init(usf_obj_t *self, PyObject *args, PyObject *kwds)
{
    char *file_name = NULL;
    char *kwlist[] = { "file_name", NULL };

    self->usf_file = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|s", kwlist, &file_name))
        return -1;

    if (file_name) {
        /* File name is optional, try to open the file if it was specified. */
        if (!PyObject_CallMethod((PyObject *)self, "open", "s", file_name))
            return -1;
    }

    return 0;
}

static void
usf_obj_dealloc(usf_obj_t *self)
{
    if (self->usf_file)
        usf_close(self->usf_file);

    self->ob_type->tp_free((PyObject *)self);
}

static PyObject *
usf_obj_iter(usf_obj_t *self)
{
    if (!self->usf_file) {
        PyErr_SetString(PyExc_ValueError, "I/O operation on closed file");
        return NULL;
    }

    Py_INCREF(self);
    return (PyObject *)self;
}

static PyObject *
usf_obj_iternext(usf_obj_t *self)
{
    usf_error_t error;
    usf_event_t event;

    error = usf_read(self->usf_file, &event);
    switch (error) {
        case USF_ERROR_OK:
            switch (event.type) {
                case USF_EVENT_SAMPLE:
                    return (PyObject *)sample_obj_create(&event.u.sample);
                case USF_EVENT_DANGLING:
                    return (PyObject *)dangling_obj_create(&event.u.dangling);
	        case USF_EVENT_STRIDE:
                    return (PyObject *)stride_obj_create(&event.u.stride);
	        case USF_EVENT_SMPTRACE:
                    return (PyObject *)smptrace_obj_create(&event.u.smptrace);
                case USF_EVENT_BURST:
                    return (PyObject *)burst_obj_create(&event.u.burst);
                case USF_EVENT_TRACE:
                    return (PyObject *)trace_obj_create(&event.u.trace);
                default:
                    assert(0);
            }
        case USF_ERROR_EOF:
            PyErr_SetNone(PyExc_StopIteration);
            return NULL;
        default:
            PyErr_SetString(PyExc_IOError, usf_strerror(error));
            return NULL;
    }
}

static PyObject *
usf_obj_open(usf_obj_t *self, PyObject *args, PyObject *kwds)
{
    char *kwlist[] = { "file_name", NULL };
    char *file_name = NULL;
    const usf_header_t *header;
    usf_error_t error;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "z", kwlist, &file_name))
        return NULL;

    if (self->usf_file) {
        PyErr_SetString(PyExc_IOError,
                        "File object already contains an open file reference.");
        return NULL;
    }

    do {
        error = usf_open(&self->usf_file, file_name);
        if (error != USF_ERROR_OK)
            break;

        error = usf_header(&header, self->usf_file);
        if (error != USF_ERROR_OK)
            break;

        self->header = header_obj_create(header);
        Py_RETURN_NONE;
    } while (0);

    PyErr_SetString(PyExc_IOError, usf_strerror(error));
    return NULL;
}

static PyObject *
usf_obj_create(usf_obj_t *self, PyObject *args, PyObject *kwds)
{
    char *kwlist[] = { "file_name", "header", NULL };
    char *file_name = NULL;
    PyObject *header_obj;
    usf_error_t error;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "sO", kwlist,
                                     &file_name, &header_obj)) {
        return NULL;
    }
 
    if (self->usf_file) {
        PyErr_SetString(PyExc_IOError,
                        "File object already contains an open file reference.");
        return NULL;
    }

    Py_INCREF(header_obj);
    self->header = (header_obj_t *)header_obj;
    
    error = usf_create(&self->usf_file, file_name, &self->header->header);
    if (error != USF_ERROR_OK) {
        PyErr_SetString(PyExc_IOError, usf_strerror(error));
        return NULL;
    }

    Py_RETURN_NONE;
}

static PyObject *
usf_obj_close(usf_obj_t *self)
{
    if (self->usf_file) {
        usf_error_t error;

        error = usf_close(self->usf_file);
        if (error != USF_ERROR_OK) {
            PyErr_SetString(PyExc_IOError, usf_strerror(error));
            return NULL;
        }

        self->usf_file = NULL;
    } else {
        PyErr_SetString(PyExc_ValueError, "I/O operation on closed file");
        return NULL;
    }

    Py_RETURN_NONE;
}

static PyObject *
usf_obj_append(usf_obj_t *self, PyObject *args)
{
    PyObject *event_obj;
    usf_event_t event;
    usf_error_t error;

    extern PyTypeObject sample_obj_type;
    extern PyTypeObject stride_obj_type;
    extern PyTypeObject smptrace_obj_type;
    extern PyTypeObject dangling_obj_type;
    extern PyTypeObject burst_obj_type;
    extern PyTypeObject trace_obj_type;

    if (!PyArg_ParseTuple(args, "O", &event_obj))
        return NULL;

    if (PyObject_TypeCheck(event_obj, &sample_obj_type)) {
        event.type = USF_EVENT_SAMPLE;
        event.u.sample.begin = ((sample_obj_t *)event_obj)->begin->access;
        event.u.sample.end = ((sample_obj_t *)event_obj)->end->access;
    } else if (PyObject_TypeCheck(event_obj, &stride_obj_type)) {
        event.type = USF_EVENT_STRIDE;
        event.u.stride.begin = ((stride_obj_t *)event_obj)->begin->access;
        event.u.stride.end = ((stride_obj_t *)event_obj)->end->access;
    } else if (PyObject_TypeCheck(event_obj, &smptrace_obj_type)) {
        event.type = USF_EVENT_SMPTRACE;
        event.u.smptrace.begin = ((smptrace_obj_t *)event_obj)->begin->access;
    } else if (PyObject_TypeCheck(event_obj, &dangling_obj_type)) {
        event.type = USF_EVENT_DANGLING;
        event.u.dangling.begin = ((dangling_obj_t *)event_obj)->begin->access;
    } else if (PyObject_TypeCheck(event_obj, &burst_obj_type)) {
        event.type = USF_EVENT_BURST;
        event.u.burst = ((burst_obj_t *)event_obj)->burst;
    } else if (PyObject_TypeCheck(event_obj, &trace_obj_type)) {
        event.type = USF_EVENT_TRACE;
        event.u.trace.access = ((trace_obj_t *)event_obj)->access->access;
    }

    error = usf_append(self->usf_file, &event);
    if (error != USF_ERROR_OK) {
        PyErr_SetString(PyExc_IOError, usf_strerror(error));
        return NULL;
    }

    Py_RETURN_NONE;
}

static PyMethodDef usf_obj_methods[] = {
    {"open",   (PyCFunction)usf_obj_open,   METH_KEYWORDS, "XXX"},
    {"create", (PyCFunction)usf_obj_create, METH_KEYWORDS, "XXX"},
    {"close",  (PyCFunction)usf_obj_close,  METH_NOARGS,   "XXX"},
    {"append", (PyCFunction)usf_obj_append, METH_VARARGS, "XXX"},
    {NULL, NULL, 0, NULL}
};


static PyMemberDef ufs_obj_members[] = {
    {"header", T_OBJECT, offsetof(usf_obj_t, header), 0, "XXX"},
    {NULL}
};

PyTypeObject usf_obj_type = {
    PyObject_HEAD_INIT(NULL)
    0,                                          /* ob_size              */
    "pyusf.Usf",                                /* tp_name              */
    sizeof(usf_obj_t),                          /* tp_basicsize         */
    0,                                          /* tp_itemsize          */
    (destructor)usf_obj_dealloc,                /* tp_dealloc           */
    0,                                          /* tp_print             */
    0,                                          /* tp_getattr           */
    0,                                          /* tp_setattr           */
    0,                                          /* tp_compare           */
    0,                                          /* tp_repr              */
    0,                                          /* tp_as_number         */
    0,                                          /* tp_as_sequence       */
    0,                                          /* tp_as_mapping        */
    0,                                          /* tp_hash              */
    0,                                          /* tp_call              */
    0,                                          /* tp_str               */
    0,                                          /* tp_getattro          */
    0,                                          /* tp_setattro          */
    0,                                          /* tp_as_buffer         */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,   /* tp_flags             */
    "XXX",                                      /* tp_doc               */
    0,                                          /* tp_traverse          */
    0,                                          /* tp_clear             */
    0,                                          /* tp_richcompare       */
    0,                                          /* tp_weaklistoffset    */
    (getiterfunc)usf_obj_iter,                  /* tp_iter              */
    (iternextfunc)usf_obj_iternext,             /* tp_iternext          */
    usf_obj_methods,                            /* tp_methods           */
    ufs_obj_members,                            /* tp_members           */
    0,                                          /* tp_getset            */
    0,                                          /* tp_base              */
    0,                                          /* tp_dict              */
    0,                                          /* tp_descr_get         */
    0,                                          /* tp_descr_set         */
    0,                                          /* tp_dictoffset        */
    (initproc)usf_obj_init,                     /* tp_init              */
    0,                                          /* tp_alloc             */
    PyType_GenericNew,                          /* tp_new               */
};

