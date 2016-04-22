%option noyywrap

%{

#include <iostream>
#include <string>
#include "tokens.h"

using namespace std;

string id;
string merror, mcomment, mtext;
int inum;
float fnum;
int line = 0;

%}

DIGIT [0-9]
LETTER [a-zA-Z]

%x expr

%%

"<?" { BEGIN(expr); return TK_PHPInit; }
. { mtext = yytext; return TK_TEXT; }
\n  { line++; }

<expr>"=" { return TK_EQUAL; }
<expr>"+" { return TK_ADD; }
<expr>"*" { return TK_MULT; }
<expr>"(" { return TK_OPENP; }
<expr>")" { return TK_CLOSEP; }
<expr>";" { return TK_SEMIC; }
<expr>"assign" { return TK_ASSIGN; }
<expr>[ \t] /* Nada */
<expr>\n  { line++; }
<expr>{DIGIT}+ { inum = atoi(yytext); return TK_INT; }
<expr>{DIGIT}+.{DIGIT}+ { fnum = atof(yytext); return TK_FLOAT; }
<expr>{LETTER}({DIGIT}|{LETTER}|_)* { id = yytext; return TK_ID; }
<expr>"//"[^\n]*  { mcomment = yytext; return TK_COMMENT; }
<expr>.   { merror = yytext; return TK_ERROR; }
<expr>"?>" { BEGIN(INITIAL); return TK_PHPEnd; }

<<EOF>> { return TK_EOF; }

%%

int main(){
  int token = yylex();

  while (true){
    cout << line << " ... " << token ;

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
      case TK_TEXT: cout << " -> TEXT: " << mtext; break;
      case TK_PHPInit: cout << " -> PHP Init "; break;
      case TK_PHPEnd: cout << " -> PHP End "; break;
    }
    cout << endl;
    token = yylex();
  }
  return 0;
}
