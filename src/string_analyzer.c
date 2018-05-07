
#include "string_analyzer.h"
#include "helpers.h"

char *strlow(char *str)
{
    char *ptr = str;
    for ( ; *str; ++str) *str = tolower(*str);
    return ptr;
}

bst_t *str_split(const char *str)
{
    bst_t *tree = bst_init();
    size_t line_index = 1;
    char *text = salloc(NULL, strlen(str) + 1), *line = NULL, *word = NULL;
    strncpy(text, str, strlen(str));
    while ((line = strtok_r(text, "\n", &text)) != NULL)
    {
        while ((word = strtok_r(line, DELIMITERS, &line)) != NULL)
        {
            // strlow(word);
            tree = bst_insert(tree, word, line_index);
        }
        line_index++;
    }
    return tree;
}

bst_t *fstr_split(FILE *fstream)
{
    bst_t *tree = bst_init();
    char *line = NULL, *word = NULL;
    size_t line_length = 0, line_index = 1;
    while (getline(&line, &line_length, fstream) != -1)
    {
        word = strtok(line, DELIMITERS);
        while (word != NULL)
        {
            // strlow(word);
            tree = bst_insert(tree, word, line_index);
            word = strtok(NULL, DELIMITERS);
        }
        line_index++;
    }
    return tree;
}