
#include "repository.h"

void Repo::update_rank(int id,int rank) {
    for(auto& m:melodii){
        if(m.get_id()==id) {
            m.set_rank(rank);
            storetofile();
        }
    }
}
void Repo::update_titlu(int id,string titlu) {
    for(auto& m:melodii){
        if(m.get_id()==id){
            m.set_titlu(titlu);
            storetofile();
        }

    }
}

void Repo::sterge(int id) {
    int ok=0;
    string artist;
    for(auto& m:melodii)
        if(m.get_id()==id){
            ok=1;
            artist=m.get_artist();
        }
    if(ok==0)
        throw ("Melodia nu exista!");
    int cont=0;
    for(auto& m:melodii){
        if(m.get_artist()==artist)
            cont++;
    }
    if(cont==1){
        throw ("Este ultima melodie a artistului!");
    }
    auto new_end= remove_if(melodii.begin(),melodii.end(),[id](Melodie& m){
            return m.get_id()==id;
    });
    melodii.erase(new_end,melodii.end());
    storetofile();
}

void Repo::loadfromfile() {
    ifstream f(fileName);
    string line;
    while(getline(f,line)){
        int id,rank;
        string titlu,artist;
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
                rank= stoi(curent);
            nr++;
        }
        melodii.push_back(Melodie(id,titlu,artist,rank));
    }
    f.close();
}
void Repo::storetofile() {
    ofstream g(fileName);
    for(auto& m:melodii)
        g<<m.get_id()<<","<<m.get_titlu()<<","<<m.get_artist()<<","<<m.get_rank()<<"\n";
    g.close();
}

void test_repo(){
    ofstream g("test.txt");
    g<<"1,a,b,3";
    g.close();
    Repo r{"test.txt"};
    assert(r.get_all().size()==1);
    r.update_rank(1,5);
    r.update_titlu(1,"g");
    assert(r.get_all()[0].get_rank()==5);
    assert(r.get_all()[0].get_titlu()=="g");
    try{
        r.sterge(1);
        assert(false);
    }
    catch(const char* msg){
        assert(true);
    }
}