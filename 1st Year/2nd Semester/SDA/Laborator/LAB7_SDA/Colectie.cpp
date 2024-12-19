#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>

using namespace std;
/**
 * Complexitate: 0(1)
 * Best Case= Worst Case= Average Case
 * @param c1
 * @param c2
 * @return
 */
bool rela(TElem c1, TElem c2) {
    if (c1 <= c2) {
        return true;
    }
    else {
        return false;
    }
}
/**
 * Complexitate: 0(cp)
 * Best Case= Worst Case= Average Case
 */
Colectie::Colectie() {
    rel = rela;
    cate = 0;
    prim = -1;
    stanga = new int[cp];
    dreapta = new int[cp];
    e = new StangaDreapta[cp];
    for (int i = 0; i < cp - 1; i++)
        stanga[i] = i + 1;
    stanga[cp - 1] = -1;
    primLiber = 0;
}
/**
 * Complexitate: 0(h), h=adancimea arborelui
 * Best Case= Worst Case= Average Case
 * @param elem
 * @param primul
 * @param i
 */
void Colectie::doo(TElem elem, int primul, int i)
{
    if (rel(e[primul].element, elem) && dreapta[primul] == -1) {
        dreapta[primul] = i; return;
    }
    if (!rel(e[primul].element, elem) && stanga[primul] == -1) {
        stanga[primul] = i; return;
    }
    if (rel(e[primul].element, elem) && dreapta[primul] != -1) {
        doo(elem, dreapta[primul], i);
    }
    if (!rel(e[primul].element, elem) && stanga[primul] != -1) {
        doo(elem, stanga[primul], i);
    }
}
/**
 * Complexitate: 0(h)
 * Best Case= Worst Case= Average Case
 * @param e
 */
void Colectie::adauga(TElem e)
{
    int i, j = prim;
    i = aloca();
    if (i != -1) {
        this->e[i].element = e;
        stanga[i] = -1;
        dreapta[i] = -1;
    }
    if (prim == -1) {
        prim = 0;
        j = prim;
    }
    if (i != j) {
        doo(e, j, i);
    }
    cate++;
}
/**
 * Complexitate: O(h)
 * Best Case= 0(1) se gaseste in radacina
 * Worst Case= 0(h) nu exista sau e pe ultimul nivel
 * @param i
 * @param elem
 * @return
 */
bool Colectie::stergee(int i, TElem elem) {
    TElem minim;
    if (i == -1) {
        return false;
    }
    if (rel(elem, e[i].element) && e[i].element != elem) {
        return stergee(stanga[i], elem);
    }
    else {
        if (rel(e[i].element, elem) && e[i].element != elem) {
            return stergee(dreapta[i], elem);
        }
        else {
            if (e[i].element == elem) {
                if (stanga[i] != -1 && dreapta[i] != -1) {
                    minim = mini(dreapta[i]);
                    e[i].element = minim;
                    return stergee(dreapta[i], e[i].element);
                }
                else {
                    dealoca(i);
                }
                return true;
            }
            else {
                return false;
            }
        }
    }
}
/**
 * Complexitate: O(h)
 * Best Case= 0(1) se gaseste in radacina
 * Worst Case= 0(h) nu exista sau e pe ultimul nivel
 * @param elem
 * @return
 */
bool Colectie::sterge(TElem e)
{
    if (cate == 0) {
        return false;
    }
    if (stergee(prim, e)) {
        cate--;
        return true;
    }
    return false;
}

/**
 * Complexitate: O(h)
 * Best Case= 0(1) se gaseste in radacina
 * Worst Case= 0(h) nu exista sau e pe ultimul nivel
 * @param i
 * @param elem
 * @return
 */
bool Colectie::cautaa(int i, TElem elem)const {
    if (e[i].element == elem) {
        return true;
    }
    if (rel(e[i].element, elem) && dreapta[i] != -1) {
        return cautaa(dreapta[i], elem);
    }
    if (!rel(e[i].element, elem) && stanga[i] != -1) {
        return cautaa(stanga[i], elem);
    }
    return false;
}
/**
 * Complexitate: O(h)
 * Best Case= 0(1) se gaseste in radacina
 * Worst Case= 0(h) nu exista sau e pe ultimul nivel
 * @param elem
 * @return
 */
bool Colectie::cauta(TElem elem) const {
    if (cate == 0) {
        return false;
    }
    return cautaa(prim, elem);
}
/**
 * Complexitate: 0(n)
 * Best Case= Worst Case= Average Case
 * @param i
 * @param elem
 * @return
 */
int Colectie::apar(int i, TElem elem)const {
    int nr = 0;
    if (i == -1) {
        return 0;
    }
    if (e[i].element == elem) {
        nr++;
    }
    nr += apar(stanga[i],elem);
    nr += apar(dreapta[i],elem);
    return nr;
}

/**
 * Complexitate: 0(n)
 * Best Case= Worst Case= Average Case
 * @param elem
 * @return
 */
int Colectie::nrAparitii(TElem elem) const {
    if (cate == 0) {
        return 0;
    }
    int nr = 0;
    nr += apar(prim,elem);
    return nr;
}
/**
* Complexitate: O(h), adancimea subarborelui dat
* Best Case= 0(1) pe nivelul urmator
* Worst Case= 0(h) pe ultimul nivel
 * @param i
 * @return
 */
TElem Colectie::mini(int i){
    while(stanga[i]!=-1)
        i=stanga[i];
    return e[i].element;
}
/**
 * Complexitate: 0(1)
 * @return
 */
int Colectie::dim() const {
    return cate;
}

/**
 * Complexitate: 0(1)
 * @return
 */
bool Colectie::vida() const {
    if (cate == 0) {
        return true;
    }
    return false;
}

/**
 * Complexitate: 0(1)
 * @return
 */
IteratorColectie Colectie::iterator() const {
    return  IteratorColectie(*this);
}

/**
 * Complexitate: 0(1)
 */
Colectie::~Colectie() {
    delete[]e;
    delete[]stanga;
    delete[]dreapta;
}

/**
 * Complexitate: 0(1)
 * @return
 */
int Colectie::aloca() {
    int i = primLiber;
    primLiber = stanga[primLiber];
    return i;
}
/**
 * Complexitate: 0(cp)
 * Se trece pozitia i in lista spatiului liber
 * @param i
 */
void Colectie::dealoca(int i) {
    for (int k = 0; k < cp; k++) {
        if (stanga[k] == i) {
            int m = max(stanga[i], dreapta[i]);
            stanga[k] = m;
        }
    }
    for (int k = 0; k < cp; k++) {
        if (dreapta[k] == i) {
            int m = max(stanga[i], dreapta[i]);
            dreapta[k] = m;
        }
    }
    if (i == prim) {
        prim = dreapta[i];
        primLiber = i;
        stanga[primLiber] = cate;
    }
    else {
        int ant = primLiber;
        primLiber = i;
        stanga[i] = ant;
    }
}

/**
 * Complexitate: 0(n)
 * Best case = Worst Case = Average Case
 * @return
 */
int Colectie::valoareMaxima() const {
    if(vida())
        return NULL;
    int max = INT_MIN;
    for (int i = 0; i < cate; i++) {
        if (e[i].element > max) {
            max = e[i].element;
        }
    }
    return max;
}
/**
* Subalg valoareMaxima
 * daca vida atunci
 *      returneaza -1
 * max<- -1
 * pentru i<-1,capacitate executa
 *     daca elemente[i]>max atunci
 *       max<-elemente[i]
 *
 * returneaza max
*/