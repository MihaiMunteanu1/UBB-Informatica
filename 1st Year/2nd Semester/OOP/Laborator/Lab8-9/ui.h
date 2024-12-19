#pragma once
#include "ActivitateService.h"
class ui {
    ActivitateService& serv;
public:
    explicit ui(ActivitateService& serv): serv{serv}{
    }
    void run();

    void uiDictionar();

    void adaugaActivitate();

    void stergeActivitate();

    void actualizeazaActivitate();

    void afiseazaActivitati();

    void afiseazaActivitatiFiltrate();

    void afiseazaActivitatiSortate();

    void uiCautare();

    static void menuManager();

    void uiAddToListaActivitati();

    void uiEmptyListaActivitati();

    void uiAddRandom();

    void uiPrint();

    void uiExport();
};



