#include "ui.h"
#include <iostream>
using std::cin;
using std::cout;
void ui::adaugaActivitate() {
    string titlu;
    string descriere;
    string tip;
    int durata;
    cout << "Titlu: ";
    cin >> titlu;
    cout << "\nDescriere: ";
    cin >> descriere;
    cout << "\nTip: ";
    cin >> tip;
    cout << "\nDurata: ";
    cin >> durata;
    try {
        serv.add_activitate(titlu, descriere, tip, durata);
        cout << "Activitate adaugata cu succes\n";
    }
    catch (RepoException &ex) {
        cout << ex.getMessage();
    }
}
void ui::actualizeazaActivitate() {
    string titlu;
    string descriere;
    string tip;
    int durata;
    cout << "Titlu: ";
    cin >> titlu;
    cout << "\nDescriere noua: ";
    cin >> descriere;
    cout << "\nTip nou: ";
    cin >> tip;
    cout << "\nDurata noua: ";
    cin >> durata;
    try {
        serv.actualizare_activitate(titlu, descriere, tip, durata);
        cout << "Activitate actualizata cu succes\n";
    }
    catch (RepoException &ex) {
        cout << ex.getMessage();
    }
}
void ui::stergeActivitate() {
    string titlu;
    cout << "Titlu: ";
    cin >> titlu;
    try {
        serv.stergere_activitate(titlu);
        cout << "Activitate stearsa cu succes\n";
    }
    catch (RepoException &ex) {
        cout << ex.getMessage();
    }
}
void ui::afiseazaActivitati() {
    auto activitati = serv.get_all();
    if (activitati.size() == 0) {
        cout << "Nu exista activitati!\n";
    } else {
        for (const auto &activitate: activitati) {
            cout << activitate.get_titlu() << " " << activitate.get_descriere() << " " << activitate.get_tip() << " "
                 << activitate.get_durata() << "\n";
        }
    }
}
void ui::afiseazaActivitatiFiltrate() {
    cout<<"1. Filtrare tip\n2. Filtrare descriere\n>>>";
    int cmd1;
    cin>>cmd1;
    if(cmd1==1){
        string tip;
        cout<<"Tip: ";
        cin>>tip;
        auto activitati=serv.filtrare_tip(tip);
        if(activitati.size()==0){
            cout<<"Nu exista activitati!\n";
        }else{
            for(const auto& activitate:activitati){
                cout<<activitate.get_titlu()<<" "<<activitate.get_descriere()<<" "<<activitate.get_tip()<<" "<<activitate.get_durata()<<"\n";
            }
        }
    }
    if(cmd1==2){
        string descriere;
        cout<<"Descriere: ";
        cin>>descriere;
        auto activitati=serv.filtrare_descriere(descriere);
        if(activitati.size()==0){
            cout<<"Nu exista activitati!\n";
        }else{
            for(const auto& activitate:activitati){
                cout<<activitate.get_titlu()<<" "<<activitate.get_descriere()<<" "<<activitate.get_tip()<<" "<<activitate.get_durata()<<"\n";
            }
        }
    }
}
void ui::afiseazaActivitatiSortate() {
    cout<<"1. Sortare dupa titlu\n2. Sortare dupa descriere\n3. Sortare dupa tip si durata\n>>>";
    int cmd1;
    cin>>cmd1;
    if(cmd1==1){
        auto activitati=serv.sortare_titlu();
        if(activitati.size()==0){
            cout<<"Nu exista activitati!\n";
        }else{
            for(const auto& activitate:activitati){
                cout<<activitate.get_titlu()<<" "<<activitate.get_descriere()<<" "<<activitate.get_tip()<<" "<<activitate.get_durata()<<"\n";
            }
        }
    }
    if(cmd1==2){
        auto activitati=serv.sortare_descriere();
        if(activitati.size()==0){
            cout<<"Nu exista activitati!\n";
        }else{
            for(const auto& activitate:activitati){
                cout<<activitate.get_titlu()<<" "<<activitate.get_descriere()<<" "<<activitate.get_tip()<<" "<<activitate.get_durata()<<"\n";
            }
        }
    }
    if(cmd1==3){
        auto activitati=serv.sortare_tip_durata();
        if(activitati.size()==0){
            cout<<"Nu exista activitati!\n";
        }else{
            for(const auto& activitate:activitati){
                cout<<activitate.get_titlu()<<" "<<activitate.get_descriere()<<" "<<activitate.get_tip()<<" "<<activitate.get_durata()<<"\n";
            }
        }
    }
}
void ui::uiCautare() {
    string titlu;
    cout << "Titlu: ";
    cin >> titlu;
    auto activitati = serv.get_all();
    for (const auto &activitate: activitati) {
        if (activitate.get_titlu() == titlu) {
            cout << activitate.get_titlu() << " " << activitate.get_descriere() << " " << activitate.get_tip()
                 << " " << activitate.get_durata() << "\n";
        }
    }
}
void ui::run() {
    while (true) {
        cout << "1. Adauga\n2. Actualizare\n3. Sterge\n4. Print\n5. Filtrare\n"
                "6. Sortare\n7. Cautare\n0. Exit\nComand:";
        int cmd = 0;
        cin >> cmd;
        if (cmd == 0) {
            break;
        }
        if (cmd == 1) {
            adaugaActivitate();
        }
        if (cmd == 2) {
            actualizeazaActivitate();
        }
        if (cmd == 3) {
            stergeActivitate();
        }
        if (cmd == 4) {
            afiseazaActivitati();
        }
        if (cmd == 5) {
            afiseazaActivitatiFiltrate();
        }
        if (cmd == 6) {
            afiseazaActivitatiSortate();
        }
        if (cmd == 7) {
            uiCautare();
        }
    }
}
