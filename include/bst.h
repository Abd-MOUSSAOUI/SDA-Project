

#ifndef __BST_H__
#define __BST_H__

#include <stdio.h>
#include <stdlib.h>
#include "ordered_set.h"

typedef struct bst_s
{
    char *word;
    ordered_set_t *positions;
    struct bst_s *left_child;
    struct bst_s *right_child;
} bst_t;

bst_t *bst_create(void);
void bst_destroy(bst_t **bst);
size_t bst_get_words_count(const bst_t *bst);
size_t bst_get_word_pos_count(const bst_t *bst);
void bst_insert(bst_t *bst, const char *word, const ordered_set_t *set);
size_t *bst_find_occurences(const bst_t *bst, const char *word);


/*

• find qui permet de retrouver tous les indices d’occurrences d’un mot.
• findCooccurrences qui permet de retrouver tous les indices de coocurrences de plusieurs mots.
• printBinarySearchTree qui affiche un arbre binaire de recherche

*/

#endif