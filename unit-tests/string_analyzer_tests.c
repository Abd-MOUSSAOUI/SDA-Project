

#include "string_analyzer_tests.h"

ut_status_t string_analyzer_hello_world_test_case()
{
    const char *example = "Hello World\nThis Might Hello Hello Be The End\nOf The Hello World";
    print_ascii_tree(str_split(example));
    ut_test_case_fulfill();
}

ut_status_t string_analyzer_subject_test_case()
{
    const char *example = "foo qux baz bar.\nfoo grault corge bar.\ncorge foo grault waldo.";

    bst_t *t = str_split(example);
    print_ascii_tree(t);

    ut_assert_equal(t, t, bst_cmp, "Trees are not equal")

    ut_test_case_fulfill();
}

ut_status_t string_analyzer_file_test_case()
{
    
    FILE *hello_world_file = fopen("unit-tests/input/HelloWorld.txt", "r");
    bst_t *t = fstr_split(hello_world_file);

    print_ascii_tree(t);

    ut_test_case_fulfill();
}

ut_status_t string_analyzer_lorem_ipsum_test_case()
{
    
    FILE *hello_world_file = fopen("unit-tests/input/LoremIpsum.txt", "r");
    bst_t *t = fstr_split(hello_world_file);

    print_ascii_tree(t);

    ut_test_case_fulfill();
}

ut_status_t string_analyzer_numbers_test_case()
{
    FILE *numbers_file = fopen("unit-tests/input/Numbers.txt", "r");
    bst_t *t = fstr_split(numbers_file);

    print_ascii_tree(t);

    ut_test_case_fulfill();
}

void run_string_analyzer_test_unit()
{
    ut_test_unit_t unit = ut_test_unit_create("String analyzer unit");

    ut_test_unit_new_case(&unit, "String analyzer hello world test case", string_analyzer_hello_world_test_case);
    ut_test_unit_new_case(&unit, "String analyzer from the subject test case", string_analyzer_subject_test_case);
    ut_test_unit_new_case(&unit, "String analyzer from file test case", string_analyzer_file_test_case);
    ut_test_unit_new_case(&unit, "String analyzer with Lorem Ipsum test case", string_analyzer_lorem_ipsum_test_case);
    ut_test_unit_new_case(&unit, "String analyzer with numbers test case", string_analyzer_numbers_test_case);

    ut_test_unit_run(unit);
}