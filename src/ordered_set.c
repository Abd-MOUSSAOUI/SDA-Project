
#include "ordered_set.h"


ordered_set_t *ordered_set_create()
{
    ordered_set_t *set = salloc(NULL, sizeof(struct ordered_set_s));
    set->values = salloc(NULL, BLOCK_SIZE * sizeof(void *));
    set->count = 0;
    set->_available = BLOCK_SIZE;
    return set;
}

ordered_set_t *ordered_set_init(const index_t *values, size_t count)
{
    ordered_set_t *set = salloc(NULL, sizeof(struct ordered_set_s));
    set->values = salloc(NULL, count * sizeof(index_t));
    memcpy(set->values, values, count * sizeof(index_t));
    set->count = count;
    set->_available = 0;
    return set;
}

void ordered_set_destroy(ordered_set_t **set)
{
    free((*set)->values);
    free(*set);
}

void ordered_set_grow_if_needed(ordered_set_t *set)
{
    if (set->_available > 0) return;
    set->values = salloc(set->values, (set->count + BLOCK_SIZE) * sizeof(index_t));
    set->_available += BLOCK_SIZE;
}

void ordered_set_shrink_if_possible(ordered_set_t *set)
{
    if (set->_available < BLOCK_SIZE) return;
    set->values = salloc(set->values, (set->count - BLOCK_SIZE) * sizeof(index_t));
    set->_available -= BLOCK_SIZE;
}

size_t ordered_set_get_count(const ordered_set_t *set)
{
    return set->count;
}

void ordered_set_insert(ordered_set_t *set, index_t value)
{
    index_t insertion_index = 0;
    if (set->count != 0)
    {  

    }
    // Commit the insertion after getting the index
    ordered_set_grow_if_needed(set);
}

int ordered_set_contains(const ordered_set_t *set, index_t value)
{
    size_t index;
    for (index = 0; index < set->count; index++)
        if (value == set->values[index]) return 1;
    return 0;
}

void ordered_set_print(const ordered_set_t *set)
{
    size_t index;
    putchar('(');
    for (index = 0; index < set->count; index++)
    {
        printf("%ld", set->values[index]);
        if (index != set->count - 1) printf(", ");
    }
    putchar(')');
    putchar('\n');
}

ordered_set_t *ordered_set_intersect(const ordered_set_t **sets, size_t setc)
{   /* TODO: Implement this */
    return NULL;
}