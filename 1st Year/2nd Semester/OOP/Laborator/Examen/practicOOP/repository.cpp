#include "repository.h"

void Repo::storetofile() {
    ofstream g(fileName);
    for(auto& u:utilaje)
        g<<u.get_id()<<" "<<u.get_denumire()<<" "<<u.get_tip()<<" "<<u.get_cilindrii()<<"\n";
    g.close();
}

void Repo::loadfromfile() {
    ifstream f(fileName);
    int id;
    string denumire;
    string tip;
    int cilindrii;
    while(f>>id>>denumire>>tip>>cilindrii){
        Utilaj u(id,denumire,tip,cilindrii);
        utilaje.push_back(u);
    }
    f.close();
}
void Repo::modifica(Utilaj u) {
    for(auto& ut:utilaje){
        if(ut.get_id()==u.get_id())
            ut=u;
    }
    storetofile();
}
void Repo::sterge(int id) {
    int ok=0,nrC=0;
    for(auto& u:utilaje)
        if(u.get_id()==id){
            ok=1;
            nrC=u.get_cilindrii();
        }
    if(ok==0)
        throw("Nu exista utilajul");
    int cont=0;
    for(auto& u:utilaje){
        if(u.get_cilindrii()==nrC)
            cont++;
    }
    if(cont==1)
        throw("Este ultimul utilaj cu nr de cilindrii");

    auto new_end= remove_if(utilaje.begin(),utilaje.end(),[id](Utilaj& u1){
        return u1.get_id()==id;
    });
    utilaje.erase(new_end,utilaje.end());
    storetofile();
}

void test_repo(){
    ofstream g("test.txt");
    g<<"1 c b 4\n2 a b 4\n";
    g.close();
    Repo rep("test.txt");
    assert(rep.get_all().size()==2);
    rep.modifica(Utilaj(1,"c","d",4));
    assert(rep.get_all()[0].get_cilindrii()==4);
    assert(rep.get_all()[0].get_denumire()=="c");
    assert(rep.get_all()[0].get_tip()=="d");
    rep.sterge(1);
    assert(rep.get_all().size()==1);
    try{
        rep.sterge(4);

    }
    catch(const char* msg){
        assert(true);
    }
    assert(rep.get_all().size()==1);
}