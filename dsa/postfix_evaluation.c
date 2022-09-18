#include<stdio.h>
#include<stdbool.h>
#include<ctype.h>
#include<string.h>

bool isOperator(char symbol){
    switch(symbol){
        case '+': 
        case '-': 
        case '*': 
        case '/': 
        case '^': return true;
    }
    return false;
}

int evaluate(int num1,int num2,char symbol){
    switch(symbol){
        case '+': return num2+num1;
        case '-': return num2-num1;
        case '*': return num2*num1;
        case '/': return num2/num1;
        case '^': return num2^num1;
    }
}
void evaluatePostfix(char postfix[]){
    char symbol;
    int stack[100],top=-1,result,digit,num,num1,num2;
    for(int i=0;i<strlen(postfix);i++){
        symbol=postfix[i];
        if(symbol==' '){
            continue;
        }
        if(isOperator(symbol)){
            num1=stack[top];
            top--;
            num2=stack[top];
            stack[top]=evaluate(num1,num2,symbol);
        }
        else{
            if(isdigit(symbol)){
                num=0;
                do {
                    digit=symbol-'0';
                    num=num*10+digit;
                    if(isdigit(postfix[++i])){
                        symbol=postfix[i];
                    }
                }while(isdigit(postfix[i]));
            }
            top++;
            stack[top]=num;
        }
    }
    result=stack[top];
    printf("Result=%d\n",result);
}

void main(){
    char postfix[100];
    printf("Enter Postfix Expression:");
	scanf("%99[^\n]%*1[\n]",postfix);
    evaluatePostfix(postfix);
}
