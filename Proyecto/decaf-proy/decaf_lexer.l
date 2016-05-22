%option noyywrap

%{

    #include <math.h>
    #include <iostream>
    #include "Value.h"
    #include "Variable.h"
    #include "Expression.h"
    #include "Statement.h"
    #include "MethodDef.h"
    #include "ClassDef.h"
    #include "Util.h"
    #include "TokenInfo.h"
    #include "decaf_tokens.h"

    using namespace std;

    #define YY_DECL int nextToken(struct TokenInfo *&p_info)

    #define YY_INPUT(buf,result,max_size)  {\
        result = GetNextChar(buf, max_size); \
        if (  result <= 0  ) \
          result = YY_NULL; \
        }

    #define RETURN_TOKEN(tk) do {   \
                            p_info = NULL; \
                            return tk;  \
                        } while(0)

    YYLTYPE *yylloc = new YYLTYPE;

%}

DIGIT    [0-9]
LETTER   [a-zA-Z]

%%

"class"		{ BeginToken(yytext, yylloc); RETURN_TOKEN(K_CLASS); }
"break"		{ BeginToken(yytext, yylloc); RETURN_TOKEN(K_BREAK); }
"continue"	{ BeginToken(yytext, yylloc); RETURN_TOKEN(K_CONTINUE); }
"while"		{ BeginToken(yytext, yylloc); RETURN_TOKEN(K_WHILE); }
"for"		{ BeginToken(yytext, yylloc); RETURN_TOKEN(K_FOR); }
"if"		{ BeginToken(yytext, yylloc); RETURN_TOKEN(K_IF); }
"else"		{ BeginToken(yytext, yylloc); RETURN_TOKEN(K_ELSE); }
"return"	{ BeginToken(yytext, yylloc); RETURN_TOKEN(K_RETURN); }
"read"		{ BeginToken(yytext, yylloc); RETURN_TOKEN(K_READ); }
"print"		{ BeginToken(yytext, yylloc); RETURN_TOKEN(K_PRINT); }
"true"		{ BeginToken(yytext, yylloc); RETURN_TOKEN(K_TRUE); }
"false"		{ BeginToken(yytext, yylloc); RETURN_TOKEN(K_FALSE); }
"int"		  { BeginToken(yytext, yylloc); RETURN_TOKEN(K_INT); }
"void"		{ BeginToken(yytext, yylloc); RETURN_TOKEN(K_VOID); }
"boolean"	{ BeginToken(yytext, yylloc); RETURN_TOKEN(K_BOOLEAN); }
"||"		{ BeginToken(yytext, yylloc); p_info = allocTokenInfo(BOOL_OP_AND, strdup(yytext)); p_info->oper = OpOr; return BOOL_OP_OR; }
"&&"		{ BeginToken(yytext, yylloc); p_info = allocTokenInfo(BOOL_OP_AND, strdup(yytext)); p_info->oper = OpAnd; return BOOL_OP_AND; }
">>"		{ BeginToken(yytext, yylloc); p_info = allocTokenInfo(BIT_SHIFT_OP, strdup(yytext)); p_info->oper = OpRShift; return BIT_SHIFT_OP; }
"<<"		{ BeginToken(yytext, yylloc); p_info = allocTokenInfo(BIT_SHIFT_OP, strdup(yytext)); p_info->oper = OpLShift; return BIT_SHIFT_OP; }
"rot"		{ BeginToken(yytext, yylloc); p_info = allocTokenInfo(BIT_SHIFT_OP, strdup(yytext)); p_info->oper = OpRot; return BIT_SHIFT_OP; }
">"			{ BeginToken(yytext, yylloc); p_info = allocTokenInfo(REL_OP, strdup(yytext)); p_info->oper = OpGT; return REL_OP; }
"<"			{ BeginToken(yytext, yylloc); p_info = allocTokenInfo(REL_OP, strdup(yytext)); p_info->oper = OpLT; return REL_OP; }
">="		{ BeginToken(yytext, yylloc); p_info = allocTokenInfo(REL_OP, strdup(yytext)); p_info->oper = OpGTE; return REL_OP; }
"<="		{ BeginToken(yytext, yylloc); p_info = allocTokenInfo(REL_OP, strdup(yytext)); p_info->oper = OpLTE; return REL_OP; }
"=="		{ BeginToken(yytext, yylloc); p_info = allocTokenInfo(REL_OP, strdup(yytext)); p_info->oper = OpEq; return REL_OP; }
"!="		{ BeginToken(yytext, yylloc); p_info = allocTokenInfo(REL_OP, strdup(yytext)); p_info->oper = OpNotEq; return REL_OP; }
"+"			{ BeginToken(yytext, yylloc); p_info = allocTokenInfo(ARITH_OP_SUM, strdup(yytext)); p_info->oper = OpAdd; return ARITH_OP_SUM; }
"-"			{ BeginToken(yytext, yylloc); p_info = allocTokenInfo(ARITH_OP_SUM, strdup(yytext)); p_info->oper = OpSub; return ARITH_OP_SUM; }
"*"			{ BeginToken(yytext, yylloc); p_info = allocTokenInfo(ARITH_OP_MUL, strdup(yytext)); p_info->oper = OpMul; return ARITH_OP_MUL; }
"/"			{ BeginToken(yytext, yylloc); p_info = allocTokenInfo(ARITH_OP_MUL, strdup(yytext)); p_info->oper = OpDiv; return ARITH_OP_MUL; }
"%"			{ BeginToken(yytext, yylloc); p_info = allocTokenInfo(ARITH_OP_MUL, strdup(yytext)); p_info->oper = OpMod; return ARITH_OP_MUL; }
\"([^"]|\"\")*\"	{
						BeginToken(yytext, yylloc);
            p_info = allocTokenInfo(STRING_CONSTANT, strdup(yytext));
						p_info->strValue = strdup(yytext);
						return STRING_CONSTANT;
					}
{DIGIT}+		{
					BeginToken(yytext, yylloc);
          p_info = allocTokenInfo(INT_CONSTANT, strdup(yytext));
					p_info->intValue = atoi(yytext);
					return INT_CONSTANT;
				}
(_|{LETTER})(_|{LETTER}|{DIGIT})*	{
										BeginToken(yytext, yylloc);
                    p_info = allocTokenInfo(ID, strdup(yytext));
										p_info->strValue = strdup(yytext);
										return ID;
									}
";"		{ BeginToken(yytext, yylloc); RETURN_TOKEN(T_SEMICOLON); }
","		{ BeginToken(yytext, yylloc); RETURN_TOKEN(T_COMMA); }
"("		{ BeginToken(yytext, yylloc); RETURN_TOKEN(T_OPAR); }
")"		{ BeginToken(yytext, yylloc); RETURN_TOKEN(T_CPAR); }
"{"		{ BeginToken(yytext, yylloc); RETURN_TOKEN(T_OSET); }
"}"		{ BeginToken(yytext, yylloc); RETURN_TOKEN(T_CSET); }
"["		{ BeginToken(yytext, yylloc); RETURN_TOKEN(T_OBRACKET); }
"]"		{ BeginToken(yytext, yylloc); RETURN_TOKEN(T_CBRACKET); }
"="		{ BeginToken(yytext, yylloc); RETURN_TOKEN(T_ASSIGN); }
"!"		{ BeginToken(yytext, yylloc); RETURN_TOKEN(T_NOT); }
"//".*"\n"	{ BeginToken(yytext, yylloc); };
[ \t]+		{ BeginToken(yytext, yylloc); }
"\n"		{ yylloc->last_line++; yylloc->first_column = 0; }
<<EOF>> { RETURN_TOKEN(T_EOF); }
.           printf( "%d:Caracter no reconocido: #%d, %s\n", yylloc->last_line, yytext[0], yytext );

%%

string getTokenString(int token, TokenInfo *info)
{
    string tokenName;

    switch (token) {
    case K_IF: tokenName = "K_IF"; break;
    case K_ELSE: tokenName = "K_ELSE"; break;
    case K_WHILE:tokenName = "K_WHILE"; break;
    case T_EOF: tokenName = "end of file"; break;
    case K_CLASS: tokenName = "K_CLASS"; break;
    case K_INT: tokenName = "K_INT"; break;

    case T_SEMICOLON:
    case T_OSET:
    case T_CSET:
    case REL_OP:
    case T_OPAR:
    case T_CPAR:
    case T_ASSIGN:
        tokenName += " symbol";
        break;

    case ID: tokenName = "identifier"; break;
    case INT_CONSTANT: tokenName = "number"; break;
    default:
        tokenName = ::convertToString(token);
    }

    string result = tokenName;

    if (info != NULL)
        result += " '" + ::convertToString(info->strValue) + "'";

    return result;
}
