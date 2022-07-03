#include <stdio.h>
#include <stdlib.h>

//typedef struct node *treePointer;
typedef struct node {
    int data;
    int visit;
    struct node* leftChild;
    struct node* rightChild;
} node ;

void createnode(node *ptr, int n);
void preorder(node* ptr);
void push(node* stack[], node* ptr, int* top);
void iterInorder(node* ptr);
void iterPreorder(node* ptr);
void iterPostorder(node* ptr);

node* pop(node* stack[], int* top);

int main(void){

    node *testtree = (node*)malloc(sizeof(node));

    createnode(testtree, 3);
    preorder(testtree);
    printf("\n");
    iterPostorder(testtree);

    return 0;
}

void createnode(node *ptr, int n){

    if(n == 0){
        ptr->data = n;
        ptr->visit = 0;
        ptr->leftChild = NULL;
        ptr->rightChild = NULL;
        return;
    } else {
        ptr->leftChild = (node*)malloc(sizeof(node));
        ptr->rightChild = (node*)malloc(sizeof(node));
        ptr->data = n;
        createnode(ptr->leftChild, n-1);
        createnode(ptr->rightChild, n-1);
    }

}

void preorder(node* ptr){

    if(ptr){

        preorder(ptr->leftChild);
        preorder(ptr->rightChild);
        printf("%d" , ptr->data);
    }
}

void iterInorder(node* ptr){

    int top = -1;
    node* stack[50];
    for(;;){
        for(;ptr; ptr = ptr->leftChild){
            push(stack, ptr, &top);
        }
        ptr = pop(stack, &top);
        if(!ptr) break;
        printf("%d", ptr->data);
        ptr = ptr->rightChild;
    }
}

void iterPreorder(node* ptr){

    int top = -1;
    node* stack[50];
    for(;;){
        for(;ptr; ptr = ptr->leftChild){
            printf("%d", ptr->data);
            push(stack, ptr, &top);
        }
        ptr = pop(stack, &top);
        if(!ptr) break;
        ptr = ptr->rightChild;
    }
}

void iterPostorder(node* ptr){

    int top = -1;
    node* stack[50];
    for(;;){
        for(;ptr; ptr = ptr->leftChild){

            
            push(stack, ptr, &top);
            
        }
        //printf("%d", ptr->data);
        ptr = pop(stack, &top);
        if(!ptr) break;
        printf("%d", ptr->data);

        ptr = ptr->rightChild;
        printf("%d", ptr->data);
    }
}

void push(node** stack, node* ptr, int* top){

    (*top)++;
    stack[*top] = ptr;
}


node* pop(node* stack[], int* top){

    node* result;
    result = stack[*top];
    stack[*top] = NULL;
    (*top)--;
    return result;
}
