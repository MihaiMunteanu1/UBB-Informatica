#pragma once
#include "repository.h"

class Service{
private:
    Repo& repo;
public:
    Service(Repo& repo):repo{repo}{}

    vector<Tractoare> get_all(){
        return sortare(repo.get_all());
    }
    vector<Tractoare> sortare(vector<Tractoare> tractoare);

    void adauga(int id,string denumire,string tip,int nrRoti);

    vector<string> getTipuri(vector<Tractoare> tractoare);

    int nrTipuri(Tractoare t);

};