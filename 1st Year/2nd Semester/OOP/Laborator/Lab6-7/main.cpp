#include "repository.h"
#include "ActivitateService.h"
#include "ui.h"
#include "vectordinamic.h"
#include "testeVD.cpp"
/**4. Inchiriere masini

Creati o aplicatie pentru o firma de inchirieri auto. Fiecare masina are un numar de inmatriculare,
model si categorie (mini, sport, suv, etc).
Aplicatia permite:
a) adaugare de masini
b) actualizare masina existenta
c) inchiriere masina/returnare masina
d) Vizualizare masini dupa un criteru dat (categorie, model)
e) Permite sortarea masinilor dupa: model sau categorie (crescator/descrescator)*/

int main(){
    testeVectorDinamic<VectorDinamic<Activitate>>();
    testAll();
    ActivitateRepo repo;
    ActivitateService srv{repo};
    ui ui{srv};
    ui.run();
    return 0;
}
