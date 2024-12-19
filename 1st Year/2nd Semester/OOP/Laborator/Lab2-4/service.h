/*
#ifndef OOP_LAB2_4_SERVICE_H
#define OOP_LAB2_4_SERVICE_H

#endif //OOP_LAB2_4_SERVICE_H
*/
#pragma once
#include "medicament.h"
#include "myList.h"

typedef struct{
    List* lista;
    List* undoList;
} Farmacie;

typedef int (*filtreazaFunction)(Entitate ,Entitate);

int filternume(Entitate m,Entitate nume);

int filterstoc(Entitate m,Entitate stoc);

int filterconcentratie(Entitate m,Entitate concentratie);

List* filterFarmacie(List* list, filtreazaFunction f, Entitate criteriu);

/*Functie care creaza o lista ce contine o lista de medicamente*/
Farmacie createFarmacie();

int Undo(Farmacie* );

/*Functie care dealoca lista ce contine lista de medicamente*/
void destroyFarmacie(Farmacie* );

/*Functie care adauga o entitate in farmacie*/
int addEnt(Farmacie* list, int, char*, float, int);

/*Functie care sterge o entitate din store*/
int deleteEnt(Farmacie* list, int );

/*Functie care face update la un produs*/
int updateEnt(Farmacie* , int, char*, float);

/*Cauta un id in lista*/
int checkId(Farmacie* list, int);

/*Adauga in stocul unui produs deja existent*/
void addStoc(Farmacie* list, int);

/*Distruge tot*/
void destroyAll(Farmacie* list);

/*Sorteaza medicamentele dupa stoc.*/
List* sortareStoc(Farmacie* list);

/*Sorteaza medicamentele alfabetic*/
List* sortareNume(Farmacie* list);

/*Filtreaza medicamentele care au stocul mai mic decat o valoare data*/
List* filterStoc(Farmacie* list,int);

/*Filtreaza medicamentele care incep cu o litera data*/
List* filterNume(Farmacie* list, char litera);

List* filterConcentratie(Farmacie* list,float);