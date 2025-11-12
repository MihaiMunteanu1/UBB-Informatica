#include <bits/stdc++.h>
#include <mpi.h>
using namespace std;

void run(int rank, int p, const string& file1_path, const string& file2_path, const string& result_path) {
    int *a = nullptr, *b = nullptr, *sum = nullptr;
    int N_1 = 0, N_2 = 0, N = 0;
    int chunk_size = 0;
    int NOrig;

    MPI_Barrier(MPI_COMM_WORLD);
    double start_time = MPI_Wtime();

    if (rank == 0) {
        ifstream f1(file1_path), f2(file2_path);
        if (!f1 || !f2) {
            cerr << "Cannot open input files\n";
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        f1 >> N_1;
        f2 >> N_2;
        N = max(N_1, N_2);

        NOrig = N;
        if (N % p != 0)
            N += p - (N % p);

        a = new int[N]();
        b = new int[N]();

        for (int i = 0; i < N_1; i++)
            f1 >> a[i];
        for (int i = 0; i < N_2; i++)
            f2 >> b[i];

        f1.close();
        f2.close();

        sum = new int[N + 1]();
        chunk_size = N / p;
    }

    MPI_Bcast(&NOrig, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&chunk_size, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int *local_a = new int[chunk_size]();
    int *local_b = new int[chunk_size]();
    int *local_sum = new int[chunk_size]();
    MPI_Scatter(a, chunk_size, MPI_INT, local_a, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(b, chunk_size, MPI_INT, local_b, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    int incoming_carry = 0;
    if (rank > 0) {
        MPI_Recv(&incoming_carry, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    for (int i = 0; i < chunk_size; i++) {
        int s = local_a[i] + local_b[i] + incoming_carry;
        local_sum[i] = s % 10;
        incoming_carry = s / 10;
    }
    if (rank < p - 1) {
        MPI_Send(&incoming_carry, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
    }

    MPI_Gather(local_sum, chunk_size, MPI_INT, sum, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    int final_carry = 0;
    int final_carry_val = 0;

    if (p > 1) {
        if (rank == p - 1) {
            final_carry_val = incoming_carry;
        }

        MPI_Bcast(&final_carry_val, 1, MPI_INT, p - 1, MPI_COMM_WORLD);
        final_carry = final_carry_val;
    } else {
        final_carry = incoming_carry;
    }

    MPI_Barrier(MPI_COMM_WORLD);
    double end_time = MPI_Wtime();

    if (rank == 0) {
        int effective_array_size = N;
        if (final_carry > 0) {
            sum[NOrig] = final_carry;
            effective_array_size = NOrig + 1;
        } else {
            effective_array_size = N;
        }

        int last_non_zero_index = -1;

        for (int i = effective_array_size - 1; i >= 0; i--) {
            if (sum[i] != 0) {
                last_non_zero_index = i;
                break;
            }
        }

        int total_digits;
        if (last_non_zero_index != -1) {
            total_digits = last_non_zero_index + 1;
        } else {
            total_digits = 1;
        }

        ofstream fout(result_path);
        if (!fout) {
            cerr << "Cannot open output file\n";
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        for (int i = 0; i < total_digits; i++)
            fout << sum[i] << " ";
        fout << "\n";
        fout.close();

        double elapsed_seconds = end_time - start_time;
        double elapsed_milliseconds = elapsed_seconds * 1000.0;
        cout << "Timp total MPI Varianta 2: " << elapsed_milliseconds << " ms\n";
    }

    delete[] local_a;
    delete[] local_b;
    delete[] local_sum;
    if (rank == 0) {
        delete[] a;
        delete[] b;
        delete[] sum;
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
    string file1_path = "Vers2/data" + test + "/Numar1.txt";
    string file2_path = "Vers2/data" + test + "/Numar2.txt";
    string result_path = "Vers2/data" + test + "/Numar3.txt";

    string result_secv_path = "Vers2/data" + test + "/Numar3Secv.txt";


    run(rank, p, file1_path, file2_path, result_path);

    verifyResults(result_path, result_secv_path);

    MPI_Finalize();
    return 0;
}
