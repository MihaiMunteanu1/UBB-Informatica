#include "service.h"
#include <string.h>
#include "customsort.h"
#include <assert.h>
ManagerOferte createManagerOferte()
{
    ManagerOferte store;
    store.allOferte = createEmpty(destroyOferta);
    store.undoList = createEmpty(destroy);
    return store;
}
void destroyManagerOferte(ManagerOferte* store)
{
    destroy(store->allOferte);
    destroy(store->undoList);
}
/*
 * Adauga Oferta la lista l
 * param l: lista
 * param tip: tipul imobiliarului
 * param suprafata: suprafata imobiliarului
 * param adresa: adresa imobiliarului
 * param pret: pretul imobiliarului
 * return: adauga o oferta
 */
int adaugaOferta(ManagerOferte* store, char* tip, int suprafata, char* adresa, int pret)
{
    Oferta* a = creeazaOferta(tip,suprafata,adresa,pret);
    int succ=valideazaOferta(a);
    if(succ!=0)
    {
        destroyOferta(a);
        return succ;
    }
    List* toUndo= copyList(store->allOferte,copyOferta);
    add(store->allOferte, a);
    add(store->undoList,toUndo);
    return 0;
}
int findOferta(ManagerOferte* store, char* tip,int suprafata){
    int poz_to_delete = -1;

    for (int i = 0; i < store->allOferte->length; i++) {
        Oferta * a = get(store->allOferte, i);
        if (strcmp(a->tip, tip) == 0 && a->suprafata==suprafata) {
            poz_to_delete = i;
            break;
        }
    }
    return poz_to_delete;
}
/*
 * Sterge oferta in functie de tip si suprafata
 * param l: lista
 * param tip: tipul imobiliarului ofertei
 * param suprafata: suprafata imobiliarului ofertei
 * return: 1 - daca s-a sters din stoc
 *         0 - daca nu s-a sters nimic din stoc
 */
int stergeOferta(ManagerOferte* store, char* tip, int suprafata)
{
    int poz_to_delete=findOferta(store,tip,suprafata);
    if(poz_to_delete!=-1)
    {
        List* toUndo= copyList(store->allOferte,copyOferta);
        add(store->undoList,toUndo);

        Oferta* a= delete(store->allOferte, poz_to_delete);
        destroyOferta(a);
        return 1;
    }
    return 0;
}

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
int modificaOferta(ManagerOferte* store, char* tip, int suprafata, char* tip_nou, int suprafata_noua, char* adresa_noua,int pret_nou)
{
    int poz_to_delete=findOferta(store,tip,suprafata);
    if (poz_to_delete != -1) {
        List* toUndo = copyList(store->allOferte, copyOferta);
        add(store->undoList, toUndo);

        Oferta * ofertaNoua = creeazaOferta(tip_nou, suprafata_noua, adresa_noua, pret_nou);
        Oferta * ofertaReplaced = setElem(store->allOferte, poz_to_delete, ofertaNoua);
        destroyOferta(ofertaReplaced);
        return 1;
    }
    else
        return 0;
}

int compararePret(Oferta* a1,Oferta* a2)
{
    return a1->pret > a2->pret;
}

int comparareTip(Oferta* a1,Oferta* a2)
{
    return strcmp(a1->tip, a2->tip);
}
List* sortOferteByPret(ManagerOferte * store) {
    List* ofertaList = copyList(store->allOferte, copyOferta);
    sort(ofertaList, compararePret);
    return ofertaList;
}

List* sortOferteByTip(ManagerOferte * store) {
    List* ofertaList = copyList(store->allOferte, copyOferta);
    sort(ofertaList, comparareTip);
    return ofertaList;
}

List* filterOferteTip(ManagerOferte * store, char* tip) {
    if (strcmp(tip, "") != 0) {
        List* filteredList = createEmpty(destroyOferta);
        for (int i = 0; i < store->allOferte->length; i++) {
            Oferta * a = get(store->allOferte, i);
            if (strcmp(tip, a->tip) == 0)
                add(filteredList, creeazaOferta(a->tip,a->suprafata, a->adresa, a->pret));
        }
        return filteredList;
    }
    else {
        return copyList(store->allOferte, copyOferta);
    }
}
List* filterOferteSuprafata(ManagerOferte * store, int suprafata) {
    if (suprafata >= 0) {
        List* filteredList = createEmpty(destroyOferta);
        for (int i = 0; i < store->allOferte->length; i++) {
            Oferta * a = get(store->allOferte, i);
            if (a->suprafata == suprafata)
                add(filteredList, creeazaOferta(a->tip,a->suprafata, a->adresa, a->pret));
        }
        return filteredList;
    }
    else {
        return copyList(store->allOferte, copyOferta);
    }
}
List* filterOfertePret(ManagerOferte * store, int pret) {
    if (pret >= 0) {
        List* filteredList = createEmpty(destroyOferta);
        for (int i = 0; i < store->allOferte->length; i++) {
            Oferta * a = get(store->allOferte, i);
            if (a->pret == pret)
                add(filteredList, creeazaOferta(a->tip,a->suprafata, a->adresa, a->pret));
        }
        return filteredList;
    }
    else {
        return copyList(store->allOferte, copyOferta);
    }
}
int undo(ManagerOferte* store) {
    if (size(store->undoList) == 0)
        return 0;
    List* l = delete(store->undoList, store->undoList->length - 1);
    destroy(store->allOferte);
    store->allOferte = l;
    return 1;
}
void testAddService() {
    ManagerOferte store = createManagerOferte();
    int successful1 = adaugaOferta(&store, "teren",1000, "zorilor", 50000);
    assert(successful1 == 0);

    int successful2 = adaugaOferta(&store, "",1000, "zorilor", 50000);
    assert(successful2 == 1);

    int successful3 = adaugaOferta(&store, "teren",-1000, "zorilor", 50000);
    assert(successful3 == 2);

    int successful4 = adaugaOferta(&store, "teren",1000, "", 50000);
    assert(successful4 == 3);

    int successful5 = adaugaOferta(&store, "teren",1000, "zorilor", -50000);
    assert(successful5 == 4);

    List* allOferte = filterOferteTip(&store, "");
    assert(size(allOferte) == 1);
    destroy(allOferte);

    destroyManagerOferte(&store);


}
void testFindService() {
    ManagerOferte store = createManagerOferte();

    int successful1 = adaugaOferta(&store, "teren",1000, "zorilor", 50000);
    assert(successful1 == 0);

    int successful2 = adaugaOferta(&store, "casa",1000, "zorilor", 50000);
    assert(successful2 == 0);

    int successful3 = adaugaOferta(&store, "teren",1000, "zorilor", 50000);
    assert(successful3 == 0);

    int successful4 = adaugaOferta(&store, "teren",1000, "iris", 50000);
    assert(successful4 == 0);

    assert(size(store.allOferte) == 4);
    int poz = findOferta(&store, "casa", 1000);
    assert(poz==1);

    int poz2 = findOferta(&store, "apartament", 1000);
    assert(poz2==-1);

    destroyManagerOferte(&store);

}
void testModifyService() {
    ManagerOferte store = createManagerOferte();

    int successful1 = adaugaOferta(&store, "teren",1000, "zorilor", 50000);
    assert(successful1 == 0);

    int successful2 = adaugaOferta(&store, "casa",1000, "zorilor", 50000);
    assert(successful2 == 0);

    int successful3 = adaugaOferta(&store, "teren",2000, "zorilor", 50000);
    assert(successful3 == 0);

    int successful4 = adaugaOferta(&store, "teren",3000, "iris", 50000);
    assert(successful4 == 0);

    assert(size(store.allOferte) == 4);
    int modify_success = modificaOferta(&store, "casa", 1000, "apartament", 1000, "zorilor", 50000);
    assert(modify_success==1);
    int modify_success2 = modificaOferta(&store, "apartament", 10000, "apartament", 1000, "zorilor", 50000);
    assert(modify_success2 == 0);
    destroyManagerOferte(&store);
}
void testDeleteService() {
    ManagerOferte store = createManagerOferte();

    int successful1 = adaugaOferta(&store, "teren",1000, "zorilor", 50000);
    assert(successful1 == 0);

    int successful2 = adaugaOferta(&store, "casa",1000, "zorilor", 50000);
    assert(successful2 == 0);

    int successful3 = adaugaOferta(&store, "teren",2000, "zorilor", 50000);
    assert(successful3 == 0);

    assert(size(store.allOferte) == 3);
    int succesful_del = stergeOferta(&store, "teren", 2000);
    assert(succesful_del == 1);
    int succesfully_del = stergeOferta(&store, "apartament", 1000);
    assert(succesfully_del == 0);
    destroyManagerOferte(&store);
}

void testFilterTipService() {
    ManagerOferte store = createManagerOferte();

    int successful1 = adaugaOferta(&store, "teren",1000, "zorilor", 50000);
    assert(successful1 == 0);

    int successful2 = adaugaOferta(&store, "casa",1000, "zorilor", 50000);
    assert(successful2 == 0);

    int successful3 = adaugaOferta(&store, "teren",2000, "zorilor", 50000);
    assert(successful3 == 0);

    assert(size(store.allOferte) == 3);

    List* filteredList = filterOferteTip(&store, "teren");
    assert(size(filteredList) == 2);
    destroy(filteredList);

    filteredList = filterOferteTip(&store, "apartament");
    assert(size(filteredList) == 0);
    destroy(filteredList);

    filteredList = filterOferteTip(&store, "");
    assert(size(filteredList) == 3);
    destroy(filteredList);
    destroyManagerOferte(&store);
}
void testFilterPretService() {
    ManagerOferte store = createManagerOferte();

    int successful1 = adaugaOferta(&store, "teren",1000, "zorilor", 50000);
    assert(successful1 == 0);

    int successful2 = adaugaOferta(&store, "casa",1000, "zorilor", 30000);
    assert(successful2 == 0);

    int successful3 = adaugaOferta(&store, "teren",2000, "zorilor", 50000);
    assert(successful3 == 0);

    assert(size(store.allOferte) == 3);

    List* filteredList = filterOfertePret(&store,50000 );
    assert(size(filteredList) == 2);
    destroy(filteredList);

    filteredList = filterOfertePret(&store, 10);
    assert(size(filteredList) == 0);
    destroy(filteredList);

    filteredList = filterOfertePret(&store,-10 );
    assert(size(filteredList) == 3);
    destroy(filteredList);
    destroyManagerOferte(&store);
}
void testFilterSuprafataService() {
    ManagerOferte store = createManagerOferte();

    int successful1 = adaugaOferta(&store, "teren",1000, "zorilor", 50000);
    assert(successful1 == 0);

    int successful2 = adaugaOferta(&store, "casa",1000, "zorilor", 30000);
    assert(successful2 == 0);

    int successful3 = adaugaOferta(&store, "teren",2000, "zorilor", 50000);
    assert(successful3 == 0);

    assert(size(store.allOferte) == 3);

    List* filteredList = filterOferteSuprafata(&store,1000 );
    assert(size(filteredList) == 2);
    destroy(filteredList);

    filteredList = filterOferteSuprafata(&store, 3000);
    assert(size(filteredList) == 0);
    destroy(filteredList);

    filteredList = filterOferteSuprafata(&store,-10 );
    assert(size(filteredList) == 3);
    destroy(filteredList);
    destroyManagerOferte(&store);
}
void testSortPretService() {
    ManagerOferte store = createManagerOferte();

    int successful1 = adaugaOferta(&store, "teren",1000, "zorilor", 50000);
    assert(successful1 == 0);

    int successful2 = adaugaOferta(&store, "casa",1000, "zorilor", 30000);
    assert(successful2 == 0);

    int successful3 = adaugaOferta(&store, "teren",2000, "zorilor", 50000);
    assert(successful3 == 0);

    assert(size(store.allOferte) == 3);
    List* sortedList = sortOferteByPret(&store);
    Oferta* a1 = get(sortedList, 0);
    Oferta* a2 = get(sortedList, 1);
    Oferta* a3 = get(sortedList, 2);


    assert(a1->pret == 30000);
    assert(a2->pret == 50000);
    assert(a3->pret == 50000);

    destroy(sortedList);
    destroyManagerOferte(&store);
}

void populateOfertaList(ManagerOferte * store) {
    int successful1 = adaugaOferta(store, "teren",1000, "zorilor", 50000);
    int successful2 = adaugaOferta(store, "casa",1000, "zorilor", 30000);
    int successful3 = adaugaOferta(store, "teren",2000, "zorilor", 50000);
    int successful4 = adaugaOferta(store, "apartament",1000, "zorilor", 50000);
    assert(successful1 == 0);
    assert(successful2 == 0);
    assert(successful3 == 0);
    assert(successful4 == 0);
}

void testSortTipService()
{
    ManagerOferte store = createManagerOferte();

    populateOfertaList(&store);
    assert(size(store.allOferte) == 4);

    List* sortedList = sortOferteByTip(&store);
    Oferta* a1 = get(sortedList, 0);
    Oferta* a2 = get(sortedList, 1);
    Oferta* a3 = get(sortedList, 2);
    Oferta* a4 = get(sortedList, 3);

    assert(strcmp(a1->tip, "apartament") == 0);
    assert(strcmp(a2->tip, "casa") == 0);
    assert(strcmp(a3->tip, "teren") == 0);
    assert(strcmp(a4->tip, "teren") == 0);

    destroy(sortedList);
    destroyManagerOferte(&store);

}

void testUndo() {
    ManagerOferte store = createManagerOferte();
    assert(adaugaOferta(&store, "teren",1000, "zorilor", 5000)==0);
    assert(modificaOferta(&store, "teren",1000,"apartament",2000,"bunaziua" ,8900) == 1);
    assert(stergeOferta(&store, "apartament", 2000) == 1);

    //undo delete
    undo(&store);

    List* crtOfertaList = filterOferteTip(&store, "");
    assert(size(crtOfertaList) == 1);
    Oferta* a = get(crtOfertaList, 0);
    assert(a->pret == 8900);
    destroy(crtOfertaList);

    //undo modify
    undo(&store);

    crtOfertaList = filterOferteTip(&store, "");
    assert(size(crtOfertaList) == 1);
    Oferta* a1 = get(crtOfertaList, 0);
    assert(a1->pret == 5000);
    destroy(crtOfertaList);

    //undo add
    undo(&store);
    crtOfertaList = filterOferteTip(&store, "");
    assert(size(crtOfertaList) == 0);
    destroy(crtOfertaList);

    int moreUndo = undo(&store);
    assert(moreUndo == 0);
    destroyManagerOferte(&store);
}