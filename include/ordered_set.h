

#ifndef __ORDERED_SET_H__
#define __ORDERED_SET_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "helpers.h"

#define ORDERED_SET_STR_MAX 1024
#define BLOCK_SIZE 16

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned long index_t;

typedef struct ordered_set_s
{
    index_t *values;
    size_t count;
    size_t _available;
} ordered_set_t;

ordered_set_t *ordered_set_create(void);
ordered_set_t *ordered_set_init(const index_t *values, size_t count);
int ordered_set_is_empty(const ordered_set_t *set);
void ordered_set_destroy(ordered_set_t **set);
size_t ordered_set_get_count(const ordered_set_t *set);
void ordered_set_insert(ordered_set_t *set, index_t value);
int ordered_set_contains(const ordered_set_t *set, index_t value);
void ordered_set_print(const ordered_set_t *set);
ordered_set_t *ordered_set_copy(const ordered_set_t *set);
ordered_set_t *ordered_set_intersect(const ordered_set_t **sets, size_t setc);
int ordered_set_cmp(const ordered_set_t *lhs, const ordered_set_t *rhs);
char *ordered_set_to_string(const ordered_set_t *set);
static inline int index_cmp(index_t lhs, index_t rhs) { return lhs - rhs; }

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __ORDERED_SET_H__ */
