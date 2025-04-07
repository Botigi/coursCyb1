#ifndef ABR_H
#define ABR_H

#include <stdlib.h>
#include "tree.h"


// BST = ABR = arebre binaire de recherche

// Fonctions de recherche
int bst_search_recursive(struct tree_node* root, int value);
int bst_search_iterative(struct tree_node* root, int value);


// Fonctions de création et destruction
struct tree_node* bst_create_node(int key);
void bst_destroy(struct tree_node* root);

// Fonstions insertions
struct node* ABR_insertF_rec( struct* root, int value);
struct node* ABR_insertF_iter( struct* root, int value);

#endif // ABR_H