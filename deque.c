#include<stdio.h>
#include<stdbool.h>

int deque[100];
int front=-1;
int rear=-1;
int SIZE=100;

bool isFull(){
    if((rear+1)%SIZE==front)
        return true;
    else
     return false;
}

bool isEmpty(){
    if(front==-1 && rear==-1)
        return true;
    else
     return false;
}

void enqueueFront(int item){
    if(isFull())
        printf("Deque is Full.\n");
    else{
        if(isEmpty()){
            front=0;
            rear=0;
        }
        else
            front=(front+SIZE-1)%SIZE;
        deque[front]=item;
    }
}

void enqueueRear(int item){
    if(isFull())
        printf("Deque is Full.\n");
    else{
        if(isEmpty()){
            front=0;
            rear=0;
        }
        else
            rear=(rear+1)%SIZE;
        deque[rear]=item;
    }
}

void dequeueFront(){
    int data;
    if(isEmpty())
        printf("Deque is Empty.\n");
    else{
        data=deque[front];
        if(front==rear){
            front=-1;
            rear=-1;
        }
        else
            front=(front+1)%SIZE;
        printf("%d was Removed from Front of Deque\n",data);
    }
}

void dequeueRear(){
    int data;
    if(isEmpty())
        printf("Deque is Empty.\n");
    else{
        data=deque[rear];
        if(front==rear){
            front=-1;
            rear=-1;
        }
        else
            rear=(rear+SIZE-1)%SIZE;
        printf("%d was Removed from Rear of Deque\n",data);
    }
}

void display(){
    if(isEmpty())
        printf("Deque is Empty.\n");
    else{
        for(int i=front;i!=rear;i=(i+1)%SIZE)
            printf("%d\t",deque[i]);
        printf("%d\n",deque[rear]);
    }
}

int main(){
    int ch,item;
    printf("Enter Size of Deque:");
    scanf("%d", &SIZE);
    printf("MENU\n1)Add Element to Front of Deque\n2)Add Element to Rear of Deque\n3)Remove Element from Front of Deque\n4)Remove Element from Rear of Deque\n5)Print Deque\n6)Exit\n");
    do{
        printf("Enter choice:");
        scanf("%d", &ch);
       switch(ch){
           case 1: printf("Enter Item to Add:");
                   scanf("%d",&item);
                   enqueueFront(item);
                   break;
           case 2: printf("Enter Item to Add:");
                   scanf("%d",&item);
                   enqueueRear(item);
                   break;
           case 3: dequeueFront();
                   break;
           case 4: dequeueRear();
                   break;
           case 5: display();
                   break;
           case 6: printf("Good Bye.\n");
                    break;
           default: printf("Invalid Choice.\n");
       }
    }while(ch!=6);
    return 0;
}
