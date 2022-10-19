#include "empty_generator.h"

static void generate_empty_tree_subheader(struct tree_subheader *subheader, size_t pattern_size) {
    subheader->pattern_size = (uint64_t) pattern_size;
    subheader->cur_id = NULL_VALUE;
    subheader->ASCII_signature = BIG_ENDIAN;
    subheader->first_seq = NULL_VALUE;
    subheader->second_seq = NULL_VALUE;
    subheader->root_offset = NULL_VALUE;
    for (size_t index = 0; index < RESERVED_CELLS; index++){
        subheader->reserved[index] = NULL_VALUE;
    }
}

void generate_empty_tree_header(char **pattern, size_t pattern_size, struct tree_header *header){
    header->subheader = (struct tree_subheader *) malloc(sizeof(struct tree_subheader));
    generate_empty_tree_subheader(header->subheader, pattern_size);

}


