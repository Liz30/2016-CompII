#include <string>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include "expr_h.h"
#include "tokens.h"

using namespace std;
extern int line;

void *ParseAlloc(void *(*mallocProc)(size_t));
void ParseFree(void *p, void (*freeProc)(void*));
void Parse(void *yyp, int yymajor, TokenInfo *yyminor);
int nextToken(struct TokenInfo *info);

int main(){
  void *parser = ParseAlloc(malloc);
  struct TokenInfo *ti = new TokenInfo;

  int token = nextToken(ti);
  while (token != TK_EOF){

    if (token == TK_TEXT){
        string bloque_text;
        cout << token <<endl;
        while (token == TK_TEXT){
            bloque_text += ti->lexem;
            token=nextToken(ti);
            cout << token <<endl;
        }
        cout << token <<endl;
        cout << " Fin WHILE "<<endl;
        struct TokenInfo *tii = new TokenInfo;
        tii->lexem = bloque_text;
        Parse(parser, TK_TEXT, tii);
        Parse(parser, token, ti);
    }
    else
        Parse(parser, token, ti);

    ti = new TokenInfo;
    token = nextToken(ti);
  }
  Parse(parser, TK_EOF, ti);
  ParseFree(parser, free);
  return 0;
}
