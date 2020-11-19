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
    return 0;
}

void evaluatePrefix(char prefix[]){
    char symbol;
    int stack[100],top=-1,result,digit,num,num1,num2,multiplier;
    for(int i=strlen(prefix)-1;i>=0;i--){
        symbol=prefix[i];
        if(symbol==' '){
            continue;
        }
        if(isOperator(symbol)){
            num2=stack[top];
            top--;
            num1=stack[top];
            stack[top]=evaluate(num1,num2,symbol);
        }
        else{
            if(isdigit(symbol)){
                num=0;
                multiplier=1;
                do {
                    digit=symbol-'0';
                    num=digit*multiplier+num;
                    multiplier*=10;
                    if(isdigit(prefix[--i])){
                        symbol=prefix[i];
                    }
                }while(isdigit(prefix[i]));
            }
            top++;
            stack[top]=num;
        }
    }
    result=stack[top];
    printf("Result=%d\n",result);
}

int main() {
    char prefix[100];
    printf("Enter Prefix Expression:");
	scanf("%99[^\n]%*1[\n]",prefix);
    evaluatePrefix(prefix);
    return 0;
}
