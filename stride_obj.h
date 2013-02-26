#ifndef _STRIDE_OBJ_H_
#define _STRIDE_OBJ_H_
#include <Python.h>
#include <uart/usf.h>
#include "access_obj.h"

typedef struct {
    PyObject_HEAD

    usf_event_type_t type;
    access_obj_t *begin;
    access_obj_t *end;
    usf_line_size_2_t line_size;
} stride_obj_t;

extern PyTypeObject stride_obj_type;

stride_obj_t* stride_obj_create(usf_event_stride_t *stride);

#endif /* _STRIDE_OBJ_H */
