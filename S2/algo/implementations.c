#include <stdio.h>
#include <stdlib.h>

struct liste_t {
    int* tab;
    int size_max;
    int size;
};

struct list_p {
    int value;
    struct list_p* next;  
};

int size(struct liste_p* first) {
    struct liste_p* current = first;
    int n = 0;
    while (current != NULL) {
        current = current->next;
        n++;
    }
    return n;
}

struct liste_p* getElement(struct liste_p* first, int pos) {
    struct liste_p* current = first;
    for (int i = 0; i < pos; i++) {
        current = current->next;
        if (current == NULL)
            return NULL;  // error 404 : Elt not found
    }
    return current;
}

struct liste_p* getElementR(struct liste_p* first, int pos) {
    if (first == NULL)
        return NULL;  // error 404 : Elt not found
    if (pos == 0) {
        return first;
    }
    return getElementR(first->next, pos - 1);
}

struct liste_p* searchElement(struct liste_p* first, int value) {
    struct liste_p* current = first;
    while (current != NULL) {
        if (current->value == value)  
            return current;
        current = current->next;
    }
    return NULL; 
}

struct list
{
    int value;
    struct list *next;
};

struct list* list_prepend(struct list* list, int value) {
    struct list* new_node = malloc(sizeof(struct list));  
    if (new_node == NULL) {
        return NULL;
    }
    new_node->value = value;
    new_node->next = list;
    return new_node; 
}

size_t list_length(struct list *list)
{
    size_t count = 0;
    struct list *_node= list;
    while (_node != NULL)
    {
        count += 1;
        _node = _node->next;
    }
    return count;
}

struct list* list_get_element(struct list* list, int pos) {
    if (list_length(list) <= pos) {
        return NULL;
    }

    int index = 0;
    struct list* node = list;
    while (index != pos) {
        index++;
        node = node->next;
    }
    return node;  


struct list *list_get_element_recursive(struct list *list, int pos)
{
    if ( list == NULL)
    {
        return NULL;
    }
    if (pos == 0)
    {
        return list;
    }
    return list_get_element_recursive(list->next, (pos - 1));
}

struct list *list_seach_element(struct list *list, int elt)
{
    struct list *_node = list;
    while (elt != _node->value)
    {
        if (_node == NULL)
        {
            return NULL;
        }
        _node=_node->next;
    }
    return _node;
}

void list_print(struct list *list)
{
    if (list == NULL)
    {
        return;
    }
    while (list != NULL)
    {
        printf("%d", list->value);
        if (list->next != NULL)
        {
            printf(" ");
        }
        list = list->next;
    }
    printf("\n");
}

void list_destroy(struct list *list)
{
    struct list *_temp;
    while (list != NULL)
    {
        _temp = list;
        list = list->next;
        free(_temp);
    }
}

struct list* list_add_element(struct list* list, int pos, int value){
    struct list* new_node = malloc(sizeof(struct list));
    new_node->value = value;

    if (pos <= 0) {
        new_node->next = list;
        return new_node;
    }
    int len_list = list_length(list);
    
    struct list* node = list;
    if (len_list < pos) {
        for (int i = 1; i < len_list; i++) {
            node = node->next;
        }
        node->next = new_node;
    } else {
        for (int i = 1; i < pos; i++) {
            node = node->next;
        }
        new_node->next = node->next;
        node->next = new_node;
    }
    return list;
}

struct list* list_add_element2(struct list* list, int pos, int value) {
    struct list* new_node = malloc(sizeof(struct list));
    new_node->value = value;

    if (pos <= 0) {
        new_node->next = list;  
        return new_node;
    }

    int index = 0;
    struct list* node = list;
    while (index != pos) {
        if (node->next == NULL) {
            break;  
        }
        index++;
        node = node->next;
    }
    new_node->next = node->next; 
    node->next = new_node;

    return list;  
}
