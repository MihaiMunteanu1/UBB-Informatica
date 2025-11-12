#include <bits/stdc++.h>
#include <mpi.h>
using namespace std;

int readDataPartial(ifstream &f, int *v, int n) {
    int d, i = 0;
    while (i < n && (f >> d))
        v[i++] = d;
    while (i < n)
        v[i++] = 0;
    return n;
}

void run(int rank, int p, const string& file1_path, const string& file2_path, const string& result_path) {
    MPI_Barrier(MPI_COMM_WORLD);
    double start_time = MPI_Wtime();

    if (rank == 0) {
        ifstream f1(file1_path), f2(file2_path);
        if (!f1 || !f2) {
            cerr << "Cannot open input files!\n";
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        int N_1, N_2;
        f1 >> N_1;
        f2 >> N_2;
        int N = max(N_1, N_2);
        int dim = N / (p-1);
        int rest = N % (p-1);

        for (int id = 1; id < p; ++id) {
            int chunk = dim + (rest > 0 ? 1 : 0);
            if (rest > 0)
                rest--;

            int *a = new int[chunk];
            int *b = new int[chunk];
            readDataPartial(f1, a, chunk);
            readDataPartial(f2, b, chunk);

            MPI_Request reqs[3];
            MPI_Isend(&chunk, 1, MPI_INT, id, 0, MPI_COMM_WORLD, &reqs[0]);
            MPI_Isend(a, chunk, MPI_INT, id, 1, MPI_COMM_WORLD, &reqs[1]);
            MPI_Isend(b, chunk, MPI_INT, id, 2, MPI_COMM_WORLD, &reqs[2]);
            MPI_Waitall(3, reqs, MPI_STATUSES_IGNORE);

            delete[] a;
            delete[] b;
        }

        vector<int> result_lengths(p-1);
        vector<vector<int>> results(p-1);
        vector<MPI_Request> length_requests(p-1);
        vector<MPI_Request> data_requests(p-1);

        for (int id = 1; id < p; ++id) {
            MPI_Irecv(&result_lengths[id-1], 1, MPI_INT, id, 3, MPI_COMM_WORLD, &length_requests[id-1]);
        }

        MPI_Waitall(p-1, length_requests.data(), MPI_STATUSES_IGNORE);

        for (int id = 1; id < p; ++id) {
            results[id-1].resize(result_lengths[id-1]);
            MPI_Irecv(results[id-1].data(), result_lengths[id-1], MPI_INT, id, 4, MPI_COMM_WORLD, &data_requests[id-1]);
        }

        MPI_Waitall(p-1, data_requests.data(), MPI_STATUSES_IGNORE);

        ofstream fout(result_path);
        if (!fout) {
            cerr << "Cannot open output file!\n";
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        for (int id = 1; id < p; ++id) {
            for (int i = 0; i < result_lengths[id-1]; i++) {
                fout << results[id-1][i] << " ";
            }
        }

        fout << "\n";
        f1.close();
        f2.close();
        fout.close();
    }
    else {
        int chunk;
        MPI_Request rq0;
        MPI_Irecv(&chunk, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &rq0);
        MPI_Wait(&rq0, MPI_STATUS_IGNORE);

        int *a = new int[chunk];
        int *b = new int[chunk];
        MPI_Request rq[2];
        MPI_Irecv(a, chunk, MPI_INT, 0, 1, MPI_COMM_WORLD, &rq[0]);
        MPI_Irecv(b, chunk, MPI_INT, 0, 2, MPI_COMM_WORLD, &rq[1]);
        MPI_Waitall(2, rq, MPI_STATUSES_IGNORE);

        int carry = 0;
        MPI_Request recvCarry = MPI_REQUEST_NULL;
        if (rank != 1)
            MPI_Irecv(&carry, 1, MPI_INT, rank - 1, 5, MPI_COMM_WORLD, &recvCarry);

        if (recvCarry != MPI_REQUEST_NULL)
            MPI_Wait(&recvCarry, MPI_STATUS_IGNORE);

        int *sum = new int[chunk + 1];
        for (int i = 0; i < chunk; i++) {
            int s = a[i] + b[i] + carry;
            sum[i] = s % 10;
            carry = s / 10;
        }

        int len = chunk;
        if (carry && rank == p - 1)
            sum[len++] = carry;

        MPI_Request sendReqs[2];
        MPI_Isend(&len, 1, MPI_INT, 0, 3, MPI_COMM_WORLD, &sendReqs[0]);
        MPI_Isend(sum, len, MPI_INT, 0, 4, MPI_COMM_WORLD, &sendReqs[1]);

        if (rank + 1 < p) {
            MPI_Request tmp;
            MPI_Isend(&carry, 1, MPI_INT, rank + 1, 5, MPI_COMM_WORLD, &tmp);
            MPI_Request_free(&tmp);
        }

        MPI_Waitall(2, sendReqs, MPI_STATUSES_IGNORE);

        delete[] a;
        delete[] b;
        delete[] sum;
    }

    MPI_Barrier(MPI_COMM_WORLD);
    double end_time = MPI_Wtime();

    if (rank == 0) {
        double elapsed_seconds = end_time - start_time;
        double elapsed_milliseconds = elapsed_seconds * 1000.0;
        cout << "Timp total MPI Varianta 3: " << elapsed_milliseconds << " ms\n";
    }
}

void verifyResults(const string& f1, const string& f2) {
    ifstream file1(f1);
    ifstream file2(f2);

    string line1, line2;

    while (true) {
        bool eof1 = !getline(file1, line1);
        bool eof2 = !getline(file2, line2);

        if (eof1 && eof2)
            break;

        if (eof1 || eof2 || line1 != line2) {
            cout << "Fisiere diferite\n";
            break;
        }
    }

    file1.close();
    file2.close();
}

int main(int argc, char **argv) {
    if (argc != 2) {
        cout << "Introduceti testul" << endl;
        return 1;
    }

    MPI_Init(&argc, &argv);

    int rank, p;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    string test = argv[1];
    string file1_path = "Vers3/data" + test + "/Numar1.txt";
    string file2_path = "Vers3/data" + test + "/Numar2.txt";
    string result_path = "Vers3/data" + test + "/Numar3.txt";
    string result_secv_path = "Vers3/data" + test + "/Numar3Secv.txt";

    run(rank, p, file1_path, file2_path, result_path);

    verifyResults(result_path, result_secv_path);
    MPI_Finalize();
    return 0;
}