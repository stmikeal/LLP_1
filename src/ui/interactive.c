#include "interactive.h"
void print_help();

uint8_t loop = NULL_VALUE;

enum commands_desc{
    ADD_COMMAND = 0,
    REMOVE_COMMAND,
    UPDATE_COMMAND,
    FIND_COMMAND,
    HELP_COMMAND,
    EXIT_COMMAND,
    WRONG_COMMAND
};

uint64_t commands_hash[6];

uint64_t get_hash(char *string) {
    uint64_t value = INITHASH;
    while(*string) value = (value * AHASH) ^ (*(string++) * BHASH);
    return value % CHASH;
}

void init_params() {
    commands_hash[0] = get_hash("add");
    commands_hash[1] = get_hash("remove");
    commands_hash[2] = get_hash("update");
    commands_hash[3] = get_hash("find");
    commands_hash[4] = get_hash("help");
    commands_hash[5] = get_hash("exit");
}

enum commands_desc parse_command(char *command) {
    uint64_t hash = get_hash(command);
    for (size_t iter = 0; iter < 6; iter++){
        if (commands_hash[iter] == hash) return iter;
    }
    return WRONG_COMMAND;
}

static void print_need_help() {
    printf("Type 'help' for available commands info.\n");
}

static void print_program_header() {
    printf("Welcome to bigdata program!\n");
    printf("File opened successfully!\n");
    print_need_help();
}

static void print_wrong_command() {
    printf("You typed wrong command\n");
    print_need_help();
}

static void exit_program() {
    printf("Goodbye!\n");
    loop++;
}

int32_t interactive_mode(char *filename) {
    FILE *file;
    enum file_open_status open_status = open_file_anyway(&file, filename);
    if (open_status) return open_status;

    init_params();
    print_program_header();

    char command[BUFFER_COMMAND_SIZE];
    while(!loop) {
        read_command_line(command);
        switch (parse_command(command)) {
            case ADD_COMMAND: add_execute(file); break;
            case REMOVE_COMMAND: remove_execute(file); break;
            case UPDATE_COMMAND: update_execute(file); break;
            case FIND_COMMAND: find_execute(file); break;
            case HELP_COMMAND: print_help();break;
            case EXIT_COMMAND: exit_program(); break;
            default: print_wrong_command(); break;
        }
    }


    close_file(file);
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