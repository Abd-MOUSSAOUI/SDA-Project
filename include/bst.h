

#ifndef __BST_H__
#define __BST_H__

typedef struct bst_s
{
    void *value;
    struct bst_s *left_child;
    struct bst_s *right_child;
} bst_t;

bst_t *bst_create(void);


/*

initBinarySearchTree qui cr´ee un nouvel arbre binaire de recherche vide.
• freeBinarySearchTree qui lib`ere la m´emoire allou´eev pour l’arbre.
• getNumberString qui renvoie le nombre de mots diff´erents contenus dans l’arbre.
• getTotalNumberString qui renvoie le nombre de paires mots-phrases diff´erentes contenues dans
l’arbre.
• insert qui permet d’ajouter une nouvelle paire mot-position dans l’arbre :
1. Si le mot n’existe pas, on cr´ee un nouveau noeud contenant le mot et un nouvel ensemble de
positions pour y stocker l’index de la phrase.
2. Si le mot existe, on rajoute `a l’index de la phrase au noeud correspondant.
3. Rapel : Si un mot apparait plusieurs fois, on stocke une unique fois l’index de la phrase.
• find qui permet de retrouver tous les indices d’occurrences d’un mot.
• findCooccurrences qui permet de retrouver tous les indices de coocurrences de plusieurs mots.
• printBinarySearchTree qui affiche un arbre binaire de recherche

*/

#endif