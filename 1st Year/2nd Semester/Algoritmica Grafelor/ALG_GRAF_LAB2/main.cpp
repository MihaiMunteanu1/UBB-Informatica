#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
ifstream f1("input.txt");
ifstream f2("input2.txt");
ifstream f3("labirint_1.txt");
ofstream g("labirint1_rezolvat.txt");
///Problema 1
int mat[100][100], viz[100][100], rez[100];
int n,mini=-1;
void  dfs(int node, int nr )
{
    int c = 0;
    for (int i = 0; i <= n; i++)
        if (mat[node][i] && viz[node][i] == 0){
            rez[nr] = i;
            viz[node][i] = 1;
            dfs(i, nr + 1);
            viz[node][i] = 0;
            c++;
        }
    if (c == 0 and (mini == -1 || nr < mini))
        mini = nr;
}

///Problema 2
int mat2[100][100];
void afisare_matrice(int n2)
{
    for(int i = 1; i<=n2; i++) {
        for(int j = 1; j<=n2; j++) {
            cout<<mat2[i][j]<<" ";
        }
        cout<<endl;
    }
}

void matrice_inchidere_tranzitiva(int n2)
{
    for(int k = 1; k<=n2; k++)
    {
        for(int i = 1; i<=n2; i++)
        {
            for(int j = 1; j<=n2; j++)
            {
                if(mat2[i][j] == 0)
                {
                    mat2[i][j] = (mat2[i][k] && mat2[k][j]);
                }
            }
        }
    }
}

///Problema 3
int mat3[1000][1000],n3,m3,xs,ys,xf,yf;
char sir[1000];

void bordare_matrice()
{
    //bordarea matricei
    for(int i = 0; i <= n3+1; i++)
    {
        mat3[i][0] = -1;
        mat3[i][m3 + 1] = -1;
    }
    for(int i = 0;i <= m3+1; i++)
    {
        mat3[0][i] = -1;
        mat3[n3 + 1][i] = -1;
    }
}

void algoritm_lee(int x, int y)
{
    if(x == xf && y == yf) {
        return;
    }
    if(mat3[x + 1][y] == 0 || mat3[x][y] + 1 < mat3[x + 1][y]) {
        mat3[x + 1][y] = mat3[x][y] + 1;
        algoritm_lee(x + 1, y);
    }
    if(mat3[x - 1][y] == 0 || mat3[x][y] + 1 < mat3[x - 1][y]) {
        mat3[x - 1][y] = mat3[x][y] + 1;
        algoritm_lee(x - 1, y);
    }
    if(mat3[x][y + 1] == 0 || mat3[x][y] + 1 < mat3[x][y + 1]) {
        mat3[x][y + 1] = mat3[x][y] + 1;
        algoritm_lee(x, y + 1);
    }
    if(mat3[x][y - 1] == 0 || mat3[x][y] + 1 < mat3[x][y - 1]) {
        mat3[x][y - 1] = mat3[x][y] + 1;
        algoritm_lee(x, y - 1);
    }
}
///Problema 4
int vizitati[100],mat4[100][100],n4;
int coada[100],inceput,sfarsit;

void BFS(int nod)
{
    coada[sfarsit++] = nod;
    int d = 1;
    vizitati[nod] = 1;
    while(sfarsit != inceput)
    {
        for(int i=1;i<=n4;i++)
            if(mat4[coada[inceput]][i] && !vizitati[i])
            {
                cout << i << " " << d << endl;
                coada[sfarsit++] = i;
                vizitati[i] = 1;
            }
        inceput++;
        d++;
    }
}

///Problema 5
int viz5[100],mat5[100][100];
void DFS(int nod,int n5)
{
    for (int i = 1; i <= n5; i++)
    {
        if(!viz5[i] and mat5[nod][i])
        {
            cout << i << " ";
            viz5[i] = 1;
            DFS(i,n5);
        }
    }
}
int main() {
    /// Problema 1
    /*int x, y, vf;
    f1 >> n;
    while (f1 >> x >> y){
        mat[x][y] = 1;
    }
    cout<<"Varf sursa: ";
    cin >> vf;
    cout<<endl;
    dfs(vf, 0);
    cout<< vf<<" ";
    for (int i = 0; i < mini; i++)
        cout<< rez[i] << " ";*/

    ///Problema 2
    int x,y;
    int n2, m;
    f2 >> n2 >> m;
    while(f2>>x>>y)
    {
        mat2[x][y] = 1;
    }
    cout<<"Matricea inchiderii tranzitive: "<<endl;
    matrice_inchidere_tranzitiva(n2);
    afisare_matrice(n2);
    /**
     * pt prob 2
     * 5 6
1 2
2 3
2 5
3 4
4 2
4 5
     */
    ///Problema 3
    /*int x,y;

    while(f3.getline(sir, 2000))
    {
        n3++;
        m3 = strlen(sir);

        for(int i = 0; i<strlen(sir); i++) {
            if(sir[i] == '1')
                mat3[n3][i + 1] = -1;

            else if(sir[i] == ' ')
                mat3[n3][i + 1]=0;

            else if(sir[i] == 'S')
            {
                mat3[n3][i + 1] = 1;
                xs = n3;
                ys = i + 1;
            }
            else
            {
                xf = n3;
                yf = i + 1;
            }
        }
    }

    bordare_matrice();
    algoritm_lee(xs, ys);

    g << "lungime drum: " << mat3[xf][yf] << '\n';

    x = xf;
    y = yf;

    while(x != xs || y != ys)
    {
        if(mat3[x - 1][y] + 1 == mat3[x][y]) {
            mat3[x][y] = -2;
            x--;
        }
        else if(mat3[x + 1][y] + 1 == mat3[x][y]) {
            mat3[x][y] = -2;
            x++;
        }
        else if(mat3[x][y - 1] + 1 == mat3[x][y]) {
            mat3[x][y] = -2;
            y--;
        }
        else if(mat3[x][y + 1] + 1 == mat3[x][y]) {
            mat3[x][y] = -2;
            y++;
        }
    }

    mat3[xf][yf] = -3;

    for(int i = 1; i <= n3; i++) {
        for(int j = 1; j <= m3; j++) {
            if(mat3[i][j] == 1)
                g << 'S';
            else if(mat3[i][j] == -2)
                g << 'X';
            else if(mat3[i][j] == -3)
                g << 'F';
            else g << ' ';
        }
        g << '\n';
    }*/

    ///Problema 4
    /*int x,y;
    f1 >> n4;
    while(f1 >> x >> y)
    {
        mat4[x][y] = 1;
    }
    int nod;
    cout<<"Varf sursa: ";
    cin >> nod;
    BFS(nod);*/

    ///Problema 5
    /*int x5,y5,nod5,n5;
    f1 >> n5;
    while(f1 >> x5 >> y5)
        mat5[x5][y5] = 1;
    cout<<"Varf visit: ";
    cin >> nod5;
    DFS(nod5,n5);*/
    return 0;
}
