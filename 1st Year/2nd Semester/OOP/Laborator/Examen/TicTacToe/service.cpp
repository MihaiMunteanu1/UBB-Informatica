#include "service.h"

vector<Joc> Service::sortare(vector<Joc> jocuri) {
    sort(jocuri.begin(),jocuri.end(),[&](Joc& j1,Joc& j2){
        return j1.get_stare()<j2.get_stare();
    });
    return jocuri;
}

void Service::adauga(int id, int dim, std::string tabla, char jucator) {
    if(dim!=3 && dim!=4 && dim!=5)
        throw("Dimensiune invalida");
    if(tabla.size()!=dim*dim)
        throw("Tabal invalida!");
    if(jucator!='X' && jucator!='O')
        throw("Jucator invalid!");
    Joc j(id,dim,tabla,jucator,"Neinceput");
    try{
        repo.adauga(j);
    }
    catch(const char* msg){
        throw(msg);
    }
}

void Service::modifica(int id, int dim, std::string tabla, char jucator, std::string stare) {
    if(dim!=3 && dim!=4 && dim!=5)
        throw("Dimensiune invalida");
    if(tabla.size()!=dim*dim)
        throw("Tabal invalida!");
    if(jucator!='X' && jucator!='O')
        throw("Jucator invalid!");
    if(stare!="Neinceput" && stare!="In derulare" && stare!="Terminat")
        throw("Stare invalida");
    try{
        repo.modifica(id,dim,tabla,jucator,stare);
    }
    catch(const char* msg){
        throw(msg);
    }
}