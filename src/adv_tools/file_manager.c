#include "file_manager.h"

enum file_write_status init_empty_file(FILE *file, char **pattern, uint32_t *types, size_t pattern_size, size_t *key_sizes) {
    fseek(file, 0, SEEK_SET);
    struct tree_header *header = (struct tree_header *) malloc(sizeof(struct tree_header));
    generate_empty_tree_header(pattern, types, pattern_size, key_sizes, header);
    enum file_write_status code =  write_tree_header(file, header);
    free_tree_header(header);
    return  code;
}

enum file_open_status open_file_anyway(FILE **file, char *filename){
    enum file_open_status code = open_exist_file(filename, file);
    if (code) {
        code = open_new_file(filename, file);
    }
    char *s1 = "name";
    char *s2 = "code";
    char *ss[2] = {s1, s2};
    uint32_t t[2] = {3, 1};
    size_t si[2] = {5, 5};
    init_empty_file(*file, ss, t, 2, si);
    return code;
}
