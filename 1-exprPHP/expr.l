%option noyywrap

%{

#include <iostream>
#include <string>
#include "tokens.h"

using namespace std;

string id;
string merror, mcomment;
int inum;
float fnum;
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
{DIGIT}+ { inum = atoi(yytext); return TK_INT; }
{DIGIT}+.{DIGIT}+ { fnum = atof(yytext); return TK_FLOAT; }
{LETTER}({DIGIT}|{LETTER}|_)* { id = yytext; return TK_ID; }
"//"[^\n]*  { mcomment = yytext; return TK_COMMENT; }
<<EOF>> { return TK_EOF; }
.   { merror = yytext; return TK_ERROR; }

%%

int main(){
  int token = yylex();

  while (true){
    cout << token ;

    switch(token){
      case TK_EQUAL: cout << " -> EQUAL  "; break;
      case TK_ADD: cout << " -> ADD  "; break;
      case TK_MULT: cout << " -> MULT  "; break;
      case TK_OPENP: cout << " -> OPENP  "; break;
      case TK_CLOSEP: cout << " -> CLOSEP  "; break;
      case TK_SEMIC: cout << " -> SEMIC  "; break;
      case TK_ASSIGN: cout << " -> ASSIGN  "; break;
      case TK_INT: cout << " -> INT: "<<inum; break;
      case TK_ID: cout << " -> ID: "<<id; break;
      case TK_EOF: cout << " -> EOF  "; return 0;
      case TK_FLOAT: cout << " -> FLOAT: "<<fnum; break;
      case TK_ERROR: cout << " -> Simbolo no valido: " << merror; break;
      case TK_COMMENT: cout << " -> COMMENT: "<< mcomment; break;
    }
    cout << endl;
    token = yylex();
  }
  return 0;
}
