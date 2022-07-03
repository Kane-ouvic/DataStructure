#include <stdio.h>


void DFS(int t, int v);
void reset2Darr(int m);
void reset1Darr(int m);
int countVertices(int m);


int input_arr[100][100];
int visited[100];

int main(void){

    int n;
    scanf("%d" ,&n);

    //int input_arr[100][100];
    //int visited[100];
    
    for(int i = 0; i < n; i++){
        int m,t,v;
        scanf("%d %d" ,&m ,&t);
        for(int j = 0; j < m; j++){
            for(int k = 0; k < m; k++){
                scanf("%d" ,&input_arr[j][k]);
            }
        }
        v = countVertices(m);
        DFS(t, m);
        printf("\n");
        reset2Darr(m);
        reset1Darr(m);
    }

    return 0;
}

void DFS(int t, int v){
    int j;
    visited[t] = 1;
    printf("%d " ,t);
    for(j = 0; j < v; j++){
        if(input_arr[t][j] == 1 && visited[j] == 0){
            DFS(j,v);
        }
    }
}

void reset2Darr(int m){

    for(int i = 0; i < m; i++){
        for(int j = 0; j < m; j++){
            if(input_arr[i][j] == 1) input_arr[i][j] = 0;
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
        if(visited[i] == 1) visited[i] = 0;
    }
}