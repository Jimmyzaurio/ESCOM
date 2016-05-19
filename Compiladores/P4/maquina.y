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
	//double n;
	//Complejo val = *new Complejo(0, 0);
	Inst *val;
	Symbol *sym;
}
%token  <sym>   NUMBER PRINT VAR UNDEF WHILE IF ELSE
%type   <val>  stmt asgn expr stmtlist cond while if end

%right	'='
%left	OR					//  Asociacion
%left	AND					//   practica
%left	GT GE LT LE EQ NE 	//      5
%left	'+' '-'
%left	'*' '/' 'i'
%left   UNARYMINUS NOT		// practica 5
%%
list: 	/* nada */
		|	list '\n'
		|   list asgn '\n' { code2(xpop, STOP); return 1; }
		|   list stmt '\n' { code(STOP); return 1; }			// Practica 5
		|	list expr '\n' { code2(print, STOP); return 1; }
		|	list error '\n' { yyerrok; }
		;
asgn:	VAR '=' expr { cout << "asignando\n"; $$ = $3; code3(varpush, (Inst)$1, assign); }
		;
stmt:		expr		{ code(xpop); }
		|	PRINT expr	{ code(prexpr); $$ = $2; }
		|	while cond stmt end	{
			($1)[1] = (Inst)$3;		// cuerpo del loop
			($1)[2] = (Inst)$4;		// end, if cond fails
								}
		|	if cond stmt end	{
			($1)[1] = (Inst)$3;		// then part
			($1)[3] = (Inst)$4;	}	// fin del if
		|	if cond stmt end ELSE stmt end	{
			($1)[1] = (Inst)$3;		// then part
			($1)[2] = (Inst)$6;		// fin del if
			($1)[3] = (Inst)$7;		// fin del if
											}
		|	'{' stmtlist '}'      { $$ = $2; }
	    ;
cond:	'(' expr ')'  { cout << "condicion\n"; code(STOP); $$ = $2; }
    	;
while:	WHILE { $$ = code3(whilecode, STOP, STOP); }
        ;
if:		IF    { cout << "hay un if\n"; $$ = code(ifcode); code3(STOP, STOP, STOP); }
        ;
end:      /* nothing */         { code(STOP); $$ = progp; }
        ;
stmtlist: /* nothing */         { $$ = progp; }
	    | stmtlist '\n'
	    | stmtlist stmt
	    ;    
expr:		NUMBER			{ code2(constpush, (Inst)$1); }
		|	VAR 			{ code3(varpush, (Inst)$1, eval); }
		|	asgn
		|	'(' expr ')'	{ $$ = $2; }
		|	expr '+' expr  	{ code(add);  }
		|	expr '-' expr  	{ code(sub);  }
		|	expr '*' expr  	{ code(mul);  }
		|	expr '/' expr  	{ code(division); }
		|	expr 'i'		{ code(imag); }
		|	'-' expr %prec UNARYMINUS { $$ = $2; code(negar); }
        | expr GT expr  { code(gt); }
        | expr GE expr  { code(ge); }
        | expr LT expr  { cout << "menor que\n"; code(lt); }
        | expr LE expr  { code(le); }
        | expr EQ expr  { code(eq); }
        | expr NE expr  { code(ne); }
        | expr AND expr { code(_and); }
        | expr OR expr  { code(_or); }
        | NOT expr      { $$ = $2; code(_not); }
		;
%%

#include <stdio.h>
//#include "init.cpp" // no estoy seguro

char *aux;
string progname;
int  lineno = 1;

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
		return s->type == UNDEF? VAR: s->type;
	}

	switch (c) {
		case '>':       return follow('=', GE, GT);
	    case '<':       return follow('=', LE, LT);
	    case '=':       return follow('=', EQ, '=');
	    case '!':       return follow('=', NE, NOT);
	    case '|':       return follow('|', OR, '|');
	    case '&':       return follow('&', AND, '&');
	    case '\n':      lineno++; return '\n';
	    default:        return c;
	}
}

int follow(int expect, int ifyes, int ifno) {
	int c = getchar();

	if (c == expect) return ifyes;
    ungetc(c, stdin);
    return ifno;
}

int main(int argc, char **argv) {
	if(argc > 0) {
		aux = argv[0];
		progname = array_to_string(aux);
	}
	init();
	for(initcode(); yyparse(); initcode()) {
		execute(prog);
	}
	return 0;
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