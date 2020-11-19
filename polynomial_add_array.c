#include<stdio.h>

struct polynomial{
    int coef;
    int exp;
};

int startA,startB,finishA,finishB,startD,finishD;
struct polynomial terms[100];
struct polynomial sum[100];

void display(struct polynomial pol[],int start,int finish){
    for(int i=finish;i>start;i--)
        printf("%d x^%d + ",pol[i].coef,pol[i].exp);
    printf("%d x^%d\n",pol[start].coef,pol[start].exp);
}

void add(){
    int a=startA,b=startB,d=0;;
    startD=d;
    while(a<=finishA && b<=finishB){
        if(terms[a].exp<terms[b].exp){
            sum[d].exp=terms[a].exp;
            sum[d].coef=terms[a].coef;
            a++;
            d++;
        }
        else if(terms[a].exp==terms[b].exp){
            sum[d].exp=terms[a].exp;
            sum[d].coef=terms[a].coef+terms[b].coef;
            a++;
            b++;
            d++;
        }
        else{
            sum[d].exp=terms[b].exp;
            sum[d].coef=terms[b].coef;
            b++;
            d++;
        }
    }
    while(a<=finishA){
        sum[d].exp=terms[a].exp;
        sum[d].coef=terms[a].coef;
        a++;
        d++;
       
    }
    while(b<=finishB){
        sum[d].exp=terms[b].exp;
        sum[d].coef=terms[b].coef;
        b++;
        d++;
       
    }
    finishD=d-1;
}

int main(){
    int i,degreeA,degreeB,exp,coef;
    printf("Enter degree of A(x):");
    scanf("%d", &degreeA);
    startA=0;
    finishA=degreeA;
    exp=0;
    for(i=startA;i<=finishA;i++){
        printf("Enter Coefficient for A(x) of x^%d:",exp);
        scanf("%d",&coef);
        if(coef){
            terms[i].coef=coef;
            terms[i].exp=exp;
        }
        else{
            finishA--;
            i--;
        }
        exp++;
    }
    printf("Enter degree of B(x):");
    scanf("%d", &degreeB);
    startB=finishA+1;
    finishB=startB+degreeB;
    exp=0;
    for(i=startB;i<=finishB;i++){
        printf("Enter Coefficient for B(x) of x^%d:",exp);
        scanf("%d",&coef);
        if(coef){
            terms[i].coef=coef;
            terms[i].exp=exp;
        }
        else{
            finishB--;
            i--;
        }
        exp++;
    }
    printf("A(x) = ");
    display(terms, startA, finishA);
    printf("B(x) = ");
    display(terms, startB, finishB);
    printf("Adding A(x) + B(x) = D(x)\n");
    add();
    printf("D(x) = ");
    display(sum,startD,finishD);
    return 0;
}
