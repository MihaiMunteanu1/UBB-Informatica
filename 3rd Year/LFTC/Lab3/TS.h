#ifndef TS_H
#define TS_H

#define MAX_SYMBOLS 500

typedef struct {
    int poz;
    char atom[50];
    int next;
} TSElement;

typedef struct {
    TSElement symbols[MAX_SYMBOLS];
    int count;
    int nextPoz;
} TS;

extern TS ts;

void initTS();
int findSymbol(const char* symbol);
int addSymbol(const char* symbol);
void sortTS();
void printTS();

#endif
