#include "ListaActivitati.h"
#include <cassert>

using std::shuffle;
void ListaActivitati::adaugaListaActivitati(const Activitate& activitate) {
    this->lista_activitati.push_back(activitate);
}

void ListaActivitati::addRandomActivitati(vector<Activitate> originalActivitati, int howMany) {
    shuffle(originalActivitati.begin(), originalActivitati.end(), std::default_random_engine(std::random_device{}()));
    while (lista_activitati.size() < howMany && !originalActivitati.empty()) {
        lista_activitati.push_back(originalActivitati.back());
        originalActivitati.pop_back();
    }
    notify();
}


void testListaActivitati() {
    ListaActivitati listaActivitai;
    Activitate a1("Baschet", "Dribbling", "miscare", 2);
    listaActivitai.adaugaListaActivitati(a1);
    const auto& activitati = listaActivitai.getAllListaActivitati();
    assert(activitati.size() == 1);
    assert(activitati[0].get_titlu() == "Baschet");
    assert(activitati[0].get_descriere() == "Dribbling");
    assert(activitati[0].get_tip() == "miscare");
    assert(activitati[0].get_durata() == 2);
    assert(activitati.size() == 1);
    listaActivitai.clearAllListaActivitati();
    assert(listaActivitai.getAllListaActivitati().empty());
    vector<Activitate> originalActivitati;
    originalActivitati.push_back(a1);
    Activitate a2("Fotbal", "Dribbling", "miscare", 2);
    originalActivitati.push_back(a2);
    listaActivitai.addRandomActivitati(originalActivitati, 2);
    assert(listaActivitai.getAllListaActivitati().size() == 2);
}
