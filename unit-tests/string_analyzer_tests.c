

#include "string_analyzer_tests.h"

ut_status_t string_analyzer_hello_world_test_case()
{
    const char *example = "Hello World\nThis Might Hello Hello Be The End\nOf The Hello World";
    print_ascii_tree(str_split(example));
    ut_test_case_fulfill();
}

ut_status_t string_analyzer_subject_test_case()
{
    const char *example = "fôo qux baz bar.\nfôo grault corge bar.\ncorge fôo grault waldo.";

    bst_t *t = str_split(example);
    print_ascii_tree(t);

    ut_assert_equal(t, t, bst_cmp, "Trees are not equal")

    ut_test_case_fulfill();
}

ut_status_t string_analyzer_file_test_case()
{
    
    FILE *hello_world_file = fopen("unit-tests/HelloWorld.txt", "r");
    bst_t *t = fstr_split(hello_world_file);

    print_ascii_tree(t);

    ut_test_case_fulfill();
}

ut_status_t string_analyzer_lorem_ipsum_test_case()
{
    
    FILE *hello_world_file = fopen("unit-tests/LoremIpsum.txt", "r");
    bst_t *t = fstr_split(hello_world_file);

    print_ascii_tree(t);

    ut_test_case_fulfill();
}

void run_string_analyzer_test_unit()
{
    ut_test_unit_t unit = ut_test_unit_create("String analyzer unit");

    ut_test_unit_new_case(&unit, "String analyzer hello world test case", string_analyzer_hello_world_test_case);
    ut_test_unit_new_case(&unit, "String analyzer example from the subject", string_analyzer_subject_test_case);
    ut_test_unit_new_case(&unit, "String analyzer example from file", string_analyzer_file_test_case);
    ut_test_unit_new_case(&unit, "String analyzer example from Lorem Ipsum", string_analyzer_lorem_ipsum_test_case);

    ut_test_unit_run(unit);
}