#ifndef _SAMPLE_OBJ_H_
#define _SAMPLE_OBJ_H_
#include <Python.h>
#include <uart/usf.h>
#include "access_obj.h"

typedef struct {
    PyObject_HEAD

    usf_event_type_t type;
    access_obj_t *begin;
    access_obj_t *end;
    usf_line_size_2_t line_size;
} sample_obj_t;

extern PyTypeObject sample_obj_type;

sample_obj_t* sample_obj_create(usf_event_sample_t *sample);

#endif /* _SAMPLE_OBJ_H */
