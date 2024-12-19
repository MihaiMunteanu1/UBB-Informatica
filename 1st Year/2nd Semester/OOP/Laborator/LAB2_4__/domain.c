#include <string.h>
#include <stdlib.h>
#include "domain.h"
#include <assert.h>
/*
 * Creeaza o entitate de tipul Oferta
 * param tip: tipul imobiliarului(char) (teren, casa, apartament)
 * param suprafata: suprafata imobiliarului (int)
 * param adresa: adresa imobiliarului (char)
 * param pret: pretul imobiliarului ofertei (int)
 * return: Oferta
 */
Oferta* creeazaOferta(char* tip, int suprafata, char* adresa, int pret)
{
    Oferta *a = malloc(sizeof(Oferta));

    int nrc=(int) strlen(tip)+1;
    a->tip=malloc(nrc*sizeof(char));
    strncpy(a->tip, tip,nrc);

    a->suprafata=suprafata;

    nrc=(int) strlen(adresa)+1;
    a->adresa=malloc(nrc*sizeof(char));
    strncpy(a->adresa, adresa,nrc);

    a->pret=pret;

    return a;
}

/*
 * Valideaza o entitate de tipul Oferta
 * param: a (struct)
 * return: 1 - daca tip nu e valid
 *         2 - daca suprafata nu e valida
 *         3 - daca adresa nu e valida
 *         4 - daca pretul nu e valid
 *         0 - daca oferta e valida
 */
int valideazaOferta(Oferta* a)
{
    if(strlen(a->tip)==0)
        return 1;
    if (a->suprafata<0)
        return 2;
    if(strlen(a->adresa)==0)
        return 3;
    if(a->pret<0)
        return 4;
    return 0;
}

/*
 * Sterge elementele entitatii de tipul Oferta
 * param: a (struct)
 */
void destroyOferta(Oferta* a)
{
    /*a->suprafata=-1;
    a->pret=-1;
    a->tip=NULL;
    a->adresa=NULL;*/
    free(a->tip);
    free(a->adresa);
    free(a);
}

Oferta* copyOferta(Oferta* a)
{
    return creeazaOferta(a->tip,a->suprafata,a->adresa,a->pret);
}
void testCreateDestroy() {
    Oferta* a = creeazaOferta("teren",1000, "zorilor", 40000);

    assert(strcmp(a->tip, "teren") == 0);
    assert(strcmp(a->adresa, "zorilor") == 0);
    assert(a->suprafata==1000);
    assert(a->pret==40000);

    destroyOferta(a);

}

void testValideaza() {
    Oferta* a1 = creeazaOferta("teren",1000, "zorilor", 40000);
    assert(valideazaOferta(a1) == 0);

    Oferta* a2 = creeazaOferta("",1000, "zorilor", 40000);
    assert(valideazaOferta(a2) == 1);

    Oferta* a3 = creeazaOferta("teren",-1000, "zorilor", 40000);
    assert(valideazaOferta(a3) == 2);

    Oferta* a4 = creeazaOferta("teren",1000, "", 40000);
    assert(valideazaOferta(a4) == 3);

    Oferta* a5 = creeazaOferta("teren",1000, "zorilor", -40000);
    assert(valideazaOferta(a5) == 4);

    destroyOferta(a1);
    destroyOferta(a2);
    destroyOferta(a3);
    destroyOferta(a4);
    destroyOferta(a5);
}