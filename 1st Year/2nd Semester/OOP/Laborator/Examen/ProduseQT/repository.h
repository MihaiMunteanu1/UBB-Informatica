#pragma once
#include "domain.h"

class Repo{
private:
    vector<Produs> produse;
    string fileName;
public:
    Repo(string fileName):fileName{fileName}{
        loadfromfile();
    }
    void loadfromfile();

    void storetofile();

    vector<Produs> get_all(){
        return produse;
    }

    void adauga(const Produs& p);
};