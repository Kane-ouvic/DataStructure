#include <stdio.h>
#define MAX_STACK_SIZE 100
#define FALSE 0
#define TRUE 1

typedef struct {

    int row;
    int col;
    int dir;

} element;


typedef struct {

    int vert;
    int horiz;

} offsets;

void path(int maze[50][50], int mark[50][50], int size_x, int size_y);
element pop(void);
void push(element item);
void setDir(void);
//
element stack[MAX_STACK_SIZE];
int top = 0;
offsets move[8];

int main(void){

    int m,n,k;
    scanf("%d %d" ,&m ,&n);
    int maze[50][50];
    int mark[50][50];
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            scanf("%d" ,&k);
            maze[i][j] = k;
            mark[i][j] = k;
        }
    }
    setDir();
    path(maze, mark, m, n);
    return 0;
}

void path(int maze[50][50], int mark[50][50], int size_x, int size_y){

    int row, col;
    int nextRow, nextCol, dir;
    int found = FALSE;
    element position;

    while(top > -1 && !found){

        position = pop();
        row = position.row;
        col = position.col;
        dir = position.dir;

        while(dir < 8 && !found){

            nextRow = row + move[dir].vert;
            nextCol = col + move[dir].horiz;
            if(nextRow > size_x-1 || nextRow < 0){ //超過範圍
                ++dir;
                continue;
            }
            if(nextCol > size_y-1 || nextCol < 0){ //超過範圍
                ++dir;
                continue;
            }
            if(nextRow == size_x-1 && nextCol == size_y-1){ //找到終點了

                position.row = row;
                position.col = col;
                push(position);
                position.row = nextRow;
                position.col = nextCol;
                push(position);
                found = TRUE;

            } else if(!maze[nextRow][nextCol] && !mark[nextRow][nextCol]){ //找到路

                mark[nextRow][nextCol] = 1;
                position.row = row;
                position.col = col;
                position.dir = ++dir;
                push(position);
                row = nextRow; col = nextCol; dir = 0;
            } else {
                ++dir;
            }
        }
    }
    if(found){
        element road;
        for(int i = 0; i <= top; i++){
            road = stack[i];
            printf("%d %d \n" ,road.row ,road.col);
        }
    } else {
        printf("no answer \n");
    }
}

void push(element item){

    if(top == MAX_STACK_SIZE){
        //full
    } else {
        stack[++top] = item;
    }
}

element pop(void){

    if(top < 0){

    } else {
        return stack[top--];
    }
}

void setDir(){

    move[0].vert = -1; move[0].horiz = 0;
    move[1].vert = -1; move[0].horiz = 1;
    move[2].vert = 0; move[2].horiz = 1;
    move[3].vert = 1; move[3].horiz = 1;
    move[4].vert = 1; move[4].horiz = 0;
    move[5].vert = 1; move[5].horiz = -1;
    move[6].vert = 0; move[6].horiz = -1;
    move[7].vert = -1; move[7].horiz = -1;
}