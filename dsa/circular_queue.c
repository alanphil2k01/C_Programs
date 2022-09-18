#include<stdio.h>
#include<stdbool.h>

int circular_queue[100];
int front=-1;
int rear=-1;
int SIZE=100;

bool isEmpty(){
    if(front==-1)
        return true;
    else
     return false;
}

bool isFull(){
    if((front==rear+1) || (front==0 && rear== SIZE-1))
        return true;
    else
     return false;
}

void enqueue(int item){
    if(isFull())
        printf("Circular Queue is Full.\n");
    else{
        if(front==-1)
            front=0;
        rear=(rear+1)%SIZE;
        circular_queue[rear]=item;
    }
}

void dequeue(){
    int data;
    if(isEmpty())
        printf("Circular Queue is Empty.\n");
    else{
        data=circular_queue[front];
        if(front==rear){
            front=-1;
            rear=-1;
        }
        else
            front=(front+1)%SIZE;
        printf("%d was removed from the circular queue.\n",data);
    }
}

void display(){
    if(isEmpty())
        printf("Circular Queue is Empty.\n");
    else{
        for(int i=front;i!=rear;i=(i+1)%SIZE)
            printf("%d\t",circular_queue[i]);
        printf("%d",circular_queue[rear]);
        printf("\n");
    }
}

int main(){
    int ch,item;
    printf("Enter size of the circular queue:");
    scanf("%d",&SIZE);
    printf("Menu\n1)Add Element to Circular Queue\n2)Remove Element from Circular Queue\n3)Print Circular Queue\n4)Exit\n");
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
    return 0;
}
