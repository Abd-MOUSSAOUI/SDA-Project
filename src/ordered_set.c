
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

int ordered_set_is_empty(const ordered_set_t *set)
{
    return set->count == 0;
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
    if (!ordered_set_is_empty(set))
    {  
        index_t i = 0, j = set->count - 1;
        while(i <= j)
        {
            index_t mid = (i + j) / 2;
            if (set->values[mid] > value)
            {
                if (mid == 0)
                    return 0;
                j = mid - 1;
            }
            else if (set->values[mid] < value)
                i = mid + 1; 
            else 
                return 1;
        }
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

int _ordered_set_group_contain(const ordered_set_t **sets, size_t setc, index_t val)
{
    index_t seti;
    for (seti = 0; seti < setc; seti++)
    {
        if (!ordered_set_contains(sets[seti], val))
            return 0;
    }
    return 1;
}

ordered_set_t *ordered_set_intersect(const ordered_set_t **sets, size_t setc)
{
    if (sets == NULL || setc == 0)
        return ordered_set_create();

    ordered_set_t *intersection = ordered_set_create();
    const ordered_set_t *first = *sets;

    index_t vali;

    for (vali = 0; vali < first->count; vali++)
    {
        index_t val = first->values[vali];
        if (_ordered_set_group_contain((sets + 1), setc - 1, val))
            ordered_set_insert(intersection, val);
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

int ordered_set_cmp(const ordered_set_t *lhs, const ordered_set_t *rhs)
{
    if (lhs->count != rhs->count) return 1;
    index_t index;
    for (index = 0; index < lhs->count; index++)
        if (lhs->values[index] != rhs->values[index])
            return 1;
    return 0;
}

unsigned short int digits_count(index_t i)
{
    unsigned short int digits = 0;

    while (i > 0)
    {
        i /= 10; 
        digits++;
    }
    return digits;
}

char *ordered_set_to_string(const ordered_set_t *set)
{
    if (ordered_set_is_empty(set))
        return "(empty)";
    char *str = malloc(ORDERED_SET_STR_MAX);
    index_t index, i = 1;
    sprintf(str, "(");
    for (index = 0; index < set->count; index++)
    {
        sprintf((str + i), "%lu", set->values[index]);
        i += digits_count(set->values[index]);
        if (index != set->count - 1) 
        {
            sprintf((str + i), ", ");
            i += 2;
        }
    }
    sprintf(str + (i++), ")");
    str[i] = 0;
    return str;
}