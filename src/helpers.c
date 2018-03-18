


#include "helpers.h"

void *salloc(void *ptr, size_t size) 
{
    void *_tmp = realloc(ptr, size);
    assert(_tmp != NULL);
    return _tmp;
}