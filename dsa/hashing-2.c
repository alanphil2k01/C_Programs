#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char **hashTable;
int SIZE=26;
int noOfElements=0;
int resolutionMethod=0;

int hash(char*);
void addKey(char*);
void rehash();
void searchElement(char*);
void showHashTable();

int hash(char *key){
    if(key[0]>='A' && key[0]<='Z')
	    return (key[0]-'A')%SIZE;
    else if(key[0]>='a' && key[0]<='z')
	    return (key[0]-'a')%SIZE;
    else if(key[0]>='0' && key[0]<='9')
	    return (key[0]-'0')%SIZE;
    else
	    return 0;
}

void addKey(char *key){
    if(noOfElements==SIZE){ 
        printf("Stack Full. Rehashing.\n");
        rehash();
    }
    int value=hash(key);
    if(resolutionMethod==1){
        while(hashTable[value]!=NULL){
            value=(value+1)%SIZE;
        }
        hashTable[value]=key;
        noOfElements++;
    }
    else if(resolutionMethod==2){
        int initial=value,f=0;
        for(int i=0;i<SIZE;i++){
            value=(initial+i*i)%SIZE;
            if(hashTable[value]==NULL){
                hashTable[value]=key;
                noOfElements++;
                f=1;
                break;
            }
        }
        if(f==0)
            printf("Key could not be added to Stack\n");
    }
}

void rehash(){
    char **oldTable=hashTable;
    SIZE=SIZE*2;
    noOfElements=0;
    hashTable=malloc(sizeof(char*)*SIZE);
    for(int i=0;i<SIZE;i++){
        hashTable[i]=NULL;
    }
    for(int i=0; i<=SIZE/2;i++)
        if(oldTable[i]!=NULL)
            addKey(oldTable[i]);
    free(oldTable);
}

void searchElement(char *key){
    int f=0,noOfComparisons=0;
    int start,i,count=0;
    start=i=hash(key);
    printf("%d",start);
    do{
        noOfComparisons++;
        if(strcmp(hashTable[i],key)==0){
            f=1;
            printf("Element found at index %d\n",i);
            break;
        }
        if(resolutionMethod==1)
            i=(i+1)%SIZE;
        else if(resolutionMethod==2){
            count++;
            i=(start+count*count)%SIZE;
        }
    }while(i!=start && hashTable[i]!=NULL);
    if(f==0)
        printf("Element not found in Hash Table\n");
    if(resolutionMethod==1)
        printf("It took %d comparisons to find key when using linear probing collision resolution method\n",noOfComparisons);
    else if(resolutionMethod==2)
        printf("It took %d comparisons to find key when using quadratic probing collision resolution method\n",noOfComparisons);
}

void showHashTable(){
    printf("Hash Table\n");
    printf("H(k)\tk\n");
    for(int i=0;i<SIZE;i++){
        if(hashTable[i]!=NULL)
            printf("%d\t%s\n",i,hashTable[i]);
        else
         continue;
    }
}

int main(){
    hashTable=malloc(sizeof(char*)*SIZE);
    for(int i=0;i<SIZE;i++){
        hashTable[i]=NULL;
    }
    int ch;
    printf("Select Collision Resolution Method:-\n1)Linear Probing\n2)Quadratic Probing\n");
    while(1){
        printf("Enter Choice:");
        scanf("%d",&ch);
        if(ch==1){
            resolutionMethod=1;
            break;
        }
        else if(ch==2){
            resolutionMethod=2;
            break;
        }
        else
            printf("Invalid choicc\n");
    }
    printf("Menu\n1)Add Value to Hash Table\n2)Search for Element\n3)Show Hash Table\n4)Exit\n");
    do{
        char *value=malloc(sizeof(char)*64);
        printf("Enter Choice:");
        scanf("%d",&ch);
        switch(ch){
            case 1: printf("Enter value:");
                    scanf("%s",value);
                    addKey(value);
                    break;
            case 2: printf("Enter value:");
                    scanf("%s",value);
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
