#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <algorithm>
using namespace std;

class Joc {
private:
    int id,dim;
    string tabla;
    char jucator;
    string stare;
public:
    Joc(int id,int dim,string tabla,char jucator,string stare):id{id},dim{dim},tabla{tabla},
    jucator{jucator},stare{stare}{}

    void set_id(int new_id){
        id=new_id;
    }
    void set_dim(int new_dim){
        dim=new_dim;
    }
    void set_tabla(string new_tabla){
        tabla=new_tabla;
    }
    void set_jucator(char new_jucator){
        jucator=new_jucator;
    }
    void set_stare(string new_stare){
        stare=new_stare;
    }
    int get_id( ){
        return id;
    }
    int get_dim( ){
        return dim;
    }
    string get_tabla( ){
        return tabla;
    }
    char get_jucator( ){
        return jucator;
    }
    string get_stare( ){
        return stare;
    }

    ~Joc()=default;
};
