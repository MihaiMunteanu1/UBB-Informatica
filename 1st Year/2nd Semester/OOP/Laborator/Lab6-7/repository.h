#pragma once
#include <utility>
#include <vector>
#include <stdexcept>
#include <cassert>
#include "Activitate.h"
#include "vectordinamic.h"
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

class ActivitateRepo {
private:
    VectorDinamic<Activitate> activitati;
public:

    //ActivitateRepo(const ActivitateRepo& ot) = default;

    //ActivitateRepo()=default;

    void store(const Activitate& m);

    void actualizare(const Activitate& m);

    void stergere(const string& titlu);

    /**
     * Functie care returneaza toate activitatile din lista de activitati.
     * @return
     */
    const VectorDinamic<Activitate>& get_all(){
        return activitati;
    }
};

void testRepo();

void testRepoActualizare();

void testRepoStergere();

void RepoTestAll();
