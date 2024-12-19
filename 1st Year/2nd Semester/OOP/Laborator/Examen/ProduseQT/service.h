#pragma once
#include "repository.h"
#include "Observer.h"
class Service:public Observable {
private:
    Repo& repo;
public:
    Service(Repo& repo):repo{repo}{}

    vector<Produs> get_all(){
        return sortare(repo.get_all());
    }
    vector<Produs> sortare(vector<Produs> p);

    string adauga(int id,string nume,string tip,double pret);

    int nr_tipuri(string tip);

    vector<string> tipuri();
};

