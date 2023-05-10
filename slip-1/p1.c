// Write a C Menu driven Program to implement following functionality
// a) Accept Available
// b) Display Allocation, Max
// c) Display the contents of need matrix
// d) Display Available
// Process  Allocation   Max   Available
//    	      A B C     A B C    A B C
//    P0      2 3 2     9 7 5    3 3 2
//    P1      4 0 0     5 2 2   
//    P2      5 0 4     1 0 4   
//    P3      4 3 3     4 4 4   
//    P4      2 2 4     6 5 5 
#include<stdio.h>

int N, M;
int Alloc[10][10];
int TempAlloc[10][10];
int Need[10][10];
int Max[10][10];
int Avail[10];
int Safeseq[10];

int AcceptInput(){
    int i,j;

    printf("\nEnter number of process:");
    scanf("%d",&N);

    printf("\nEnter number of resources:");
    scanf("%d",&M);

    printf("\nEnter available:\n");
    for(i=0;i<M; i++)
    {
        printf("\nAvailable res[%c]",65+i);
        scanf("%d",&Avail[i]);   
    }

    printf("\nEnter Max Matrix:");
    for(i=0;i<N;i++)
    {
        for(j=0;j<M;j++)
        {
            printf("\nMax for P%d res[%c] :",i,65+j);
            scanf("%d",&Max[i][j]);
        }
    }
    
    printf("\nEnter Allocation Matrix:");
    for(i=0;i<N;i++)
    {
        for(j=0;j<M;j++)
        {
            printf("\nAlloc for P%d res[%c] ",i,65+j);
            scanf("%d",&Alloc[i][j]);
        }
    }

    for(i=0;i<N;i++)
        Safeseq[i]=-1;
}

int CalNeed()
{
    int i,j;
    for(i=0;i<N;i++)
    {
        for(j=0;j<M;j++)
        {
            Need[i][j]=Max[i][j]-Alloc[i][j];
        }
    }
}

int DisplayMatrix(int a[10][10], int N, int M)
{
    int i,j;

    for(i=0;i<N;i++)
    {
        for(j=0;j<M;j++)
        {
            printf("%d  ",a[i][j]);
        }
        printf("\n");
    }
}

int IsFeasible(int pno)
{
    int i;

    for(i=0;i<N;i++)
    {
        if(Need[pno][i]>Avail[i])
            return 0;
    }
    return 1;
}

int Banker()
{
    int flags[5]={0,0,0,0,0};
    int k=0;
    int i,j;
    int finish=0;
    while(finish!=1)
    {
        for(i=0;i<N;i++)
        {
            if(IsFeasible(i) && flags[i] !=1)
            {
                //remove from available
                for(j=0;j<M;j++)
                {
                   Avail[j]-=Need[i][j]; 
                }
                //add need to alloc
                for(j=0;j<M;j++)
                {
                   Alloc[i][j]+=Need[i][j]; 
                }
                //process relasees resources
                for(j=0;j<M;j++)
                {
                   Avail[j]+=Alloc[i][j]; 
                }
                //add safe seq
                Safeseq[k++]=i;
                flags[i]=1;
            }
        }

        for(i=0;i<M;i++)
        {
            if(flags[i]==1)
                continue;
            else
                break;
        }

        if(i==N)
            finish=1;
    }
}

int PrintSafeSeq(){
    int i;
    printf("Safe seq:");
    for(i=0;i<N;i++)
    {
        printf("P%d ",Safeseq[i]);
    }
}

int main()
{
	AcceptInput();
	CalNeed();
	printf("\nMAX:\n");
	DisplayMatrix(Max, N, M);
	printf("\nALLOCATION:\n");
	DisplayMatrix(Alloc, N, M);
	printf("\nNEED:\n");
	DisplayMatrix(Need, N, M);
	Banker();
	PrintSafeSeq();
	// NewRequest();

	return 0;
}