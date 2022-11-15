#ifndef TOOLS_H
#define TOOLS_H
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include "../configuration.h"

int32_t read_command_line(char *buffer);
uint64_t get_hash(char *string);
void init_file(FILE *file);

#endif
