#include <stdio.h>
#include <stdlib.h>

typedef struct node{

    int data;
    struct node* leftChild;
    struct node* rightChild;

}node;

struct node* newNode(int data);
struct node* constructTreeUtil(int pre[], int* preIndex, int low, int high, int size);
struct node* constructTree(int pre[], int size);
void Preorder(struct node* node);
void Postorder(struct node* node);


int main(void){

    int pre[] = {1, 2, 3, -1, -1, 4, -1, -1, 5, 6, -1, 7, -1, -1, 8, -1, -1};
    int size = sizeof(pre)/sizeof(pre[0]);

    struct node* root = constructTree(pre, size);

    Preorder(root);
    printf("\n");
    Postorder(root);

    return 0;
}

struct node* newNode(int data){

    struct node* node = (struct node*)malloc(sizeof(struct node));
    node->data = data;
    node->leftChild = NULL;
    node->rightChild = NULL;
    return node;

}

struct node* constructTreeUtil(int pre[], int* preIndex, int low, int high, int size){

    if(*preIndex >= size || low > high){
        return NULL;
    }

    struct node* root = newNode(pre[*preIndex]);
    (*preIndex)++;
    if(low == high){
        return root;
    }
    
    int i = 0;
    for(i = low; i <= high; i++){
        if(pre[i] > root->data) break;
    }

    root->leftChild = constructTreeUtil(pre, preIndex, *preIndex, i-1, size);
    root->rightChild = constructTreeUtil(pre, preIndex, i, high, size);
    return root;


}

struct node* constructTree(int pre[], int size){

    int preIndex = 0;
    return constructTreeUtil(pre, &preIndex, 0, size-1, size);
}

void Preorder(struct node* node){

    if(node == NULL){
        return;
    } else {
        if(node->data != -1) printf("%d" ,node->data);
        Preorder(node->leftChild);
        Preorder(node->rightChild);
    }
}

void Postorder(struct node* node){

    if(node == NULL){
        return;
    } else {
        Postorder(node->leftChild);
        if(node->data != -1) printf("%d" ,node->data);
        Postorder(node->rightChild);
    }
}