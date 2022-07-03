#include <stdio.h>
#define MAX_TERMS 101

typedef struct {
    int row;
    int col;
    int value;
} term;

void fastTranspose(term a[], term b[]);

int main(void){

    int col, row, value;
    scanf("%d %d %d" ,&row ,&col ,&value);
    term a[value];
    term b[value];

    a[0].row = row;
    a[0].col = col;
    a[0].value = value;

    for(int i = 1; i <= value; i++){
        scanf("%d %d %d" ,&a[i].row ,&a[i].col ,&a[i].value);
    }

    fastTranspose(a, b);
    for(int i = 0; i <= b[0].value; i++){
        printf("%d %d %d\n" ,b[i].row ,b[i].col ,b[i].value);
    }

    return 0;
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

        for(int i = 1; i <= a[0].value; i++){ //初始化
            startingPos[a[i].col]++;
        }
        sum = startingPos[0];
        startingPos[0] = 1;

        for(int i = 1; i < a[0].value; i++){ //設定轉置後列的起始位置
            save = startingPos[i];
            startingPos[i] = startingPos[i-1] + sum;
            sum = save;
        }

        for(int i = 1; i <= a[0].value; i++){ //將轉至後的元素放入b
            count = startingPos[a[i].col]++;
            b[count].row = a[i].col;
            b[count].col = a[i].row;
            b[count].value = a[i].value;
        }
    }
}