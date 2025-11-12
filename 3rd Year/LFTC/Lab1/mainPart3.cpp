//#include <iostream>
//#include <vector>
//#include <fstream>
//#include <sstream>
//#include <string>
//#include <algorithm>
//#include <map>
//#include "TS.h"
//#include "FIP.cpp"
//
//
//using namespace std;
//
//bool checkErori = false;
//
//// identificare atomi in program
//vector<string> identificare(const string& programText) {
//    istringstream iss(programText);
//    string word;
//    vector<string> rez;
//
//    while (iss >> word) {
//        if (find(rez.begin(), rez.end(), word) == rez.end()) {
//            rez.push_back(word);
//        }
//    }
//    return rez;
//}
//
//vector<string> identificareAll(const string& programText) {
//    istringstream iss(programText);
//    string word;
//    vector<string> rez;
//
//    while (iss >> word) {
//            rez.push_back(word);
//
//    }
//    return rez;
//}
//
////verificare daca atom e const
//bool checkCONST(const string &word) {
//    if (word.empty()) {
//        return false;
//    }
//
//    for (char c : word) {
//        if (!isdigit(c)) {
//            return false;
//        }
//    }
//
//    return true;
//}
//
//
//// verificare daca un atom este ID sau CONST pentru a fi adaugat in TS
//bool checkTS(const string &word, vector<string> keywords) {
//
//    if (word.empty()) {
//        return false;
//    }
//
//
//    if (find(keywords.begin(), keywords.end(), word) != keywords.end()) {
//        return false;
//    }
//
//    if(!checkCONST(word) && word.length()<8){
//        return true;
//    }
//    else if(!checkCONST(word) && word.length()>=8){
//        if(!checkErori){
//            cout<<"Eroare: "<<word<<endl;
//            checkErori = true;
//        }
//        return false;
//    }
//
//    return true;
//}
//
//void loadKeywords(vector<string>& keywords) {
//    ifstream keyFile("../files/keywords.txt");
//    if (keyFile) {
//        string line;
//        while (getline(keyFile, line)) {
//            size_t colonPos = line.find(" : ");
//            if (colonPos != string::npos) {
//                string keyword = line.substr(0, colonPos);
//                keywords.push_back(keyword);
//            }
//        }
//        keyFile.close();
//    }
//}
//
//
//
//int main() {
//    std::ifstream inFile("../files/program.txt");
//    if (!inFile) {
//        std::cerr << "Eroare la deschidere" << std::endl;
//        return 1;
//    }
//
//    std::string program((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
//    inFile.close();
//
//    std::vector<std::string> rez = identificare(program);
//
//    static std::vector<std::string> keywords;
//    loadKeywords(keywords);
//
//    TS ts;
//    for (const auto& item : rez) {
//        if (checkTS(item, keywords)) {
//            ts.add(item);
//        }
//    }
//    ts.sort();
//
//    std::ofstream outTS("TS.txt");
//    if (outTS) {
//        ts.save(outTS);
//        outTS.close();
//    } else {
//        std::cerr << "Eroare la crearea fisierului `TS.txt`" << std::endl;
//    }
//
//    // Build FIP
//    FIP fip;
//    std::vector<std::string> rezAll = identificareAll(program);
//
//    for (const auto& item : rezAll) {
//        // keyword?
//        auto it = std::find(keywords.begin(), keywords.end(), item);
//        if (it != keywords.end()) {
//            int kod = static_cast<int>(std::distance(keywords.begin(), it));
//            fip.add(kod, 0);
//            continue;
//        }
//
//        // const?
//        if (checkCONST(item)) {
//            fip.add(1, 0); // code 1 = CONST
//            continue;
//        }
//
//        // identifier in TS?
//        if (checkTS(item, keywords)) {
//            int posTS = ts.search(item);
//            fip.add(0, posTS); // code 0 = ID
//            continue;
//        }
//
//        // unknown / other token
//        fip.add(-1, 0);
//    }
//
//    std::ofstream outFIP("FIP.txt");
//    if (outFIP) {
//        fip.save(outFIP);
//        outFIP.close();
//    } else {
//        std::cerr << "Eroare la crearea fisierului `FIP.txt`" << std::endl;
//    }
//
//    // Print FIP to console (same layout as before)
//    std::cout << "-----------FIP----------" << std::endl;
//    std::cout << "| Cod atom  |  Poz. TS |" << std::endl;
//    for (const auto& e : fip.entries()) {
//        std::cout << "| " << e.codAtom << "        | " << e.pozTS << std::endl;
//    }
//
//    return 0;
//}
