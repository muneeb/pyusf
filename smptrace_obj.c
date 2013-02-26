#include <Python.h>
#include <numpy/ndarraytypes.h> 
#include <numpy/ndarrayobject.h>
#include "structmember.h"
#include <uart/usf.h>
#include "types.h"
#include "smptrace_obj.h"
#include "access_obj.h"


static int
smptrace_obj_init(smptrace_obj_t *self, PyObject *args, PyObject *kwds)
{
    self->type = USF_EVENT_SMPTRACE;
    self->begin = PyObject_New(access_obj_t, &access_obj_type);
    return 0;
}

static void
smptrace_obj_dealloc(smptrace_obj_t* self)
{
    Py_XDECREF((PyObject *)self->begin);
    self->ob_type->tp_free((PyObject *)self);
}


static PyMemberDef smptrace_obj_members[] = {
    {
	"type",
	USF_TYPE(usf_event_type_t),
	offsetof(smptrace_obj_t, type),
	0,
	"XXX"
    }, {
	"begin",
	T_OBJECT,
	offsetof(smptrace_obj_t, begin),
	0,
	"XXX"
    }, {
	"ins_trace",
	T_OBJECT,
	offsetof(smptrace_obj_t, ins_trace),
	0,
	"XXX"
    }, {
	NULL
    }
};

PyTypeObject smptrace_obj_type = {
    PyObject_HEAD_INIT(NULL)
    0,                                          /* ob_size              */
    "pyusf.Smptrace",                             /* tp_name              */
    sizeof(smptrace_obj_t),                       /* tp_basicsize         */
    0,                                            /* tp_itemsize          */
    (destructor)smptrace_obj_dealloc,             /* tp_dealloc           */
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
    smptrace_obj_members,                         /* tp_members           */
    0,                                          /* tp_getset            */
    0,                                          /* tp_base              */
    0,                                          /* tp_dict              */
    0,                                          /* tp_descr_get         */
    0,                                          /* tp_descr_set         */
    0,                                          /* tp_dictoffset        */
    (initproc)smptrace_obj_init,                  /* tp_init              */
    0,                                          /* tp_alloc             */
    PyType_GenericNew,                          /* tp_new               */
};


smptrace_obj_t *
smptrace_obj_create(usf_event_smptrace_t *smptrace)
{
    smptrace_obj_t *ret;
    int i;
    npy_intp size[1] = {SMPTRACE_LEN};
    PyObject* c;
    void *arr_data;
    
    ret = PyObject_New(smptrace_obj_t, &smptrace_obj_type);
    ret->type = USF_EVENT_SMPTRACE;
    ret->begin = access_obj_create(&smptrace->begin);
    
    import_array();

    c = PyArray_SimpleNew(1, size, NPY_ULONG);

    arr_data = PyArray_DATA((PyArrayObject*) c);

    memcpy(arr_data, smptrace->ins_trace, PyArray_ITEMSIZE((PyArrayObject*) c) * size[0]);

    ret->ins_trace = c; 

    return ret;
}
