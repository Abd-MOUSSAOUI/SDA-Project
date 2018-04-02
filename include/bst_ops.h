
#ifndef __BST_OPS_H__
#define __BST_OPS_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bst.h"

#ifdef __cplusplus
extern "C" {
#endif

#define bool int
#define true 1
#define false 0
#define max(X,Y) ((X) > (Y) ? (X) : (Y))

bool bst_is_balanced(bst_t *t);
int bst_get_height(bst_t *t);
bst_t bst_rotate_left(bst_t *t);
bst_t bst_rotate_right(bst_t *t);
void bst_drotate_left(bst_t *t);
void bst_drotate_right(bst_t *t);


#ifdef __cplusplus
}
#endif  /* __cplusplus__ */
#endif /* __BST_OPS_H__ */
