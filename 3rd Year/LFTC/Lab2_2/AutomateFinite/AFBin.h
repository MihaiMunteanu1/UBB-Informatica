#include <iostream>
#include <string>
#include <set>
#include <map>
#include <cctype>

using namespace std;

class AFBin {
public:
    set<string> states = {"q0", "q0Zero", "qBinPrefix", "qBin"};
    set<char> alphabet = {'0', '1', 'b', 'B'};
    map<pair<string, char>, string> transitions;
    string startState = "q0";
    set<string> finalStates = {"q0Zero", "qBin"};

    AFBin();
    bool verificaSecventa(const string& secventa);
};



