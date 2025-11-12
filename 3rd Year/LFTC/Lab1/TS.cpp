#include "TS.h"
#include <fstream>
#include <algorithm>
#include <numeric>
using namespace std;

TS::TS() {

}


void TS::add(const string &atom) {
    tabel.push_back({nextPoz++, atom, -1});
}


void TS::sort() {
    if (tabel.empty()) return;

    std::vector<int> idx;
    idx.reserve((int)tabel.size());
    for (int i = 0; i < (int)tabel.size(); i++) {
        idx.push_back(i);
    }

    int n = (int)idx.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            int a = idx[j];
            int b = idx[j + 1];

            bool ok = false;
            if (tabel[a].atom > tabel[b].atom) {
                ok = true;
            } else if (tabel[a].atom == tabel[b].atom && tabel[a].poz > tabel[b].poz) {
                ok = true;
            }

            if (ok) {
                std::swap(idx[j], idx[j + 1]);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        tabel[i].next = -1;
    }
    for (int k = 0; k + 1 < n; k++) {
        int cur = idx[k];
        int nxt = idx[k + 1];
        tabel[cur].next = nxt;
    }
}


void TS::save(ofstream& outFile) {

    outFile << "| Pozitie | Atom | Next |\n";
    outFile << "| ----------------------|\n";

    for(int i=0;i<tabel.size();i++){
        outFile << "| " << tabel[i].poz << "       | " << tabel[i].atom << "   | " << tabel[i].next << "     |\n";
    }
}

int TS::search(const string& atom) {
    for(const auto& item : tabel){
        if(item.atom == atom){
            return item.poz;
        }
    }
    return -1;
}