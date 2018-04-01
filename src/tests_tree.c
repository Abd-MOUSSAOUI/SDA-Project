#include "tests_tree.h"




bool tree_isBalanced(bst_t *t)
{
   int lh;
   int rh;

   if(t == NULL) return 1;

   lh = height(t->left_child);
   rh = height(t->right_child);

   if( abs(lh-rh) <= 1 && tree_isBalanced(t->left_child)
                       && tree_isBalanced(t->right_child)) return 1;

   return 0;
}


int max (int X, int Y)
{
  return ((X) > (Y)) ? (X) : (Y);
}


int height(bst_t *t)
{
   if(t == NULL) return 0;
   return 1 + max(height(t->left_child), height(t->right_child));
}
