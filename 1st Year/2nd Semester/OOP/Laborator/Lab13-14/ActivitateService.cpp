#include <random>
#include <algorithm>
#include "ActivitateService.h"
#include <unordered_map>
#include <fstream>
#include <memory>
#include "Undo2.h"
#include "export.h"

std::mt19937 mt{ std::random_device{}() };

Activitate ActivitateService::find(const string& titlu){
    return repo.find(titlu);
}
void ActivitateService::undo() {
    if (undoActions.empty()) {
        throw ActivitateException("Nu mai exista actiuni de undo!\n");
    }
    undoActions.back()->doUndo();
    undoActions.pop_back();
}

void ActivitateService::afisare_dictionar(std::unordered_map<std::string, int>& dictionar) {
    for (const auto& activitate : repo.get_all()) {
        dictionar[activitate.get_tip()]++;
    }
}
/**
 * Functie care adauga o activitate in lista de activitati.c
 * @param titlu
 * @param descriere
 * @param tip
 * @param durata
 */
void ActivitateService::add_activitate(const string& titlu, const string& descriere, const string& tip, int durata) {

    Activitate a{ titlu,descriere,tip,durata };
    val.validareActivitate(a);
    repo.store(a);
    undoActions.push_back(std::make_unique<UndoAdauga>(repo, a));
}
/**
 * Functie care actualizeaza o activitate din lista de activitati.
 * @param titlu
 * @param descriere
 * @param tip
 * @param durata
 */
void ActivitateService::actualizare_activitate(const std::string& titlu, const std::string& descriere, const std::string& tip, int durata) {
    /*Activitate a{titlu,descriere,tip,durata};
    val.validareActivitate(a);
    const auto& activitate_veche=repo.find(titlu);
    repo.actualizare(a);
    undoActions.push_back(std::make_unique<UndoModifica>(repo,activitate_veche));*/
    Activitate a{ titlu,descriere,tip,durata };
    val.validareActivitate(a);
    Activitate veche = repo.find(titlu);
    repo.stergere(veche.get_titlu());
    repo.store(a);
    undoActions.push_back(std::make_unique<UndoModifica>(repo, a, veche));
}
/**
 * Functie care sterge o activitate din lista de activitati.
 * @param titlu
 */
void ActivitateService::stergere_activitate(const std::string& titlu) {
    try {
        const Activitate& activitate_stearsa = repo.find(titlu);
        repo.stergere(titlu);
        undoActions.push_back(std::make_unique<UndoSterge>(repo, activitate_stearsa));
    }
    catch (RepoException& e) {
        throw ActivitateException(e.getMessage());
    }
}
/**
 * Functie care filtreaza toate activitatile in functie de tip
 * @param tip
 * @return
 */
vector<Activitate> ActivitateService::filtrare_tip(const string& tip) {
    vector<Activitate> rez;
    std::copy_if(repo.get_all().begin(), repo.get_all().end(), std::back_inserter(rez), [tip](const Activitate& a) { return a.get_tip() == tip; });
    /*for (const auto & i : repo.get_all())
        if (i.get_tip() == tip) {
            activitati.push_back(i);
        }*/
    return rez;
}
vector<Activitate> ActivitateService::filtrare_titlu(const string& titlu) {
    vector<Activitate> rez;
    std::copy_if(repo.get_all().begin(), repo.get_all().end(), std::back_inserter(rez), [titlu](const Activitate& a) { return a.get_titlu() == titlu; });

    return rez;
}
vector<Activitate> ActivitateService::filtrare_durata(int durata) {
    vector<Activitate> rez;
    std::copy_if(repo.get_all().begin(), repo.get_all().end(), std::back_inserter(rez), [durata](const Activitate& a) { return a.get_durata() == durata; });

    return rez;
}
/**
 * Functie care filtreaza toate activitatile in functie de descriere
 * @param descriere
 * @return
 */
vector<Activitate>ActivitateService::filtrare_descriere(const string& descriere) {
    vector<Activitate> rez;
    std::copy_if(repo.get_all().begin(), repo.get_all().end(), std::back_inserter(rez), [descriere](const Activitate& a) { return a.get_descriere() == descriere; });
    /*for (const auto & i : repo.get_all()){
        if (i.get_descriere() == descriere){
            activitati.push_back(i);
        }
    }*/
    return rez;
}
vector<Activitate>ActivitateService::sortare(Sort functie_sortare) {
    vector<Activitate> activitati_sortate = repo.get_all();
    std::sort(activitati_sortate.begin(), activitati_sortate.end(), functie_sortare);
    /*for(int i=0;i<activitati_sortate.size();i++){
        for(int j=i+1;j<activitati_sortate.size();j++){
            if(functie_sortare(activitati_sortate[i],activitati_sortate[j])>0){
                std::swap(activitati_sortate[i],activitati_sortate[j]);
            }
        }
    }*/
    return activitati_sortate;
}
int sortare_titlu(const Activitate& a, const Activitate& b) {
    return a.get_titlu() < b.get_titlu();
}
int sortare_descriere(const Activitate& a, const Activitate& b) {
    return a.get_descriere() < b.get_descriere();
}
int sortare_tip_durata(const Activitate& a, const Activitate& b) {
    if (a.get_tip() < b.get_tip()) {
        return 1;
    }
    if (a.get_tip() == b.get_tip() && a.get_durata() < b.get_durata())
        return 1;
    return 0;
}
int sortare_durata(const Activitate& a1, const Activitate& a2) {
    return a1.get_durata() < a2.get_durata();
}

void ActivitateService::clearAllListaActivitati() {
    lista_activitati_curenta.clearAllListaActivitati();
    notify();
}

void ActivitateService::add_to_lista_activitati(const std::string& titlu) {
    const auto& activitati = repo.find(titlu);
    lista_activitati_curenta.adaugaListaActivitati(activitati);
}

int ActivitateService::addRandomToListaActivitati(int howMany) {
    vector<Activitate> originalActivitati = repo.get_all();
    lista_activitati_curenta.addRandomActivitati(originalActivitati, howMany);
    notify();
    return lista_activitati_curenta.getAllListaActivitati().size();
}

void ActivitateService::exporttofileHTML(const std::string& filename) {
    exportToHTML(filename, lista_activitati_curenta.getAllListaActivitati());
}
void ActivitateService::exporttofileCVS(const std::string& filename) {
    exportToCVS(filename, lista_activitati_curenta.getAllListaActivitati());

}
void test_export() {
    ActivitateRepo repo;
    ValidatorActivitate val;
    ActivitateService serv{ repo,val };
    serv.add_activitate("Baschet", "Dribbling", "miscare", 2);
    serv.add_activitate("Fotbal", "Pase", "alergare", 2);
    serv.add_activitate("Volei", "Serva", "miscare", 2);
    serv.addRandomToListaActivitati(3);
    serv.exporttofileCVS("testExport.cvs");
    std::ifstream fin("testExport.cvs");
    assert(fin.is_open());
    int countLines = 0;
    while (!fin.eof()) {
        std::string line;
        std::getline(fin, line);
        countLines++;
    }
    fin.close();
    assert(countLines == 4);
    serv.exporttofileHTML("testExport.html");
    fin.open("testExport.html");
    assert(fin.is_open());
    try {
        serv.exporttofileCVS("test/Export.cvs");
    }
    catch (ActivitateException) {
        assert(true);
    }
    try {
        serv.exporttofileHTML("a/b/c/Export.html");
    }
    catch (ActivitateException) {
        assert(true);
    }

}
void test_undo() {
    ActivitateRepo repo;
    ValidatorActivitate val;
    ActivitateService serv{ repo,val };
    serv.add_activitate("Baschet", "Dribbling", "miscare", 2);
    serv.add_activitate("Fotbal", "Pase", "alergare", 2);
    serv.add_activitate("Volei", "Serva", "miscare", 2);
    serv.undo();
    assert(serv.get_all().size() == 2);
    serv.undo();
    serv.undo();
    assert(serv.get_all().empty());
    try {
        serv.undo();
    }
    catch (ActivitateException& except) {
        assert(except.get_msg() == "Nu mai exista actiuni de undo!\n");
    }
    serv.add_activitate("Baschet", "Dribbling", "miscare", 2);
    serv.actualizare_activitate("Baschet", "Pase", "miscare", 2);
    serv.undo();
    assert(serv.get_all()[0].get_descriere() == "Dribbling");
    serv.stergere_activitate("Baschet");
    serv.undo();
    assert(serv.get_all().size() == 1);
}
void testListaActivitatiService() {
    ActivitateRepo repo;
    ValidatorActivitate val;
    ActivitateService serv{ repo,val };
    serv.add_activitate("Baschet", "Dribbling", "miscare", 2);
    serv.add_activitate("Fotbal", "Pase", "alergare", 2);
    serv.add_activitate("Volei", "Serva", "miscare", 2);
    serv.add_to_lista_activitati("Baschet");
    serv.add_to_lista_activitati("Fotbal");
    serv.add_to_lista_activitati("Volei");
    assert(serv.getAllListaActivitai().size() == 3);
    serv.clearAllListaActivitati();
    assert(serv.getAllListaActivitai().empty());
    serv.addRandomToListaActivitati(2);
    assert(serv.getAllListaActivitai().size() == 2);
}

void testDictionar() {
    ActivitateRepo repo;
    ValidatorActivitate val;
    ActivitateService service{ repo,val };
    service.add_activitate("Baschet", "Dribbling", "miscare", 2);
    service.add_activitate("Fotbal", "Pase", "alergare", 2);
    service.add_activitate("Volei", "Serva", "miscare", 2);
    std::unordered_map<std::string, int> dictionar;
    service.afisare_dictionar(dictionar);
    assert(dictionar["miscare"] == 2);
    assert(dictionar["alergare"] == 1);

}

void testAdd() {
    ActivitateRepo repo;
    ValidatorActivitate val;
    ActivitateService service{ repo,val };
    string titlu = "Baschet";
    string descriere = "Dribbling";
    string tip = "miscare";
    int durata = 2;
    service.add_activitate(titlu, descriere, tip, durata);
    assert(service.get_all().size() == 1);
    titlu = "Fotbal";
    service.add_activitate(titlu, descriere, tip, durata);
    assert(service.get_all().size() == 2);
    try {
        service.add_activitate(titlu, descriere, tip, durata);
    }
    catch (RepoException& except) {
        assert(except.getMessage() == "Activitatea exista deja!\n");
    }
    titlu = "";
    try {
        service.add_activitate(titlu, descriere, tip, durata);
    }
    catch (ValidatorException& except) {
        assert(except.get_msg() == "Titlul nu poate fi vid!\n");
    }
    titlu = "Baschet";
    descriere = "";
    try {
        service.add_activitate(titlu, descriere, tip, durata);
    }
    catch (ValidatorException& except) {
        assert(except.get_msg() == "Descrierea nu poate fi vida!\n");
    }
    descriere = "Dribbling";
    tip = "";
    try {
        service.add_activitate(titlu, descriere, tip, durata);
    }
    catch (ValidatorException& except) {
        assert(except.get_msg() == "Tipul nu poate fi vid!\n");
    }
    tip = "miscare";
    durata = -2;
    try {
        service.add_activitate(titlu, descriere, tip, durata);
    }
    catch (ValidatorException& except) {
        assert(except.get_msg() == "Durata trebuie sa fie un numar pozitiv!\n");
    }
}
void testActualizare() {
    ActivitateRepo repo;
    ValidatorActivitate val;
    ActivitateService service{ repo,val };
    string titlu = "Baschet";
    string descriere = "Dribbling";
    string tip = "miscare";
    int durata = 2;
    service.add_activitate(titlu, descriere, tip, durata);
    descriere = "Pase";
    service.actualizare_activitate(titlu, descriere, tip, durata);
    assert(service.get_all()[0].get_descriere() == "Pase");
    descriere = "Dribbling";
    tip = "miscare";
    service.actualizare_activitate(titlu, descriere, tip, durata);
    titlu = "Fotbal";
    try {
        service.actualizare_activitate(titlu, descriere, tip, durata);
    }
    catch (RepoException& except) {
        assert(except.getMessage() == "Activitatea nu exista!\n");
    }
    titlu = "";
    try {
        service.actualizare_activitate(titlu, descriere, tip, durata);
    }
    catch (ValidatorException& except) {
        assert(except.get_msg() == "Titlul nu poate fi vid!\n");
    }
    titlu = "Baschet";
    descriere = "";
    try {
        service.actualizare_activitate(titlu, descriere, tip, durata);
    }
    catch (ValidatorException& except) {
        assert(except.get_msg() == "Descrierea nu poate fi vida!\n");
    }
    descriere = "Dribbling";
    tip = "";
    try {
        service.actualizare_activitate(titlu, descriere, tip, durata);
    }
    catch (ValidatorException& except) {
        assert(except.get_msg() == "Tipul nu poate fi vid!\n");
    }
    tip = "miscare";
    durata = -2;
    try {
        service.actualizare_activitate(titlu, descriere, tip, durata);
    }
    catch (ValidatorException& except) {
        assert(except.get_msg() == "Durata trebuie sa fie un numar pozitiv!\n");
    }
}

void testStergere() {
    ActivitateRepo repo;
    ValidatorActivitate val;
    ActivitateService service{ repo,val };
    string titlu = "Baschet";
    string descriere = "Dribbling";
    string tip = "miscare";
    int durata = 2;
    service.add_activitate(titlu, descriere, tip, durata);
    auto a=service.find(titlu);
    assert(a.get_tip()=="miscare");
    service.stergere_activitate(titlu);
    assert(service.get_all().empty());
    try {
        service.stergere_activitate(titlu);
    }
    catch (ActivitateException& except) {
        assert(except.get_msg() == "Activitatea nu exista!\n");
    }
}

void testSortare() {
    ActivitateRepo repo;
    ValidatorActivitate val;
    ActivitateService serv{ repo,val };
    serv.add_activitate("Baschet", "Dribbling", "miscare", 2);
    serv.add_activitate("Fotbal", "Pase", "alergare", 2);
    serv.add_activitate("Volei", "Serva", "miscare", 2);
    auto activitati = serv.sortare(sortare_titlu);
    assert(activitati.size() == 3);
    assert(activitati[0].get_titlu() == "Baschet");
    assert(activitati[1].get_titlu() == "Fotbal");
    assert(activitati[2].get_titlu() == "Volei");
    activitati = serv.sortare(sortare_descriere);
    assert(activitati.size() == 3);
    assert(activitati[0].get_descriere() == "Dribbling");
    assert(activitati[1].get_descriere() == "Pase");
    assert(activitati[2].get_descriere() == "Serva");
    activitati = serv.sortare(sortare_tip_durata);
    assert(activitati.size() == 3);
    assert(activitati[0].get_tip() == "alergare");
    assert(activitati[1].get_tip() == "miscare");
    assert(activitati[2].get_tip() == "miscare");
    assert(activitati[0].get_durata() == 2);
    assert(activitati[1].get_durata() == 2);
    assert(activitati[2].get_durata() == 2);
    serv.add_activitate("Tenis", "Serva", "miscare", 1);
    activitati = serv.sortare(sortare_tip_durata);
    assert(activitati.size() == 4);
    assert(activitati[0].get_tip() == "alergare");
    assert(activitati[1].get_tip() == "miscare");
    assert(activitati[2].get_tip() == "miscare");
    assert(activitati[3].get_tip() == "miscare");
}

void testFiltrare() {
    ActivitateRepo repo;
    ValidatorActivitate val;
    ActivitateService serv{ repo,val };
    serv.add_activitate("Baschet", "Dribbling", "miscare", 2);
    serv.add_activitate("Fotbal", "Pase", "alergare", 2);
    serv.add_activitate("Volei", "Serva", "miscare", 2);
    auto activitati = serv.filtrare_tip("miscare");
    assert(activitati.size() == 2);
    activitati = serv.filtrare_tip("alergare");
    assert(activitati.size() == 1);
    activitati = serv.filtrare_tip("inot");
    assert(activitati.empty());

}
void testFiltrareDescriere() {
    ActivitateRepo repo;
    ValidatorActivitate val;
    ActivitateService serv{ repo,val };
    serv.add_activitate("Baschet", "Dribbling", "miscare", 2);
    serv.add_activitate("Fotbal", "Pase", "alergare", 2);
    serv.add_activitate("Volei", "Serva", "miscare", 2);
    auto activitati = serv.filtrare_descriere("Dribbling");
    assert(activitati.size() == 1);
}
void testFiltrareTitlu(){
    ActivitateRepo repo;
    ValidatorActivitate val;
    ActivitateService serv{ repo,val };
    serv.add_activitate("Baschet", "Dribbling", "miscare", 2);
    serv.add_activitate("Fotbal", "Pase", "alergare", 2);
    serv.add_activitate("Volei", "Serva", "miscare", 2);
    auto activitati = serv.filtrare_titlu("Baschet");
    assert(activitati.size() == 1);
}
void testFiltrareDurata(){
    ActivitateRepo repo;
    ValidatorActivitate val;
    ActivitateService serv{ repo,val };
    serv.add_activitate("Baschet", "Dribbling", "miscare", 2);
    serv.add_activitate("Fotbal", "Pase", "alergare", 2);
    serv.add_activitate("Volei", "Serva", "miscare", 2);
    auto activitati = serv.filtrare_durata(2);
    assert(activitati.size() == 3);

}
void testSortareDurata(){
    ActivitateRepo repo;
    ValidatorActivitate val;
    ActivitateService serv{ repo,val };
    serv.add_activitate("Baschet", "Dribbling", "miscare", 2);
    serv.add_activitate("Fotbal", "Pase", "alergare", 2);
    serv.add_activitate("Tenis", "Serva", "miscare", 1);
    auto activitati = serv.sortare(sortare_durata);
    assert(activitati.size() == 3);
    assert(activitati[0].get_titlu() == "Tenis");
    assert(activitati[1].get_titlu() == "Baschet");
    assert(activitati[2].get_titlu() == "Fotbal");

}
void testAll()
{
    testSortareDurata();
    testFiltrareDurata();
    testFiltrareTitlu();
    test_undo();
    test_export();
    testListaActivitatiService();
    testListaActivitati();
    testDictionar();
    testFiltrareDescriere();
    testFiltrare();
    testSortare();
    RepoTestAll();
    testAdd();
    testActualizare();
    testStergere();
}