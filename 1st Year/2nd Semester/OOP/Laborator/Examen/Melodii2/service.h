#pragma once
#include "repository.h"

class Service {
private:
    Repo& repo;
public:
    Service(Repo& repo):repo{repo}{}

    vector<Melodie> get_all(){
        return sortare(repo.get_all());
    }

    vector<Melodie> sortare(vector<Melodie> m);

    void adauga(string titlu,string artist,string gen);

    void sterge(int id);

    int nr_melodii_gen(const string& gen);

    int nr_melodii_artist(const string& artist);
};


