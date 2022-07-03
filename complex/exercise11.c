#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct threadedTree{

    int data;
    struct threadedTree* leftChild;
    struct threadedTree* rightChild;
    int leftThread;
    int rightThread;

} threadedTree ;

struct threadedTree* insuc(threadedTree* tree);
struct threadedTree* getNode(int data);
struct threadedTree* searchNode(threadedTree* list[], int m, int data);
void insertRight(threadedTree* parent, threadedTree* child);
void insertLeft(threadedTree* parent, threadedTree* child);
void inorder(threadedTree* tree);
void inorder_ex();
void inorder_ex2(threadedTree* ptr);

struct threadedTree* top;

int main(void){
    
    int m, n;
    //int count;
    scanf("%d %d" ,&m ,&n);

    struct threadedTree* list[1000];
    top = getNode(n);
    top->leftChild = top;
    top->rightChild = top;

    list[0] = top;

    for(int i = 0; i < m ; i++){
        char input_category[10];
        int inputP, inputC;
        threadedTree* parent;
        threadedTree* child;
        scanf("%d %s %d" ,&inputP ,input_category, &inputC);
        if(strcmp(input_category, "left") == 0){
            parent = searchNode(list, m, inputP);
            child = getNode(inputC);
            //child->leftChild = top;
            //child->rightChild = top;
            //printf("-------------1\n");
            insertLeft(parent, child);
            list[i+1] = child;

        } else if(strcmp(input_category, "right") == 0){
            parent = searchNode(list, m, inputP);
            child = getNode(inputC);
            //printf("-------------2\n");
            insertRight(parent, child);
            //printf("-------------3\n");
            list[i+1] = child;
        }
    }
    //top = top->leftChild;
    //top = top->leftChild;
    //top = top->leftChild;
    inorder_ex2(top);


    return 0;
}

struct threadedTree* searchNode(threadedTree* list[], int m, int data){

    for(int i = 0; i < m; i++){
        if(list[i]->data == data){
            //printf("%d\n" ,list[i]->data);
            return list[i];
        }
    }
    return list[0];
}

struct threadedTree* getNode(int data){

    struct threadedTree* temp = (struct threadedTree*)malloc(sizeof(struct threadedTree));
    temp->data = data;
    temp->rightThread = 0;
    temp->leftThread = 0;
    temp->leftChild = NULL;
    temp->rightChild = NULL;
    return temp;

}

struct threadedTree* insuc(threadedTree* tree){

    threadedTree* temp = tree->rightChild;
    //printf("-------------6\n");
    if(tree->rightThread){
        //printf("-------------7\n");
        while(temp->leftThread){
            temp = temp->leftChild;
        }
    }
    //printf("-------------8\n");
    return temp;
}

void insertRight(threadedTree* parent, threadedTree* child){

    threadedTree* temp;
    child->rightChild = parent->rightChild;
    child->rightThread = parent->rightThread;
    child->leftChild = parent;
    child->leftThread = 0;
    parent->rightChild = child;
    parent->rightThread = 1;
    
    if(child->rightThread){
        //printf("-------------4\n");
        temp = insuc(child);
        //printf("-------------5\n");
        temp->leftChild = child;
    }
}

void insertLeft(threadedTree* parent, threadedTree* child){

    threadedTree* temp;
    child->leftChild = parent->leftChild;
    child->leftThread = parent->leftThread;
    child->rightChild = parent;
    child->rightThread = 0;
    parent->leftChild = child;
    parent->leftThread = 1;

    if(child->leftThread){
        temp = insuc(child);
        temp->rightChild = child;
    }
    
}

void inorder(threadedTree* tree){

    threadedTree* temp = tree;
    for(;;){
        temp = insuc(temp);
        if(temp == tree) break;
        printf("%d\n" ,temp->data);
    }
}

void inorder_ex(){
    threadedTree *tempNode = top;
    do{
        if (tempNode->rightThread == 0)
            tempNode=tempNode->rightChild;
        else {
            tempNode=tempNode->rightChild;
            while (tempNode->leftThread != 0)
                tempNode=tempNode->leftChild;
        }
        if (tempNode != top)
            printf("%d ", tempNode->data);
    }while (tempNode != top);
    printf("\n");
}

void inorder_ex2(threadedTree* ptr){

    if(ptr->leftThread == 0 && ptr->rightThread == 0){
        printf("%d ", ptr->data);
        return;
    }
    if(ptr->leftThread == 1) inorder_ex2(ptr->leftChild);
    printf("%d ", ptr->data);
    if(ptr->rightThread == 1) inorder_ex2(ptr->rightChild);
}

