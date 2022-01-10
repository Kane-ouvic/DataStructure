#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 20

struct element{
    int data;
    int key;
};

struct element* hashArray[SIZE];
struct element* dummyItem;
struct element* item;

int hashCode(int key){
    return key % SIZE;
}

struct element* search(int key){

    int hashIndex = hashCode(key);

    while(hashArray[hashIndex] != NULL){
        if(hashArray[hashIndex]->key == key){
            return hashArray[hashIndex];
        }
        hashIndex++;
        hashIndex %= SIZE;
    }

    return NULL;
}

void insert(int key, int data){

    struct element* item = (struct element*)malloc(sizeof(struct element));
    item->data = data;
    item->key = key;

    int hashIndex = hashCode(key);

    while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1){
        hashIndex++;
        hashIndex %= SIZE;
    }

    hashArray[hashIndex] = item;
}

struct element* delete(struct element* item){

    int key = item->key;
    int hashIndex = hashCode(key);

    while(hashArray[hashIndex] != NULL){

        if(hashArray[hashIndex]->key == key){
            struct element* temp = hashArray[hashIndex];
            hashArray[hashIndex] = dummyItem;
            return temp;
        }

        hashIndex++;
        hashIndex %= SIZE;
    }
    return NULL;
}

void display(){

    int i = 0;
    for(i = 0; i < SIZE; i++){
        if(hashArray[i] != NULL){
            printf("(%d,%d) ", hashArray[i]->key, hashArray[i]->data);
        } else {
            printf(" -- ");
        }
    }
    printf("\n");
}

int main() {
   dummyItem = (struct element*) malloc(sizeof(struct element));
   dummyItem->data = -1;  
   dummyItem->key = -1; 

   char input_category[10];
   while(strcmp(input_category, "quit") != 0){

       scanf("%s" ,input_category);
       if(strcmp(input_category, "insert") == 0){
           int key,data;
           scanf("%d %d" ,&key ,&data);
           insert(key, data);

       } else if(strcmp(input_category, "search") == 0) {
           int key;
           scanf("%d" ,&key);
           item = search(key);
           if(item != NULL) {
                printf("Element found: %d\n", item->data);
            } else {
                printf("Element not found\n");
            }

       } else if(strcmp(input_category, "delete") == 0) {
           int key;
           scanf("%d" ,&key);
           item = search(key);
           delete(item);

       } else if(strcmp(input_category, "display") == 0){
           display();
       }

   }

    return 0;
}