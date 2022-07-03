#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{

    int data;
    struct node* leftChild;
    struct node* rightChild;
} node;

int search(int arr[], int start, int end, int value);
struct node* newNode(int data);
struct node* buildTreePreI(int in[], int pre[], int inStart, int inEnd);
struct node* buildTreePostI(int in[], int post[], int inStart, int inEnd, int *pIndex);
struct node* constructPostI(int in[], int post[], int n);
void Inorder(struct node* nide);
void Preorder(struct node* node);
void Postorder(struct node* node);
void reset1Darr(int arr[], int m);

int preIndex = 0;
int postIndex = 0;

int main(void){

    int preorder[1000];
    int postorder[1000];
    int inorder[1000];

    int times;
    scanf("%d" ,&times);
    for(int i = 0; i < times; i++){
        char input_category[20];
        int m;
        scanf("%s" ,input_category);
        if(strcmp(input_category, "preorder-inorder") == 0){
            scanf("%d" ,&m);
            for(int j = 0; j < m; j++){
                scanf("%d" ,&preorder[j]);
            }
            for(int j = 0; j < m; j++){
                scanf("%d" ,&inorder[j]);
            }
            int len = sizeof(inorder)/sizeof(inorder[0]);
            struct node* root = buildTreePreI(inorder, preorder, 0, m-1);
            Postorder(root);
            printf("\n");
        } else if(strcmp(input_category, "postorder-inorder") == 0){
            scanf("%d" ,&m);
            for(int j = 0; j < m; j++){
                scanf("%d" ,&postorder[j]);
            }
            for(int j = 0; j < m; j++){
                scanf("%d" ,&inorder[j]);
            }
            struct node* root = constructPostI(inorder, postorder, m-1);
            Preorder(root);
            printf("\n");
        }
        reset1Darr(inorder, m);
        reset1Darr(preorder, m);
        reset1Darr(postorder, m);
        preIndex = 0;
        postIndex = 0;
    }

    return 0;
}

struct node* buildTreePreI(int in[], int pre[], int inStart, int inEnd){

    if(inStart > inEnd){
        return NULL;
    }
    struct node* tNode = newNode(pre[preIndex++]);
    if(inStart == inEnd){
        return tNode;
    }
    int inIndex = search(in, inStart, inEnd, tNode->data);
    tNode->leftChild = buildTreePreI(in, pre, inStart, inIndex-1);
    tNode->rightChild = buildTreePreI(in, pre, inIndex + 1, inEnd);

    return tNode;
}

struct node* constructPostI(int in[], int post[], int n){

    int *pIndex = &n;
    return buildTreePostI(in, post, 0, n, pIndex);
}

struct node* buildTreePostI(int in[], int post[], int inStart, int inEnd, int *pIndex){

    if(inStart > inEnd){
        return NULL;
    }
    struct node* tNode = newNode(post[(*pIndex)--]);

    int i;
    for(i = inStart; i <= inEnd; i++){
        if(in[i] == tNode->data){
            break;
        }
    }

    tNode->rightChild = buildTreePostI(in, post, i + 1, inEnd, pIndex);
    tNode->leftChild = buildTreePostI(in, post, inStart, i-1, pIndex);

    return tNode;
}

int search(int arr[], int start, int end, int value){

    int i;
    for(i = start; i <= end; i++){
        if(arr[i] == value){
            return i;
        }
    }
    return 0;
}

struct node* newNode(int data){

    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->leftChild = NULL;
    temp->rightChild = NULL;

    return temp;
}

void Inorder(struct node* node)
{
    if (node == NULL)
        return;
 
    Inorder(node->leftChild);
    printf("%d ", node->data);
    Inorder(node->rightChild);
}

void Postorder(struct node* node)
{
    if (node == NULL)
        return;

    Postorder(node->leftChild);
    Postorder(node->rightChild);
    printf("%d ", node->data);
}

void Preorder(struct node* node)
{
    if (node == NULL)
        return;

    printf("%d ", node->data);    
    Preorder(node->leftChild);
    Preorder(node->rightChild);
}

void reset1Darr(int arr[], int m){

    for(int i = 0; i < m; i++){
        arr[i] = 0;
    }
}
