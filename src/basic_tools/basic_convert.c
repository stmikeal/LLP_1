#include "basic_convert.h"

size_t get_real_tuple_size(uint64_t pattern_size) {
    return pattern_size * SINGLE_TUPLE_VALUE_SIZE < MINIMAL_TUPLE_SIZE
           ? MINIMAL_TUPLE_SIZE
           : pattern_size * SINGLE_TUPLE_VALUE_SIZE;
}

size_t get_real_id_array_size(uint64_t pattern_size, uint64_t cur_id){
    size_t real_tuple_size = get_real_tuple_size(pattern_size);
    if (cur_id == 0) cur_id++;
    return 50000;
}

size_t get_real_string_size(size_t len) {
    return (len/FILE_GRANULARITY + (len % FILE_GRANULARITY ? 1: 0)) * FILE_GRANULARITY;
}