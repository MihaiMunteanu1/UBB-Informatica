#pragma once
#include <utility>
#include <vector>
#include <stdexcept>
#include <cassert>
#include "Activitate.h"
using std::vector;
using std::exception;
class RepoException : public exception{
    string msg;
public:
    explicit RepoException(string m): msg{std::move(m)}{
    }
    string getMessage(){
        return msg;
    }
};
class AbstractRepo{
public:
    AbstractRepo()=default;

    AbstractRepo(const AbstractRepo& ot)=delete;

    virtual void store(const Activitate& m)=0;

    virtual void stergere(const string& titlu)=0;

    virtual const Activitate& find(const string& titlu)=0;

    virtual vector<Activitate>& get_all()=0;

};
class ActivitateRepo:public AbstractRepo {
private:
    vector<Activitate> activitati;
public:

    //ActivitateRepo(const ActivitateRepo& ot) = default;

    //ActivitateRepo()=default;

    void store(const Activitate& m) override;

    void actualizare(const Activitate& m);

    void stergere(const string& titlu) override;

    const Activitate& find(const string& titlu) override;

    /**
     * Functie care returneaza toate activitatile din lista de activitati.
     * @return
     */
    vector<Activitate>& get_all() override{
        return activitati;
    }

};

class ActivitateRepoFile:public ActivitateRepo{
private:
    string fileName;

    void loadfromfile();

    void storetofile();

public:
     explicit ActivitateRepoFile(string fname): ActivitateRepo(),fileName{fname}{
        loadfromfile();
     };

    void store(const Activitate& m) override{
        ActivitateRepo::store(m);
        storetofile();
    }

    void stergere(const string& titlu) override{
        ActivitateRepo::stergere(titlu);
        storetofile();
    }

};
void testRepo();

void testRepoActualizare();

void testRepoStergere();

void RepoTestAll();

void testFileRepo();