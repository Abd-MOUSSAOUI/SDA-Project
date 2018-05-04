

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

size_t bst_get_words_count(const bst_t *bst)
{
    if (bst == NULL) return 0;
    return 1 + bst_get_words_count(bst->left_child) + bst_get_words_count(bst->right_child);
}

size_t bst_get_word_pos_count(const bst_t *bst)
{
    if (bst == NULL) return 0;
    return bst->positions->count + bst_get_word_pos_count(bst->left_child) + bst_get_word_pos_count(bst->right_child);
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

char *bst_find(const bst_t *bst, const char *word)
{
    char *occu;
    if (bst == NULL) occu=NULL;
    else if (bst->word == word) occu = ordered_set_to_string(bst->positions);
    else  
    {
        bst_find(bst->left_child, word);
        bst_find(bst->right_child, word);
    }
    return occu;
}

char **bst_find_occurence_indexes(const bst_t *bst, const char **word)
{
    const char **word_to_search = word;
    int i=0, j=0;
    while (word_to_search != NULL)
    {
        i++;
    }
    char **occurences = salloc(occurences, (i + 2) * sizeof(char *));
    while (j<i)
    {
        occurences[j] = bst_find(bst, word_to_search[j]);
        j++;
    }
    occurences[j+1]=NULL;
    return occurences;
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

void bst_traverse(bst_t *bst, bst_traversal traversal, forerach_node process, void *arg)
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