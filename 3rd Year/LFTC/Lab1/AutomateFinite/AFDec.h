#include <iostream>
#include <string>
#include <set>
#include <map>
#include <cctype>

using namespace std;

class AFDec {
public:
    set<string> states = {"q0", "qSign", "qInt"};
    set<char> alphabet = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-'};
    map<pair<string, char>, string> transitions;
    string startState = "q0";
    set<string> finalStates = {"qInt"};

    AFDec();
    bool verificaSecventa(const string& secventa);
};
