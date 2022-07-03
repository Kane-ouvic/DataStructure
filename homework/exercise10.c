#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* parent;
    struct node* leftChild;
    struct node* rightChild;
} node;

struct node* newNode(int data);
struct node* generateTree(int* array, int times);
void Preorder(struct node* node);
void Inorder(struct node* node);
void swapTree(struct node* node);

int main(void){

    int numbers;
    node* input;
    scanf("%d" ,&numbers);
    int array[numbers];
    for(int i = 0; i < numbers; i++){
        scanf("%d" ,&array[i]);
    }
    input = generateTree(array, numbers);
    swapTree(input);
    Preorder(input);
    printf("\n");
    Inorder(input);

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

void Preorder(struct node* node){

    if(node == NULL){
        return;
    }  else {
        if(node->data != -1) printf("%d " ,node->data);
        Preorder(node->leftChild);
        Preorder(node->rightChild);
    }
}

void Inorder(struct node* node){

    if(node == NULL){
        return;
    } else {
        Inorder(node->leftChild);
        if(node->data != -1) printf("%d " ,node->data);
        Inorder(node->rightChild);
    }
}

void swapTree(struct node* node){

    if(node == NULL) return;
    struct node* temp = node->leftChild;
    node->leftChild = node->rightChild;
    node->rightChild = temp;
    swapTree(node->leftChild);
    swapTree(node->rightChild);

}
