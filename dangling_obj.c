#include <Python.h>
#include "structmember.h"
#include "types.h"
#include "dangling_obj.h"

    
static int
dangling_obj_init(dangling_obj_t *self, PyObject *args, PyObject *kwds)
{
    self->type = USF_EVENT_DANGLING;
    self->begin = PyObject_New(access_obj_t, &access_obj_type);
    return 0;
}

static void
dangling_obj_dealloc(dangling_obj_t* self)
{
    Py_XDECREF((PyObject *)self->begin);
    self->ob_type->tp_free((PyObject *)self);
}

static PyMemberDef dangling_obj_members[] = {
    {
	"type",
	USF_TYPE(usf_event_type_t),
	offsetof(dangling_obj_t, type),
	0,
	"XXX"
    }, {
	"begin",
	T_OBJECT,
	offsetof(dangling_obj_t, begin),
	0,
	"XXX"
    }, {
	"line_size",
	USF_TYPE(usf_line_size_2_t),
	offsetof(dangling_obj_t, line_size),
	0,
	"XXX"
    }, {
	NULL
    }
};

PyTypeObject dangling_obj_type = {
    PyObject_HEAD_INIT(NULL)
    0,                                          /* ob_size              */
    "pyusf.Dangling",                           /* tp_name              */
    sizeof(dangling_obj_t),                     /* tp_basicsize         */
    0,                                          /* tp_itemsize          */
    (destructor)dangling_obj_dealloc,           /* tp_dealloc           */
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
    dangling_obj_members,                       /* tp_members           */
    0,                                          /* tp_getset            */
    0,                                          /* tp_base              */
    0,                                          /* tp_dict              */
    0,                                          /* tp_descr_get         */
    0,                                          /* tp_descr_set         */
    0,                                          /* tp_dictoffset        */
    (initproc)dangling_obj_init,                /* tp_init              */
    0,                                          /* tp_alloc             */
    PyType_GenericNew,                          /* tp_new               */
};


dangling_obj_t *
dangling_obj_create(usf_event_dangling_t *dangling)
{
    dangling_obj_t *ret;

    ret = PyObject_New(dangling_obj_t, &dangling_obj_type);
    ret->type = USF_EVENT_DANGLING;
    ret->begin = access_obj_create(&dangling->begin);
    ret->line_size = dangling->line_size;

    return ret;
}
