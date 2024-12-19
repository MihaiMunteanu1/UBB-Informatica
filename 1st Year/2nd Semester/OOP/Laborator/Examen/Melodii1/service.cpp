#include "service.h"

vector<Melodie> Service::sortare(vector<Melodie> m) {
    sort(m.begin(),m.end(),[&](Melodie& m1,Melodie& m2){
       return m1.get_rank()<m2.get_rank();
    });
    return m;
}

void Service::sterge(int id) {
    try{
        repo.sterge(id);
    }
    catch(const char& msg){
        throw (msg);
    }
}

void test_service(){
    ofstream g("test.txt");
    g<<"1,a,b,3";
    g.close();
    Repo r{"test.txt"};
    Service srv{r};
    assert(srv.get_all().size()==1);
    assert(srv.melodii_cu_acelasi_rank(3)==1);
}