#include "big_data_tools.h"

size_t get_real_tuple_size(uint64_t pattern_size) {
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
    code |= read_from_file(key_value, file);
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
        code |= read_key(element_pattern, file);
        *array_of_key = element_pattern;
    }

    size_t real_tuple_size = get_real_tuple_size(subheader->pattern_size);
    size_t real_id_array_size = subheader->cur_id*OFFSET_VALUE_SIZE/real_tuple_size +
            (subheader->cur_id*OFFSET_VALUE_SIZE%real_tuple_size ? real_tuple_size : 0);
    uint64_t *id_array = (uint64_t *) malloc(real_id_array_size);
    header->id_sequence = id_array;
    code |= read_from_file(id_array, file);

    code |= fgetpos(file, fpos);

    return code;
}

enum file_read_status read_basic_tuple(struct tuple **tuple, FILE *file, struct tree_header *tree_header) {
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
    code |= read_from_file(data, file);
    temp_tuple->data = data;

    *tuple = temp_tuple;

    return code;
}

enum file_read_status read_string_tuple(struct tuple **tuple, FILE *file, struct tree_header *tree_header) {
    union tuple_header *header = (union tuple_header *) malloc(sizeof(union tuple_header));
    enum file_read_status code = read_from_file(header, file);
    struct tuple *temp_tuple = (struct tuple *) malloc(sizeof(struct tuple));
    temp_tuple->header = *header;
    free(header);

    uint64_t *data = (uint64_t *) malloc(get_real_tuple_size(tree_header->subheader->pattern_size));
    code |= read_from_file(data, file);
    temp_tuple->data = data;

    *tuple = temp_tuple;

    return code;
}

static enum file_write_status write_tree_subheader(FILE *file, struct tree_subheader *subheader){
    enum file_write_status code = write_to_file(subheader, file);
    return code;
}

static enum file_write_status write_pattern(FILE *file, struct key **pattern, size_t pattern_size){
    enum file_write_status code = NULL_VALUE;
    for (; pattern_size-- > 0; pattern++){
        code |= write_to_file((*pattern)->header, file);
        code |= write_to_file((*pattern)->key_value, file);
    }
    return code;
}

static enum file_write_status write_id_sequence(FILE *file, uint64_t *id_sequence){
    enum file_write_status code = write_to_file(id_sequence, file);
    return code;
}

enum file_write_status write_tree_header(FILE *file, struct tree_header *header, size_t pattern_size){
    enum file_write_status code = write_tree_subheader(file, header->subheader);
    code |= write_pattern(file, header->pattern, pattern_size);
    code |= write_id_sequence(file, header->id_sequence);
    return code;
}

enum file_write_status init_empty_file(FILE *file, char **pattern, uint32_t *types, size_t pattern_size, size_t *key_sizes){
    fseek(file, 0, SEEK_SET);
    struct tree_header *header = (struct tree_header *) malloc(sizeof(struct tree_header));
    generate_empty_tree_header(pattern, types, pattern_size, key_sizes, header);
    return write_tree_header(file, header, pattern_size);
}

enum file_open_status open_file_anyway(FILE **file, char *filename){
    enum file_open_status code = open_exist_file(filename, file);
    if (code) {
        code = open_new_file(filename, file);
    }
    return code;
}

enum file_write_status write_tuple(FILE *file, struct tuple *tuple){
    union tuple_header *tuple_header = malloc(sizeof(union  tuple_header));
    *tuple_header = tuple->header;
    enum file_write_status code = write_to_file(tuple_header, file);
    free(tuple_header);
    code |= write_to_file(tuple->data, file);
    return code;
}