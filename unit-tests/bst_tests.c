

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

ut_status_t bst_find_test_case()
{
    char *example = "foo qux baz bar.\nfoo grault corge bar.\ncorge foo grault waldo.";
    bst_t *t = str_split(example);

    #ifdef DEBUG
    printf("Testing tree: \n");
    print_ascii_tree(t);
    putchar('\n');
    #endif

    char *found_word = bst_find(t, "foo");

    #ifdef DEBUG
    printf("Occurences of the word 'foo': \n");
    printf("%s\n", found_word != NULL ? found_word : "NULL");
    putchar('\n');
    #endif

    char *not_found_word = bst_find(t, "abdou");

    #ifdef DEBUG
    printf("Occurences of the word 'abdou': \n");
    printf("%s\n", not_found_word != NULL ? not_found_word : "NULL");
    putchar('\n');
    #endif

    ut_assert_not_null(found_word, "foo can't be found");
    ut_assert_null(not_found_word, "abdou shouldn't exist");

    ut_test_case_fulfill();
}

ut_status_t bst_find_occurences_test_case()
{
    char *example = "foo qux baz bar.\nfoo grault corge bar.\ncorge foo grault waldo.";
    bst_t *t = str_split(example);

    #ifdef DEBUG
    printf("Testing tree: \n");
    print_ascii_tree(t);
    putchar('\n');
    #endif

    const char *words[] = {"foo", "grault", "bar", "non-existant"};
    char **occurences = bst_find_occurence_indexes(t, words, 4);

    #ifdef DEBUG
    printf("foo: %s\ngrault: %s\nbar: %s\nnon-exsitant: NULL", occurences[0], 
                                occurences[1], occurences[2]);
    #endif

    ut_assert_equal(occurences[0], "1|2|3", strcmp, "");
    ut_assert_equal(occurences[1], "2|3", strcmp, "");
    ut_assert_equal(occurences[2], "1|2", strcmp, "");
    ut_assert_null(occurences[3], "");

    ut_test_case_fulfill();
}

ut_status_t get_number_string_test_case() 
{

    FILE *hello_world = fopen("unit-tests/input/HelloWorld.txt", "r");
    bst_t *t = fstr_split(hello_world);

    #ifdef DEBUG
    printf("Testing tree: \n");
    print_ascii_tree(t);
    putchar('\n');
    #endif

    ut_assert_true(bst_get_number_string(t) == 8, "");

    #ifdef DEBUG
    printf("number of words without repetition is: %zu\n", bst_get_number_string(t));
    putchar('\n');
    #endif

    ut_test_case_fulfill();
}

ut_status_t get_total_number_string_test_case() 
{
    FILE *hello_world = fopen("unit-tests/input/HelloWorld.txt", "r");
    bst_t *t = fstr_split(hello_world);

    #ifdef DEBUG
    printf("Testing tree: \n");
    print_ascii_tree(t);
    putchar('\n');
    #endif

    ut_assert_true(bst_get_total_number_string(t) == 13, "");

    #ifdef DEBUG
    printf("number of words is: %zu\n", bst_get_total_number_string(t));
    putchar('\n');
    #endif

    ut_test_case_fulfill();
}

ut_status_t bst_get_average_depth_test_case()
{
    char *example = "foo qux baz bar.\nfoo grault corge bar.\ncorge foo grault waldo.";
    bst_t *t = str_split(example);

    #ifdef DEBUG
    printf("Testing tree: \n");
    print_ascii_tree(t);
    putchar('\n');
    #endif

    printf("average depth: %f\n", bst_get_average_depth(t));

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
    ut_test_unit_new_case(&unit, "Binary Search Tree find occurences test case", bst_find_occurences_test_case);
    ut_test_unit_new_case(&unit, "Binary Search Tree find occurences test case", bst_get_average_depth_test_case);

    ut_test_unit_run(unit);
}