#ifndef BASIC_CRUD_H
#define BASIC_CRUD_H
#include "../filetools/big_data_tools.h"
#include <unistd.h>
#include <string.h>

/**
 * Удаляет последний кортеж их файла
 * @param file файл
 * @param full_tuple_size размер одного кортежа вместе с заголовком
 * @return статус операции
 */
enum crud_operation_status delete_last_tuple(FILE *file, size_t full_tuple_size);

/**
 * Вставляет на позицию кортеж
 * @param file файл
 * @param pos_from откуда скопировать
 * @param pos_to куда скопировать
 * @return статус операции
 */
enum crud_operation_status swap_tuple_to(FILE *file, uint64_t pos_from, uint64_t pos_to, size_t tuple_size);

/**
 * Вставляет в конец файла новый кортеж
 * @param file файл
 * @param tuple кортеж
 * @param full_tuple_size размер одного кортежа вместе с заголовком
 * @return статус операции
 */
enum crud_operation_status insert_string_tuple(FILE *file, char *string, size_t tuple_size, uint64_t par_pos, uint64_t *str_pos);
enum crud_operation_status insert_new_tuple(FILE *file, struct tuple *tuple, size_t full_tuple_size, uint64_t *tuple_pos);
void get_types(FILE *file, uint32_t **types, size_t *size);
enum crud_operation_status change_parameter(FILE *file, enum tree_subheader_parameter parameter, uint64_t value);
enum crud_operation_status append_to_id_array(FILE *file, uint64_t offset);
uint64_t remove_from_id_array(FILE *file, uint64_t id);
enum crud_operation_status id_to_offset(FILE *file, uint64_t id, uint64_t* offset);
enum crud_operation_status offset_to_id(FILE *file, uint64_t* id, uint64_t offset);
enum crud_operation_status change_string_tuple(FILE *file, uint64_t offset, char *new_string,  uint64_t size);
struct uint64_list *get_childs_by_id(FILE *file, uint64_t id);
void free_uint64_list(struct uint64_list *result);
enum crud_operation_status swap_with_last(FILE *file, uint64_t offset, uint64_t size);
enum crud_operation_status remove_string_from_file(FILE* file, uint64_t offset, uint64_t size);
/**
 * Статус операции
 */
enum crud_operation_status {
    CRUD_OK = 0,
    CRUD_END_OF_FILE,
    CRUD_INVALID
};

struct uint64_list{
    uint64_t value;
    struct uint64_list *next;
};

#endif
