
#include "analyzer.h"
#include "helpers.h"

#ifdef __clang__
void str_split(const char *str, char delimiter, void(^map_function)(const char *, void *), void *arg)
#else
void str_split(const char *str, char delimiter, void(*map_function)(const char *, void *), void *arg)
#endif
{
    char *word_ptr = (char *)str;
    size_t char_count = 0;
    
    while (*str)
    {
        if (*str == delimiter)
        {
            char *word = salloc(NULL, (char_count + 1) * sizeof(char));
            strncpy(word, word_ptr, char_count);
            word[char_count] = '\0';
            map_function(word, arg);
            word_ptr = (char *)(str + 1);
            char_count = 0;
        }
        else 
            char_count++;
        str++;
    }
    map_function(word_ptr, arg);
}