#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

struct queue_node {
    int val;
    struct queue_node* next;
};

struct queue {
    struct queue_node* front;
    struct queue_node* rear;
};

void enqueue(struct queue* q, int element) {
    struct queue_node* new_node = malloc(sizeof(struct queue_node));
    new_node->element = element;
    new_node->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = new_node;
    } else {
        q->rear->next = new_node;
        q->rear = new_node;
    }
}

int dequeue(struct queue* q) {
    if (q->front == NULL) 
        return -1;
    struct queue_node* temp = q->front;
    q->front = q->front->next;
    
    if (q->front == NULL) 
        q->rear = NULL;
    struct node* val = temp->val;
    free(temp);
    return val;
}
