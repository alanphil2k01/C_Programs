#include <stdio.h>

int stack[100];
int top1=-1;
int top2=-1;
int max_size=100;

void push(int item){
    int x;
    printf("Enter stack number:");
    scanf("%d",&x);
    if(x==1){
        if(top1==(max_size-1) || top1==(top2-1)){
            printf("Stacks are full\n");
        }
        else{
            top1++;
            stack[top1]=item;
        }
    }
    else if(x==2){
        if(top2<0 || top2==(top1+1)){
            printf("Stacks are full\n");
        }
        else{
            top2--;
            stack[top2]=item;
        }
    }
    else{
        printf("Invalid stack number\n");
    }
}

void pop(){
    int x,data;
    printf("Enter stack number:");
    scanf("%d",&x);
    if(x==1){
        if(top1>=0){
            data=stack[top1];
            top1--;
            printf("%d was removed from the stack %d.\n",data,x);
        }
        else{
            printf("Stack %d is empty\n",x);
        }
    }
    else if(x==2){
        if(top2 < max_size){
            data=stack[top2];
            top2++;
            printf("%d was removed from the stack %d.\n",data,x);
        }
        else{
            printf("Stack %d is empty.\n",x);
        }
    }
    else{
        printf("Invalid stack number\n");
    }
}

void peek(){
    int x;
    printf("Enter stack number:");
    scanf("%d",&x);
    if(x==1){
        if(top1>=0){
            printf("Top element=%d\n",stack[top1]);
        }
        else{
            printf("Stack %d is empty.\n",x);
        }
    }
    else if(x==2){
        if(top2<max_size){
            printf("Top element=%d\n",stack[top2]);
        }
        else{
            printf("Stack %d is empty.\n",x);
        }
    }
    else{
        printf("Invalid stack number\n");
    }
}

void display(){
    int i;
    printf("Stack 1:");
    if(top1>=0){
        for(i=0;i<=top1;i++){
            printf("%d\t",stack[i]);
        }
        printf("\n");
}
    else{
        printf("Empty\n");
    }
    printf("Stack 2:");
    if(top2<max_size){
        for(i=max_size-1;i>=top2;i--){
            printf("%d\t",stack[i]);
        }
        printf("\n");
    }
    else{
        printf("Empty\n");
    }
}

void main(){
    int stack[10],ch,item;
    printf("Enter maximum size of array:");
    scanf("%d",&max_size);
    top2=max_size;
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
