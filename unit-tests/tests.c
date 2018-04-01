

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unit_test.h"
#include "ordered_set_tests.h"
#include "string_analyzer_tests.h"

int main(int argc, char *argv[])
{

    run_string_analyzer_test_unit();
    run_ordered_set_test_unit();

    return EXIT_SUCCESS;
}