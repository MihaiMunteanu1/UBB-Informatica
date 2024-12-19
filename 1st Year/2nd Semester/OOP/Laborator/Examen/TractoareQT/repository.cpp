#include "repository.h"
#include <fstream>
using std::ifstream;
using std::ofstream;

void Repo::loadfromfile() {
    ifstream f(fileName);
    int id,nrRoti;
    string denumire,tip;
    while(f>>id>>denumire>>tip>>nrRoti){
        Tractoare t(id,denumire,tip,nrRoti);
        tractoare.push_back(t);
    }
    f.close();
}

void Repo::storetofile() {
    ofstream g(fileName);

    for (auto tr:tractoare){
        int id=tr.get_id();
        int nrRoti=tr.get_nrRoti();
        string denumire=tr.get_denumire();
        string tip=tr.get_tip();
        g<<id<<" "<<denumire<<" "<<tip<<" "<<nrRoti<<"\n";
    }

    g.close();
}

void Repo::adauga(const Tractoare& t) {
    tractoare.push_back(t);
    storetofile();
}