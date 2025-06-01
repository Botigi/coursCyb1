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

struct node* ABR_insertF_iterProf( struct* root, int value) 
{
    struct node * newNode = malloc(sizeof(struct node));
    newNode->key = value;
    newNode->left_child = NULL;
    newNode->right_child = NULL;
    
    if(root == NULL) {
        return newNode;
    }               
    struct node * current = root;                    //boucle utile pour trouber la position a la quel inserer 
    struct node * parent = root;                     //boucle utile pour trouber la position a la quel inserer 
 
    while(current != NULL) {                         //boucle utile pour trouber la position a la quel inserer 
        parent = current;                            //boucle utile pour trouber la position a la quel inserer 
        if(current->key > value) {                   //boucle utile pour trouber la position a la quel inserer 
            current = current->left_child;           //boucle utile pour trouber la position a la quel inserer 
        } else { current = current->right_child; }   //boucle utile pour trouber la position a la quel inserer 
    }
    if(parent->key >= value) {
        parent->left_child = newNode;
    } else { parent->right_child = newNode;}
    return root;
}                                                                      





// Fonction pour supprimer un élément dans l'ABR
struct node* ABR_Delete(struct node *root, int value) {
    if (root == NULL) {
        return NULL;
    }

    struct node *delNode = root;
    struct node *parent = root;


    // Trouver le nœud à supprimer (Parcours jusqu'à la valeur ou NULL)

    while(delNode != NULL && delNode->key != value) {
        parent = delNode;
        if (value < delNode->key) {
            delNode = delNode->left_child;
        } else {
            delNode = delNode->right_child;
        }
    }

    if(delNode == NULL) {
        return root; // La valeur n'existe pas dans l'arbre
    }
    // Cas 1 : Nœud à supprimer est une feuille (n'a pas d'enfants)
    if (delNode->left_child == NULL && delNode->right_child == NULL) {
        /* pas necessaire 
        if(delNode == root) {
            free(delNode);
            return NULL;
        }
        */
        if(parent->key > value){
            parent->left_child = NULL;
        } else {
            parent->right_child = NULL;
        }
        free(delNode);
        delNode = NULL;
        return root;
    }

    // Cas 2 : Nœud à supprimer a un enfant gauche
    if (delNode->left_child != NULL && delNode->right_child == NULL) {
        if(delNode == root){
            root = root->left_child;
        }
        else if(parent->key > value){
                parent->left_child = delNode->left_child;
        }
        else{
            parent->right_child = delNode->left_child;
        }
    }
    free(delNode);
    delNode = NULL;
    return root;

        // Cas 2 bis : Nœud à supprimer a un enfant droit
        if (delNode->left_child == NULL && delNode->right_child != NULL) {
            if(delNode == root){
                root = root->right_child;
            }
            else if(parent->key > value){
                    parent->left_child = delNode->right_child;
            }
            else{
                parent->right_child = delNode->right_child;
            }
        }
        free(delNode);
        delNode = NULL;
        return root;



}



// Fonction pour créer un nouveau nœud
struct node* createNode(int key) {
    struct node* newNode = malloc(sizeof(struct node));
    if (newNode != NULL) {
        newNode->key = key;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    return newNode;
}

// Fonction pour supprimer un nœud
void freeNode(struct node* node) {
    if (node != NULL) {
        free(node);
    }
}

struct node* deleteNode(struct node* root, int value) {
    if (root == NULL || root->key == value) {
        return NULL; // L'arbre est vide
    }

    struct node* delNode = root;
    struct node* parent = NULL;

    // Trouver le nœud à supprimer
    while (delNode != NULL && delNode->key != value) {
        parent = delNode;
        if (value < delNode->key) {
            delNode = delNode->left;
        } else {
            delNode = delNode->right;
        }
    }

    if (delNode == NULL) {
        return root; // La valeur n'existe pas dans l'arbre
    }

    // Cas 1 : Aucun enfant
    if (delNode->left == NULL && delNode->right == NULL) {
        if (parent != NULL) {
            if (parent->left == delNode) {
                parent->left = NULL;
            } else {
                parent->right = NULL;
            }
        } else {
            root = NULL; // Suppression de la racine
        }
        freeNode(delNode);
        return root;
    }

    // Cas 2.1 : Un enfant gauche
    if (delNode->left != NULL && delNode->right == NULL) {
        if (parent != NULL) {
            if (parent->left == delNode) {
                parent->left = delNode->left;
            } else {
                parent->right = delNode->left;
            }
        } else {
            root = delNode->left; // Suppression de la racine
        }
        freeNode(delNode);
        return root;
    }

    // Cas 2.2 : Un enfant droit
    if (delNode->left == NULL && delNode->right != NULL) {
        if (parent != NULL) {
            if (parent->left == delNode) {
                parent->left = delNode->right;
            } else {
                parent->right = delNode->right;
            }
        } else {
            root = delNode->right; // Suppression de la racine
        }
        freeNode(delNode);
        return root;
    }

    // Cas 3 : Deux enfants
    if (delNode->left != NULL && delNode->right != NULL) {
        struct node* greatestNode = delNode->left;
        struct node* greatestParent = delNode;

        // Trouver le plus grand nœud dans le sous-arbre gauche
        while (greatestNode->right != NULL) {
            greatestParent = greatestNode;
            greatestNode = greatestNode->right;
        }

        if ( greatestNode->left != NULL ){
            greatestParent->right = greatestNode->left;
        }

        // Réassigner les pointeurs du nœud à supprimer
        greatestNode->left = delNode->left;
        greatestNode->right = delNode->right;

        // Si le nœud à supprimer est la racine sion placer le nouveau noeud
        if (parent == NULL) {
            root = greatestNode;
        } else if (parent->left == delNode) {
            parent->left = greatestParent->right;
        } else {
            parent->right = greatestParent->right;
        }

        freeNode(delNode);
    }

    return root;
}

struct node *deleteNode(struct node *root, int value){ //correction loop
    // cas 1 (aucun fils)
    
    // cas 2.1 (fils gauche)
    
    // cas 2.2 (fils droite)
    
    // cas 3 (2 fils)
    if (delNode->left!=NULL && delNode->right!=NULL){
        struct node *greatestNode = delNode->left;
        struct node *greatestParent = delNode->left;
        while(delNode->right != NULL){
            greatestParent=greatestNode;
            greatestNode=greatestNode->right;
        }
        if (delNode==root) root=greatestNode;
        
        if(parent->key >= value){
            parent->left=greatestNode;
        }else{
            parent->right=greatestNode;
        }
        
        greatestNode->right=delNode->right;
        if (greatestNode != delNode->left){
            greatestParent->right=greatestNode->left;
            greatestNode->left=delNode-left;
        }
        free(delNode);
        delNode==NULL;
        return root;
    }
}
