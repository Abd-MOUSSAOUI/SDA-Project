

#include "bst_tests.h"

ut_status_t insertion_test_case()
{
    bst_t *test_bst = bst_create("root", ordered_set_create());

    test_bst->left_child = bst_create("left", ordered_set_create());
    test_bst->right_child = bst_create("right", ordered_set_create());

    bst_insert(test_bst, "foo", 1);

    print_ascii_tree(test_bst);

    ut_test_case_fulfill();
}

void run_bst_test_unit()
{
    ut_test_unit_t unit = ut_test_unit_create("Binary search tree tests");

    ut_test_unit_new_case(&unit, "Insertion test", insertion_test_case);

    ut_test_unit_run(unit);
}