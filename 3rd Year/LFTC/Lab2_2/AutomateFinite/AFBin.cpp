#include "AFBin.h"

AFBin::AFBin() {
    transitions[{"q0", '0'}] = "q0Zero";

    transitions[{"q0Zero", 'b'}] = "qBinPrefix";
    transitions[{"q0Zero", 'B'}] = "qBinPrefix";

    transitions[{"qBinPrefix", '0'}] = "qBin";
    transitions[{"qBinPrefix", '1'}] = "qBin";

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