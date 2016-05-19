#include "maquina.h"
#include "y.tab.h"
#include<string>
using namespace std;

static struct {         /* Keywords */
    string  name;
    int     kval;
} keywords[] = {
    "if",           IF,
    "else",         ELSE,
    "while",        WHILE,
    "print",        PRINT,
};

void init()     /* install constants and built-ins in table */
{
    int i;
    Symbol *s;
    for (i = 0; i < 4; i++) 
    	install(keywords[i].name, keywords[i].kval, *new Complejo(0.0, 0.0));    
}
