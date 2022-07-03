#include <stdlib.h>
#include <stdio.h>

void print2D(int p[50][50]){

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            printf("%d" ,p[i][j]);
        }
        printf("\n");
    }
}

int main(){

    int test[50][50];
    printf("--------------");

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            scanf("%d" ,&test[i][j]);
        }
    }

    print2D(test);

    return 0;
}