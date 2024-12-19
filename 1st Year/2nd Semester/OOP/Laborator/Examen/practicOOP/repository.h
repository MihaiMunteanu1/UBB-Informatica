#pragma once
#include "domain.h"

class Repo {
private:
    vector<Utilaj> utilaje;
    string fileName;
    void loadfromfile();
public:
    /**
     * Constructor
     * @param fileName
     */
    Repo(string fileName):fileName{fileName}{
        loadfromfile();
    }
    /**
     * Functie care salveaza in fisier datele
     */
    void storetofile();

    /**
     * Functie care sterge un utilaj
     * @param id
     */
    void sterge(int id);

    /**
     * Functie care modifica un utilaj
     * @param u
     */
    void modifica(Utilaj u);

    /**
     * Functie care returneaza toate utilajele
     * @return
     */
    vector<Utilaj> get_all(){
        return utilaje;
    }
};

/**
 * Functie de teste pentru repository
 */
void test_repo();