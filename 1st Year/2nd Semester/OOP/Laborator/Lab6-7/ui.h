#pragma once
#include "ActivitateService.h"
class ui {
    ActivitateService serv;
public:
    explicit ui(const ActivitateService& serv): serv{serv}{
    }
    void run();

    void adaugaActivitate();

    void stergeActivitate();

    void actualizeazaActivitate();

    void afiseazaActivitati();

    void afiseazaActivitatiFiltrate();

    void afiseazaActivitatiSortate();

    void uiCautare();

};



