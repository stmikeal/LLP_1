#include "ui/interactive.h"
#include "interface/configuration.h"


int main(int argc, char** argv) {
    char *filename = argv[argc-1];
    if (argc > 2) {
        return generator_mode(filename, argv[argc-2]);
    } else {
        return interactive_mode(filename);
    }

}

