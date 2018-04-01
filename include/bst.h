

#ifndef __BST_H__
#define __BST_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ordered_set.h"
#include "helpers.h"

typedef struct bst_s
{
    char *word;
    ordered_set_t *positions;
    struct bst_s *left_child;
    struct bst_s *right_child;
} bst_t;

bst_t *bst_init(void);
bst_t *bst_create(const char *word, const ordered_set_t *positions);
void bst_destroy(bst_t **bst);
size_t bst_get_words_count(const bst_t *bst);
size_t bst_get_word_pos_count(const bst_t *bst);
bst_t* bst_insert(bst_t *bst, const char *word, index_t pos);
ordered_set_t *bst_find_occurence_indexes(const bst_t *bst, const char *word);

/*
• findCooccurrences qui permet de retrouver tous les indices de coocurrences de plusieurs mots.
*/

#endif
