#include <fstream>
#include <barrier>
#include <string>
#include <iomanip>
#include <thread>
#include "my_barrier.h"
using namespace std;

int p;
int N, M, k;
int** F,** C;

void readDate(const string& filename) {
    ifstream fin(filename);
    fin >> N;
    M=N;
    F = new int* [N];
    for (int i = 0; i < N; ++i)
        F[i] =new int[M];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            fin >> F[i][j];
        }
    }
    k=3;
    C = new int* [k];
    for (int i = 0; i < k; ++i)
        C[i] = new int[k];
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            fin >> C[i][j];
        }
    }
}


void freeMatrix(int** a, int rows) {
    if (!a)
        return;
    for (int i = 0; i < rows; i++)
        delete[] a[i];
    delete[] a;
}


void deallocate() {
    freeMatrix(F, N);
    freeMatrix(C, k);
}

void writeResult(bool secv=false,bool par=false){
    if(secv){
        ofstream gS("outputSecv.txt");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                gS <<setw(5)<< F[i][j] << " ";
            }
            gS<<endl;
        }
        gS.close();
    }
    if(par){
        ofstream gP("outputPar.txt");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                gP <<setw(5)<< F[i][j] << " ";
            }
            gP<<endl;
        }
        gP.close();
    }
}

void verifyResults() {
    ifstream file1("outputSecv.txt");
    ifstream file2("outputPar.txt");

    string line1, line2;
    int lineNumber = 1;

    while (true) {
        bool eof1 = !getline(file1, line1);
        bool eof2 = !getline(file2, line2);

        if (eof1 && eof2)
            break;

        if (eof1 || eof2 || line1 != line2) {
            std::cout << "Diferenta la linia " << lineNumber << ":\n";
            std::cout << "outputSecv: " << (eof1 ? "EOF" : line1) << "\n";
            std::cout << "outputPar : " << (eof2 ? "EOF" : line2) << "\n";
        }
        lineNumber++;
    }

    file1.close();
    file2.close();
}

int clamp(int value, int min, int max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}


void applyConvolution(int i, int j, int end, const int* prev_line,const int* curr_line,const int* next_line) {
    int s = 0;
    int diff = (k - 1) / 2;
    for (int x = 0; x < k; x++) {
        for (int y = 0; y < k; y++) {
            int ii = i - diff + x;
            int jj = j - diff + y;

            ii=clamp(ii,0,N-1);
            jj=clamp(jj,0,N-1);

            int elem_cov;
            if (ii < i) {
                elem_cov = prev_line[jj];
            }
            else if (ii == i) {
                elem_cov = curr_line[jj];
            }
            else if (ii >= end) {
                elem_cov = next_line[jj];
            }
            else {
                elem_cov = F[ii][jj];
            }
            s += elem_cov * C[x][y];
        }
    }
    F[i][j] = s;
}

void convultieSecventiala() {
    int* previous_line = new int[M];
    int* curr_line = new int[M];
    int* next_line = new int[M];

    for (int i = 0; i < M; i++) {
        previous_line[i] = F[0][i];
        curr_line[i] = F[0][i];
        next_line[i] = F[N - 1][i];

    }
    for (int i = 0; i < N; i++) {
        if (i != 0) {
            for (int j = 0; j < M; j++) {
                previous_line[j] = curr_line[j];
                curr_line[j] = F[i][j];
            }
        }
        for (int j = 0; j < M; j++) {
            applyConvolution(i, j, N, previous_line, curr_line, next_line);
        }
    }
    delete[] previous_line;
    delete[] curr_line;
    delete[] next_line;
}



void computeRows(int start, int end, my_barrier& barrier) {
    int* previous_line = new int[M];
    int* curr_line = new int[M];
    int* next_line = new int[M];

    int previous_line_number = start - 1;
    int next_line_number = end;
    if (previous_line_number < 0) {
        previous_line_number = 0;
    }
    if (next_line_number >= N) {
        next_line_number = N - 1;
    }

    for (int i = 0; i < N; i++) {
        previous_line[i] = F[previous_line_number][i];
        curr_line[i] = F[previous_line_number][i];
        next_line[i] = F[next_line_number][i];
    }

    barrier.wait();

    for (int i = start; i < end; i++)
    {
        if (i != previous_line_number) {
            for (int j = 0; j < M; j++)
            {
                previous_line[j] = curr_line[j];
                curr_line[j] = F[i][j];
            }
        }

        for (int j = 0; j < M; j++) {
            applyConvolution(i, j, end, previous_line, curr_line, next_line);
        }
    }
}

void parallelHorizontal() {
    thread t[p];
    int dim_split = N / p;
    int r = N % p;
    int start = 0;
    int end;
    my_barrier barrier(p);
    for (int i = 0; i < p; i++) {
        int currentNoRows = dim_split;
        if (r > 0) {
            r--;
            currentNoRows++;
        }
        end = start + currentNoRows;
        t[i] = thread(computeRows, start, end, ref(barrier));
        start += currentNoRows;
    }
    for (int i = 0; i < p; i++)
    {
        t[i].join();
    }
}

int main(int argc, char* argv[])
{
    //p = stoi(argv[1]);
    p=2;
    const string filename = "date1.txt";

    readDate(filename);

    const auto start = std::chrono::high_resolution_clock::now();
    parallelHorizontal();
  //  convultieSecventiala();
    const auto end = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double, std::milli> duration = end - start;

    cout<<"Timp: "<<endl;
    std::cout << duration.count();

    deallocate();
}