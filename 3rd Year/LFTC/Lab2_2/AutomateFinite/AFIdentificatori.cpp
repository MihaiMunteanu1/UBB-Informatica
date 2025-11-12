
#include "AFIdentificatori.h"

AFIdentificatori::AFIdentificatori() {
    for (char letter = 'a'; letter <= 'z'; ++letter) {
        transitions[{"q0", letter}] = "q1";
        transitions[{"q1", letter}] = "q1";
    }
    for (char letter = 'A'; letter <= 'Z'; ++letter) {
        transitions[{"q0", letter}] = "q1";
        transitions[{"q1", letter}] = "q1";
    }

    for (char digit = '0'; digit <= '9'; ++digit) {
        transitions[{"q1", digit}] = "q1";
    }
}

bool AFIdentificatori::verificaSecventa(const string& secventa) {
    string currentState = startState;

    for (const auto& symbol : secventa) {
        if (transitions.find({currentState, symbol}) == transitions.end()) {
            return false;
        }
        currentState = transitions[{currentState, symbol}];
    }

    return finalStates.find(currentState) != finalStates.end();
}