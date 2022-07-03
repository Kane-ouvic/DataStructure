#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

typedef struct node{

    int key;
    int degree;
    int value;
    struct node* left_sibling;
    struct node* right_sibling;
    struct node* parent;
    struct node* child;
    bool mark;
    bool visited;

} node;

typedef struct fibanocci_heap{

    int n;
    node* min;
    int phi;
    int degree;

} fib_heap;

fib_heap* make_fib_heap();
void insertion(fib_heap *H, node *new, int val, int num);
node* extract_min(fib_heap *H);
void consolidate(fib_heap *H);
void fib_heap_link(fib_heap *H, node *y, node *x);
node* find_min_node(fib_heap *H);
void decrease_key(fib_heap *H, node *node, int key);
void cut(fib_heap *H, node *node_to_be_decrease, node *parent_node);
void cascading_cut(fib_heap *H, node *parent_node);
void delete_node(fib_heap *H, int dec_key);

fib_heap *make_fib_heap(){

    fib_heap *H;
    H = (fib_heap *)malloc(sizeof(fib_heap));
    H->n = 0;
    H->min = NULL;
    H->phi = 0;
    H->degree = 0;
    return H;
}

void print_heap(node *n){

    node *x;
    for(x = n; ; x = x->right_sibling){
        if(x->child == NULL){
            printf("node with no child (%d) \n" ,x->key);
        } else {
            printf("NODE(%d) with child(%d)\n" ,x->key ,x->child->key);
            print_heap(x->child);
        }
        if(x->right_sibling == n){
            break;
        }
    }
}

void insertion(fib_heap *H, node *new, int val, int num){

    new = (node *)malloc(sizeof(node));
    new->key = val;
    new->degree = 0;
    new->value = num;
    new->mark = false;
    new->parent = NULL;
    new->child = NULL;
    new->visited = false;
    new->left_sibling = new;
    new->right_sibling = new;
    if(H->min == NULL){
        H->min = new;
    } else {
        H->min->left_sibling->right_sibling = new;
        new->right_sibling = H->min;
        new->left_sibling = H->min->left_sibling;
        H->min->left_sibling = new;
        if(new->key < H->min->key){
            H->min = new;
        }
    }
    (H->n)++;
}

node* find_min_node(fib_heap *H){

    if(H == NULL){
        printf("\n Fibonacci heap not created \n");
        return NULL;
    } else {
        return H->min;
    }
}

fib_heap* unionHeap(fib_heap *H1, fib_heap *H2){

    fib_heap *Hnew;
    Hnew = make_fib_heap();
    Hnew->min = H1->min;

    node* temp1;
    node* temp2;
    temp1 = Hnew->min->right_sibling;
    temp2 = H2->min->left_sibling;

    Hnew->min->right_sibling->left_sibling = H2->min->left_sibling;
    Hnew->min->right_sibling = H2->min;
    H2->min->left_sibling = Hnew->min;
    temp2->right_sibling = temp1;

    if((H1->min == NULL) || (H2->min != NULL && H2->min->key < H1->min->key)){
        Hnew->min = H2->min;
    }
    Hnew->n = H1->n + H2->n;
    return Hnew;

}

int cal_degree(int n){

    int count = 0;
    while(n > 0){
        n = n / 2;
        count++;
    }
    return count;
}

void consolidate(fib_heap *H){
    
    int degree, i, d;
    degree = cal_degree(H->n);
    node* A[degree], *x, *y, *z;
    for(i = 0; i <= degree; i++){
        A[i] = NULL;
    }
    x = H->min;
    do{
        d = x->degree;
        while(A[d] != NULL){
            y = A[d];
            if(x->key > y->key){
                node* exchange_help;
                exchange_help = x;
                x = y;
                y = exchange_help;
            }
            if(y == H->min){
                H->min = x;
            }
            fib_heap_link(H, y, x);
            if(y->right_sibling == x){
                H->min = x;
            }
            A[d] = NULL;
            d++;
        }
        A[d] = x;
        x = x->right_sibling;
    } while(x != H->min);

    H->min = NULL;
    for(i = 0; i < degree; i++){
        if(A[i] != NULL){
            A[i]->left_sibling = A[i];
            A[i]->right_sibling = A[i];
            if(H->min == NULL){
                H->min = A[i];
            } else {
                H->min->left_sibling->right_sibling = A[i];
                A[i]->right_sibling = H->min;
                A[i]->left_sibling = H->min->left_sibling;
                H->min->left_sibling = A[i];
                if(A[i]->key < H->min->key){
                    H->min = A[i];
                }
            }
            if(H->min == NULL){
                H->min = A[i];
            } else if(A[i]->key < H->min->key){
                H->min = A[i];
            }
        }
    }
}

void fib_heap_link(fib_heap *H, node *y, node *x){

    y->right_sibling->left_sibling = y->left_sibling;
    y->left_sibling->right_sibling = y->right_sibling;

    if(x->right_sibling == x){
        H->min = x;
    }
    y->left_sibling = y;
    y->right_sibling = y;
    y->parent = x;

    if(x->child == NULL){
        x->child = y;
    }

    y->right_sibling = x->child;
    y->left_sibling = x->child->left_sibling;
    x->child->left_sibling->right_sibling = y;
    x->child->left_sibling = y;
    if((y->key) < (x->child->key)){
        x->child = y;
    }
    (x->degree)++;
}

node* extract_min(fib_heap *H){

    if(H->min == NULL){
        printf("\n the heap is empty");
    } else {
        node* temp = H->min;
        node* pntr;
        pntr = temp;
        node* x = NULL;
        if(temp->child != NULL){
            x = temp->child;
            do{
                pntr = x->right_sibling;
                (H->min->left_sibling)->right_sibling = x;
                x->right_sibling = H->min;
                x->left_sibling = H->min->left_sibling;
                H->min->left_sibling = x;
                if(x->key < H->min->key){
                    H->min = x;
                }
                x->parent = NULL;
                x = pntr;
            } while(pntr != temp->child);
        }
        (temp->left_sibling)->right_sibling = temp->right_sibling;
        (temp->right_sibling)->left_sibling = temp->left_sibling;
        H->min = temp->right_sibling;

        if(temp == temp->right_sibling && temp->child == NULL){
            H->min = NULL;
        } else {
            H->min = temp->right_sibling;
            consolidate(H);
        }
        H->n = H->n - 1;
        return temp;
    }
    return H->min;
}

void cut(fib_heap *H, node *node_to_be_decrease, node *parent_node){

    node *temp_parent_check;
    if(node_to_be_decrease == node_to_be_decrease->right_sibling){
        parent_node->child = NULL;
    }
    node_to_be_decrease->left_sibling->right_sibling = node_to_be_decrease->right_sibling;
    node_to_be_decrease->right_sibling->left_sibling = node_to_be_decrease->left_sibling;
    if(node_to_be_decrease == parent_node->child){
        parent_node->child = node_to_be_decrease->right_sibling;
    }
    (parent_node->degree)--;
    node_to_be_decrease->left_sibling = node_to_be_decrease;
    node_to_be_decrease->right_sibling = node_to_be_decrease;
    H->min->left_sibling->right_sibling = node_to_be_decrease;
    node_to_be_decrease->right_sibling = H->min;
    node_to_be_decrease->left_sibling = H->min->left_sibling;
    H->min->left_sibling = node_to_be_decrease;

    node_to_be_decrease->parent = NULL;
    node_to_be_decrease->mark = false;
}

void cascading_cut(fib_heap *H, node *parent_node){

    node* aux;
    aux = parent_node->parent;
    if(aux != NULL){
        if(parent_node->mark == false){
            parent_node->mark = true;
        } else {
            cut(H, parent_node, aux);
            cascading_cut(H, aux);
        }
    }
}

void decrease_key(fib_heap *H, node *node_to_be_decrease, int new_key){

    node* parent_node;
    if(H == NULL){
       // printf("FIbonacci heap not created ");
        return;
    }
    if(node_to_be_decrease == NULL){
       // printf("Node is not in the heap");
    } else {
        if(node_to_be_decrease->key < new_key){
          //  printf("\n Invalid new key for decrease key operation \n");
        } else {
            node_to_be_decrease->key = new_key;
            parent_node = node_to_be_decrease->parent;
            if((parent_node != NULL) && (node_to_be_decrease->key < parent_node->key)){
            //    printf("\n cut called");
                cut(H, node_to_be_decrease, parent_node);
            //    printf("\n cascading cut called");
                cascading_cut(H, parent_node);
            }
            if(node_to_be_decrease->key < H->min->key){
                H->min = node_to_be_decrease;
            }
        }
    }
}

void* find_node(fib_heap *H, node *n, int key, int new_key){

    node *find_use = n;
    node *f = NULL;
    find_use->visited = true;
    if(find_use->key == key){
        find_use->visited = false;
        f = find_use;
        decrease_key(H, f, new_key);
    }
    if(find_use->child != NULL){
        find_node(H, find_use->child, key, new_key);
    }
    if((find_use->right_sibling->visited != true)){
        find_node(H, find_use->right_sibling, key, new_key);
    }

    find_use->visited = false;
}

fib_heap* insertion_procedure(){

    fib_heap *temp;
    int no_of_nodes, ele, i;
    node *new_node;
    temp = (fib_heap *)malloc(sizeof(fib_heap));
    temp = NULL;
    if(temp == NULL){
        temp = make_fib_heap();
    }
    printf("\n enter number of nodes to be insert = ");
    scanf("%d", &no_of_nodes);
    for (i = 1; i <= no_of_nodes; i++) {
        printf("\n node %d and its key value = ", i);
        scanf("%d", &ele);
        //insertion(temp, new_node, ele);
    }
    return temp;
}

void Delete_Node(fib_heap *H, int dec_key) {
  node *p = NULL;
  find_node(H, H->min, dec_key, -500000);
  p = extract_min(H);
  if (p != NULL)
    printf("\n Node deleted");
  else
    printf("\n Node not deleted:some error");
}

int main(int argc, char **argv) {
    node *new_node, *min_node, *extracted_min, *node_to_be_decrease, *find_use;
    fib_heap *heap, *h1, *h2;
    int operation_no, new_key, dec_key, ele, i, no_of_nodes;
    heap = make_fib_heap();

    char input_str[10];
    int val1;
    int val2;
    int val3;

    while(1){
        scanf("%s" ,input_str);

        if(strcmp(input_str, "insert") == 0){

            scanf("%d %d" ,&val1 ,&val2);
            insertion(heap, new_node, val1, val2);

        } else if(strcmp(input_str, "extract") == 0){

            extracted_min = extract_min(heap);
            printf("(%d)%d\n", extracted_min->key ,extracted_min->value);
            //printf("\n Updated heap: \n");
            //print_heap(heap->min);


        } else if(strcmp(input_str, "delete") == 0){

            scanf("%d %d" ,&val1 ,&val2);
            printf("-------------\n");
            Delete_Node(heap, val1);

        } else if(strcmp(input_str, "decrease") == 0){

            scanf("%d %d %d" ,&val1 ,&val2, &val3);
            find_use = heap->min;
            find_node(heap, find_use, val1, val1-val3);
            
        } else if(strcmp(input_str, "quit") == 0){
            break;
        }
    }


/*
  while (1) {
    printf(" \n Operations \n 1. Create Fibonacci heap \n 2. Insert nodes into fibonacci heap \n 3. Find min \n 4. Union \n 5. Extract min \n 6. Decrease key \n 7.Delete node \n 8. print heap \n 9. exit \n enter operation_no = ");
    scanf("%d", &operation_no);

    switch (operation_no) {
      case 1:
        heap = make_fib_heap();
        break;

      case 2:
        if (heap == NULL) {
          heap = make_fib_heap();
        }
        printf(" enter number of nodes to be insert = ");
        scanf("%d", &no_of_nodes);
        for (i = 1; i <= no_of_nodes; i++) {
          printf("\n node %d and its key value = ", i);
          scanf("%d", &ele);
          //insertion(heap, new_node, ele);
        }
        break;

      case 3:
        min_node = find_min_node(heap);
        if (min_node == NULL)
          printf("No minimum value");
        else
          printf("\n min value = %d", min_node->key);
        break;

      case 4:
        if (heap == NULL) {
          printf("\n no FIbonacci heap created \n ");
          break;
        }
        h1 = insertion_procedure();
        heap = unionHeap(heap, h1);
        printf("Unified Heap:\n");
        print_heap(heap->min);
        break;

      case 5:
        if (heap == NULL)
          printf("Empty Fibonacci heap");
        else {
          extracted_min = extract_min(heap);
          printf("\n min value = %d", extracted_min->key);
          printf("\n Updated heap: \n");
          print_heap(heap->min);
        }
        break;

      case 6:
        if (heap == NULL)
          printf("Fibonacci heap is empty");
        else {
          printf(" \n node to be decreased = ");
          scanf("%d", &dec_key);
          printf(" \n enter the new key = ");
          scanf("%d", &new_key);
          find_use = heap->min;
          find_node(heap, find_use, dec_key, new_key);
          printf("\n Key decreased- Corresponding heap:\n");
          print_heap(heap->min);
        }
        break;
      case 7:
        if (heap == NULL)
          printf("Fibonacci heap is empty");
        else {
          printf(" \n Enter node key to be deleted = ");
          scanf("%d", &dec_key);
          Delete_Node(heap, dec_key);
          printf("\n Node Deleted- Corresponding heap:\n");
          print_heap(heap->min);
          break;
        }
      case 8:
        print_heap(heap->min);
        break;

      case 9:
        free(new_node);
        free(heap);
        exit(0);

      default:
        printf("Invalid choice ");
    }
  }*/
}