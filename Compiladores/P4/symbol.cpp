#include  "maquina.h"
#include  "y.tab.h"
using namespace std;

static Symbol *symlist = 0;    /* tabla de simbolos: lista ligada */

/* encontrar s en la tabla de símbolos */
Symbol *lookup(string s) {
	Symbol  *sp;
	for (sp = symlist; sp != (Symbol *)0; sp = sp->next) 
		if (sp->name.compare(s) == 0) // Lo encontramos
			return sp;		
	return 0;      /* 0 ==> no se encontró */ 
}

/* instalar s en la tabla de símbolos */
Symbol *install(string s,int t, Complejo d) {	
	Symbol *sp;
	sp = (Symbol *) malloc(sizeof(Symbol));	
	sp->name = s;
	sp->type = t;
	sp->val = d;
	sp->next = symlist;   /*  poner al frente de la lista   */
	symlist = sp;
	return sp;
}