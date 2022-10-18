#include "big_data_tools.h"

static size_t get_real_tuple_size(uint64_t pattern_size) {
    return pattern_size * SINGLE_TUPLE_VALUE_SIZE < MINIMAL_TUPLE_SIZE
           ? MINIMAL_TUPLE_SIZE
           : SINGLE_TUPLE_VALUE_SIZE;
}

static enum file_read_status read_tree_subheader(struct tree_subheader *header, FILE *file) {
    enum file_read_status code = read_from_file(header, file);
    return code;
}

static enum file_read_status read_key(struct key *key, FILE *file) {
    struct key_header *header = malloc(sizeof(struct key_header));
    enum file_read_status code = read_from_file(header, file);
    key->header = header;

    char *key_value = (char *) malloc(header->size/FILE_GRANULARITY + (header->size % FILE_GRANULARITY ? FILE_GRANULARITY : 0));
    code = read_from_file(key_value, file) | code;
    key->key_value = key_value;

    return code;
}

enum file_read_status read_tree_header(struct tree_header *header, FILE *file, fpos_t *fpos) {
    struct tree_subheader *subheader= (struct tree_subheader *) malloc(sizeof(struct tree_subheader));
    enum file_read_status code = read_tree_subheader(subheader, file);
    header->subheader = subheader;

    struct key **array_of_key = malloc(sizeof(struct key *) * subheader->pattern_size);
    header->pattern = array_of_key;
    for (size_t iter = subheader->pattern_size; iter-- > 0; array_of_key++){
        struct key *element_pattern = malloc(sizeof(struct key));
        code = read_key(element_pattern, file) | code;
        *array_of_key = element_pattern;
    }

    size_t real_tuple_size = get_real_tuple_size(subheader->pattern_size);
    size_t real_id_array_size = subheader->cur_id*OFFSET_VALUE_SIZE/real_tuple_size +
            (subheader->cur_id*OFFSET_VALUE_SIZE%real_tuple_size ? real_tuple_size : 0);
    uint64_t *id_array = (uint64_t *) malloc(real_id_array_size);
    header->id_sequence = id_array;
    code = read_from_file(id_array, file) | code;

    code = fgetpos(file, fpos) | code;

    return code;
}

static enum file_read_status read_basic_tuple(struct tuple **tuple, FILE *file, struct tree_header *tree_header) {
    union tuple_header *header = (union tuple_header *) malloc(sizeof(union tuple_header));
    enum file_read_status code = read_from_file(header, file);
    if (header->alloc) {
        *tuple = (struct tuple *)header->alloc;
        free(header);
        return code;
    }
    fseek(file, -(sizeof(union tuple_header)), SEEK_CUR);
    struct tuple *temp_tuple = (struct tuple *) malloc(sizeof(struct tuple));
    temp_tuple->header = *header;
    free(header);
    header->alloc = (uint64_t) temp_tuple;
    write_to_file(header, file);


    uint64_t *data = (uint64_t *) malloc(get_real_tuple_size(tree_header->subheader->pattern_size));
    code = read_from_file(data, file) | code;
    temp_tuple->data = data;

    *tuple = temp_tuple;

    return code;
}

static enum file_read_status read_string_tuple(struct tuple **tuple, FILE *file, struct tree_header *tree_header) {
    union tuple_header *header = (union tuple_header *) malloc(sizeof(union tuple_header));
    enum file_read_status code = read_from_file(header, file);
    struct tuple *temp_tuple = (struct tuple *) malloc(sizeof(struct tuple));
    temp_tuple->header = *header;
    free(header);

    uint64_t *data = (uint64_t *) malloc(get_real_tuple_size(tree_header->subheader->pattern_size));
    code = read_from_file(data, file) | code;
    temp_tuple->data = data;

    *tuple = temp_tuple;

    return code;
}