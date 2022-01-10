#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SWAP(x,y,t) ((t) = (x), (x) = (y), (y) = (t))


void quickSort(int *arr, int left, int right){

    int temp;
    if(left < right){

        int s = arr[(left+right)/2];


        int i = left-1;
        int j = right+1;

        while(1){
            while(arr[++i] < s);
            while(arr[--j] > s);
            if(i >= j) break;
            SWAP(arr[i], arr[j], temp);
        }
        quickSort(arr, left, i-1);
        quickSort(arr, j+1, right);
    }
}