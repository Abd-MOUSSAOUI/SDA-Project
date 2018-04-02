
#ifndef __TESTS_TREE__
#define __TESTS_TREE__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bst.h"
#define bool int
#define true 1
#define false 0


bool tree_isBalanced(bst_t *t);
int tree_getHeight(bst_t *t);
int max(int a, int b);


#endif
