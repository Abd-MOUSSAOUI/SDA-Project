

#include <stdio.h>
#include <stdlib.h>
#include "ordered_set.h"
#include "bst.h"

int main(int argc, char *argv[])
{

    index_t values[10] = {0, 2, 5, 6, 13, 66, 253, 2445, 12309, 143534};
    ordered_set_t *set = ordered_set_init(values, 10);

    ordered_set_print(set);

    printf("This set contains 13 ? %s\n", ordered_set_contains(set, 13) ? "YES" : "NO");

    ordered_set_destroy(&set);

    return EXIT_SUCCESS;
}