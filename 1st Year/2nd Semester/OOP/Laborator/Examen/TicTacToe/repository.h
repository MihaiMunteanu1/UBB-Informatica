#pragma once
#include "domain.h"

class Repo {
private:
    vector<Joc> jocuri;
    string fileName;
    void loadfromfile();
public:
    Repo(string fileName):fileName{fileName}{
        loadfromfile();
    }

    void storetofile();

    void adauga(Joc j);

    vector<Joc> get_all(){
        return jocuri;
    }

    void modifica(int id,int dim,string tabla,char jucator,string stare);
};



