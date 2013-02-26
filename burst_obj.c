#include <Python.h>
#include "structmember.h"
#include "types.h"
#include "burst_obj.h"

static int
bust_obj_init(burst_obj_t *self, PyObject *args, PyObject *kwds)
{
    self->type = USF_EVENT_BURST;
    return 0;
}

#define ATTROFFSET(_attr) \
    (offsetof(burst_obj_t, burst) + offsetof(usf_event_burst_t, _attr))

static PyMemberDef burst_obj_members[] = {
    {
	"type",
	USF_TYPE(usf_event_type_t),
	offsetof(burst_obj_t, type),
	0,
	"XXX"
    }, {
	"begin_time",
	USF_TYPE(usf_atime_t),
	ATTROFFSET(begin_time),
	0,
	"XXX"
    }, {
	NULL
    }
};

PyTypeObject burst_obj_type = {
    PyObject_HEAD_INIT(NULL)
    0,                                          /* ob_size              */
    "pyusf.Burst",                              /* tp_name              */
    sizeof(burst_obj_t),                        /* tp_basicsize         */
    0,                                          /* tp_itemsize          */
    0,                                          /* tp_dealloc           */
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
    burst_obj_members,                          /* tp_members           */
    0,                                          /* tp_getset            */
    0,                                          /* tp_base              */
    0,                                          /* tp_dict              */
    0,                                          /* tp_descr_get         */
    0,                                          /* tp_descr_set         */
    0,                                          /* tp_dictoffset        */
    (initproc)bust_obj_init,                    /* tp_init              */
    0,                                          /* tp_alloc             */
    PyType_GenericNew,                          /* tp_new               */
};



burst_obj_t *
burst_obj_create(usf_event_burst_t *burst)
{
    burst_obj_t *ret;

    ret = PyObject_New(burst_obj_t, &burst_obj_type);
    ret->type = USF_EVENT_BURST;
    ret->burst = *burst;

    return ret;
}
