#include <iostream>
#include <fstream>
#define INF 9999
using namespace std;
ifstream f("input.txt");
ofstream g("output.txt");

int n,graf[20][20],distante[20],parinte[20];

void citire_graf() {
    f>>n;
    int x,y,z;
    while (f>>x>>y>>z) {
        graf[x][y]=z;
    }
}

void relaxare(int j, int k) {
    if (distante[k]>distante[j]+graf[j][k]) {
        distante[k]=distante[j]+graf[j][k];
        parinte[k]=j;
    }
}

bool bellman_ford(int nod_start) {
    int i,j,k;
    for (i=1;i<=n;i++)
    {
        distante[i]=INF;
        parinte[i]= -1;
    }
    distante[nod_start]= 0;
    parinte[nod_start]= 0;

    for (i=1; i<=n; i++) {
        for (j=1;j<=n;j++)
            for (k=1; k<=n; k++)
            {
                if (graf[j][k] != 0 ) {
                    relaxare(j, k);
                }
            }
    }
    for (j=1; j<=n; j++)
        for (k=1; k<=n; k++)
        {
            if (graf[j][k] != 0 && distante[k]>distante[j]+graf[j][k]) {
                return false;
            }
        }
    return true;

}
int main() {
    citire_graf();
    int nod_start,i;
    cout<<"Nodul de start este: ";
    cin>>nod_start;
    bool ok=bellman_ford(nod_start);
    if (!ok) {
        g<<"Ciclu infinit!";
        return 0;
    }
    g<<"Nodul sursa: "<<nod_start<<endl;
    g<<"   D P"<<endl;
    for (i=1; i<=n; i++)
    {
        g<<i<<": "<<distante[i]<<' ';
        int j=i;
        while(parinte[j]!=0 && parinte[j]!=nod_start)
        {
            g<<parinte[j]<<' ';
            j=parinte[j];
        }
        g<<endl;
    }

    return 0;
}