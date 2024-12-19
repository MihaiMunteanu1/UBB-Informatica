#pragma once
#include "domain.h"

class Repo {
private:
    vector<Melodie> melodii;
    string fileName;
public:
    Repo(string fileName):fileName{fileName}{
        loadfromfile();
    }
    void loadfromfile();

    void storetofile();

    vector<Melodie> get_all(){
        return melodii;
    }

    void update_titlu(int id,string titlu);

    void update_rank(int id,int rank);

    void sterge(int id);

};


void test_repo();
