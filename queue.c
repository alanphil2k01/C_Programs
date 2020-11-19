#include <stdio.h>

#define MAX 10

int queue[10];
int front=-1;
int rear=-1;

int isFull(){
    if(rear==MAX-1)
        return 1;
    else
        return 0;
}

int isEmpty(){
    if(rear<0 || front>rear){
        return 1;
}
    else
        return 0;
}

void enqueue(int item){
       if(isFull()==1)
           printf("Queue is full\n");
       else {
           if(front==-1){
               front++;
           }
           rear++;
           queue[rear]=item;
       }
}

void dequeue(){
    int data;
        if(isEmpty()==0){
            data=queue[front];
            front++;
            printf("%d was removed from the queue.\n",data);
        }
        else{
            printf("Queue is empty.\n");
        }
}

void display(){
    if(isEmpty()==0){
        for(int i=front==-1?0:front;i<=rear;i++){
            printf("%d\t",queue[i]);
        }
        printf("\n");
    }
    else{
        printf("Stack is empty.\n");
    }
}

void main(){
    int ch,item;
    printf("Menu\n1)Add Element to Queue\n2)Remove Element from Queue\n3)Print Queue\n4)Exit\n");
    do{
       printf("Enter Choice:"); 
       scanf("%d",&ch);
       switch(ch){
           case 1: printf("Enter item to add:");
                   scanf("%d",&item);
                   enqueue(item);
                   break;
           case 2: dequeue();
                   break;
           case 3: display();
                   break;
           case 4: printf("Good Bye.\n");
                    break;
           default: printf("Invalid Choice.\n");
       }
    } while(ch!=4);
}
