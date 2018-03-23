
#ifndef __HELPERS_H__
#define __HELPERS_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define ASSERT(COND, ...) \
    if (!(COND)) \
    { \
        fprintf(stderr, __VA_ARGS__); \
        fprintf(stderr, "Assertion failed at line %d in file %s called from: %s\n", __LINE__, __FILE__, __PRETTY_FUNCTION__); \
        exit(EXIT_FAILURE); \
    }


void *salloc(void *ptr, size_t size);

#endif