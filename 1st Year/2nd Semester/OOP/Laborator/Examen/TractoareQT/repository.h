#pragma once
#include "domain.h"
#include <vector>
using std::vector;

class Repo{
private:
    vector<Tractoare> tractoare;
    string fileName;
public:
    Repo(string fileName):fileName{fileName}{
        loadfromfile();
    }
    void loadfromfile();

    void storetofile();

    vector<Tractoare> get_all(){
        return tractoare;
    }

    void adauga(const Tractoare& t);
};