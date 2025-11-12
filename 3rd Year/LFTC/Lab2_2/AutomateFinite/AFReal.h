
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <cctype>

using namespace std;

class AFReal {
public:
    set<string> states = {"q0", "qSign", "qInt", "qDot", "qFrac"};
    set<char> alphabet = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-', '.'};
    map<pair<string, char>, string> transitions;
    string startState = "q0";
    set<string> finalStates = {"qInt", "qFrac"};

    AFReal();
    bool verificaSecventa(const string& secventa);
};


