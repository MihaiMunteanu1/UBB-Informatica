#include "Activitate.h"

/**
 * Functie care returneaza titlu activitatii
 * @return
 */
string Activitate::get_titlu() const {
    return titlu;
}
/**
 * Functie care returneaza descrierea activitatii.
 * @return
 */
string Activitate::get_descriere() const {
    return descriere;
}
/**
 * Functie care returneaza tipul activitatii.
 * @return
 */
string Activitate::get_tip() const {
    return tip;
}
/**
 * Functie care returneaza durata activitatii.
 * @return
 */
int Activitate::get_durata() const {
    return durata;
}
/**
 * Functie care valideaza o activitate.
 * @param activitate
 * @return
 */
int Activitate::validareActivitate(const Activitate &activitate){
    if(activitate.get_titlu().empty())
        return 1;
    if(activitate.get_descriere().empty())
        return 2;
    if(activitate.get_tip().empty())
        return 3;
    if(activitate.get_durata() <= 0)
        return 4;
    return 0;
}

