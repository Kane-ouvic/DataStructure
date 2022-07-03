#include <stdio.h>
#include <stdlib.h>
#define MAX 1000000

typedef struct edge{
    int u, v, w;
} edge;

typedef struct edgelist{
    edge data[MAX];
    int n;
} edgelist;

edgelist elist;

//int G[MAX][MAX];

int test1[MAX];
int test2[MAX];
int numbers[MAX];
int n;
int edges;
edgelist spanlist;

void kruskal();
int find(int belongs[], int vertexno);
void union1(int belongs[], int c1, int c2);
void sort();
void print();

int main(void){

    int total_cost;

    scanf("%d %d" ,&n ,&edges);


    for(int k = 0; k < edges; k++){
        int i, j, number;
        scanf("%d %d %d" ,&i ,&j ,&number);
        test1[k] = i;
        test2[k] = j;
        numbers[k] = number; 
    }


    kruskal();
    print();

    return 0;
}

void kruskal(){
    int belongs[n], i, j, cno1, cno2;
    elist.n = 0;

    for(int k = 0; k < edges; k++){
        elist.data[elist.n].u = test1[k];
        elist.data[elist.n].v = test2[k];
        elist.data[elist.n].w = numbers[k];
        elist.n++;
    }

    sort();
    for(i = 0; i < n; i++){
        belongs[i] = i;
    }
    spanlist.n = 0;

    for(i = 0; i < elist.n; i++){
        cno1 = find(belongs, elist.data[i].u);
        cno2 = find(belongs, elist.data[i].v);
        if(cno1 != cno2){
            spanlist.data[spanlist.n] = elist.data[i];
            spanlist.n = spanlist.n + 1;
            union1(belongs, cno1, cno2);
        }
    }        
}

int find(int belongs[], int vertexno){
    return belongs[vertexno];
}

void union1(int belongs[], int c1, int c2){

    int i;
    for(i = 0; i < n; i++){
        if(belongs[i] == c2){
            belongs[i] = c1;
        }
    }
}

void sort(){

    int i,j;
    edge temp;
    for(i = 1; i < elist.n; i++){
        for(j = 0; j < elist.n-1; j++){
            if(elist.data[j].w > elist.data[j+1].w){
                temp = elist.data[j];
                elist.data[j] = elist.data[j+1];
                elist.data[j+1] = temp;
            }
        }
    }
}

void print(){

    int i = 0;
    long long int cost = 0;
    for(i = 0; i < spanlist.n; i++){
        cost = cost + spanlist.data[i].w;
    }

    printf("%lld",cost);
}