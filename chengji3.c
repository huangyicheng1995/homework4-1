#include "mpi.h"
#include <stdio.h>
#include <math.h>


int main( int argc, char *argv[])
{
    int done = 0, n, myid, numprocs, i;
    double startwtime = 0.0, endwtime;
    int  namelen;

    int i1, m,j1;
    double a[10000], b[10000], result;

    m = 10000;
    result = 0.0;
    for (i1 = 0; i1 < m; i1++)
    {
	a[i] = i1 * 1.0;
	b[i] = i1 * 2.0;
    }


    char processor_name[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    MPI_Get_processor_name(processor_name,&namelen);

    fprintf(stderr,"Process %d on %s\n",
            myid, processor_name);

    n = 0;
    while (!done)
    {
        if (myid == 0)
        {
            if (n==0) n=100; else n=0;


            startwtime = MPI_Wtime();
        }
        MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
        if (n == 0)
            done = 1;
        else
        {
		
            for (i1 = 0; i1 < n; i1++)
            {
	        for (j1=0;j1<n;j1++)
	        {
		      result = result + (a[i1] * b[j1]);
	        }
            }

            if (myid == 0)
            {
                printf("计算结果为：%.16g\n",result); 
                endwtime = MPI_Wtime();
                printf("wall clock time = %f\n",
                       endwtime-startwtime);
            }
        }
    }
    MPI_Finalize();
    return 0;
}

