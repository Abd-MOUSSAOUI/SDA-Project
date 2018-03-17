

#ifndef __ORDERED_SET_H__
#define __ORDERED_SET_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct ordered_set_s
{

} ordered_set_t;

typedef int (*ordered_set_cmp)(const void *);

ordered_set_t *ordered_set_create(void);
void ordered_set_destroy(ordered_set_t **set);
size_t ordered_set_get_count(const ordered_set_t *set);
void ordered_set_insert(ordered_set_t *set, void *value);
int ordered_set_contains(const ordered_set_t *set, const void *value, ordered_set_cmp cmp_func);
void ordered_set_print(const ordered_set_t *set);
ordered_set_t *ordered_set_intersect(const ordered_set_t **sets);

#endif