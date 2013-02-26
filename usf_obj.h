#ifndef _USF_OBJ_H_
#define _USF_OBJ_H_
#include <Python.h>
#include <uart/usf.h>
#include "header_obj.h"

typedef struct {
    PyObject_HEAD

    usf_file_t *usf_file;
    header_obj_t *header;
} usf_obj_t;

extern PyTypeObject usf_obj_type;

#endif /* _USF_OBJ_H_ */
