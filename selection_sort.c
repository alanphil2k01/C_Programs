#include<stdio.h>

void display_array(int *arr,int n){
    for(int i=0;i<n;i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void selection_sort(int *arr, int n){
    int small,temp;
    for(int i=0;i<n-1;i++){
        small=i;
        for(int j=i+1;j<n;j++){
            if(arr[j]<arr[small]){
                small=j;
            }
        }
        if(small!=i){
            temp=arr[i];
            arr[i]=arr[small];
            arr[small]=temp;
        }
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
    selection_sort(arr,n);
    printf("\nArray after sorting\n");
    display_array(arr,n);
    return 0;
}
