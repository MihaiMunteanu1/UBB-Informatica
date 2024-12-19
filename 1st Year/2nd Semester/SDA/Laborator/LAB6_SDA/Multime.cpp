#include "Multime.h"
#include "IteratorMultime.h"
#include <iostream>
#include <cmath>

/**
Verifica daca un numar este prim.
Complexitate: 0(sqrt(x))
Best case=Worst case=Average case
*/
bool prim(int x) {
    int d = 2;
    while (d <= sqrt(x)) {
        if (x % d == 0) {
            return false;
        }
        d++;
    }
    return true;
}
/**
Gaseste urmatorul numar prim mai mare decat cel dat.
Complexitate: 0(n)
Best case=Worst case=Average case
*/
int next_prime(int number) {
    int next_prime_number = number * 2;

    if (prim(next_prime_number))
        return next_prime_number;

    while (!prim(next_prime_number)) {
        next_prime_number++;
    }

    return next_prime_number;
}

/**
Constructorul care initializeaza o multime noua.
Complexitate: 0(n)
Best case=Worst case=Average case
 */
Multime::Multime() {
    capacitate = 17;
    dimensiune = 0;
    elemente = new TElem[capacitate];
    for (int i = 0; i < capacitate; i++) {
        elemente[i] = EMPTY_POSITION;
    }
}

/**
Functia care adauga un element in multime.
Complexitate: 0(1) pentru best case si 0(n) pentru worst case=> O(n)
 */
bool Multime::adauga(TElem elem) {
    if (cauta(elem))
        return false;
    int poz = doubleHash(elem);
    if (poz != -1) {
        elemente[poz] = elem;
        dimensiune++;
        return true;
    } else {
        resize();
        poz = doubleHash(elem);
        elemente[poz] = elem;
        dimensiune++;
        return true;
    }
}

/**
Functia care sterge un element din multime.
Complexitate: 0(1) pentru best case, 0(n) pentru worst case=> O(n)
 */
bool Multime::sterge(TElem elem) {
    int p = 0;
    int poz;
    int aux = abs(elem);
    while (p < capacitate) {
        poz = (hashFunction1(aux) + p * hashFunction2(aux)) % capacitate;
        if (elemente[poz] == EMPTY_POSITION)
            return false;
        else if (elemente[poz] != elem)
            p++;
        else if (elemente[poz] == elem) {
            elemente[poz] = DELETED_POSITION;
            dimensiune--;
            return true;
        }
    }
    return false;
}

/**
Functia care verifica daca un anumit element exista in multime.
Complexitate: 0(1) pentru best case, 0(n) pentru worst case => O(n)
 */
bool Multime::cauta(TElem elem) const {
    int p = 0;
    int poz;
    int aux = abs(elem);
    while (p < capacitate) {
        poz = (hashFunction1(aux) + p * hashFunction2(aux)) % capacitate;
        if (elemente[poz] == EMPTY_POSITION)
            return false;
        else if (elemente[poz] != elem)
            p++;
        else if (elemente[poz] == elem)
            return true;
    }
    return false;
}

/**
Functia care returneaza dimensiunea multimii (numarul de elemente).
Complexitate: 0(1)
Best case=Worst case=Average case
*/
int Multime::dim() const {
    return dimensiune;
}

/**
Functia care verifica daca multimea este vida.
Complexitate: 0(1)
Best case=Worst case=Average case
*/
bool Multime::vida() const {
    return dimensiune == 0;
}

/**
Functia care redimensioneaza multimea.
Complexitate: 0(n)
Best case=Worst case=Average case
 */
void Multime::resize() {
    TElem* aux = new TElem[dimensiune];
    int j = 0;
    for (int i = 0; i < capacitate; i++) {
        if (elemente[i] != EMPTY_POSITION && elemente[i] != DELETED_POSITION) {
            aux[j] = elemente[i];
            j++;
        }
    }
    capacitate = next_prime(capacitate);
    elemente = new TElem[capacitate];
    int poz;
    for (int i = 0; i < capacitate; i++) {
        elemente[i] = EMPTY_POSITION;
    }
    for (int i = 0; i < j; i++) {
        poz = doubleHash(aux[i]);
        elemente[poz] = aux[i];
    }
}

/**
Destructorul care elibereaza memoria alocata pentru multime.
Complexitate: 0(1)
Best case = Worst case = Average case
 */
Multime::~Multime() {
    delete[] elemente;
}

// Functia care returneaza un iterator pentru multime.
IteratorMultime Multime::iterator() const {
    return IteratorMultime(*this);
}
//Verifica daca multimea curenta e o submultime a multimii primite ca parametru
//Complexitate: O(n)
/*
subalg submultime( Multime m)
 pentru i<-1,capacitate executa
    daca elemente[i]!=EMPTY_POSITION si elemente[i]!= DELETED_POSITION atunci
        daca !m.cauata(elemente[i])
            return fals;
        sf daca
    sf daca
  sf pentru
  return adevarat
sf subalg
 */
bool Multime::submultime(Multime &m) const {
    for (int i = 0; i < capacitate; i++) {
        if (elemente[i] != EMPTY_POSITION && elemente[i] != DELETED_POSITION) {
            if (!m.cauta(elemente[i])) {
                return false;
            }
        }
    }
    return true;
}
