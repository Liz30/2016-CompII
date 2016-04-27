%option noyywrap

%{

#include <iostream>
#include <string>
#include "tokens.h"

using namespace std;

string id, merror, mcomment, mtext;
int inum;
float fnum;
int line = 0;

%}

DIGIT [0-9]
LETTER [a-zA-Z]

%x expr_e
%x text_e

%%

"<?" { BEGIN(expr_e); return TK_PHPInit; }
.    { mtext += yytext; BEGIN(text_e); return TK_TEXTInit; }
\n  { line++; }
<<EOF>> { return TK_EOF; }

<text_e>"<?" { BEGIN (expr_e); return TK_PHPInit; }
<text_e>.* { mtext += yytext; }
<text_e>\n { line++; mtext += yytext; }

<expr_e>"=" { return TK_EQUAL; }
<expr_e>"+" { return TK_ADD; }
<expr_e>"*" { return TK_MULT; }
<expr_e>"(" { return TK_OPENP; }
<expr_e>")" { return TK_CLOSEP; }
<expr_e>";" { return TK_SEMIC; }
<expr_e>"assign" { return TK_ASSIGN; }
<expr_e>[ \t] /* Nada */
<expr_e>\n  { line++; }
<expr_e>{DIGIT}+ { inum = atoi(yytext); return TK_INT; }
<expr_e>{DIGIT}+.{DIGIT}+ { fnum = atof(yytext); return TK_FLOAT; }
<expr_e>{LETTER}({DIGIT}|{LETTER}|_)* { id = yytext; return TK_ID; }
<expr_e>"//"[^\n]*  { mcomment = yytext; return TK_COMMENT; }
<expr_e>.   { merror = yytext; return TK_ERROR; }
<expr_e>"?>" { BEGIN(INITIAL); return TK_PHPEnd; }


%%

int main(){
  int token = yylex();

  while (true){
    //cout << "Linea: "<< line << "... Token: " << token ;

    switch(token){
      case TK_EQUAL: cout << "Linea: "<< line << "... Token: " << token << " -> EQUAL  "; break;
      case TK_ADD: cout << "Linea: "<< line << "... Token: " << token << " -> ADD  "; break;
      case TK_MULT: cout << "Linea: "<< line << "... Token: " << token << " -> MULT  "; break;
      case TK_OPENP: cout << "Linea: "<< line << "... Token: " << token << " -> OPENP  "; break;
      case TK_CLOSEP: cout << "Linea: "<< line << "... Token: " << token << " -> CLOSEP  "; break;
      case TK_SEMIC: cout << "Linea: "<< line << "... Token: " << token << " -> SEMIC  "; break;
      case TK_ASSIGN: cout << "Linea: "<< line << "... Token: " << token << " -> ASSIGN  "; break;
      case TK_INT: cout << "Linea: "<< line << "... Token: " << token << " -> INT: "<<inum; break;
      case TK_ID: cout << "Linea: "<< line << "... Token: " << token << " -> ID: "<<id; break;
      case TK_EOF: cout << mtext << "Linea: "<< line << "... Token: " << token << " -> EOF  "; return 0;
      case TK_FLOAT: cout << "Linea: "<< line << "... Token: " << token << " -> FLOAT: "<<fnum; break;
      case TK_ERROR: cout << "Linea: "<< line << "... Token: " << token << " -> Simbolo no valido: " << merror; break;
      case TK_COMMENT: cout << "Linea: "<< line << "... Token: " << token << " -> COMMENT: "<< mcomment; break;
      case TK_TEXTInit: cout << "Linea: "<< line << "... Token: " << token << " -> TEXT: "; break;
      case TK_TEXTEnd: cout << mtext; mtext=" "; break;
      case TK_PHPInit: cout << mtext << "Linea: "<< line << "... Token: " << token << " -> PHP Init "; mtext=""; break;
      case TK_PHPEnd: cout << "Linea: "<< line << "... Token: " << token << " -> PHP End "; break;
    }
    cout << endl;
    token = yylex();
  }
  return 0;
}
