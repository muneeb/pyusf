#ifndef _BURST_OBJ_H_
#define _BURST_OBJ_H_
#include <Python.h>
#include <uart/usf.h>

typedef struct {
    PyObject_HEAD

    usf_event_type_t type;
    usf_event_burst_t burst;
} burst_obj_t;

extern PyTypeObject burst_obj_type;

burst_obj_t* burst_obj_create(usf_event_burst_t *burst);


#endif /* _BURST_OBJ_H_ */
