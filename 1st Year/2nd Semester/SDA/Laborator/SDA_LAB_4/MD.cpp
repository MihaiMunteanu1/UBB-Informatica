#include "MD.h"
#include "IteratorMD.h"
#include <exception>

using namespace std;
/**
 * Constructor
 * Complexitate: Θ(n)
 * Best Case = Worst Case = Average Case

 */
MD::MD() {
    prim = -1;
    maxSize = 50;
    size = 0;

    elem = new TElem[maxSize];
    urm = new int[maxSize];
    pre = new int[maxSize];

    for (int i = 0; i < maxSize; i++) {
        urm[i] = -1;
        pre[i] = -1;
    }
}
/**
 * Redimensioneaza vectorii
 * Complexitate: Θ(n)
 * Best Case = Worst Case = Average Case
 */
void MD::redim() {
    auto *elemNou = new TElem[2 * maxSize];
    int *urmNou = new int[2 * maxSize];
    int *preNou = new int[2 * maxSize];

    for (int i = 0; i < maxSize; i++) {
        elemNou[i] = elem[i];
        urmNou[i] = urm[i];
        preNou[i] = pre[i];
    }

    for (int i = maxSize; i < 2 * maxSize; i++) {
        urmNou[i] = -1;
        preNou[i] = -1;
    }

    delete[] elem;
    delete[] urm;
    delete[] pre;
    elem = elemNou;
    urm = urmNou;
    pre = preNou;

    maxSize *= 2;
}
/**
 * Returneaza ultimul element din lista
 * Complexitate: O(n)
 * Best Case = Avem un singur element in lista
 * Worst Case = Avem n elemente in lista
 * @return
 */
int MD::getUltim() {
    int i = prim;
    while (urm[i] != -2)
        i = urm[i];
    return i;
}
/**
 * Returneaza primul element liber din lista
 * Complexitate: O(n)
 * Best Case = Avem un singur element in lista
 * Worst Case = Avem n elemente in lista
 * @return
 */
int MD::getPrimLiber() {
    int i = 0;
    while (urm[i] != -1)
        i++;
    return i;
}
/**
 * Adauga o pereche (cheie, valoare) in MD
 * Complexitate: O(n)
 * Worst Case = 0(n) daca size = maxSize
 * Best Case = 0(1) daca size != maxSize
 * @param c
 * @param v
 */
void MD::adauga(TCheie c, TValoare v) {
    if (size == 0) {
        elem[0] = make_pair(c, v);
        urm[0] = -2;
        pre[0] = -1;
        prim = 0;
        size++;
        return;
    }
    if (size == maxSize)
        redim();
    int ultim = getUltim();
    int primLiber = getPrimLiber();
    urm[ultim] = primLiber;
    pre[primLiber] = ultim;
    elem[primLiber] = make_pair(c, v);
    urm[primLiber] = -2;
    size++;
}
/**
 * Sterge o cheie si o valoare
 * Complexitate: O(n)
 * Best Case = 0(1) daca size = 0
 * Worst Case = 0(n) daca cheia e pe ultima pozitie
 * @param c
 * @param v
 * @return
 */
bool MD::sterge(TCheie c, TValoare v) {
    if (size == 0)
        return false;

    int i = prim;
    TElem elemDeSters = make_pair(c, v);
    while (i != -2 && elem[i] != elemDeSters) {
        i = urm[i];
    }

    if (i == -2 || elem[i] != elemDeSters)
        return false;

    if (i == prim) {
        prim = urm[i];
        if (prim != -2)
            pre[prim] = -1;
    } else {
        int ant = pre[i];
        urm[ant] = urm[i];
        if (urm[i] != -2)
            pre[urm[i]] = ant;
    }

    urm[i] = -1;
    pre[i] = -1;
    size--;

    return true;
}
/**
 * Cauta o cheie si returneaza vectorul de valori asociate
 * Complexitate: O(n)
 * Best Case 0(1) daca size = 0
 * Worst Case 0(n) daca cheia e pe ultima pozitie
 * @param c
 * @return
 */
vector<TValoare> MD::cauta(TCheie c) const {
    vector<TValoare> valori;
    if (size == 0)
        return valori;

    int i = prim;
    while (i != -2) {
        if (elem[i].first == c)
            valori.push_back(elem[i].second);
        i = urm[i];
    }

    return valori;
}
/**
 * Returneaza numarul de perechi (cheie, valoare) din MD
 * Complexitate: 0(1)
 * Best Case = Worst Case = Average Case
 * @return
 */
int MD::dim() const {
    return size;
}
/**
 * Verifica daca MD e vid
 * Complexitate: 0(1)
 * Best Case = Worst Case = Average Case
 * @return
 */
bool MD::vid() const {
    return (size == 0);
}
/**
 * Returneaza un iterator pe MD
 * Complexitate: 0(1)
 * Best Case = Worst Case = Average Case
 * @return
 */
IteratorMD MD::iterator() {
    return IteratorMD(*this);
}
/**
 * Destructor
 * Complexitate: 0(1)
 * Best Case = Worst Case = Average Case
 */
MD::~MD() {
    delete[] elem;
    delete[] urm;
    delete[] pre;
}
