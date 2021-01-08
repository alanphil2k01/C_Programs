#include<stdio.h>

void display_array(int *arr,int n){
    for(int i=0;i<n;i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int partition(int *arr,int lb,int ub){
	int pivot,up,down,temp;
	pivot=arr[lb];
	up=ub;
	down=lb;
	while(down<up){
		while(arr[down]<=pivot && down<ub)
			down++;
		while(arr[up]>pivot)
			up--;
		if(down<up){
			temp=arr[down];
			arr[down]=arr[up];
			arr[up]=temp;
		}
	}
	arr[lb]=arr[up];
	arr[up]=pivot;
	return up;
}

void quick_sort(int *arr, int lb, int ub){
    int temp;
    if (lb>=ub) 
        return;
    int j=partition(arr,lb,ub);
    quick_sort(arr,lb,j-1);
    quick_sort(arr,j+1,ub);
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
    quick_sort(arr,0, n-1);
    printf("\nArray after sorting\n");
    display_array(arr,n);
    return 0;
}
