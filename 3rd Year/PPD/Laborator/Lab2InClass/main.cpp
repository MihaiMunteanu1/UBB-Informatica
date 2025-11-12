//#include <iostream>
//#include <thread>
//#include <chrono> // pt masurare performanta
//#include <math.h>
//#include <string.h>
//
//using namespace std;
//using namespace std::chrono;
//
//// int b[100]; // se afla pe data segment ( var declarata inafara main-ului )
//
//const int N = 10000000;
//const int MAX_VAL = 10000;
//const int P = 8; // nr threads ( procese )
//
//int a[N], b[N], c[N], c_secv[N];
//
//void init(int *v, int len){
//    for(int i=0;i<len;i++){
//        v[i] = rand() % MAX_VAL;
//    }
//}
//
//void sum(const int *a,const int *b, int *c, int len){
//    for(int i = 0; i < len; i ++){
//        c[i] = a[i] + b[i];
//        //c[i] = sqrt(a[i]*a[i]*a[i]) - b[i]*b[i];
//    }
//}
//
//void sum_par(const int *a,const int *b, int *c, int start_idx, int end_idx){
//    for(int i = start_idx; i < end_idx; i ++){
//        c[i] = a[i] + b[i];
//        //c[i] = sqrt(a[i]*a[i]*a[i]) - b[i]*b[i];
//
//    }
//}
//
//void run_thr(int *a, int *b, int *c, int *c_secv){
//    int dim_split = N / P;
//    int r = N % P;
//
//    int start_idx = 0;
//    int end_idx = dim_split;
//
//    thread t[P];
//
//    auto start_par = high_resolution_clock::now();
//    for(int thread_idx = 0; thread_idx< P; thread_idx++){
//        if(r>0){
//            end_idx ++;
//            r--;
//        }
//
////        cout<<"Thread: " << thread_idx
////        <<" start: "<< start_idx
////        <<" end: "<< end_idx<<endl;
//
//        t[thread_idx]  = thread(sum_par,a,b,c,start_idx, end_idx);
//
//        start_idx = end_idx;
//        end_idx += dim_split; // sau end_idx = start_idx + dim_split
//    }
//
//    for(int thread_idx = 0; thread_idx< P; thread_idx++) {
//        t[thread_idx].join();
//    }
//    auto end_par = high_resolution_clock::now();
//    duration<double,milli> delta_par = end_par - start_par;
//
//    cout<<"Par time: "<<delta_par.count() << " ms \n";
//
//
//    // c[1]= 0; // eroare pt verificare
//
//    for(int i =0 ;i<N;i++){
//        if(c[i] != c_secv[i]){
//            cout<<"Err at: "<< i<< " c: "<<c[i]<<" c_secv: "<<c_secv[i]<<endl;
//            exit(1);
//        }
//    }
//}
//
//int main() {
//    cout << "Hello thread!" << endl;
//
//    init(a,N);
//    init(b,N);
//
//    auto start_secv = high_resolution_clock::now();
//    sum(a,b,c_secv,N);
//    auto end_secv = high_resolution_clock::now();
//    duration<double,milli > delta_secv = end_secv - start_secv;
//
//    cout<<"Secv time: "<<delta_secv.count() << " ms \n";
//
//    for(int i=0;i<3;i++){
//        cout<<"a: "<<a[i];
//        cout<<" b: "<<b[i];
//        cout<<" c: "<<c_secv[i]<<endl;
//    }
//
//    run_thr(a,b,c,c_secv);
//
//    int *a_d = new int [N];
//    int *b_d = new int [N];
//    int *c_d = new int [N];
//
//    int *all = new int[N*3];
//
//    memcpy(a_d,a,N * sizeof(int));
//    memcpy(b_d,a,N * sizeof(int));
//
//    memcpy(all,b,N * sizeof(int));
//    memcpy(all + N,b,N * sizeof(int));
//
//    run_thr(a_d,b_d,c_d,c_secv);
//    run_thr(all,all+N,all+N*2,c_secv);
//
//    delete[] a_d;
//    delete[] b_d;
//    delete[] c_d;
//    delete[] all;
//
//    return 0;
//}


#include <iostream>
#include <thread>
#include <cstring>
#include <ranges>
using namespace std;
using namespace std::chrono;

const int N = 10000000;
const int MAX_VAL = 10000;
const int P = 8;
int a[N], b[N], c[N], c_secv[N];

void init(int* v, int len) {
    for (int i = 0; i < len; i++) {
        v[i] = rand() % MAX_VAL;;
    }
}

void sum_par(const int* a,const int* b, int* c, int start_idx, int end_idx) {
    for (int i = start_idx; i < end_idx; i++) {
        c[i] = a[i] + b[i];
    }
}

void sum(int* a, int* b, int* c, int len) {
    for (int i = 0; i < len; i++) {
        c[i] = a[i] + b[i];
    }
}

void run_thr(int *a, int *b, int *c, int *c_secv){
    int dim_split = N / P;
    int r = N % P;

    int start_idx = 0;
    int end_idx = dim_split;

    thread t[P];

    auto start_par = high_resolution_clock::now();
    for(int thread_idx = 0; thread_idx< P; thread_idx++){
        if(r>0){
            end_idx ++;
            r--;
        }

        //        cout<<"Thread: " << thread_idx
        //        <<" start: "<< start_idx
        //        <<" end: "<< end_idx<<endl;

        t[thread_idx]  = thread(sum_par,a,b,c,start_idx, end_idx);

        start_idx = end_idx;
        end_idx += dim_split; // sau end_idx = start_idx + dim_split
    }

    for(int thread_idx = 0; thread_idx< P; thread_idx++) {
        t[thread_idx].join();
    }
    auto end_par = high_resolution_clock::now();
    duration<double,milli> delta_par = end_par - start_par;

    cout<<"Par time: "<<delta_par.count() << " ms \n";


    // c[1]= 0; // eroare pt verificare

    for(int i =0 ;i<N;i++){
        if(c[i] != c_secv[i]){
            cout<<"Err at: "<< i<< " c: "<<c[i]<<" c_secv: "<<c_secv[i]<<endl;
            exit(1);
        }
    }
}

int main() {
    cout << "Hello thread!" << endl;

    init(a, N);
    init(b, N);

    auto start_secv = high_resolution_clock::now();
    sum(a, b, c_secv, N);
    auto end_secv = high_resolution_clock::now();
    duration<double, milli> delta_secv = end_secv - start_secv;

    cout << "Secv time: " << delta_secv.count() << "ms " << endl;

    for (int i = 0; i < 3; i++) {
        cout << "a: " << a[i] << " b: " << b[i] << " c: " << c_secv[i] << endl;
    }
    run_thr(a,b,c,c_secv);

    int *a_d = new int[N];
    int *b_d = new int[N];
    int *c_d = new int[N];

    int *all = new int[N*3];

    memcpy(a_d,a,sizeof(int) * N);
    memcpy(b_d,b,sizeof(int) * N);

    memcpy(all, a, N*sizeof(int));
    memcpy(all + N,b,sizeof(int) * N);

    run_thr(a_d,b_d,c_d,c_secv);
    run_thr(all, all+N, all+N*2, c_secv);

    delete[] a_d;
    delete[] b_d;
    delete[] c_d;
    delete[] all;
    return 0;
}