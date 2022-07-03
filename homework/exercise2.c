#include <stdio.h>


void hanoi(int n, char T1, char T2, char T3);
int main(void){

    int n;
    //int *amountp;
    //int amount = 1;
    //amountp = &amount;
    scanf("%d", &n);
    hanoi(n, '1', '2', '3');
    return 0;
}


void hanoi(int n, char T1, char T2, char T3){

    if(n > 0){
        hanoi(n-1, T1, T3, T2);
        printf("%d %c %c\n",n ,T1, T3);
        hanoi(n-1, T2, T1, T3);
    }
}