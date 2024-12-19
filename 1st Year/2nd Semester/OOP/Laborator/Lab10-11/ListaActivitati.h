#pragma once

#include "Activitate.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "repository.h"
#include "Observer.h"
using std::vector;

class ListaActivitati:public Observable {
private:
    vector<Activitate> lista_activitati;
public:
    ListaActivitati() = default;

    void clearAllListaActivitati() {
        this->lista_activitati.clear();
        notify();
    }

    void adaugaListaActivitati(const Activitate& activitate);

    const vector<Activitate>& getAllListaActivitati() {
        return this->lista_activitati;
    }

    void addRandomActivitati(vector<Activitate> originalActivitati, int howMany);
};

void testListaActivitati();