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

void convert_to_tupleform(int r,int c){ 
    int k=1,l=1;
    tupleA[0].row=r;
    tupleB[0].row=r;
    tupleA[0].col=c;
    tupleB[0].col=c;
    for(int i=0;i<r;++i){
        for(int j=0;j<c;++j){
            if(normalA[i][j]!=0){
                tupleA[k].row=i+1;
                tupleA[k].col=j+1;
                tupleA[k].value=normalA[i][j];
                k++;
            }
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

void addition(term A[],term B[]){
    int i=1,j=1,k=1;
    term C[MAX_TERM+1];
    printf("Adding Matrix C = Matrix A + Matrix B.\n");
    C[0].row=A[0].row;
    C[0].col=A[0].col;
    while(i<=A[0].value && j<=B[0].value){
        if(A[i].row==B[j].row){
            if(A[i].col==B[j].col){
                C[k].row=A[i].row;
                C[k].col=A[i].col;
                C[k].value=A[i].value+B[j].value;
                i++;
                j++;
                k++;
            }
            else if(A[i].col<B[j].col){
                C[k]=A[i];
                i++;
                k++;
            }
            else {
                C[k]=B[j];
                j++;
                k++;               
            }
        }
        else if(A[i].row<B[j].row){
            C[k]=A[i];
            i++;
            k++;
        }
        else{
            C[k]=B[j];
            j++;
            k++;               
        }
    }
    while(i<=A[0].value){
            C[k]=A[i];
            i++;
            k++;
    }
    while(j<=tupleB[0].value){
            C[k]=B[j];
            j++;
            k++;
    }
    C[0].value=k-1;
    printf("Matrix C:-\n");
    display_tuple_form(C);
}

void main(){
    int r1,c1,r2,c2,i,j;
    printf("Enter number of rows for matrix A:");
    scanf("%d",&r1);
    printf("Enter number of columns for matrix A:");
    scanf("%d",&c1);
    printf("Enter number of rows for matrix B:");
    scanf("%d",&r2);
    printf("Enter number of columns for matrix B:");
    scanf("%d",&c2);
    if(r1==r2 && c1==c2){
        if(r1 > 10 || c1 > 10){
            printf("The number of rows or columns exceeded the maximum allowed value. \n");
            if(r1>10){r1=10;}
            if(c1>10){c1=10;}
            printf("Taking size as %dx%d\n",r1,c1);
        }
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
        convert_to_tupleform(r1,c1);
        addition(tupleA,tupleB);
    }
    else {
        printf("Number of rows or columns don't match. Exiting...\n");
    }
}
