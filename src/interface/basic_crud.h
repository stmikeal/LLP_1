#ifndef BASIC_CRUD_H
#define BASIC_CRUD_H
#include "../filetools/big_data_tools.h"
#include <unistd.h>

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
 * @param tuple_to_swap кортеж
 * @param pos позиция вставки
 * @return статус операции
 */
enum crud_operation_status swap_tuple_to(FILE *file, struct tuple *tuple_to_swap, uint64_t pos);

/**
 * Вставляет в конец файла новый кортеж
 * @param file файл
 * @param tuple кортеж
 * @param full_tuple_size размер одного кортежа вместе с заголовком
 * @return статус операции
 */
enum crud_operation_status insert_new_tuple(FILE *file, struct tuple *tuple, size_t full_tuple_size);

/**
 * Статус операции
 */
enum crud_operation_status {
    CRUD_OK = 0,
    CRUD_END_OF_FILE,
    CRUD_INVALID
};

#endif
