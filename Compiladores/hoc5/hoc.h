typedef struct Symbol { /* symbol table entry */
    char    *name;
    short   type;   /* VAR, BLTIN, UNDEF */
    union {
	double  val;            /* if VAR */
	double  (*ptr)();       /* if BLTIN */
    } u;
    struct Symbol   *next;  /* to link to another */
} Symbol;

Symbol *install(char *s, int t, double d);
Symbol *lookup(char *s);

typedef union Datum {   /* interpreter stack type */
    double  val;
    Symbol  *sym;
} Datum;

typedef void (*Inst)(void);  /* machine instruction */
#define STOP    (Inst) 0

extern Inst prog[], *progp;
extern Inst *code(Inst f);
extern Datum pop(void);
extern void xpop(void);
extern void eval(void);
extern void add(void);
extern void sub(void);
extern void mul(void);
extern void divide(void);
extern void negate(void);
extern void power(void);
extern void assign(void);
extern void bltin(void);
extern void varpush(void);
extern void constpush(void);
extern void print(void);
extern void prexpr(void);
extern void gt(void);
extern void lt(void);
extern void eq(void);
extern void ge(void);
extern void le(void);
extern void ne(void);
extern void and(void);
extern void or(void);
extern void not();
extern void ifcode(void);
extern void whilecode();
