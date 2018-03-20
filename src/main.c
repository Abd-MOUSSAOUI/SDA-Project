

#include <stdio.h>
#include <stdlib.h>
#include "ordered_set.h"
#include "bst.h"

int main(int argc, char *argv[])
{
    index_t pos[4] = {0, 1, 3};
    ordered_set_t *set = ordered_set_init(pos, 3);
    ordered_set_print(set);

    bst_t *test = bst_create("Hello World", set, BST_CREATE_PTR);

    bst_print(test);

    bst_destroy(&test, BST_DESTROY_ALL);

    return EXIT_SUCCESS;
}