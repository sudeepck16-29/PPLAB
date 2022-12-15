#include<stdio.h>
#include<mpi.h>

int main(int argc, char **argv)
{
    int process_rank, num_processes;
    int i, n, n_p;
    int a[100], b[100], sum[100], a_p[100], b_p[100], sum_p[100];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);

    if(process_rank == 0)
    {
        printf("Enter the length of the vectors\n");
        scanf("%d", &n);

        printf("Enter the elements of vector 1\n");
        for(i = 0; i < n; i++)
        {
            scanf("%d", &a[i]);
        }

        printf("Enter the elements of vector 2\n");
        for(i = 0; i < n; i++)
        {
            scanf("%d", &b[i]);
        }

        n_p = n / num_processes;
    }

    MPI_Bcast(&n_p, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scatter(a, n_p, MPI_INT, a_p, n_p, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(b, n_p, MPI_INT, b_p, n_p, MPI_INT, 0, MPI_COMM_WORLD);

    for(i = 0; i < n_p; i++)
    {
        sum_p[i] = a_p[i] + b_p[i];
    }

    MPI_Gather(sum_p, n_p, MPI_INT, sum, n_p, MPI_INT, 0, MPI_COMM_WORLD);

    if(process_rank == 0)
    {
        printf("Resultant vector :-\n");

        for(i = 0; i < n; i++)
        {
            printf("%d ", sum[i]);
        }

        printf("\n");
    }

    MPI_Finalize();
    return 0;
}