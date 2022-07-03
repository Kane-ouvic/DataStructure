#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 10000

int find(int i);
void heightUnion(int i, int j);
int same(int x, int y);

int parent[MAX];
int count[MAX];
int height[MAX];

int main(void){
    int times;
    
    scanf("%d" ,&times);

    for(int i = 0; i < times; i++){
        int n, ops;
        scanf("%d %d" ,&n ,&ops);
        for(int j = 0; j < n; j++){
            parent[j] = j;
            height[j] = -1;
        }
        for(int j = 0; j < ops; j++){
            char input_category[10];
            scanf("%s" ,input_category);
            if(strcmp(input_category, "union") == 0){
                int x,y;
                scanf("%d %d" ,&x ,&y);
                heightUnion(x, y);

            } else if(strcmp(input_category, "find") == 0){
                int x;
                scanf("%d" ,&x);
                printf("%d\n" ,find(x));

            } else if(strcmp(input_category, "same") == 0){
                int x, y;
                scanf("%d %d" ,&x ,&y);
                if(same(x,y)){
                    printf("true\n");
                } else {
                    printf("false\n");
                }

            }

        }

    }


    return 0;
}

int find(int i){

    if(parent[i] != i){
        find(parent[i]);
    } else {
        return i;
    }
}

int same(int x, int y){

    if(find(x) == find(y)){
        return 1;
    } else {
        return 0;
    }
}

void heightUnion(int i, int j){

    int x = find(i);
    int y = find(j);
    if(x == y) return;

    if(height[x] < height[y]){
        parent[y] = x;
        //height[i]--;
    } else if(height[x] == height[y]) {
        parent[y] = x;
        height[x]--;
    } else {
        parent[x] = y;
    }
}
