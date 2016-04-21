%option noyywrap

%{

#include <iostream>
#include <string>
#include "tokens.h"

using namespace std;

string id;
int num;
int line = 0;

%}

DIGIT [0-9]
LETTER [a-zA-Z]

%%

"=" { return TK_EQUAL; }
"+" { return TK_ADD; }
"*" { return TK_MULT; }
"(" { return TK_OPENP; }
")" { return TK_CLOSEP; }
";" { return TK_SEMIC; }
"assign" { return TK_ASSIGN; }
[ \t] /* Nada */
\n  { line++; }
{DIGIT}+ { num = atoi(yytext); return TK_NUM; }
{LETTER}({DIGIT}|{LETTER})* { id = yytext; return TK_ID; }
"//"[^\n]*
<<EOF>> { return TK_EOF; }
.   { printf("Simbolo no valido\n"); }

%%

int main(){
  int token = yylex();

  while (token != TK_EOF){
    cout << token << endl;
    token = yylex();
  }
  return 0;
}
