/*
Alan Philipose N.V.
CS3A
Roll no:3
Q35. Write a menu driven program in C to implement a binary search tree and to perform the following operations
        i. Insertion
        ii. Deletion
        iii. Searching
*/

#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node *left;
    struct node *right;
};

struct node *root;

void insertNode(int);
void searchNode(int);
void deleteNode(int);
void inorderTraverse(struct node*);

void insertNode(int data){
    struct node *current, *parent, *tempNode = (struct node*)malloc(sizeof(struct node));
    tempNode->data=data;
    tempNode->left=NULL;
    tempNode->right=NULL;
    if(root==NULL){
        root=tempNode;
        return;
    }
    current=root;
    parent=NULL;
    while(1){
        parent = current;
        if(data<parent->data){
            current=current->left;
            if(current==NULL){
                parent->left=tempNode;
                return;
            }
        }
        else{
            current=current->right;
            if(current==NULL){
                parent->right=tempNode;
                return;
            }
        }
    }
}

void searchNode(int data){
    struct node *current=root;
    printf("Searching for %d.\n", data);
    while(current!=NULL){
        if(current->data==data){
            printf("%d was found in the tree\n", current->data);
            return;
        }
        else if(current->data>data)
            current=current->left;
        else
            current=current->right;
    }
    printf("%d was NOT found in the tree\n", data);
}

void deleteNode(int data){
    struct node *temp, *parent;
    if(root == NULL){
        printf("The Tree is Empty !\n");
        return;
    }
    else{
        temp = root;
        parent = temp;
        while(temp!=NULL){
            if(temp->data<data){
                parent=temp;
                temp=temp->right;
            }
            else if(temp->data>data){
                parent=temp;
                temp=temp->left;
            }
            else{
                if((temp->left == NULL) && (temp->right == NULL)){
                    if(temp == root)
                        root = NULL;
                    else if((parent->left != NULL) && (parent->left)->data == data)
                        parent->left = NULL;
                    else
                        parent->right = NULL;
                }
                else if((temp->left == NULL) || (temp->right == NULL)){
                    if(temp == root)
                        root = (temp->left == NULL)?temp->right:temp->left;
                    else if((parent->left != NULL) && ((parent->left)->data == data)){
                        if(temp->left != NULL)
                            parent->left = temp->left;
                        else
                            parent->left = temp->right;
                    }
                    else if((parent->right != NULL) && (parent->right)->data == data){
                        if(temp->left != NULL)
                            parent->right = temp->left;
                        else
                            parent->right = temp->right;
                    }
                }
                else{
                    struct node *newnode;
                    struct node *parent;
                    newnode = temp->right;
                    parent = newnode;
                    while(newnode->left != NULL){
                        parent = newnode;
                        newnode = newnode->left;
                    }
                    if(newnode == parent){
                        temp->right = newnode->right;
                    }
                    parent->left = NULL;
                    temp->data = newnode->data;
                    temp=newnode;
                }
                free(temp);
                return;
            }
        }
    }
}

void inorderTraverse(struct node* root){
    if(root==NULL)
        return;
    inorderTraverse(root->left);
    printf("%d ", root->data);
    inorderTraverse(root->right);
}

int main(){
    int ch, item;
    printf("MENU\n1)Add node\n2)Search Element\n3)Delete Element\n4)Display tree(inorder)\n5)Exit\n");
    do{
        printf("Enter Choice: ");
        scanf("%d", &ch);
        switch(ch){
            case 1: printf("Enter element to be inserted: ");
                    scanf("%d", &item);
                    insertNode(item);
                    break;
            case 2: printf("Enter element to be searched: ");
                    scanf("%d", &item);
                    searchNode(item);
                    break;
            case 3: printf("Enter element to be deleted: ");
                    scanf("%d", &item);
                    deleteNode(item);
                    break;
            case 4: printf("Inorder Traversing:-\n");
                    printf("ROOT=%d\n", root->data);
                    inorderTraverse(root);
                    printf("\n");
                    break;
            case 5: printf("Good Bye...\n");
                    break;
            default: printf("Invalid Choice\n");
        }
    }while(ch!=5);
    return 0;
}
