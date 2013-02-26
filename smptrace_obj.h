#ifndef _SMPTRACE_OBJ_H_
#define _SMPTRACE_OBJ_H_
#include <Python.h>
#include <uart/usf.h>
#include "access_obj.h"

typedef struct {
    PyObject_HEAD

    usf_event_type_t type;
    access_obj_t *begin;
    usf_addr_t *ins_trace; //[SMPTRACE_LEN];
} smptrace_obj_t;

extern PyTypeObject smptrace_obj_type;

smptrace_obj_t* smptrace_obj_create(usf_event_smptrace_t *smptrace);

#endif /* _SMPTRACE_OBJ_H */
