#include "IteratorColectie.h"
#include "Colectie.h"
#include <exception>
/**
 * Complexity θ(1)
 * CF=CD=CM
 * return: -
 */
IteratorColectie::IteratorColectie(const Colectie& c): col(c) {
    // Constructorul Iteratorului, inițializăm iteratorul pe primul element
    this -> curent = 0;
    this -> frecventa = 1;
}
/**
 * Complexity θ(1)
 * CF=CD=CM
 * return: -
 */
void IteratorColectie::prim() {
    // Setează iteratorul la începutul colecției
    curent=0;
    frecventa=1;
}
/**
 * Complexity θ(1)
 * CF=CD=CM
 * return: -
 */
void IteratorColectie::urmator() {
    // Trecem la următorul element din colecție
    if(valid())
    {
        if(frecventa < col.p[curent].frecventa)
        {
            frecventa++;
        }
        else
        {
            curent++;
            frecventa=1;
        }
    }
    else {
        throw std::exception();
    }
}
/**
 * Complexity θ(1)
 * CF=CD=CM
 * return: false daca iteratorul nu e valid, true altfel
 */
bool IteratorColectie::valid() const {
    // Verificăm dacă iteratorul este valid
    return curent < col.n;
}
/**
 * Complexity θ(1)
 * CF=CD=CM
 */
TElem IteratorColectie::element() const {
    // Returnează elementul curent referit de iterator
    if (valid())
    {
        return col.p[curent].e;
    }
    else
    {
        throw std::exception();
    }
}


