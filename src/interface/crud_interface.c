#include "crud_interface.h"

enum crud_operation_status add_tuple(FILE *file, struct tuple *tuple){
    size_t full_tuple_size = sizeof(union tuple_header);
    uint32_t *types;
    size_t size;
    get_types(file, &types, &size);
    return insert_new_tuple(file, tuple, full_tuple_size + get_real_tuple_size(size), &size);
}