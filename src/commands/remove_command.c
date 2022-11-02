#include "remove_command.h"

enum crud_operation_status remove_execute(FILE *file){
    printf("Enter id\n");
    printf("%-20s:", "Id");
    uint64_t  id;
    scanf("%ld", &id);
    remove_tuple(file, id);
}