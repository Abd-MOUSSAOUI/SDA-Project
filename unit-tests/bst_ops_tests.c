

#include "bst_ops_tests.h"



ut_status_t bst_is_balanced_test_case()
{

    char *example = "foo qux baz bar.\nfoo grault corge bar.\ncorge foo grault waldo.";
    bst_t *t = str_split(example);
    ut_assert_true(bst_is_balanced(t));
    #ifdef DEBUG
    printf("• Balanced tree: \n");
    print_ascii_tree(t);
    #endif

    example = "foo grault corge bar.\nfoo qux baz bar.\ncorge foo grault waldo.";
    t = str_split(example);
    ut_assert_false(bst_is_balanced(t));
    #ifdef DEBUG
    printf("• Unbalanced tree: \n");
    print_ascii_tree(t);
    #endif

    bst_destroy(&t);

    ut_test_case_fulfill();
    
}

ut_status_t bst_get_height_test_case()
{
    FILE *hello_world = fopen("unit-tests/input/HelloWorld.txt", "r");
    bst_t *t = fstr_split(hello_world);

    int height = bst_get_height(t);

    #ifdef DEBUG
    printf("• Testing tree: \n");
    print_ascii_tree(t);
    printf("• Height: %d\n", height);
    #endif
    ut_assert_true(height == 6);

    bst_destroy(&t);
    fclose(hello_world);

    ut_test_case_fulfill();
}

ut_status_t bst_rotate_left_test_case()
{

    char *example = "foo qux baz bar.\nfoo grault corge bar.\ncorge foo grault waldo.";
    bst_t *t = str_split(example);
    
    #ifdef DEBUG
    printf("• Before: \n");
    print_ascii_tree(t);
    #endif

    t = bst_rotate_left(t);
    #ifdef DEBUG
    printf("• After: \n");
    print_ascii_tree(t);
    #endif
    ut_assert_equal(t->word, "qux", strcmp);
    ut_assert_equal(t->left_child->word, "foo", strcmp);
    ut_assert_equal(t->right_child->word, "waldo", strcmp);

    bst_destroy(&t);

    ut_test_case_fulfill();
}

ut_status_t bst_balance_factor_test_case()
{

    bst_t *t = str_split("foo qux baz bar.\nfoo grault corge bar.\ncorge foo grault waldo.");
    
    #ifdef DEBUG
    print_ascii_tree(t);
    printf("• Balance: %d\n", bst_balance_factor(t));
    #endif

    ut_assert_true(bst_balance_factor(t) == 0);

    t = str_split("qux foo baz bar.\nfoo grault corge bar.\ncorge foo grault waldo.");

    #ifdef DEBUG
    print_ascii_tree(t);
    printf("• Balance: %d\n", bst_balance_factor(t));
    #endif

    ut_assert_true(bst_balance_factor(t) == 2);

    bst_destroy(&t);

    ut_test_case_fulfill();
}

ut_status_t bst_rotate_right_test_case()
{

    FILE *hello_world = fopen("unit-tests/input/qux.txt", "r");
    bst_t *t = fstr_split(hello_world);
    
    #ifdef DEBUG
    printf("• Before: \n");
    print_ascii_tree(t);
    #endif
    ut_assert_true(bst_balance_factor(t) == 2);

    t = bst_rotate_right(t);

    #ifdef DEBUG
    printf("• After: \n");
    print_ascii_tree(t);
    #endif

    ut_assert_true(bst_is_balanced(t));

    bst_destroy(&t);

    ut_test_case_fulfill();
}

ut_status_t bst_rotate_left_right_test_case()
{

    FILE *hello_world = fopen("unit-tests/input/qux.txt", "r");
    bst_t *t = fstr_split(hello_world);
    
    #ifdef DEBUG
    printf("• Before: \n");
    print_ascii_tree(t);
    #endif

    t = bst_left_right_rotate(t);

    #ifdef DEBUG
    printf("• After: \n");
    print_ascii_tree(t);
    #endif

    bst_destroy(&t);

    ut_test_case_fulfill();
}

ut_status_t bst_rotate_right_left_test_case()
{

    FILE *hello_world = fopen("unit-tests/input/qux.txt", "r");
    bst_t *t = fstr_split(hello_world);
    
    #ifdef DEBUG
    printf("• Before: \n");
    print_ascii_tree(t);
    #endif

    t = bst_right_left_rotate(t); 

    #ifdef DEBUG
    printf("• After: \n");
    print_ascii_tree(t);
    #endif

    bst_destroy(&t);

    ut_test_case_fulfill();
}

ut_status_t bst_balance_test_case()
{

    FILE *hello_world = fopen("unit-tests/input/qux.txt", "r");
    bst_t *t = fstr_split(hello_world);
    
    #ifdef DEBUG
    printf("• Before: \n");
    print_ascii_tree(t);
    #endif

    t = bst_balance(t);

    #ifdef DEBUG
    printf("• After: \n");
    print_ascii_tree(t);
    #endif

    ut_assert_true(bst_is_balanced(t) && t != NULL);

    bst_destroy(&t);

    ut_test_case_fulfill();
}

void run_bst_ops_test_unit()
{
    ut_test_unit_t unit = ut_test_unit_create("Binary search tree operations tests");

    ut_test_unit_new_case(&unit, "Binary Search Tree get height test case", bst_get_height_test_case);
    ut_test_unit_new_case(&unit, "Binary Search Tree is balanced test case", bst_is_balanced_test_case);
    ut_test_unit_new_case(&unit, "Binary Search Tree balance factor test case", bst_balance_factor_test_case);
    ut_test_unit_new_case(&unit, "Binary Search Tree rotate left test case", bst_rotate_left_test_case);
    ut_test_unit_new_case(&unit, "Binary Search Tree rotate right test case", bst_rotate_right_test_case);
    ut_test_unit_new_case(&unit, "Binary Search Tree rotate left right test case", bst_rotate_left_right_test_case);
    ut_test_unit_new_case(&unit, "Binary Search Tree rotate right left test case", bst_rotate_right_left_test_case);
    ut_test_unit_new_case(&unit, "Binary Search Tree balance test case", bst_balance_test_case);

    ut_test_unit_run(unit);
}