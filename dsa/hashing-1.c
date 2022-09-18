#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

int *hashTable;
int SIZE=13;
int noOfElements;

int hash(int);
void addKey(int);
void rehash();
void searchElement(int);
void showHashTable();

int hash(int key){
    return key % SIZE;
}

void addKey(int key){
    if(noOfElements==SIZE){
        printf("Stack Full. Rehashing.\n");
        rehash();
    }
    int value = hash(key);
    if(value<0)
        value=value+SIZE;
    while(hashTable[value]!=INT_MIN){
        value = (value+1)%SIZE;
    }
    hashTable[value]=key;
    noOfElements++;
}

void rehash(){
    int *oldTable=hashTable;
    SIZE=SIZE*2;
    noOfElements=0;
    hashTable=malloc(sizeof(int)*SIZE);
    for(int i=0;i<SIZE;i++){
        hashTable[i]=INT_MIN;
    }
    for(int i=0; i<=SIZE/2;i++)
        addKey(oldTable[i]);
    free(oldTable);
}

void searchElement(int key){
   int f=0;
   int start,i;
   start=i=hash(key);
   do{
        if(hashTable[i]==key){
            f=1;
            printf("Element found at index %d\n",i);
            break;
        }
        i=(i+1)%SIZE;
   }while(i!=start && hashTable[i]!=INT_MIN);
   if(f==0)
       printf("Element not found in Hash Table\n");
}

void showHashTable(){
    printf("Hash Table\n");
    printf("H(k)\tk\n");
    for(int i=0;i<SIZE;i++){
        if(hashTable[i]!=INT_MIN)
            printf("%d\t%d\n",i,hashTable[i]);
        else
         continue;
    }
}

int main(){
    hashTable=malloc(sizeof(int)*SIZE);
    for(int i=0;i<SIZE;i++){
        hashTable[i]=INT_MIN;
    }
    int value,ch;
    printf("Menu\n1)Add Value to Hash Table\n2)Search for Element\n3)Show Hash Table\n4)Exit\n");
    do{
        printf("Enter Choice:");
        scanf("%d",&ch);
        switch(ch){
            case 1: printf("Enter value:");
                    scanf("%d",&value);
                    addKey(value);
                    break;
            case 2: printf("Enter value:");
                    scanf("%d",&value);
                    searchElement(value);
                    break;
            case 3: showHashTable();
                    break;
            case 4: printf("Good Bye!\n");
                    break;
            default: printf("Invalid Choice\n");
        }
    }while(ch!=4);
    return 0;
}
