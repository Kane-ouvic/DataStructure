#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

#define BLANK ' '
#define TAB '\t'
#define MAX 50

char *pop();
char prefix[MAX];
char postfix[MAX];
char stack[MAX][MAX];
void push(char *str);
int isempty();
int white_space(char symbol);
void prefix_to_postfix();
void postfix_to_prefix();
int top;

int main()
{

        gets(prefix);
        gets(postfix);
        top = -1;
        prefix_to_postfix();
        top = -1;
        postfix_to_prefix();

}/*End of main()*/

void prefix_to_postfix()
{
        int i;
        char operand1[MAX], operand2[MAX];
        char symbol;
        char temp[2];
        char strin[MAX];
        for(i=strlen(prefix)-1;i>=0;i--)
        {
                symbol=prefix[i];
                temp[0]=symbol;
                temp[1]='\0';
                                
                if(!white_space(symbol))
                {
                        switch(symbol)
                        {
                        case '+':
                        case '-':
                        case '*':
                        case '/':
                        case '%':
                        case '^':
                                strcpy(operand1,pop());
                                strcpy(operand2,pop());
                                strcpy(strin,operand1);
                                strcat(strin,operand2);
                                strcat(strin,temp);             
                                push(strin);
                                break;
                        default: /*if an operand comes*/
                             push(temp);
                        }
                }
        }
        puts(stack[0]);
}/*End of prefix_to_postfix()*/

void postfix_to_prefix()
{
        int i;
        char operand1[MAX], operand2[MAX];
        char symbol;
        char temp[2];
        char strin[MAX];
        for(i=0;i<strlen(postfix);i++)
        {
                symbol=postfix[i];
                temp[0]=symbol;
                temp[1]='\0';

                if(!white_space(symbol))
                {
                        switch(symbol)
                        {
                        case '+':
                        case '-':
                        case '*':
                        case '/':
                        case '%':
                        case '^':
                                strcpy(operand1,pop());
                                strcpy(operand2,pop());
                                strcpy(strin,temp);
                                strcat(strin,operand2);
                                strcat(strin,operand1);
                                push(strin);
                                break;
                        default: /*if an operand comes*/
                             push(temp);
                        }
                }
        }
        puts(stack[0]);
}/*End of postfix_to_prefix()*/

void push(char *str)
{
        if(top > MAX)
        {
                exit(1);
        }
        else
        {
                top=top+1;
                strcpy( stack[top], str); 
        }
}

char *pop()
{
        if(top == -1 )
        {
                exit(2);
        }
        else
                return (stack[top--]);
}

int isempty()
{
        if(top==-1)
                return 1;
        else
                return 0;
}

int white_space(char symbol)
{
        if(symbol==BLANK || symbol==TAB || symbol=='\0')
                return 1;
        else
                return 0;
}