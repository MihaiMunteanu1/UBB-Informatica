#include "repository.h"

void Repo::loadfromfile() {
    ifstream f(fileName);
    string line;
    while(getline(f,line)){
        int id;
        string artist,titlu,gen;
        string curent;
        int nr=0;
        stringstream linestream(line);
        while(getline(linestream,curent,',')){
            if(nr==0)
                id= stoi(curent);
            if(nr==1)
                titlu=curent;
            if(nr==2)
                artist=curent;
            if(nr==3)
                gen=curent;
            nr++;
        }
        melodii.push_back(Melodie(id,titlu,artist,gen));
    }
    f.close();
}
void Repo::storetofile() {
    ofstream g(fileName);
    for(auto& m:melodii)
        g<<m.get_id()<<","<<m.get_titlu()<<","<<m.get_artist()<<","<<m.get_gen()<<"\n";
    g.close();
}
void Repo::adauga(Melodie &m) {
    for(auto& me:melodii)
        if(me.get_id()==m.get_id())
            throw("Melodia exista!");
    melodii.push_back(m);
    storetofile();
}

void Repo::sterge(int id) {
    int ok=0;
    for(auto& m:melodii)
        if(m.get_id()==id)
            ok=1;
    if(ok==0)
        throw("Melodia nu exista");
    auto new_end=remove_if(melodii.begin(),melodii.end(),[id](Melodie& m){
        return m.get_id()==id;
    });
    melodii.erase(new_end,melodii.end());
    storetofile();
}