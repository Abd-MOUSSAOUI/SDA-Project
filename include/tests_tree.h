
#ifndef __TESTS_TREE__
#define __TESTS_TREE__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bst.h"
#define bool int


bool tree_isBalanced(bst_t *t);
int MAX(int a, int b);
int height(bst_t *t);

#endif
