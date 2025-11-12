#include <iostream>
#include <mpi.h>
#include <string>

using namespace std;

void mpi_hello(int rank, int p){

    const int STRING_LEN = 36;


    if (rank == 0){
        // main proc

        char* buf = new char[STRING_LEN * (p - 1) + 1];

        buf[STRING_LEN * (p-1) + 1] = '\0';

        for (int pid = 1; pid < p; pid++) {
            MPI_Recv(buf + STRING_LEN * (pid - 1), STRING_LEN, MPI_CHAR, pid, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        }

        printf ("%s", buf);

        delete[] buf;

    } else {
        //worker

        char* buf = new char[STRING_LEN+1];

        snprintf(buf, STRING_LEN + 1, "Salut frate, de la proc: %10d\n", rank);

        MPI_Send(buf, STRING_LEN, MPI_CHAR, 0, 0, MPI_COMM_WORLD);



        delete[] buf;
    }
}

void mpi_hello_async(int rank, int p){

    const int STRING_LEN = 36;


    if (rank == 0){
        // main proc
        MPI_Request* reqs = new MPI_Request[p-1];
        char* buf = new char[STRING_LEN * (p - 1) + 1];
        bool ok = false;

        buf[STRING_LEN * (p-1) + 1] = '\0';

        for (int pid = 1; pid < p; pid++) {
            MPI_Irecv(buf + STRING_LEN * (pid - 1), STRING_LEN, MPI_CHAR, pid, 0, MPI_COMM_WORLD, &reqs[pid - 1]);
        }

        // int* flags = new int[p-1];

        // while (!ok){
        //     ok = true;
        //     for (int pid = 1; pid < p; pid++){
        //         MPI_Test(&reqs[pid-1],&flags[pid-1], MPI_STATUSES_IGNORE);

        //         if (flags[pid-1] == 0){
        //             ok = false;
        //         } else {
        //             printf("PID: %d has finished\n", pid);
        //         }
        //     }
        // }


        // MPI_Waitall(p-1, reqs, MPI_STATUSES_IGNORE);

        for (int i = 0; i < p-1; i++){
            int idx;
            MPI_Waitany(p-1, reqs, &idx, MPI_STATUSES_IGNORE);

            printf("%d has arrived\n", idx);
        }
        printf ("%s", buf);
        delete[] buf;
        delete[] reqs;
        // delete[] flags;

    } else {
        //worker
        MPI_Request req;

        char* buf = new char[STRING_LEN+1];

        snprintf(buf, STRING_LEN + 1, "Salut frate, de la proc: %10d\n", rank);

        MPI_Isend(buf, STRING_LEN, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &req);


        MPI_Wait(&req, MPI_STATUSES_IGNORE);
        delete[] buf;
    }
}

void init(int* vec, int len) {
    for (int i = 0; i < len; i++) {
        vec[i] = rand() % 100;
    }
}

void validare(int* a, int* b, int* c, int len) {
    for (int i = 0; i < len; i++) {
        if ( c[i] != a[i] + b[i] ) {
            printf("i: %d; %d != %d + %d\n", i, c[i], a[i], b[i]);
            return;
        }
    }

    printf("All good\n");
}

void mpi_sum(int rank, int p) {
    const int N = 1000;
    if (rank == 0) {
        int* a = new int[N];
        int* b = new int[N];
        int* c = new int[N];

        MPI_Request* reqs = new MPI_Request[p-1];

        init(a, N);
        init(b, N);

        int dim = N / (p - 1);
        int r = N % (p - 1);
        int start = 0;
        int end = dim;

        for (int pid = 1; pid < p; pid++) {
            if (r > 0) {
                end++;
                r--;
            }

            int len = end - start;

            MPI_Send(&len, 1, MPI_INT, pid, 0, MPI_COMM_WORLD);
            MPI_Send(a + start, len, MPI_INT, pid, 0, MPI_COMM_WORLD);
            MPI_Send(b + start, len, MPI_INT, pid, 0, MPI_COMM_WORLD);
            MPI_Irecv(c + start, len, MPI_INT, pid, 0, MPI_COMM_WORLD, &reqs[pid - 1]);

            start = end;
            end += dim;
        }

        MPI_Waitall(p-1, reqs, MPI_STATUSES_IGNORE);

        /*
        // sync
        // In loc de asta punem ca sus Irecv sus si MPI_Waitall, si asta de sus e async
        r = N % (p - 1);
        start = 0;
        end = dim;
        for (int pid = 1; pid < p; pid++) {
            if (r > 0) {
                end++;
                r--;
            }

            MPI_Recv(c + start, end - start, MPI_INT, pid, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);


            start = end;
            end += dim;
        }*/

        validare(a, b, c, N);

        delete[] a;
        delete[] b;
        delete[] c;
        delete[] reqs;
    } else {
        int dim = N / (p - 1);
        int* ar = new int[dim + 1];
        int* br = new int[dim + 1];
        int* cr = new int[dim + 1];

        // int r = N / ( p - 1 )
        // int actual_dim = dim + ((rankj - 1) < r);
        int len;
        MPI_Recv(&len, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        MPI_Recv(ar, len, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        MPI_Recv(br, len, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);

        for (int  i = 0; i < len; i++) {
            cr[i] = ar[i] + br[i];
        }

        MPI_Send(cr, len, MPI_INT, 0, 0, MPI_COMM_WORLD);


        delete[] ar;
        delete[] br;
        delete[] cr;

    }

}

void mpi_sum_scatter(int rank, int p){
    const int N = 1000;
    int* a= nullptr;
    int* b= nullptr;
    int* c= nullptr;

    if(rank == 0) {
        a = new int[N];
        b = new int[N];
        c = new int[N];

        init(a, N);
        init(b, N);
    }
    int dim = N/p;
    int* ar = new int[dim];
    int* br = new int[dim];
    int* cr = new int[dim];

    MPI_Scatter(a, dim, MPI_INT, ar, dim, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(b, dim, MPI_INT, br, dim, MPI_INT, 0, MPI_COMM_WORLD);

    for(int i=0;i<dim;i++){
        cr[i] = ar[i] + br[i];
    }

    // opusul lui scatter, ii ca o bariera
    MPI_Gather(cr, dim, MPI_INT, c, dim, MPI_INT,0, MPI_COMM_WORLD);

    if(rank == 0){
        validare(a,b,c,dim * p);
    }


    delete[] ar;
    delete[] br;
    delete[] cr;

    if(rank == 0){
        delete[] a;
        delete[] b;
        delete[] c;
    }
}

int main(int argc, char* argv[]){
    printf("Hello\n");

    MPI_Init(&argc, &argv);

    if (argc < 2){
        printf("Usage: %s [param]\n");
    }
    int rank, p;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    printf("Hello from: %d/%d\n", rank, p);

    int param = stoi(argv[1]);

    switch(param){
        case 1:
            mpi_hello(rank, p);
            break;
        case 2:
            mpi_hello_async(rank, p);
            break;
        case 3:
            mpi_sum(rank, p);
            break;
        default:
            break;
    }



    MPI_Finalize();
    return 0;
}