#include <iostream>
#include <thread>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace std::chrono;

const int MAX_DIM = 10000;
const int MAX_VAL =100;
int N,M,n,p;
double finalTime;


int F[MAX_DIM][MAX_DIM],C[MAX_DIM][MAX_DIM],V[MAX_DIM][MAX_DIM],V_Secv[MAX_DIM][MAX_DIM];


void readDate(){
    ifstream f("date.txt");
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            f>>F[i][j];
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            f>>C[i][j];
        }
    }
}

void generareDate(){
    ofstream g("date.txt");
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            g<<rand()%MAX_VAL<<" ";
        }
        g<<endl;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            g<<rand()%2<<" ";
        }
        g<<endl;
    }

    g.close();
}

int clamp(int value, int min, int max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

void convultieSecventiala(){

    auto start_secv = high_resolution_clock::now();

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int s = 0;
            for (int a = 0; a < n; a++)
                for (int b = 0; b < n; b++){
                    int ii = i - n / 2 + a;
                    int jj = j - n / 2 + b;

                    ii = clamp(ii, 0, N - 1);
                    jj = clamp(jj, 0, M - 1);

                    s += F[ii][jj] * C[a][b];
                }
            V_Secv[i][j] = s;
        }
    }

    auto end_secv = high_resolution_clock::now();

    duration<double, milli> delta_secv = end_secv - start_secv;
    cout << "Secv time: " << delta_secv.count() << "ms " << endl << endl;

    finalTime = delta_secv.count();

}

void computeRows(const int F[][MAX_DIM], const int C[MAX_DIM][MAX_DIM], int V[][MAX_DIM], int startRow, int endRow) {
    for(int i = startRow; i < endRow; i++) {
        for(int j = 0; j < M; j++) {
            int s = 0;
            for(int a = 0; a < n; a++)
                for(int b = 0; b < n; b++){
                    int ii = i - n / 2 + a;
                    int jj = j - n / 2 + b;

                    ii = clamp(ii, 0, N - 1);
                    jj = clamp(jj, 0, M - 1);

                    s += F[ii][jj] * C[a][b];
                }
            V[i][j] = s;
        }
    }
}
void computeColumns(const int F[][MAX_DIM], const int C[MAX_DIM][MAX_DIM], int V[][MAX_DIM], int startCol, int endCol) {
    for(int i = 0; i < N; i++) {
        for(int j = startCol; j < endCol; j++) {
            int s = 0;
            for(int a = 0; a < n; a++)
                for(int b = 0; b < n; b++){
                    int ii = i - n / 2 + a;
                    int jj = j - n / 2 + b;

                    ii = clamp(ii, 0, N - 1);
                    jj = clamp(jj, 0, M - 1);

                    s += F[ii][jj] * C[a][b];
                }
            V[i][j] = s;
        }
    }
}

void parallelHorizontal() {
    int dim_split = N / p;
    int r = N % p;

    thread t[p];
    int startRow = 0;
    int endRow =dim_split;

    auto start_par = high_resolution_clock::now();

    for(int i = 0; i < p; i++) {
        if(r > 0) {
            endRow++;
            r--;
        }
        t[i] = thread (computeRows, F, C, V, startRow, endRow);
        startRow = endRow;
        endRow += dim_split;
    }

    for(auto &th : t)
        th.join();

    auto end_par = high_resolution_clock::now();
    duration<double,milli> delta_par = end_par - start_par;

    cout<<"Par time horizontal: "<<delta_par.count() << " ms \n";

    finalTime = delta_par.count();

}


void parallelVertical() {
    int dim_split = M / p;
    int r = M % p;

    thread t[p];
    int startCol = 0;
    int endCol =dim_split;

    auto start_par = high_resolution_clock::now();

    for(int i = 0; i < p; i++) {
        if(r > 0) {
            endCol++;
            r--;
        }
        t[i] = thread(computeColumns, F, C, V, startCol, endCol);
        startCol = endCol;
        endCol += dim_split;
    }

    for(auto &th : t)
        th.join();

    auto end_par = high_resolution_clock::now();
    duration<double,milli> delta_par = end_par - start_par;

    cout<<"Par time vertical: "<<delta_par.count() << " ms \n";

    finalTime = delta_par.count();

}

void writeResult(){
    ofstream g("outputSecv.txt");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            g <<setw(5)<< V_Secv[i][j] << " ";
        }
        g<<endl;
    }
    g.close();

    ofstream gP("outputPar.txt");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            gP <<setw(5)<< V[i][j] << " ";
        }
        gP<<endl;
    }
    gP.close();
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



int main(int argc, char* argv[]) {

    N=10;
    M=10;
    n=3;
    p=4;

    generareDate();
    readDate();

    convultieSecventiala();
    parallelHorizontal();
//    parallelVertical();


    writeResult();
    verifyResults();

    //cout<<finalTime<<endl;



    return 0;

}
