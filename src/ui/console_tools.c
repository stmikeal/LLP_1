#include "console_tools.h"
#include <stdio.h>

const char *command_hint = ">>> ";

int32_t read_command_line(char *buffer) {
    printf("%s", command_hint);
    scanf("%s", buffer);
}