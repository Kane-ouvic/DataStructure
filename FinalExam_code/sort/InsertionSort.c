#include <stdlib.h>
#include <time.h>
#define SWAP(x,y,t) ((t) = (x), (x) = (y), (y) = (t))

void insertionSort(int *arr, int len){

    int i,j;
    int temp;
    for(i = 1; i < len; i++){
        temp = arr[i];
        j = i-1;
        for(; j >= 0 && arr[j] > temp; j--){
            arr[j+1] = arr[j];
        }
        arr[j+1] = temp;
    }
}