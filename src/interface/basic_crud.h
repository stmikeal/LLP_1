#ifndef BASIC_CRUD_H
#define BASIC_CRUD_H
#include "../filetools/big_data_tools.h"
#include <unistd.h>
enum crud_operation_status {
    CRUD_OK = 0,
    CRUD_END_OF_FILE,
    CRUD_INVALID
};

#endif
