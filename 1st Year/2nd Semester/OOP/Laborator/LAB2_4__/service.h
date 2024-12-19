#pragma once
#include "repository.h"
#include <stdlib.h>

typedef struct {
    List* allOferte;
    List* undoList;
}ManagerOferte;

ManagerOferte createManagerOferte();

void destroyManagerOferte(ManagerOferte* store);
/*
 * Adauga Oferta la lista l
 * param l: lista
 * param tip: tipul imobiliarului Ofertei
 * param suprafata: suprafata imobiliarului
 * param adresa: adresa imobiliarului
 * param pret: pretul imobiliarului
 * return: 1 - daca s-a efectuat adaugarea
 *         0 - daca datele au fost invalide
 */
int adaugaOferta(ManagerOferte* store, char* tip, int suprafata, char* adresa, int pret);
/*
 * Sterge Oferta in functie de tip si suprafata
 * param l: lista
 * param tip: Tipul Ofertei ce se sterge
 * param suprafata: Suprafata imboniliarului Ofertei ce se sterge
 * return: 1 - daca s-a sters din stoc
 *         0 - daca nu s-a sters nimic din stoc
 */
int stergeOferta(ManagerOferte* store, char* tip, int suprafata);

/*
 * Modifica Oferta in functie de tip si suprafata
 * param l: lista
 * param tip: Tipul Ofertei ce se modifica
 * param suprafata: Suprafata imobiliarului ofertei ce se modifica
 * param tip_nou: Tipul Nou al Ofertei ce se modifica
 * param suprafata_nou: Suprafata noua a imobiliarului ofertei ce se modifica
 * return: 1 - daca s-a modificat
 *         0 - daca nu s-a modificat
 */
int modificaOferta(ManagerOferte* store, char* tip, int suprafata, char* tip_nou, int suprafata_noua,char* adresa_noua,int pret_nou);

List* filterOferteTip(ManagerOferte * store, char* tip);

List* filterOferteSuprafata(ManagerOferte * store, int suprafata);

List* filterOfertePret(ManagerOferte * store, int pret);

List* sortOferteByPret(ManagerOferte* store);

List* sortOferteByTip(ManagerOferte* store);

int undo(ManagerOferte* store);

int findOferta(ManagerOferte* store, char* tip,int suprafata);

void testAddService();
void testFindService();
void testDeleteService();
void testModifyService();
void testFilterTipService();
void testFilterSuprafataService();
void testFilterPretService();
void testSortPretService();
void testSortTipService();
void testUndo();
