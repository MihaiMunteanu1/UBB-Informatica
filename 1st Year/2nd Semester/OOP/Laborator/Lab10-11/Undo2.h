#pragma once

#include "Activitate.h"
#include "repository.h"

class ActiuneUndo {
public:
    virtual void doUndo() = 0;
    virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
    Activitate activitateAdaugata;
    AbstractRepo& repo;
public:
    UndoAdauga(AbstractRepo& repo, const Activitate& a) : repo{ repo }, activitateAdaugata{ a } {}

    void doUndo() override {
        repo.stergere(activitateAdaugata.get_titlu());
    }
};


class UndoModifica : public ActiuneUndo {
    Activitate activitateNoua, activitateVeche;
    AbstractRepo& repo;
public:
    UndoModifica(AbstractRepo& repo, const Activitate& activitateNoua, const Activitate& activitateVeche) : repo{ repo },
                                                                                                            activitateNoua{ activitateNoua }, activitateVeche{ activitateVeche } {
    }
    void doUndo() override {
        repo.stergere(activitateNoua.get_titlu());
        repo.store(activitateVeche);
    }
};

class UndoSterge : public ActiuneUndo {
    const Activitate& activitateStearsa;
    AbstractRepo& repo;
public:
    UndoSterge(AbstractRepo& repo, const Activitate& activitateStearsa) : repo{ repo }, activitateStearsa{ activitateStearsa } {}

    void doUndo() override {
        repo.store(activitateStearsa);
    }
};
