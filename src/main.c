#include "ui/interactive.h"
#include "interface/basic_crud.h"

int main(int argc, char** argv) {
    FILE *file;
    open_file_anyway(&file, "simple.txt");
    char *par1 = "Code";
    char *par2 = "Name";
    char **pattern = malloc(sizeof(char *) * 2);
    pattern[0] = par1;
    pattern[1] = par2;
    size_t pattern_size = 2;
    size_t *sizes = malloc(sizeof (size_t) * 2);
    sizes[0] = 5;
    sizes[1] = 8;
    uint32_t *types = malloc(sizeof (uint32_t) * 2);
    types[0] = 1;
    types[1] = 3;
    init_empty_file(file, pattern, types, pattern_size, sizes);
    print_tree_header_from_file(file);
    /*int flag = 0;
    char* filename;
    if (argc > 3){
        printf("Too many args!");
        return 0;
    }
    for (size_t i = 0; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (flag > 0) {
                printf("Too many flags!");
                return 0;
            } else {
                flag = argv[i][1];
            }
        } else {
            filename = argv[i];
        }
    }
    if (flag == 'i'){
        interactive_mode(filename);
    }*/
    return 0;
}

