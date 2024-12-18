#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
vector<int> Decodare_Prufer(vector<int>& code, int n) {
    n++;
    vector<int> parinte(n, -1);
    vector<int> degree(n, 1);

    for (int node : code) {
        degree[node]++;
    }

    int i = 0;
    while (degree[i] != 1) i++;
    int frunza = i;

    for (int node : code) {
        parinte[frunza] = node;
        degree[node]--;
        degree[frunza]--;

        if (degree[node] == 1 && node < i) {
            frunza = node;
        } else {
            i++;
            while (degree[i] != 1) i++;
            frunza = i;
        }
    }
    parinte[frunza] = -1;
    return parinte;
}

int main(int argc,char* argv[])
{
    ifstream f(argv[1]);
    ofstream g(argv[2]);
    vector<int> v;

    int n;
    f >> n;

    for (int i = 0; i < n; ++i) {
        int x;
        f >> x;
        v.push_back(x);
    }
    f.close();
    auto tree = Decodare_Prufer(v, n);

    g << tree.size() << "\n";
    for (auto t : tree) {
        g << t << " ";
    }
    g.close();
    return 0;
}