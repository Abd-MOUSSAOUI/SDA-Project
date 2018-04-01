

#include "string_analyzer_tests.h"

ut_status_t build_bst_test_case()
{
    const char *example = "Hello World\nThis Might Hello Hello Be The End\nOf The Hello World";

    bst_t *built_tree = str_split(example, ' ');

    printf("%s\n", ordered_set_to_string(built_tree->positions));

    print_ascii_tree(built_tree);

    ut_test_case_fulfill();
}

void run_string_analyzer_test_unit()
{
    ut_test_unit_t unit = ut_test_unit_create("String analyzer unit");

    ut_test_unit_new_case(&unit, "Build tree from string", build_bst_test_case);

    ut_test_unit_run(unit);
}