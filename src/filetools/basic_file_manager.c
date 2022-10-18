#include "basic_file_manager.h"

enum file_read_status read_from_file(void *buffer, FILE *file) {
    size_t length = fread(buffer, sizeof(buffer), 1, file);
    int code = READ_OK;
    if (length < 1) {
        code = READ_INVALID;
    } else if (sizeof(buffer) < length) {
        code = READ_END_OF_FILE;
    }
    return code;
}

enum file_write_status write_to_file(void *buffer, FILE *file) {
    size_t length = fwrite(buffer, sizeof(buffer), 1, file);
    int code = WRITE_OK;
    if (length < 1) {
        code = WRITE_WRONG_INTEGRITY;
    } else if (sizeof(buffer) < length) {
        code = WRITE_INVALID;
    }
    return code;
}

static enum file_open_status open_file(char *filename, FILE *file, char *open_descriptor){
    FILE *p_file = fopen(filename, "r+");
    int code = OPEN_OK;
    if (p_file==NULL){
        code = OPEN_FAILED;
    } else {
        *file = *p_file;
    }
    return code;
}

enum file_open_status open_exist_file(char *filename, FILE *file, char *open_descriptor){
    return open_file(filename, file, "r+");
}

enum file_open_status open_new_file(char *filename, FILE *file, char *open_descriptor){
    return open_file(filename, file, "w+");
}

void close_file(FILE *file){
    fclose(file);
}