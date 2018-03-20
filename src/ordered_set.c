
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

void _ordered_set_grow_if_needed(ordered_set_t *set)
{
    if (set->_available > 0) return;
    set->values = salloc(set->values, (set->count + BLOCK_SIZE) * sizeof(index_t));
    set->_available += BLOCK_SIZE;
}

void _ordered_set_shrink_if_possible(ordered_set_t *set)
{
    if (set->_available < BLOCK_SIZE) return;
    set->values = salloc(set->values, (set->count - BLOCK_SIZE) * sizeof(index_t));
    set->_available -= BLOCK_SIZE;
}

void _ordered_set_shift(ordered_set_t *set, index_t from, off_t offset)
{
    memmove(set->values + from + offset, set->values + from, (set->count - from) * sizeof(void *));
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
        index_t i = 0, j = set->count - 1;
        while(i <= j)
        {
            index_t mid = (i + j) / 2;
            ASSERT(set->values[mid] != value, "Value %ld already exists %s\n", value, "thanks");
            if (set->values[mid] > value)
                j = mid - 1;
            else if (set->values[mid] < value)
                i = mid + 1;
        }
        insertion_index = i;
    }
    _ordered_set_grow_if_needed(set);
    _ordered_set_shift(set, insertion_index, 1);
    set->values[insertion_index] = value;
    set->count++;
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