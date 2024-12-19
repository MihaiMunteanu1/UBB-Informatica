#include "repository.h"
/**
 * Adauga o activitate in lista de activitati
 * @param a
 */
void ActivitateRepo::store(const Activitate& a){
    for (const Activitate& A: activitati) {
        if (A.get_titlu()==a.get_titlu()) {
            throw RepoException("Activitatea exista deja!\n");
        }
    }
    activitati.add(a);
}
/**
 * Actualizeaza o activitate din lista de activitati
 * @param a
 */
void ActivitateRepo::actualizare(const Activitate& a){
    for (auto& A: activitati) {
        if (A.get_titlu()==a.get_titlu()) {
            A = a;
            return;
        }
    }
    throw RepoException("Activitatea nu exista!\n");
}
/**
 * Sterge o activitate din lista de activitati
 * @param numar_inmatriculare
 */
void ActivitateRepo::stergere(const string& titlu){
    for (int i=0;i<activitati.size();i++){
        if (activitati.get(i).get_titlu() == titlu){
            activitati.sterge(i);
            return;
        }
    }
    throw RepoException("Activitatea nu exista!\n");
}


void testRepo(){
    ActivitateRepo repo;
    Activitate a1("Baschet", "Dribbling", "miscare",2);
    repo.store(a1);
    const auto& activitati = repo.get_all();
    assert(activitati.size() == 1);
    assert(activitati.get(0).get_titlu() == "Baschet");
    assert(activitati.get(0).get_descriere() == "Dribbling");
    assert(activitati.get(0).get_tip() == "miscare");
    assert(activitati.get(0).get_durata() == 2);
    assert(activitati.size()==1);
    try {
        repo.store(a1);
    } catch (RepoException& e) {
        assert(e.getMessage() == "Activitatea exista deja!\n");
    }
}

void testRepoActualizare(){
    ActivitateRepo repo;
    Activitate a1("Baschet", "Dribbling", "miscare",2);
    repo.store(a1);
    repo.actualizare(a1);
    const auto& activitati = repo.get_all();
    assert(activitati.size() == 1);
    assert(activitati.get(0).get_titlu() == "Baschet");
    assert(activitati.get(0).get_descriere() == "Dribbling");
    assert(activitati.get(0).get_tip() == "miscare");
    assert(activitati.get(0).get_durata() == 2);
}

void testRepoStergere(){
    ActivitateRepo repo;
    Activitate a1("Baschet", "Dribbling", "miscare",2);
    repo.store(a1);
    repo.stergere("Baschet");
    const auto& activitati = repo.get_all();
    assert(activitati.size()==0);
    try {
        repo.stergere("Baschet");
    } catch (RepoException& e) {
        assert(e.getMessage() == "Activitatea nu exista!\n");
    }
}
void RepoTestAll(){
    testRepo();
    testRepoActualizare();
    testRepoStergere();
}