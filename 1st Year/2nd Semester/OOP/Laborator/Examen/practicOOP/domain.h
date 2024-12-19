#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <assert.h>

using namespace std;

class Utilaj {
private:
    int id;
    string denumire;
    string tip;
    int cilindrii;
public:
    Utilaj(int id, string denumire, string tip, int cilindrii) : id{id}, denumire{denumire}, tip{tip},
                                                                 cilindrii{cilindrii}{}
    /**
     * Functie care resturneaza id-ul unui utilaj
     * @return
     */
    int get_id(){
        return id;
    }
    /**
     * Functie care returneaza denumirea unui utilaj
     * @return
     */
    string get_denumire(){
        return denumire;
    }
    /**
     * Functia care returneaza tipul unui utilaj
     * @return
     */
    string get_tip(){
        return tip;
    }
    /**
     * Functie care returneaza cilindrii unui utilaj
     * @return
     */
    int get_cilindrii(){
        return cilindrii;
    }
};
/**
 * Functie de teste pentru domain
 */
void test_domain();
