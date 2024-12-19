#include "domain.h"

void test_domain(){
    Melodie m(1,"a","b",2);
    assert(m.get_id()==1);
    assert(m.get_titlu()=="a");
    assert(m.get_artist()=="b");
    assert(m.get_rank()==2);
    m.set_rank(5);
    assert(m.get_rank()==5);
    m.set_titlu("g");
    assert(m.get_titlu()=="g");

}