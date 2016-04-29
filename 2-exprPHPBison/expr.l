%option noyywrap

%{

#include <iostream>
#include <string>
#include "tokens.h"

using namespace std;

string mtext;
int line = 0;

%}

DIGIT [0-9]
LETTER [a-zA-Z]

%x expr_e

%%

"<?" { BEGIN(expr_e); }
.*    { /*mtext += yytext;*/ mtext=yytext; return TK_TEXT; }
\n  { line++; /*mtext += yytext;*/ }

<expr_e>"=" { return '='; }
<expr_e>"+" { return '+'; }
<expr_e>"*" { return '*'; }
<expr_e>"-" { return '-'; }
<expr_e>"/" { return '/'; }
<expr_e>"(" { return '('; }
<expr_e>")" { return ')'; }
<expr_e>"assign" { return TK_ASSIGN; }
<expr_e>[ \t] /* Nada */
<expr_e>\n  { line++; }
<expr_e>{DIGIT}+ { yylval.num_t = atoi(yytext); return NUM; }
<expr_e>{LETTER}({DIGIT}|{LETTER}|_)* { yylval.id_t = strdup(yytext); return ID; }
<expr_e>"//"[^\n]*
<expr_e>"?>" { BEGIN(INITIAL); mtext=""; }
<expr_e>.   /*{ printf(" Linea: %d Simbolo no valido: %s\n", line, yytext); }*/


%%

int yyparse();

int main(){
    yyparse();
}
