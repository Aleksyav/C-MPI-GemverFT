#include <mpi.h>
// #include <mpi-ext.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char *argv[])
{
    int rank, size, rc, len;
    char errstr[MPI_MAX_ERROR_STRING];

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Comm_set_errhandler(MPI_COMM_WORLD,
                            MPI_ERRORS_RETURN);

    MPI_Barrier(MPI_COMM_WORLD);
    if( rank == (size-1) ) raise(SIGKILL);
    if (rank % 2 == 0) {
        int a = rand() % 100;
        printf("Rank: %d Sending to rank %d\ta = %d\n", rank, rank + 1, a);
        MPI_Request req;
        MPI_Isend(&a, 1, MPI_INT, rank + 1, 11111, MPI_COMM_WORLD, &req);
        MPI_Status stat;
        printf("Rank: %d Waiting 'a' from rank %d\n", rank, rank + 1);
        rc = MPI_Recv(&a, 1, MPI_INT, rank + 1, 11111, MPI_COMM_WORLD, &stat);
        printf("Rank: %d Status Recv %d\n", rank, rc);

        if (rc == 0) {
            printf("Rank: %d Got 'a' from rank %d\t a = %d\n", rank, rank + 1, a);
            MPI_Error_string(rc, errstr, &len);
            printf("Rank %d / %d: Message of OK %s\n", rank, size, errstr);

        } else {
            printf("Rank: %d No Message from %d\n", rank, rank + 1);
            MPI_Error_string(rc, errstr, &len);
            printf("Rank %d / %d: Message of error %s\n", rank, size, errstr);
        }
    } else {
        int a = rand() % 100;
        printf("Rank: %d Sending to rank %d\ta = %d\n", rank, rank + 1, a);
        MPI_Request req;
        MPI_Isend(&a, 1, MPI_INT, rank - 1, 11111, MPI_COMM_WORLD, &req);
        MPI_Status stat;
        printf("Rank: %d Waiting 'a' from rank %d\n", rank, rank + 1);
        rc = MPI_Recv(&a, 1, MPI_INT, rank - 1, 11111, MPI_COMM_WORLD, &stat);
        printf("Rank: %d Status Recv %d\n", rank, rc);

        if (rc == 0) {
            printf("Rank: %d Got 'a' from rank %d\t a = %d\n", rank, rank - 1, a);
            MPI_Error_string(rc, errstr, &len);
            printf("Rank %d / %d: Message of OK %s\n", rank, size, errstr);

        } else {
            printf("Rank: %d No Message from %d\n", rank, rank - 1);
            MPI_Error_string(rc, errstr, &len);
            printf("Rank %d / %d: Message of error %s\n", rank, size, errstr);
        }
    }
    MPI_Finalize();
}
