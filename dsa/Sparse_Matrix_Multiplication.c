#include <stdio.h>

#define MAX_TERM 100

typedef struct{
    int row,col,value;
}term;

int normalA[10][10];
int normalB[10][10];
term tupleA[MAX_TERM+1];
term tupleB[MAX_TERM+1];

void display_tuple_form(term A[]){
    printf("Displaying Matrix in Tuple Form:-\nRow\tColumn\tValue\n");
    for(int i=1;i<=A[0].value;++i){
        printf(" %d\t %d\t %d\n",A[i].row,A[i].col,A[i].value);
    }
}

void convert_to_tupleform(int r1,int c1,int r2, int c2){ 
    int k=1,l=1;
    tupleA[0].row=r1;
    tupleA[0].col=c1;
    tupleB[0].row=r2;
    tupleB[0].col=c2;
    for(int i=0;i<r1;++i){
        for(int j=0;j<c1;++j){
            if(normalA[i][j]!=0){
                tupleA[k].row=i+1;
                tupleA[k].col=j+1;
                tupleA[k].value=normalA[i][j];
                k++;
            }
        }
    }
    for(int i=0;i<r2;++i){
        for(int j=0;j<c2;++j){
            if(normalB[i][j]!=0){
                tupleB[l].row=i+1;
                tupleB[l].col=j+1; 
                tupleB[l].value=normalB[i][j];
                l++;
            }
        }
    }
    tupleA[0].value=k-1;
    tupleB[0].value=l-1;
    printf("Converted matrix to tuple form\n");
    printf("Matrix A:-\n");
    display_tuple_form(tupleA);
    printf("Matrix B:-\n");
    display_tuple_form(tupleB);
}

void multiplication(term A[],term B[]){
    term C[MAX_TERM+1],temp[MAX_TERM+1];
    int i,j,k=1,sum;
    printf("Multiplying Matrix C = Matrix A * Matrix B.\n");
    temp[0].row = A[0].row;
    temp[0].col = B[0].col;
    for(i=1;i<=A[0].value;i++){
        for(j=1;j<=B[0].value;j++){
            if(A[i].col==B[j].row){
                temp[k].row=A[i].row;
                temp[k].col=B[j].col;
                temp[k].value=A[i].value*B[j].value;
                k++;
            }
        }
    }
    temp[0].value = k - 1;
    C[0].row=A[0].row;
    C[0].col=B[0].col;
    k=1;
    for(i=1;i<=temp[0].value;i++){
        sum=temp[i].value;
        for(j=i+1;j<=temp[0].value;j++){
            if (temp[i].row==temp[j].row && temp[i].col==temp[j].col && temp[j].row>0) {
                sum+=temp[j].value;
                temp[j].row=-1;
                temp[j].col=-1; 
            }
        }
        if(temp[i].row>0) {
            C[k].row=temp[i].row;
            C[k].col=temp[i].col;
            C[k].value=sum;
            k++;
        }
    }
    C[0].value=k-1;
    printf("Matrix C:-\n");
    display_tuple_form(C);
}

void main(){
    int i,j,r1,r2,c1,c2;
    printf("Enter number of rows for matrix A:");
    scanf("%d",&r1);
    printf("Enter number of columns for matrix A:");
    scanf("%d",&c1);
    printf("Enter number of rows for matrix B:");
    scanf("%d",&r2);
    printf("Enter number of columns for matrix B:");
    scanf("%d",&c2);
    if(c1 == r2){
        printf("Enter the matrix A in normal form\n");
        for(i=0;i<r1;++i){
            for(j=0;j<c1;++j){
                printf("Enter Element:");
                scanf("%d",&normalA[i][j]);
            }
        }
        printf("Enter the matrix B in normal form\n");
        for(i=0;i<r2;++i){
            for(j=0;j<c2;++j){
                printf("Enter Element:");
                scanf("%d",&normalB[i][j]);
            }
        }
        printf("Matrix A:-\n");
        for(i=0;i<r1;++i){
            for(j=0;j<c1;++j){
                printf("%d\t",normalA[i][j]);
            }
            printf("\n");
        }
        printf("Matrix B:-\n");
        for(i=0;i<r2;++i){
            for(j=0;j<c2;++j){
                printf("%d\t",normalB[i][j]);
            }
            printf("\n");
        }
        convert_to_tupleform(r1,c1,r2,c2);
        multiplication(tupleA,tupleB);
    }
    else {
        printf("The number of columns for Matrix A and number of rows of Matrix B should be equal. Exiting....\n");
    }
}
