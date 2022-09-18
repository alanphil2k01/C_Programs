#include <stdio.h>

#define MAX 10

int stack[10];
int top=-1;

int isEmpty(){
    if(top==-1)
        return 1;
    else
        return 0;
}

void push(int item){
       if(top==MAX-1)
           printf("Stack is full\n");
       else {
           top++;
           stack[top]=item;
       }
}

void pop(){
    int data;
        if(isEmpty()==0){
            data=stack[top];
            top--;
            printf("%d was removed from the stack.\n",data);
        }
        else{
            printf("Stack is empty.\n");
        }
}

void display(){
    if(isEmpty()==0){
        for(int i=0;i<=top;i++){
            printf("%d\t",stack[i]);
        }
        printf("\n");
    }
    else{
        printf("Stack is empty.\n");
    }
}

void peek(){
    if(isEmpty()==1){
        printf("Stack is empty.\n");
    }
    else{
        printf("Top element=%d\n",stack[top]);
    }
}

void main(){
    int stack[10],ch,item;
    printf("Menu\n1)Push Element\n2)Pop Element\n3)Peek top element\n4)Print Stack\n5)Exit\n");
    do{
       printf("Enter Choice:"); 
       scanf("%d",&ch);
       switch(ch){
           case 1: printf("Enter item to add:");
                   scanf("%d",&item);
                   push(item);
                   break;
           case 2: pop();
                   break;
           case 3: peek();
                   break;
           case 4: display();
                   break;
           case 5: printf("Good Bye.\n");
                    break;
           default: printf("Invalid Choice.\n");
       }
    } while(ch!=5);
}
