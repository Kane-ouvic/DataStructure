#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SWAP(x,y,t) ((t) = (x), (x) = (y), (y) = (t))


void heapify(int *arr, int n, int i){

    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if(left < n && arr[left] > arr[largest]){
        largest = left;
    }
    if(right < n && arr[right] > arr[largest]){
        largest = right;
    }
    if(largest != i){
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int *arr, int n){

    for(int i = n/2 - 1; i >= 0; i--){
        heapify(arr, n, i);
    }
    for(int i = n-1; i >= 0; i--){

        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

void swap(int *a, int *b){

    int temp = *a;
    *a = *b;
    *b = temp;
}

void permute(int *arr, int n){
    /* random permutation generator */
    int i, j;
    int temp;
    for(i = n; i >= 2; i--) {
        j = rand() % i + 1;
        SWAP(arr[j], arr[i], temp);
    }
}