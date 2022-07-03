#include <stdio.h>

void BFS(int t, int v);
void reset2Darr(int m);
void reset1Darr(int m);
void printGraph(int v, int m);

int input_arr[100][100];
int visited[100];
int q[100];
int front = -1;
int rear = -1;

int main(void){

    int n;
    scanf("%d" ,&n);
    for(int i = 0; i < n; i++){

        int m,t;
        scanf("%d %d" ,&m ,&t);
        visited[t] = 1;
         for(int j = 0; j < m; j++){
            for(int k = 0; k < m; k++){
                scanf("%d" ,&input_arr[j][k]);
            }
        }
        printf("%d ",t);
        BFS(t, m);
        printf("\n");
        reset2Darr(m);
        reset1Darr(m);
        front = -1, rear = -1;

    }
}

void BFS(int t, int v){
    int j;
    for(j = 0; j < v; j++){
        if(input_arr[t][j] == 1 && visited[j] == 0){
            rear++;
            q[rear] = j;
            visited[j] = 1;
            printf("%d " ,j);
        }
    }
    front++;
    if(front <= rear){
        BFS(q[front], v);
    }
}


void reset2Darr(int m){

    for(int i = 0; i < m; i++){
        for(int j = 0; j < m; j++){
            input_arr[i][j] = 0;
        }
    }

}

void reset1Darr(int m){

    for(int i = 0; i < m; i++){
            visited[i] = 0;
            q[i] = 0;
    }
}

void printGraph(int v, int m){

    for(int i = 0; i < m; i++)
        printf("%d ",q[i]);

}