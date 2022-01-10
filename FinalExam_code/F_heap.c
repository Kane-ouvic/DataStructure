#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

void insertion(fib_heap *H, node*new, int val, int num){

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
        return NULL;
    } else {
        return H->min;
    }
}

int cal_degree(int n){

    int count = 0;
    while(n > 0){
        n /= 2;
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
        H->n--;
        return temp;
    }
    return H->min;
}

void cut(fib_heap *H, node *node_decrease, node *parent_node){

    node *temp_parent_check;
    if(node_decrease == node_decrease->right_sibling){
        parent_node->child = NULL;
    }
    node_decrease->left_sibling->right_sibling = node_decrease->right_sibling;
    node_decrease->right_sibling->left_sibling = node_decrease->left_sibling;
    if(node_decrease == parent_node->child){
        parent_node->child = node_decrease->right_sibling;
    }
    (parent_node->degree)--;
    node_decrease->left_sibling = node_decrease;
    node_decrease->right_sibling = node_decrease;
    H->min->left_sibling->right_sibling = node_decrease;
    node_decrease->right_sibling = H->min;
    node_decrease->left_sibling = H->min->left_sibling;
    H->min->left_sibling = node_decrease;

    node_decrease->parent = NULL;
    node_decrease->mark = false;
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

void decrease_key(fib_heap *H, node *node_decrease, int new_key){

    node* parent_node;
    if(H == NULL){

        return;
    }
    if(node_decrease == NULL){
       
    } else {
        if(node_decrease->key < new_key){
          
        } else {
            node_decrease->key = new_key;
            parent_node = node_decrease->parent;
            if((parent_node != NULL) && (node_decrease->key < parent_node->key)){
                cut(H, node_decrease, parent_node);
                cascading_cut(H, parent_node);
            }
            if(node_decrease->key < H->min->key){
                H->min = node_decrease;
            }
        }
    }
}

void find_node(fib_heap *H, node *n, int key, int new_key){

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
    if(find_use->right_sibling->visited != true){
        find_node(H, find_use->right_sibling, key, new_key);
    }
    find_use->visited = false;
}

void deleteNode(fib_heap *H, int dec_key){

    node *p = NULL;
    find_node(H, H->min, dec_key, -5000000);
    p = extract_min(H);
}