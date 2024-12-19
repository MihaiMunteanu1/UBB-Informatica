#pragma once
#include "repository.h"
#include "Activitate.h"
#include <string>
using std::string;

class ActivitateService{
private:
    ActivitateRepo repo;
public:
    explicit ActivitateService(ActivitateRepo& r): repo{r}{
    }

    ActivitateService(const ActivitateService& ot) = default;

    ActivitateService()=default;

    void add_activitate(const string& titlu,const string& descriere,const string& tip,int durata);

    void actualizare_activitate(const string& titlu,const string& descriere,const string& tip,int durata);

    void stergere_activitate(const string& titlu);

    /**
     * Functie care returneaza toate activitatile din lista de activitati.
     * @return
     */
    VectorDinamic<Activitate> get_all(){
        return repo.get_all();
    }

    VectorDinamic<Activitate> filtrare_tip(const string& model);

    VectorDinamic<Activitate> filtrare_descriere(const string& descriere);

    VectorDinamic<Activitate> sortare_titlu();

    VectorDinamic<Activitate> sortare_descriere();

    VectorDinamic<Activitate> sortare_tip_durata();

};

void testSortareTipDurata();

void testFiltrareDescriere();

void testValideazaActivitate();

void testAdd();

void testActualizare();

void testAll();

void testSortare();

void testFiltrare();

void testSortareDescriere();