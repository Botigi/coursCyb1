#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "abr.h"
#include "tree.h"

// BST = ABR = arebre binaire de recherche


  
  

int bst_search_recursive(struct tree_node* root, int value) {
    if (root == NULL) {
        return -1;
    }
    struct tree_node* current = root;

    if (current->key == key) {
        return 0;  //la racine d'un arbre est a l'hauteur 0
    }
    if (value < current -> key)
        return bst_search_recursive(current->left_child, value) + 1;
    return bst_search_recursive(current->right_child, value) + 1; 

}



int bst_search_iterative(struct tree_node* root, int value) {
    if (root == NULL) {
        return -1;
    }
    
    struct tree_node* current = root;
    int depth = 0;  //la racine d'un arbre est a l'hauteur 0
    
    while (current != NULL) {
        if (current->key == value) {
            return depth;
        }
        
        current = (current->key > value) ? current->left : current->right;
        depth++;
    }
    
    return -1;
}

struct tree_node* bst_create_node(int key) {
    struct tree_node* node = malloc(sizeof(struct tree_node));
    if (node != NULL) {
        node->key = key;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

void bst_destroy(struct tree_node* root) {
    if (root != NULL) {
        bst_destroy(root->left);
        bst_destroy(root->right);
        free(root);
    }
}



struct node* ABR_insertF_rec( struct* root, int value)
{
    if ( root == NULL ) {
        struct node* newNode=malloc(siezeof(struct node));
        newNode->key=value;
        newNode->left_chld=NULL;
        newNode->reight_child=NULL;
        return newNode;                                    
    }
    else {
        if( root -> key > value ) 
        {
            root -> left_child = ABR_insertF_Rec( root -> left_child, value );
        }
        else 
        {
            root -> right_child = ABR_insertF_Rec( root -> right_child, value ); 
        }
        return root;                        
    }               
}


struct node* ABR_insertF_iter( struct* root, int value)
{
    struct node* newNode=bst_create_node(value);
    if ( root == NULL ) {
        return newNode;                                    
    }
    else {
        struct node* current = root;
        while (current != NULL) {
            if (current->key > value) {
                if (current->left_child == NULL) {
                    current->left_child = newNode;
                    return root;
                }
                current = current->left_child;
            } else {
                if (current->right_child == NULL) {
                    current->right_child = newNode;
                    return root;
                }
                current = current->right_child;
            }
        }
        return root;
    }
}
