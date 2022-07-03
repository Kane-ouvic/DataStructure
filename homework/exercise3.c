#include <stdio.h>
#define MAX_TERMS 101

typedef struct{
    int row;
    int col;
    int value;
} term;

void amatrix(term a[]);
void fastTranspose(term a[], term b[]);

int main(void){

    int col, row, value;

    scanf("%d %d %d", &row, &col, &value);
    term a[value];
    term b[value];

    a[0].row = row;
    a[0].col = col;
    a[0].value = value;

    for(int i = 1; i <= value ; i++){
        scanf("%d %d %d" ,&a[i].row, &a[i].col, &a[i].value);
    }


    fastTranspose(a, b);
    for(int i = 0; i <= b[0].value; i++){
        printf("%d  %d  %d \n", b[i].row, b[i].col, b[i].value);

    }
    return 0;
}

void amatrix(term a[]){

    a[0].row = 6;   a[0].col = 6;  a[0].value = 9;

    a[1].row = 0;   a[1].col = 0;  a[1].value = 15;
    a[2].row = 0;   a[2].col = 3;  a[2].value = 22;
    a[3].row = 4;   a[3].col = 0;  a[3].value = 91;
    a[4].row = 1;   a[4].col = 3;  a[4].value = -5;
    a[5].row = 4;   a[5].col = 3;  a[5].value = -6;
    a[6].row = 5;   a[6].col = 2;  a[6].value = -7;
    a[7].row = 3;   a[7].col = 5;  a[7].value = 51;
    a[8].row = 4;   a[8].col = 1;  a[8].value = 24;
    a[9].row = 1;   a[9].col = 1;  a[9].value = -3;
}

void fastTranspose(term a[], term b[]){

    int startingPos[a[0].col];
    int count = 0;
    int sum = 0;
    int save = 0;
    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].value = a[0].value;

    for(int i = 0; i < a[0].col; i++){
        startingPos[i] = 0;
    }

    if(a[0].value > 0){

        //startingPos[0] = 1;
        for(int i = 1; i <= a[0].value; i++){  //計算每列的個數
            startingPos[a[i].col]++;
        }

        /*for(int i = 0; i < a[0].col; i++){ //debug
            printf("---%d---%d\n" ,startingPos[i] ,i);
        }*/

        sum = startingPos[0];
        startingPos[0] = 1;
        for(int i = 1; i < a[0].value; i++){

            save = startingPos[i];
            startingPos[i] = startingPos[i-1] + sum;
            sum = save;
            
        }


        for(int i = 1; i <= a[0].value; i++){

            count = startingPos[a[i].col]++; 
            b[count].row = a[i].col;
            b[count].col = a[i].row;
            b[count].value = a[i].value;
        }


    }


}