#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <stdlib.h>

struct node{

    int n;
    int degree;
    struct node* parent;
    struct node* child;
    struct node* sibling;
};

//實驗
int rand_numbers[5000];
int index = 0;
int times_m = 500;
int check = 0;
//

struct node* MAKE_bin_HEAP();
int bin_LINK(struct node*, struct node*);
struct node* CREATE_NODE(int);
struct node* bin_HEAP_UNION(struct node*, struct node*);
struct node* bin_HEAP_INSERT(struct node*, struct node*);
struct node* bin_HEAP_MERGE(struct node*, struct node*);
struct node* bin_HEAP_EXTRACT_MIN(struct node*);
int REVERT_LIST(struct node*);
int DISPLAY(struct node*);
struct node* FIND_NODE(struct node*, int);
int bin_HEAP_DECREASE_KEY(struct node*, int, int);
int bin_HEAP_DELETE(struct node*, int);

int count = 1;

struct node* MAKE_bin_HEAP(){

    struct node* np;
    np = NULL;
    return np;
}

struct node* H = NULL;
struct node* Hr = NULL;

int bin_LINK(struct node* y, struct node* z){

    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree = z->degree + 1;
}

struct node* CREATE_NODE(int k){

    struct node* p;
    p = (struct node*)malloc(sizeof(struct node));
    p->n = k;
    return p;
}

struct node* bin_HEAP_UNION(struct node* H1, struct node* H2){

    struct node* prev_x;
    struct node* next_x;
    struct node* x;
    struct node* H = MAKE_bin_HEAP();
    H = bin_HEAP_MERGE(H1, H2);
    if(H == NULL){
        return H;
    }
    prev_x = NULL;
    x = H;
    next_x = x->sibling;
    while(next_x != NULL){

        if((x->degree != next_x->degree) || ((next_x->sibling != NULL) && (next_x->sibling)->degree == x->degree)){
            prev_x = x;
            x = next_x;
        } else {
            if(x->n <= next_x->n){
                x->sibling = next_x->sibling;
                bin_LINK(next_x, x);
            } else {
                if(prev_x == NULL){
                    H = next_x;
                } else {
                    prev_x->sibling = next_x;
                }
                bin_LINK(x, next_x);
                x = next_x;
            }
        }
        next_x = x->sibling;
    }
    return H;
}

struct node* bin_HEAP_INSERT(struct node* H, struct node* x){

    struct node* H1 = MAKE_bin_HEAP();
    x->parent = NULL;
    x->child = NULL;
    x->sibling = NULL;
    x->degree = 0;
    H1 = x;
    H = bin_HEAP_UNION(H, H1);
    return H;
}

struct node* bin_HEAP_MERGE(struct node* H1, struct node* H2){

    struct node* H = MAKE_bin_HEAP();
    struct node* y;
    struct node* z;
    struct node* a;
    struct node* b;
    y = H1;
    z = H2;
    if(y != NULL){
        if(z != NULL && y->degree <= z->degree){
            H = y;
        } else if(z != NULL && y->degree > z->degree){
            H = z;
        } else {
            H = y;
        }
    } else {
        H = z;
    }
    while(y != NULL && z != NULL){
        if(y->degree < z->degree){
            y = y->sibling;
        } else if(y->degree == z->degree){
            a = y->sibling;
            y->sibling = z;
            y = a;
        } else {
            b = z->sibling;
            z->sibling = y;
            z = b;
        }
    }
    return H;
}

int DISPLAY(struct node* H){

    struct node* p;
    if(H == NULL){
        printf("\n heap empty");
        return 0;
    }
    printf("\nThe root node are:-\n");
    p = H;
    while(p != NULL){
        printf("%d",p->n);
        if(p->sibling != NULL){
            printf("-->");
        }
        p = p->sibling;
    }
    printf("\n");
}

struct node* bin_HEAP_EXTRACT_MIN(struct node* H1){

    int min;
    struct node* t = NULL;
    struct node* x = H1;
    struct node* Hr;
    struct node* p;

    Hr = NULL;

    if(x == NULL){
        printf("\nnothing to extract");
        return x;
    }
    p = x;
    while(p->sibling != NULL){
        if((p->sibling)->n < min){
            min = (p->sibling)->n;
            t = p;
            x = p->sibling;
        }
        p = p->sibling;
    }
    if(t == NULL && x->sibling == NULL){
        H1 = NULL;
    } else if(t == NULL){
        H1 = x->sibling;
    } else if(t->sibling == NULL){
        t = NULL;
    } else {
        t->sibling = x->sibling;
    }
    if(x->child != NULL){
        REVERT_LIST(x->child);
        (x->child)->sibling = NULL;
    }
    H = bin_HEAP_UNION(H1, Hr);
    return x;
}

int REVERT_LIST(struct node* y){

    if(y->sibling != NULL){
        REVERT_LIST(y->sibling);
        (y->sibling)->sibling = y;
    } else {
        Hr = y;
    }
}

struct node* FIND_NODE(struct node* H, int k){

    struct node* x = H;
    struct node* p = NULL;
    if(x->n == k){
        p = x;
        return p;
    }
    if(x->child != NULL && p == NULL){
        p = FIND_NODE(x->child, k);
    }
    if(x->sibling != NULL && p == NULL){
        p = FIND_NODE(x->sibling, k);
    }
    return p;
}

int bin_HEAP_DECREASE_KEY(struct node* H, int i, int k){
    
    int temp;
    struct node* p;
    struct node* y;
    struct node* z;
    p = FIND_NODE(H, i);
    if(p == NULL){
        printf("\ninvalid choice of key to be reduced");
        return 0;
    }
    if(k > p->n){
        printf("\nsorry! the new key is greater than current one");
        return 0;
    }
    p->n = k;
    y = p;
    z = p->parent;
    while(z != NULL && y->n < z->n){
        temp = y->n;
        y->n = z->n;
        z->n = temp;
        y = z;
        z = z->parent;
    }
    printf("\nkey reduced successfully!");
}

int bin_HEAP_DELETE(struct node* H, int k){

    struct node* np;
    if(H == NULL){
        printf("\nheap empty");
        return 0;
    }
    bin_HEAP_DECREASE_KEY(H, k, -1000);
    np = bin_HEAP_EXTRACT_MIN(H);
    if(np != NULL){
        printf("\nnode deleted successfully");
    }
}

int main(){

    int i,l;
    struct node* p;
    struct node* np;

    struct node* root;
    root = NULL;

    /*char ch;
    do{
        printf("\nmenu:-\n");
        printf("\n1) insert an element");
        printf("\n2) extract the minimum key node");
        printf("\n3) decrease a node key");
        printf("\n4) delete a node");
        printf("\n5) quit");
        scanf("%d" ,&l);
        switch (l)
        {
            case 1:
                do{
                    printf("\nenter the element to be inserted:");
                    scanf("%d" ,&m);
                    p = CREATE_NODE(m);
                    H = bin_HEAP_INSERT(H, p);
                    printf("\nnow the heap is: \n");
                    DISPLAY(H);
                    printf("\ninsert more(y/Y) = \n");
                    fflush(stdin);
                    scanf("%c" ,&ch);

                } while(ch == 'Y' || ch == 'y');
                break;
            
            case 2:
                do {
                    printf("\nEXTRACTING THE MINIMUM KEY NODE");
                    p = bin_HEAP_EXTRACT_MIN(H);
                    if (p != NULL)
                        printf("\nTHE EXTRACTED NODE IS %d", p->n);
                    printf("\nNOW THE HEAP IS:\n");
                    DISPLAY(H);
                    printf("\nEXTRACT MORE(y/Y)\n");
                    fflush(stdin);
                    scanf("%c", &ch);
                } while (ch == 'Y' || ch == 'y');
                break;

            case 3:
                do {
                    printf("\nENTER THE KEY OF THE NODE TO BE DECREASED:");
                    scanf("%d", &m);
                    printf("\nENTER THE NEW KEY : ");
                    scanf("%d", &l);
                    bin_HEAP_DECREASE_KEY(H, m, l);
                    printf("\nNOW THE HEAP IS:\n");
                    DISPLAY(H);
                    printf("\nDECREASE MORE(y/Y)\n");
                    fflush(stdin);
                    scanf("%c", &ch);
                } while (ch == 'Y' || ch == 'y');
                break;

            case 4:
                do {
                    printf("\nENTER THE KEY TO BE DELETED: ");
                    scanf("%d", &m);
                    bin_HEAP_DELETE(H, m);
                    printf("\nDELETE MORE(y/Y)\n");
                    fflush(stdin);
                    scanf("%c", &ch);
                } while (ch == 'y' || ch == 'Y');
                break;

            case 5:
                printf("\nthank you sir\n");
                break;
            
            default:
                printf("\ninvalid entry...try again....\n");
            }
    } while (l != 5);*/


    //
    double start;
    double end;
    double runtime;
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
            root = CREATE_NODE(rand_numbers[index]);
            H = bin_HEAP_INSERT(H, root);
            //check++;
        } else {
            //check--;
            root = bin_HEAP_EXTRACT_MIN(H);
            if (root != NULL){
                printf("\nTHE EXTRACTED NODE IS %d", root->n);
            }

        }
    }
    end = clock();
    runtime = end - start;
    printf("\nRuntime: %f ms" ,runtime/CLOCKS_PER_SEC*1000);
    printf("\nAverage Runtime: %f ms" ,runtime/CLOCKS_PER_SEC/5);


    return 0;
}
