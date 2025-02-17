#pragma once

#define NULL_TELEM -1
typedef int TElem;

class IteratorColectie;

//pentru perechea (element,frecventa)
struct TPereche{
    TElem e;
    int frecventa;

} ;

class Colectie
{
    friend class IteratorColectie;

private:
    //capacitate
    int cp;

    //dimensiune
    int n;

    //dimensiunea colectie cu tot cu frecventa
    int n_total;

    //elemente
    TPereche *p;

    //pentru redimensionare
    void redim();

public:

    //constructorul implicit
    Colectie();

    //adauga un element in colectie
    void adauga(TElem e);

    //sterge o aparitie a unui element din colectie
    //returneaza adevarat daca s-a putut sterge
    bool sterge(TElem e);

    //verifica daca un element se afla in colectie
    bool cauta(TElem elem) const;

    //returneaza numar de aparitii ale unui element in colectie
    int nrAparitii(TElem elem) const;

    //intoarce numarul de elemente din colectie;
    int dim() const;

    //verifica daca colectia e vida;
    bool vida() const;

    //returneaza un iterator pe colectie
    IteratorColectie iterator() const;

    // destructorul colectiei
    ~Colectie();

    //adauga aparitii multiple ale unui element
    void adaugaAparitiiMultiple(int nr, TElem elem);

};