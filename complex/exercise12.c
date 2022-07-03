#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENTS 200
#define HEAP_FULL(n) (n == MAX_ELEMENTS - 1)
#define HEAP_EMPTY(n) (!n)

typedef struct element{
    int key;
} element;

element heap[MAX_ELEMENTS];
int n = 0;

void push(element item, int *n);
void printCategory();
element pop(int *n);

int main(void){

    while(1){
        printCategory();
        int number;
        scanf("%d" ,&number);

        switch(number){
            case 1:
                printf("Type the numbers of elements: ");
                scanf("%d",&n);
                printf("Type elements ");
                for(int i = 1; i <= n; i++){
                    int input;
                    scanf("%d" ,&input);
                    heap[i].key = input;
                }
                printf("\n");
                break;
            case 2:
                element rm;
                rm = pop(&n);
                printf("Remove element: %d\n" ,rm.key);
                break;
            case 3:
                printf("Type the index of element you want to change -- 1 ~ %d : " ,n);
                int input_index;
                scanf("%d" ,&input_index);
                printf("\n");
                printf("Type the number: ");
                int input_number;
                scanf("%d" ,&input_number);
                heap[input_index].key = input_number;
                printf("\n");
                break;
            case 4:
                int input;
                scanf("%d" ,&input);
                element input_element;
                input_element.key = input;
                push(input_element, &n);
                break;
            case 0: 
                return 0;
                break;
            default:
                printf("Retype your number \n");

        }

    }

    return 0;
}

void printCategory(){
    printf("=============================\n");
    printf("Type number to execute: \n");
    printf("Create a min heap -- 1\n");
    printf("Remove the key with the lowest value -- 2\n");
    printf("Change the priority of an arbitrary element -- 3 \n");
    printf("Insert an element into the heap -- 4\n");
    printf("Exit -- 0\n");
    printf("min heap: ");
    for(int i = 1; i <= n; i++){
        printf("%d " ,heap[i].key);
    }
    printf("\n");
    printf("=============================\n");
    
}

void push(element item, int *n){

    int i;
    if(HEAP_FULL(*n)){
        fprintf(stderr, "The heap is full. \n");
        return;
    }
    i = ++(*n);
    while((i != 1) && (item.key < heap[i/2].key)){
        heap[i] = heap[i/2];
        i /= 2;

    }
    heap[i] = item;
}

element pop(int *n){

    int parent, child;
    element item, temp;
    if(HEAP_EMPTY(*n)){
        fprintf(stderr, "The heap is empty\n");
        exit(EXIT_FAILURE);
    }

    item = heap[1];
    temp = heap[(*n)--];
    parent = 1;
    child = 2;

    while(child <= *n){
        if((child < *n) && (heap[child].key > heap[child+1].key)){
            child++;
        }
        if(temp.key <= heap[child].key) break;
        heap[parent] = heap[child];
        parent = child;
        child *= 2;
    }
    heap[parent] = temp;
    return item;


}
