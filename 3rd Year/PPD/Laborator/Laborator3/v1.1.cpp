#include <bits/stdc++.h>
#include <mpi.h>
using namespace std;

int readDataPartial(ifstream &file, int* chunk, int chunk_size) {
    int count = 0;
    int digit;
    while (count < chunk_size && (file >> digit)) {
        chunk[count++] = digit;
    }
    return count;
}

void writeDataPartial(ofstream &fout, int* partial_sum, int chunk_size) {
    for (int i = 0; i < chunk_size; ++i) {
        fout << partial_sum[i] << " ";
    }
}

void run(int rank, int p, const string& file1_path, const string& file2_path, const string& result_path) {
    MPI_Barrier(MPI_COMM_WORLD);
    double start_time = MPI_Wtime();
    if (rank == 0) {
        ifstream f1(file1_path);
        ifstream f2(file2_path);
        if (!f1 || !f2) {
            cerr << "Nu pot deschide fisierele de intrare\n";
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        int N_1, N_2;
        f1 >> N_1;
        f2 >> N_2;
        int N = max(N_1, N_2);

        int dim = N / (p - 1);
        int rest = N % (p - 1);
        int id_proces_curent = 1;

        ofstream fout(result_path);
        if (!fout) {
            cerr << "Nu pot deschide fisierul de iesire\n";
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        while (id_proces_curent < p) {
            int chunk_size = dim;
            if (rest > 0) {
                chunk_size++;
                rest--;
            }

            int* chunk1 = new int[chunk_size];
            int* chunk2 = new int[chunk_size];

            int read1 = readDataPartial(f1, chunk1, chunk_size);
            int read2 = readDataPartial(f2, chunk2, chunk_size);
            while (read1 < chunk_size)
                chunk1[read1++] = 0;
            while (read2 < chunk_size)
                chunk2[read2++] = 0;

            MPI_Send(&chunk_size, 1, MPI_INT, id_proces_curent, 0, MPI_COMM_WORLD);
            MPI_Send(chunk1, chunk_size, MPI_INT, id_proces_curent, 0, MPI_COMM_WORLD);
            MPI_Send(chunk2, chunk_size, MPI_INT, id_proces_curent, 0, MPI_COMM_WORLD);

            int partial_result_len;
            MPI_Recv(&partial_result_len, 1, MPI_INT, id_proces_curent, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
            int* partial_result = new int[partial_result_len];
            MPI_Recv(partial_result, partial_result_len, MPI_INT, id_proces_curent, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);

            writeDataPartial(fout, partial_result, partial_result_len);

            delete[] chunk1;
            delete[] chunk2;
            delete[] partial_result;

            id_proces_curent++;
        }

        fout << "\n";
        fout.close();

    } else {
        int carry = 0;
        int localLen;
        MPI_Recv(&localLen, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);

        int* chunk1 = new int[localLen];
        int* chunk2 = new int[localLen];
        MPI_Recv(chunk1, localLen, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        MPI_Recv(chunk2, localLen, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);

        if (rank != 1) {
            MPI_Recv(&carry, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        }

        int* partial_sum = new int[localLen + 1];
        int newLen = localLen;

        for (int i = 0; i < localLen; ++i) {
            partial_sum[i] = chunk1[i] + chunk2[i] + carry;
            carry = partial_sum[i] / 10;
            partial_sum[i] %= 10;
        }

        if (carry > 0 && rank == p - 1) {
            partial_sum[localLen] = carry;
            newLen = localLen + 1;
        }

        MPI_Send(&newLen, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Send(partial_sum, newLen, MPI_INT, 0, 0, MPI_COMM_WORLD);

        if (rank + 1 < p) {
            MPI_Send(&carry, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        }

        delete[] chunk1;
        delete[] chunk2;
        delete[] partial_sum;
    }
    MPI_Barrier(MPI_COMM_WORLD);
    double end_time = MPI_Wtime();
    if (rank == 0) {
        double elapsed_seconds = end_time - start_time;
        double elapsed_milliseconds = elapsed_seconds * 1000.0;
        cout << "Timp total MPI Varianta 1: " << elapsed_milliseconds << " ms\n";
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

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "Introduceti testul" << endl;
        return 1;
    }

    MPI_Init(&argc, &argv);

    int rank, p;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);


    string test = argv[1];
    string file1_path = "Vers1/data" + test + "/Numar1.txt";
    string file2_path = "Vers1/data" + test + "/Numar2.txt";
    string result_path = "Vers1/data" + test + "/Numar3.txt";
    string result_secv_path = "Vers1/data" + test + "/Numar3Secv.txt";


    run(rank, p, file1_path, file2_path, result_path);

    verifyResults(result_path, result_secv_path);


    MPI_Finalize();
    return 0;
}
