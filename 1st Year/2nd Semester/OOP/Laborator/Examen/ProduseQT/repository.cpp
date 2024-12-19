#include "repository.h"
#include <sstream>
void Repo::adauga(const Produs &p) {
    produse.push_back(p);
    storetofile();
}
void Repo::loadfromfile() {
    ifstream f(fileName);
    string line;
    while(getline(f,line)){
        int id;
        string nume,tip;
        double pret;
        stringstream linestream(line);
        string curent;
        int nr=0;
        while(getline(linestream,curent,',')){
            if(nr==0)
                id=stoi(curent);
            if(nr==1)
                nume=curent;
            if(nr==2)
                tip=curent;
            if(nr==3)
                pret=stod(curent);
            nr++;
        }
        Produs p(id,nume,tip,pret);
        produse.push_back(p);
    }
    f.close();
}
void Repo::storetofile() {
    ofstream g(fileName);
    for(auto& p:produse)
        g<<p.get_id()<<","<<p.get_nume()<<","<<p.get_nume()<<","<<p.get_pret()<<"\n";
    g.close();
}