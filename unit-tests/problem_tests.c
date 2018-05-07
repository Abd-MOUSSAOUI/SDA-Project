

#include "problem_tests.h"

bst_t *tree;

ut_status_t analyze_test_case()
{

    FILE *experimentation_file = fopen("unit-tests/input/CMI-HPC.txt", "r");
    tree = fstr_split(experimentation_file);

    #ifdef DEBUG
    printf("• Experimentation tree: \n");
    print_ascii_tree(tree);
    #endif

    ut_assert_equal(tree->word, "le", strcmp);
    ut_assert_equal(tree->left_child->word, "cmi", strcmp);
    ut_assert_equal(tree->left_child->left_child->word, "besoin", strcmp);
    ut_assert_equal(tree->left_child->right_child->word, "cursus", strcmp);
    ut_assert_equal(tree->right_child->word, "master", strcmp);
    ut_assert_equal(tree->right_child->right_child->word, "réseau", strcmp);

    ut_test_case_fulfill();
}

ut_status_t balance_factor_test_case()
{

    int balance_factor = bst_balance_factor(tree);

    #ifdef DEBUG
    printf("Root's balance factor: %d\n", balance_factor);
    printf("Left child's balance factor: %d\n", bst_balance_factor(tree->left_child));
    printf("Right child's balance factor: %d\n", bst_balance_factor(tree->right_child));
    #endif  

    ut_assert_true(balance_factor == balance_factor);

    ut_test_case_fulfill();
}

void run_problem_test_unit()
{

    ut_test_unit_t unit = ut_test_unit_create("PROBLEM TESTS");

    ut_test_unit_new_case(&unit, "ANALYZE TEST", analyze_test_case);
    ut_test_unit_new_case(&unit, "BALANCE FACTOR TEST", balance_factor_test_case);

    ut_test_unit_run(unit);

    bst_destroy(&tree);

}