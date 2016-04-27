%{
#include <cstdio>
#include <string>
#include <map>

using namespace std;

int yylex();

void yyerror(const char *str)
{
    printf("%s\n", str);
}

map<string, int> vars;

#define YYERROR_VERBOSE 1

%}

%union {
    char *id_t;
    int  num_t;
}

%token<num_t> NUM
%token<id_t> ID
%token TK_ASSIGN
%type<num_t> expr term factor

%%

input: list_st
;

list_st: list_st st
        | st
;

st: TK_ASSIGN ID '=' expr    {
                          string id = $2;

                          free($2);
                          vars[id] = $4;
                        }
    | expr              { printf("%d\n", $1); }
;

expr: expr '+' term { $$ = $1 + $3; }
    | expr '-' term { $$ = $1 - $3; }
    | term          { $$ = $1; }
;

term: term '*' factor   { $$ = $1 * $3; }
    | term '/' factor   { $$ = $1 / $3; }
    | factor            { $$ = $1; }
;

factor: '(' expr ')'    { $$ = $2; }
        | NUM           { $$ = $1; }
        | ID            {
                            string id = $1;

                            free($1);
                            $$ = vars[id];
                        }
;

%%
