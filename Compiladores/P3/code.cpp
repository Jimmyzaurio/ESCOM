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
Inst *pc;

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

Inst * code(Inst f) {
	Inst *oprogp = progp;
	if(progp >= &prog[NPROG])
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

void print() {
	Datum d = pop();
	d.val.imprime();
	//printf("\t%.8g\n", d.val);
}

void eval() {
	Datum d = pop();
	if(d.sym->type == UNDEF)
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
	/*
	cout << "antes del imaginario :";
	d.val.imprime();
	d.val = d.val*(*new Complejo(0, 1));
	cout << "despues del imaginario :";
	d.val.imprime();
	*/
	d.val = d.val*(*new Complejo(0, 1));
	push(d);
}