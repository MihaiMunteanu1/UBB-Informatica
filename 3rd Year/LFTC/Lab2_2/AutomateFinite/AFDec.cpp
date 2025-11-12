
#include "AFDec.h"


AFDec::AFDec() {
    transitions[{"q0", '-'}] = "qSign";

    for (char c = '0'; c <= '9'; c++) {
        transitions[{"q0", c}] = "qInt";
    }

    for (char c = '0'; c <= '9'; c++) {
        transitions[{"qSign", c}] = "qInt";
    }

    for (char c = '0'; c <= '9'; c++) {
        transitions[{"qInt", c}] = "qInt";
    }
}


bool AFDec::verificaSecventa(const string &secventa) {
    string currentState = startState;

    for (const auto& symbol : secventa) {
        if (transitions.find({currentState, symbol}) == transitions.end()) {
            return false;
        }
        currentState = transitions[{currentState, symbol}];
    }

    return finalStates.find(currentState) != finalStates.end();
}