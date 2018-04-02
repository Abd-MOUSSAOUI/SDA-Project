#include "bst_ops.h"




bool bst_is_balanced(bst_t *t)
{
   long lh;
   long rh;

   if(t == NULL) return true;

   lh = bst_get_height(t->left_child);
   rh = bst_get_height(t->right_child);

   if( labs(lh-rh) <= 1 && bst_is_balanced(t->left_child)
                       && bst_is_balanced(t->right_child)) return true;

   return false;
}



long bst_get_height(bst_t *t)
{
   if(t == NULL) return 0;
   return 1 + max(bst_get_height(t->left_child), bst_is_balanced(t->right_child));
}
