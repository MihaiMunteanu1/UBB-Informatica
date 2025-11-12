
#include "AFReal.h"

AFReal::AFReal() {
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

    // qInt -> qInt on digits 0-9 (more integer digits)
    for (char c = '0'; c <= '9'; c++) {
        transitions[{"qInt", c}] = "qInt";
    }

    // qInt -> qDot on '.'
    transitions[{"qInt", '.'}] = "qDot";

    // qDot -> qFrac on digits 0-9
    for (char c = '0'; c <= '9'; c++) {
        transitions[{"qDot", c}] = "qFrac";
    }

    // qFrac -> qFrac on digits 0-9 (more fractional digits)
    for (char c = '0'; c <= '9'; c++) {
        transitions[{"qFrac", c}] = "qFrac";
    }
}


bool AFReal::verificaSecventa(const string& secventa) {
    string currentState = startState;

    for (const auto& symbol : secventa) {
        if (transitions.find({currentState, symbol}) == transitions.end()) {
            return false;
        }
        currentState = transitions[{currentState, symbol}];
    }

    return finalStates.find(currentState) != finalStates.end();
}