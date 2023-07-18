#include <stdio.h>
#include <string.h>

int iterativeF(int n);
int recursiveF(int n);

int main(void){
    printf("test\n");
    int n;
    scanf("%d", &n);
    int a[n];

    for(int i = 0; i < n; i++){
        char str[20];
        int j;
        scanf("%s %d", str, &j);
        if(!strcmp(str, "iterative")){
            a[i] = iterativeF(j);
        }
        if(!strcmp(str, "recursive")){
            a[i] = recursiveF(j);
        }
        //a[i] = 0;
    }

    for(int i = 0; i < n; i++){
        printf("%d \n", a[i]);
    }

    //printf("%d \n", iterativeF(4));

    return 0;
}

int iterativeF(int n){

    int f1 = 0;
    int f2 = 1;
    int result = 0;

    if(n == 1) return 1;

    for(int i=1; i < n; i++){

        result = f1 + f2;
        f1 = f2;
        f2 = result;
    }

    return result;


}

int recursiveF(int n){

    if(n == 0) {
        return 0;
    } else if (n == 1){
        return 1;
    } else{
        return recursiveF(n-2) + recursiveF(n-1);
    }

}
