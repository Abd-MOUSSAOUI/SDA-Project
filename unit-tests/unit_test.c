

#include "unit_test.h"

size_t number_of_tests = 0;

void ut_test_case(const char *desc, ut_test_block_t code)
{
    ut_status_t status = code();
    if (status == UT_SUCCESS)
    {
        printf(GREEN "\u2713\t%s\n" RESET, desc);
    } else 
    {
        printf(RED "\u2717\t%s\n" RESET, desc);
    }
    number_of_tests++;
}

ut_test_case_t ut_test_case_create(const char *desc, ut_test_block_t code)
{
    ut_test_case_t test_case;
    test_case.desc = desc;
    test_case.test_code = code;
    return test_case;
}

ut_test_unit_t ut_test_unit_create(const char *desc, ut_test_case_t test_cases[], size_t count)
{
    ut_test_unit_t test_unit;
    test_unit.desc = desc;
    test_unit.test_cases = test_cases;
    test_unit.test_cases_count = count;
    return test_unit;
}

void ut_test_case_run(ut_test_case_t test_case)
{
    ut_status_t status = test_case.test_code();
    if (status == UT_SUCCESS)
    {
        printf(GREEN "\u2713\t%s\n" RESET, test_case.desc);
    } else 
    {
        printf(RED "\u2717\t%s\n" RESET, test_case.desc);
    }
}

void ut_test_unit_run(ut_test_unit_t unit)
{
    printf("%s\n\n", unit.desc);
    size_t i;
    for (i = 0; i < unit.test_cases_count; i++)
        ut_test_case_run(unit.test_cases[i]);
    
    printf("%ld tests executed\n", unit.test_cases_count);

}