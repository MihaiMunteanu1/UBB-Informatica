#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
#include <assert.h>
using namespace std;

class Melodie {
private:
    int id,rank;
    string titlu,artist;
public:
    Melodie(int id,string titlu,string artist,int rank):id{id},titlu{titlu},artist{artist},rank{rank}{}

    int get_id(){
        return id;
    }
    int get_rank(){
        return rank;
    }
    string get_titlu(){
        return titlu;
    }
    string get_artist(){
        return artist;
    }
    void set_rank(int new_rank){
        rank=new_rank;
    }
    void set_titlu(string new_titlu){
        titlu=new_titlu;
    }

    ~Melodie()=default;
};


void test_domain();