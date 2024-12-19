#include "IteratorMultime.h"
#include "Multime.h"
#include <stdexcept>
#include <exception>
#define NOT_VALID 999999

/**
Constructorul care initializeaza un iterator pentru o multime data.
Complexitate: 0(n)
Best case=Worst case=Average case
 */
IteratorMultime::IteratorMultime(const Multime& m) : multime(m) {
    pozitie_curenta = 0;
    if ((element() == EMPTY_POSITION || element() == DELETED_POSITION) && pozitie_curenta < multime.get_capacitate())
        while ((element() == EMPTY_POSITION || element() == DELETED_POSITION) && pozitie_curenta < multime.get_capacitate()) {
            pozitie_curenta++;
        }
    if (pozitie_curenta >= multime.get_capacitate())
        pozitie_curenta = NOT_VALID;
}

/**
Muta iteratorul la prima pozitie valida din multime.
Complexitate: 0(n)
Best case=Worst case=Average case
 */
void IteratorMultime::prim() {
    pozitie_curenta = 0;
    if ((element() == EMPTY_POSITION || element() == DELETED_POSITION) && pozitie_curenta < multime.get_capacitate())
        while ((element() == EMPTY_POSITION || element() == DELETED_POSITION) && pozitie_curenta < multime.get_capacitate()) {
            pozitie_curenta++;
        }
    if (pozitie_curenta >= multime.get_capacitate())
        pozitie_curenta = NOT_VALID;
}

/**
Avanseaza iteratorul la urmatoarea pozitie valida din multime.
Complexitate: 0(n)
Best case=Worst case=Average case
 */
void IteratorMultime::urmator() {
    if (!valid()) {
        throw _exception();
    }
    pozitie_curenta++;
    if ((element() == EMPTY_POSITION || element() == DELETED_POSITION) && pozitie_curenta < multime.get_capacitate())
        while ((element() == EMPTY_POSITION || element() == DELETED_POSITION) && pozitie_curenta < multime.get_capacitate()) {
            pozitie_curenta++;
        }
    if (pozitie_curenta >= multime.get_capacitate())
        pozitie_curenta = NOT_VALID;
}

/**
Returneaza elementul curent din multime.
Complexitate: 0(1)
Best case=Worst case=Average case
 */
TElem IteratorMultime::element() const {
    if (valid())
        return multime.get_elemente()[pozitie_curenta];
    else
        return -1;
}

/**
Verifica daca iteratorul este valid.
Complexitate: 0(1)
Best case=Worst case=Average case
 */
bool IteratorMultime::valid() const {
    if (pozitie_curenta != NOT_VALID)
        return true;
    return false;
}