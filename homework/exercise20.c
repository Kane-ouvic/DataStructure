#include <stdio.h>
#include <stdlib.h>

typedef struct node{

    int data, dist;
    struct node* right;
    struct node* left;
} node;

struct node* root;
struct node* temp;
struct node* r1;
struct node* r2;

void inorder(struct node* ptr);
void postorder(struct node* ptr);
int depth(struct node* ptr);
struct node* meld(struct node* h, struct node* k);
struct node* deletion(struct node* root);
struct node* insert(struct node* newroot);
void treemerge();

int main(void){

    int bkpoint = 0;
    int value;
    int val1;

    printf("\n****Lefist Max Heap Management****");
    printf("\nEnter root node\n");
    scanf("%d" ,&value);
    root = (struct node*)malloc(sizeof(struct node));
    root->right = NULL;
    root->left = NULL;
    root->dist = 0;
    root->data = value;

    while(1){
        printf("\nEnter ur option 1.insert\t2.Delete\t3.Traversal\t4.Meld\t5.exit\n");
        scanf("%d" ,&val1);

        switch(val1){
            case 1:
                root = insert(root);
                break;

            case 2:
                root = deletion(root);
                break;

            case 3:
                printf("Inorder traversal \n");
                inorder(root);

                printf("\nPostorder traversal \n");
                postorder(root);

                break;
            
            case 4:
                treemerge();
                break;
            
            case 5:
                bkpoint = 1;
                break;
            
            default:
                break;
            
        }
        if(bkpoint == 1){
            break;
        }
    }

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

struct node* insert(struct node* newroot){

    int val;
    struct node* z;
    struct node* x;
    z = (struct node *)malloc(sizeof(struct node));
    z->right = NULL;
    z->left = NULL;
    z->dist = 0;
    printf("Enter the value of the node to be added: ");
    scanf("%d" ,&val);
    z->data = val;
    newroot = meld(newroot, z);
    printf("Root element is %d\t distance value is %d" ,newroot->data ,newroot->dist + 1);
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
            r1 = insert(r1);
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
            r2 = insert(r2);
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