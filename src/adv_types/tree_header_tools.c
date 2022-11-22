#include "adv_types/tree_header_tools.h"

enum crud_operation_status offset_to_id(FILE *file, uint64_t* id, uint64_t offset) {
    fseek(file, 0, SEEK_SET);
    struct tree_header *header = malloc(sizeof(struct tree_header));
    size_t pos;
    read_tree_header(header, file, &pos);
    for (size_t iter = 0; iter < header->subheader->cur_id; iter++){
        if (header->id_sequence[iter] == offset){
            *id = iter;
            free(header);
            return CRUD_OK;
        }
    }
    free_tree_header(header);
    return CRUD_INVALID;
}

enum crud_operation_status id_to_offset(FILE *file, uint64_t id, uint64_t* offset) {
    fseek(file, 0, SEEK_SET);
    struct tree_header *header = malloc(sizeof(struct tree_header));
    size_t pos;
    read_tree_header(header, file, &pos);
    *offset = header->id_sequence[id];
    free_tree_header(header);
    return CRUD_OK;
}

struct uint64_list *get_childs_by_id(FILE *file, uint64_t id) {
    fseek(file, 0, SEEK_SET);
    struct tree_header *header = malloc(sizeof(struct tree_header));
    read_tree_header_np(header, file);
    struct uint64_list *result = NULL;
    union tuple_header cur_header;
    for (uint64_t iter = 0; iter < header->subheader->cur_id; iter++) {
        fseek(file, (int64_t) header->id_sequence[iter], SEEK_SET);
        read_from_file(&cur_header, file, sizeof(union tuple_header));
        if (cur_header.parent == id) append_to_uint64_list(iter, &result);
    }
    free_tree_header(header);
    return result;
}

uint64_t remove_from_id_array(FILE *file, uint64_t id) {
    uint64_t offset;
    fseek(file, 0, SEEK_SET);
    struct tree_header *header = malloc(sizeof(struct tree_header));
    size_t pos;
    read_tree_header(header, file, &pos);
    if (header->id_sequence[id] == NULL_VALUE) {
        free_tree_header(header);
        return NULL_VALUE;
    } else {
        offset = header->id_sequence[id];
        if (header->subheader->cur_id-1 == id) {
            header->subheader->cur_id--;
        }
        header->id_sequence[id] = 0;
        write_tree_header(file, header);
        free_tree_header(header);
        return offset;
    }
}

enum crud_operation_status append_to_id_array(FILE *file, uint64_t offset) {
    fseek(file, 0, SEEK_SET);
    struct tree_header *header = malloc(sizeof(struct tree_header));
    size_t pos;
    read_tree_header(header, file, &pos);
    if (!((header->subheader->cur_id + 1) % get_real_id_array_size(header->subheader->pattern_size, header->subheader->cur_id))){
        uint64_t from = ftell(file);
        fseek(file, 0, SEEK_END);
        swap_tuple_to(file, from, ftell(file), get_real_tuple_size(header->subheader->pattern_size));
    }
    header->id_sequence[header->subheader->cur_id] = offset;
    header->subheader->cur_id++;
    write_tree_header(file, header);
    free_tree_header(header);
    return 0;
}

void get_types(FILE *file, uint32_t **types, size_t *size) {
    fseek(file, 0, SEEK_SET);
    struct tree_header *header = malloc(sizeof(struct tree_header));
    size_t pos;
    read_tree_header(header, file, &pos);
    uint32_t *temp_types = malloc(header->subheader->pattern_size * sizeof(uint32_t));
    for (size_t iter = 0; iter < header->subheader->pattern_size; iter++) {
        temp_types[iter] = header->pattern[iter]->header->type;
    }
    *types = temp_types;
    *size = header->subheader->pattern_size;
    free_tree_header(header);
}
