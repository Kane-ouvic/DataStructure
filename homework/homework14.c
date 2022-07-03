#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAX 10000

int find(int i);
void heightUnion(int i, int j);
void weightUnion(int i, int j);
void weightedUnion(int i, int j);
int same(int x, int y);
int collaspingFind(int i);
int collaspingFind_ex(int i);

int parent[MAX];
int count[MAX];
int height[MAX];
int stack[MAX];

int main(void){
    int times;
    char union_category[20];
    printf("Type the category you want to union heightUnion / weightUnion\n");
    scanf("%s" ,union_category);
    scanf("%d" ,&times);

    for(int i = 0; i < times; i++){
        int n, ops;
        scanf("%d %d" ,&n ,&ops);
        for(int j = 0; j < n; j++){
            parent[j] = j;
            height[j] = -1;
            count[j] = -1;
            stack[j] = -1;
        }
        for(int j = 0; j < ops; j++){
            char input_category[10];
            scanf("%s" ,input_category);
            if(strcmp(input_category, "union") == 0){
                int x,y;
                scanf("%d %d" ,&x ,&y);
                if(strcmp(union_category, "weightUnion") == 0) weightUnion(x, y);
                if(strcmp(union_category, "heightUnion") == 0) heightUnion(x, y);


            } else if(strcmp(input_category, "find") == 0){

                double start, end;
                start = clock();
                int x;
                int root;
                scanf("%d" ,&x);
                root = find(x);
                collaspingFind(x);
                //printf("%d\n" ,find(x));
                for(int k = 0; k < n; k++){
                    if(stack[k] == 1){
                        parent[k] = root;
                    }
                }
                end = clock();
                printf("%d\n" ,root);
                printf("Runtime: %f s\n" ,(end - start)/CLOCKS_PER_SEC);

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
        /*for(int j = 0; j < n; j++){
            printf("%d " ,parent[j]);
        }*/
        printf("\n");

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

int collaspingFind_ex(int i){

    if(parent[i] != i){
        collaspingFind_ex(parent[i]);
        stack[i] = 1;
        //find(parent[i]);
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
    } else if(height[x] == height[y]) {
        parent[y] = x;
        height[x]--;
    } else {
        parent[x] = y;
    }
}

void weightUnion(int i, int j){
    
    int x = find(i);
    int y = find(j);

    int temp = -count[x] + -parent[y];
    if(count[x] <= count[y]){
        parent[y] = x;
        count[x] = temp;
    } else {
        parent[x] = y;
        count[y] = temp;
    }

}

void weightedUnion(int i, int j){
    
    parent[i] = -count[i];
    parent[j] = -count[j];
    int temp = parent[i] + parent[j];
    if(parent[i] > parent[j]){
        parent[i] = j;
        parent[j] = temp;
    } else {
        parent[j] = i;
        parent[i] = temp;
    }

}

int collaspingFind(int i){
    int root;
    int trail;
    int lead;
    for(root = i; parent[root] != root; root = parent[root]){
    }
    for(trail = i; trail != root; trail = lead){
        lead = parent[trail];
        parent[trail] = root;
    }

    return root;
}