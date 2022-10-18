#include "../filetools/basic_file_manager.h"
#include <string.h>

void print_help();

void interactive_mode(char *filename) {
    FILE *f = NULL;
    if (open_exist_file(filename, &f) == OPEN_FAILED) {
        printf("File doesn't exist, should we create it? (Y/n): ");
        char str[1];
        int res = scanf("%s", str);
        while (strcmp(str, "Y") != 0) {
            if (strcmp(str, "n") == 0 || res == EOF) return;
            printf("Incorrect input (Y/n): ");
            res = scanf("%s", str);
        }
        open_new_file(filename, &f);
    }

    printf("File opened successfully!\n");
    printf("Type 'help' for available commands info.\n");


    char input_str[100];
    scanf("%s", input_str);
    while (strcmp(input_str, "exit") != 0) {
        char *token = strtok(input_str, " ");
        while (token != NULL) {
            if (strcmp(token, "help") == 0) print_help();

            else if (strcmp(token, "add") == 0) printf("не торопи события сынок\n");

            else if (strcmp(token, "update") == 0) printf("не торопи события сынок\n");

            else if (strcmp(token, "delete") == 0) printf("не торопи события сынок\n");

            else printf("Unknown command, try using 'help'");
            token = strtok(NULL, " ");
        }
        scanf("%s", input_str);
    }
    close_file(f);
}

void print_help() {
    printf("add <parent_id> <key1>=<value1> <key2>=<value2> ...\n");
    printf("Adds the specified node to tree. Given arguments must match the full pattern.\n\n");
    printf("update <node_id> <key1>=<upd_value1> <key2>=<upd_value2> ...\n");
    printf("Updates some (one or more) fields of specified node.\n\n");
    printf("delete <node_id>\n");
    printf("Deletes specified node with all descendants.\n\n");
    printf("exit\n");
    printf("Exit the program.\n\n");

}