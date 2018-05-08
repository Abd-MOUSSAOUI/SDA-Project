

#include "bst.h"

bst_t *bst_init()
{
    return NULL;
}

bst_t *bst_create(const char *word, const ordered_set_t *positions)
{
    bst_t *bst = salloc(NULL, sizeof(struct bst_s));

    bst->positions = ordered_set_copy(positions);

    bst->word = salloc(NULL, (strlen(word) + 1) * sizeof(char)) ;
    strcpy(bst->word, word);

    bst->left_child = NULL;
    bst->right_child = NULL;

    return bst;
}

void bst_destroy(bst_t **bst)
{
    if (*bst == NULL) return;
    bst_destroy(&((*bst)->left_child));
    bst_destroy(&((*bst)->right_child));
    ordered_set_destroy(&((*bst)->positions));
    free((*bst)->word);
}

size_t bst_get_number_string(const bst_t *bst)
{
    if (bst == NULL) return 0;
    return 1 + bst_get_number_string(bst->left_child) 
             + bst_get_number_string(bst->right_child);
}

size_t bst_get_total_number_string(const bst_t *bst)
{
    if (bst == NULL) return 0;
    return bst->positions->count + bst_get_total_number_string(bst->left_child) 
                                + bst_get_total_number_string(bst->right_child);
}

float _bst_get_total_depth(const bst_t *bst, float init_depth)
{
    if (bst == NULL)
        return 0;
    return init_depth + _bst_get_total_depth(bst->left_child, init_depth + 1)
                      + _bst_get_total_depth(bst->right_child, init_depth + 1);
}

float bst_get_average_depth(const bst_t *bst)
{
    return _bst_get_total_depth(bst, 0) / bst_get_number_string(bst);
}

bst_t *bst_insert(bst_t *bst, const char *word, index_t pos)
{
    if (bst == NULL)
    {
      ordered_set_t *positions = ordered_set_create();
      ordered_set_insert(positions, pos);
      return bst_create(word, positions);
    }
    if (strcmp(bst->word, word)>0)
    {
        if (bst->left_child == NULL)
        {
          ordered_set_t *positions = ordered_set_create();
          ordered_set_insert(positions, pos);
          bst->left_child = bst_create(word, positions);
        }
        else
        {
            bst_insert(bst->left_child, word, pos);
        }
    }
    if (strcmp(bst->word, word)<0)
    {
      if (bst->right_child == NULL)
      {
        ordered_set_t *positions = ordered_set_create();
        ordered_set_insert(positions, pos);
        bst->right_child = bst_create(word, positions);
      }
      else 
        bst_insert(bst->right_child, word, pos);
    }

    if (strcmp(bst->word, word) == 0)
    {
      if (!ordered_set_contains(bst->positions, pos))
        ordered_set_insert(bst->positions, pos);
    }
    return bst;
}

ordered_set_t *bst_find(const bst_t *bst, const char *word)
{
    if (bst == NULL) 
        return ordered_set_create();
    else if (strcmp(bst->word, word) == 0) 
        return bst->positions;
    else
    {
        ordered_set_t *found = bst_find(bst->left_child, word);
        return !ordered_set_is_empty(found) ? found : bst_find(bst->right_child, word);
    }
}

ordered_set_t *bst_find_cooccurences(const bst_t *bst, const char **words, 
                                          size_t wordc)
{
    ordered_set_t *intersection;
    const ordered_set_t **position_sets = salloc(NULL, wordc * sizeof(const ordered_set_t *));
    unsigned i;
    for (i = 0; i < wordc; i++)
        position_sets[i] = bst_find(bst, words[i]);
    return ordered_set_intersect(position_sets, wordc);
}

int bst_cmp(const bst_t *lhs, const bst_t *rhs)
{
    if (lhs && rhs) 
        return  strcmp(lhs->word, rhs->word) && 
                bst_cmp(lhs->left_child, rhs->left_child) && 
                bst_cmp(lhs->right_child, rhs->right_child) ;
    else if (!lhs && !rhs) return 0;
    else return 1;
}

void bst_traverse(bst_t *bst, bst_traversal traversal, process_node_f process, void *arg)
{
    if (bst == NULL) return;
    switch (traversal)
    {
        case INORDER:
            bst_traverse(bst->left_child, traversal, process, arg);
            process(bst, arg);
            bst_traverse(bst->right_child, traversal, process, arg);
            break;
        case PREORDER:
            process(bst, arg);
            bst_traverse(bst->left_child, traversal, process, arg);
            bst_traverse(bst->right_child, traversal, process, arg);
            break;
        case POSTORDER:
            bst_traverse(bst->left_child, traversal, process, arg);
            bst_traverse(bst->right_child, traversal, process, arg);
            process(bst, arg);
            break;
    }
}

void bst_fill_list(const bst_t *bst, void *arg)
{
    char ***list = (char ***)arg;
    char **l = *list;
    index_t size = 0;
    while (l != NULL && *l != NULL)
    {
        l++;
        size++;
    }
    
    (*list) = salloc((*list), (size + 2) * sizeof(char *));
    (*list)[size] = bst->word;
    (*list)[size + 1] = NULL;

}

char **bst_to_list(const bst_t *bst)
{

    char **list = NULL;

    bst_traverse((bst_t *)bst, INORDER, bst_fill_list, &list);

    return list;
}