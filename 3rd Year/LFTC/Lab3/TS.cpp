#include "TS.h"
#include <stdio.h>
#include <string.h>

TS ts;

void initTS() {
    ts.count = 0;
    ts.nextPoz = 0;
}

int findSymbol(const char* symbol) {
    for (int i = 0; i < ts.count; i++) {
        if (strcmp(ts.symbols[i].atom, symbol) == 0) {
            return ts.symbols[i].poz;
        }
    }
    return -1;
}

int addSymbol(const char* symbol) {
    if (ts.count < MAX_SYMBOLS) {
        ts.symbols[ts.count].poz = ts.nextPoz++;
        strcpy(ts.symbols[ts.count].atom, symbol);
        ts.symbols[ts.count].next = -1;
        ts.count++;

        // Sort after adding new element
        sortTS();

        return ts.symbols[ts.count - 1].poz;
    }
    return -1;
}

void sortTS() {
    if (ts.count <= 1) return;

    int idx[MAX_SYMBOLS];
    for (int i = 0; i < ts.count; i++) {
        idx[i] = i;
    }

    for (int i = 0; i < ts.count - 1; i++) {
        for (int j = 0; j < ts.count - 1 - i; j++) {
            int a = idx[j];
            int b = idx[j + 1];

            int cmp = strcmp(ts.symbols[a].atom, ts.symbols[b].atom);
            bool shouldSwap = false;

            if (cmp > 0) {
                shouldSwap = true;
            } else if (cmp == 0 && ts.symbols[a].poz > ts.symbols[b].poz) {
                shouldSwap = true;
            }

            if (shouldSwap) {
                int temp = idx[j];
                idx[j] = idx[j + 1];
                idx[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < ts.count; i++) {
        ts.symbols[i].next = -1;
    }

    for (int k = 0; k < ts.count - 1; k++) {
        int cur = idx[k];
        int nxt = idx[k + 1];
        ts.symbols[cur].next = nxt;
    }
}

void printTS() {
    printf("\nTS :\n");
    printf("| Pozitie | Atom        | Next |\n");
    printf("|---------|-------------|------|\n");
    for (int i = 0; i < ts.count; i++) {
        printf("| %-7d | %-11s | %-4d |\n",
               ts.symbols[i].poz,
               ts.symbols[i].atom,
               ts.symbols[i].next);
    }
}
