/*
Alan Philipose N.V.
CS3A
Roll no:3
Q33. Write a program in C to perform Heap sort

*/
#include<stdio.h>

void display_array(int *arr,int n){
    for(int i=0;i<n;i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void swap(int *a, int *b){
    int temp=*a;
    *a=*b;
    *b=temp;
}

void heapify(int *arr, int i, int n){
   int largest=i, left=2*i+1, right=2*i+2;
   if(left<n && arr[left] > arr[largest])
       largest=left;
   if(right<n && arr[right] > arr[largest])
       largest=right;
   if(largest!=i){
       swap(&arr[i], &arr[largest]);
       heapify(arr, largest,n);
   }
}

void build_heap(int *arr, int n){
    for(int i=n/2-1; i>=0; i--)
        heapify(arr, i,n);
}

void heap_sort(int *arr, int n){
    build_heap(arr, n);
    for(int i=n-1; i>=0; i--){
        swap(&arr[0],&arr[i]);
        heapify(arr, 0, i);
    }
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
    heap_sort(arr, n);
    printf("\nArray after sorting\n");
    display_array(arr,n);
    return 0;
}
