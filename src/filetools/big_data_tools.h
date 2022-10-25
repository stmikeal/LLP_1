#ifndef BIG_DATA_TOOLS_H
#define BIG_DATA_TOOLS_H
#include <stdlib.h>

#include "../interface/configuration.h"
#include "../interface/signatures.h"
#include "../generator/empty_generator.h"
#include "basic_file_manager.h"

/**
 * Получение реального размера кортежа
 * @param pattern_size размер массива шаблона
 * @return размер внутренних данных кортежа
 */
size_t get_real_tuple_size(uint64_t pattern_size);

/**
 * Запись кортежа в файл
 * @param file файл
 * @param tuple кортеж
 * @return статус записи
 */
enum file_write_status write_tuple(FILE *file, struct tuple *tuple);

/**
 * Открытие файла или его создание в случае его отсутствия
 * @param file контейнер для файлового потока
 * @param filename имя файла
 * @return статус открытия
 */
enum file_open_status open_file_anyway(FILE **file, char *filename);

/**
 * Создать файл с пустой структурой
 * @param file файл
 * @param pattern массив строк для шаблона
 * @param types типы полей шаблона
 * @param pattern_size размер массива шаблона
 * @param key_sizes размеры строк шаблона
 * @return статус записи
 */
enum file_write_status init_empty_file(FILE *file, char **pattern, uint32_t *types, size_t pattern_size, size_t *key_sizes);

/**
 * Записать заголовок файла
 * @param file файл
 * @param header заголовок файла
 * @param pattern_size размер массива шаблона
 * @return статус записи
 */
enum file_write_status write_tree_header(FILE *file, struct tree_header *header, size_t pattern_size);

/**
 * Прочитать строчный кортеж
 * @param tuple контейнер для кортежа
 * @param file файл
 * @param tree_header заголовок дерева
 * @return статус чтения
 */
enum file_read_status read_string_tuple(struct tuple **tuple, FILE *file, struct tree_header *tree_header);

/**
 * Прочитать обычный кортеж
 * @param tuple контейнер для кортежа
 * @param file файл
 * @param tree_header заголовок
 * @return статус чтения
 */
enum file_read_status read_basic_tuple(struct tuple **tuple, FILE *file, struct tree_header *tree_header);

/**
 * Прочитать заголовок файла
 * @param header контейнер для заголовка
 * @param file файл
 * @param fpos контейнер для позиции окончания чтения файла
 * @return статус чтения
 */
enum file_read_status read_tree_header(struct tree_header *header, FILE *file, fpos_t *fpos);

#endif
