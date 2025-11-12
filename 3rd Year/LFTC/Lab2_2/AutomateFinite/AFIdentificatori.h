
#include <iostream>
#include <string>
#include <set>
#include <map>

using namespace std;

class AFIdentificatori {
public:
    set<string> states = {"q0", "q1"};
    set<char> alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                          'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                          '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    map<pair<string, char>, string> transitions;
    string startState = "q0";
    set<string> finalStates = {"q1"};

    AFIdentificatori();

    bool verificaSecventa(const string& secventa);
};


