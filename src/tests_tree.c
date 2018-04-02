#include "tests_tree.h"




bool tree_isBalanced(bst_t *t)
{
   int lh;
   int rh;

   if(t == NULL) return true;

   lh = tree_getHeight(t->left_child);
   rh = tree_getHeight(t->right_child);

   if( abs(lh-rh) <= 1 && tree_isBalanced(t->left_child)
                       && tree_isBalanced(t->right_child)) return true;

   return false;
}


int max (int X, int Y)
{
  return ((X) > (Y)) ? (X) : (Y);
}


int tree_getHeight(bst_t *t)
{
   if(t == NULL) return 0;
   return 1 + max(tree_getHeight(t->left_child), tree_getHeight(t->right_child));
}
