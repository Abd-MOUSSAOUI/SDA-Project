


#include "helpers.h"

void *salloc(void *ptr, size_t size) 
{
    void *_tmp = realloc(ptr, size);
    ASSERT(_tmp != NULL, "Can't allocate memory\n");
    return _tmp;
}

int readchar(FILE *fstream)
{
    static char buf[BUFSIZ];
    static char *bufp = buf;
    static int n = 0;

    if (n <= 0) /* buffer is empty */
    {
        n = fread(buf, BUFSIZ, sizeof(char), fstream);
        bufp = buf;
    }

    return (--n >= 0) ? (unsigned char) *bufp++ : EOF;
}