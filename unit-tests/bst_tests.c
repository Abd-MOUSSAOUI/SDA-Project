

#include "bst_tests.h"

ut_status_t bst_insertion_test_case()
{
    bst_t *test_bst = bst_insert(NULL, "root", 1);

    bst_insert(test_bst, "world", 2);
    bst_insert(test_bst, "foo", 1);
    bst_insert(test_bst, "hello", 2);

    #ifdef DEBUG
    printf("• Testing tree: \n");
    print_ascii_tree(test_bst);
    #endif

    ut_assert_equal(test_bst->word, "root", strcmp);
    ut_assert_equal(test_bst->left_child->word, "foo", strcmp);
    ut_assert_equal(test_bst->right_child->word, "world", strcmp);
    ut_assert_equal(test_bst->left_child->right_child->word, "hello", strcmp);

    bst_destroy(&test_bst);

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

    #ifdef DEBUG
    printf("• Testing tree: \n");
    print_ascii_tree(test_bst);
    #endif

    bst_traverse(test_bst, PREORDER, traverse_example, &ind);

    #ifdef DEBUG
    printf("• Number of nodes returned by the traversal: %lu \n", ind);
    #endif

    ut_assert_true(ind == 4);

    bst_destroy(&test_bst);

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

    #ifdef DEBUG
    printf("• Testing tree: \n");
    print_ascii_tree(test_bst);
    printf("• Returned list of nodes: \n");
    #endif

    while (*list != NULL)
    {
        #ifdef DEBUG
        printf("%s, ", *list);
        #endif
        ut_assert_equal(*(list++), ex[index++], strcmp);
    }
    putchar('\n');

    bst_destroy(&test_bst);

    ut_test_case_fulfill();
}

ut_status_t bst_find_test_case()
{
    char *example = "foo qux baz bar.\nfoo grault corge bar.\ncorge foo grault waldo.";
    bst_t *t = str_split(example);

    #ifdef DEBUG
    printf("• Testing tree: \n");
    print_ascii_tree(t);
    putchar('\n');
    #endif

    ordered_set_t *found = bst_find(t, "foo");

    #ifdef DEBUG
    printf("• Occurences of the word 'foo': \n");
    printf("%s\n", ordered_set_to_string(found));
    putchar('\n');
    #endif

    ordered_set_t *not_found = bst_find(t, "abdou");

    #ifdef DEBUG
    printf("• Occurences of the word 'abdou': \n");
    printf("%s\n", ordered_set_to_string(not_found));
    putchar('\n');
    #endif

    ut_assert_true(ordered_set_is_empty(not_found));
    ut_assert_false(ordered_set_is_empty(found));

    bst_destroy(&t);

    ut_test_case_fulfill();
}

ut_status_t bst_find_cooccurences_test_case()
{
    char *example = "foo qux baz bar.\nfoo grault corge bar.\ncorge foo grault waldo.";
    bst_t *t = str_split(example);

    #ifdef DEBUG
    printf("• Testing tree: \n");
    print_ascii_tree(t);
    putchar('\n');
    #endif

    const char *words[] = {"foo", "grault", "bar", "non-existant"};
    ordered_set_t *coocurences = bst_find_cooccurences(t, words, 4);

    #ifdef DEBUG
    printf("• Returned positions for words 'foo', 'grault', 'bar', 'non-existant':\n %s", 
            ordered_set_to_string(coocurences));
    #endif

    bst_destroy(&t);
    ordered_set_destroy(&coocurences);

    ut_test_case_fulfill();
}

ut_status_t get_number_string_test_case() 
{

    FILE *hello_world = fopen("unit-tests/input/HelloWorld.txt", "r");
    bst_t *t = fstr_split(hello_world);

    #ifdef DEBUG
    printf("• Testing tree: \n");
    print_ascii_tree(t);
    putchar('\n');
    #endif

    ut_assert_true(bst_get_number_string(t) == 8);

    #ifdef DEBUG
    printf("• number of words without repetition is: %zu\n", bst_get_number_string(t));
    putchar('\n');
    #endif

    bst_destroy(&t);
    fclose(hello_world);

    ut_test_case_fulfill();
}

ut_status_t get_total_number_string_test_case() 
{
    FILE *hello_world = fopen("unit-tests/input/HelloWorld.txt", "r");
    bst_t *t = fstr_split(hello_world);

    #ifdef DEBUG
    printf("• Testing tree: \n");
    print_ascii_tree(t);
    putchar('\n');
    #endif

    ut_assert_true(bst_get_total_number_string(t) == 13);

    #ifdef DEBUG
    printf("• number of words is: %zu\n", bst_get_total_number_string(t));
    putchar('\n');
    #endif

    bst_destroy(&t);
    fclose(hello_world);

    ut_test_case_fulfill();
}

ut_status_t bst_get_average_depth_test_case()
{
    const char *example = "foo qux baz bar.\nfoo grault corge bar.\ncorge foo grault waldo.";
    bst_t *t = str_split(example);

    float average_depth = bst_get_average_depth(t);

    #ifdef DEBUG
    printf("• Testing tree: \n");
    print_ascii_tree(t);
    putchar('\n');
    printf("• average depth: %f\n", average_depth);
    #endif

    ut_assert_true(average_depth > 1.624 && average_depth < 1.626);

    bst_destroy(&t);

    ut_test_case_fulfill();
}

void run_bst_test_unit()
{
    ut_test_unit_t unit = ut_test_unit_create("Binary search tree tests");

    ut_test_unit_new_case(&unit, "Binary Search Tree get number string test case", get_number_string_test_case);
    ut_test_unit_new_case(&unit, "Binary Search Tree get total number string test case", get_total_number_string_test_case);
    ut_test_unit_new_case(&unit, "Binary Search Tree insertion test case", bst_insertion_test_case);
    ut_test_unit_new_case(&unit, "Binary Search Tree traversal test case", bst_traversal_test_case);
    ut_test_unit_new_case(&unit, "Binary Search Tree to string test case", bst_to_list_test_case);
    ut_test_unit_new_case(&unit, "Binary Search Tree find test case", bst_find_test_case);
    ut_test_unit_new_case(&unit, "Binary Search Tree find occurences test case", bst_find_cooccurences_test_case);
    ut_test_unit_new_case(&unit, "Binary Search Tree get average depth test case", bst_get_average_depth_test_case);

    ut_test_unit_run(unit);
}