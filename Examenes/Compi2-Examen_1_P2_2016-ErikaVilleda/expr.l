%option noyywrap

%{

#include <cstdlib>
#include <iostream>
#include <string>
#include "lexer_util.h"
#include "tokens.h"

using namespace std;

string text;
int line = 1;
int hasText = 0;

#define YY_DECL int nextToken(struct TokenInfo *&p_info)

#define RETURN_TOKEN(tk) do {   \
                            p_info = NULL; \
                            return tk;  \
                        } while(0)

string getSymbol(char ch) {
    string str = "";

    if (ch >=32 && ch <=128)
        str += ch;
    else {
        str = ::convertToString((int)ch);
    }

    return str;
}

%}

%x expr

DIGIT [0-9]
LETTER [a-zA-Z]

%%

<expr>"<?" { BEGIN(expr); }
<expr>"=" { RETURN_TOKEN(TK_EQUAL); }
<expr>"+" { RETURN_TOKEN(TK_ADD); }
<expr>"-" { RETURN_TOKEN(TK_SUB); }
<expr>"*" { RETURN_TOKEN(TK_MULT); }
<expr>"/" { RETURN_TOKEN(TK_DIV); }
<expr>"(" { RETURN_TOKEN(TK_LPAREN); }
<expr>")" { RETURN_TOKEN(TK_RPAREN); }
<expr>";" { RETURN_TOKEN(TK_SEMICOLON); }
<expr>"<" { RETURN_TOKEN(TK_LESS); }
<expr>"{" { RETURN_TOKEN(TK_LSET); }
<expr>"}" { RETURN_TOKEN(TK_RSET); }
<expr>"assign" { RETURN_TOKEN(KW_ASSIGN); }
<expr>"print" { RETURN_TOKEN(KW_PRINT); }
<expr>"if"  { RETURN_TOKEN(KW_IF); }
<expr>"else" { RETURN_TOKEN(KW_ELSE); }
<expr>"while" { RETURN_TOKEN(KW_WHILE); }
<expr>[ \t] /* Nada */
<expr>\n  { line++; }
<expr>{DIGIT}+ {
                    p_info = allocTokenInfo(TK_NUM, yytext);
                    p_info->intValue = atoi(yytext);
                    return TK_NUM;
               }
<expr>{LETTER}({DIGIT}|{LETTER})* {
                                    p_info = allocTokenInfo(TK_ID, yytext);
                                    return TK_ID;
                                  }
<expr>"//"[^\n]*
<expr>"?>" { BEGIN(INITIAL); }
<expr><<EOF>> { RETURN_TOKEN(TK_EOF); }
<expr>.   { printf("Invalid symbol in block code '%s'\n", getSymbol(yytext[0]).c_str()); }
<<EOF>>   { RETURN_TOKEN(TK_EOF); }
.|\n {
        stringstream ss;
        int c;

        c = yytext[0];
        for ( ; ; ) {
            ss << (char)c;

            if (c == '\n') line++;

            c = yyinput();

            if (c == EOF) break;

            if ( c == '<' ) {
                int c2 = yyinput();
                if ( c2 == '?' ) {
                    BEGIN(expr);
                    unput('?');
                    unput('<');
                    break;
                } else {
                    ss << (char)c;
                    c = c2;
                }
            }
        }
        p_info = allocTokenInfo(TK_TEXT, ss.str());
        return TK_TEXT;
    }
%%

string getTokenString(int token, TokenInfo *info)
{
    string tokenName;

    switch (token) {
    case TK_EOF: tokenName = "end of input"; break;
    case TK_TEXT: tokenName = "text block"; break;
    case KW_IF: tokenName = "KW_IF"; break;
    case KW_ELSE: tokenName = "KW_ELSE"; break;
    case KW_WHILE:tokenName = "KW_WHILE"; break;
    case KW_ASSIGN:tokenName = "KW_ASSIGN"; break;
    case KW_PRINT: tokenName = "KW_PRINT"; break;

    case TK_LESS: tokenName = "TK_LESS";
    break;
    case TK_LSET:tokenName = "TK_LSET";
    break;
    case TK_RSET:tokenName = "TK_RSET";
    break;
    case TK_EQUAL:tokenName = "TK_EQUAL";
    break;
    case TK_ADD:tokenName = "TK_ADD";
    break;
    case TK_SUB:tokenName = "TK_SUB";
    break;
    case TK_MULT:tokenName = "TK_MULT";
    break;
    case TK_DIV:tokenName = "TK_DIV";
    break;
    case TK_LPAREN:tokenName = "TK_LPAREN";
    break;
    case TK_RPAREN:tokenName = "TK_RPAREN";
    break;
    case TK_SEMICOLON:
        tokenName = "symbol";
        break;

    case TK_ID: tokenName = "identifier"; break;
    case TK_NUM: tokenName = "number"; break;
    default:
        tokenName = ::convertToString(token);
    }

    string result = tokenName;

    if (info != NULL)
        result += " '" + info->strValue + "'";

    return result;
}
