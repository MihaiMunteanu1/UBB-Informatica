#include "TestScurt.h"
#include <assert.h>
#include <string>
#include "Dictionar.h"
#include "IteratorDictionar.h"

void testAdaugaInexistente(){
    Dictionar d;
    d.adauga(1, 1);
    d.adauga(2, 2);
    d.adauga(3, 3);
    Dictionar d2;
    d2.adauga(1, 1);
    d2.adauga(4, 4);
    d2.adauga(5, 5);
    assert(d.adaugaInexistente(d2) == 2);
    Dictionar d3;
    d3.adauga(1,1);
    assert(d.adaugaInexistente(d3) == 0);
}

void testAll() { //apelam fiecare functie sa vedem daca exista
    testAdaugaInexistente();
	Dictionar d;
	assert(d.vid() == true);
	assert(d.dim() == 0); //adaug niste elemente
	assert(d.adauga(5,5)==NULL_TVALOARE);
	assert(d.adauga(1,111)==NULL_TVALOARE);
	assert(d.adauga(10,110)==NULL_TVALOARE);
	assert(d.adauga(7,7)==NULL_TVALOARE);
	assert(d.adauga(1,1)==111);
	assert(d.adauga(10,10)==110);
	assert(d.adauga(-3,-3)==NULL_TVALOARE);
	assert(d.dim() == 5);
	assert(d.cauta(10) == 10);
	assert(d.cauta(16) == -1);
	assert(d.sterge(1) == 1);
	assert(d.sterge(6) == -1);
	assert(d.dim() == 4);



	TElem e;
	IteratorDictionar id = d.iterator();
	id.prim();
	int s1 = 0, s2 = 0;
	while (id.valid()) {
		e = id.element();
		s1 += e.first;
		s2 += e.second;
		id.urmator();
	}
	assert(s1 == 19);
	assert(s2 == 19);

}

