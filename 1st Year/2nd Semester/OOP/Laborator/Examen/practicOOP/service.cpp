#include "service.h"


vector<Utilaj> Service::sortare(vector<Utilaj> v) {
    sort(v.begin(),v.end(),[&](Utilaj& u1,Utilaj& u2){
        if(u1.get_tip()<u2.get_tip())
            return u1.get_tip()<u2.get_tip();
        else if(u1.get_tip()==u2.get_tip())
            return u1.get_denumire()<u2.get_denumire();
        else
            return u1.get_tip()<u2.get_tip();
    });
    return v;
}

void Service::sterge(int id) {
    try{
        repo.sterge(id);
    }
    catch(const char* msg){
        throw(msg);
    }
}

void Service::modifica(int id, std::string denumire, std::string tip, int cilindrii) {
    if(cilindrii!=1 && cilindrii!=2 && cilindrii!=4 && cilindrii!=8)
        throw("Nr invalid de cilindrii");
    if(denumire.empty())
        throw("Denumire invalida");
    if(tip.empty())
        throw("Tip invalid");
    Utilaj u(id,denumire,tip,cilindrii);
    repo.modifica(u);
}


int Service::nr_utilaje_tip(string tip) {
    int cont=0;
    for(auto& u:get_all()){
        if(u.get_tip()==tip)
            cont++;
    }
    return cont;
}

int Service::nr_utilaje_cilindrii(int nrC) {
    int cont=0;
    for(auto& u:get_all()){
        if(u.get_cilindrii()==nrC)
            cont++;
    }
    return cont;
}

void test_service(){
    Repo rep("test.txt");
    Service srv{rep};
    ofstream g("test.txt");
    g<<"2 a b 4\n";
    g.close();
    assert(srv.get_all().size()==1);
    srv.modifica(2,"c","d",8);
    try{
        srv.modifica(2,"a","b",22);
    }
    catch(const char* msg){
        assert(true);
    }
    try{
        srv.modifica(10,"a","b",2);
    }
    catch(const char* msg){
    }
    try{
        srv.modifica(2,"","b",2);
    }
    catch(const char* msg){}
    try{
        srv.modifica(2,"a","",2);
    }
    catch(const char* msg){}
    assert(srv.get_all()[0].get_denumire()=="c");
    try{
        srv.sterge(2);
    }
    catch(const char* msg){
        assert(true);
    }
    assert(srv.nr_utilaje_cilindrii(8)==1);
    assert(srv.nr_utilaje_cilindrii(2)==0);
    assert(srv.nr_utilaje_tip("d")==1);
    assert(srv.nr_utilaje_tip("e")==0);
}