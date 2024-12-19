#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <assert.h>
using namespace std;

class Produs{
private:
    int id;
    double pret;
    string nume,tip;
public:
    Produs(int id,string nume,string tip,double pret):id{id},nume{nume},tip{tip},pret{pret}{}

    ~Produs()=default;
    int get_nr_vocale(){
        int cont=0;
        for(auto& c:nume)
            if(c=='a' || c=='e' || c=='i' || c=='o' || c=='u' || c=='A' || c=='E' || c=='I' || c=='O' || c=='U')
                cont++;
        return cont;
    }
    int get_id(){
        return id;
    }
    double get_pret(){
        return pret;
    }
    string get_nume(){
        return nume;
    }
    string get_tip(){
        return tip;
    }
};
