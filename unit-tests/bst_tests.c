

#include "bst_tests.h"

ut_status_t bst_insertion_test_case()
{
    bst_t *test_bst = bst_insert(NULL, "root", 1);

    bst_insert(test_bst, "world", 2);
    bst_insert(test_bst, "foo", 1);
    bst_insert(test_bst, "hello", 2);

    ut_assert_equal(test_bst->word, "root", strcmp, "root word is not correct");
    ut_assert_equal(test_bst->left_child->word, "foo", strcmp, "left child word is not correct");
    ut_assert_equal(test_bst->right_child->word, "world", strcmp, "right word is not correct");
    ut_assert_equal(test_bst->left_child->right_child->word, "hello", strcmp, "left's right word is not correct");

    ut_test_case_fulfill();
}

void traverse_example(const bst_t *bst, void *arg)
{
    index_t *ind = (index_t *)arg;
    (*ind) += bst->positions->count;
}

ut_status_t bst_traversal_test_case()
{
    bst_t *test_bst = bst_insert(NULL, "root", 1);
    index_t ind = 0;

    bst_insert(test_bst, "world", 2);
    bst_insert(test_bst, "foo", 1);
    bst_insert(test_bst, "hello", 2);

    bst_traverse(test_bst, PREORDER, traverse_example, &ind);

    ut_assert_true(ind == 4, "tree wasn't correctly traversed");
    ut_test_case_fulfill();
}

ut_status_t bst_to_list_test_case()
{
    bst_t *test_bst = bst_insert(NULL, "root", 1);

    bst_insert(test_bst, "world", 2);
    bst_insert(test_bst, "foo", 1);
    bst_insert(test_bst, "hello", 2);

    char **list = bst_to_list(test_bst);
    char *ex[] = {"foo", "hello", "root", "world"};
    index_t index = 0;

    while (*list != NULL)
    {
        ut_assert_equal(*list, ex[index++], strcmp, "%s != %s", *list, *ex);
        list++;
    }

    ut_test_case_fulfill();
}

void run_bst_test_unit()
{
    ut_test_unit_t unit = ut_test_unit_create("Binary search tree tests");

    ut_test_unit_new_case(&unit, "Binary Search Tree insertion test case", bst_insertion_test_case);
    ut_test_unit_new_case(&unit, "Binary Search Tree traversal test case", bst_traversal_test_case);
    ut_test_unit_new_case(&unit, "Binary Search Tree to string test case", bst_to_list_test_case);

    ut_test_unit_run(unit);
}