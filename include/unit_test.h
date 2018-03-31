

#ifndef __UNIT_TEST_H__
#define __UNIT_TEST_H__

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include "helpers.h"
#include "chrono.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { UT_SUCCESS = 0, UT_FAIL } ut_status_t;

#ifdef __clang__
typedef ut_status_t(^ut_test_block_t)(void); 
#else 
typedef ut_status_t(*ut_test_block_t)(void); 
#endif

typedef struct ut_test_case_s
{
    const char *desc;
    ut_test_block_t test_code;
} ut_test_case_t;

typedef struct ut_test_unit_s
{
    const char *desc;
    ut_test_case_t *test_cases;
    size_t test_cases_count;
} ut_test_unit_t;

#define ut_assert_null(__PTR, ...) \
    if ((__PTR) != NULL) \
    { \
        printf(__VA_ARGS__); \
        putchar('\n'); \
        return UT_FAIL; \
    }

#define ut_assert_not_null(__PTR, ...) \
    if ((__PTR) == NULL) \
    { \
        printf(__VA_ARGS__); \
        putchar('\n'); \
        return UT_FAIL; \
    }

#define ut_assert_equal(__LHS, __RHS, __CMP, ...) \
    if (__CMP(__LHS, __RHS) != 0) \
    { \
        printf(__VA_ARGS__); \
        putchar('\n'); \
        return UT_FAIL; \
    }

#define ut_assert_not_equal(__LHS, __RHS, __CMP, ...) \
    if (__CMP(__LHS, __RHS) == 0) \
    { \
        printf(__VA_ARGS__); \
        putchar('\n'); \
        return UT_FAIL; \
    }

#define ut_assert_true(__COND, ...) \
    if (!(__COND)) \
    { \
        printf(__VA_ARGS__); \
        putchar('\n'); \
        return UT_FAIL; \
    }

#define ut_assert_false(__COND, ...) \
    if (!(__COND)) \
    { \
        printf(__VA_ARGS__); \
        putchar('\n'); \
        return UT_FAIL; \
    }

#define ut_test_case_fulfill() return UT_SUCCESS

#define ut_test_case_fail(__MSG, ...) \
    printf((__MSG), __VA_ARGS__); \
    putchar('\n'); \
    return UT_FAIL

ut_test_case_t ut_test_case_create(const char *desc, ut_test_block_t code);
ut_status_t ut_test_case_run(ut_test_case_t test_case);

ut_test_unit_t ut_test_unit_init(const char *desc, ut_test_case_t test_cases[], size_t count);
ut_test_unit_t ut_test_unit_create(const char *desc);
void ut_test_unit_run(ut_test_unit_t unit);
void ut_test_unit_new_case(ut_test_unit_t *unit, const char *desc, ut_test_block_t code);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __UNIT_TEST_H__ */