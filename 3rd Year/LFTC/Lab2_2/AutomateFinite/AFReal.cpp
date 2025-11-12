
#include "AFReal.h"

AFReal::AFReal() {
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

    transitions[{"qInt", '.'}] = "qDot";

    for (char c = '0'; c <= '9'; c++) {
        transitions[{"qDot", c}] = "qFrac";
    }

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