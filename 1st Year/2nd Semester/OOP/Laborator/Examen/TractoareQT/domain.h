#pragma once
#include <iostream>
#include <string>
#include <assert.h>
using std::string;

class Tractoare{
private:
    int id,nrRoti;
    string denumire,tip;
public:
    Tractoare(int id,string denumire,string tip,int nrRoti):id{id},denumire{denumire},tip{tip},nrRoti{nrRoti}{}

    int get_id(){
        return id;
    }
    int get_nrRoti(){
        return nrRoti;
    }
    string get_denumire(){
        return denumire;
    }
    string get_tip(){
        return tip;
    }

};