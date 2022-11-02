#include "ui/interactive.h"
#include "interface/configuration.h"


int main(int argc, char** argv) {
    char *filename = argv[argc-1];
    return interactive_mode(filename);
}

