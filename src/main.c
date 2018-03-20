

#include <stdio.h>
#include <stdlib.h>
#include "ordered_set.h"
#include "bst.h"

int main(int argc, char *argv[])
{

    index_t values[10] = {0, 2, 5, 6, 13, 66, 253, 2445, 12309, 143534};
    index_t values2[5] = {0, 55, 66, 2445, 5123};
    ordered_set_t *set = ordered_set_init(values, 10);
    ordered_set_t *sset = ordered_set_init(values2, 5);

    ordered_set_print(set);
    ordered_set_print(sset);

    ordered_set_t *sets[2] = {set, sset};

    ordered_set_t *inter = ordered_set_intersect(sets, 2);

    ordered_set_print(inter);

    ordered_set_destroy(&set);
    ordered_set_destroy(&sset);
    ordered_set_destroy(&inter);

    return EXIT_SUCCESS;
}