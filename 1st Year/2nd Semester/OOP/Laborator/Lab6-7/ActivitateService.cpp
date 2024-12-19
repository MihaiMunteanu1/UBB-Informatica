#include "ActivitateService.h"

/**
 * Functie care adauga o activitate in lista de activitati.c
 * @param titlu
 * @param descriere
 * @param tip
 * @param durata
 */
void ActivitateService::add_activitate(const string& titlu,const string& descriere,const string& tip,int durata){

    Activitate a{titlu,descriere,tip,durata};
    switch (Activitate::validareActivitate(a)) {
        case 1:
            throw ActivitateException("Titlu invalid!");
        case 2:
            throw ActivitateException("Descriere invalida!");
        case 3:
            throw ActivitateException("Tip invalid!");
        case 4:
            throw ActivitateException("Durata invalida!");
        default:
            try{
                repo.store(a);
            } catch (RepoException& e) {
                throw ActivitateException(e.getMessage());
            }
            break;
    }
}
/**
 * Functie care actualizeaza o activitate din lista de activitati.
 * @param titlu
 * @param descriere
 * @param tip
 * @param durata
 */
void ActivitateService::actualizare_activitate(const std::string &titlu, const std::string &descriere,const std::string &tip, int durata) {
    Activitate a{titlu,descriere,tip,durata};
    switch (Activitate::validareActivitate(a)) {
        case 1:
            throw ActivitateException("Titlu invalid!");
        case 2:
            throw ActivitateException("Descriere invalida!");
        case 3:
            throw ActivitateException("Tip invalid!");
        case 4:
            throw ActivitateException("Durata invalida!");
        default:
            try{
                repo.actualizare(a);
            }catch (RepoException& e) {
                throw ActivitateException(e.getMessage());
            }
            break;
    }
}
/**
 * Functie care sterge o activitate din lista de activitati.
 * @param titlu
 */
void ActivitateService::stergere_activitate(const std::string &titlu){
    try {
        repo.stergere(titlu);
    } catch (RepoException& e) {
        throw ActivitateException(e.getMessage());
    }
}
/**
 * Functie care filtreaza toate activitatile in functie de tip
 * @param tip
 * @return
 */
VectorDinamic<Activitate> ActivitateService::filtrare_tip(const string& tip) {
    VectorDinamic<Activitate> activitati;
    for (int i=0;i<repo.get_all().size();i++){
        if (repo.get_all().get(i).get_tip() == tip){
            activitati.add(repo.get_all().get(i));
        }
    }
    return activitati;
}
/**
 * Functie care filtreaza toate activitatile in functie de descriere
 * @param descriere
 * @return
 */
VectorDinamic<Activitate>ActivitateService::filtrare_descriere(const string &descriere) {
    VectorDinamic<Activitate> activitati;
    for (int i=0;i<repo.get_all().size();i++){
        if (repo.get_all().get(i).get_descriere() == descriere){
            activitati.add(repo.get_all().get(i));
        }
    }
    return activitati;
}
/**
 * Functie care sorteaza activitatile crescator in functie de titlu
 * @return
 */
VectorDinamic<Activitate>ActivitateService:: sortare_titlu() {
    VectorDinamic<Activitate> activitati_sortate=repo.get_all();
    for(int i=0;i<activitati_sortate.size();i++){
        for(int j=i+1;j<activitati_sortate.size();j++){
            if(activitati_sortate.get(i).get_titlu()>activitati_sortate.get(j).get_titlu()){
                std::swap(activitati_sortate.get(i),activitati_sortate.get(j));
            }
        }
    }
    return activitati_sortate;
}
/**
 * Functie care sorteaza activitatile crescator in functie de descriere
 * @return
 */
VectorDinamic<Activitate>ActivitateService:: sortare_descriere() {
    VectorDinamic<Activitate> activitati_sortate=repo.get_all();
    for(int i=0;i<activitati_sortate.size();i++){
        for(int j=i+1;j<activitati_sortate.size();j++){
            if(activitati_sortate.get(i).get_descriere()>activitati_sortate.get(j).get_descriere()){
                std::swap(activitati_sortate.get(i),activitati_sortate.get(j));
            }
        }
    }
    return activitati_sortate;
}
/**
 * Functie care sorteaza activitatile crescator in functie de tip si durata
 * @return
 */
VectorDinamic<Activitate>ActivitateService:: sortare_tip_durata(){
    VectorDinamic<Activitate> activitati_sortate=repo.get_all();
    for(int i=0;i<activitati_sortate.size();i++){
        for(int j=i+1;j<activitati_sortate.size();j++){
            if(activitati_sortate.get(i).get_tip()>activitati_sortate.get(j).get_tip())
            {
                std::swap(activitati_sortate.get(i),activitati_sortate.get(j));
            }
            else if(activitati_sortate.get(i).get_tip()==activitati_sortate.get(j).get_tip() && activitati_sortate.get(i).get_durata()>activitati_sortate.get(j).get_durata()){
                std::swap(activitati_sortate.get(i),activitati_sortate.get(j));
            }
        }
    }
    return activitati_sortate;
}

void testAdd(){
    ActivitateRepo repo;
    ActivitateService service(repo);
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
    } catch(ActivitateException & except) {
        assert(except.get_msg() == "Activitatea exista deja!\n");
    }
    titlu = "";
    try {
        service.add_activitate(titlu, descriere, tip, durata);
    } catch(ActivitateException & except) {
        assert(except.get_msg() == "Titlu invalid!");
    }
    titlu = "Baschet";
    descriere = "";
    try {
        service.add_activitate(titlu, descriere, tip, durata);
    } catch(ActivitateException & except) {
        assert(except.get_msg() == "Descriere invalida!");
    }
    descriere = "Dribbling";
    tip = "";
    try {
        service.add_activitate(titlu, descriere, tip, durata);
    } catch(ActivitateException & except) {
        assert(except.get_msg() == "Tip invalid!");
    }
    tip = "miscare";
    durata = -2;
    try {
        service.add_activitate(titlu, descriere, tip, durata);
    } catch(ActivitateException & except) {
        assert(except.get_msg() == "Durata invalida!");
    }
}
void testActualizare(){
    ActivitateRepo repo;
    ActivitateService service(repo);
    string titlu = "Baschet";
    string descriere = "Dribbling";
    string tip = "miscare";
    int durata = 2;
    service.add_activitate(titlu, descriere, tip, durata);
    descriere = "Pase";
    service.actualizare_activitate(titlu, descriere, tip, durata);
    assert(service.get_all().get(0).get_descriere() == "Pase");
    descriere = "Dribbling";
    tip = "miscare";
    service.actualizare_activitate(titlu, descriere, tip, durata);
    titlu = "Fotbal";
    try {
        service.actualizare_activitate(titlu, descriere, tip, durata);
    } catch(ActivitateException & except) {
        assert(except.get_msg() == "Activitatea nu exista!\n");
    }
    titlu = "";
    try {
        service.actualizare_activitate(titlu, descriere, tip, durata);
    } catch(ActivitateException & except) {
        assert(except.get_msg() == "Titlu invalid!");
    }
    titlu = "Baschet";
    descriere = "";
    try {
        service.actualizare_activitate(titlu, descriere, tip, durata);
    } catch(ActivitateException & except) {
        assert(except.get_msg() == "Descriere invalida!");
    }
    descriere = "Dribbling";
    tip = "";
    try {
        service.actualizare_activitate(titlu, descriere, tip, durata);
    } catch(ActivitateException & except) {
        assert(except.get_msg() == "Tip invalid!");
    }
    tip = "miscare";
    durata = -2;
    try {
        service.actualizare_activitate(titlu, descriere, tip, durata);
    } catch(ActivitateException & except) {
        assert(except.get_msg() == "Durata invalida!");
    }
}

void testStergere(){
    ActivitateRepo repo;
    ActivitateService service(repo);
    string titlu = "Baschet";
    string descriere = "Dribbling";
    string tip = "miscare";
    int durata = 2;
    service.add_activitate(titlu, descriere, tip, durata);
    service.stergere_activitate(titlu);
    assert(service.get_all().size() == 0);
    try {
        service.stergere_activitate(titlu);
    } catch(ActivitateException & except) {
        assert(except.get_msg() == "Activitatea nu exista!\n");
    }
}

void testSortare(){
    ActivitateRepo repo;
    ActivitateService serv{repo};
    serv.add_activitate("Baschet", "Dribbling", "miscare",2);
    serv.add_activitate("Volei", "Pase", "miscare",2);
    serv.add_activitate("Fotbal", "Serva", "miscare",2);
    auto activitati = serv.sortare_titlu();
    assert(activitati.size() == 3);
    assert(activitati.get(0).get_titlu() == "Baschet");
    assert(activitati.get(1).get_titlu() == "Fotbal");
    assert(activitati.get(2).get_titlu() == "Volei");
}

void testFiltrare(){
    ActivitateRepo repo;
    ActivitateService serv{repo};
    serv.add_activitate("Baschet", "Dribbling", "miscare",2);
    serv.add_activitate("Fotbal", "Pase", "alergare",2);
    serv.add_activitate("Volei", "Serva", "miscare",2);
    auto activitati = serv.filtrare_tip("miscare");
    assert(activitati.size() == 2);
    activitati = serv.filtrare_tip("alergare");
    assert(activitati.size() == 1);
    activitati = serv.filtrare_tip("inot");
    assert(activitati.size() == 0);

}
void testValideazaActivitate(){
    Activitate a{"Baschet", "Dribbling", "miscare",2};
    assert(Activitate::validareActivitate(a) == 0);
    a = Activitate{"", "Dribbling", "miscare",2};
    assert(Activitate::validareActivitate(a) == 1);
    a = Activitate{"Baschet", "", "miscare",2};
    assert(Activitate::validareActivitate(a) == 2);
    a = Activitate{"Baschet", "Dribbling", "",2};
    assert(Activitate::validareActivitate(a) == 3);
    a = Activitate{"Baschet", "Dribbling", "miscare",-2};
    assert(Activitate::validareActivitate(a) == 4);
}
void testFiltrareDescriere(){
    ActivitateRepo repo;
    ActivitateService serv{repo};
    serv.add_activitate("Baschet", "Dribbling", "miscare",2);
    serv.add_activitate("Fotbal", "Pase", "alergare",2);
    serv.add_activitate("Volei", "Serva", "miscare",2);
    auto activitati = serv.filtrare_descriere("Dribbling");
    assert(activitati.size() == 1);
}
void testSortareDescriere(){
    ActivitateRepo repo;
    ActivitateService serv{repo};
    serv.add_activitate("Baschet", "Dribbling", "miscare",2);
    serv.add_activitate("Volei", "Serva", "miscare",2);
    serv.add_activitate("Fotbal", "Pase", "miscare",2);
    auto activitati = serv.sortare_descriere();
    assert(activitati.size() == 3);
    assert(activitati.get(0).get_descriere() == "Dribbling");
    assert(activitati.get(1).get_descriere() == "Pase");
    assert(activitati.get(2).get_descriere() == "Serva");
}
void testSortareTipDurata() {
    ActivitateRepo repo;
    ActivitateService serv{repo};
    serv.add_activitate("Baschet", "Dribbling", "miscare", 3);
    serv.add_activitate("Volei", "Serva", "alergare", 1);
    serv.add_activitate("Fotbal", "Pase", "miscare", 1);
    auto activitati = serv.sortare_tip_durata();
    assert(activitati.size() == 3);
    assert(activitati.get(0).get_tip() == "alergare");
    assert(activitati.get(1).get_tip() == "miscare");
    assert(activitati.get(2).get_tip() == "miscare");
    assert(activitati.get(0).get_durata() == 1);
    assert(activitati.get(1).get_durata() == 1);
    assert(activitati.get(2).get_durata() == 3);
}
void testAll()
{
    testSortareTipDurata();
    testSortareDescriere();
    testFiltrareDescriere();
    testValideazaActivitate();
    testFiltrare();
    testSortare();
    RepoTestAll();
    testAdd();
    testActualizare();
    testStergere();
}