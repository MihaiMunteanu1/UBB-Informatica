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


