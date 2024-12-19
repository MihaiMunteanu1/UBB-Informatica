#include "IteratorColectie.h"
#include "Colectie.h"

/**
 * Complexitate: 0(1)
 * @param c
 */
IteratorColectie::IteratorColectie(const Colectie& c) : col(c) {
    curent = c.prim;
}
/**
 * Complexitate: 0(h), h=inaltimea pe partea stanga a radacinii curente
 * @return
 */
TElem IteratorColectie::element()  {
    while (curent != -1) {
        s.push(curent);
        curent = col.stanga[curent];
    }
    curent = s.top();
    s.pop();
    return col.e[curent].element;
}
/**
 * Complexitate: 0(1)
 */
bool IteratorColectie::valid() const {
    return curent != -1 || !s.empty();
}
/**
 * Complexitate: 0(1)
 */
void IteratorColectie::urmator() {
    curent = col.dreapta[curent];
}
/**
 * Complexitate: 0(1)
 */
void IteratorColectie::prim() {
    curent = col.prim;
}