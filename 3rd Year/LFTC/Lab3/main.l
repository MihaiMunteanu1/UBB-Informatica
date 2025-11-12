%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FIP.h"
#include "TS.h"

#define MAX_KEYWORDS 100
#define MAX_TOKENS 1000

typedef struct {
    char keyword[50];
    int code;
} Keyword;

typedef struct {
    char type[20];
    int count;
} TokenCounter;

Keyword keywords[] = {
    {"ID", 0},
    {"CONST", 1},
    {"int", 2},
    {"(", 3},
    {")", 4},
    {"{", 5},
    {"<-", 6},
    {";", 7},
    {"citeste", 8},
    {"loop", 9},
    {">", 10},
    {"+", 11},
    {"-", 12},
    {"scrie", 13},
    {"}", 14},
    {",", 15},
    {"==", 16},
    {"!=", 17},
    {"<=", 18},
    {">=", 19},
    {"<", 20},
    {"\"", 21},
    {"/", 22},
    {"*", 23},
    {"%", 24},
    {"float", 25},
    {"string", 26},
    {"bool", 27},
    {"main", 28},
    {"daca", 29},
    {"altfel", 30},
    {"&", 31},
    {"!", 33},
    {"||", 34},
    {"for", 35},
    {":", 36}
};

int keywordCount = sizeof(keywords) / sizeof(keywords[0]);

int getKeywordCode(const char* word) {
    for (int i = 0; i < keywordCount; i++) {
        if (strcmp(keywords[i].keyword, word) == 0) {
            return keywords[i].code;
        }
    }
    return -1;
}


int yycolumn = 1;
%}

%option yylineno
%option noyywrap

IDENTIFIER  [a-zA-Z][a-zA-Z0-9]*
DECIMAL     -?[0-9]+
REAL        [0-9]+\.[0-9]+
BINARY      0[bB][01]+
WHITESPACE  [ \t]+
NEWLINE     \n

%%

"int"|"citeste"|"scrie"|"loop"|"daca"|"altfel"|"main"|"float"|"string"|"bool"|"for" {
    yycolumn += yyleng;
    int keywordCode = getKeywordCode(yytext);
    if (keywordCode != -1) {
        addFIPEntry(keywordCode, -1);
    }
}

"<-"|"<="|">="|"=="|"!="|"||" {
    yycolumn += yyleng;
    int keywordCode = getKeywordCode(yytext);
    if (keywordCode != -1) {
        addFIPEntry(keywordCode, -1);
    }
}

{BINARY}|{REAL}|{DECIMAL} {
    yycolumn += yyleng;
    int pos = findSymbol(yytext);
    if (pos == -1) {
        pos = addSymbol(yytext);
    }
    if (pos != -1) {
        addFIPEntry(1, pos);
    }
}

{IDENTIFIER} {
    yycolumn += yyleng;
    if (strlen(yytext) >= 8) {
        printf("Identifier prea lung: %s \nNumar linie: %d \n \n",yytext,yylineno);
    } else {
        int pos = findSymbol(yytext);
        if (pos == -1) {
            pos = addSymbol(yytext);
        }
        if (pos != -1) {
            addFIPEntry(0, pos);
        }
    }
}

[+\-*/%=<>(){}();,:&!"] {
    yycolumn += yyleng;
    char singleChar[2] = {yytext[0], '\0'};
    int keywordCode = getKeywordCode(singleChar);
    if (keywordCode != -1) {
        addFIPEntry(keywordCode, -1);
    }
}

{WHITESPACE} {
    yycolumn += yyleng;
}

{NEWLINE} {
    yycolumn = 1;
}

. {
    yycolumn++;
}

%%

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    initTS();
    initFIP();

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        printf("Error: Could not open file %s\n", argv[1]);
        return 1;
    }

    yyin = file;
    yylex();

    printFIP();
    printTS();

    fclose(file);
    return 0;
}
