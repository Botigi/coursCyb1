void print_table_BFS( int tab[] , int len)
{
    for (int i = 0 ; i < len; i++){
        if (tab[i] !=NULL ){  // remplacer par -1 ou NULL en fonction de l'implementation du tableau
            printf(tab[i]);
         }
    }
}                

void pointer_BFS(struct node *_node)
{
    if (_node == NULL)
        return;
_
    struct fifo *_fifo = fifoinit();
    fifo_push(_fifo, _node);

    while (!is_empty(_fifo)) {
        struct node *current = fifo_pop(_fifo);
        printf("%d\n", current->key);

        if (current->left != NULL)
            fifo_push(_fifo, current->left);

        if (current->right != NULL)
            fifo_push(_fifo, current->right);
    }
}

///correction:
void BFS(struct node *root; struct queue *mafile)
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
    }    }
 }  

 void DFS_pointeur(node *root)
{  
  if (root == NULL)
    return;
  printf("%d\n", root->key); // prefixe
  DFS(root->left_child);
 
  printf("%d\n", root->key); // infixe
  
  DFS(root->right_child);
 
  printf("%d\n", root->key); // suffixe
  
}


void print_table_BFS( int tab[] , int len)
{
    for (int i = 0 ; i < len; i++){
        if (tab[i] !=NULL ){  // remplacer par -1 ou NULL en fonction de l'implementation du tableau
            printf(tab[i]);
         }
    }
}    

void pointer_BFS(struct node *_node)
{
    if (_node == NULL)
        return;
_
    struct fifo *_fifo = fifoinit();
    fifo_push(_fifo, _node);

    while (!is_empty(_fifo)) {
        struct node *current = fifo_pop(_fifo);
        printf("%d\n", current->key);

        if (current->left != NULL)
            fifo_push(_fifo, current->left);

        if (current->right != NULL)
            fifo_push(_fifo, current->right);
    }
}

///correction:
void BFS(struct node *root; struct queue *mafile)
{
  if (root != NULL) {
    enqueue(mafile, root);
  }
  while(!=isEmpty(mafile)) {  
    struct node *current = dequeue(mafile);
    printf("%d\n", current -> key);
    if (current -> left_child != NULL) {
      enqueue(mafile, current -> left_child);
    }
  if (current -> right_child != NULL) {
    enqueue(mafile, current -> right_child);
    }    }
}  

void DFS_tableau(int tab[], int len, stack *maPile)
{
    if (tab[] == NULL) { // Changer NULL en -1 en fonction de l'implémentation du tableau
        push(maPile, 1);
    }
    int i = 1;
    while (!isEmpty(maPile)) {
        i = pop(maPile);
        printf("%d\n", tab[i - 1]); // On met le -1 car le tableau C commence à 0 mais le tableau des binaires commence à 1

        if (tab[(2 * i + 1) - 1] != -1) { // On met le -1 car le tableau C commence à 0 mais le tableau des binaires commence à 1
            push(maPile, 2 * i + 1);
        }

        if (tab[(2 * i) - 1] != -1) { // On met le -1 car le tableau C commence à 0 mais le tableau des binaires commence à 1
            push(maPile, 2 * i);
        }
        
    }
}

void DFS_left_pointer(int [] tree, int size, struct stackep * maPile) {
    if (size !=0) {
        push(maPile, 1);
        while(! isEmpty(maPile){
          int pos = pop(maPile);
          printf("%d\n", tree [pos-1];
          if ( 2*pos+1 <=size){
              push(maPile,2*pos+1);
          }
          if (2*pos <= size) {
              push(maPile, 2*pos);
          }
        }
    }                                      
                                                                                                                        
    
    printf("%d\n", node->key);
      
    DFS_left_pointer(node->left);
    DFS_left_pointer(node->right);
}

struct node {
    int key;
      struct node*left_child;
      struct node*right_child;   
  }
  
int height_tree(struct node *node)
  {
    if(node->key == NULL)
      return;
  
    int left_height = height_tree(node->left_child);
    int right_height = height_tree(node->right_child);
   
   if (left_height>right_height)
      return 1 + left_height;
   else
      return 1 + right_height;
        
  }

int findDepthRuben(struct node *node, int key, int depth)
{
    if (node == NULL)
      return -1;
    if (node -> data == key)
      return depth;
    int leftDepth = findDepth(node->left_child, key, depth + 1);
    if (depth != -1)
      return leftDepth;
    return findDepth(node->right_child, key, depth + 1);       
}  

int findDepthBarrot(struct node *root, int value)
{
  if (root == NULL) return -1;
  if (root->key == value) return 0;

  int left_depth = findDepthBarrot(root->left_child, value);
  if (left_depth != -1) return 1 + left_depth;
  
  int right_depth = findDepthBarrot(root->right_child, value);
  if (right_depth != -1) return 1 + right_depth;
 
  return -1;  
}