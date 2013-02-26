#include <Python.h>
#include "structmember.h"
#include "types.h"
#include <uart/usf.h>
#include "trace_obj.h"
#include "access_obj.h"

static int
trace_obj_init(trace_obj_t *self, PyObject *args, PyObject *kwds)
{
    self->type = USF_EVENT_TRACE;
    self->access = PyObject_New(access_obj_t, &access_obj_type);
    return 0;
}

static void
trace_obj_dealloc(trace_obj_t *self)
{
    Py_XDECREF((PyObject *)self->access);
    self->ob_type->tp_free((PyObject *)self);
}

static PyMemberDef trace_obj_members[] = {
    {
	"type",
	USF_TYPE(usf_event_type_t),
	offsetof(trace_obj_t, type ),
	0,
	"XXX"
    }, {
	"access",
	T_OBJECT,
	offsetof(trace_obj_t, access),
	0,
	"XXX"
    }, {
	NULL
    }
};

PyTypeObject trace_obj_type = {
    PyObject_HEAD_INIT(NULL)
    0,                                          /* ob_size              */
    "pyusf.Trace",                              /* tp_name              */
    sizeof(trace_obj_t),                        /* tp_basicsize         */
    0,                                          /* tp_itemsize          */
    (destructor)trace_obj_dealloc,              /* tp_dealloc           */
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
    0,                                          /* tp_iter              */
    0,                                          /* tp_iternext          */
    0,                                          /* tp_methods           */
    trace_obj_members,                          /* tp_members           */
    0,                                          /* tp_getset            */
    0,                                          /* tp_base              */
    0,                                          /* tp_dict              */
    0,                                          /* tp_descr_get         */
    0,                                          /* tp_descr_set         */
    0,                                          /* tp_dictoffset        */
    (initproc)trace_obj_init,                   /* tp_init              */
    0,                                          /* tp_alloc             */
    PyType_GenericNew,                          /* tp_new               */
};


trace_obj_t *
trace_obj_create(usf_event_trace_t *trace)
{
    trace_obj_t *ret;

    ret = PyObject_New(trace_obj_t, &trace_obj_type);
    ret->type = USF_EVENT_TRACE;
    ret->access = access_obj_create(&trace->access);

    return ret;
}
