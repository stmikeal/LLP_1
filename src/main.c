#include "ui/interactive.h"
#include "test.h"

int main(int argc, char** argv) {
    struct file_config *config = new_file_config();
    if (argc == 4) {
        config->filename = argv[argc-1];
        config->generator_filename = argv[argc-2];
        config->generator_flag = !NULL_VALUE;
    } else if (argc == 2){
        if (argv[1][0]=='-' && argv[1][1]=='t' && argv[1][2]==0){
            return run_all_test();
        }
        config->filename = argv[argc-1];
    } else {
        printf("Неправильные аргументы программы.\n");
        printf("main [flags] <output filename>\n");
        printf("[flags]\n");
        printf("-g | fill file with generator data, have to add <generator filename>.");
    }
    int code = interactive_mode(config);
    free(config);
    return code;
}

