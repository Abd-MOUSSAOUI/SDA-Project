

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unit_test.h"
#include "analyzer.h"

#ifndef __clang__
void str_split_foreach(const char *word, void *arg)
{
    strcat((char *)arg, word);
    strcat((char *)arg, ":");
}

ut_status_t analyzer_test()
{
    const char *correctString = "Hello World This Might Be The End Of The World";
    char *resultString = malloc(strlen(correctString) + 2);
    str_split(correctString, ' ', str_split_foreach, resultString);
    ut_assert_equal(resultString, "Hello:World:This:Might:Be:The:End:Of:The:World:", strcmp, "Strings did not match");
    ut_test_case_fulfill();
}
#endif

int main(int argc, char *argv[])
{

    ut_test_unit_t unit = ut_test_unit_create("String analyzer tests");

    #ifdef __clang__
    ut_test_unit_new_case(&unit, "Correct example", ^ {
        const char *correctString = "Hello World This Might Be The End Of The World";
        char *resultString = malloc(strlen(correctString) + 2);
        str_split(correctString, ' ', ^(const char *word, void *arg) {
            strcat(resultString, word);
            strcat(resultString, ":");
        }, NULL);
        ut_assert_equal(resultString, "Hello:World:This:Might:Be:The:End:Of:The:World:", strcmp, "Strings did not match");
        ut_test_case_fulfill();
    });
    #else
    ut_test_unit_new_case(&unit, "Correct example", analyzer_test);
    #endif

    ut_test_unit_run(unit);

    return EXIT_SUCCESS;
}