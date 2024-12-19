#include "repository.h"
#include <fstream>
#include <algorithm>

using std::ifstream;
using std::ofstream;
/**
 * Adauga o activitate in lista de activitati
 * @param a
 */
void ActivitateRepo::store(const Activitate& a) {
    for (const Activitate& A : activitati) {
        if (A.get_titlu() == a.get_titlu()) {
            throw RepoException("Activitatea exista deja!\n");
        }
    }
    activitati.push_back(a);
}
/**
 * Actualizeaza o activitate din lista de activitati
 * @param a
 */
void ActivitateRepo::actualizare(const Activitate& a) {
    for (auto& A : activitati) {
        if (A.get_titlu() == a.get_titlu()) {
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
void ActivitateRepo::stergere(const string& titlu) {
    try {
        find(titlu);
        auto new_end = std::remove_if(activitati.begin(), activitati.end(), [titlu](const Activitate& a) {
            return a.get_titlu() == titlu;
        });
        activitati.erase(new_end, activitati.end());
    }
    catch (RepoException) {
        throw RepoException("Activitatea nu exista!\n");
    }
}

const Activitate& ActivitateRepo::find(const string& titlu) {
    for (const Activitate& A : activitati) {
        if (A.get_titlu() == titlu) {
            return A;
        }
    }
    throw RepoException("Activitatea nu exista!\n");
}


void ActivitateRepoFile::loadfromfile() {
    ifstream f(fileName);
    if (!f.is_open()) {
        throw RepoException("Fisierul nu exista!\n");
    }
    string titlu, descriere, tip, durata;
    while (f >> titlu >> descriere >> tip >> durata) {
        Activitate a(titlu, descriere, tip, stoi(durata));
        ActivitateRepo::store(a);
    }
    f.close();
}

void ActivitateRepoFile::storetofile() {
    ofstream f(fileName);
    //if (!f.is_open()){
    //throw RepoException("Fisierul nu exista!\n");
    // }
    for (const auto& a : get_all()) {
        f << a.get_titlu() << " " << a.get_descriere() << " " << a.get_tip() << " " << a.get_durata() << "\n";
    }
    f.close();
}

void testFileRepo() {
    ofstream f;
    f.open("test.txt", std::ofstream::out | std::ofstream::trunc);
    f << "Baschet Dribbling miscare 2\n";
    f << "Fotbal Pase miscare 3\n";
    f << "Tenis Servire miscare 1\n";
    f.close();

    try {
        ActivitateRepoFile repo{ "test2.txt" };
        //assert(false);
    }
    catch (RepoException&) {
        assert(true);
    }
    ActivitateRepoFile repo{ "test.txt" };
    assert(repo.get_all().size() == 3);

    auto foundActivitate = repo.find("Baschet");
    assert(foundActivitate.get_titlu() == "Baschet");
    assert(foundActivitate.get_descriere() == "Dribbling");
    assert(foundActivitate.get_tip() == "miscare");
    assert(foundActivitate.get_durata() == 2);

    Activitate a1("Volei", "Servire", "miscare", 1);
    repo.store(a1);
    assert(repo.get_all().size() == 4);
    Activitate a2 = repo.find("Volei");
    assert(a2.get_descriere() == "Servire");
    assert(a2.get_tip() == "miscare");

    repo.stergere("Volei");
    assert(repo.get_all().size() == 3);
}

void testFind() {
    ActivitateRepo repo;
    Activitate a1("Baschet", "Dribbling", "miscare", 2);
    repo.store(a1);
    const auto& activitate = repo.find("Baschet");
    assert(activitate.get_titlu() == "Baschet");
    assert(activitate.get_descriere() == "Dribbling");
    assert(activitate.get_tip() == "miscare");
    assert(activitate.get_durata() == 2);
    try {
        repo.find("Fotbal");
    }
    catch (RepoException& e) {
        assert(e.getMessage() == "Activitatea nu exista!\n");
    }

}

void testRepo() {
    ActivitateRepo repo;
    Activitate a1("Baschet", "Dribbling", "miscare", 2);
    repo.store(a1);
    const auto& activitati = repo.get_all();
    assert(activitati.size() == 1);
    assert(activitati[0].get_titlu() == "Baschet");
    assert(activitati[0].get_descriere() == "Dribbling");
    assert(activitati[0].get_tip() == "miscare");
    assert(activitati[0].get_durata() == 2);
    assert(activitati.size() == 1);
    try {
        repo.store(a1);
    }
    catch (RepoException& e) {
        assert(e.getMessage() == "Activitatea exista deja!\n");
    }
}

void testRepoActualizare() {
    ActivitateRepo repo;
    Activitate a1("Baschet", "Dribbling", "miscare", 2);
    repo.store(a1);
    repo.actualizare(a1);
    const auto& activitati = repo.get_all();
    assert(activitati.size() == 1);
    assert(activitati[0].get_titlu() == "Baschet");
    assert(activitati[0].get_descriere() == "Dribbling");
    assert(activitati[0].get_tip() == "miscare");
    assert(activitati[0].get_durata() == 2);
    try {
        repo.actualizare(Activitate("Fotbal", "Pase", "miscare", 3));
    }
    catch (RepoException& e) {
        assert(e.getMessage() == "Activitatea nu exista!\n");
    }
}

void testRepoStergere() {
    ActivitateRepo repo;
    Activitate a1("Baschet", "Dribbling", "miscare", 2);
    repo.store(a1);
    repo.stergere("Baschet");
    const auto& activitati = repo.get_all();
    assert(activitati.empty());
    try {
        repo.stergere("Baschet");
    }
    catch (RepoException& e) {
        assert(e.getMessage() == "Activitatea nu exista!\n");
    }
}
void RepoTestAll() {
    testFileRepo();
    testFind();
    testRepo();
    testRepoActualizare();
    testRepoStergere();
}