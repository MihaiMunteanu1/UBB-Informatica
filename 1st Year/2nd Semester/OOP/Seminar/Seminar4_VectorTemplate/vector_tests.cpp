#include "vector_tests.h"
#include <assert.h>
#include <iostream>

void test_create() {
    MyVector<int> v;
    assert(v.size() == 0);
}
void test_push_back() {
    MyVector<int> vec;
    assert(vec.size() == 0);

    vec.push_back(10);
    assert(vec.size() == 1);
    assert(vec[0] == 10);

    vec.push_back(20);
    vec.push_back(30);
    assert(vec.size() == 3);
    assert(vec[1] == 20);
    assert(vec[2] == 30);
}

void test_range_for() {
    MyVector<int> vec;
    assert(vec.size() == 0);

    for (int i = 0; i < 100; i++)
        vec.push_back(i);

    size_t count = 0;
    for (const auto& elem : vec) {
        assert(elem == count);
        count++;
    }
    count = 0;
    for (auto e : vec)
    {
        assert(e == count);
        count++;
    }
}


void test_get_set() {
    MyVector<int> vec(3);
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    assert(vec[0] == 10);
    assert(vec[1] == 20);
    assert(vec[2] == 30);

    vec[0] = 100;
    assert(vec[0] == 100);

    
}

void test_iterator() {
    MyVector<int> vec(3);
    for (int i = 0; i < 10; i++)
        vec.push_back(i);

    IteratorVector<int> it{vec};
    int valToCompare = 0;
    while (it.valid()) {
        assert(*it == valToCompare);
        valToCompare++;
        ++it;
    }

    IteratorVector<int> it2{vec};
    valToCompare = 0;
    while (it2.valid()) {
        assert(*it2 == valToCompare);
        valToCompare++;
        it2++;
    }
}

void test_size() {
    MyVector<int> vec;
    assert(vec.size() == 0);

    vec.push_back(10);
    assert(vec.size() == 1);

    vec.push_back(20);
    vec.push_back(30);
    assert(vec.size() == 3);
}

void test_iterator2() {
    MyVector<int> vec(3);
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    int sum = 0;
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        sum += *it;
    }
    assert(sum == 60);
}


void test_copy_constructor() {
    MyVector<int> vec1;
    vec1.push_back(10);
    vec1.push_back(20);
    vec1.push_back(30);

    MyVector<int> vec2 = vec1;

    assert(vec2.size() == 3);
    assert(vec2[0] == 10);
    assert(vec2[1] == 20);
    assert(vec2[2] == 30);

    // Modify vec1 to verify deep copy
    vec1[1] = 100;
    assert(vec1[1] == 100);
    assert(vec2[1] == 20);  // Ensure vec2 remains unchanged
}

void test_assignment_operator() {
    MyVector<int> vec1;
    vec1.push_back(10);
    vec1.push_back(20);
    vec1.push_back(30);

    MyVector<int> vec2;
    vec2.push_back(40);
    vec2.push_back(50);

    vec2 = vec1;

    assert(vec2.size() == 3);
    assert(vec2[0] == 10);
    assert(vec2[1] == 20);
    assert(vec2[2] == 30);

    // Modify vec1 to verify deep copy
    vec1[1] = 100;
    assert(vec1[1] == 100);
    assert(vec2[1] == 20);  // Ensure vec2 remains unchanged
}

void testAllForVector() {
    test_create();
    test_push_back();
    test_range_for();
    test_get_set();
    test_iterator();
    test_iterator2();
    test_size();
    test_assignment_operator();
    test_copy_constructor();
  
}
