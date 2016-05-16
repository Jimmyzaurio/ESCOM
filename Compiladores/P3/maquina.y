%{
#include "maquina.h"
#include "complejo.h"
#include <iostream>
#include <string>
#include <stdio.h>
#define code2(c1, c2) 		code(c1); code(c2)
#define code3(c1, c2, c3) 	code(c1); code(c2); code(c3)
using namespace std;
%}
%union {
	double n;
	Complejo val = *new Complejo(0, 0);
	Symbol *sym;
}
%token <sym> VAR UNDEF NUMBER
%type <val> expr asgn

%right	'='
%left	'+' '-'
%left	'*' '/' 'i'
%left   UNARYMINUS
%%
list:
	|	list '\n'
	|   list asgn '\n' { code2(pop, STOP); return 1; }
	|	list expr '\n' { code2(print, STOP); return 1; }
	|	list error '\n' { yyerrok; }
	;
asgn: VAR '=' expr { code3(varpush, (Inst)$1, assign); }
	;
expr:  NUMBER 		{ code2(constpush, (Inst)$1); }
	|  VAR 			{ code3(varpush, (Inst)$1, eval); }
	|  expr 'i'		  { code(imag);    }
	|  expr '+' expr  { code(add); }
	|  expr '-' expr  { code(sub); }
	|  expr '*' expr  { code(mul); }
	|  expr '/' expr  { code(division); }
	|  '(' expr ')'
	|  '-' expr %prec UNARYMINUS { code(negar); }
	;
%%

#include <stdio.h>

char *aux;
string progname;
int  lineno = 1;

int main(int argc, char **argv) {
	if(argc > 0) {
		aux = argv[0];
		progname = array_to_string(aux);
	}
	for(initcode(); yyparse(); initcode()) {
		execute(prog);
	}
	return 0;
}

int yylex() {
	int c;
	while ((c = getchar()) == ' ' || c == '\t');
	if (c == EOF) return 0;
	if (c == '.' || isdigit(c)) {
		double d;
		ungetc(c, stdin);
		scanf("%lf", &d);
		//cout << "lei this num  " << d << "\n";
		yylval.sym = install(" ", NUMBER, *new Complejo(d, 0));
		//yylval.val = *new Complejo(d, 0);
		//cout << "hre iam \n";
		return NUMBER;
	}

	if (isalpha(c) && c != 'i') {
		Symbol *s;

		string cad;
		do {
			cad += c;
		} while ((c = getchar()) != EOF && isalnum(c));		
		ungetc(c, stdin);

		if ((s = lookup(cad)) == NULL) {
			s = install(cad, UNDEF, *new Complejo(0, 0));
		}
		yylval.sym = s;
		return s->type == UNDEF ? VAR : s->type;
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

string array_to_string(char *s) {
	return string(s);
}