
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
            ASSERT(set->values[mid] != value, "Value %ld already exists\n", value);
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
    set->_available--;
}

int ordered_set_contains(const ordered_set_t *set, index_t value)
{
    index_t index = 0;
    if (set->count != 0)
    {  
        index_t i = 0, j = set->count - 1;
        while(i <= j)
        {
            index_t mid = (i + j) / 2;
            if (set->values[mid] > value)
                j = mid - 1;
            else if (set->values[mid] < value)
                i = mid + 1;
            else 
                return 1;
        }
        index = i;
    }
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

ordered_set_t *ordered_set_intersect(ordered_set_t * const *sets, size_t setc)
{
    index_t index;
    ordered_set_t *st_set = (ordered_set_t *)sets[0], *intersection = ordered_set_create();
    for (index = 0; index < st_set->count; index++)
    {
        index_t set_index, value = st_set->values[index];
        for (set_index = 1; set_index < setc; set_index++)
            if (ordered_set_contains(sets[set_index], value))
                ordered_set_insert(intersection, value);
    }
    return intersection;
}

ordered_set_t *ordered_set_copy(const ordered_set_t *set)
{
    ordered_set_t *copy = ordered_set_create();
    index_t index;
    for (index = 0; index < set->count; index++)
    {
        _ordered_set_grow_if_needed(copy);
        copy->values[index] = set->values[index];
        copy->count++;
        copy->_available--;
    }
    return copy;
}