#include <stdio.h>
#include "service.h"
void testAll()
{
    testCreateDestroy();
    testValideaza();
    testCreateVector();
    testIterate();
    testListVoid();
    testSet();
    testCopy();
    testDelete();
    testAddService();
    testFindService();
    testDeleteService();
    testModifyService();
    testFilterSuprafataService();
    testFilterTipService();
    testFilterPretService();
    testSortPretService();
    testSortTipService();
    testUndo();
}
void ui_meniu()
{
    printf("1. Adaugarea de noi oferte\n");
    printf("2. Actualizare oferte\n");
    printf("3. Stergere oferta\n");
    printf("4. Vizualiare oferte\n");
    printf("5. Vizualiare oferte ordonate dupa pret/tip\n");
    printf("6. Vizualiare oferte filtrate dupa un criteriu\n");
    printf("7. Undo\n");
    printf("8. Exit\n");
}
void uiAdd(ManagerOferte* store)
{
    char tip[30], adresa[30];
    int pret, suprafata;
    printf("Tip: ");
    scanf("%s", tip);
    printf("Suprafata: ");
    scanf("%d", &suprafata);
    printf("Adresa: ");
    scanf("%s", adresa);
    printf("Pret: ");
    scanf("%d", &pret);
    int succes=adaugaOferta(store, tip, suprafata, adresa,pret);
    if(!succes)
        printf("Oferta adaugata cu succes!\n");
    else
        printf("Oferta nu este valida!\n");
}
void uiActualizare(ManagerOferte* store)
{
    char tip[30], tip_nou[30], adresa_noua[30];
    int suprafata,suprafata_noua,pret_nou;
    printf("De modificat\n");
    printf("Tip: ");
    scanf("%s", tip);
    printf("Suprafata: ");
    scanf("%d", &suprafata);
    printf("Tip nou: ");
    scanf("%s", tip_nou);
    printf("Suprafata noua: ");
    scanf("%d", &suprafata_noua);
    printf("Adresa noua: ");
    scanf("%s", adresa_noua);
    printf("Pret nou: ");
    scanf("%d", &pret_nou);
    int succes=modificaOferta(store, tip, suprafata, tip_nou, suprafata_noua, adresa_noua, pret_nou);
    if(succes)
        printf("Modificarea s-a efectuat cu succes!\n");
    else
        printf("Modificarea nu s-a efectuat!\n");
}
void uiSterge(ManagerOferte* store)
{
    char tip[30];
    int suprafata;
    printf("Tipul imobiliarului ofertei de sters: ");
    scanf("%s", tip);
    printf("Suprafata imobiliarului ofertei de sters: ");
    scanf("%d", &suprafata);
    int succes=stergeOferta(store, tip, suprafata);
    if(succes)
        printf("Oferta stearsa cu succes!\n");
    else
        printf("Nu exista Oferta de acest fel!\n");
}
void uiOferte(List* l)
{
    if(l->length==0)
        printf("Nu este nicio oferta!\n");
    else
    {
        printf("Oferte: \n");
        for(int i=0; i<size(l); i++) {
            Oferta* a = get(l, i);
            printf("Tip: %s | Suprafata: %d | Adresa: %s | Pret: %d\n", a->tip,a->suprafata,a->adresa,a->pret);
        }
    }
}
void filterOfertaTip(ManagerOferte* store)
{
    printf("Introduceti tipul: ");
    char filterStr[30];
    scanf("%s", filterStr);

    List* filteredList = filterOferteTip(store, filterStr);
    uiOferte(filteredList);
    destroy(filteredList);
}
void filterOfertaSuprafata(ManagerOferte* store)
{
    printf("Introduceti suprafata: ");
    int filterStr;
    scanf("%d", &filterStr);

    List* filteredList = filterOferteSuprafata(store, filterStr);
    uiOferte(filteredList);
    destroy(filteredList);
}
void filterOfertaPret(ManagerOferte* store)
{
    printf("Introduceti pretul: ");
    int filterStr;
    scanf("%d", &filterStr);

    List* filteredList = filterOfertePret(store, filterStr);
    uiOferte(filteredList);
    destroy(filteredList);
}
void uiSortPretCrescator(ManagerOferte * store)
{
    List* listaSortata = sortOferteByPret(store);
    uiOferte(listaSortata);
    destroy(listaSortata);
}
void uiSortTipCrescator(ManagerOferte * store)
{
    List* listaSortata = sortOferteByTip(store);
    uiOferte(listaSortata);
    destroy(listaSortata);
}
void uiUndo(ManagerOferte* s) {
    int successful = undo(s);
    if (successful)
        printf("Undo realizat cu succes.\n");
    else
        printf("Nu se mai poate face undo.\n");
}
void run()
{
    ManagerOferte store = createManagerOferte();
    int optiune,ok=1;
    while(ok)
    {
        ui_meniu();
        printf(">>>");
        scanf("%d",&optiune);
        switch(optiune)
        {
            case 1:
                uiAdd(&store);
                break;
            case 2:
                uiActualizare(&store);
                break;
            case 3:
                uiSterge(&store);
                break;
            case 4:
                uiOferte(store.allOferte);
                break;
            case 5:
                printf("1. Tip\n2. Pret\n>>>");
                int optiune2;
                scanf("%d",&optiune2);
                switch(optiune2)
                {
                    case 1:
                        uiSortTipCrescator(&store);
                        break;
                    case 2:
                        uiSortPretCrescator(&store);
                        break;
                    default:
                        printf("Optiune invalida\n");
                        break;
                }
                break;
            case 6:
                printf("1. Suprafata\n2. Tip\n3. Pret\n>>>");
                int optiune22;
                scanf("%d",&optiune22);
                switch(optiune22)
                {
                    case 1:
                        filterOfertaSuprafata(&store);
                        break;
                    case 2:
                        filterOfertaTip(&store);
                        break;
                    case 3:
                        filterOfertaPret(&store);
                        break;
                    default:
                        printf("Optiune invalida\n");
                        break;
                }
                break;
            case 7:
                uiUndo(&store);
                break;
            case 8:
                ok = 0;
                break;
            default:
                printf("Optiunea nu este valida!\n");
                break;
        }
    }
    destroyManagerOferte(&store);
}
int main()
{
    testAll();
    run();
    return 0;
}