#include <stdio.h>


void BFS(int t, int v);
void reset2Darr(int m);
void reset1Darr(int m);
int countVertices(int m);
void printGraph(int v, int m);


int input_arr[100][100];
int visited[100];
int q[100];
int front = -1;
int rear = -1;

int main(void){

    int n;
    scanf("%d" ,&n);

    //int input_arr[100][100];
    //int visited[100];
    
    for(int i = 0; i < n; i++){
        int m,t,v;
        scanf("%d %d" ,&m ,&t);
        //reset2Darr(m);
        //reset1Darr(m);
        visited[t] = 1;
        for(int j = 0; j < m; j++){
            for(int k = 0; k < m; k++){
                scanf("%d" ,&input_arr[j][k]);
            }
        }
        v = countVertices(m);
        printf("%d ",t);
        BFS(t, m);
        printf("\n");
        //printGraph(v, m);
        //printf("\n");
        reset2Darr(m);
        printf("\n---------------------------------");
        reset1Darr(m);
        front = -1, rear = -1;
    }

    return 0;
}

void BFS(int t, int v){
    int j;

    
    //visited[t] = 1;
    //printf("%d " ,t);
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
                //visited[q[front]] = 1;
        BFS(q[front],v);
    }
}

void reset2Darr(int m){

    for(int i = 0; i < m; i++){
        for(int j = 0; j < m; j++){
            input_arr[i][j] = 0;
        }
    }

}

int countVertices(int m){

    int count = 0;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < m; j++){
            if(input_arr[i][j] == 1) count++;
        }
    }
    return count;
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