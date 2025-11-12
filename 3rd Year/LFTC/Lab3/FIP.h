#ifndef FIP_H
#define FIP_H

#define MAX_TOKENS 1000


/*
 * flex main.l
 * g++ -o lexer lex.yy.c FIP.cpp TS.cpp
 * ./lexer program.txt
 */


typedef struct {
    int atom;
    int position;
} FIPEntry;

typedef struct {
    FIPEntry entries[MAX_TOKENS];
    int count;
} FIP;

extern FIP fip;

void initFIP();
void addFIPEntry(int atom, int pos);
void printFIP();

#endif
