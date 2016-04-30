%{
#include <cstdio>
#include <string>
#include <map>
#include "arbol.h"

using namespace std;

int yylex();
extern int line;
extern char* mtext;
Statement *input;

void yyerror(const char *str)
{
    printf("Linea: %d\nError: %s\n", line, str);
}

#define YYERROR_VERBOSE 1

%}

%union {
    char *id_t;
    int  num_t;
    Statement *st_t;
    Expr *expr_t;
}

%token<num_t> NUM
%token<id_t> ID
%token TK_ASSIGN TK_TEXT TK_ERROR
%type<expr_t> expr term factor
%type<st_t> st list_st list_bloque list_text bloque_op

%%

input: list_bloque { input = $1; }
;

list_bloque: list_bloque bloque_op {
                                      if ( ($1->getKind() == CODEBLOCK_ST) ||
                                          ($1->getKind() == TEXTBLOCK_ST) ){
                                              BlockST *b = (BlockST*)$1;
                                              b->blList.push_back($2);
                                              $$ = b;
                                      }
                                      else{
                                          list<Statement *> nl;
                                          nl.push_back($1);
                                          nl.push_back($2);
                                          $$ = new BlockST(nl);
                                      }
                                    }
      | bloque_op         { $$ = $1; }
;

bloque_op:  list_st   { $$ = $1; }
        |   list_text { $$ = $1; }
;

list_text: TK_TEXT { $$ = new TextBlockST(mtext); }
;

list_st:  list_st st  {
                          if ($1->getKind() == CODEBLOCK_ST){
                              CodeBlockST *cb = (CodeBlockST*)$1;
                              cb->stList.push_back($2);
                              $$ = cb;
                          }
                          else {
                              list<Statement *> nl;
                              nl.push_back($1);
                              nl.push_back($2);
                              $$ = new CodeBlockST(nl);
                          }
                      }
        | st          { $$ = $1;}
;

st: TK_ASSIGN ID '=' expr    {
                          string id = $2;
                          free($2);
                          $$ = new AssignST(id, $4);
                        }
    | expr              { $$ = new PrintST($1); }
    |                   { $$ = 0; }
;

expr: expr '+' term { $$ = new SumExpr($1, $3); }
    | expr '-' term { $$ = new RestExpr($1, $3); }
    | term          { $$ = $1; }
;

term: term '*' factor   { $$ = new MultExpr($1, $3); }
    | term '/' factor   { $$ = new DivExpr($1, $3); }
    | factor            { $$ = $1; }
;

factor: '(' expr ')'    { $$ = $2; }
        | NUM           { $$ = new IntExpr($1); }
        | ID            {
                            string id = $1;
                            free($1);
                            $$ = new IdExpr(id);
                        }
;

%%
