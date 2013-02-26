#include <Python.h>
#include "structmember.h"
#include <uart/usf.h>
#include "types.h"
#include "sample_obj.h"
#include "access_obj.h"


static int
sample_obj_init(sample_obj_t *self, PyObject *args, PyObject *kwds)
{
    self->type = USF_EVENT_SAMPLE;
    self->begin = PyObject_New(access_obj_t, &access_obj_type);
    self->end = PyObject_New(access_obj_t, &access_obj_type);
    return 0;
}

static void
sample_obj_dealloc(sample_obj_t* self)
{
    Py_XDECREF((PyObject *)self->begin);
    Py_XDECREF((PyObject *)self->end);
    self->ob_type->tp_free((PyObject *)self);
}


static PyMemberDef sample_obj_members[] = {
    {
	"type",
	USF_TYPE(usf_event_type_t),
	offsetof(sample_obj_t, type),
	0,
	"XXX"
    }, {
	"begin",
	T_OBJECT,
	offsetof(sample_obj_t, begin),
	0,
	"XXX"
    }, {
	"end",
	T_OBJECT,
	offsetof(sample_obj_t, end),
	0,
	"XXX"
    }, {
	"line_size",
	USF_TYPE(usf_line_size_2_t),
	offsetof(sample_obj_t, line_size),
	0,
	"XXX"
    }, {
	NULL
    }
};

PyTypeObject sample_obj_type = {
    PyObject_HEAD_INIT(NULL)
    0,                                          /* ob_size              */
    "pyusf.Sample",                             /* tp_name              */
    sizeof(sample_obj_t),                       /* tp_basicsize         */
    0,                                          /* tp_itemsize          */
    (destructor)sample_obj_dealloc,             /* tp_dealloc           */
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
    sample_obj_members,                         /* tp_members           */
    0,                                          /* tp_getset            */
    0,                                          /* tp_base              */
    0,                                          /* tp_dict              */
    0,                                          /* tp_descr_get         */
    0,                                          /* tp_descr_set         */
    0,                                          /* tp_dictoffset        */
    (initproc)sample_obj_init,                  /* tp_init              */
    0,                                          /* tp_alloc             */
    PyType_GenericNew,                          /* tp_new               */
};


sample_obj_t *
sample_obj_create(usf_event_sample_t *sample)
{
    sample_obj_t *ret;

    ret = PyObject_New(sample_obj_t, &sample_obj_type);
    ret->type = USF_EVENT_SAMPLE;
    ret->begin = access_obj_create(&sample->begin);
    ret->end = access_obj_create(&sample->end);
    ret->line_size = sample->line_size;

    return ret;
}
