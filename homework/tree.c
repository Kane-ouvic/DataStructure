#include <stdio.h>
#include <stdlib.h>

typedef struct node{

    int data;
    struct node* parent;
    struct node* left;
    struct node* right;
    
} node;

struct node* createNode(int data);
struct node* generateTree(int* array, int times);
void Preorder(struct node* node);
void Postorder(struct node* node);

int main(void){

    int numbers;
    node* test;
    scanf("%d" ,&numbers);
    int array[numbers];
    for(int i = 0; i < numbers; i++){
        scanf("%d",&array[i]);
    }

    test = generateTree(array, numbers);
    printf("\n");
    Preorder(test);
    printf("\n");
    Postorder(test);

    return 0;
}

struct node* createNode(int data){

    struct node* temp = (struct node*)malloc(sizeof(node));

    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    temp->parent = NULL;
    //printf("---3");
    return temp;
}

struct node* generateTree(int* array, int times){

    //printf("---1");
    node* top = createNode(array[0]);
    node* ptr = top;
    //printf("---2");
    int counter = 0;

    for(int i = 1; i < times; i++){
        if(ptr->left == NULL){
            printf("--------------1 %d\n" ,i);
            ptr->left = createNode(array[i]);
            ptr->left->parent = ptr;
            if(ptr->left->data != -1) ptr = ptr->left;
            //break;
        } else if(ptr->right == NULL){
            printf("--------------2 %d\n" ,i);
            ptr->right = createNode(array[i]);
            ptr->right->parent = ptr;
            if(ptr->right->data != -1) ptr = ptr->right;
            //break;
        } else {
            while(ptr->right != NULL){
                printf("--------------3 %d\n" ,i);
                ptr = ptr->parent;
                
            }
            ptr->right = createNode(array[i]);
            ptr->right->parent = ptr;
            if(ptr->right->data != -1) ptr = ptr->right;
        }
    }
    return top;
}

void Preorder(struct node* node){

    if(node == NULL){
        return;
    } else {
        if(node->data != -1) printf("%d" ,node->data);
        Preorder(node->left);
        Preorder(node->right);
    }
}

void Postorder(struct node* node){

    if(node == NULL){
        return;
    } else {
        Postorder(node->left);
        Postorder(node->right);
        if(node->data != -1) printf("%d" ,node->data);
        
    }
}
