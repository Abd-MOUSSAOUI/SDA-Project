

#include <stdio.h>
#include <stdlib.h>
#include "analyzer.h"

#ifndef __clang__
void print_word(const char *word)
{
    printf("%s:", word);
}
#endif

int main(int argc, char *argv[])
{

    const char *testString = "Hello world this is a testing string";

    #ifdef __clang__
    str_split(testString, ' ', ^(const char *word){
        printf("%s:", word);
    });
    #else
    str_split(testString, ' ', print_word);
    #endif
    
    putchar('\n');

    return EXIT_SUCCESS;
}