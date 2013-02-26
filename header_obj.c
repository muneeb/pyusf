#include <Python.h>
#include "structmember.h"
#include "types.h"
#include <uart/usf.h>
#include "header_obj.h"

#define ATTROFFSET(_attr) \
    (offsetof(header_obj_t, header) + offsetof(usf_header_t, _attr))

static PyMemberDef header_obj_members[] = {
    {
	"version",
	USF_TYPE(usf_version_t),
	ATTROFFSET(version),
	0,
	"XXX"
    }, {
	"compression",
	USF_TYPE(usf_compression_t),
	ATTROFFSET(compression),
	0,
	"XXX"
    }, {
	"flags",
	USF_TYPE(usf_flags_t),
	ATTROFFSET(flags),
	0,
	"XXX"
    }, {
	"time_begin",
	USF_TYPE(usf_wtime_t),
	ATTROFFSET(time_begin),
	0,
	"XXX"
    }, {
	"time_end",
	USF_TYPE(usf_wtime_t),
	ATTROFFSET(time_end),
	0,
	"XXX"
    }, {
	"line_sizes",
	USF_TYPE(usf_line_size_mask_t),
	ATTROFFSET(line_sizes),
	0,
	"XXX"
    }, {
	NULL
    }
};

PyTypeObject header_obj_type = {
    PyObject_HEAD_INIT(NULL)
    0,                                          /* ob_size              */
    "pyusf.Header",                             /* tp_name              */
    sizeof(header_obj_t),                       /* tp_basicsize         */
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
    header_obj_members,                         /* tp_members           */
    0,                                          /* tp_getset            */
    0,                                          /* tp_base              */
    0,                                          /* tp_dict              */
    0,                                          /* tp_descr_get         */
    0,                                          /* tp_descr_set         */
    0,                                          /* tp_dictoffset        */
    0,                                          /* tp_init              */
    0,                                          /* tp_alloc             */
    PyType_GenericNew,                          /* tp_new               */
};

header_obj_t *
header_obj_create(const usf_header_t *header)
{
    header_obj_t *ret;

    ret = PyObject_New(header_obj_t, &header_obj_type);
    ret->header = *header;

    return ret;
}

