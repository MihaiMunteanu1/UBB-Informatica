#include "repository.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
/*
 * Creeaza o lista goala
 * return: lista
 */
List* createEmpty(DestroyFct f)
{
    List* l=malloc(sizeof(List));
    l->length = 0;
    l->capacitate=1;
    l->elements= malloc(sizeof(ElemType)*l->capacitate);
    l->dfnc=f;
    return l;
}

/*
 * Distruge o lista
 */
void destroy(List* l)
{
    for(int i=0; i<l->length; i++)
    {
        l->dfnc(l->elements[i]);
    }
    l->length=0;
    free(l->elements);
    free(l);
}
/*
 * Adauga in lista l elementul el
 * param l: lista
 * param el: elementul ce se introduce in lista
 */
void add(List* l, ElemType el)
{
    if(l->length == l->capacitate)
    {
        int newCapacitate = l->capacitate * 2;
        ElemType* newElements = malloc(sizeof(ElemType) * newCapacitate);
        for(int i=0; i<l->length; i++)
        {
            newElements[i]=l->elements[i];
        }
        free(l->elements);
        l->elements = newElements;
        l->capacitate = newCapacitate;
    }

    l->elements[l->length] = el;
    l->length++;
}

/*
 * Inlocuieste in lista l, elementul de pe pozitia poz cu el
 * param l: lista
 * param el: elementul ce se introduce in lista
 * param poz (int): pozitia din lista in care se introduce elementul el
 */
ElemType delete(List* l, int poz)
{
    ElemType el = l->elements[poz];
    for(int i=poz; i<l->length-1; i++)
    {
        l->elements[i]= l->elements[i+1];
    }
    l->length--;
    return el;
}

/*
 * Returneaza elementul de pe pozitia poz
 * param l: lista
 * param poz: pozitia elementului ce se returneaza
 * return: Elementul de pe pozitia poz
 */
ElemType get(List* l, int poz)
{
    return l->elements[poz];
}

/*
 * Returneaza lungimea listei l
 * param l: lista
 * return: lungimea listei l
 */
int size(List* l)
{
    return l->length;
}
/*
 * Face o copie a listei
 * return List care contine aceleasi elemente ca l
 */
List* copyList(List* l,CopyFct copyFct)
{
    List* l_copy = createEmpty(l->dfnc);
    for(int i=0; i<l->length; i++)
    {
        ElemType el = get(l, i);
        add(l_copy, copyFct(el));
    }
    return l_copy;
}

ElemType setElem(List* l, int poz, ElemType el) {
    ElemType replaced = l->elements[poz];
    l->elements[poz] = el;
    return replaced;
}

void testCreateVector() {
    List* l = createEmpty(destroyOferta);
    assert(size(l) == 0);
    destroy(l);

}
void testIterate() {
    List* l = createEmpty(destroyOferta);
    Oferta* a1 = creeazaOferta("teren",1000, "zorilor", 30000);
    Oferta* a2 = creeazaOferta("apartament",100, "bunaziua", 40000);
    Oferta* a3 = creeazaOferta("casa",250, "iris", 500000);


    add(l, a1);
    add(l, a2);
    add(l, a3);

    assert(size(l) == 3);
    Oferta * a = get(l, 0);

    assert(strcmp(a->tip, "teren") == 0);
    assert(strcmp(a->adresa, "zorilor") == 0);
    assert(a->suprafata==1000);
    assert(a->pret==30000);

    destroy(l);

}

void testCopy() {
    List* l1 = createEmpty(destroyOferta);
    add(l1, creeazaOferta("teren",1000, "zorilor", 30000));
    add(l1,creeazaOferta("apartament",100, "bunaziua", 40000));


    assert(size(l1) == 2);
    List* l2 = copyList(l1, copyOferta);
    assert(size(l2) == 2);
    Oferta* a = get(l2, 0);
    assert(strcmp(a->tip, "teren") == 0);
    destroy(l1);
    destroy(l2);

}

void testDelete() {
    List* l1 = createEmpty(destroyOferta);
    add(l1, creeazaOferta("teren",1000, "zorilor", 30000));
    add(l1,creeazaOferta("apartament",100, "bunaziua", 40000));


    assert(size(l1) == 2);
    Oferta * a = delete(l1, 0);

    assert(strcmp(a->tip, "teren") == 0);
    assert(strcmp(a->adresa, "zorilor") == 0);
    assert(a->suprafata==1000);
    assert(a->pret==30000);

    destroyOferta(a);

    assert(size(l1) == 1);
    destroy(l1);

}
void testSet() {
    List* l1 = createEmpty(destroyOferta);
    add(l1,  creeazaOferta("teren",1000, "zorilor", 30000));
    assert(size(l1) == 1);
    Oferta * replaced = setElem(l1,0,  creeazaOferta("apartament",100, "bunaziua", 40000));
    Oferta * a = get(l1, 0);
    assert(strcmp(a->tip, "apartament") == 0);
    assert(strcmp(a->adresa, "bunaziua") == 0);
    assert(a->suprafata==100);
    assert(a->pret==40000);
    destroyOferta(replaced);
    destroy(l1);
}
void testListVoid() {
    List* ofertaList = createEmpty(destroyOferta);
    add(ofertaList, creeazaOferta("teren",1000, "zorilor", 30000));
    add(ofertaList, creeazaOferta("apartament",100, "bunaziua", 40000));

    List* ofertaList2 = createEmpty(destroyOferta);
    add(ofertaList2, creeazaOferta("casa",250, "iris", 600000));
    add(ofertaList2, creeazaOferta("teren",2500, "turzii", 50000));
    add(ofertaList2, creeazaOferta("casa",350, "manastur", 700000));

    List* undoList = createEmpty(destroy);

    add(undoList, ofertaList);
    assert(size(undoList) == 1);
    add(undoList, ofertaList2);
    assert(size(undoList) == 2);
    destroy(undoList);
}