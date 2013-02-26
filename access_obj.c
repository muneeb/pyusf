#include <Python.h>
#include "structmember.h"
#include <uart/usf.h>
#include "types.h"
#include "access_obj.h"

#define ATTROFFSET(_attr) \
    (offsetof(access_obj_t, access) + offsetof(usf_access_t, _attr))

static PyMemberDef access_obj_members[] = {
    {
	"pc",
	USF_TYPE(usf_addr_t),
	ATTROFFSET(pc),
	0,
	"XXX"
    }, {
	"addr",
	USF_TYPE(usf_addr_t),
	ATTROFFSET(addr),
	0,
	"XXX"
    }, {
	"time",
	USF_TYPE(usf_atime_t),
	ATTROFFSET(time),
	0,
	"XXX"
    }, {
	"tid",
	USF_TYPE(usf_tid_t),
	ATTROFFSET(tid),
	0,
	"XXX"
    }, {
	"len",
	USF_TYPE(usf_alen_t),
	ATTROFFSET(len),
	0,
	"XXX"
    }, {
	"type",
	USF_TYPE(usf_atype_t),
	ATTROFFSET(type),
	0,
	"XXX"
    }, {
	"operand",
	USF_TYPE(usf_operand_t),
	ATTROFFSET(operand),
	0,
	"Index of memory operand for multi-oreand instructions"
    }, {
	NULL
    }
};


PyTypeObject access_obj_type = {
    PyObject_HEAD_INIT(NULL)
    0,                                          /* ob_size              */
    "pyusf.Access",                             /* tp_name              */
    sizeof(access_obj_t),                       /* tp_basicsize         */
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
    access_obj_members,                         /* tp_members           */
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


access_obj_t *
access_obj_create(usf_access_t *access)
{
    access_obj_t *ret;

    ret = PyObject_New(access_obj_t, &access_obj_type);
    ret->access = *access;

    return ret;
}
