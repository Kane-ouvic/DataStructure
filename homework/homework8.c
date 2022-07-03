#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100
#define TRUE 1
#define FALSE 0

typedef struct treeNode{
    char data;
    struct treeNode* link;
} treeNode;

void push(treeNode* item);
struct treeNode* pop();
struct treeNode* newNode(char data);
struct treeNode* read(char* input);
void write(struct treeNode* topNode);
struct treeNode* copy(struct treeNode* topNode);
int isequal(struct treeNode* topNodeA, struct treeNode* topNodeB);
void clear(struct treeNode* topNode);
void swap(struct treeNode* target);
void swapFix(struct treeNode* target);
struct treeNode* getLast(struct treeNode* ptr);

struct treeNode* stack[MAX_STACK_SIZE];
int top = -1;

int main(void){

    char input[100];
    char category[10];
    struct treeNode* Tree[3];
    Tree[0] = NULL;
    Tree[1] = NULL;
    Tree[2] = NULL;
    int times;
    scanf("%d" ,&times);

    for(int i = 0; i < times; i++){

        scanf("%s" ,category);
        if(strcmp(category, "read") == 0){
            int number;
            scanf("%d %s" ,&number ,input);
            Tree[number] = read(input);

        } else if(strcmp(category, "write") == 0){
            int number;
            scanf("%d" ,&number);
            write(Tree[number]);

        } else if(strcmp(category, "copy") == 0){
            int number1, number2;
            scanf("%d %d" ,&number1 ,&number2);
            Tree[number2] = copy(Tree[number1]);

        } else if(strcmp(category, "clear") == 0){
            int number;
            scanf("%d" ,&number);
            clear(Tree[number]);
        } else if(strcmp(category, "isequal") == 0){
            int number1, number2;
            scanf("%d %d" ,&number1 ,&number2);
            if(isequal(Tree[number1], Tree[number2])){
                printf("true\n");
            } else {
                printf("false\n");
            }
        }

    }
    return 0;
}

struct treeNode* read(char* input){

    struct treeNode* topNode = newNode(input[0]);
    struct treeNode* ptr = topNode;
    struct treeNode* temp;

    for(int i = 1; i < strlen(input); i++){
        ptr->link = newNode(input[i]);
        ptr = ptr->link;
    }
    ptr = topNode;
    for(; ptr != NULL; ptr = ptr->link){

        if(ptr->data == '('){
            push(ptr);
        } else if(ptr->data == ')'){
            temp = pop();
            swap(temp);
        }
    }

    printf("pread");
    return topNode;
}

struct treeNode* getLast(struct treeNode* ptr){

    struct treeNode* pre = ptr;
    int check = 0;

    if(ptr->link->data == '('){
        ptr = ptr->link;
        for(;ptr != NULL; ptr = ptr->link){
            if(ptr->data == '('){
                check++;
                continue;
            } else if(ptr->data == ')'){
                check--;
                if(check == 0) return ptr;
                continue;
            }
        }
    }

    return ptr;
}

void swap(struct treeNode* target){

    struct treeNode* ptr1 = target->link;
    struct treeNode* ptr2;
    struct treeNode* pre1 = target;
    struct treeNode* pre2 = getLast(ptr1)->link;
    struct treeNode* temp;
    struct treeNode* save;
    
    if(pre2->data == ')') return;

    for(; ptr1->data != ')'; ptr1 = (getLast(ptr1)->link)->link){
        for(ptr2 = (getLast(ptr1)->link)->link; ptr2->data != ')'; ptr2 = (getLast(ptr2)->link)->link){
            if(ptr1->data > ptr2->data){
                temp = getLast(ptr1)->link;
                getLast(ptr1)->link = getLast(ptr2)->link;
                getLast(ptr2)->link = temp;
                pre1->link = ptr2;
                pre2->link = ptr1;
                temp = ptr1;
                ptr1 = ptr2;
                ptr2 = temp;
            }
            pre2 = getLast(ptr2)->link;
            if(pre2->data == ')') return;
        }
        pre1 = getLast(ptr1)->link;
    }

}

struct treeNode* copy(struct treeNode* topNode){

    struct treeNode* temp = newNode(topNode->data);
    struct treeNode* top = temp;
    struct treeNode* ptr = topNode->link;
    for(; ptr != NULL; ptr = ptr->link){
        temp->link = newNode(ptr->data);
        temp = temp->link;
    }
    printf("copied\n");
    return top;
}

int isequal(struct treeNode* topNodeA, struct treeNode* topNodeB){

    struct treeNode* ptrA = topNodeA;
    struct treeNode* ptrB = topNodeB;

    for(; ptrA != NULL && ptrB != NULL; ptrA = ptrA->link, ptrB = ptrB->link){
        if(ptrA->data != ptrB->data){
            return FALSE;
        }
    }
    return TRUE;
}

void clear(struct treeNode* topNode){

    struct treeNode* ptr = topNode->link;
    struct treeNode* pre = topNode;
    topNode = NULL;

    for(;ptr != NULL; ptr = ptr->link){
        free(pre);
        pre = ptr;
    }
    free(pre);
    printf("cleared\n");
}

void write(struct treeNode* topNode){

    struct treeNode* ptr = topNode;
    for(; ptr != NULL; ptr = ptr->link){
        printf("%c" ,ptr->data);
    }
    printf("\n");
}

struct treeNode* newNode(char data){

    struct treeNode* temp = (struct treeNode*)malloc(sizeof(treeNode));
    temp->data = data;
    temp->link = NULL;
    return temp;
}

void push(treeNode* item){

    if(top == MAX_STACK_SIZE){

    } else {
        stack[++top] = item;
    }
}

struct treeNode* pop(){

    if(top == -1){

    } else {
        return stack[top--];
    }
}




