#ifndef TREE_H
#define TREE_H

#include <stdlib.h>

// Structure d'un nœud d'arbre
struct tree_node {
    int key;
    struct tree_node* left;
    struct tree_node* right;
};

// Fonctions de parcours
void tree_bfs(struct tree_node* root);
void tree_dfs(struct tree_node* root);

// Fonctions utilitaires
int tree_height(struct tree_node* root);
int tree_find_depth(struct tree_node* root, int key, int depth);

// Fonctions de création et destruction
struct tree_node* tree_create_node(int key);
void tree_destroy(struct tree_node* root);

#endif // TREE_H