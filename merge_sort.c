/*
Alan Philipose N.V.
CS3A
Roll no:3
Q32. Write a program in C to perform merge sort
*/
#include<stdio.h>

void display_array(int *arr,int n){
    for(int i=0;i<n;i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}
void merge(int *A, int first, int mid, int last){ 
    int j=0, lpt=first, upt=mid+1, n=last-first+1, B[n];
    while(lpt<mid+1 && upt<last+1){
        if(A[lpt]<A[upt]){
            B[j]=A[lpt];
            j++;
            lpt++;
        }
        else{
            B[j]=A[upt];
            j++;
            upt++;
        }
    }
    while(lpt<mid+1){
        B[j]=A[lpt];
        j++;
        lpt++;
    }
    while(upt<last+1){
        B[j]=A[upt];
        j++;
        upt++;
    }
    for(j=0, lpt=first; j<n; j++, lpt++)
        A[lpt]=B[j];
}

void merge_sort(int *arr, int first, int last){
    if(first==last)
        return;
    int mid=(first+last)/2;
    merge_sort(arr,first,mid);
    merge_sort(arr,mid+1,last);
    merge(arr,first,mid,last);
}

int main(){
    int n,*arr;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        printf("Enter number: ");
        scanf("%d", &arr[i]);
    }
    printf("\nArray before sorting\n");
    display_array(arr,n);
    merge_sort(arr,0, n-1);
    printf("\nArray after sorting\n");
    display_array(arr,n);
    return 0;
}
