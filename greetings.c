#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<string.h>

int main(int argc, char **argv)
{
    char send_greeting[50], recv_greeting[50];
    int process_rank, num_processes, method;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);

    sprintf(send_greeting, "Greetings from process %d", process_rank);

    if(process_rank == 0)
    {
        printf("Select method 1 (all receive) or 2 (only root receives)\n");
        scanf("%d", &method);
    }

    MPI_Bcast(&method, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(method == 1)
    {
        for(int i = 0; i < num_processes; i++)
        {
            if(i != process_rank)
            {
                MPI_Bsend(send_greeting, strlen(send_greeting), MPI_CHAR, i, 0, MPI_COMM_WORLD);
            }
        }

        for(int i = 0; i < num_processes - 1; i++)
        {
            MPI_Recv(recv_greeting, 50, MPI_CHAR, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            printf("%s, process %d!\n", recv_greeting, process_rank);
        }
    }
    else
    {
        if(process_rank != 0)
        {
            MPI_Send(send_greeting, strlen(send_greeting), MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        }
        else
        {
            for(int i = 1; i < num_processes; i++)
            {
                MPI_Recv(recv_greeting, 50, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

                printf("%s, root!\n", recv_greeting);
            }
        }
    }
    
    MPI_Finalize();
}