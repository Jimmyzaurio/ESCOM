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

Symbol *install(string s,int t, Complejo d), *lookup(string s);

typedef struct Datum {
	Complejo val;
	struct Symbol *sym;
} Datum;

typedef int (*Inst)();
#define STOP (Inst)0

/* practica 4
extern Inst prog[];
extern Datum pop();
extern void eval(), add(), sub(), mul(), division(), negar(), imag();
extern void assign(), varpush(), constpush(), print();
*/

// Inicio practica 5
extern Inst prog[], *progp;
extern Inst *code(Inst f);
extern Datum pop();
extern void xpop();
extern void eval();
extern void add();
extern void sub();
extern void mul();
extern void division();
extern void negar();
extern void imag();
extern void assign();
extern void varpush();
extern void constpush();
extern void print();
extern void prexpr();
extern void gt();
extern void lt();
extern void eq();
extern void ge();
extern void le();
extern void ne();
extern void _and();
extern void _or();
extern void _not();
extern void ifcode();
extern void whilecode();
// fin practica 5

void init();
void initcode();
void execute(Inst *p);
void yyerror(string s);
void warning(string s, string t);
void execerror(string s, string t);
void fpecatch();
int yylex();
int follow(int expect, int ifyes, int ifno);
string array_to_string(char *s);