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

  while (true){
    cout <<endl << token ;

    switch(token){
      case TK_EQUAL: cout << " -> EQUAL  "; break;
      case TK_ADD: cout << " -> ADD  "; break;
      case TK_MULT: cout << " -> MULT  "; break;
      case TK_OPENP: cout << " -> OPENP  "; break;
      case TK_CLOSEP: cout << " -> CLOSEP  "; break;
      case TK_SEMIC: cout << " -> SEMIC  "; break;
      case TK_ASSIGN: cout << " -> ASSIGN  "; break;
      case TK_NUM: cout << " -> NUM: "<<num; break;
      case TK_ID: cout << " -> ID: "<<id; break;
      case TK_EOF: cout << " -> EOF  "; return 0;
    }

    token = yylex();
  }
  return 0;
}
