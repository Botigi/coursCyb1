#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

struct stack_p
{
  int elt;
  struct stack_p * next;
};
struct stack_p *push(struct stack_p *head, int val)
{
  struct stack_p *new_node = malloc(sizeof(struct stack_p));
  new_node->elt = val;
  new_node->next = head;
  return new_node;
}

struct stack_p *pop(struct stack_p *head)
{
  if (Empty(head)){
    return NULL;
  }
        
  struct stack_p *new_head = head->next;
  free(head);
  return new_head;
}      



struct stack_t *CreateStackT(int max_len){
    struct stack_t *s = NULL;
    s = malloc(sizeof(struct stack_t));
    s->len=0; 
    s->max_len = max_len; 
    s->tab = malloc(max_len * sizeof(int));
    return s; 
}

int Push(struct stack_t *s, int elt){
    if(IsFull(s))
        return(-2);
    s->tab[s->len] = elt;
    s->len+=1;
    return 0;
}

int Pop(struct stack_t *s){
    if(IsEmpty(s) )
    return (-1);
    
    s->len-=1;
    return 0;
}

int Head(struct stack_t *s){
    if(IsEmpty(s))
    return(-1);
    
    return (s->tab[(s->len - 1)]);
}

int IsFull(struct stack_t *s){
    return(s->len == s->max_len);
}

int IsEmpty(struct stack_t *s){
    return(s->len == 0);
}

int Length(struct stack_t *s){
    return s->len;
}

int Clear(struct stack_t *s){
    /*int size = len;
    s->len = 0;
    return size*/
    
    int temp=0;
    while(!IsEmpty(s)){
        Pop(s);
        temp++;
    }
    return temp;
    
}

void Delete(struct stack_t *s){
    free(s->tab);  // clear(s)
    free(s);
}

