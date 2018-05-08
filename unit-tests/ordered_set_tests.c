

#include "ordered_set_tests.h"


ut_status_t ordered_set_initialization_test_case()
{
    index_t test_values[11] = {0, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100};
    ordered_set_t *test_set = ordered_set_init(test_values, 11);
    index_t index;

    #ifdef DEBUG
    printf("Ordered set of the first 11 integer squares:\n");
    ordered_set_print(test_set);
    #endif

    for (index = 0; index < 11; index++)
        ut_assert_equal(test_set->values[index], index * index, index_cmp);
    
    ordered_set_destroy(&test_set);
    
    ut_test_case_fulfill();
}

ut_status_t ordered_set_insertion_test_case()
{
    index_t test_values[10] = {0, 1, 4, 9, 25, 36, 49, 64, 81, 100};
    ordered_set_t *test_set = ordered_set_init(test_values, 10);

    #ifdef DEBUG
    printf("Before insertion of `16`: \n");
    ordered_set_print(test_set);
    #endif

    ordered_set_insert(test_set, 16);

    #ifdef DEBUG
    printf("After insertion: \n");
    ordered_set_print(test_set);
    #endif

    index_t post_test_values[11] = {0, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100};
    ordered_set_t *post_test_set = ordered_set_init(post_test_values, 11);
    ut_assert_equal(test_set, post_test_set, ordered_set_cmp);

    ordered_set_destroy(&test_set);
    ordered_set_destroy(&post_test_set);

    ut_test_case_fulfill();
}

ut_status_t ordered_set_contains_test_case()
{

    index_t test_values[10] = {0, 1, 4, 9, 25, 36, 49, 64, 81, 100};
    ordered_set_t *test_set = ordered_set_init(test_values, 10);

    #ifdef DEBUG
    printf("• Testing set:\n");
    ordered_set_print(test_set);
    #endif

    index_t ind;
    for (ind = 1; ind < 128; ind *= 8)
        printf("• Does it contain %lu? %s\n", ind, ordered_set_contains(test_set, ind) ? "YES" : "NO");

    ut_assert_true(ordered_set_contains(test_set, 9));
    ut_assert_true(ordered_set_contains(test_set, 25));
    ut_assert_true(ordered_set_contains(test_set, 81));
    ut_assert_true(ordered_set_contains(test_set, 100));

    ordered_set_destroy(&test_set);

    ut_test_case_fulfill();
}

ut_status_t ordered_set_intersect_test_case()
{

    index_t lhsvals[10] = {0, 1, 4, 9, 25, 36, 49, 64, 81, 100};
    ordered_set_t *lhsset = ordered_set_init(lhsvals, 10);

    index_t rhsvals[10] = {0, 1, 4, 9, 16, 64, 100, 121, 144, 269};
    ordered_set_t *rhsset = ordered_set_init(rhsvals, 10);

    #ifdef DEBUG
    printf("• LHS: \n");
    ordered_set_print(lhsset);
    printf("• RHS: \n");
    ordered_set_print(rhsset);
    #endif

    ordered_set_t *inter = ordered_set_intersect((const ordered_set_t *[2]){lhsset, rhsset}, 2);

    #ifdef DEBUG
    printf("• Intersection: \n");
    ordered_set_print(inter);
    #endif

    index_t intervals[] = {0, 1, 4, 9, 64, 100};
    ordered_set_t *right_inter = ordered_set_init(intervals, 6);

    ut_assert_equal(inter, right_inter, ordered_set_cmp);

    ordered_set_destroy(&lhsset);
    ordered_set_destroy(&rhsset);
    ordered_set_destroy(&inter);
    ordered_set_destroy(&right_inter);

    ut_test_case_fulfill();
}

void run_ordered_set_test_unit()
{
    ut_test_unit_t unit = ut_test_unit_create("Ordered set tests");

    ut_test_unit_new_case(&unit, "Initialization test case", ordered_set_initialization_test_case);
    ut_test_unit_new_case(&unit, "Insertion test case", ordered_set_insertion_test_case);
    ut_test_unit_new_case(&unit, "Contains test case", ordered_set_contains_test_case);
    ut_test_unit_new_case(&unit, "Intersection test case", ordered_set_intersect_test_case);

    ut_test_unit_run(unit);
}