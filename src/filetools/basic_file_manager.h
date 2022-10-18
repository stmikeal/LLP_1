#ifndef BASIC_FILE_MANAGER_H
#define BASIC_FILE_MANAGER_H

#include <stdio.h>
#include <inttypes.h>

enum file_read_status {
    READ_OK = 0,
    READ_END_OF_FILE,
    READ_INVALID
};

enum file_write_status {
    WRITE_OK = 0,
    WRITE_WRONG_INTEGRITY,
    WRITE_INVALID
};

enum file_open_status {
    OPEN_OK = 0,
    OPEN_FAILED
};

#endif
