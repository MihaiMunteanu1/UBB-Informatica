#pragma once
#include <stdlib.h>
typedef struct{
    char* tip;
    int suprafata;
    char* adresa;
    int pret;
}Oferta;

/*
* Creeaza o entitate de tipul Oferta
* param tip: tipul imobiliarului(char) (teren, casa, apartament)
* param suprafata: suprafata imobiliarului (int)
* param adresa: adresa imobiliarului (char)
* param pret: pretul imobiliarului ofertei (int)
* return: Oferta
*/

Oferta* creeazaOferta(char* tip, int suprafata, char* adresa, int pret);
/*
 * Valideaza o entitate de tipul Oferta
 * param: a (struct)
 * return: 1 - daca tip nu e valid
 *         2 - daca suprafata nu e valida
 *         3 - daca adresa nu e valida
 *         4 - daca pretul nu e valid
 *         0 - daca oferta e valida
 */
int valideazaOferta(Oferta* a);

/*
 * Sterge elementele entitatii de tipul Oferta
 * Dealocate memory occupied by oferta
 * param: a (struct)
 */
void destroyOferta(Oferta* a);


Oferta* copyOferta(Oferta* a);

void testCreateDestroy();

void testValideaza();


