#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
using namespace std;

typedef struct Symbol { /* entrada de la tabla de símbolos */
	string name;
	short   type;   /* VAR, BLTIN, UNDEF */
	union {
		double val;	       /* si es VAR */
		double  (*ptr)();      /* sí es BLTIN */
	} u;
	struct Symbol *next;  /* para ligarse a otro */ 
} Symbol;

Symbol *install(char *s,int t, double d), *lookup(char *s);
