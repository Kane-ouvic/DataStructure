#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define INFINITY 2147483647

void print(int list[], int n);
void insert(int list[], int key, int n);
int deleteMin(int list[], int n);
int deleteMax(int list[], int n);

int main()
{
    char manual[] = "menu:\n1.insert\n2.deleteMin\n3.deleteMax\n4.print(just reference)\n5.exit\n\nop:";
    int op;

    int key;

    int list[MAX_SIZE];
    int list[1] = INFINITY;
    int n = 1;

    while(1){
        printf("%s", manual);
        scanf("%d", &op);

        switch(op){
            case 1:
                printf("\ninsert value:");
                scanf("%d", &key);
                insert(list, key, ++n);
                break;

            case 2:
                if(n < 2){
                    printf("Heap is empty!\n\n");
                    break;
                }
                printf("Min value = %d\n", deleteMin(list, n--));
                break;

            case 3:
               if(n < 2){
                    printf("Heap is empty!\n\n");
                    break;
                }
                printf("Max value = %d\n", deleteMax(list, n--));
                break; 

            case 4:
                print(list, n);
                break;

            case 5:
                exit(0);
        }
    }

    return 0;
}

void insert(int list[], int key, int n)
{
    if(n == 2){
        list[2] = key;
        return;
    }

    list[n] = key;
    int pos = n; // insertPos

    if(n%2 && list[n-1] > list[n]){ //rightChild && left > right => swap
        printf("in\n");
        int tmp = list[n];
        list[n] = list[n-1];
        list[n-1] = tmp;
        pos--;
    }

    // left up
    int value = list[pos];
    int tmp = pos;
    int grandparent = pos/4;
    while(grandparent >= 1){
        if(value >= list[grandparent*2])
            break;

        list[tmp] = list[grandparent*2];
        tmp = grandparent*2;
        grandparent = tmp/4;
    }
    if(tmp != pos)
        list[tmp] = value;

    //right up
    tmp = pos;
    grandparent = pos/4;
    while(grandparent >= 1){
        if(value <= list[grandparent*2+1])
            break;

        list[tmp] = list[grandparent*2+1];
        tmp = grandparent*2+1;
        grandparent = tmp/4;
    }
    if(tmp != pos)
        list[tmp] = value;
}

int deleteMin(int list[], int n)
{

    int minValue = list[2];
    int tmp = list[n--];
    int pos = 2;

    while(1){
        if(pos*2 > n){
            list[pos] = tmp;
            if(pos+1 <= n && list[pos] > list[pos+1]){
                int tmp = list[pos];
                list[pos] = list[pos+1];
                list[pos+1] = tmp;
            }
            break;
        }
        else if((pos+1)*2 > n){
            if(list[pos*2] < tmp){
                list[pos] = list[pos*2];
                pos = pos*2;
            }
            else{
                list[pos] = tmp;
                break;
            }
        }
        else{
            int minPos = list[pos*2] < list[(pos+1)*2] ? pos*2 : (pos+1)*2;
            if(list[minPos] < tmp){
                list[pos] = list[minPos];
                pos = minPos;
            }
            else{
                list[pos] = tmp;
                break;
            }
        }
    }
    return minValue;
}


int deleteMax(int list[], int n)
{
    if(n == 2){
        n--;
        return list[2];
    }

    int maxValue = list[3];
    int tmp = list[n--];
    int pos = 3;

    while(1){
        if((pos-1)*2 + 1 > n){
            list[pos] = tmp;

            if(list[pos-1] > list[pos]){
                int tmp = list[pos];
                list[pos] = list[pos-1];
                list[pos-1] = tmp;
            }

            break;
        }
       else if(pos*2 + 1 > n){
            if(list[(pos-1)*2 + 1] > tmp){
                list[pos] = list[(pos-1)*2+1];
                pos = (pos-1)*2+1;
            }
            else{
                list[pos] = tmp;
                break;
            }
        }
        else{
            int maxPos = list[pos*2+1] > list[(pos-1)*2 +1] ? pos*2+1 : (pos-1)*2+1;
            if(list[maxPos] > tmp){
                list[pos] = list[maxPos];
                pos = maxPos;
            }
            else{
                list[pos] = tmp;
                break;
            }
        }
    }

    return maxValue;
}

void print(int list[], int n)
{
    if(n<1){
        printf("Heap is empty\n\n");
        return;
    }


    for(int i = 1, level = 0; i<=n; i*=2, level++){

        int j = i;
        for(int k = 20-2*level; k>0; k--)
            printf("_");

        for(int j = 0; j<i && i+j <= n; j++){

            for(int k = 10-2*level; k>0; k--)
                printf("_");

            printf("%d", list[i+j]);

        }

        printf("\n");
    }
}