#include<stdio.h>
#include<stdbool.h>

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

int getPrecedence(char symbol){
    switch(symbol){
        case '+': return 1;
        case '-': return 1; 
        case '*': return 2; 
        case '/': return 2; 
        case '^': return 3;
    }
}

bool precedenceGreater(char symbol1,char symbol2){
    if(symbol2=='('){
        return true;
    }
    else if(getPrecedence(symbol1)>getPrecedence(symbol2)){
        return true;
    }
    else if(getPrecedence(symbol1)<getPrecedence(symbol2)){
        return false;
    }
    else {
        if(symbol1=='^'){
            return true;
        }
        else 
            return false;
    }
    return false;
}

void infix_to_postfix(char infix[]){
    char symbol,stack[100], postfix[100];
    int top=-1,pos=0,data;
    for(int i=0;infix[i]!='\0';++i){
        symbol=infix[i];
        if(symbol=='('){
            top++;
            stack[top]=symbol; 
        }
        else if(symbol==')'){
            while(stack[top]!='('){
                data=stack[top];
                stack[top]='\0';
                top--;
                postfix[pos]=data;
                pos++;
            }
            stack[top]='\0';
            top--;
        }
        else if(isOperator(symbol)){
            while(true){
                if(top==-1){
                    top++;
                    stack[top]=symbol;
                    break;
                }
                else {
                    if(precedenceGreater(symbol,stack[top])){
                        top++;
                        stack[top]=symbol;
                        break;
                    }
                    else {
                        data=stack[top];
                        stack[top]='\0';
                        top--;
                        postfix[pos]=data;
                        pos++;
                    }
                }
            }
        }
        else{
            postfix[pos]=symbol;
            pos++;
        }
    }

    while(top!=-1){
        data=stack[top];
        stack[top]='\0';
        top--;
        postfix[pos]=data;
        pos++;
    }

    printf("Postfix Expression: %s\n",postfix);
}
void main(){
    char infix[100];
    printf("Enter Infix Expression:");
    scanf("%s",&infix);
    infix_to_postfix(infix);
}
