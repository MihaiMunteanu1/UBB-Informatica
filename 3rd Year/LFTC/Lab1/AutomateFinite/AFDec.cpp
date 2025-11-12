
#include "AFDec.h"


AFDec::AFDec() {
    // q0 -> qSign on '-'
    transitions[{"q0", '-'}] = "qSign";

    // q0 -> qInt on digits 0-9
    for (char c = '0'; c <= '9'; c++) {
        transitions[{"q0", c}] = "qInt";
    }

    // qSign -> qInt on digits 0-9
    for (char c = '0'; c <= '9'; c++) {
        transitions[{"qSign", c}] = "qInt";
    }

    // qInt -> qInt on digits 0-9 (more digits)
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