#include <iostream>
#include <vector>

using namespace std;

struct Element{
    int poz;
    string atom;
    int next = -1;

};

class TS {
public:
    TS();
    int search(const string& atom);
    void add(const string& atom);
    void save(ofstream& outFile);
    void sort();

private:
    vector<Element> tabel;
    int nextPoz = 0;
};



