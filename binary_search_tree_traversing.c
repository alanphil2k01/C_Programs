/*
Alan Philipose N.V.
CS3A
Roll no:3
Q34.Write a menu driven program in C to implement a binary search tree and to perform the following operations
    Traversing – inorder, preorder, & postorder
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
void inorderTraverse(struct node*);
void preorderTraverse(struct node*);
void postorderTraverse(struct node*);

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

void inorderTraverse(struct node* root){
    if(root==NULL)
        return;
    inorderTraverse(root->left);
    printf("%d ", root->data);
    inorderTraverse(root->right);
}

void preorderTraverse(struct node* root){
    if(root==NULL)
        return;
    printf("%d ", root->data);
    preorderTraverse(root->left);
    preorderTraverse(root->right);
}

void postorderTraverse(struct node* root){
    if(root==NULL)
        return;
    postorderTraverse(root->left);
    postorderTraverse(root->right);
    printf("%d ", root->data);
}

int main(){
    int ch, item;
    printf("MENU\n1)Add node\n2)Inorder traversing\n3)Preorder Traversing\n4)Postorder Traversing\n5)Exit\n");
    do{
        printf("Enter Choice: ");
        scanf("%d", &ch);
        switch(ch){
            case 1: printf("Enter element to be inserted: ");
                    scanf("%d", &item);
                    insertNode(item);
                    break;
            case 2: printf("Inorder Traversing:-\n");
                    inorderTraverse(root);
                    printf("\n");
                    break;
            case 3: printf("Preorder Traversing:-\n");
                    preorderTraverse(root);
                    printf("\n");
                    break;
            case 4: printf("Postorder Traversing:-\n");
                    postorderTraverse(root);
                    printf("\n");
                    break;
            case 5: printf("Good Bye...\n");
                    break;
            default: printf("Invalid Choice\n");
        }
    }while(ch!=5);
    return 0;
}
