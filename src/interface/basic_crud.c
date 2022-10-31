#include "basic_crud.h"

enum crud_operation_status delete_last_tuple(FILE *file, size_t full_tuple_size){
    fseek(file, full_tuple_size, SEEK_END);
    int fd = fileno(file);
    return ftruncate(fd, ftell(file));
}

enum crud_operation_status swap_tuple_to(FILE *file, struct tuple *tuple_to_swap, uint64_t pos, size_t tuple_size){
    fseek(file, (long) pos, SEEK_SET);
    return (enum crud_operation_status) write_tuple(file, tuple_to_swap, tuple_size);
}

enum crud_operation_status insert_new_tuple(FILE *file, struct tuple *tuple, size_t full_tuple_size, uint64_t *tuple_pos){
    fseek(file, 0, SEEK_END);
    *tuple_pos = ftell(file);
    int fd = fileno(file);
    ftruncate(fd, ftell(file) + full_tuple_size);
    return (enum crud_operation_status) write_tuple(file, tuple, full_tuple_size - sizeof(union tuple_header));
}



enum crud_operation_status insert_string_tuple(FILE *file, char *string, size_t tuple_size, uint64_t *str_pos){
    size_t len = strlen(string);
    size_t count = len / tuple_size + (len % tuple_size ? 1 : 0) - 1;
    struct tuple *temp_tuple = malloc(sizeof(struct tuple));
    uint64_t *temp_tuple_content = (uint64_t *) string;
    size_t pos = (size_t) ftell(file);
    *str_pos = ftell(file);
    uint64_t fake_pos;
    fseek(file, 0, SEEK_END);
    for(size_t iter = 0; count > iter; iter ++) {
        if (count-1 == iter){
            temp_tuple->header.next = 0;
        } else {
            temp_tuple->header.next = pos + (tuple_size + sizeof(union tuple_header)) * (iter + 1);
        }
        if (0 == iter){
            temp_tuple->header.prev = 0;
        } else {
            temp_tuple->header.prev = pos + (tuple_size + sizeof(union tuple_header)) * (iter - 1);
        }
        temp_tuple->data = temp_tuple_content;
        insert_new_tuple(file, temp_tuple, tuple_size + sizeof(union tuple_header), &fake_pos);
    }
    return 0;
}

void get_types(FILE *file, uint32_t **types, size_t *size){
    fseek(file, 0, SEEK_SET);
    struct tree_header *header = malloc(sizeof(struct tree_header));
    size_t pos;
    read_tree_header(header, file, &pos);
    uint32_t *temp_types = malloc(header->subheader->pattern_size * sizeof (uint32_t));
    for(size_t iter = 0; iter < header->subheader->pattern_size; iter++){
        temp_types[iter] = header->pattern[iter]->header->type;
    }
    *types = temp_types;
    *size = header->subheader->pattern_size;
    free(header);
}

enum crud_operation_status change_parameter(FILE *file, enum tree_subheader_parameter parameter, uint64_t *value){
    return 0;
}


