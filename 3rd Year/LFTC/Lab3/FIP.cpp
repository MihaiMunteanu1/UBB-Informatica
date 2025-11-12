#include "FIP.h"
#include <stdio.h>

FIP fip;

void initFIP() {
    fip.count = 0;
}

void addFIPEntry(int atom, int pos) {
    if (fip.count < MAX_TOKENS) {
        fip.entries[fip.count].atom = atom;
        fip.entries[fip.count].position = pos;
        fip.count++;
    }
}

void printFIP() {
    printf("FIP:\n");
    printf("Atom | Position\n");
    printf("--------------\n");
    for (int i = 0; i < fip.count; i++) {
        printf("%-4d | %-8d\n", fip.entries[i].atom, fip.entries[i].position);
    }
}
