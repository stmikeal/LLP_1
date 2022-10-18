#ifndef SIGNATURE_H
#define SIGNATURE_H

#include <stdio.h>
#include <inttypes.h>

/**
 * Container to store file parameters
 * ASCII_signature - 0xFFFE or 0xFEFF character to define little- or big- endian byte order
 * root_offset     - offset to root element
 * first_seq       - sequence that increase, when we open working file
 * second_seq      - sequence that increase, when we close working file
 * cur_id          - sequence to manage auto-incremental id
 * reserved[16]    - reserved empty space
 */
struct tree_subheader {
    uint64_t ASCII_signature;
    uint64_t root_offset;
    uint64_t first_seq;
    uint64_t second_seq;
    uint64_t cur_id;
    uint64_t pattern_size;
    uint64_t reserved[16];
};

/**
 * Container to store single key
 */
#pragma pack(push, 4)
struct key_header {
    uint32_t size;
    uint32_t type;
};
struct key {
    struct key_header *header;
    char *key_value;
};
#pragma pack(pop)

/**
 * File-header that stores meta-data of file
 * id_sequence - array to map id of vertices on offsets
 */
struct tree_header {
    struct tree_subheader *subheader;
    struct key **pattern;
    uint64_t *id_sequence;
};

/**
 * Header for each tuple with data
 * (in case when we store string in tuple we should use different variables for header)
 */
union tuple_header {
    struct {
        uint64_t parent;
        uint64_t alloc;
    };
    struct {
        uint64_t prev;
        uint64_t next;
    };
};

/**
 * Basic unit of data
 */
struct tuple {
    union tuple_header header;
    uint64_t *data;
};

/**
 * Structure of whole file
 */
struct document_tree {
    struct tree_header header;
    struct tuple *tuples;
};

#endif