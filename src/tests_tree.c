#include "tests_tree.h"




bool tree_isBalanced(bst_t *t)
{
   int lh;
   int rh;

   if(t == NULL) return true;

   lh = height(t->left_child);
   rh = height(t->right_child);

   if( abs(lh-rh) <= 1 && tree_isBalanced(t->left_child)
                       && tree_isBalanced(t->right_child)) return true;

   return false;
}


int MAX (int X, int Y)
{
  return ((X) > (Y)) ? (X) : (Y);
}


int height(struct node* node)
{
   if(node == NULL) return 0;
   return 1 + max(height(node->left), height(node->right));
}
