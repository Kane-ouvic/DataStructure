#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void merge(int *arr, int l, int m, int r){

    int i,j,k;
    int n1 = m-l+1;
    int n2 = r-m;

    int L[n1];
    int R[n2];

    for(i = 0; i < n1; i++){
        L[i] = arr[l+i];
    }
    for(j = 0; j < n2; j++){
        R[j] = arr[m+1+j];
    }

    i = 0;
    j = 0;
    k = l;

    while(i < n1 && j < n2){
        if(L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while(i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }

    while(j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }

}

void mergeSort(int *arr, int l, int r){

    if(l < r){

        int m = l + (r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}


//generate the worst case of merge sort

void join(int *arr, int *left, int *right, int l, int m, int r){

    int i;
    for(i = 0; i <= m-l; i++){
        arr[i] = left[i];
    }
    for(int j = 0; j < r-m; j++){
        arr[i+j] = right[j];
    }
}

void split(int *arr, int *left, int *right, int l, int m, int r){

    for(int i = 0; i <= m-l; i++){
        left[i] = arr[i*2];
    }
    for(int i = 0; i < r-m; i++){
        right[i] = arr[i*2+1];
    }
}

void generateWorstCase(int *arr, int l, int r){

    if(l < r){

        int m = l + (r-l)/2;
        int left[m-l+1];
        int right[r-m];

        split(arr, left, right, l, m, r);
        generateWorstCase(left, l, m);
        generateWorstCase(right, m+1, r);

        join(arr, left, right, l, m, r);
    }
}