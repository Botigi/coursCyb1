#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stddef.h>

// Structure d'un nœud de liste
struct list_node {
    int value;
    struct list_node* next;
};

// Fonctions de création et destruction
struct list_node* list_create_node(int value);
void list_destroy(struct list_node* head);

// Fonctions de consultation
size_t list_size(struct list_node* head);
struct list_node* list_get_at(struct list_node* head, int position);
struct list_node* list_get_at_recursive(struct list_node* head, int position);
struct list_node* list_find(struct list_node* head, int value);

// Fonctions de modification
struct list_node* list_prepend(struct list_node* head, int value);
void list_print(struct list_node* head);

#endif // LIST_H
