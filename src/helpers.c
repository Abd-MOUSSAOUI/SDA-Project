


#include "helpers.h"

void *salloc(void *ptr, size_t size) 
{
    void *_tmp = realloc(ptr, size);
    ASSERT(_tmp != NULL, "Can't allocate memory\n");
    return _tmp;
}