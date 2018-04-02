#include "bst_ops.h"




bool bst_is_balanced(bst_t *t)
{
   int lh;
   int rh;

   if(t == NULL) return true;

   lh = bst_get_height(t->left_child);
   rh = bst_get_height(t->right_child);

   if( abs(lh-rh) <= 1 && bst_is_balanced(t->left_child)
                        && bst_is_balanced(t->right_child)) return true;

   return false;
}



int bst_get_height(bst_t *t)
{
    int lh=0, rh=0;
    if(t == NULL) return 0;
    if(t->left_child != NULL) lh = bst_get_height(t->left_child);
    if(t->right_child != NULL) rh = bst_get_height(t->right_child);
    return 1 + max(lh, rh);
}


void bst_rotate_left(bst_t *t)
{

}

void bst_rotate_right(bst_t *t)
{

}

void bst_drotate_left(bst_t *t)
{

}

void bst_drotate_right(bst_t *t)
{
    
}