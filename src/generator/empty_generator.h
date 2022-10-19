#ifndef EMPTY_GENERATOR_H
#define GENERATOR_H
#include "../interface/signatures.h"
#include "../filetools/basic_file_manager.h"
#include <stdlib.h>
#include "../interface/configuration.h"
#include "../filetools/big_data_tools.h"

void generate_empty_tree_header(char **pattern, uint32_t *types,size_t pattern_size, size_t *key_sizes, struct tree_header *header);

#endif
