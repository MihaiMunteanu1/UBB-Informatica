#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

class AF {
public:
    set<string> stari;
    set<char> alfabet;
    map<pair<string, char>, string> tranzitii;
    string startStare;
    set<string> finalStari;
    bool determinist;
};


void readData(AF& af) {
    af.determinist=true;

    int nrStari, nrStariFinale, nrTranzitii;
    string state;

    cout << "Nr stari: ";
    cin >> nrStari;
    cout << "Starile: ";
    for (int i = 0; i < nrStari; ++i) {
        cin >> state;
        af.stari.insert(state);
    }

    int alfabetSize;
    cout << "Dimensiunea alfabetului: ";
    cin >> alfabetSize;
    cout << "Alfabetul: ";
    for (int i = 0; i < alfabetSize; ++i) {
        char symbol;
        cin >> symbol;
        af.alfabet.insert(symbol);
    }

    cout << "Numar de tranzitii: ";
    cin >> nrTranzitii;
    cout << "Tranzitiile: " << endl;
    for (int i = 0; i < nrTranzitii; ++i) {
        string currentState, nextState;
        char symbol;
        cin >> currentState >> symbol >> nextState;

        if (af.tranzitii.find({currentState, symbol}) != af.tranzitii.end()) {
            af.determinist = false;
        }

        af.tranzitii[{currentState, symbol}] = nextState;
    }

    cout << "Starea initiala: ";
    cin >> af.startStare;

    cout << "Nr stari finale: ";
    cin >> nrStariFinale;
    cout << "Starile finale: ";
    for (int i = 0; i < nrStariFinale; ++i) {
        cin >> state;
        af.finalStari.insert(state);
    }
}

void readDataFile(AF& af, const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return;
    }
    af.determinist=true;

    int nrStari, nrStariFinale, nrTranzitii;
    string state;

    file >> nrStari;
    for (int i = 0; i < nrStari; ++i) {
        file >> state;
        af.stari.insert(state);
    }

    int alfabetSize;
    file >> alfabetSize;
    for (int i = 0; i < alfabetSize; ++i) {
        char symbol;
        file >> symbol;
        af.alfabet.insert(symbol);
    }

    file >> nrTranzitii;
    for (int i = 0; i < nrTranzitii; ++i) {
        string currentState, nextState;
        char symbol;
        file >> currentState >> symbol >> nextState;

        if (af.tranzitii.find({currentState, symbol}) != af.tranzitii.end()) {
            af.determinist=false;
        }
        af.tranzitii[{currentState, symbol}] = nextState;
    }

    file >> af.startStare;

    file >> nrStariFinale;
    for (int i = 0; i < nrStariFinale; ++i) {
        file >> state;
        af.finalStari.insert(state);
    }

    file.close();
}

void afisareStari(const AF& af) {
    cout << "Starile: ";
    for (const auto& state : af.stari) {
        cout << state << " ";
    }
    cout << endl;
}

void afisareAlfabet(const AF& af) {
    cout << "Alfabetul: ";
    for (const auto& symbol : af.alfabet) {
        cout << symbol << " ";
    }
    cout << endl;
}

void afisareTranzitii(const AF& af) {
    cout << "Tranzitiile: " << endl;
    for (const auto& transition : af.tranzitii) {
        cout << "(" << transition.first.first << ", " << transition.first.second << ") -> " << transition.second << endl;
    }
}

void afisareStariFinale(const AF& af) {
    cout << "Starile finale: ";
    for (const auto& state : af.finalStari) {
        cout << state << " ";
    }
    cout << endl;
}

bool checkSecventa(const AF& af, const string& secventa) {
    string currentState = af.startStare;

    for (const auto& symbol : secventa) {
        if (af.tranzitii.find({currentState, symbol}) == af.tranzitii.end()) {
            return false;
        }
        currentState = af.tranzitii.at({currentState, symbol});
    }

    return af.finalStari.find(currentState) != af.finalStari.end();
}

string prefixLung(const AF& af, const string& secventa) {
    string currentState = af.startStare;
    string longestPrefix="";
    string currentPrefix="";

    for (const auto& symbol : secventa) {
        if (af.tranzitii.find({currentState, symbol}) == af.tranzitii.end()) {
            break;
        }
        currentState = af.tranzitii.at({currentState, symbol});
        currentPrefix += symbol;
        if (af.finalStari.find(currentState) != af.finalStari.end()) {
            longestPrefix = currentPrefix;
        }
    }

    return longestPrefix;
}

void afisareMeniu() {
    cout << "1:Multimea starilor" << endl;
    cout << "2:Alfabetul" << endl;
    cout << "3:Tranzitiile" << endl;
    cout << "4:Multimea starilor finale" << endl;
    cout << "5:Verificare secventa" << endl;
    cout << "6:Cel mai lung prefix acceptat" << endl;
    cout << "0:Exit" << endl;
}


int main() {
    AF af;
    int optiune;

    cout << "Read file/tastatura (1/2): ";
    cin >> optiune;

    if (optiune == 1) {
        readDataFile(af, "cst.txt");
    } else {
        readData(af);
    }

    while (1) {
        afisareMeniu();
        cout << ">>>";
        cin >> optiune;

        if (optiune == 0) {
            break;
        }

        switch (optiune) {
            case 1:
                afisareStari(af);
                break;
            case 2:
                afisareAlfabet(af);
                break;
            case 3:
                afisareTranzitii(af);
                break;
            case 4:
                afisareStariFinale(af);
                break;
            case 5: {
                if(!af.determinist){
                    cout<<"AF-ul nu e determinist."<<endl;
                    break;
                }
                string secventa;
                cout << "Introduceti secventa de verificat: ";
                cin >> secventa;
                if (checkSecventa(af, secventa)) {
                    cout << "Secventa acceptata." << endl;
                } else {
                    cout << "Secventa nu e acceptata." << endl;
                }
                break;
            }
            case 6: {
                if(!af.determinist){
                    cout<<"AF-ul nu e determinist."<<endl;
                    break;
                }
                string secventa;
                cout << "Introduceti secventa: ";
                cin >> secventa;
                string prefix = prefixLung(af, secventa);
                cout << "Cel mai lung prefix acceptat: " << prefix << endl;
                break;
            }
            default:
                cout << "Optiune invalida!" << endl;
                break;
        }
    }

    return 0;
}
