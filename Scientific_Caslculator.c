#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_TOK 512
#define PI 3.14159265358979323846

typedef enum { T_NUM, T_OP, T_FUNC, T_LP, T_RP } TokType;

typedef struct {
    TokType type;
    double  val;   
    char    op;   
    int     fn;   
} Token;

static int    deg_mode = 1;
static double last_ans = 0.0;
static char   errmsg[128];


typedef double (*Fn)(double);

static double f_sin(double x)  { return sin(deg_mode ? x * PI / 180 : x); }
static double f_cos(double x)  { return cos(deg_mode ? x * PI / 180 : x); }
static double f_tan(double x)  { return tan(deg_mode ? x * PI / 180 : x); }
static double f_asin(double x) { double r = asin(x); return deg_mode ? r * 180 / PI : r; }
static double f_acos(double x) { double r = acos(x); return deg_mode ? r * 180 / PI : r; }
static double f_atan(double x) { double r = atan(x); return deg_mode ? r * 180 / PI : r; }
static double f_fact(double x) {
    if (x < 0 || x != floor(x) || x > 170) return NAN;
    double r = 1;
    for (int i = 2; i <= (int)x; i++) r *= i;
    return r;
}

static const struct { const char *name; Fn f; } FUNCS[] = {
    {"sin", f_sin}, {"cos", f_cos}, {"tan", f_tan},
    {"asin", f_asin}, {"acos", f_acos}, {"atan", f_atan},
    {"sinh", sinh}, {"cosh", cosh}, {"tanh", tanh},
    {"log", log10}, {"ln", log}, {"sqrt", sqrt}, {"cbrt", cbrt},
    {"exp", exp}, {"abs", fabs}, {"floor", floor}, {"ceil", ceil},
    {"fact", f_fact},
};
#define NFUNCS ((int)(sizeof(FUNCS) / sizeof(FUNCS[0])))


static int tokenize(const char *s, Token *out, int *n) {
    int cnt = 0;
    const char *p = s;
    while (*p) {
        if (isspace((unsigned char)*p)) { p++; continue; }
        if (cnt >= MAX_TOK - 1) { strcpy(errmsg, "expression too long"); return 0; }

        int prev_value = cnt > 0 &&
            (out[cnt-1].type == T_NUM || out[cnt-1].type == T_RP ||
             (out[cnt-1].type == T_OP && out[cnt-1].op == '!'));

        if (isdigit((unsigned char)*p) || *p == '.') {
            char *end;
            double v = strtod(p, &end);
            if (end == p) { strcpy(errmsg, "bad number"); return 0; }
            out[cnt++] = (Token){T_NUM, v, 0, 0};
            p = end;
        } else if (isalpha((unsigned char)*p)) {
            char name[32]; int i = 0;
            while (isalpha((unsigned char)*p) && i < 31) name[i++] = *p++;
            name[i] = 0;
            if (!strcmp(name, "pi"))       out[cnt++] = (Token){T_NUM, PI, 0, 0};
            else if (!strcmp(name, "e"))   out[cnt++] = (Token){T_NUM, M_E, 0, 0};
            else if (!strcmp(name, "ans")) out[cnt++] = (Token){T_NUM, last_ans, 0, 0};
            else {
                int k, found = -1;
                for (k = 0; k < NFUNCS; k++) if (!strcmp(name, FUNCS[k].name)) { found = k; break; }
                if (found < 0) { snprintf(errmsg, sizeof errmsg, "unknown name '%s'", name); return 0; }
                out[cnt++] = (Token){T_FUNC, 0, 0, found};
            }
        } else if (*p == '(') { out[cnt++] = (Token){T_LP, 0, 0, 0}; p++; }
        else if (*p == ')')   { out[cnt++] = (Token){T_RP, 0, 0, 0}; p++; }
        else if (strchr("+-*/%^!", *p)) {
            char c = *p++;
            if (c == '-' && !prev_value) c = 'u';         
            else if (c == '+' && !prev_value) continue;   
            out[cnt++] = (Token){T_OP, 0, c, 0};
        } else {
            snprintf(errmsg, sizeof errmsg, "unexpected character '%c'", *p);
            return 0;
        }
    }
    *n = cnt;
    return 1;
}

static int prec(char op) {
    switch (op) {
        case '+': case '-': return 1;
        case '*': case '/': case '%': return 2;
        case 'u': return 3;
        case '^': return 4;
        case '!': return 5;
    }
    return 0;
}
static int right_assoc(char op) { return op == '^' || op == 'u'; }

static int to_rpn(const Token *in, int n, Token *out, int *m) {
    Token st[MAX_TOK]; int sp = 0, o = 0;
    for (int i = 0; i < n; i++) {
        Token t = in[i];
        switch (t.type) {
        case T_NUM:  out[o++] = t; break;
        case T_FUNC: st[sp++] = t; break;
        case T_OP:
            if (t.op == '!') { out[o++] = t; break; }   
            if (t.op != 'u') {                             
                while (sp > 0 && st[sp-1].type == T_OP) {
                    char top = st[sp-1].op;
                    if (prec(top) > prec(t.op) ||
                        (prec(top) == prec(t.op) && !right_assoc(t.op)))
                        out[o++] = st[--sp];
                    else break;
                }
            }
            st[sp++] = t;
            break;
        case T_LP: st[sp++] = t; break;
        case T_RP:
            while (sp > 0 && st[sp-1].type != T_LP) out[o++] = st[--sp];
            if (sp == 0) { strcpy(errmsg, "mismatched ')'"); return 0; }
            sp--;                                           /* discard '(' */
            if (sp > 0 && st[sp-1].type == T_FUNC) out[o++] = st[--sp];
            break;
        }
    }
    while (sp > 0) {
        if (st[sp-1].type == T_LP) { strcpy(errmsg, "mismatched '('"); return 0; }
        out[o++] = st[--sp];
    }
    *m = o;
    return 1;
}

static int eval_rpn(const Token *rpn, int n, double *result) {
    double st[MAX_TOK]; int sp = 0;
    for (int i = 0; i < n; i++) {
        Token t = rpn[i];
        if (t.type == T_NUM) { st[sp++] = t.val; continue; }
        if (t.type == T_FUNC) {
            if (sp < 1) { strcpy(errmsg, "missing function argument"); return 0; }
            st[sp-1] = FUNCS[t.fn].f(st[sp-1]);
            continue;
        }
        if (t.op == 'u' || t.op == '!') {
            if (sp < 1) { strcpy(errmsg, "missing operand"); return 0; }
            st[sp-1] = (t.op == 'u') ? -st[sp-1] : f_fact(st[sp-1]);
            continue;
        }
        if (sp < 2) { strcpy(errmsg, "missing operand"); return 0; }
        double b = st[--sp], a = st[sp-1], r = 0;
        switch (t.op) {
            case '+': r = a + b; break;
            case '-': r = a - b; break;
            case '*': r = a * b; break;
            case '/': if (b == 0) { strcpy(errmsg, "division by zero"); return 0; } r = a / b; break;
            case '%': if (b == 0) { strcpy(errmsg, "modulo by zero"); return 0; } r = fmod(a, b); break;
            case '^': r = pow(a, b); break;
        }
        st[sp-1] = r;
    }
    if (sp != 1) { strcpy(errmsg, "malformed expression"); return 0; }
    if (isnan(st[0])) { strcpy(errmsg, "math domain error"); return 0; }
    *result = st[0];
    return 1;
}

static int calculate(const char *expr, double *res) {
    Token toks[MAX_TOK], rpn[MAX_TOK];
    int n, m;
    errmsg[0] = 0;
    if (!tokenize(expr, toks, &n)) return 0;
    if (n == 0) { strcpy(errmsg, "empty expression"); return 0; }
    if (!to_rpn(toks, n, rpn, &m)) return 0;
    return eval_rpn(rpn, m, res);
}

static void help(void) {
    puts("Operators: + - * / % ^ !   Parentheses: ( )\n"
         "Constants: pi e ans\n"
         "Functions: sin cos tan asin acos atan sinh cosh tanh\n"
         "           log ln sqrt cbrt exp abs floor ceil fact\n"
         "Commands : mode deg | mode rad | help | quit");
}

static void run(const char *line) {
    if (!strcmp(line, "mode deg")) { deg_mode = 1; puts("Degrees mode"); return; }
    if (!strcmp(line, "mode rad")) { deg_mode = 0; puts("Radians mode"); return; }
    if (!strcmp(line, "help"))     { help(); return; }
    double r;
    if (calculate(line, &r)) { last_ans = r; printf("= %.10g\n", r); }
    else printf("Error: %s\n", errmsg);
}

int main(int argc, char **argv) {
    if (argc > 1) { run(argv[1]); return 0; }
    char line[512];
    puts("Scientific Calculator  (type 'help' or 'quit')");
    for (;;) {
        printf("[%s] > ", deg_mode ? "DEG" : "RAD");
        if (!fgets(line, sizeof line, stdin)) break;
        line[strcspn(line, "\n")] = 0;
        if (!strcmp(line, "quit") || !strcmp(line, "exit")) break;
        if (line[0]) run(line);
    }
    return 0;
}
