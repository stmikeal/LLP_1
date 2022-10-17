#include "signatures.h"
#include <stdint.h>
#include <malloc.h>

/*
 * Чтобы динамически размер key'я задать
 */
struct pattern pattern_init(uint32_t size, const char type[4], const char *key) {
    struct pattern ptrn = {.size = size, .type = type};
    ptrn.key = malloc(size);
    *(ptrn.key) = *key;
    return ptrn;
}