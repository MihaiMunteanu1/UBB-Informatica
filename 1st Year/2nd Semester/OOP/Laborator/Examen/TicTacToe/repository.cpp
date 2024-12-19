#include "repository.h"

void Repo::adauga(Joc j) {
    for(auto& joc:jocuri){
        if(joc.get_id()==j.get_id())
            throw("Jocul deja exista!");
    }
    jocuri.push_back(j);
    storetofile();
}

void Repo::modifica(int id, int dim, std::string tabla, char jucator, std::string stare) {
    int ok=0;
    for(auto& joc:jocuri){
        if(joc.get_id()==id)
            ok=1;
    }
    if(ok==0)
        throw("Jocul nu exista!");

    for(auto& j:jocuri){
            if(j.get_id()==id){
                j.set_dim(dim);
                j.set_tabla(tabla);
                j.set_jucator(jucator);
                j.set_stare(stare);
            }
    }
    storetofile();
}

void Repo::loadfromfile() {
    ifstream f(fileName);
    string line;
    while(getline(f,line)){
        int id,dim;
        string tabla,stare;
        char jucator;
        string curent;
        int nr=0;
        stringstream linestream(line);
        while(getline(linestream,curent,',')){
            if(nr==0)
                id=stoi(curent);
            if(nr==1)
                dim=stoi(curent);
            if(nr==2)
                tabla=curent;
            if(nr==3)
                jucator=curent[0];
            if(nr==4)
                stare=curent;
            nr++;
        }
        jocuri.push_back(Joc(id,dim,tabla,jucator,stare));
    }
    f.close();
}
void Repo::storetofile() {
    ofstream g(fileName);
    for(auto& j:jocuri)
        g<<j.get_id()<<","<<j.get_dim()<<","<<j.get_tabla()<<","<<j.get_jucator()<<","<<j.get_stare()<<"\n";
    g.close();
}