#include "Dictionar.h"
#include "IteratorDictionar.h"
using namespace std;
/**
 * Complexity: O(n*m)
 * Best Case = toate cheile lui d se afla si in dictionar 0(n*min(m,n))
 * Worst Case = exista chei care nu se afla in dictionar 0(n*m) ,m-> nr elemente dictionar
 * Adauga in dictionarul curent toate perechile din d a caror cheie nu se afla deja in dictionar
 * @param d
 * @return nr_perechi
 */
int Dictionar::adaugaInexistente(Dictionar& d){
    int nr_perechi=0;
    IteratorDictionar it = d.iterator();
    while(it.valid()){
        TElem e = it.element();
        if(cauta(e.first)==NULL_TVALOARE){
            adauga(e.first,e.second);
            nr_perechi++;
        }
        it.urmator();
    }
    return nr_perechi;
}
/**
sublag adaugaInexistente(Dictionar& d)
    nr_perechi<-0
    IteratorDictionar it<-d.iterator()
    cat timp it.valid() executa
        TElem e <- it.element()
        daca cauta(e.first)=NULL_TVALOARE atunci
            adauga(e.first,e.second)
            nr_perechi<-nr_perechi + 1
        sf daca
        it.urmator()
    sf cattimp
    return nr_perechi
sf subalg
 */

/**
 * Constructor
 * Complexity: 0(1)
 * Best Case = Worst Case = Average Case
 */
Dictionar::Dictionar():elems(NULL){
    //Constructor
}
/**
 * Destructor
 * Complexity: 0(n)
 * Best Case = Worst Case = Average Case
 */
Dictionar::~Dictionar() {
	//Destructor
    while(elems!=NULL){
        Nod* next=elems->next;
        delete elems;
        elems=next;
    }
}
/**
 * Adauga o pereche (cheie, valoare) in dictionar
 * daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
 * daca nu exista cheia, adauga perechea si returneaza null
 * Complexity: O(n)
 * Best Case = 0(1) daca cheia exista deja
 * Worst Case = 0(n) daca cheia nu exista
 * @param c
 * @param v
 * @return
 */
TValoare Dictionar::adauga(TCheie c, TValoare v){
    Nod* current = elems;
    while (current != NULL) {
        if (current->key.first == c) {
            TValoare oldValue = current->key.second;
            current->key.second = v;
            return oldValue;
        }
        current = current->next;
    }
    Nod* newNode = new Nod;
    newNode->key.first = c;
    newNode->key.second = v;
    newNode->next = elems;
    elems = newNode;
    return NULL_TVALOARE;
}


/**
 * Cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
 * Complexity: O(n)
 * Best Case = 0(1) daca cheia este prima
 * Worst Case = 0(n) daca cheia nu exista
 * @param c
 * @return
 */
TValoare Dictionar::cauta(TCheie c) const{
    Nod* current = elems;
    while (current != NULL) {
        if (current->key.first == c) {
            return current->key.second;
        }
        current = current->next;
    }
	return NULL_TVALOARE;
}

/**
 * Sterge o cheie si returneaza valoarea asociata (daca exista) sau null
 * Complexity: O(n)
 * Best Case = 0(1) daca cheia este prima
 * Worst Case = 0(n) daca cheia nu exista
 * @param c
 * @return
 */
TValoare Dictionar::sterge(TCheie c){
    Nod* current = elems;
    Nod* prev = NULL;
    while (current != NULL) {
        if (current->key.first == c) {
            if (prev != NULL) {
                prev->next = current->next;
            } else {
                elems = current->next;
            }
            TValoare oldValue = current->key.second;
            delete current;
            return oldValue;
        }
        prev = current;
        current = current->next;
    }
	return NULL_TVALOARE;
}

/**
 * Returneaza numarul de perechi (cheie, valoare) din dictionar
 * Complexity: 0(n)
 * Best Case = Worst Case = Average Case
 * @return
 */
int Dictionar::dim() const {
    int size = 0;
    Nod* current = elems;
    while (current != NULL) {
        size++;
        current = current->next;
    }
    return size;
}

/**
 * Verifica daca dictionarul e vid
 * Complexity: 0(1)
 * Best Case = Worst Case = Average Case
 * @return
 */
bool Dictionar::vid() const{
    return (elems==NULL);
}

/**
 * Returneaza iterator pe dictionar
 * Complexity: 0(1)
 * Best Case = Worst Case = Average Case
 * @return
 */
IteratorDictionar Dictionar::iterator() const {
	return  IteratorDictionar(*this);
}


