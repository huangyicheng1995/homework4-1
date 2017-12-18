#include "mpi.h"
#include <stdio.h>
#include <math.h>

int main (int argc, char **argv)
{
int myid, numprocs;
int namelen;
double start,end,startchuan,endchuan,timechuan;
int i1,j1,flg,sum=0,a=0;
int done = 0, n, i;
FILE *fp;
fp=fopen("result","w");

    char processor_name[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    MPI_Get_processor_name(processor_name,&namelen);

    fprintf(stderr,"Process %d on %s\n",
            myid, processor_name);

    n = 0;a=0;sum=0;
    while (!done)
    {
        if (myid == 0)
        {
            if (n==0) n=100; else n=0;
            start = MPI_Wtime();
        }
        MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
        if (n == 0)
            done = 1;
        else
        {
		
            for (i1=2;i1<=100000;i1++)
		{
			flg=1;
			for(j1=2;j1<i1;j1++)
			{
				if(i1%j1==0)
				{
					flg=0;break;
				}
			}
			if(flg)
			{
				sum+=i1;
				a=a+1;
				fprintf(fp,"%d\t",i1);
			}
		}
            if (myid == 0)
            {
                printf("素数个数为：%d\n",a); 
                end = MPI_Wtime();
                printf("MPI运行时间 = %f\n",end-start);
            }
        }
    }
MPI_Finalize();

a=0;sum=0;
if (myid == 0)
{
	startchuan=MPI_Wtime();
for (i1=2;i1<=100000;i1++)
{
	flg=1;
	for(j1=2;j1<i1;j1++)
	{
		if(i1%j1==0)
		{
			flg=0;break;
		}
	}
	if(flg)
	{
		sum+=i1;
		a=a+1;
		fprintf(fp,"%d\t",i1);
	}
}

	printf("素数个数为：%d\n",a); 
	endchuan=MPI_Wtime();
	printf("串行运行时间 = %f seconds\n",endchuan-startchuan);
}
return 0;
}
