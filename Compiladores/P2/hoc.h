#include "complejo.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
using namespace std;

typedef struct Symbol { /* entrada de la tabla de símbolos */
	string name;
	short   type;   /* VAR, UNDEF */
	Complejo val;	
	struct Symbol *next;  /* para ligarse a otro */ 
} Symbol;

Symbol *install(string s,int t, Complejo d), *lookup(string s);

void yyerror (string s);
int yylex ();
void warning(string s, string t);
void execerror(string s, string t);
void fpecatch();
string array_to_string(char *s);