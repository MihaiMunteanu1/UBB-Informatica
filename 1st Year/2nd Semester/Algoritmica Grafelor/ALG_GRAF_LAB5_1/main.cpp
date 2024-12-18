#include <bits/stdc++.h>

using namespace std;

#define nmax 1001


int n , m;

vector < int > graf[nmax];
int cost[nmax][nmax], reziduri[nmax][nmax];
int viz[nmax] , pred[nmax];

int bfs(ofstream &g)
{

    for(int i=0;i<=n;i++)
        viz[i] = 0;
    queue < int > noduri;
    noduri.push(1);
    viz[1] = 1;
    while(!noduri.empty()){
        int nc = noduri.front();
        for(int i=0;i<graf[nc].size()&&nc!=n;i++){
            int nv = graf[nc][i];
            if(reziduri[nc][nv]==cost[nc][nv]||viz[nv]==1)continue;
            viz[nv] = 1;
            noduri.push(nv);
            pred[nv] = nc;
        }

        noduri.pop();
    }
    return viz[n];
}

int edmonds_karp(ofstream &g){
    int noduri, fminim, flux;
    flux = 0;
    while(bfs(g)==1){
            for(int i=0;i<graf[n].size();i++)
            {
                int nc = graf[n][i];
                if(cost[nc][n]==reziduri[nc][n]||viz[nc]==0)
                    continue;
                pred[n] = nc;
                fminim = 550000005;
                for(noduri = n; noduri != 1; noduri = pred[noduri]){
                    fminim = min(fminim,cost[pred[noduri]][noduri]-reziduri[pred[noduri]][noduri]);
                }
                if(fminim==0)
                    continue;
                for(noduri = n; noduri != 1; noduri = pred[noduri]){
                    reziduri[pred[noduri]][noduri] += fminim;
                    reziduri[noduri][pred[noduri]] -= fminim;
                }
                flux += fminim;
            }
    }
    return flux;
}

int main(int argc,char* argv[])
{
    ifstream f(argv[1]);
    ofstream g(argv[2]);
    int x , y , z;
    f >> n >> m;
    for(int i=1;i<=m;i++){
        f >> x >> y >> z;
        x++;y++;
        cost[x][y] += z;
        graf[x].push_back(y);
        graf[y].push_back(x);
    }
    f.close();
    g << edmonds_karp(g);
    g.close();
    return 0;
}