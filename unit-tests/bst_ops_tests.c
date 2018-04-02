

#include "bst_ops_tests.h"

<<<<<<< HEAD
=======
// bool bst_is_balanced(bst_t *t);
// int bst_get_height(bst_t *t);
>>>>>>> 797f8dbcdea10a8c0f787431b764933d9844838c

ut_status_t bst_is_balanced_test_case()
{

    char *example = "foo qux baz bar.\nfoo grault corge bar.\ncorge foo grault waldo.";
    bst_t *t = str_split(example);
    ut_assert_true(bst_is_balanced(t), "Tree is balanced dosen't work correctly");

    example = "foo grault corge bar.\nfoo qux baz bar.\ncorge foo grault waldo.";
    t = str_split(example);
    ut_assert_false(bst_is_balanced(t), "Tree is balanced dosen't work correctly");
    
    ut_test_case_fulfill();
    
}

ut_status_t bst_get_height_test_case()
{
    FILE *lorem_ipsum = fopen("unit-tests/input/LoremIpsum.txt", "r");
    bst_t *lit = fstr_split(lorem_ipsum);
<<<<<<< HEAD

    ut_assert_true(bst_get_height(lit) == 8, "bst height isn't correct");
=======
    print_ascii_tree(lit);
    printf("%d\n", bst_get_height(lit));
    ut_assert_true(bst_get_height(lit) == 11, "bst height don't work");
>>>>>>> 797f8dbcdea10a8c0f787431b764933d9844838c

    ut_test_case_fulfill();
}

void run_bst_ops_test_unit()
{
    ut_test_unit_t unit = ut_test_unit_create("Binary search tree operations tests");

    ut_test_unit_new_case(&unit, "Binary Search Tree is balanced test case", bst_is_balanced_test_case);
    ut_test_unit_new_case(&unit, "Binary Search Tree get height test case", bst_get_height_test_case);

    ut_test_unit_run(unit);
}