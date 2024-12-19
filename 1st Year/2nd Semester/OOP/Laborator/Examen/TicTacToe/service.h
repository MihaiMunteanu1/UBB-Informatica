#pragma once
#include "repository.h"

class Service {
private:
    Repo& repo;
public:
    Service(Repo& repo):repo{repo}{}

    vector<Joc> get_all(){
        return sortare(repo.get_all());
    }

    vector<Joc> sortare(vector<Joc> jocuri);

    void adauga(int id,int dim,string tabla,char jucator);

    void modifica(int id,int dim,string tabla,char jucator,string stare);

};



