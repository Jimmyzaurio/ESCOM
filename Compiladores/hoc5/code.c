#include <stdio.h>

#include "hoc.h"
#include "y.tab.h"

#define NSTACK  256

static Datum stack[NSTACK];
static Datum *stackp;

#define NPROG   2000
Inst prog[NPROG];
static Inst *pc;
Inst *progp;

extern double Pow();

/*
 * prototype
 */

void execute(Inst *p);

void initcode(void)
{
    progp = prog;
    stackp = stack;
}

void push(Datum d)
{
    if (stackp >= &stack[NSTACK])
        execerror("stack too deep", (char *)0);
    *stackp++ = d;
}

Datum pop(void)
{
    if (stackp == stack)
        execerror("stack underflow", (char *)0);
    return *--stackp;
}

void xpop(void) /* for when no value is wanted */
{
    if (stackp == stack)
        execerror("stack underflow", (char *)0);
    --stackp;
}

void constpush(void)
{
    Datum d;
    d.val = ((Symbol *)*pc++)->u.val;
    push(d);
}

void varpush(void)
{
    Datum d;
    d.sym = (Symbol *)(*pc++);
    push(d);
}

void whilecode(void)
{
    Datum d;
    Inst *savepc = pc;  /* loop body */

    execute(savepc+2);  /* condition */
    d = pop();
    while (d.val) {
        execute(*((Inst **)(savepc)));  /* body */
        execute(savepc+2);
        d = pop();
    }
    pc = *((Inst **)(savepc+1));  /* next statement */
}

void ifcode(void)
{
    Datum d;
    Inst *savepc = pc;  /* then part */

    execute(savepc+3);  /* condition */
    d = pop();
    if (d.val)
        execute(*((Inst **)(savepc)));
    else if (*((Inst **)(savepc+1))) /* else part? */
        execute(*((Inst **)(savepc+1)));
    pc = *((Inst **)(savepc+2));         /* next stmt */
}

void bltin(void)
{
    Datum d;
    d = pop();
    d.val = (*(double (*)())(*pc++))(d.val);
    push(d);
}

void eval(void) /* Evaluate variable on stack */
{
    Datum d;
    d = pop();
    if (d.sym->type != VAR && d.sym->type != UNDEF)
        execerror("attempt to evaluate non-variable", d.sym->name);
    if (d.sym->type == UNDEF)
        execerror("undefined variable", d.sym->name);
    d.val = d.sym->u.val;
    push(d);
}

void add(void)
{
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val += d2.val;
    push(d1);
}

void sub(void)
{
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val -= d2.val;
    push(d1);
}

void mul(void)
{
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val *= d2.val;
    push(d1);
}

void divide(void)
{
    Datum d1, d2;
    d2 = pop();
    if (d2.val == 0.0)
        execerror("division by zero", (char *)0);
    d1 = pop();
    d1.val /= d2.val;
    push(d1);
}

void negate(void)
{
    Datum d;
    d = pop();
    d.val =  -d.val;
    push(d);
}

void gt(void)
{
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (double)(d1.val > d2.val);
    push(d1);
}

void lt(void)
{
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (double)(d1.val < d2.val);
    push(d1);
}

void ge(void)
{
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (double)(d1.val >= d2.val);
    push(d1);
}

void le(void)
{
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (double)(d1.val <= d2.val);
    push(d1);
}

void eq(void)
{
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (double)(d1.val == d2.val);
    push(d1);
}

void ne(void)
{
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (double)(d1.val  !=  d2.val);
    push(d1);
}

void and(void)
{
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (double)(d1.val != 0.0 && d2.val != 0.0);
    push(d1);
}

void or(void)
{
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (double)(d1.val != 0.0 || d2.val != 0.0);
    push(d1);
}

void not(void)
{
    Datum d;
    d = pop();
    d.val = (double)(d.val == 0.0);
    push(d);
}

void power(void)
{
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = Pow(d1.val, d2.val);
    push(d1);
}

void assign(void)
{
    Datum d1, d2;
    d1 = pop();
    d2 = pop();
    if (d1.sym->type != VAR && d1.sym->type != UNDEF)
        execerror("assignment to non-variable",
                  d1.sym->name);
    d1.sym->u.val = d2.val;
    d1.sym->type = VAR;
    push(d2);
}

void print(void)
{
    Datum d;
    d = pop();
    printf("\t%.8g\n", d.val);
}

void prexpr(void)       /* print numeric value */
{
    Datum d;
    d = pop();
    printf("%.8g\n", d.val);
}

Inst *code(Inst f)      /* install one instruction or operand */
{
    Inst *oprogp = progp;
    if (progp >= &prog[NPROG])
        execerror("expression too complicated", (char *)0);
    *progp++ = f;
    return oprogp;
}

void execute(Inst *p)
{
    for (pc = p; *pc != STOP; )
        (*(*pc++))();
}

