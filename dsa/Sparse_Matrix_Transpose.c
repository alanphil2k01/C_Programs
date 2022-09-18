#include <stdio.h>

#define MAX_TERM 100

typedef struct{
    int row,col,value;
}term;

int matrixNormal[10][10];
term matrixTuple[MAX_TERM+1];

void display_tuple_form(term A[]){
    printf("Displaying Matrix in Tuple Form:-\nRow\tColumn\tValue\n");
    for(int i=1;i<=A[0].value;++i){
        printf(" %d\t %d\t %d\n",A[i].row,A[i].col,A[i].value);
    }
}

void display_tuple_as_normal(term A[]){
    int i,j,k=1;
    int B[A[0].row][A[0].col];
    printf("Displaying in normal form:-\n");
    for (i=0;i<A[0].row;i++){
        for(j=0;j<A[0].col;j++){
            B[i][j]=0;
        }
    }
    for(k=1;k<=A[0].value;k++){
        B[A[k].row-1][A[k].col-1]=A[k].value;
    }
    for(i=0;i<A[0].row;i++){
        for(j=0;j<A[0].col;j++){
            printf("%d\t",B[i][j]);
        }
        printf("\n");
    }
}

void convert_to_tupleform(int r,int c){ 
    int k=1;
    matrixTuple[0].row=r;
    matrixTuple[0].col=c;
    for(int i=0;i<r;++i){
        for(int j=0;j<c;++j){
            if(matrixNormal[i][j]!=0){
                matrixTuple[k].row=i+1;
                matrixTuple[k].col=j+1;
                matrixTuple[k].value=matrixNormal[i][j];
                k++;
            }
        }
    }
    matrixTuple[0].value=k-1;
    printf("Converted matrix to tuple form\n");
    display_tuple_form(matrixTuple);
}

void transpose(term A[]){
    term Transpose[MAX_TERM+1];
    for(int i=0;i<=A[0].value;++i){
        Transpose[i].row=A[i].col;
        Transpose[i].col=A[i].row;
        Transpose[i].value=A[i].value;
    }
    printf("Transpose Matrix:-\n");
    display_tuple_form(Transpose);
    display_tuple_as_normal(Transpose);
}

void main(){
    int r,c,i,j;
    printf("Enter number of rows:");
    scanf("%d",&r);
    printf("Enter number of columns:");
    scanf("%d",&c);
    if(r > 10 || c > 10){
        printf("The number of rows or columns exceeded the maximum allowed value. \n");
        if(r>10){r=10;}
        if(c>10){c=10;}
        printf("Taking size as %dx%d\n",r,c);
    }
    printf("Enter the matrix in normal form\n");
    for(i=0;i<r;++i){
        for(j=0;j<c;++j){
            printf("Enter Element:");
            scanf("%d",&matrixNormal[i][j]);
        }
    }
    for(i=0;i<r;++i){
        for(j=0;j<c;++j){
            printf("%d\t",matrixNormal[i][j]);
        }
        printf("\n");
    }
    convert_to_tupleform(r,c);
    transpose(matrixTuple);
}
