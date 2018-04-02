

#include "bst_ops_tests.h"

/*
bool bst_is_balanced(bst_t *t);
long bst_get_height(bst_t *t);
*/
ut_status_t bst_is_balanced_test_case()
{

    FILE *lorem_ipsum = fopen("unit-tests/input/LoremIpsum.txt", "r");

    bst_t *lit = fstr_split(lorem_ipsum);

    printf("%ld\n", bst_get_height(lit));
    ut_assert_true(bst_get_height(lit) == 8, "bst height don't work");

    ut_test_case_fulfill();
}

void run_bst_ops_test_unit()
{
    ut_test_unit_t unit = ut_test_unit_create("Binary search tree operations tests");

    ut_test_unit_new_case(&unit, "Binary Search Tree is balanced test case", bst_is_balanced_test_case);

    ut_test_unit_run(unit);
}