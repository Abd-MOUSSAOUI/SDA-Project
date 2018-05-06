

#include "string_analyzer_tests.h"

ut_status_t string_analyzer_hello_world_test_case()
{
    const char *example = "Hello World\nThis Might Hello Hello Be The End";
    bst_t *t = str_split(example);

    #ifdef DEBUG
    printf("Testing tree: \n");
    print_ascii_tree(t);
    #endif

    ut_assert_equal(t->word, "hello", strcmp);
    ut_assert_equal(t->right_child->word, "world", strcmp);
    ut_assert_equal(t->left_child->word, "be", strcmp);
    ut_assert_true(ordered_set_get_count(t->positions) == 2);

    bst_destroy(&t);

    ut_test_case_fulfill();
}

ut_status_t string_analyzer_subject_test_case()
{
    const char *example = "foo qux baz bar.\nfoo grault corge bar.\ncorge foo grault waldo.";

    bst_t *t = str_split(example);

    #ifdef DEBUG
    printf("Testing tree: \n");
    print_ascii_tree(t);
    #endif

    ut_assert_equal(t->word, "foo", strcmp);
    ut_assert_equal(t->right_child->word, "qux", strcmp);
    ut_assert_equal(t->left_child->word, "baz", strcmp);
    ut_assert_true(bst_is_balanced(t));

    bst_destroy(&t);

    ut_test_case_fulfill();
}

ut_status_t string_analyzer_file_test_case()
{
    
    FILE *hello_world_file = fopen("unit-tests/input/HelloWorld.txt", "r");
    bst_t *t = fstr_split(hello_world_file);

    #ifdef DEBUG
    printf("Testing tree: \n");
    print_ascii_tree(t);
    #endif

    ut_assert_equal(t->word, "hello", strcmp);
    ut_assert_equal(t->right_child->word, "world", strcmp);
    ut_assert_equal(t->left_child->word, "be", strcmp);
    ut_assert_true(ordered_set_get_count(t->left_child->positions) == 1);
    ut_assert_true(ordered_set_get_count(t->right_child->positions) == 2);
    ut_assert_true(ordered_set_get_count(t->positions) == 4);

    bst_destroy(&t);

    ut_test_case_fulfill();
}

ut_status_t string_analyzer_lorem_ipsum_test_case()
{
    
    FILE *hello_world_file = fopen("unit-tests/input/LoremIpsum.txt", "r");
    bst_t *t = fstr_split(hello_world_file);

    #ifdef DEBUG
    printf("Testing tree: \n");
    print_ascii_tree(t);
    #endif

    ut_assert_equal(t->word, "usu", strcmp);
    ut_assert_equal(t->right_child->word, "ut", strcmp);
    ut_assert_equal(t->left_child->word, "ea", strcmp);

    bst_destroy(&t);

    ut_test_case_fulfill();
}

ut_status_t string_analyzer_numbers_test_case()
{
    FILE *numbers_file = fopen("unit-tests/input/Numbers.txt", "r");
    bst_t *t = fstr_split(numbers_file);

    #ifdef DEBUG
    printf("Testing tree: \n");
    print_ascii_tree(t);
    #endif

    ut_assert_equal(t->word, "123", strcmp);
    ut_assert_equal(t->right_child->word, "13", strcmp);
    ut_assert_equal(t->left_child->word, "1", strcmp);

    bst_destroy(&t);

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