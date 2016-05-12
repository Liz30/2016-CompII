%left PLUS MINUS.
%left MULTIPLY DIVIDE MODULO.
%token_prefix T_

%token_type {Token *}

%include{
    #include <iostream>
    #include <assert.h>
    #include "scalc.h"
    #include "tokens.h"

    using namespace std;
}

l ::= e.
e ::= e PLUS e.
e ::= e MINUS e.
e ::= e MULTIPLY e.
e ::= e DIVIDE e.
e ::= e MODULO e.
e ::= OPEN_PAREN e CLOSE_PAREN.
e ::= number.
number ::= INTEGER.
