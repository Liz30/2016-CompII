%token_type {TokenInfo *}

%left ADD SUB.
%left DIV MULT.

%include{
    #include <cstdio>
    #include <string>
    #include <map>
    #include <stdlib.h>
    #include <sstream>
    #include "expr_h.h"
    #include "tokens.h"

    using namespace std;

    extern int line;
    extern char* mtext;

    map<string, int> vars;
}

%token_destructor { if ($$ != NULL) delete $$; }
%default_type {int}
%token_prefix TK_

%type expr    {int}
%type term    {int}
%type factor  {int}


%syntax_error{
    cout << "Systax Error. Line: " << line << endl;
}

%start_symbol sstart

sstart ::= input EOF.

input ::= input bloque.
input ::= .

bloque ::= text_list.
bloque ::= INIT list_st END.

text_list ::= text_list TEXT(B). { printf("%s", B->lexem.c_str()); }
text_list ::= TEXT(B). { printf("%s", B->lexem.c_str()); }

list_st ::=  list_st st.
list_st ::=  st.

st ::= ASSIGN ID(B) EQUAL expr(C) PC.    {
                          vars[B->lexem] = C;
                        }
st ::= expr(B) PC.      { printf("%d\n", B); }

expr(A) ::= expr(B) ADD term(C). { A = B + C; }
expr(A) ::= expr(B) SUB term(C). { A = B - C; }
expr(A) ::= term(B).          { A = B; }

term(A) ::= term(B) MULT factor(C).   {A = B * C; }
term(A) ::= term(B) DIV factor(C).   { A = B / C; }
term(A) ::= factor(B).            { A = B; }

factor(A) ::= OPAR expr(B) CPAR.    { A = B; }
factor(A) ::= NUM(B).           { A = B->value; }
factor(A) ::= ID(B).            {
                            A = vars[B->lexem];
                        }
