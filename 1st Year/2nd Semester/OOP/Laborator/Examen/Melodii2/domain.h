#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <assert.h>
using namespace std;

class Melodie {
private:
    int id;
    string titlu,artist,gen;
public:
    Melodie(int id,string titlu,string artitst,string gen):id{id},titlu{titlu},artist{artitst},gen{gen}{}

    int get_id(){
        return id;
    }
    string get_titlu(){
        return titlu;
    }
    string get_artist(){
        return artist;
    }
    string get_gen(){
        return gen;
    }

    ~Melodie()=default;
};


