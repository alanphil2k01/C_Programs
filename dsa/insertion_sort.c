#include<stdio.h>

void display_array(int *arr,int n){
    for(int i=0;i<n;i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void insertion_sort(int *arr, int n){
    int temp;
    for(int i=1; i<n; i++){
        temp = arr[i];
        int j = i-1;
        while(temp<arr[j] && j>=0){
            arr[j+1] = arr[j];
            j = j-1;
        }
        arr[j+1] = temp;
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
    insertion_sort(arr,n);
    printf("\nArray after sorting\n");
    display_array(arr,n);
    return 0;
}
