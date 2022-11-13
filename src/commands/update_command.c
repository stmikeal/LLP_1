#include "update_command.h"

enum crud_operation_status update_execute(FILE *file){
    printf("Enter id\n");
    printf("%-20s:", "Id");
    uint64_t  id;
    scanf("%ld", &id);
    printf("Choose field\n");
    struct tree_header *header = malloc(sizeof(struct tree_header));
    read_tree_header_np(header, file);
    for (uint64_t iter = 0; iter < header->subheader->pattern_size; iter++) {
        printf("%ld. %s\n", iter, header->pattern[iter]->key_value);
    }
    uint64_t  number;
    printf("Field: ");
    scanf("%ld", &number);
    printf("Enter new value:\n");
    printf("Value: ");
    uint64_t value;
    char s[BUFFER_FIELD_SIZE];
    switch (header->pattern[number]->header->type) {
        case INTEGER_TYPE: scanf("%ld", &value);; break;
        case BOOLEAN_TYPE: scanf("%ld", &value);; break;
        case FLOAT_TYPE: scanf("%lf", (double *) &value);; break;
        default: scanf("%s", s); value = (uint64_t) s; break;
    }
    enum crud_operation_status status = update_tuple(file, number, &value, id);
    if (status == CRUD_OK) printf("TUPLE %3ld UPDATED\n", header->subheader->cur_id);
    else printf("NOT UPDATED\n");
    free_tree_header(header);
    return status;
}