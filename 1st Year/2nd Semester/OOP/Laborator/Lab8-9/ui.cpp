#include "ui.h"
#include <iostream>
#include <unordered_map>
#include <algorithm>

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
    catch (ValidatorException &ex) {
        cout << ex.get_msg();
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
    if (activitati.empty()) {
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
        if(activitati.empty()){
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
        if(activitati.empty()){
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
        auto activitati=serv.sortare(sortare_titlu);
        if(activitati.empty()){
            cout<<"Nu exista activitati!\n";
        }else{
            for(const auto& activitate:activitati){
                cout<<activitate.get_titlu()<<" "<<activitate.get_descriere()<<" "<<activitate.get_tip()<<" "<<activitate.get_durata()<<"\n";
            }
        }
    }
    if(cmd1==2){
        auto activitati=serv.sortare(sortare_descriere);
        if(activitati.empty()){
            cout<<"Nu exista activitati!\n";
        }else{
            for(const auto& activitate:activitati){
                cout<<activitate.get_titlu()<<" "<<activitate.get_descriere()<<" "<<activitate.get_tip()<<" "<<activitate.get_durata()<<"\n";
            }
        }
    }
    if(cmd1==3){
        auto activitati=serv.sortare(sortare_tip_durata);
        if(activitati.empty()){
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
    auto it=std::find_if(activitati.begin(), activitati.end(),[titlu](const Activitate &activitate) {
        return activitate.get_titlu() == titlu;
    });
    /*for (const auto &activitate: activitati) {
        if (activitate.get_titlu() == titlu) {
            cout << activitate.get_titlu() << " " << activitate.get_descriere() << " " << activitate.get_tip()
                 << " " << activitate.get_durata() << "\n";
        }
    }*/
    if(it!=activitati.end()){
        cout << it->get_titlu() << " " << it->get_descriere() << " " << it->get_tip() << " " << it->get_durata() << "\n";
    }
    else{
        cout<<"Activitatea nu exista!\n";
    }
}
void ui::uiDictionar() {
    std::unordered_map<std::string, int> dictionar;
    serv.afisare_dictionar(dictionar);
    for (const auto& [key, value] : dictionar)
        std::cout << key << " " << value << "\n";
}
void ui::run() {
    while (true) {
        cout << "1. Adauga\n2. Actualizare\n3. Sterge\n4. Print\n5. Filtrare\n"
                "6. Sortare\n7. Cautare\n8. Lista activitati de efectuat\n"
                "9. Afisare dictionar\n10. Undo\n0. Exit\nComand:";
        int cmd = 0;
        cin >> cmd;
        switch (cmd) {
            case 1:
                adaugaActivitate();
                break;
            case 2:
                actualizeazaActivitate();
                break;
            case 3:
                stergeActivitate();
                break;
            case 4:
                afiseazaActivitati();
                break;
            case 5:
                afiseazaActivitatiFiltrate();
                break;
            case 6:
                afiseazaActivitatiSortate();
                break;
            case 7:
                uiCautare();
                break;
            case 8:
                menuManager();
                int cmd2;
                cin >> cmd2;
                switch (cmd2)
                {
                    case 1:
                        uiAddToListaActivitati();
                        break;
                    case 2:
                        uiEmptyListaActivitati();
                        break;
                    case 3:
                        uiAddRandom();
                        break;
                    case 4:
                        uiPrint();
                        break;
                    case 5:
                        uiExport();
                        break;
                    case 0:
                        break;
                    default:
                        cout << "\nComanda invalida!";
                        break;
                }
                break;
            case 9:
                uiDictionar();
                break;
            case 10:
                try{
                    serv.undo();
                    cout<<"Undo realizat cu succes!\n";
                }
                catch(RepoException& ex){
                    cout<<ex.getMessage()<<std::endl;
                }
                break;
            case 0:
                return;
            default:
                cout << "Optiune invalida!\n";
                break;
        }
    }
}

void ui::menuManager(){
    cout<<"1. Adauga activitate\n"
          "2. Goleste lista\n"
          "3. Genereaza lista\n"
          "4. Print\n"
          "5. Export\n"
          "0. Exit\nCommand: ";
}

void ui::uiAddToListaActivitati() {
    string titlu;
    cout << " Titlu: ";
    cin >> titlu;
    try {
        serv.add_to_lista_activitati(titlu);
        cout << "Activitate adaugata cu succes\n";
    }
    catch (RepoException &ex) {
        cout << ex.getMessage();
    }
    catch (ValidatorException &ex) {
        cout << ex.get_msg();
    }
    cout<<"\n"<<serv.getAllListaActivitai().size()<<"\n";

}

void ui::uiEmptyListaActivitati() {
    serv.clearAllListaActivitati();
    cout<<"S-au sters toate activitatile din lista de activitati.\n";
    cout<<"\n"<<serv.getAllListaActivitai().size()<<"\n";

}

void ui::uiAddRandom() {
    int howMany;
    cout << "Cate activitati sa se adauge: ";
    cin >> howMany;
    try{
        int howManyAdded = serv.addRandomToListaActivitati(howMany);
        cout << "S-au adaugat " << howManyAdded << " activitati in lista de activitati.\n";
    }
    catch (RepoException &ex) {
        cout << ex.getMessage();
    }
    cout<<"\n"<<serv.getAllListaActivitai().size()<<"\n";

}

void ui::uiPrint() {
    auto activitati = serv.getAllListaActivitai();
    if (activitati.empty()) {
        cout << "Nu exista activitati in lista de activitati!\n";
    } else {
        for (const auto &activitate: activitati) {
            cout << activitate.get_titlu() << " " << activitate.get_descriere() << " " << activitate.get_tip() << " "
                 << activitate.get_durata() << "\n";
        }
    }
    cout<<"\n"<<serv.getAllListaActivitai().size()<<"\n";
}

void ui::uiExport() {
    string fileName;
    cout << "Nume fisier: ";
    cin >> fileName;
    cout<<"Mod:\n1. HTML\n2. CVS\n>>>";
    int cmd1;
    cin>>cmd1;
    if(cmd1==1){
        serv.exporttofileHTML(fileName);
        cout << "Export realizat cu succes!\n";
    }
    else if(cmd1==2){
        serv.exporttofileCVS(fileName);
        cout << "Export realizat cu succes!\n";
    }
    else{
        cout<<"Comanda invalida!\n";
    }
    cout<<"\n"<<serv.getAllListaActivitai().size()<<"\n";

}
