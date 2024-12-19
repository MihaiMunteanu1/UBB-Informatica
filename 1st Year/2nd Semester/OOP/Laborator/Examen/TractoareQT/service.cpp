#include "service.h"
#include <algorithm>
#include <exception>
#include <iostream>
void Service::adauga(int id, std::string denumire, std::string tip, int nrRoti) {
    if(denumire.empty() || tip.empty())
        throw ("Denumire invalida sau Tip invalid");
    if(nrRoti%2==1 || nrRoti<2 || nrRoti>16)
        throw ("Nr Roti invalid");
    for(auto& t:repo.get_all())
        if(t.get_id()==id)
            throw("Id existent");
    repo.adauga(Tractoare(id,denumire,tip,nrRoti));
}

vector<Tractoare> Service::sortare(vector<Tractoare> tractoare) {
    sort(tractoare.begin(),tractoare.end(),[&](Tractoare& t1,Tractoare& t2){
        return t1.get_denumire()<t2.get_denumire();
    });
    return tractoare;
}

vector<string> Service::getTipuri(vector<Tractoare> tractoare) {
    vector<string> tipuri;
    for(auto &t : tractoare) {
        int ok = 1;
        for(auto &tip : tipuri) {
            if(t.get_tip() == tip) {
                ok = 0;
            }
        }
        if(ok == 1) {
            tipuri.push_back(t.get_tip());
        }
        ok = 1;
    }
    return tipuri;
}

int Service::nrTipuri(Tractoare t) {
    int nr = 0;
    for(auto &tr : get_all()) {
        if(tr.get_tip() == t.get_tip()) {
            nr++;
        }
    }
    return nr;
}