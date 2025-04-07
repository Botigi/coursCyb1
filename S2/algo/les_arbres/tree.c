#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "abr.h"
#include "tree.h"


// Fonctions de création et destruction
struct tree_node* tree_create_node(int key)
{
	struct tree_node* node = malloc(sizeof(struct tree_node));
	if (node != NULL)
	{
		node->key = key;
		node->left = NULL;
		node->right = NULL;
	}
	return node;
}

void tree_destroy(struct tree_node* root)
{
	if (root != NULL)
	{
		tree_destroy(root->left);
		tree_destroy(root->right);
		free(root);
	}
}

// BFS = Breadth-First Search ( parcours largeur)
void BFS_tableau( int tab[] , int len)  // implemetation tableau
{
    for (int i = 0 ; i < len; i++){
        if (tab[i] !=NULL ){  // remplacer par -1 ou NULL en fonction de l'implementation du tableau
            printf(tab[i]);
         }
    }
}                

void BFS_pointer(struct node *root; struct queue *mafile)
{
    if (root != NULL) {
        enqueue(mafile, root);
    }
    while(!isEmpty(mafile)) {  
        struct node *current = dequeue(mafile);
        printf("%d\n", current -> key);
        if (current -> left_child != NULL) {
          enqueue(mafile, current -> left_child);
        }     
        if (current -> right_child != NULL) {
            enqueue(mafile, current -> right_child);
        }    
    }
}

// DFS = Deep-First Search ( parcours profondeur )
void DFS_tableau_iter(int tab[], int len, stack *maPile)
{
    if (tab[] == NULL) { // Changer NULL en -1 en fonction de l'implémentation du tableau
        push(maPile, 1);
    }
    while (!isEmpty(maPile)) {
        int i = pop(maPile);
        printf("%d\n", tab[i - 1]); // On met le -1 car le tableau C commence à 0 mais le tableau des binaires commence à 1

        if (tab[(2 * i + 1) - 1] != -1) { // On met le -1 car le tableau C commence à 0 mais le tableau des binaires commence à 1
            push(maPile, 2 * i + 1); // autre condition possible : (2*pos+1 <= size)
        }

        if (tab[(2 * i) - 1] != -1) { // On met le -1 car le tableau C commence à 0 mais le tableau des binaires commence à 1
            push(maPile, 2 * i); // autre condition possible : (2*pos <= size)
        }
        
    }
}


void DFS_pointeur_rec(node *root)
{  
    if (root == NULL)
        return;
    printf("%d\n", root->key); // prefixe
    DFS(root->left_child);
 
    printf("%d\n", root->key); // infixe
  
    DFS(root->right_child);
 
    printf("%d\n", root->key); // suffixe
  
}
void DFS_pointeur_iter(node *root)
{
    if (root == NULL)
        return;
    stack *maPile = NULL;
    push(maPile, root);
    while (!isEmpty(maPile))
    {
        node *current = pop(maPile);
        printf("%d\n", current->key);
        if (current->right_child != NULL)
        {
          push(maPile, current->right_child);
        }
        if (current->left_child != NULL)
        {
          push(maPile, current->left_child);
        }
    }
}

// Fonctions usuelles sur pointeurs
int size_tree(struct node *node)
{
  if(node->key == NULL)
      return 0;
   return 1 + size_tree(node->left_child) + size_tree(node->right_child);                
}

int height_tree(struct node* root)
{
	if (root == NULL)
	{
		return -1;
	}
	return 1 + max(height(root->left_child), height(root->right_child))
}

int arity_node(struct node* n) 
{
    if (n == NULL) return 0;
    return (n->left_child != NULL) + (n->right_child != NULL);
}

int find_Depth_node(struct node *root, int value)
{
  if (root == NULL) return -1;
  if (root->key == value) return 0;

  int left_depth = find_Depth_node(root->left_child, value);
  if (left_depth != -1) return 1 + left_depth;
  
  int right_depth = find_Depth_node(root->right_child, value);
  if (right_depth != -1) return 1 + right_depth;
 
  return -1;  
}

