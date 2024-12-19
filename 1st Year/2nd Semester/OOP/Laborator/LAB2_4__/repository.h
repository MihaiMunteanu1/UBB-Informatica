#pragma once
#include <stdlib.h>
#include "domain.h"

typedef void* ElemType;

typedef void (*DestroyFct)(ElemType);
typedef ElemType(*CopyFct)(ElemType);

typedef struct {
    ElemType* elements;
    int length;
    int capacitate;
    DestroyFct dfnc;
} List;
/*
 * Creeaza o lista goala
 * return: lista
 */
List* createEmpty(DestroyFct f);

/*
 * Distruge o lista
 */
void destroy(List* l);

/*
 * Adauga in lista l elementul el
 * param l: lista
 * param el: elementul ce se introduce in lista
 */
void add(List* l, ElemType el);
/*
 * Sterge elementul de pe pozitia poz din lista l
 * param l: lista din care se sterge
 * param poz: pozitia elementului ce se sterge (int)
 * return: elementul ce s-a sters
 */
ElemType delete(List* l, int poz);

/*
 * Returneaza elementul de pe pozitia poz
 * param l: lista
 * param poz: pozitia elementului ce se returneaza
 * return: Elementul de pe pozitia poz
 */
ElemType get(List* l, int poz);

/*
 * Returneaza lungimea listei l
 * param l: lista
 * return: lungimea listei l
 */
int size(List* l);
/*
 * Face o copie a listei
 * return List care contine aceleasi elemente ca l
 */
List* copyList(List* l,CopyFct copyFct);

ElemType setElem(List* v, int poz, ElemType el);

void testCreateVector();
void testIterate();
void testCopy();
void testSet();
void testDelete();
void testListVoid();