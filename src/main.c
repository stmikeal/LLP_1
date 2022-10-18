#include <stdio.h>
#include "interface/signatures.h"

int main() {
    struct tree_subheader tree = {.ASCII_signature=12, .cur_id=32};
    printf("%" PRIu64 "\n", tree.ASCII_signature);
    return 0;
}

