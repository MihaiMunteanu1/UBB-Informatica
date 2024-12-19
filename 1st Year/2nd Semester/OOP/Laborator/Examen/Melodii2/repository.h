#pragma once
#include "domain.h"

class Repo {
private:
    vector<Melodie> melodii;
    string fileName;
    void loadfromfile();
public:
    Repo(string fileName):fileName{fileName}{
        loadfromfile();
    }
    void storetofile();

    vector<Melodie> get_all(){
        return melodii;
    }

    void sterge(int id);

    void adauga(Melodie& m);

};



