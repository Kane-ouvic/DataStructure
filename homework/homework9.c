#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    int data;
    struct node* parent;
    struct node* leftChild;
    struct node* rightChild;
} node;

struct node* newNode(int data);
struct node* generateTree(int* array, int times);
void iterPreorder(node* ptr);
void iterPostorder(node* ptr);
void push(node** stack, node* ptr, int* top);
struct node* pop(node* stack[], int* top);
struct node* getTop(node* stack[], int* top);

int main(void){

    int numbers;
    node* input;
    scanf("%d" ,&numbers);
    int array[numbers];
    for(int i = 0; i < numbers; i++){
        scanf("%d" ,&array[i]);
    }
    input = generateTree(array, numbers);
    iterPreorder(input);
    printf("\n");
    iterPostorder(input);
    return 0;
}

struct node* newNode(int data){

    struct node* temp = (struct node*)malloc(sizeof(node));
    temp->data = data;
    temp->leftChild = NULL;
    temp->rightChild = NULL;
    temp->parent = NULL;
    return temp;

}

struct node* generateTree(int* array, int times){

    node* top = newNode(array[0]);
    node* ptr = top;

    for(int i = 1; i < times; i++){
        if(ptr->leftChild == NULL){
            ptr->leftChild = newNode(array[i]);
            ptr->leftChild->parent = ptr;
            if(ptr->leftChild->data != -1) ptr = ptr->leftChild;
        } else if(ptr->rightChild == NULL){
            ptr->rightChild = newNode(array[i]);
            ptr->rightChild->parent = ptr;
            if(ptr->rightChild->data != -1) ptr = ptr->rightChild;
        } else {
            while(ptr->rightChild != NULL){
                ptr = ptr->parent;
            }
            ptr->rightChild = newNode(array[i]);
            ptr->rightChild->parent = ptr;
            if(ptr->rightChild->data != -1) ptr = ptr->rightChild;
        }
    }

    return top;
}

void iterPreorder(node* ptr){

    int top = -1;
    node* stack[50];
    node* temp;
    for(;;){
        for(;ptr ; ptr = ptr->leftChild){
            if(ptr->data != -1) printf("%d " ,ptr->data);
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
    node* temp;

    do{
        while(ptr){
            if(ptr->rightChild){
                push(stack, ptr->rightChild, &top);
            }
            push(stack, ptr, &top);
            ptr = ptr->leftChild;
        }
        ptr = pop(stack, &top);
        if(ptr->rightChild && getTop(stack, &top) == ptr->rightChild){
            pop(stack, &top);
            push(stack, ptr, &top);
            ptr = ptr->rightChild;
        } else {
            if(ptr->data != -1) printf("%d " ,ptr->data);
            ptr = NULL;
        }
    } while(top > -1);
}

void push(node** stack, node* ptr, int* top){

    (*top)++;
    stack[*top] = ptr;
}

struct node* pop(node* stack[], int* top){

    node* result;
    result = stack[*top];
    stack[*top] = NULL;
    (*top)--;
    return result;
}

struct node* getTop(node* stack[], int* top){

    node* result;
    result = stack[*top];
    return result;
}