%{
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "conjunto_cal.h"
#define MSDOS

void yyerror (char *s);
int yylex ();
void warning (char *s, char *t);
%}

%union {
	int n;
	Conjunto* c;
}
%token <n> NUMERO
%type <c> conj exp

%% 
lista: 
	 | lista'\n'
	 | lista exp '\n' { imprimeConjunto($2); }
	 ;

exp: '{' conj '}' { $$ = $2; }
   | '{' conj '}' 'U' '{' conj '}' { $$ = unirConjunto($2, $6); } 	 
   | '{' conj '}' 'I' '{' conj '}' { $$ = intersecConjunto($2, $6); } 	 
   | '{' conj '}' 'D' '{' conj '}' { $$ = diferenConjunto($2, $6); } 	 
   | '{' conj '}' 'S' '{' conj '}' { $$ = difsimConjunto($2, $6); }
   ;

conj: conj ',' NUMERO { $$ = insertar($$, $3); }
    | NUMERO { $$ = creaConjunto(0); $$ = insertar($$, $1); }
    ;
%%

char *progname;
int lineno = 1;
using namespace std;

int main (int argc, char *argv[]) {
	progname = argv[0];
	yyparse();
}

int yylex() {
	int c;

	while ((c = getchar()) == ' ' || c == '\t');
	if (c == EOF) return 0;
	if (isdigit(c)) {
		ungetc (c, stdin);
		scanf("%d", &yylval.n);
		return NUMERO;
	}
	if (c == '\n') lineno++;
	return c;
}	

void yyerror (char *s) {
	warning (s, (char *) 0);
}

void warning(char *s, char *t) {
	fprintf (stderr, "%s: %s", progname, s);
	if (t)
		fprintf(stderr, "%s", t);
	fprintf(stderr, "Cerca de la linea %d \n", lineno);
}
