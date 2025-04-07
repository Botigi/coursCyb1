#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

struct list
{
    int value;
    struct list *next;
};

struct list *list_prepend(struct list *list, int value)
{
    struct list *_new_node = malloc(sizeof(struct list));
    if (_new_node == NULL)
    {
        return NULL;
    }
    _new_node->value = value;
    _new_node->next = list;
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

struct list *list_get_element(struct list *list, int pos)
{
    if (list_length(list) <= pos)
    {
        return NULL;
    }
    
    int index=0;
    struct list *_node = list;
    while (index != pos)
    {
        index++;
        _node = _node->next;        
    }
    return _node;
}


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

struct list *list_search_element(struct list *list, int elt)
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

struct list *list_add_element(struct list *list, int pos, int value){
  struct list *_new_node = malloc(sizeof(struct list));
  _new_node->value = value;

  if ( pos <= 0 ){
        _new_node->next = list;
        return _new_node;    
  }
  int len_list = list_lengt(list);
  
  struct list *_node = list;
  if (len_list < pos){
      
    for (int i = 1; i < len_list; i++ ){
       _node = _node->next;
    }
    _node->next = _new_node;
  }else{

    for (int i = 1; i < pos; i++ ){
       _node = _node->next;
    }

    _new_node->next = _node->next;
    _node->next = _new_node;    
  }       

  return list;
}

struct list *list_add_element2(struct list *list, int pos, int value){
  struct list *_new_node = malloc(sizeof(struct list));
  _new_node->value = value;

  if ( pos <= 0 ){
        _nex_node->next = list;
        return _new_node;    
  }
    
    int index=0;
    struct list *_node = list;
    while (index != pos)
    {
        if (_node->next == NULL){
         break
         }       
                      
        index++;
        _node = _node->next;        
    }
    _node_node->next = _node->next;
   _node->next = _new_node;        
    
    return _list;
}    



             
  