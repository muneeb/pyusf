#ifndef _ACCESS_OBJ_H_
#define _ACCESS_OBJ_H_
#include <Python.h>
#include <uart/usf.h>

typedef struct {
    PyObject_HEAD

    usf_access_t access;
} access_obj_t;

extern PyTypeObject access_obj_type;

access_obj_t* access_obj_create(usf_access_t *access);

#endif /* _ACCESS_OBJ_H_ */
