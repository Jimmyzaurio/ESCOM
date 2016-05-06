%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "complejo.h"
#define MSDOS
Complejo mem[30];
void yyerror (char *s);
int yylex ();
void warning (char *s, char *t);
%}

%union {
	int n;
	char inx;
	Complejo c = *new Complejo(0,0);
}

%token <n> NUMBER
%token <inx> VAL
%type <c> exp
%right '='
%left '+' '-'
%left '*' '/' 'i'
%left UNARYMINUS
%% 
lista: 
	 | lista'\n'
	 | lista exp '\n' { $2.imprime(); }
	 ;

exp:  NUMBER           { $$ = *new Complejo($1,0);  }
	| VAL 			   { $$ = mem[$1];}
	| VAL '=' exp  { $$ = mem[$1] = $3;}
	| exp 'i'      { $$ = $1*(*new Complejo(0,1));  }
	| exp '+' exp  { $$ = $1+$3;  }
	| exp '-' exp  { $$ = $1-$3;  }
	| exp '*' exp  { $$ = $1*$3;  }
	| exp '/' exp  { $$ = $1/$3; }	
	| '-' exp 	%prec UNARYMINUS { $$ = *new Complejo()-$2;}
	| '(' exp ')'  { $$ = $2;}
	;
%%

char *progname;
int lineno = 1;

int main (int argc, char *argv[]) {
	progname = argv[0];
	yyparse();
}

int yylex() {
	int c;
	while ((c = getchar()) == ' ' || c == '\t');
	if (c == EOF) return 0;
	if (isdigit(c)) {
		ungetc(c, stdin);
		scanf("%d", &yylval.n);
		return NUMBER;
	}
	if(islower(c) and c != 'i'){
		yylval.inx = c;
		return VAL;
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
