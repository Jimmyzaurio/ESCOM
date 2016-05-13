%{
#include "hoc.h"
#include <iostream>
#include <string>
#include <math.h>
#include <stdio.h>
#define MSDOS
using namespace std;

void yyerror (string s);
int yylex ();
void warning(string s, string t);
void execerror(string s, string t);
void fpecatch();
string array_to_string(char *s);
%}

%union {
	double val;
	Symbol *sym;
}

%token <val> NUMBER
%token <sym> VAR INDEF
%type <val> expr asgn

%right '='
%left '+' '-'
%left '*' '/'
%left UNARYMINUS
%right '^'

%% /* A continuación las reglas gramaticales y las acciones */
list:   
	| list '\n'
	| list asgn '\n'
	| list expr '\n'  { cout << $2 << "\n"; }
	| list error '\n' { yyerror("Hubo un problema"); } 
	;
asgn:	VAR '=' expr { $$ = $1->u.val = $3; $1->type = VAR;}
	;
expr:      NUMBER { $$ = $1;  }
	| VAR { 
		if($1->type == INDEF) execerror("variable no definida ", $1->name.c_str());
		$$ = $1->u.val;
	      }
	| expr '+' expr     { $$ = $1 + $3;  }
	| expr '-' expr     { $$ = $1 - $3;  }
	| expr '*' expr     { $$ = $1 * $3;  }
	| expr '/' expr     {
		if($3==0.0)
			execerror("division por cero", "");
		$$ = $1/$3; }
	| '(' expr ')'      { $$ = $2;}
	| '-' expr %prec UNARYMINUS { $$= -$2; }
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
  		scanf ("%lf", &yylval.val);
      	return NUMBER;
    }
	if (isalpha(c)) {
		Symbol *s;
		char sbuf[200], *p = sbuf;
		do {
			*p++ = c;
		} while ((c = getchar()) != EOF && isalnum(c));
		ungetc(c, stdin);
		*p='\0';

		//cout << "ya leimos \n";
		string wer(sbuf);
		//cout << "manda esto  " << wer << "/\n";

		if ((s = lookup(sbuf)) == (Symbol *)NULL)
			s = install(sbuf, INDEF, 0.0);
		//cout << "intalamos \n";
		yylval.sym = s;   
		if (s->type == INDEF) {
			return VAR;
		} else {
 			//printf("func=(%s) tipo=(%d) \n", s->name, s->type);
			return s->type;
		}
	}
  	if (c == '\n') {
		lineno++;
	}
  	return c;                                
}

void execerror(string s, string t){
	warning(s, t);
	//longjmp(begin, 0);
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
