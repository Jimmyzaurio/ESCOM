#include  "maquina.h"
#include  "y.tab.h"
using namespace std;

static Symbol *symlist = 0;    /* tabla de simbolos: lista ligada */

/* encontrar s en la tabla de símbolos */
Symbol *lookup(string s) {
	Symbol  *sp;
	//cout << "vamos a buscar " << s << "\n";
	for (sp = symlist; sp != (Symbol *)0; sp = sp->next) 
		if (sp->name.compare(s) == 0) // Lo encontramos
			return sp;
	//cout << "no hubo nada \n";
	return 0;      /* 0 ==> no se encontró */ 
}

/* instalar s en la tabla de símbolos */
Symbol *install(string s,int t, Complejo d) {
	//cout << "here u have  ";
	//d.imprime();
	Symbol *sp;
	//cout << "creamos sp \n";
	sp = (Symbol *) malloc(sizeof(Symbol));	
	//cout << "malloc \n";
	sp->name = s;
	//cout << "name \n";
	sp->type = t;
	//cout << "type \n";
	sp->val = d;
	//cout << "val \n";
	sp->next = symlist;   /*  poner al frente de la lista   */
	//cout << "next \n";
	symlist = sp;
	return sp;
}