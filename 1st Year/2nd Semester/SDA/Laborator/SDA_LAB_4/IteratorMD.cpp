#include "IteratorMD.h"
#include "MD.h"

using namespace std;
/**
 * Constructor
 * Complexitate: Θ(1)
 * Best Case = Worst Case = Average Case
 * @param _md
 */
IteratorMD::IteratorMD(MD& md): md(md) {
    poz = md.prim;
}
/**
 * Returneaza elementul curent
 * Complexitate: Θ(1)
 * Best Case = Worst Case = Average Case
 * @return
 */
TElem IteratorMD::element() const{
    if (!valid())
        throw exception();
    return md.elem[poz];
}
/**
 * Verifica daca iteratorul e valid
 * Complexitate: Θ(1)
 * Best Case = Worst Case = Average Case
 * @return
 */
bool IteratorMD::valid() const {
    return (md.urm[poz] != -1 && poz >= 0);
}
/**
 * Muta iteratorul in MD
 * Complexitate: Θ(1)
 * Best Case = Worst Case = Average Case
 */
void IteratorMD::urmator() {
    if (!valid())
        throw exception();
    poz = md.urm[poz];
}
/**
 * Reseteaza pozitia iteratorului la inceputul MD
 * Complexitate: Θ(1)
 * Best Case = Worst Case = Average Case
 */
void IteratorMD::prim() {
    poz = md.prim;
}
/**
 * Elimina elementul curent
 * Complexitate: O(n)
 * Best Case 0(1) = Elementul eliminat e pe prima pozitie
 * Worst Case O(n) = Elementul eliminat e pe ultima pozitie
 * @return
 */
TElem IteratorMD::elimina() {
    if (!valid())
        throw exception();
    TElem e = md.elem[poz];
    int nextPoz=md.urm[poz];
    md.sterge(e.first, e.second);
    poz=nextPoz;
    return e;
}
/**
subalg elimina()
    daca !valid() atunci
        arunca exceptie
     sfdaca

     e <- md.elem[poz]
     nextPoz <- md.urm[poz]
     md.sterge(e.first, e.second)
     poz <- nextPoz
     return e
sf subalg
*/