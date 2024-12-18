#include <iostream>
#include <fstream>
using namespace std;
ifstream f("graf.txt");
int viz[101];
int matrice_adiacenta[101][101];
void DFS(int x,int n)
{
    int i;
    viz[x]=1;
    for(i=0;i<n;i++)
    {
        if(matrice_adiacenta[x][i]==1 && viz[i]==0)
            DFS(i,n);
    }
}
int Conex(int n)
{
    int i;
    DFS(1,n);
    for(i=0;i<n;i++)
        if(viz[i]==0)
            return 0;
    return 1;
}

int main() {
    int n;
    f>>n;
    ///int matrice_adiacenta[n][n];
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            matrice_adiacenta[i][j]=0;
    int x;
    while(f>>x)
    {
        int y;
        f>>y;
        matrice_adiacenta[x-1][y-1] = 1;
        matrice_adiacenta[y-1][x-1] = 1;
    }

    ///A)
    cout<<"Nodurile izolate: ";
    int okk=1;
    for(int i=0;i<n;i++)
    {
        int ok=0;
        for(int j=0;j<n;j++)
            if(i!=j && matrice_adiacenta[i][j]==1) {
                ok = 1;
            }
        if(ok==0)
        {
            cout<<i+1<<" ";
            okk=0;
        }
    }
    if (okk==1)
        cout<<"nu exista"<<endl;
    else cout<<endl;


    ///B)
    int grad=0;
    int ok2=1;
    for(int j=0;j<n;j++)
    {
        if(matrice_adiacenta[0][j]==1)
            grad++;
    }
    for(int i=1;i<n;i++)
    {
        int gr=0;
        for(int j=0;j<n;j++)
            if(matrice_adiacenta[i][j]==1)
                    gr++;
        if(gr!=grad)
            ok2=0;
    }
    if(ok2)
        cout<<endl<<"Graful e regulat"<<endl;
    else cout<<endl<<"Graful nu e regulat"<<endl;

    ///C)
    cout<<endl<<"Matricea distantelor";
    int dr[n][n];
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            dr[i][j]=0;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++){
            if(i==j)
                dr[i][j]=0;
            else if(matrice_adiacenta[i][j]==1)
                dr[i][j]=1;
            else
                dr[i][j]=1000;
        }
    ///Roy FLoyd
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            for(int k=0;k<n;k++)
                if(dr[i][j]>dr[i][k]+dr[k][j])
                    dr[i][j]=dr[i][k]+dr[k][j];

    cout<<endl;
    for(int i=0;i<n;i++) {
        for (int j = 0; j < n; j++)
            cout << dr[i][j] << " ";
        cout << endl;
    }

    ///D)
    cout<<endl<<"Conex: ";
    if(Conex(n))
        cout<<"DA";
    else cout<<"NU";

    return 0;
}
