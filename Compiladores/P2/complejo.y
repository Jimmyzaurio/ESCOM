%{
#include <iostream>
#include "hoc.h"
#include "complejo.h"
#include <string>
#include <math.h>
#include <stdio.h>
#define MSDOS
using namespace std;
%}

%union {
	double n;
	Complejo val = *new Complejo(0, 0);
	Symbol *sym;
}

%token <n> NUMBER
%token <sym> VAR INDEF
%type <val> expr asgn

%right '='
%left '+' '-'
%left '*' '/' 'i'
%left UNARYMINUS
%% /* A continuación las reglas gramaticales y las acciones */
list:
	| list '\n'
	| list asgn '\n'
	| list expr '\n'  { $2.imprime(); }
	| list error '\n' { yyerror("Hubo un problema"); } 
	;
asgn:	VAR '=' expr { $$ = $1->val = $3; $1->type = VAR;}
	;
expr: NUMBER { $$ = *new Complejo($1, 0);  }
	| VAR { 
		if($1->type == INDEF) execerror("Variable no definida ", $1->name.c_str());
		$$ = $1->val;
	      }
	| expr 'i'			{ $$ = $1*(*new Complejo(0,1));  }
	| expr '+' expr     { $$ = $1 + $3;  }
	| expr '-' expr     { $$ = $1 - $3;  }
	| expr '*' expr     { $$ = $1 * $3;  }
	| expr '/' expr     { $$ = $1/$3;	 }
	| '(' expr ')'      { $$ = $2; }
	| '-' expr %prec UNARYMINUS { $$= *new Complejo() - $2; }
	;
%%

#include <stdio.h>

char *aux;
string progname;
int lineno = 1;

int main (int argc, char *argv[]){
	aux = argv[0];
	progname = array_to_string(aux);
  	yyparse ();
}

string array_to_string(char *s) {
	return string(s);
}

int yylex (){
  	int c;

  	while ((c = getchar ()) == ' ' || c == '\t');
 	if (c == EOF) return 0;
  	if (c == '.' || isdigit (c)) {
  		ungetc (c, stdin);
  		scanf ("%lf", &yylval.n);
      	return NUMBER;
    }
	if (isalpha(c) && c != 'i') {
		Symbol *s;

		string cad;
		do {
			cad += c;
		} while ((c = getchar()) != EOF && isalnum(c));		
		ungetc(c, stdin);

		if ((s = lookup(cad)) == (Symbol *)NULL)
			s = install(cad, INDEF, *new Complejo(0.0, 0.0));
		yylval.sym = s;   

		return s->type == INDEF? VAR: s->type;		
	}
  	if (c == '\n') {
		lineno++;
	}
  	return c;                                
}

void execerror(string s, string t){
	warning(s, t);
}

void fpecatch(){
	execerror("excepcion de punto flotante", (char *)0);
}

/* Llamada por yyparse ante un error */
void yyerror (string s) {
	warning(s, "---");
}

void warning(string s, string t) {
	fprintf (stderr, "%s: %s", progname.c_str(), s.c_str());
	if(t.length() != 0)
		fprintf (stderr, " %s", t.c_str()); // Lo convertimos a C-array
	fprintf (stderr, "cerca de la linea %d\n", lineno);
}
