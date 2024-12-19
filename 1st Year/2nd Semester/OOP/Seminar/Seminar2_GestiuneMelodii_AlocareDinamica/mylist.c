#include "mylist.h"
#include <stdlib.h>
#include <assert.h>
List createEmpty()
{
	List lst;
	lst.capacity = 2;
	lst.elements = (TElem*) malloc(sizeof(TElem) * lst.capacity);
	lst.length = 0;
	return lst;
}

void add(List* lista, TElem m)
{
	if (lista->capacity == lista->length) {
		int capNoua = lista->capacity * 2;
		TElem* arrNou = (TElem*)malloc(sizeof(TElem) * capNoua);
		for (int i = 0; i < lista->length; i++)
			arrNou[i] = lista->elements[i];
		free(lista->elements);
		lista->elements = arrNou;
		lista->capacity = capNoua;
	}

	lista->elements[lista->length] = m;
	lista->length++;
}

TElem getElem(List* lista, int poz)
{
	return lista->elements[poz];
}

TElem setElem(List* lista, int poz, TElem el)
{
	TElem deletedElement = getElem(lista, poz);
	lista->elements[poz] = el;
	return deletedElement;
}

TElem del(List* lista, int poz)
{
	//in versiunea cu alocare statica:
	//complexitate mai mica, dar nu se pastreaza ordinea elementelor

	TElem deletedElement = getElem(lista, poz);
	for (int i = poz; i < lista->length-1; i++) {
		lista->elements[i] = lista->elements[i + 1];
	}
	lista->length--;
	return deletedElement;


}

List copyList(List* lista)
{
	List copieLista = createEmpty();
	for (int i = 0; i < lista->length; i++) {
		TElem e = getElem(lista, i);
		//Modificare de la versiunea statica:
		//nu se adauga elementul, ci o copie a lui
		//daca am fi lasat doar e, fiindca avem memorie alocata
		//dinamic la sirurile de caractere, melodiile din lista originala 
		//si copia listei ar referi acelasi spatiu de memorie
		//eroare la dealocare (se incearca dealocare x 2 pentru
		//acelasi spatiu)
		add(&copieLista, copyMelodie(&e));
	}
	return copieLista;
}

void destroy(List* lista)
{
	for (int i = 0; i < size(lista); i++) {
		Melodie m = getElem(lista, i);
		destroyMelodie(&m);
	}
	free(lista->elements);
	lista->length = 0;
}

int size(List* lista)
{
	return lista->length;
}

void testCreateList()
{
	List testList = createEmpty();
	assert(size(&testList)==0);
	destroy(&testList);
}

void testAddToList()
{
	List lista = createEmpty();
	assert(size(&lista)==0);
	add(&lista, createMelodie( "Smoke on the Water", "Deep Purple", 3.55));
	assert(size(&lista) == 1);
	add(&lista, createMelodie( "Time", "Pink Floyd", 4.11));
	assert(size(&lista) == 2);

	Melodie m1 = getElem(&lista, 0);
	assert(strcmp(m1.artist, "Deep Purple") == 0);
	assert(strcmp(m1.titlu, "Smoke on the Water") == 0);
	assert(m1.durata==3.55);


	Melodie m2 = getElem(&lista, 1);
	assert(strcmp(m2.artist, "Pink Floyd") == 0);
	assert(strcmp(m2.titlu, "Time") == 0);
	assert(m2.durata == 4.11);
	destroy(&lista);
	assert(size(&lista) == 0);
}

void testDeleteFromList()
{
	List lista = createEmpty();
	assert(size(&lista) == 0);
	add(&lista, createMelodie("Smoke on the Water", "Deep Purple", 3.55));
	add(&lista, createMelodie("Time", "Pink Floyd", 4.11));
	add(&lista, createMelodie("Bad Moon Rising", "CCR", 4.11));
	assert(size(&lista) == 3);

	Melodie m1 = del(&lista, 0);
	assert(size(&lista) == 2);
	assert(strcmp(m1.titlu, "Smoke on the Water") == 0);
	destroyMelodie(&m1);
	//de ce distrugem melodie aici, dar nu si in testAdd, m1, m2?


	Melodie m2 = del(&lista, 1);
	assert(size(&lista) == 1);
	assert(strcmp(m2.titlu, "Bad Moon Rising") == 0);
	destroyMelodie(&m2);

	Melodie m3 = del(&lista, 0);
	assert(size(&lista) == 0);
	assert(strcmp(m3.titlu, "Time") == 0);
	destroyMelodie(&m3);

	destroy(&lista);
	assert(size(&lista) == 0);
}

void testCopyList()
{
	List lista = createEmpty();
	add(&lista, createMelodie("Smoke on the Water", "Deep Purple", 3.55));
	add(&lista, createMelodie("Time", "Pink Floyd", 4.11));

	List listaCopie = copyList(&lista);
	assert(size(&listaCopie) == 2);
	Melodie m = getElem(&listaCopie, 0);
	assert(strcmp(m.titlu, "Smoke on the Water") == 0);
	destroy(&lista);
	destroy(&listaCopie);
}


