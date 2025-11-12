#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <cctype>
#include "TS.h"
#include "FIP.cpp"
#include "AutomateFinite/AFBin.h"
#include "AutomateFinite/AFReal.h"
#include "AutomateFinite/AFIdentificatori.h"
#include "AutomateFinite/AFDec.h"

using namespace std;

bool checkErori = false;


void loadKeywords(vector<string>& keywords) {
    ifstream keyFile("../files/keywords.txt");
    if (keyFile) {
        string line;
        while (getline(keyFile, line)) {
            size_t colonPos = line.find(" : ");
            if (colonPos != string::npos) {
                string keyword = line.substr(0, colonPos);
                keywords.push_back(keyword);
            }
        }
        keyFile.close();
    }
}

bool isKeyword(const string& word, const vector<string>& keywords) {
    return find(keywords.begin(), keywords.end(), word) != keywords.end();
}

int getKeywordCode(const string& word, const vector<string>& keywords) {
    auto it = find(keywords.begin(), keywords.end(), word);
    if (it != keywords.end()) {
        return static_cast<int>(distance(keywords.begin(), it));
    }
    return -1;
}

//void analyzeCode(const string& code, vector<string>& keywords, TS& ts, FIP& fip) {
//    AFIdentificatori afi;
//    AFBin afb;
//    AFReal afr;
//    AFDec afd;
//
//    int i = 0;
//    int line = 1;
//
//    while (i < code.length()) {
//        if (isspace(code[i])) {
//            if (code[i] == '\n') {
//                line++;
//            }
//            i++;
//            continue;
//        }
//
//        if (i + 1 < code.length() && code[i] == '/' && code[i + 1] == '/') {
//            while (i < code.length() && code[i] != '\n') {
//                i++;
//            }
//            continue;
//        }
//
//        if (i + 1 < code.length() && code[i] == '/' && code[i + 1] == '*') {
//            i += 2;
//            while (i + 1 < code.length() && !(code[i] == '*' && code[i + 1] == '/')) {
//                if (code[i] == '\n') line++;
//                i++;
//            }
//            if (i + 1 < code.length()) i += 2;
//            continue;
//        }
//
//        if (code[i] == '"') {
//            i++; // skip opening quote
//            while (i < code.length() && code[i] != '"') {
//                if (code[i] == '\\' && i + 1 < code.length()) {
//                    i += 2; // skip escape sequence
//                } else {
//                    i++;
//                }
//            }
//            if (i < code.length()) i++; // skip closing quote
//            continue;
//        }
//
//        // Handle separators
//        if (isSeparator(code[i])) {
//            string sep(1, code[i]);
//            int keywordCode = getKeywordCode(sep, keywords);
//            if (keywordCode != -1) {
//                fip.add(keywordCode, 0);
//            } else {
//                fip.add(-1, 0); // unknown separator
//            }
//            i++;
//            continue;
//        }
//
//        // Handle operators
//        if (isOperator(code[i])) {
//            string op = getOperator(code, i);
//            int keywordCode = getKeywordCode(op, keywords);
//            if (keywordCode != -1) {
//                fip.add(keywordCode, 0);
//            } else {
//                fip.add(-1, 0); // unknown operator
//            }
//            i++;
//            continue;
//        }
//
//        // Try to find the longest valid token starting from current position
//        string token = "";
//        int maxValidLength = 0;
//        string bestToken = "";
//        int startPos = i;
//
//        // Build token character by character and keep track of longest valid match
//        int j = i;
//        while (j < code.length() && !isspace(code[j]) &&
//               !isSeparator(code[j]) && !isOperator(code[j]) &&
//               code[j] != '"' && !(code[j] == '/' && j + 1 < code.length() &&
//                                   (code[j + 1] == '/' || code[j + 1] == '*'))) {
//            token += code[j];
//
//            // Test if current token is valid
//            if (isKeyword(token, keywords) || afi.verificaSecventa(token) ||
//            afd.verificaSecventa(token) ||
//            afb.verificaSecventa(token) ||
//                afr.verificaSecventa(token)) {
//                maxValidLength = token.length();
//                bestToken = token;
//            }
//            j++;
//        }
//
//        if (maxValidLength > 0) {
//            // We found a valid token, use it
//            token = bestToken;
//            i = startPos + maxValidLength;
//        } else if (!token.empty()) {
//            // No valid token found, but we have characters - treat as error
//            i = j; // consume all characters
//        } else {
//            // Empty token, skip character
//            i++;
//            continue;
//        }
//
//        if (token.empty()) {
//            continue;
//        }
//
//        // Process the found token
//        bool isValid = false;
//
//        // Check if it's a keyword
//        if (isKeyword(token, keywords)) {
//            int keywordCode = getKeywordCode(token, keywords);
//            fip.add(keywordCode, 0);
//            isValid = true;
//        }
//            // Check if it's an identifier
//        else if (afi.verificaSecventa(token)) {
//            if (token.length() >= 8) {
//                if (!checkErori) {
//                    cout << "Eroare: Identificator prea lung: " << token << " la linia " << line << endl;
//                    checkErori = true;
//                }
//            } else {
//                int posTS = ts.search(token);
//                if (posTS == -1) {
//                    ts.add(token);
//                    posTS = ts.search(token);
//                }
//                fip.add(0, posTS); // code 0 = ID
//                isValid = true;
//            }
//        }
//
//            // Check if it's a binary constant
//        else if (afb.verificaSecventa(token)) {
//            fip.add(1, 0); // code 1 = CONST
//            isValid = true;
//        }
//
//        else if(afd.verificaSecventa(token)){
//            fip.add(1,0);
//            isValid = true;
//        }
//            // Check if it's a real constant
//        else if (afr.verificaSecventa(token)) {
//            fip.add(1, 0); // code 1 = CONST
//            isValid = true;
//        }
//
//        if (!isValid) {
//            if (!checkErori) {
//                cout << "Eroare: Token invalid: " << token << " la linia " << line << endl;
//                checkErori = true;
//            }
//        }
//    }
//}

void analyzeCode(const string& code, vector<string>& rez, vector<string>& keywords, TS& ts, FIP& fip) {
    AFIdentificatori afi;
    AFBin afb;
    AFReal afr;
    AFDec afd;

    int i = 0;
    int line = 1;

    while (i < code.length()) {
        if (isspace(code[i])) {
            if (code[i] == '\n') {
                line++;
            }
            i++;
            continue;
        }

        // comentarii
        if (i + 1 < code.length() && code[i] == '/' && code[i + 1] == '/') {
            while (i < code.length() && code[i] != '\n') {
                i++;
            }
            continue;
        }

        if (i + 1 < code.length() && code[i] == '/' && code[i + 1] == '*') {
            i += 2;
            while (i + 1 < code.length() && !(code[i] == '*' && code[i + 1] == '/')) {
                if (code[i] == '\n') line++;
                i++;
            }
            if (i + 1 < code.length()) i += 2;
            continue;
        }

        // quotes
        if (code[i] == '"') {
            i++;
            while (i < code.length() && code[i] != '"') {
                if (code[i] == '\\' && i + 1 < code.length()) {
                    i += 2;
                } else {
                    i++;
                }
            }
            if (i < code.length()) i++;
            continue;
        }

        //Keyword de lungime 1
        string caracter(1, code[i]);
        if(isKeyword(caracter, keywords)){
            int keywordCode = getKeywordCode(caracter, keywords);
            //fip.add(keywordCode, 0);
            rez.push_back(caracter);
            i++;
            continue;
        }


        string token = "";
        int maxValidLength = 0;
        string bestToken = "";
        int startPos = i;

        int j = i;

        bool ok = false;
        while (j < code.length() && !isspace(code[j]) &&
               code[j] != '"' && !(code[j] == '/' && j + 1 < code.length() &&
                                   (code[j + 1] == '/' || code[j + 1] == '*')) && !ok) {
            token += code[j];

            // daca e keyword ne oprim
            if (isKeyword(token, keywords)){
                ok=true;
                maxValidLength = token.length();
                bestToken = token;
                rez.push_back(token);
            }

            else if( afi.verificaSecventa(token) ||
            afd.verificaSecventa(token) ||
            afb.verificaSecventa(token) ||
                afr.verificaSecventa(token)) {
                maxValidLength = token.length();
                bestToken = token;
            }
            j++;
        }

        if (maxValidLength > 0) {
            token = bestToken;
            i = startPos + maxValidLength;
        } else if (!token.empty()) {
            i = j;
        } else {
            i++;
            continue;
        }

        if (token.empty()) {
            continue;
        }

        bool isValid = false;

        // Check if it's a keyword
        if (isKeyword(token, keywords)) {
            int keywordCode = getKeywordCode(token, keywords);
            //fip.add(keywordCode, 0);
            rez.push_back(token);

            isValid = true;
        }
            // Check if it's an identifier
        else if (afi.verificaSecventa(token)) {
            if (token.length() >= 8) {
                if (!checkErori) {
                    cout << "Eroare: Identificator prea lung: " << token << " la linia " << line << endl;
                    checkErori = true;
                }
            } else {
                int posTS = ts.search(token);
                if (posTS == -1) {
                    ts.add(token);
                    posTS = ts.search(token);
                }
                //fip.add(0, posTS); // code 0 = ID
                rez.push_back(token);

                isValid = true;
            }
        }


        else if(afd.verificaSecventa(token)){
            int posTS = ts.search(token);
            if (posTS == -1) {
                ts.add(token);
                posTS = ts.search(token);
            }
            //fip.add(0, posTS); // code 0 = ID
            rez.push_back(token);

            isValid = true;
        }
        else if (afr.verificaSecventa(token)) {
            int posTS = ts.search(token);
            if (posTS == -1) {
                ts.add(token);
                posTS = ts.search(token);
            }
            //fip.add(0, posTS); // code 0 = ID
            rez.push_back(token);

            isValid = true;
        }

            // Check if it's a binary constant
        else if (afb.verificaSecventa(token)) {
            //fip.add(1, 0); // code 1 = CONST
            rez.push_back(token);

            isValid = true;
        }

        if (!isValid) {
            if (!checkErori) {
                cout << "Eroare: Token invalid: " << token << " la linia " << line << endl;
                checkErori = true;
            }
        }
    }
}


void createFIP( vector<string>& keywords,vector<string>& rez, TS& ts, FIP& fip)
{
    AFIdentificatori afi;
    AFBin afb;
    AFReal afr;
    AFDec afd;
    for(int i=0;i<rez.size();i++){
        if(isKeyword(rez[i],keywords) ){
            int keywordCode = getKeywordCode(rez[i], keywords);
            fip.add(keywordCode,-1);
        }
        else if(afi.verificaSecventa(rez[i])){
            int tsPoz = ts.search(rez[i]);
            fip.add(0,tsPoz);
        }
        else if(afd.verificaSecventa(rez[i])){
            int tsPoz = ts.search(rez[i]);
            fip.add(1,tsPoz);
        }
        else if(afr.verificaSecventa(rez[i])){
            int tsPoz = ts.search(rez[i]);
            fip.add(1,tsPoz);
        }
        else if(afb.verificaSecventa(rez[i])){
            int tsPoz = ts.search(rez[i]);
            fip.add(1,tsPoz);
        }
    }
}


int main() {
    ifstream inFile("../files/programNoSpaces.txt");
    if (!inFile) {
        cerr << "Eroare la deschidere fisier" << endl;
        return 1;
    }

    string program((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
    inFile.close();

    vector<string> keywords;
    vector<string> rez;
    loadKeywords(keywords);


    TS ts;
    FIP fip;
    analyzeCode(program, rez,keywords, ts, fip);

    ts.sort();

    createFIP(keywords,rez,ts,fip);

    ofstream outTS("TS.txt");
    if (outTS) {
        ts.save(outTS);
        outTS.close();
    } else {
        cerr << "Eroare la crearea fisierului TS.txt" << endl;
    }

    ofstream outFIP("FIP.txt");
    if (outFIP) {
        fip.save(outFIP);
        outFIP.close();
    } else {
        cerr << "Eroare la crearea fisierului FIP.txt" << endl;
    }

    cout << "-----------FIP----------" << endl;
    cout << "| Cod atom  |  Poz. TS |" << endl;
    for (const auto& e : fip.entries()) {
        if(e.pozTS==-1){
            cout << "| " << e.codAtom << "        | " << endl;
        }
        else{
            cout << "| " << e.codAtom << "        | " << e.pozTS << endl;

        }
    }

    return 0;
}
