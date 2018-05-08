

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

void print_node_balance(const bst_t *node, void *arg)
{
    printf("%s : %d\n", node->word, bst_balance_factor((bst_t *)node));
}

ut_status_t balance_factor_test_case()
{

    int balance_factor = bst_balance_factor(tree);

    #ifdef DEBUG
    printf("• This tree is balanced? %s\n", bst_is_balanced(tree) ? "YES" : "HELL NO!");
    bst_traverse(tree, INORDER, print_node_balance, NULL);
    #endif  

    ut_test_case_fulfill();
}

ut_status_t balance_test_case()
{

    int balance_factor = bst_balance_factor(tree);

    tree = bst_balance(tree);

    printf("• After:\n");
    print_ascii_tree(tree);

    ut_assert_true(bst_is_balanced(tree));

    ut_test_case_fulfill();
}

void run_problem_test_unit()
{

    ut_test_unit_t unit = ut_test_unit_create("PROBLEM TESTS");

    ut_test_unit_new_case(&unit, "ANALYZE TEST", analyze_test_case);
    ut_test_unit_new_case(&unit, "BALANCE FACTOR TEST", balance_factor_test_case);
    ut_test_unit_new_case(&unit, "BALANCING THE TREE TEST", balance_test_case);
    ut_test_unit_new_case(&unit, "BALANCE FACTOR TEST", balance_factor_test_case);

    ut_test_unit_run(unit);

    bst_destroy(&tree);

}