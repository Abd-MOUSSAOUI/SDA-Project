

#include "ordered_set_tests.h"


ut_status_t initialization_test_case()
{
    index_t test_values[11] = {0, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100};
    ordered_set_t *test_set = ordered_set_init(test_values, 11);
    index_t index;
    for (index = 0; index < 11; index++)
        ut_assert_equal(test_set->values[index], index * index, 
                        index_cmp, "%lu != %lu", test_set->values[index], index * index);
    ut_test_case_fulfill();
}

ut_status_t insertion_test_case()
{
    index_t test_values[10] = {0, 1, 4, 9, 25, 36, 49, 64, 81, 100};
    ordered_set_t *test_set = ordered_set_init(test_values, 10);
    ordered_set_insert(test_set, 16);

    index_t post_test_values[11] = {0, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100};
    ordered_set_t *post_test_set = ordered_set_init(post_test_values, 11);
    ut_assert_equal(test_set, post_test_set, ordered_set_cmp, "Insertion wasn't successful");

    ut_test_case_fulfill();
}

void run_ordered_set_test_unit()
{
    ut_test_unit_t unit = ut_test_unit_create("Ordered set tests");

    ut_test_unit_new_case(&unit, "Initialization test", initialization_test_case);

    ut_test_unit_new_case(&unit, "Insertion test", insertion_test_case);

    ut_test_unit_run(unit);
}