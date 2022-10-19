#ifndef BIG_DATA_TOOLS_H
#define BIG_DATA_TOOLS_H
#include <stdlib.h>
#include "../interface/configuration.h"
#include "../interface/signatures.h"
#include "../generator/empty_generator.h"
#include "basic_file_manager.h"

size_t get_real_tuple_size(uint64_t pattern_size);
enum file_write_status write_tuple(FILE *file, struct tuple *tuple);
enum file_open_status open_file_anyway(FILE **file, char *filename);
enum file_write_status init_empty_file(FILE *file, char **pattern, uint32_t *types, size_t pattern_size, size_t *key_sizes);
enum file_write_status write_tree_header(FILE *file, struct tree_header *header, size_t pattern_size);
enum file_read_status read_string_tuple(struct tuple **tuple, FILE *file, struct tree_header *tree_header);
enum file_read_status read_basic_tuple(struct tuple **tuple, FILE *file, struct tree_header *tree_header);
enum file_read_status read_tree_header(struct tree_header *header, FILE *file, fpos_t *fpos);

#endif
