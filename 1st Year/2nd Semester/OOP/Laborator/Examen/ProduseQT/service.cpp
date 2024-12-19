#include "service.h"

vector<Produs> Service::sortare(vector<Produs> p) {
    sort(p.begin(),p.end(),[&](Produs& p1,Produs& p2){
        return p1.get_pret()<p2.get_pret();
    });
    return p;
}

string Service::adauga(int id, std::string nume, std::string tip, double pret) {
    string erori;
    for(auto& p:get_all())
        if(p.get_id()==id)
            erori.append("Id existent! ");
    if(nume=="")
        erori.append("Nume invalid! ");
    if(pret<=1.0 || pret>=100.0)
        erori.append("Pret invalid! ");
    if(erori.empty()){
        repo.adauga(Produs(id,nume,tip,pret));
        notify();
        return "";
    }
    else{
        return erori;
    }
}

int Service::nr_tipuri(std::string tip) {
    int cont=0;
    for(auto& p:get_all())
        if(p.get_tip()==tip)
            cont++;
    return cont;
}

vector<string> Service::tipuri() {
    vector<string> rez;
    for(auto& p:get_all()){
        string tip=p.get_tip();
        int ok=1;
        for(auto& tp:rez)
            if(tip==tp)
                ok=0;
        if(ok==1)
            rez.push_back(p.get_tip());
    }
    return rez;
}