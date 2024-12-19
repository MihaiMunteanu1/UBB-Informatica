#include "customsort.h"
void sort(List* l, CompareFct cmpF) {
    int i, j;
    for (i = 0; i < size(l); i++) {
        for (j = i + 1; j < size(l); j++) {
            void* p1 = get(l, i);
            void* p2 = get(l, j);
            if (cmpF(p1, p2) > 0) {
                setElem(l, i, p2);
                setElem(l, j, p1);
            }
        }
    }
}