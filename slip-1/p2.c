#include<stdio.h>

int N;
int M;
int Alloc[10][10],Need[10][10],Max[10][10];
int SafeSeq[10], Avail[10], tempAvail[10];

int Accept(){
    printf("\nEnter how many process:");
    scanf("%d",N);
    printf("\nEnter how many res:");
    scanf("%d",M);

    int i,j;

    printf("\nEnter available:");
    for(i=0;i<M;i++){
        printf("Avail:");
        scanf("%d",&Avail[i]);
    }

    printf("\nEnter Alloc");
    for(i=0;i<N;i++){
        for (j=0;j<M;j++)
        {
            printf("Alloc p%d res[%c]:",i,65+j);
            scanf("%d",&Alloc[i][j]);
        }
    }

    printf("\nEnter Max");
    for(i=0;i<N;i++){
        for (j=0;j<M;j++)
        {
            printf("Max p%d res[%c]:",i,65+j);
            scanf("%d",&Max[i][j]);
        }
    }

    for(i=0;i<N;i++){
        SafeSeq[i]=-1;
    }
}

int display(int a[10][10],int N, int M){
    int i,j;
    for(i=0;i<N;i++){
        for (j=0;j<M;j++)
        {
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
}

int calneed(){

    int i,j;
    for(i=0;i<N;i++){
        for (j=0;j<M;j++)
        {
           Need[i][j]=Max[i][j]-Alloc[i][j];
        }
    }
}

int Isfeasible(int pno){
    int i;
    for(i=0;i<N;i++){
        if(Need[pno][i]>Avail[i])
            return 0;
    }
    return 1;
}

int banker(){
    int i,j;
    int k=0;
    int flags[5]={0,0,0,0,0,0};
    int finish=1;

    while(finish!=0){
        for(i=0;i<N;i++){
            if(Isfeasible(i) && flags[i]!=1){
                for(j=0;j<M;j++){
                    Avail[j]-=Need[i][j];
                }
                for(j=0;j<M;j++){
                    Need[i][j]+=Alloc[i][j];
                }
                for(j=0;j<M;j++){
                    Avail[j]-=Alloc[i][j];
                }
                SafeSeq[k++]=i;
                flags[i]=1;
            }
        }
        for(i=0;i<M;i++){
            if(flags[i]==1){
                continue;
            }
            else
                break;
        }
        if(i==N)
        finish=1;
    }
}

int main(){
    Accept();
    calneed();
    display(Alloc,N,M);
    display(Need,N,M);
    display(Max,N,M);
    banker();
}