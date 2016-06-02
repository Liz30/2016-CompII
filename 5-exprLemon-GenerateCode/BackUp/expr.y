%token_type {TokenInfo *}

%left ADD SUB.
%left DIV MULT.

%include{
    #include <cstdio>
    #include <string>
    #include <map>
    #include <list>
    #include <stdlib.h>
    #include <sstream>
    #include "Utils.h"
    #include "Expression.h"
    #include "Statement.h"
    #include "tokens.h"

    using namespace std;

    extern int line;
    extern char* mtext;

    extern StatementList* stMain;

    void addToList(StatementList* source, StatementList* target){
        StatementList::iterator it = source->begin();
        while (it!=source->end()){
          Statement* n = *it;
          target->push_back(n);
          it++;
        }
    }
}

%token_destructor { if ($$ != NULL) delete $$; }
%default_type {int}
%token_prefix TK_

%type expr    {Expression*}
%type term    {Expression*}
%type factor  {Expression*}
%type exprl   {ExpressionList*}

%type st  {Statement*}
%type list_st {StatementList*}

%type text_list {Statement*}


%syntax_error{
    cout << "Syntax Error. Line: " << line << endl;
}

%start_symbol sstart

sstart ::= input EOF.

input ::= input bloque.
input ::= .

bloque ::= text_list(B).        { stMain->push_back(B); }
bloque ::= INIT list_st(B) END. { addToList(B, stMain); }

text_list(A) ::= TEXT(B). { A = new TextStatement(B->lexem); /*printf("%s", B->lexem.c_str());*/ }

list_st(A) ::=  list_st(B) st(C).  { A = B; A->push_back(C); }
list_st(A) ::=  st(B). { A = new StatementList; A->push_back(B); }

st(A) ::= ID(B) EQUAL expr(C) SEMIC. { A = new AssignStatement(B->lexem, C); }
st(A) ::= PRINT exprl(B) SEMIC.      { A = new PrintStatement(B); }

exprl(A) ::= exprl(B) COMA expr(C). { A = B; A->push_back(C); }
exprl(A) ::= expr(B). { A = new ExpressionList; A->push_back(B); }

expr(A) ::= expr(B) ADD term(C).  { A = new AddExpression(B, C); }
expr(A) ::= expr(B) SUB term(C).  { A = new SubExpression(B, C); }
expr(A) ::= term(B).              { A = B; }

term(A) ::= term(B) MULT factor(C). { A = new MultExpression(B, C); }
term(A) ::= term(B) DIV factor(C).  { A = new DivExpression(B, C); }
term(A) ::= factor(B).              { A = B; }

factor(A) ::= OPAR expr(B) CPAR.  { A = B; }
factor(A) ::= NUM(B).             { A = new IntExpression(B->value); }
factor(A) ::= ID(B).              { A = new IdExpression(B->lexem); }
