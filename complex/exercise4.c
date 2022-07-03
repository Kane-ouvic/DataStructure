#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int imove[8];
int jmove[8];

void setDir();
void walking(int array[40][20], int size_x, int size_y, int start_x, int start_y);
void initialize(int array[40][20], int size_x, int size_y);
void printMap(int array[40][20], int size_x, int size_y);


int main(void){
    char input;
    int map[40][20];
    setDir();
    while(input != 'q'){
        scanf("%c" ,&input);
        //printf("------------0");
        if(input == 'a'){
            int m,n;
            
            scanf("%d %d" ,&m ,&n);
            initialize(map, m, n);
            //printf("------------1");
            walking(map, m, n, 0, 0);
            //printf("------------2");
            printMap(map, m, n);
            //printf("%d %d" ,m ,n);
        } else if(input == 'b'){
            int numbers;
            scanf("%d" ,&numbers);
            switch (numbers)
            {
            case 1:
                initialize(map, 15, 15);
                walking(map, 15, 15, 9, 9);
                printMap(map, 15, 15);
                break;
            case 2:
                initialize(map, 39, 19);
                walking(map, 39, 19, 0, 0);
                printMap(map, 39, 19);
                break;
            default:
                break;
            }
        }
    }
    return 0;

}

void walking(int array[40][20], int size_x, int size_y, int start_x, int start_y){

    int now_x = start_x;
    int now_y = start_y;
    int next_x;
    int next_y;
    int counter = 0;
    int walks = 0;

    srand(time(NULL));
    int random;
    array[now_x][now_y]++;
    counter++;
    walks++;
   // printf("-------888888");
    while(counter < size_x*size_y){
        random  = rand();
        next_x = now_x + imove[random%8];
        next_y = now_y + jmove[random%8];
        if(next_x >= 0 && next_x < size_x && next_y >= 0 && next_y < size_y){
            if(array[next_x][next_y] == 0) counter++;
            walks++;
            array[next_x][next_y]++;
            //printf("-------99999");
            now_x = next_x;
            now_y = next_y;
        }
    }
    printf("%d\n" ,walks);

}

void initialize(int array[40][20], int size_x, int size_y) {

    for(int j = 0; j < size_y; j++){
        for(int i = 0; i < size_x; i++){
            array[i][j] = 0;
        }
    }
}

void printMap(int array[40][20], int size_x, int size_y) {

    for(int i = 0; i < size_x; i++){
        for(int j = 0; j < size_y; j++){
            printf("%4d" , array[i][j]);
        }
        printf("\n");
    }

}

void setDir() {

    imove[0] = -1; jmove[0] = 1;
    imove[1] = 0; jmove[1] = 1;
    imove[2] = 1; jmove[2] = 1;
    imove[3] = 1; jmove[3] = 0;
    imove[4] = 1; jmove[4] = -1;
    imove[5] = 0; jmove[5] = -1;
    imove[6] = -1; jmove[6] = -1;
    imove[7] = -1; jmove[7] = 0;
}
