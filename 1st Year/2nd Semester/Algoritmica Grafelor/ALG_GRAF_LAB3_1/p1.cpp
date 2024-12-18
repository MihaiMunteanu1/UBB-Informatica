#include <iostream>
#include <fstream>
#define inf 99999999
using namespace std;
int d[10001];

struct bellman{
    int x,y,w;
}muchie[10001];

void relax(int x,int y,int w){
    if(d[y]>d[x]+w){
        d[y]=d[x]+w;
    }
}
int bellman_ford(int n, int m, int s){
    for(int i=0;i<n;i++)
        d[i]=inf;
    d[s]=0;
    for(int i=0;i<n-1;i++)
        for(int j=1;j<=m;j++)
            relax(muchie[j].x,muchie[j].y,muchie[j].w);
    for(int i=1;i<=m;i++)
        if(d[muchie[i].y]>d[muchie[i].x]+muchie[i].w)
            return 0;
    return 1;
}
int main(int argc, char *argv[]) {
    ifstream f(argv[1]);
    ofstream g(argv[2]);

    int n,m,s;
    f >> n >> m >> s;

    for(int i=1;i<=m;i++)
        f >> muchie[i].x >> muchie[i].y >> muchie[i].w;
    f.close();

    if(bellman_ford(n,m,s))
        for(int i=0;i<n;i++)
            if (d[i]==inf)
                g << "inf ";
            else g << d[i] << " ";
    else
        g << "Ciclu negativ!";

    g.close();
    return 0;
}
/**
*
5 7 0
0 2 4
0 3 1
1 0 1
1 2 4
2 0 1
2 3 1
3 4 1
 ------
 6 6 1
1 2 5
1 3 3
2 3 2
2 4 6
3 4 -2
4 1 4
*/