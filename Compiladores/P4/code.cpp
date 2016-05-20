#include <stdio.h>
#include <math.h>
#include "maquina.h"
#include "y.tab.h"

#define NSTACK 1000
#define NPROG  2000

static Datum stack[NSTACK];
static Datum *stackp;

Inst prog[NPROG];
Inst *progp;
static Inst *pc;

void initcode() {
	stackp = stack;
	progp = prog;
}

void push(Datum d) {
	if(stackp >= &stack[NSTACK])
		execerror("stack overflow", nil);	
	*stackp++ = d;
}

Datum pop() {
	if(stackp <= stack)
		execerror("stack underflow", nil);	
	return *--stackp;
}

void xpop(void) {
	if (stackp == stack)
		execerror("stack underflow", " ");
	--stackp;
}

Inst * code(Inst f) {
	Inst *oprogp = progp;
	if (progp >= &prog[NPROG])
		execerror("programa demasiado grande", nil);	
	*progp++ = f;
	return oprogp;
}

void execute(Inst *p) {
	for(pc = p; *pc != STOP; ) {
		(*(*pc++))();
	}
}

void assign() {
	Datum d1, d2;
	d1 = pop();
	d2 = pop();
	if(d1.sym->type != VAR && d1.sym->type != UNDEF)
		execerror("asignacion a una no-variable", d1.sym->name);
	d1.sym->val = d2.val;
	d1.sym->type = VAR;
	push(d2);
}

void varpush() {
	Datum d;
	d.sym = (Symbol *)(*pc++);
	push(d);
}

void constpush() {
	Datum d;
	d.val = ((Symbol *)*pc++)->val;
	//cout << "los valores son : ";
	//d.val.imprime();
	push(d);
}

// inicio practica 5		********************
void whilecode() {
	Datum d;
	Inst *savepc = pc; // cuerpo del loop

	execute(savepc + 2);
	d = pop();
	while (d.val != *new Complejo()) {
		execute(*((Inst **)(savepc)));  // body 
        execute(savepc+2);
        d = pop();
	}
	pc = *((Inst **)(savepc+1));  // next statement 
}

void ifcode() {
	Datum d;	
	Inst *savepc = pc;				// then part
	cout << "empieza if\n";
    execute(savepc+3);  			// condition
    d = pop();
    if (d.val != *new Complejo())
        execute(*((Inst **)(savepc)));
    else if (*((Inst **)(savepc+1))) /* else part */
        execute(*((Inst **)(savepc+1)));
    pc = *((Inst **)(savepc+2));         /* next stmt */
}

// fin practica 5			****************************

void print() {
	Datum d = pop();
	d.val.imprime();
}

void eval() {
	Datum d = pop();
	if (d.sym->type != VAR && d.sym->type != UNDEF)
		execerror("intento de evaluar una no variable\n", d.sym->name);
	if (d.sym->type == UNDEF)
		execerror("variable indefinida", d.sym->name);
	d.val = d.sym->val;
	push(d);
}

void add() {
	Datum d1, d2;
	d1 = pop();
	d2 = pop();
	d1.val = d1.val + d2.val;
	push(d1);
}

void sub() {
	Datum d1, d2;
	d1 = pop();
	d2 = pop();
	d1.val = d2.val - d1.val;
	push(d1);
}

void mul() {
	Datum d1, d2;
	d1 = pop();
	d2 = pop();
	d1.val = d1.val * d2.val;
	push(d1);
}

void division() {
	Datum d1, d2;
	d1 = pop();
	d2 = pop();
	d1.val = d1.val / d2.val;
	push(d1);
}

void negar() {
	Datum d = pop();
	d.val = *new Complejo() - d.val;
	cout << "negado \n";
	push(d);
}

void imag() {
	Datum d = pop();
	d.val = d.val*(*new Complejo(0, 1));
	push(d);
}


// inicio practica 5
void gt() {
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (d1.val > d2.val)? *new Complejo(2.0, 2.0): *new Complejo(0, 0);
    push(d1);
}

void lt() {
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (d1.val < d2.val)? *new Complejo(2.0, 2.0): *new Complejo(0, 0);
    push(d1);
}

void ge() {
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (d1.val >= d2.val)? *new Complejo(2.0, 2.0): *new Complejo(0, 0);
    push(d1);
}

void le() {
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (d1.val <= d2.val)? *new Complejo(2.0, 2.0): *new Complejo(0, 0);
    push(d1);
}

void eq() {
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (d1.val == d2.val)? *new Complejo(2.0, 2.0): *new Complejo(0, 0);
    push(d1);
}

void ne() {
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (d1.val  !=  d2.val)? *new Complejo(2.0, 2.0): *new Complejo(0, 0);
    push(d1);
}

void _and() {
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (d1.val != *new Complejo() && d2.val != *new Complejo())? *new Complejo(2.0, 2.0): *new Complejo(0, 0);
    push(d1);
}

void _or() {
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (d1.val != *new Complejo() || d2.val != *new Complejo())? *new Complejo(2.0, 2.0): *new Complejo(0, 0);
    push(d1);
}

void _not() {
    Datum d;
    d = pop();
    d.val = (d.val == *new Complejo())? *new Complejo(2.0, 2.0): *new Complejo(0, 0);
    push(d);
}

void prexpr() {      /* print numeric value */
    Datum d;
    d = pop();
    //printf("%.8g\n", d.val);
    d.val.imprime();
}
// fin practica 5
