#include "AFBin.h"

AFBin::AFBin() {
    // q0 -> q0Zero on '0'
    transitions[{"q0", '0'}] = "q0Zero";

    // q0Zero -> qBinPrefix on 'b' or 'B'
    transitions[{"q0Zero", 'b'}] = "qBinPrefix";
    transitions[{"q0Zero", 'B'}] = "qBinPrefix";

    // qBinPrefix -> qBin on '0' or '1'
    transitions[{"qBinPrefix", '0'}] = "qBin";
    transitions[{"qBinPrefix", '1'}] = "qBin";

    // qBin -> qBin on '0' or '1' (self-loop for more digits)
    transitions[{"qBin", '0'}] = "qBin";
    transitions[{"qBin", '1'}] = "qBin";
}

bool AFBin::verificaSecventa(const string &secventa) {
    string currentState = startState;

    for (const auto& symbol : secventa) {
        if (transitions.find({currentState, symbol}) == transitions.end()) {
            return false;
        }
        currentState = transitions[{currentState, symbol}];
    }

    return finalStates.find(currentState) != finalStates.end();
}