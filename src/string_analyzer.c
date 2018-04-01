
#include "string_analyzer.h"
#include "helpers.h"

bst_t *str_split(const char *str, char delimiter)
{
    bst_t *tree = bst_init();
    char *word_ptr = (char *)str;
    index_t char_count = 0, line_count = 0;
    
    while (*str)
    {
        if (*str == delimiter || *str == '\n')
        {
            char *word = salloc(NULL, (char_count + 1) * sizeof(char));
            strncpy(word, word_ptr, char_count);
            word[char_count] = '\0';
            tree = bst_insert(tree, word, line_count);
            word_ptr = (char *)(str + 1);
            char_count = 0;
            if (*str == '\n') line_count++;
        }
        else 
            char_count++;
        str++;
    }
    bst_insert(tree, word_ptr, line_count);
    return tree;
}