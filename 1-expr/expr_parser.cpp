#include <cstdio>
#include <cstdlib>
#include "tokens.h"

int token;
extern int line;

int yylex();

void L();
void S();
void A();
void E();
void T();
void F();
void match_token(int tk);

void parse_expr()
{
    token = yylex();
    L();
    match_token(TK_EOF);
}

void L()
{
    S();
    
    while (token == TK_SEMIC) {
        token = yylex();
        S();
    }
}

void S()
{
    if (token == TK_ASSIGN)
        A();
    else
        E();
}

void match_token(int tk)
{
    if (token == tk) {
        token = yylex();
    } else {
        printf("Line %d: Expected %d\n", line, tk);
        exit(0);
    }
}

void A()
{
    match_token(TK_ASSIGN);
    match_token(TK_ID);
    match_token(TK_EQUAL);
    E();
}

void E()
{
    T();
    
    while (token == TK_ADD) {
        token = yylex();
        T();
    }
}

void T()
{
    F();
    
    while (token == TK_MULT) {
        token = yylex();
        F();
    }
}

void F()
{
    switch (token) {
        case TK_ID: 
            match_token(TK_ID);
            break;
        case TK_NUM:
            match_token(TK_NUM);
            break;
        case TK_OPENP:
            match_token(TK_OPENP);
            E();
            match_token(TK_CLOSEP);
            break;
        default:
            printf("Line %d: Error: Unexpected %d\n", line, token);
            exit(0);
    }
}

int main()
{
    parse_expr();
}

