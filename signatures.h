#include <stdio.h>
#include <inttypes.h>

struct tree_subheader {
    char ASCII_signature[8];
    uint64_t root_offset;
    uint64_t first_seq;
    uint64_t second_seq;
    uint64_t cur_id;
    uint64_t reserved[16];
};

struct pattern {
    uint32_t size;
    char type[4];
    char *key;
};


struct tree_header {
    struct tree_subheader subheader;
    struct pattern *patterns;
    uint64_t *offset;
};

/*
 * Юнионы чтобы в зависимости от типа тапла
 * там лежало либо одно, либо второе
 * но места всегда занимает 16 байт
 */
struct tuple_header {
    union {
        struct {
            uint64_t parent;
            uint64_t alloc;
        } node_header;

        struct {
            uint64_t prev;
            uint64_t next;
        } string_header;

    } inner;
};

struct tuple {
    struct tuple_header header;
    int64_t *data;
};

struct document_tree {
    struct tree_header header;
    struct tuple* tuples;
};
