
#ifndef __TESTS_TREE__
#define __TESTS_TREE__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bst.h"
#define bool int
#define true 1
#define false 0
#define max(X,Y) (X) > (Y) ? (X) : (Y)


bool bst_is_balanced(bst_t *t);
long bst_get_height(bst_t *t);


#endif
