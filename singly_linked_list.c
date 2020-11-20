#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node *link;
};

struct node *start;

void insertBegin(int item){
    struct node *newNode = malloc(sizeof(struct node));
    newNode->data=item;
    newNode->link=NULL;
    if(start!=NULL)
        newNode->link=start;
    start=newNode;
}

void insertAfterNode(int item){
    struct node *newNode = malloc(sizeof(struct node)),*loc=start;
    int val;
    newNode->data=item;
    newNode->link=NULL;
    if(start==NULL)
        start=newNode;
    else{
        printf("Enter Item after which New Item must be Inserted:");
        scanf("%d",&val);
		while((loc!=NULL) && (loc->data!=val))
			loc=loc->link;
		newNode->link = loc->link;
		loc->link = newNode;
    }
}

void insertEnd(int item){
    struct node *newNode = malloc(sizeof(struct node));
    newNode->data=item;
    newNode->link=NULL;
    struct node *loc=start;
    while(loc->link!=NULL)
        loc=loc->link;
    loc->link=newNode;
}

void deleteNode(int item){
    if(start==NULL)
        printf("List is Empty.\n");
    else{
        struct node *prev=start,*loc=start;
        while((loc!=NULL) && (loc->data!=item)){
            prev=loc;
            loc=loc->link;
        }
        if(prev==loc){
            start=prev->link;
            return;
        }
        if(loc!=NULL)
            prev->link=loc->link;
        else
         printf("Failed to find Item.\n");
    }
}

void display(){
    if(start==NULL)
        printf("List is Empty.\n");
    else{
        struct node *loc=start;
        while(loc!=NULL){
            printf("%d\t",loc->data);
            loc=loc->link;
        }
        printf("\n");
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
