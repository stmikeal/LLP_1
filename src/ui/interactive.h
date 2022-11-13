#ifndef INTERACTIVE_H
#define INTERACTIVE_H

#include "../interface/crud_interface.h"
#include <string.h>
#include <regex.h>
#include "console_tools.h"
#include "../commands/add_command.h"
#include "../commands/find_command.h"
#include "../commands/remove_command.h"
#include "../commands/update_command.h"

int32_t interactive_mode(char *filename);
int32_t generator_mode(char *filename, char *data_filename);

#endif
