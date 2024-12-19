#include "Activitate.h"
#include <vector>
using std::vector;
/*
  Functie folosit in teste
  primeste vector prin valoare -> copy constructor
  returneaza prin valoare -> copy constructor sau move constructor
*/
template <typename MyVector>
MyVector testCopyIterate(MyVector v) {
    Activitate a{"Baschet","Dribbling","miscare",2};
    v.add(a);
    return v;
}

template <typename MyVector>
void addActivitati(MyVector& v, int cate) {
    for (int i = 0; i<cate; i++) {
        Activitate a{ std::to_string(i) + "_titlu",std::to_string(i) + "_descriere",
                      std::to_string(i)+"_tip",i};
        v.add(a);
    }
}

/*
Testare constructori / assignment
E template pentru a refolosi la diferite variante de VectorDinamic din proiect
*/
template <typename MyVector>
void testCreateCopyAssign() {
    MyVector v;//default constructor
    addActivitati(v, 100);
    assert(v.size() == 100);
    assert(v.get(50).get_titlu() == "50_titlu");

    MyVector v2{ v };//constructor de copiere
    assert(v2.size() == 100);
    assert(v2.get(50).get_titlu() == "50_titlu");

    MyVector v3;//default constructor
    v3 = v;//operator=   assignment
    assert(v3.size() == 100);
    assert(v3.get(50).get_titlu() == "50_titlu");

    auto v4 = testCopyIterate(v3);
    assert(v4.size() == 101);
    assert(v4.get(50).get_titlu() == "50_titlu");
}

/*
  Test pentru move constructor si move assgnment
*/
template <typename MyVector>
void testMoveConstrAssgnment() {
    std::vector<MyVector> v;
    //adaugam un vector care este o variabila temporara
    //se v-a apela move constructor
    v.push_back(MyVector{});

    //inseram, la fel se apeleaza move costructor de la vectorul nostru
    v.insert(v.begin(),MyVector{});

    assert(v.size() == 2);

    MyVector v2;
    addActivitati(v2, 50);

    v2 = MyVector{};//move assignment

    assert(v2.size() == 0);

}
template <typename MyVector>
void testAssignmentOperator() {
    MyVector v;
    addActivitati(v, 100);
    MyVector v2=v;
    v=v;
    assert(v.size()==v2.size());
}
template <typename MyVector>
void testMoveAssignmentOperator() {
    MyVector v;
    addActivitati(v, 100);
    MyVector v2=std::move(v);
    v=std::move(v);
    assert(v.size()==0);
    assert(v2.size()==100);
}
template <typename MyVector>
void testStergere() {
    MyVector v;
    addActivitati(v, 100);
    v.sterge(50);
    assert(v.size() == 99);
    assert(v.get(50).get_titlu() == "51_titlu");
}
template <typename MyVector>
void testeVectorDinamic() {
    testStergere<MyVector>();
    testMoveAssignmentOperator<MyVector>();
    testAssignmentOperator<MyVector>();
    testCreateCopyAssign<MyVector>();
    testMoveConstrAssgnment<MyVector>();
}