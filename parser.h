#ifndef PARSER
#define PARSER

#include "lexer.h"
#include "numfunc.h"
#include "strfunc.h"
#include "vartable.h"


double func(string);
double primary();
double power();
double term();
double expression();
double define();
double statement();
void calculate();

#endif // PARSER

