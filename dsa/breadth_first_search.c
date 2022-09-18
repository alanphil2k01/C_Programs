#include<stdio.h>
#include<stdlib.h>

struct node{
    int vertex;
    struct node *next;
};

struct node **adjList;
int *visited, vertices=0, *queue, front=-1, rear=-1;

int isEmpty(){
    if(rear<0 || front>rear)
        return 1;
    return 0;
}

void addqueue(int data){
    if(front==-1)
        front++;
    rear++;
    queue[rear]=data;
}

int deletequeue(){
    int data=queue[front];
    front++;
    if(isEmpty()){
        front=-1;
        rear=-1;
    }
    return data;
}

void BFS(int i){
    int w;
    struct node *p;
    p=adjList[i];
    visited[i]=1;
    addqueue(i);
    printf("%d\t",i);
    while(!isEmpty()){
        int data=deletequeue();
        p=adjList[data];
        while(p!=NULL){
            w=p->vertex;
            if(!visited[w]){
                printf("%d\t", w);
                addqueue(w);
                visited[w]=1;
            }
            p=p->next;
        }
    }
    printf("\n");
}

void insert(int v1, int v2){
    struct node* loc;
    struct node* temp1 = malloc(sizeof(struct node));
    temp1->vertex=v2;
    temp1->next=NULL;
    if(adjList[v1]==NULL){
        adjList[v1]=temp1;
    }else{
        loc=adjList[v1];
        while(loc->next!=NULL)
            loc=loc->next;
        loc->next=temp1;
    }
    struct node* temp2 = malloc(sizeof(struct node));
    temp2->vertex=v1;
    temp2->next=NULL;
    if(adjList[v2]==NULL){
        adjList[v2]=temp2;
    }else{
        loc=adjList[v2];
        while(loc->next!=NULL)
            loc=loc->next;
        loc->next=temp2;
    }
}

void read_graph(){
    int neighbour, vertex;
    printf("Enter number of vertices: ");
    scanf("%d", &vertices);
    adjList=malloc(sizeof(struct node*)*vertices);
    for(int i=0; i<vertices; i++)
        adjList[i]=NULL;
    printf("Vertices from %d to %d created\n", 0, vertices-1);
    for(int i=0; i < vertices; i++){
        ReEnterNeighbours:
            printf("Enter number of negibours for vertex %d: ", i);
            scanf("%d", &neighbour);
            if(neighbour<0 || neighbour>=vertices){
                printf("Invalid number of neighbours. Number of neighbours should be between %d and %d\n", 0, vertices);
                goto ReEnterNeighbours;
            }
            printf("Enter ALL neighbour vertices that are not already linkeb before:-\n");
            for(int j=0;j < neighbour; j++){
                ReEnterVertex:
                    scanf("%d", &vertex);
                    if(vertex<0 || vertex>=vertices){
                        printf("Invalid neighbour vertex. Only vertex value between %d and %d allowed\n", 0, vertices-1);
                        goto ReEnterVertex;
                    }
                    insert(i,vertex);
            }
    }
}

void displayList(){
    struct node* temp;
    printf("The adjacency list is as follows with each vertex linked to its neighbouring vertices\n");
    for(int i=0; i<vertices; i++){
        printf("%d",i);
        temp=adjList[i];
        while(temp!=NULL){
            printf("->%d", temp->vertex);
            temp=temp->next;
        }
        printf("\n");
    }
}

int main(){
    int ch, start;
    read_graph();
    printf("MENU\n1)Re-enter Graph\n2)Breadth First Search\n3)Display adjacency list\n4)Exit\n");
    do{
        printf("Enter choice: ");
        scanf("%d", &ch);
        switch (ch){
            case 1: read_graph();
                    break;
            case 2: printf("Enter start vertex: ");
                    scanf("%d", &start);
                    visited=calloc(sizeof(int), vertices);
                    queue=calloc(sizeof(int), vertices);
                    BFS(start);
                    break;
            case 3: displayList();
                    break;
            case 4: printf("Good Bye.\n");
                    break;
            default: printf("Invalid choice.\n");
        }
    }while(ch!=4);
    return 0;
}
