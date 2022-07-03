#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node{

    int data, dist;
    struct node* right;
    struct node* left;
} node;

struct node* root;
struct node* temp;
struct node* r1;
struct node* r2;
//實驗
int rand_numbers[5000];
int index = 0;
int times_m = 500;
int check = 0;
//
void inorder(struct node* ptr);
void postorder(struct node* ptr);
int depth(struct node* ptr);
struct node* meld(struct node* h, struct node* k);
struct node* deletion(struct node* root);
struct node* insert(struct node* newroot, int value);
void treemerge();

int main(void){

    int bkpoint = 0;
    int value;
    int val1;
    //
    double start;
    double end;
    double runtime;
    //
    printf("\n****Lefist Max Heap Management****");
    printf("\nEnter root node\n");
    scanf("%d" ,&value);
    root = (struct node*)malloc(sizeof(struct node));
    root->right = NULL;
    root->left = NULL;
    root->dist = 0;
    root->data = value;

    //
    srand(time(NULL));
    int element;
    int choice;

    printf("\nType the numbers of array: \n");
    scanf("%d" ,&times_m);

    for(int i = 0; i < times_m; i++){
        element = rand();
        rand_numbers[i] = element;
        //printf("%d\n" ,rand_numbers[i]);
        
    }



    //測試資料
    start = clock();
    for(int i = 0; i < 5000; i++){
        choice = rand();
        index = rand()%times_m;
        if(choice%2 == 0){
            //printf("%d-- %d\n", index, rand_numbers[index]);
            root = insert(root, rand_numbers[index]);
            //check++;
        } else {
            //check--;
            root = deletion(root);
        }
    }
    end = clock();
    runtime = end - start;
    printf("\nRuntime: %f ms" ,runtime/CLOCKS_PER_SEC*1000);
    printf("\nAverage Runtime: %f ms" ,runtime/CLOCKS_PER_SEC/5);


    return 0;
}

void inorder(struct node* ptr){

    if(ptr != NULL){
        inorder(ptr->left);
        printf("%d " ,ptr->data);
        inorder(ptr->right);
    }
}

void postorder(struct node* ptr){

    if(ptr != NULL){
        inorder(ptr->left);
        inorder(ptr->right);
        printf("%d " ,ptr->data);
    }
}

int depth(struct node* ptr){

    if(ptr == NULL){
        return -1;
    } else {
        return ptr->dist;
    }
}

struct node* meld(struct node* h, struct node* k){

    if(h == NULL){
        return k;
    }
    if(k == NULL){
        return h;
    }

    if(k->data < h->data){
        temp = k;
        k = h;
        h = temp;
    }

    h->right = meld(h->right, k);
    if(depth(h->right) > depth(h->left)){
        temp = h->right;
        h->right = h->left;
        h->left = temp;
    }

    if(h->right == NULL){
        h->dist = 0;
    } else {
        h->dist = 1 + (h->right->dist);
    }

    return h;
}

struct node* deletion(struct node* root){

    if(root != NULL){

        printf("Deleted element is %d\n" ,root->data);
        root = meld(root->right, root->left);
    }

    return root;
}

struct node* insert(struct node* newroot, int value){

    int val;
    struct node* z;
    struct node* x;
    z = (struct node *)malloc(sizeof(struct node));
    z->right = NULL;
    z->left = NULL;
    z->dist = 0;
    z->data = value;
    newroot = meld(newroot, z);
    //printf("Root element is %d\t distance value is %d" ,newroot->data ,newroot->dist + 1);
    return newroot;
}

void treemerge(){

    int val;
    r1 = (struct node*)malloc(sizeof(struct node));
    r1->right = NULL;
    r1->left = NULL;
    r1->dist = 0;
    printf("*********First Tree**********");
    printf("\nEnter the root node");
    scanf("%d" ,&val);
    r1->data = val;

    while(1){
        printf("\nIf you want to insert element to first tree enter 1 else 0");
        scanf("%d" ,&val);
        if(val){
            int value;
            printf("Enter the value of the node to be added: ");
            scanf("%d" ,&value);
            r1 = insert(r1, value);
        } else {
            break;
        }
    }

    r2 = (struct node*)malloc(sizeof(struct node));
    r2->right = NULL;
    r2->left = NULL;
    r2->dist = 0;

    printf("*********Second Tree**********");
    printf("\nEnter the root node");
    scanf("%d" ,&val);
    r2->data = val;
    while(1){
        printf("\nIf you want to insert element to second tree enter 1 else 0");
        scanf("%d" ,&val);
        if(val){
            int value;
            printf("Enter the value of the node to be added: ");
            scanf("%d" ,&value);
            r2 = insert(r2, value);
        } else {
            break;
        }
    }
    printf("\nFirst tree");
    inorder(r1);
    printf("\nSecond tree");
    inorder(r2);

    treemerge();
    printf("\nRoot element is: %d\n" , r1->data);
    inorder(r1);

}