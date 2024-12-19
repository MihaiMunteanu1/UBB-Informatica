#pragma once
#include "repository.h"

class Service {
private:
    Repo& repo;
public:
    /**
     *  Constructor
     * @param repo
     */
    Service(Repo& repo):repo{repo}{}

    /**
     * Functie care returneaza toate utilajele sortate dupa tip sau denumire
     * @return
     */
    vector<Utilaj> get_all(){
        return sortare(repo.get_all());
    }
    /**
     * Functie care sorteaza utilajele
     * @param v
     * @return
     */
    vector<Utilaj> sortare(vector<Utilaj> v);

    /**
     * Functie care sterge un utilaj
     * @param id
     */
    void sterge(int id);

    /**
     * Functie care modifica un utilaj, verificand daca datele sunt valide
     * @param id
     * @param denumire
     * @param tip
     * @param cilindrii
     */
    void modifica(int id,string denumire,string tip,int cilindrii);

    /**
     * Functie care returneaza nr utilajelor cu acelasi tip ca un tip dat
     * @param tip
     * @return
     */
    int nr_utilaje_tip(string tip);

    /**
     * Functie care returneaza nr utilajelor cu acelasi nr de cilindrii ca un nr de cilindrii dat
     * @param tip
     * @return
     */
    int nr_utilaje_cilindrii(int nrC);
};

/**
 * Functie de test pentru service
 */
void test_service();

