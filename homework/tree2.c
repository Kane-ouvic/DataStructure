#include <stdio.h>
#include <stdlib.h>
#define M 4
//AB####CF####H######D####E####
typedef struct k{
    char data;
    struct k *child[M];
}tree;
/*前序遍历建树*/
tree *createTree()
{
    tree *t;int i;
    char x = getchar();
    /*1、如果是空树，则return Null*/
    if(x=='#') return NULL;
    /*2、如果只有一个根、则输出根*/
    t=(tree *)malloc(sizeof(tree));
    t->data=x;
    /*3、按照相同方法输出子树*/
    for(i=0;i<M;i++){
        t->child[i]=createTree();
    }
    return t;
}
/*函数功能：输出树的括号表示法*/
void printTree(tree *t)
{
    /*1、如果是空树，则return;*/
    if(t==NULL) return;
    /*2、输出根*/
    printf("%c",t->data);
    /*3、当有子树时，输出左括号*/
    if(t->child[0]!=NULL) printf("(");
    /*4、按照同样的方式输出子树*/
    int i;
    for(i=0;i<M;i++){
        printTree(t->child[i]);
        if(i<=2&&t->child[i+1]!=NULL) printf(",");
    }
    /*5、输出右括号*/
    if(t->child[0]!=NULL) printf(")");
}
int main()
{
    tree *T;
    (T)=createTree();
    printTree(T);
    return 0;
}