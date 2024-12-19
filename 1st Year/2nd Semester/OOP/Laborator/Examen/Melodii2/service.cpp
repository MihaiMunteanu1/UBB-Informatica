
#include "service.h"
#include <random>

int Service::nr_melodii_artist(const std::string& artist) {
    int cont=0;
    for(auto& m:get_all())
        if(m.get_artist()==artist)
            cont++;
    return cont;
}
int Service::nr_melodii_gen(const std::string& gen) {
    int cont=0;
    for(auto& m:get_all())
        if(m.get_gen()==gen)
            cont++;
    return cont;
}

void Service::sterge(int id) {
    try{
        repo.sterge(id);
    }
    catch(const char* msg){
        throw (msg);
    }
}

void Service::adauga(std::string titlu, std::string artist, std::string gen) {

    if(gen!="pop" && gen!="rock" && gen!="folk" && gen!="disco")
        throw("Gen invalid!");

    int id=rand()%100;
    Melodie m(id,titlu,artist,gen);
    try{
        repo.adauga(m);
    }
    catch(const char* msg){
        throw (msg);
    }
}

vector<Melodie> Service::sortare(vector<Melodie> m) {
    sort(m.begin(),m.end(),[&](Melodie& m1,Melodie& m2){
        return m1.get_artist()<m2.get_artist();
    });
    return m;
}