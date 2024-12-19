#pragma once
#include "repository.h"
#include "Activitate.h"
#include <string>
#include <unordered_map>
#include "ListaActivitati.h"
#include "validators.h"
#include "Undo2.h"
#include <memory>
using std::string;
using std::unique_ptr;
typedef int(*Sort)(const Activitate&, const Activitate&);

class ActivitateService{
private:
    AbstractRepo& repo;
    ListaActivitati lista_activitati_curenta;
    ValidatorActivitate& val;
    std::vector<unique_ptr<ActiuneUndo>> undoActions;
public:

    ActivitateService(AbstractRepo& r,ValidatorActivitate& val): repo{r}, val{val}{};

    ActivitateService(const ActivitateService& ot) = default;

    ActivitateService()=default;

    void add_activitate(const string& titlu,const string& descriere,const string& tip,int durata);

    void actualizare_activitate(const string& titlu,const string& descriere,const string& tip,int durata);

    void stergere_activitate(const string& titlu);

    /**
     * Functie care returneaza toate activitatile din lista de activitati.
     * @return
     */
    vector<Activitate> get_all(){
        return repo.get_all();
    }

    vector<Activitate> filtrare_tip(const string& model);

    vector<Activitate> filtrare_descriere(const string& descriere);

    vector<Activitate> sortare(Sort functie_sortare);

    const vector<Activitate>& getAllListaActivitai(){
        return lista_activitati_curenta.getAllListaActivitati();
    }

    void add_to_lista_activitati(const string& titlu);

    void clearAllListaActivitati();

    int addRandomToListaActivitati(int howMany);

    void afisare_dictionar(std::unordered_map<std::string, int>& dictionar);

    void undo();

    void exporttofileHTML(const string& filename);

    void exporttofileCVS(const string& filename);
};

void testDictionar();

int sortare_titlu(const Activitate& a1, const Activitate& a2);

int  sortare_descriere(const Activitate& a1, const Activitate& a2);

int sortare_tip_durata(const Activitate& a1, const Activitate& a2);

void testFiltrareDescriere();

void testAdd();

void testActualizare();

void testAll();

void testSortare();

void testFiltrare();

void testListaActivitatiService();

void test_export();

void testStergere();

void test_undo();