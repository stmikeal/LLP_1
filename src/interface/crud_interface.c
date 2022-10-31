#include "crud_interface.h"

enum crud_operation_status add_tuple(FILE *file, uint64_t *fields, uint64_t parent_id){
    uint32_t *types;
    size_t size;
    get_types(file, &types, &size);
    struct tuple *new_tuple = malloc(sizeof(struct tuple));
    union tuple_header new_tuple_header = {.parent = parent_id, .alloc = (uint64_t) new_tuple};
    new_tuple->header = new_tuple_header;
    new_tuple->data = malloc(size);
    uint64_t *link = malloc(sizeof(uint64_t));
    for(size_t iter = 0; iter < size; iter++){
        if (types[iter] == STRING_TYPE){
            insert_string_tuple(file, (char *) fields[iter], get_real_tuple_size(size), link);
            new_tuple->data[iter] = *link;
        } else {
            new_tuple->data[iter] = (uint64_t) fields[iter];
        }
    }
    size_t full_tuple_size = sizeof(union tuple_header) + get_real_tuple_size(size);
    enum crud_operation_status status = insert_new_tuple(file, new_tuple, full_tuple_size, link);

    free(link);
    return status;
}