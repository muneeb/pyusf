#ifndef _TRACE_OBJ_H_
#define _TRACE_OBJ_H_
#include <Python.h>
#include <uart/usf.h>
#include "access_obj.h"

typedef struct {
    PyObject_HEAD

    usf_event_type_t type;
    access_obj_t *access;
} trace_obj_t;

extern PyTypeObject trace_obj_type;

trace_obj_t* trace_obj_create(usf_event_trace_t *trace);

#endif /* _TRACE_OBJ_H */
