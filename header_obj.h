#ifndef _HEADER_OBJ_H_
#define _HEADER_OBJ_H_
#include <Python.h>
#include <uart/usf.h>

typedef struct {
    PyObject_HEAD

    usf_header_t header;
} header_obj_t;

extern PyTypeObject header_obj_type;

header_obj_t* header_obj_create(const usf_header_t *header);

#endif /* _HEADER_OBJ_H_ */
