#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node *next;
    struct node *prev;
};

struct node *start;

void insertBegin(int item){
    struct node *newNode = malloc(sizeof(struct node));
    newNode->data=item;
    if(start==NULL)
        newNode->next=newNode->prev=newNode;
    else{
        struct node *last=start->prev;
        newNode->prev=last;
        newNode->next=start;
        last->next=start->prev=newNode;
    }
    start=newNode;
}

void insertAfterNode(int item){
    int val;
    struct node *newNode = malloc(sizeof(struct node));
    newNode->data=item;
    if(start==NULL){
        printf("List Empty. Adding Item as Start of List.\n");
        newNode->next=newNode->prev=newNode;
        start=newNode;
    }
    else{
        printf("Enter Item after which New Item must be Inserted:");
        scanf("%d",&val);
        struct node *loc=start;
        while(loc->data!=val && loc->next!=start)
            loc=loc->next;
        if(loc->data!=val) printf("Did not find item. Inserting to the end of List.\n");
        newNode->prev=loc;
        newNode->next=loc->next;
        (loc->next)->prev=newNode;
        loc->next=newNode;
    }
}

void insertEnd(int item){
    struct node *newNode = malloc(sizeof(struct node));
    newNode->data=item;
    if(start==NULL){
        newNode->next=newNode->prev=newNode;
        start=newNode;
    }
    else{
        struct node *last=start->prev;
        newNode->prev=last;
        newNode->next=start;
        last->next=start->prev=newNode;
    }
}

void deleteNode(int item){
    if(start==NULL)
        printf("List is Empty.\n");
    else{
        struct node *loc=start;
		while((loc->next!=start) && (loc->data!=item))
            loc=loc->next;
        if(loc->next==start && loc->data!=item)
            printf("Failed to find Item.\n");
        else if(loc==start){
            if(loc->next==start) 
                start=NULL;
            else{
                start=loc->next;
                start->prev=loc->prev;
            }
        }
        else {
            (loc->prev)->next=loc->next;
            (loc->next)->prev=loc->prev;
        }
    }
}

void display(){
    if(start==NULL)
        printf("List is Empty.\n");
    else{
        struct node *loc=start;
        while(loc->next!=start){
            printf("%d\t",loc->data);
            loc=loc->next;
        }
        printf("%d\n",loc->data);
    }
}

int main(){
    int ch,item;
    printf("MENU\n1)Insert Node at the Beginning of the List\n2)Inset Node after a particular Node\n3)Insert Node at the End of the List\n4)Delete Node containing a particular Item\n5)Display List\n6)Exit\n");
        do{
            printf("Enter choice:");
            scanf("%d",&ch);
            switch(ch){
                case 1: printf("Enter Item to Add:");
                        scanf("%d",&item);
                        insertBegin(item);
                        break;
                case 2: printf("Enter Item to Add:");
                        scanf("%d",&item);
                        insertAfterNode(item);
                        break;
                case 3: printf("Enter Item to Add:");
                        scanf("%d",&item);
                        insertEnd(item);
                        break;
                case 4: printf("Enter Item to Delete:");
                        scanf("%d",&item);
                        deleteNode(item);
                        break;
                case 5: display();
                        break;
                case 6: printf("Good Bye!\n");
                        break;
                default: printf("Invalid Choice.\n");
            }
        }while(ch!=6);
    return 0;
}
