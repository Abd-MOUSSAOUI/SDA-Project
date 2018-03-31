

#include <stdio.h>
#include <stdlib.h>
#include "unit_test.h"

int main(int argc, char *argv[])
{

    ut_test_case_t t1 = ut_test_case_create("SUCCESS NULL TEST CASE", ^{
        ut_assert_null(NULL, "this is not a null ptr");
        ut_test_case_fulfill();
    });

    ut_test_case_t t2 = ut_test_case_create("SUCCESS TRUE TEST CASE", ^{
        ut_assert_true(1 == 1, "1. this is not a true condition");
        ut_test_case_fulfill();
    });

    ut_test_case_t t3 = ut_test_case_create("FAIL TEST CASE", ^{
        ut_assert_true(1 == 100, "2. this is not a true condition\n");
        ut_test_case_fulfill();
    });

    ut_test_case_t cases[] = {t1, t2, t3};
    ut_test_unit_t unit = ut_test_unit_create("THIS IS A BRAND NEW TEST UNIT", cases, 3);

    ut_test_unit_run(unit);

    return EXIT_SUCCESS;
}