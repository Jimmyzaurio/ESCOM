#include "complejo.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#define nil 0

typedef struct Symbol { /* entrada de la tabla de símbolos */
	string name;
	short   type;   /* VAR, UNDEF */
	Complejo val;	       /* si es VAR */	
	struct Symbol *next;  /* para ligarse a otro */ 
} Symbol;

struct Datum {
	Complejo val;
	struct Symbol *sym;
};

typedef struct Symbol Symbol;
typedef struct Datum Datum;

Symbol *install(string s,int t, Complejo d), *lookup(string s);

extern Datum pop();

typedef int (*Inst)();

#define STOP (Inst)0

extern Inst prog[];
extern void eval(), add(), sub(), mul(), division(), negar(), imag();
extern void assign(), varpush(), constpush(), print();

Inst *code(Inst f);
void init();
void initcode();
void execute(Inst *p);
void yyerror(string s);
void warning(string s, string t);
void execerror(string s, string t);
void fpecatch();
int yylex();
string array_to_string(char *s);