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

    void sterge(int id);

    void update_rank(int id,int rank){
        repo.update_rank(id,rank);
    }

    void update_titlu(int id,string titlu){
        repo.update_titlu(id,titlu);
    }
    int melodii_cu_acelasi_rank(int rank){
        int cont=0;
        for(auto& m:get_all()){
            if(m.get_rank()==rank)
                cont++;
        }
        return cont;
    }
};

void test_service();



