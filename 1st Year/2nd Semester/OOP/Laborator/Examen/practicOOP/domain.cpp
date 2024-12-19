#include "domain.h"

void test_domain(){
    Utilaj u(1,"a","b",4);
    assert(u.get_id()==1);
    assert(u.get_denumire()=="a");
    assert(u.get_tip()=="b");
    assert(u.get_cilindrii()==4);
}