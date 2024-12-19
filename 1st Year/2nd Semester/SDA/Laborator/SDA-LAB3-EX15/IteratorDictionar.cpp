#include "IteratorDictionar.h"
#include "Dictionar.h"
using namespace std;
/**
 * Constructor
 * Complexity: 0(1)
 * Best Case = Worst Case = Average Case
 * @param d
 */
IteratorDictionar::IteratorDictionar(const Dictionar& d) : dict(d), curent(d.elems) {
    /* Constructor: Initialize the iterator with the first element */
}
/**
 * Reseteaza pozitia iteratorului la inceputul containerului
 * Complexity: 0(1)
 * Best Case = Worst Case = Average Case
 */
void IteratorDictionar::prim() {
    /* Resets the iterator position to the beginning of the container */
    curent = dict.elems;
}
/**
 * Muta iteratorul la urmatorul element din container
 * arunca exceptie daca iteratorul nu e valid
 * Complexity: 0(1)
 * Best Case = Worst Case = Average Case
 */
void IteratorDictionar::urmator() {
    /* Moves the iterator to the next element in the container */
    if (valid()) {
        curent = curent->next;
    }
    else {
        throw ("Invalid iterator");
    }
}
/**
 * Returneaza valoarea elementului din container referit de iterator
 * arunca exceptie daca iteratorul nu e valid
 * Complexity: 0(1)
 * Best Case = Worst Case = Average Case
 * @return
 */
TElem IteratorDictionar::element() const {
    /* Returns the value of the current element */
    if (!valid()) {
        throw ("Invalid iterator");
    }
    return curent->key;
}
/**
 * Verifica daca iteratorul e valid
 * Complexity: 0(1)
 * Best Case = Worst Case = Average Case
 * @return
 */
bool IteratorDictionar::valid() const {
    /* Checks if the iterator is valid */
    return curent != NULL;
}
