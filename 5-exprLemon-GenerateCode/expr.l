%option noyywrap

%{

#include <iostream>
#include <string>
#include <stdlib.h>
#include "Utils.h"
#include "tokens.h"

using namespace std;

string mtext;
int line = 0;


#define YY_DECL int nextToken(struct TokenInfo *info)

#define RETURN_TOKEN (tk) do{ \
                                info->lexem = yytext; \
                                return tk; \
                            } while (0)

%}

DIGIT [0-9]
LETTER [a-zA-Z]

%x expr_e

%%

"<?" { BEGIN(expr_e); return TK_INIT; }

<expr_e>"=" { return TK_EQUAL; }
<expr_e>"+" { return TK_ADD; }
<expr_e>"*" { return TK_MULT; }
<expr_e>"-" { return TK_SUB; }
<expr_e>"/" { return TK_DIV; }
<expr_e>"(" { return TK_OPAR; }
<expr_e>")" { return TK_CPAR; }
<expr_e>";" { return TK_SEMIC; }
<expr_e>"," { return TK_COMA; }

<expr_e>"print"   { return TK_PRINT; }
<expr_e>[ \t]
<expr_e>\n  { line++; }
<expr_e>{DIGIT}+ { info->value = atoi(yytext); info->type=INT; return TK_NUM; }
<expr_e>{LETTER}({DIGIT}|{LETTER}|_)* { info->lexem = yytext; info->type=STRING; return TK_ID; }
<expr_e>"//"[^\n]*
<expr_e>"?>" { BEGIN(INITIAL); return TK_END;}
<expr_e>.   { printf(" Linea: %d Simbolo no valido: %s\n", line, yytext); }
<expr_e><<EOF>> { return TK_EOF; }

.*    { info->lexem=yytext; info->type=STRING; return TK_TEXT; }
\n  { line++; info->lexem = yytext; info->type=STRING; return TK_TEXT; }
<<EOF>> { return TK_EOF; }



%%
