#pragma once
#include "Activitate.h"
#include <vector>
#include <string>
using std::vector;
using std::string;

class ValidatorException {
    vector<string > errorMsg;
public:
    explicit ValidatorException(vector<string> msg) : errorMsg{ std::move(msg) } {}
    string get_msg() {
        string full_msg;
        for (const auto& error : errorMsg) {
            full_msg += error + "\n";
        }
        return full_msg;
    }
};

class ValidatorActivitate {
public:
    static void validareActivitate(const Activitate& activitate) {
        vector<string> errors;
        if (activitate.get_titlu().empty()) {
            errors.emplace_back("Titlul nu poate fi vid!");
        }
        if (activitate.get_descriere().empty()) {
            errors.emplace_back("Descrierea nu poate fi vida!");
        }
        if (activitate.get_tip().empty()) {
            errors.emplace_back("Tipul nu poate fi vid!");
        }
        if (activitate.get_durata() <= 0) {
            errors.emplace_back("Durata trebuie sa fie un numar pozitiv!");
        }
        if (!errors.empty()) {
            throw ValidatorException(errors);
        }
    }
};