

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

void bst_insert(bst_t *bst, const char *word, index_t pos)
{

}

size_t *bst_find_occurence_index(const bst_t *bst, const char *word)
{
    return NULL;
}

void bst_print(const bst_t *bst)
{
    if (bst == NULL) 
    {
        printf("nil");
        return;
    } 
    printf("[ ");
    bst_print(bst->left_child);
    printf(" | %s | ", bst->word);
    bst_print(bst->right_child);
    printf(" ]");
}