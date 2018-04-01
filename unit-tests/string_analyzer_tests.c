

#include "string_analyzer_tests.h"

void str_split_foreach(const char *word, void *arg)
{
    strcat((char *)arg, word);
    strcat((char *)arg, ":");
}

ut_status_t split_test()
{
    const char *correctString = "Hello World This Might Be The End Of The World";
    char *resultString = malloc(strlen(correctString) + 2);
    str_split(correctString, ' ', str_split_foreach, resultString);
    ut_assert_equal(resultString, "Hello:World:This:Might:Be:The:End:Of:The:World:", strcmp, "Strings did not match");
    ut_test_case_fulfill();
}

void run_string_analyzer_test_unit()
{
    ut_test_unit_t unit = ut_test_unit_create("String analyzer unit");

    ut_test_unit_new_case(&unit, "Split test", split_test);
    // Add any other test cases

    ut_test_unit_run(unit);
}