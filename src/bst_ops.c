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


int bst_balance_factor(bst_t *t) 
{
	int bf = 0;

	if(t->left_child) bf += bst_get_height(t->left_child);
	if(t->right_child) bf -= bst_get_height(t->right_child);

	return bf;
}


bst_t *bst_rotate_left(bst_t *t)
{
    if (t == NULL) return t;

    bst_t *x = t->right_child;
    bst_t *y = x->left_child;
 
    // Perform rotation
    x->left_child = t;
    t->right_child = y;
    
    return x;
}

bst_t *bst_rotate_right(bst_t *t)
{
    if (t == NULL) return t;

    bst_t *x = t->left_child;
    bst_t *y = x->right_child;
 
    // Perform rotation
    x->right_child = t;
    t->left_child = y;
    
    return x;
}

bst_t *bst_left_right_rotate(bst_t *t)
{
    if (t == NULL) return t;

	bst_t *x = t;
	bst_t *y = x->left_child;
	bst_t *z = y->right_child;
	
    // Perform rotation
	x->left_child = z->right_child;
	y->right_child = z->left_child; 
	z->left_child = y;
	z->right_child = x;

	return z;
}

bst_t *bst_right_left_rotate(bst_t *t)
{
    if (t == NULL) return t;

    bst_t *x = t;
	bst_t *y = x->right_child;
	if (y->right_child == NULL) return t;
	bst_t *z = y->left_child;
	
    // Perform rotation
	x->right_child = z->left_child;
	y->left_child = z->right_child;
	z->right_child = y;
	z->left_child = x;

	return z;

}

bst_t *bst_balance_node( bst_t *t ) 
{
	if (t == NULL) return t;
	bst_t *bst = NULL;

	/* Balance our children, if they exist. */
	if (t->left_child)
		t->left_child = bst_balance_node(t->left_child);
	if (t->right_child) 
		t->right_child = bst_balance_node(t->right_child);

	int bf = bst_balance_factor(t);

	if( bf >= 2 ) 
	{
		/* Left Heavy */	
		if (bst_balance_factor(t->left_child) <= -1) 
			bst = bst_left_right_rotate(t);
		else 
			bst = bst_rotate_left(t);
	} 
	else if (bf <= -2) 
	{
		/* Right Heavy */
		if (bst_balance_factor(t->right_child) >= 1 )
			bst = bst_right_left_rotate(t);
		else 
			bst = bst_rotate_right(t);
	} 
	else 
	{
		/* This t is balanced -- no change. */
		bst = t;
	}
	return bst;	
}

/* Balance a given tree */
void bst_balance(bst_t *t) 
{
	bst_t *bst = NULL;
	bst = bst_balance_node(t);
	if(bst != t) t = bst; 
}