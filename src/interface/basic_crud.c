#include "basic_crud.h"

enum crud_operation_status delete_last_tuple(FILE *file, size_t full_tuple_size){
    fseek(file, full_tuple_size, SEEK_END);
    int fd = fileno(file);
    return ftruncate(fd, ftell(file));
}

enum crud_operation_status swap_tuple_to(FILE *file, struct tuple *tuple_to_swap, uint64_t pos){
    fseek(file, (long) pos, SEEK_SET);
    return (enum crud_operation_status) write_tuple(file, tuple_to_swap);
}

enum crud_operation_status insert_new_tuple(FILE *file, struct tuple *tuple_to_swap, size_t full_tuple_size){
    fseek(file, 0, SEEK_END);
    int fd = fileno(file);
    return ftruncate(fd, ftell(file) + full_tuple_size);
}


