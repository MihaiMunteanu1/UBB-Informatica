#include "Colectie.h"
#include "IteratorColectie.h"
#include <exception>
//#include <iostream>

using namespace std;
/**
 * Complexity θ(n)
 * pre: capacitate=dimensiune sirului de perechi
 */
void Colectie::redim() {

    //alocam un spatiu de capacitate dubla
    TPereche *pNou = new TPereche [2 * cp];

    //copiem vechile valori in noua zona
    for (int i = 0; i < n; i++)
    {
        pNou[i] = p[i];
        pNou[i].frecventa = p[i].frecventa;
    }
    //dublam capacitatea
    cp = 2 * cp;

    //eliberam vechea zona
    delete[] p;

    //vectorul indica spre noua zona
    p = pNou;
}
/**
 * pre: -
 * Complexity θ(1)
 * return: o colectie vida, cp=1
 */
Colectie::Colectie() {
    // Constructorul pentru colecție
    this->cp = 1; // Capacitatea inițială
    p = new TPereche [cp]; // Alocare memorie pentru elemente
    this->n = 0; // Numărul de elemente inițial
    this->n_total=0; //Numarul total de elemente cu tot cu frecventa
}
/**
 * pre: e -> TElem
 * Complexity O(n)
 * Worst Case: θ(n)
 * Best Case: θ(1)
 * return: -
 */
void Colectie::adauga(TElem e) {
    if (n == cp)
        redim();
    if (!this->cauta(e)) {
        p[n].e = e;
        p[n].frecventa = 1;
        n++;
    }
    else {
        for (int i = 0; i < n; i++) {
            if (p[i].e == e) {
                p[i].frecventa++;
                break;
            }
        }
    }
    n_total++;
}
/**
 * pre: e apartine colectiei
 * Complexity O(n)
 * CF: elementul cautat e pe prima pozitie θ(1)
 * CD: elementul cautat nu e in colectie sau e pe ultima pozitie θ(n)
 * return: true daca e exista in colectie, false atlfel
*/
bool Colectie::sterge(TElem e) {
    if (!cauta(e))
        return false;
    else {
        int poz;
        for (poz = 0; poz < n; poz++) {
            if (p[poz].e == e)
                break;
        }
        if (p[poz].frecventa > 1)
        {
            p[poz].frecventa--;
        }
        else {
            for (int i = poz; i < n - 1; i++) {
                p[i].e = p[i + 1].e;
                p[i].frecventa = p[i + 1].frecventa;
            }
            n--;
        }
        n_total--;
        return true;
    }
}
/**
 * pre: e apartine colectiei
 * Complexity O(n)
 * CF: elementul cautat e pe prima pozitie
 * CD: elementul cautat nu e in colectie sau e pe ultima pozitie
 * return: true e apartine colectiei, false altfel
*/
bool Colectie::cauta(TElem elem) const {
    for (int i = 0; i < n; i++) {
        if (p[i].e == elem) {
            return true; // Elementul a fost găsit
        }
    }
    return false; // Elementul nu a fost găsit
}

/**
 * pre: e apartine colectiei
 * Complexity θ(n)
 * CF=CD=CM
 * return numarul de aparitii ale unui element in colectie
*/
int Colectie::nrAparitii(TElem elem) const {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (p[i].e == elem) {
            count += p[i].frecventa; // Adaugă frecvența elementului găsit
        }
    }
    return count;
}
/**
 * pre: -
 * Complexity θ(1)
 * CF=CD=CM
 */
int Colectie::dim() const {
    // Returnează dimensiunea colecției
    return n_total;
}
/**
 * pre: -
 * Complexity θ(1)
 * CF=CD=CM
 * return: true daca colectia e vida
 *          false altfel
 */
bool Colectie::vida() const {
    // Verifică dacă colecția este vidă
    return n == 0;
}
/**
 * pre: -
 * Complexity θ(1)
 * CF=CD=CM
 */
IteratorColectie Colectie::iterator() const {
    return IteratorColectie(*this); // Returnare iterator
}
/**
 * Complexity θ(1)
 * CF=CD=CM
 * return: -
 */
Colectie::~Colectie() {
    // Destructorul pentru eliberarea memoriei alocate pentru elemente
    delete[] p;
}
/**
 * pre: elem apartine colectiei
 * Complexity O(nr*n)
 * CF: nr<0 0(1)
 * CD: nr>=0 0(nr*n)
 */
void Colectie::adaugaAparitiiMultiple(int nr,TElem elem)
{
    if(nr<0)
    {
        throw ("Numar de aparitii invalid");
    }
    else{
        for(int i=0;i<nr;i++)
        {
            adauga(elem);
        }
    }
}
/*
 * subalg adaugaAparitiiMultiple(int nr, TElem elem)
 *    daca nr<0
 *         arunca exceptie: Numar de aparitii invalid
 *     altfel
 *         pentru i=0,nr executa
 *              adauga(elem)
 *
 *
 */