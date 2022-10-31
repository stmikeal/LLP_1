#ifndef CRUD_INTERFACE_H
#define CRUD_INTERFACE_H
#include "basic_crud.h"

enum crud_operation_status add_tuple(FILE *file, uint64_t *fields, uint64_t parent_id);
enum crud_operation_status get_tuple(FILE *file, uint64_t **fields, uint64_t id);
#endif
