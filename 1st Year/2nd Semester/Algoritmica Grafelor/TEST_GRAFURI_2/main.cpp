#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <fstream>

using namespace std;

class Nod {
public:
    char c;
    int fr;
    Nod* st;
    Nod* dr;
    Nod(char caracter, int frecv) : c(caracter), fr(frecv), st(nullptr), dr(nullptr) {}
};

class Comparator {
public:
    bool operator()(Nod* stanga, Nod* dreapta) {
        return stanga->fr > dreapta->fr;
    }
};

void generareCoduri(Nod* rad, const string& cod, vector<pair<char, string>>& coduriHuffman) {
    if (!rad)
        return;
    if (!rad->st && !rad->dr) {
        coduriHuffman.push_back({rad->c, cod});
    }
    generareCoduri(rad->st, cod + "0", coduriHuffman);
    generareCoduri(rad->dr, cod + "1", coduriHuffman);
}

Nod* ArboreHuffman(const string& mesaj) {
    vector<int> fr(256, 0);
    for (char c : mesaj) {
        fr[c]++;
    }

    priority_queue<Nod*, vector<Nod*>, Comparator> pq;
    for (int i = 0; i < 256; ++i) {
        if (fr[i] > 0) {
            pq.push(new Nod(i, fr[i]));
        }
    }

    while (pq.size() != 1) {
        Nod* stanga = pq.top(); pq.pop();
        Nod* dreapta = pq.top(); pq.pop();
        Nod* nou = new Nod('\0', stanga->fr + dreapta->fr);
        nou->st = stanga;
        nou->dr = dreapta;
        pq.push(nou);
    }

    return pq.top();
}

string comprima(const string& mesaj, const vector<pair<char, string>>& coduriHuffman) {
    string mesaj_comprimat;
    for (char c : mesaj) {
        for (const auto& pereche : coduriHuffman) {
            if (pereche.first == c) {
                mesaj_comprimat += pereche.second;
                break;
            }
        }
    }
    return mesaj_comprimat;
}

string decomprima(const string& mesaj_comprimat, Nod* radacina) {
    string mesaj_decomprimat;
    Nod* curr = radacina;
    for (char cif : mesaj_comprimat) {
        if (cif == '0')
            curr = curr->st;
        else
            curr = curr->dr;
        if (!curr->st && !curr->dr) {
            mesaj_decomprimat += curr->c;
            curr = radacina;
        }
    }
    return mesaj_decomprimat;
}

int main(int argc,char* argv[]) {
    ifstream f(argv[1]);
    ofstream g(argv[2]);
    string mesaj;
    f>>mesaj;

    vector<pair<char, string>> Huffman;

    Nod* rad = ArboreHuffman(mesaj);

    generareCoduri(rad, "", Huffman);

    string mesaj_comprimat = comprima(mesaj, Huffman);
    g<< mesaj_comprimat << endl;

    string mesaj_decomprimat = decomprima(mesaj_comprimat, rad);
    g<< mesaj_decomprimat << endl;

    return 0;
}
