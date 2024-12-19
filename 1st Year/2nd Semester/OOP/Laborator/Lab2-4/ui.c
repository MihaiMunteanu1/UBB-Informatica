#include <stdio.h>
#include "medicament.h"
#include "myList.h"
#include "service.h"
#include "ui.h"
#include "teste.h"
void updateMed(Farmacie* list)
{
    printf("Introduceti Id-ul:\n");
    int id;
    scanf("%d",&id);
    printf("Introduceti noua concentratie:\n");
    float concentratie;
    scanf("%f",&concentratie);
    printf("Introducceti noul nume:\n");
    char nume[30];
    scanf("%s",nume);
    if (!updateEnt(list,id,nume,concentratie))
        printf("Modificarea a avut loc cu succes!\n");
    else
        printf("Medicamentul cu id-ul dat nu exista!\n");

}
void readMed(Farmacie* list)
{
    printf("Introduceti id:\n");
    int id=-1;
    scanf("%d",&id);
    if (!checkId(list, id))
    {
        printf("Introduceti nume:\n");
        char nume[30];
        scanf("%s", nume);
        printf("Introduceti concentratie:\n");
        float concentratie;
        scanf("%f", &concentratie);
        printf("Introduceti stoc:\n");
        int stoc;
        scanf("%d", &stoc);

        if(addEnt(list, id, nume, concentratie, stoc))
            printf("Produsul a fost adaugat cu succes!\n");
        else
            printf("Medicament invalid!\n");
    }
    else
    {
        addStoc(list, id);
        printf("Stocul a fost actualizat cu succes!\n");
    }


}

void printFarmacie(Farmacie* list)
{
    if(list->lista->dimensiune == 0)
    {
        printf("Nu exista medicamente in farmacie!\n");
        return;
    }
    else{
        for(int i = 0; i< list->lista->dimensiune;i++)
        {
            Medicament* m = get(list->lista,i);
            printf("Id: %d; Nume: %s; Concentratie: %f; Stoc: %d\n",m->id,m->nume,m->concentratie,m->stoc);
        }
    }
}

void deleteMed(Farmacie* list)
{
    printf("Id-ul medicamentului pe care doriti sa il stergeti:\n");
    int id;
    scanf("%d",&id);
    if(!deleteEnt(list,id))
        printf("Acest medicament nu exista!\n");
    else
        printf("Medicament sters cu succes!\n");
}
void destroy(Farmacie *list)
{
    destroyAll(list);
}

void sortNumeCresc(Farmacie* list)
{
    List* f = sortareNume(list);
    for(int i=0;i<f->dimensiune;i++)
    {
        Medicament* m = get(f,i);
        printf("Id: %d; Nume: %s; Concentratie: %f; Stoc: %d\n", m->id, m->nume,m->concentratie, m->stoc);
    }

    destroyList(f);

}

void sortNumeDesc(Farmacie* list)
{
    List* f = sortareNume(list);
    for(int i=f->dimensiune-1;i>=0;i--)
    {
        Medicament* m = get(f,i);
        printf("Id: %d; Nume: %s; Concentratie: %f; Stoc: %d\n", m->id, m->nume,m->concentratie, m->stoc);
    }

    destroyList(f);
}

void sortStocCresc(Farmacie* list)
{
    List* f = sortareStoc(list);
    for(int i=0;i<f->dimensiune;i++)
    {
        Medicament* m = get(f,i);
        printf("Id: %d; Nume: %s; Concentratie: %f; Stoc: %d\n", m->id, m->nume,m->concentratie, m->stoc);
    }

    destroyList(f);
}

void sortStocDesc(Farmacie* list)
{
    List* f = sortareStoc(list);
    for(int i=f->dimensiune-1;i>=0;i--)
    {
        Medicament* m = get(f,i);
        printf("Id: %d; Nume: %s; Concentratie: %f; Stoc: %d\n", m->id, m->nume,m->concentratie, m->stoc);
    }
    destroyList(f);
}

void filtrareStoc(Farmacie* list)
{
    printf("Dati o valoare intrega, pozitiva, nenula:\n");
    int val;
    scanf("%d",&val);
    //List* f = filterStoc(list, val);
    List* f= filterFarmacie(list->lista,filterstoc,&val);
    for(int i=0;i<f->dimensiune;i++)
    {
        Medicament* m = get(f,i);
        printf("Id: %d; Nume: %s; Concentratie: %f; Stoc: %d\n", m->id, m->nume,m->concentratie, m->stoc);
    }

    destroyList(f);

}

void filtrareNume(Farmacie* list)
{
    printf("Dati o litera:");
    char litera[2];
    scanf("%s",litera);
    //List* f = filterNume(list, litera[0]);
    List* f= filterFarmacie(list->lista,filternume,&litera[0]);
    for(int i=0;i<f->dimensiune;i++)
    {
        Medicament* m = get(f,i);
        printf("Id: %d; Nume: %s; Concentratie: %f; Stoc: %d\n", m->id, m->nume,m->concentratie, m->stoc);
    }

    destroyList(f);
}
void filtrareConcentratie(Farmacie* list)
{
    printf("Dati o valoare pozitiva nenula:\n");
    float val;
    scanf("%f",&val);
    //List* f = filterConcentratie(list, val);
    List* f= filterFarmacie(list->lista,filterconcentratie,&val);
    for(int i=0;i<f->dimensiune;i++)
    {
        Medicament* m = get(f,i);
        printf("Id: %d; Nume: %s; Concentratie: %f; Stoc: %d\n", m->id, m->nume,m->concentratie, m->stoc);
    }
    destroyList(f);
}
void undo(Farmacie* list)
{
    int successful = Undo(list);
    if (successful)
        printf("Undo realizat cu succes.\n");
    else
        printf("Nu se mai poate face undo.\n");
}
void run()
{

    Farmacie list = createFarmacie();

    while(1)
    {
        int cmd;
        printf("0. Exit; 1. Adaugare; 2. Modificare; 3.Stergere; 4.Afisare farmacie;\n"
               "5. Sortare nume crescator; 6. Sortare nume descrescator; 7. Sortare stoc crescator;\n"
               "8. Sortare stoc descrescator; 9. Filtrare stoc; 10. Filtrare concentratie; 11. Filtrare nume\n"
               "12. Undo\n");
        scanf("%d",&cmd);
        if(cmd == 1)
            readMed(&list);
        else if(cmd == 2)
            updateMed(&list);
        else if(cmd == 3)
           deleteMed(&list);
        else if(cmd == 4)
            printFarmacie(&list);
        else if(cmd == 5)
            sortNumeCresc(&list);
        else if(cmd == 6)
            sortNumeDesc(&list);
        else if(cmd == 7)
            sortStocCresc(&list);
        else if(cmd == 8)
            sortStocDesc(&list);
        else if(cmd == 9)
            filtrareStoc(&list);
        else if(cmd == 10)
            filtrareConcentratie(&list);
        else if(cmd == 11)
            filtrareNume(&list);
        else if(cmd == 12)
            undo(&list);
        else if(cmd==0)
            {
                break;
            }
    }

    destroy(&list);

}

int main()
{

    runAllTests();


    run();

    return 0;
}
