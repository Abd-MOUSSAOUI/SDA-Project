

#include <stdio.h>
#include <stdlib.h>
#include "analyzer.h"

int main(int argc, char *argv[])
{

    const char *testString = "Hello world this is a testing string";

    str_split(testString, ' ', ^(const char *word){
        printf("%s:", word);
    });
    putchar('\n');

    return EXIT_SUCCESS;
}