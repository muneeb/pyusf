#ifndef _DANGLING_OBJ_H_
#define _DANGLING_OBJ_H_
#include <Python.h>
#include <uart/usf.h>
#include "access_obj.h"

typedef struct {
    PyObject_HEAD

    usf_event_type_t type;
    access_obj_t *begin;
    usf_line_size_2_t line_size;
} dangling_obj_t;

extern PyTypeObject dangling_obj_type;

dangling_obj_t* dangling_obj_create(usf_event_dangling_t *dangling);

#endif /* _DANGLING_OBJ_H_ */
