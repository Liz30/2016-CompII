#include <string>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <list>
#include <map>
#include "Utils.h"
#include "Expression.h"
#include "Statement.h"
#include "tokens.h"

using namespace std;
extern int line;
map<string, int> vars;

StatementList* stMain;

void *ParseAlloc(void *(*mallocProc)(size_t));
void ParseFree(void *p, void (*freeProc)(void*));
void Parse(void *yyp, int yymajor, TokenInfo *yyminor);
int nextToken(struct TokenInfo *info);

int main(){
  stMain = new StatementList;
  void *parser = ParseAlloc(malloc);
  struct TokenInfo *ti = new TokenInfo;

  int token = nextToken(ti);
  while (token != TK_EOF){
    Parse(parser, token, ti);
    ti = new TokenInfo;
    token = nextToken(ti);
  }
  Parse(parser, TK_EOF, ti);
  ParseFree(parser, free);

  //cout<<"ANTES"<<endl;
  //cout<<"Instructions: "<<stMain->size()<<endl<<endl;
  //cout<<"Vars MAIN: "<<vars.size()<<endl<<endl;

  StatementList::iterator it = stMain->begin();
  while(it != stMain->end()){
    Statement* n = *it;
    n->Execute();
    //cout<<"Type: "<<n->getKind()<<endl;
    it++;
  }



  return 0;
}
