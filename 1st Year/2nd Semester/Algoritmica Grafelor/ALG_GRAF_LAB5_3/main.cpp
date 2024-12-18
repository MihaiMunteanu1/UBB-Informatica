#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
using VI = vector<int>;
using VVI = vector<VI>;

int n;
VI L;
VVI G;

void eulerian(int k)
{
    for (int i = 0; i < n; i++)
        if (G[k][i] != 0)
        {
            G[k][i] = G[i][k] = 0;
            eulerian(i);
        }
    L.emplace_back(k);
}



int main(int argc,char* argv[])
{
    ifstream f(argv[1]);
    ofstream g(argv[2]);
    int x, y, m;
    f >> n >> m;
    G = VVI(n);
    for (int i = 0; i < n; i++)
        G[i] = VI(n, 0);
    for (int i = 1; i <= m; i++)
    {
        f >> x >> y;
        G[x][y] = G[y][x] = 1;
    }
    f.close();
    eulerian(0);
    for (auto& yy : L)
        g << yy << " ";
    g.close();
    return 0;
}