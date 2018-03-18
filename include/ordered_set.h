

#ifndef __ORDERED_SET_H__
#define __ORDERED_SET_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "helpers.h"

#define BLOCK_SIZE 16

typedef long index_t;

typedef struct ordered_set_s
{
    index_t *values;
    size_t count;
    size_t _available;
} ordered_set_t;

ordered_set_t *ordered_set_create(void);
ordered_set_t *ordered_set_init(const index_t *values, size_t count);
void ordered_set_destroy(ordered_set_t **set);
size_t ordered_set_get_count(const ordered_set_t *set);
void ordered_set_insert(ordered_set_t *set, index_t value);
int ordered_set_contains(const ordered_set_t *set, index_t value);
void ordered_set_print(const ordered_set_t *set);
ordered_set_t *ordered_set_intersect(const ordered_set_t **sets, size_t setc);

#endif