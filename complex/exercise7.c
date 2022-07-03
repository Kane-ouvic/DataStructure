#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 100;
#define TRUE 1;
#define FALSE 0;

typedef struct polyNode{

    int coef;
    int expon;
    struct polyNode* link;

} polyNode;

int COMPARE(int x, int y);
struct polyNode* newNode(int coef, int expon);
struct polyNode* pread(int* poly, int count);
struct polyNode* pmult(polyNode* expressionA, polyNode* expressionB);
struct polyNode* padd(polyNode* expressionA, polyNode* expressionB);
struct polyNode* psub(polyNode* expressionA, polyNode* expressionB);
struct polyNode* paddFix(polyNode* expressionA, polyNode* expressionB);
void pwrite(polyNode* top);
void perase(polyNode* top);
void attach(int coef, int expon, polyNode* *ptr);
double eval(polyNode* resultC, double x);

int main(void){

    int test[8] = {2,2,1,1,3,3,4,4};
    polyNode* expressionA;
    polyNode* expressionB;
    polyNode* resultC;
    int A_input[100];
    int B_input[100];
    int times;
    //char pread_str[] = "pread";

    scanf("%d" ,&times);
    
    for(int i = 0; i < times; i++){
        char input_category[20];
        scanf("%s" ,input_category);
        //printf("--------1\n");
        if(strcmp(input_category, "pread") == 0){

            char input_expression[20];
            scanf("%s" ,input_expression);
            if(strcmp(input_expression, "expressionA") == 0){
                //printf("--------2\n");
                int count;
                scanf("%d", &count);
                for(int j = 0; j < count*2; j++){
                    int input_number;
                    scanf("%d" ,&input_number);
                    A_input[j] = input_number;
                }
                expressionA = pread(A_input, count);
                printf("ok\n");
            } else if(strcmp(input_expression, "expressionB") == 0){
                int count;
                scanf("%d" ,&count);
                for(int j = 0; j < count*2; j++){
                    int input_number;
                    scanf("%d" ,&input_number);
                    B_input[j] = input_number;
                }
                expressionB = pread(B_input, count);
                printf("ok\n");
            }
        }

        if(strcmp(input_category, "pwrite") == 0){
            char input_expression[20];
            scanf("%s" ,input_expression);
            if(strcmp(input_expression, "expressionA") == 0){
                pwrite(expressionA);
                printf("\n");
            }
            if(strcmp(input_expression, "expressionB") == 0){
                pwrite(expressionB);
                printf("\n");
            }
            if(strcmp(input_expression, "resultC") == 0){
                pwrite(resultC);
                printf("\n");
            }
        }

        if(strcmp(input_category, "eval") == 0){
            char input_expression[20];
            scanf("%s" ,input_expression);
            if(strcmp(input_expression, "resultC") == 0){
                double x;
                scanf("%lf", &x);
                printf("%.2lf",eval(resultC, x));
            }
        }

        if(strcmp(input_category, "perase") == 0){
            char input_expression[20];
            scanf("%s" ,input_expression);
            if(strcmp(input_expression, "resultC") == 0){
                perase(resultC);
                resultC = NULL;
            }
        }

        if(strcmp(input_category, "padd") == 0){
            char input_expression1[20];
            char input_expression2[20];
            char input_expression3[20];
            scanf("%s %s %s" ,input_expression1 ,input_expression2 ,input_expression3);
            if(strcmp(input_expression1, "resultC") == 0 && strcmp(input_expression2, "expressionA") == 0 && strcmp(input_expression3, "expressionB") == 0){
                resultC = padd(expressionA, expressionB);
                //pwrite(resultC);
                //printf("\n");
            }
        }

        if(strcmp(input_category, "psub") == 0){
            char input_expression1[20];
            char input_expression2[20];
            char input_expression3[20];
            scanf("%s %s %s" ,input_expression1 ,input_expression2 ,input_expression3);
            if(strcmp(input_expression1, "resultC") == 0 && strcmp(input_expression2, "expressionA") == 0 && strcmp(input_expression3, "expressionB") == 0){
                resultC = psub(expressionA, expressionB);
                //pwrite(resultC);
                //printf("\n");
            }
        }

        if(strcmp(input_category, "pmult") == 0){
            char input_expression1[20];
            char input_expression2[20];
            char input_expression3[20];
            scanf("%s %s %s" ,input_expression1 ,input_expression2 ,input_expression3);
            if(strcmp(input_expression1, "resultC") == 0 && strcmp(input_expression2, "expressionA") == 0 && strcmp(input_expression3, "expressionB") == 0){
                resultC = pmult(expressionB, expressionA);
                //pwrite(resultC);
                //printf("\n");
            }
        }


    }
    //resultC = pmult(expressionB, expressionA);
    //pwrite(resultC);
}

struct polyNode* pmult(polyNode* expressionA, polyNode* expressionB){

    struct polyNode* ptrA = expressionA;
    struct polyNode* ptrB = expressionB;
    struct polyNode* topA = expressionA;
    struct polyNode* topB = expressionB;
    struct polyNode* ptrC;
    struct polyNode* topC;
    struct polyNode* pre;
    int count = 0;
    int checkA = 0;
    int checkB = 0;
    int doneA = 0;
    int doneB = 0;

    for(;checkA < 2 ; ptrA = ptrA->link){
        if(ptrA == topA) checkA++;
        if(checkA == 2) break;
        for(;checkB < 2; ptrB = ptrB->link){
            if(ptrB == topB) checkB++;
            if(checkB == 2) break;
            if(count == 0){
                    topC = newNode(ptrA->coef*ptrB->coef, ptrA->expon + ptrB->expon);
                    pre = topC;
                    count++;
                    //printf("------------------Test1\n");
                } else {
                    ptrC = newNode(ptrA->coef*ptrB->coef, ptrA->expon + ptrB->expon);
                    pre->link = ptrC;
                    pre = ptrC;
                    //printf("------------------Test2\n");
                }
            //printf("A-- c: %d e: %d ,B-- c: %d e: %d ",ptrA->coef ,ptrA->expon ,ptrB->coef ,ptrB->expon);
            //printf("A: %d B: %d\n" ,checkA ,checkB);
            
        }
        checkB = 0;
    }
    printf("multiplied\n");
    ptrC->link = topC;
    return topC;

}

struct polyNode* padd(polyNode* expressionA, polyNode* expressionB){

    struct polyNode* ptrA = expressionA;
    struct polyNode* ptrB = expressionB;
    struct polyNode* topA = expressionA;
    struct polyNode* topB = expressionB;
    struct polyNode* ptrC;
    struct polyNode* topC;
    struct polyNode* pre;
    int count = 0;
    int sum = 0;
    int done = 0;

    while(!done){

        switch(COMPARE(ptrA->expon, ptrB->expon)){

            case -1:
                if(count == 0){
                    topC = newNode(ptrB->coef, ptrB->expon);
                    pre = topC;
                    count++;
                } else {
                    ptrC = newNode(ptrB->coef, ptrB->expon);
                    pre->link = ptrC;
                    pre = ptrC;
                }
                ptrB = ptrB->link; if(ptrB == topB) done = 1;
                //printf("---------------1");
                break;

            case 0:
    
                sum = ptrA->coef + ptrB->coef;
                if(sum) {

                    if(count == 0){
                        topC = newNode(sum, ptrB->expon);
                        pre = topC;
                        count++;
                    } else {
                        ptrC = newNode(sum, ptrB->expon);
                        pre->link = ptrC;
                        pre = ptrC;
                    }
                }
                ptrA = ptrA->link; if(ptrA == topA) done = 1;
                ptrB = ptrB->link; if(ptrB == topB) done = 1;
                //printf("---------------2");
                break;

            case 1:
                if(count == 0){
                    topC = newNode(ptrA->coef, ptrA->expon);
                    pre = topC;
                    count++;
                } else {
                    ptrC = newNode(ptrA->coef, ptrA->expon);
                    pre->link = ptrC;
                    pre = ptrC;
                }
                ptrA = ptrA->link; if(ptrA == topA) done = 1;
                //printf("---------------3");
                break;
        }
        
        //if(ptrB == topB) done = 1;
    }
    //printf("---------------4\n");
    for(;ptrA != topA; ptrA = ptrA->link ){
        if(count == 0){
            topC = newNode(ptrA->coef, ptrA->expon);
            pre = topC;
            count++;
        } else {
            ptrC = newNode(ptrA->coef, ptrA->expon);
            pre->link = ptrC;
        }
    }
    for(;ptrB != topB; ptrB = ptrB->link){
        if(count == 0){
            topC = newNode(ptrB->coef, ptrB->expon);
            pre = topC;
            count++;
        } else {
            ptrC = newNode(ptrB->coef, ptrB->expon);
            pre->link = ptrC;
        }
    }
    printf("added\n");
    ptrC->link = topC;
    return topC;

}

struct polyNode* psub(polyNode* expressionA, polyNode* expressionB){

    struct polyNode* ptrA = expressionA;
    struct polyNode* ptrB = expressionB;
    struct polyNode* topA = expressionA;
    struct polyNode* topB = expressionB;
    struct polyNode* ptrC;
    struct polyNode* topC;
    struct polyNode* pre;
    int count = 0;
    int sum = 0;
    int done = 0;

    while(!done){

        switch(COMPARE(ptrA->expon, ptrB->expon)){

            case -1:
                if(count == 0){
                    topC = newNode(-ptrB->coef, ptrB->expon);
                    pre = topC;
                    count++;
                } else {
                    ptrC = newNode(-ptrB->coef, ptrB->expon);
                    pre->link = ptrC;
                    pre = ptrC;
                }
                ptrB = ptrB->link; if(ptrB == topB) done = 1;
                break;

            case 0:
    
                sum = ptrA->coef - ptrB->coef;
                if(sum) {

                    if(count == 0){
                        topC = newNode(sum, ptrB->expon);
                        pre = topC;
                        count++;
                    } else {
                        ptrC = newNode(sum, ptrB->expon);
                        pre->link = ptrC;
                        pre = ptrC;
                    }
                }
                ptrA = ptrA->link; if(ptrA == topA) done = 1;
                ptrB = ptrB->link; if(ptrB == topB) done = 1;
                break;

            case 1:
                if(count == 0){
                    topC = newNode(ptrA->coef, ptrA->expon);
                    pre = topC;
                    count++;
                } else {
                    ptrC = newNode(ptrA->coef, ptrA->expon);
                    pre->link = ptrC;
                    pre = ptrC;
                }
                ptrA = ptrA->link; if(ptrA == topA) done = 1;
                break;
        }
        
        //if(ptrB == topB) done = 1;
    }
    //printf("---------------4\n");
    for(;ptrA != topA; ptrA = ptrA->link ){
        if(count == 0){
            topC = newNode(ptrA->coef, ptrA->expon);
            pre = topC;
            count++;
        } else {
            ptrC = newNode(ptrA->coef, ptrA->expon);
            pre->link = ptrC;
        }
    }
    for(;ptrB != topB; ptrB = ptrB->link){
        if(count == 0){
            topC = newNode(-ptrB->coef, ptrB->expon);
            pre = topC;
            count++;
        } else {
            ptrC = newNode(-ptrB->coef, ptrB->expon);
            pre->link = ptrC;
        }
    }
    printf("substracted\n");
    ptrC->link = topC;
    return topC;

}

/*struct polyNode* padd(polyNode* expressionA, polyNode* expressionB){

    polyNode* startA;
    polyNode* c; 
    polyNode* lastC;
    polyNode* ptrA = expressionA;
    polyNode* ptrB = expressionB;
    polyNode* topA = expressionA;
    polyNode* topB = expressionB;
    int sum = 0;
    int done = FALSE;

    startA = expressionA;
    //ptrA = ptrA->link;
    //ptrB = ptrB->link;
    c = newNode(0, -1);
    lastC = c;
    do{
        switch(COMPARE(ptrA->expon, ptrB->expon)){

            case -1:
                attach(ptrB->coef, ptrB->expon, &lastC);
                ptrB = ptrB->link;
                printf("---------------1");
                break;

            case 0:
                if(startA == ptrA) {
                    done = TRUE;
                } else {
                    sum = ptrA->coef + ptrB->coef;
                    if(sum) attach(sum, ptrA->expon, &lastC);
                    expressionA = ptrA->link;
                    expressionB = ptrB->link;
                    printf("---------------2");
                }
                break;

            case 1:
                attach(ptrA->coef, ptrA->expon, &lastC);
                ptrA = ptrA->link;
                printf("---------------3");
                break;

        }

    } while(ptrA != topA && ptrB != topB);

    for(;ptrA->link != topA; ptrA = ptrA->link ){
        attach(ptrA->coef, ptrA->expon, &lastC);
    }
    for(;ptrB->link != topB; ptrB = ptrB->link ){
        attach(ptrB->coef, ptrB->expon, &lastC);
    }
    //pwrite(expressionA);
    lastC->link = c;
    return c;
}*/

struct polyNode* newNode(int coef, int expon){

    struct polyNode* node =  (struct polyNode*)malloc(sizeof(struct polyNode));
    node->coef = coef;
    node->expon = expon;
    return node;
}

struct polyNode* pread(int* poly, int count){

    polyNode* top;
    polyNode* temp;
    polyNode* pre;
    
    for(int i = 0; i < count*2; i+=2){

        if(i == 0){
            top = newNode(poly[i], poly[i+1]);
            pre = top;
        } else if(i == 2*count-2){
            temp = newNode(poly[i], poly[i+1]);
            pre->link = temp;
            temp->link = top;
        } else {
            temp = newNode(poly[i], poly[i+1]);
            pre->link = temp;
            pre = temp;

        }

    }
    return top;


}

double eval(polyNode* resultC, double x){

    polyNode* ptr = resultC;
    double result = 0.0;
    for(; ptr->link != resultC; ptr = ptr->link){

        result += pow(x, ptr->expon)*ptr->coef;
    }
    result += pow(x, ptr->expon)*ptr->coef;
    return result;

}

void pwrite(polyNode* top){

    polyNode* ptr = top;
    int check = 0;
    for(;check != 2; ptr = ptr->link){
        if(ptr == top) check++;
        if(check == 2) break;
        if(ptr->coef > 0 && ptr->link != top){
            printf("%dx^%d+" ,ptr->coef ,ptr->expon);
        } else {
            printf("%dx^%d" ,ptr->coef ,ptr->expon);
        }
        
        //if(ptr == top) check++;
    }
}

void perase(polyNode* top){

    polyNode* ptr = top;
    int check = 0;
    
    while(ptr->link != top){
        polyNode* temp = ptr;
        ptr = ptr->link;
        //if(ptr->link == NULL) free(ptr);
        free(temp);
    }


    printf("erased\n");
}

void attach(int coef, int expon, polyNode* *ptr){

    polyNode*  temp = newNode(coef, expon);
    (*ptr)->link = temp;
    (*ptr) = temp;
}


int COMPARE(int x, int y){

    if(x < y){
        return -1;
    } else if(x == y){
        return 0;
    } else {
        return 1;
    }
}
