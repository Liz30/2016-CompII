%option noyywrap
%option outfile="lex.cpp"

%{
    #include <iostream>
    #include <string>
    #include <stdlib.h>
    #include <vector>
    #include "scalc.h"
    #include "scalc_l.h"
    #include "tokens.h"

    using namespace std;

    #define ERROR_MSG(msg){
          std::cerr << "Error en linea: " << __LINE__ << " Mensaje: " << msg << endl;
    }

    #define ERROR() ERROR_MSG(" lalalalallala ")

    Token *pack_token(int type);
    void clean_tokens();
    vector<Token *> tokens;
    int next_token;
    int line = 0;

%}

DIGIT [0-9]

%%

"(" { return T_OPEN_PAREN; }
")" { return T_CLOSE_PAREN; }
"+" { return T_PLUS; }
"-" { return T_MINUS; }
"*" { return T_MULTIPLY; }
"/" { return T_DIVIDE; }
"%" { return T_MODULO; }
{DIGIT}+ { return INTEGER; }
\n { line++; return NEWLINE; }
[ \t\b\v]+
. { ERROR_MSG("Simbolo No Valido: " + yytext); }

%%



extern void *ParseAlloc(void *(*mallocProc)(size_t));
extern void ParseFree(void *p, void (*freeProc)(void*));
extern void Parse(void *yyp, int yymajor, Token *yyminor);
extern int line;

int main()
{
    void* parser;
    atexit(clean_tokens);

    for (;;){
        cout << "> ";
        fflush(stdout);

        clean_tokens();
        yylex();

        parser = ParseAlloc(malloc);

        if (tokens.size() > 1){
            next_token = 0;
            while (next_token < tokens.size()){
                Parse(parser, tokens[next_token]->type, tokens[next_token]);
                next_token++;
            }

            next_token = 0;

            if ( L() && next_token == tokens.size()){
                cout << "OK" << endl;
            }
            else{
                ERROR_MSG("Error de Sintaxis. Linea: " << line;)
            }
        }
        ParseFree(parser, free);
    }
    return 0;
}

Token *pack_token(int type){
    Token *t = new Token;
    if (!t)
        ERROR_MSG("Token no pudo crearse");
    return t;
}
