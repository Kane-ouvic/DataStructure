#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct threaded_tree{
    char data;
    struct threaded_tree *left, *right;
    int left_thread, right_thread;
}threaded_pointer;
threaded_pointer *root;

threaded_pointer *insuc(threaded_pointer *tree){
    threaded_pointer *temp=tree->right;
    if ( tree->right_thread ){
        while ( temp->left_thread ){
            temp=temp->left;
        }
    }
    return temp;
}

void insert_right(threaded_pointer *parent, threaded_pointer *child){
    threaded_pointer *temp;

    child->right=parent->right;
    child->right_thread=parent->right_thread;

    child->left=parent;
    child->left_thread=0;

    parent->right=child;
    parent->right_thread=1;

    if ( child->right_thread ){
        temp=insuc(child);
        temp->left=child;
    }
}

void insert_left(threaded_pointer *parent, threaded_pointer *child){
    threaded_pointer *temp;

    child->left=parent->left;
    child->left_thread=parent->left_thread;

    child->right=parent;
    child->right_thread=0;

    parent->left=child;
    parent->left_thread=1;

    if ( child->left_thread ){
        temp=insuc(child);
        temp->right=child;
    }
}

 

void inorder(){
    threaded_pointer *tempNode=root;
    do{
        if (tempNode->right_thread == 0)
            tempNode=tempNode->right;
        else {
            tempNode=tempNode->right;
            while (tempNode->left_thread != 0)
                tempNode=tempNode->left;
        }
        if (tempNode != root)
            printf("%c ", tempNode->data);
    }while (tempNode != root);
    printf("\n");
}

int main(){
    char string[100];
    gets(string);
    int length=strlen(string);
    root=(threaded_pointer *)malloc(sizeof(threaded_pointer));
    root->right=NULL;
    root->left=root;
    root->data='0';
    root->right_thread=1;
    root->left_thread=0;

    threaded_pointer *first=(threaded_pointer *)malloc(sizeof(threaded_pointer));
    first->data=string[0];
    root->right=first;
    first->left_thread=first->right_thread=0;
    first->left=first->right=root;

    int i;
    int flag=0; //0 -> left 1 ->right
    threaded_pointer *pre=first;
    for (i=1; i<length; i++){
        threaded_pointer *new_node=(threaded_pointer *)malloc(sizeof(threaded_pointer));
        if (string[i] != ' '){
            new_node->data=string[i];
            new_node->left=new_node->right=root;
            new_node->left_thread=new_node->right_thread=0;

            if ( !flag )
                insert_left(pre, new_node);
            else
                insert_right(pre, new_node);

 

            pre=new_node;
            flag=0;
        }
        else{
            if ( !flag )
                flag=1;
            else
                pre=pre->right;
        }
    }
    inorder();
    return 0;
}