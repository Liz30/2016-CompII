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

    YYLTYPE *yylloc = new YYLTYPE;

%}

DIGIT    [0-9]
LETTER   [a-zA-Z]

%%

"class"		{ BeginToken(yytext, yylloc); return K_CLASS; }
"break"		{ BeginToken(yytext, yylloc); return K_BREAK; }
"continue"	{ BeginToken(yytext, yylloc); return K_CONTINUE; }
"while"		{ BeginToken(yytext, yylloc); return K_WHILE; }
"for"		{ BeginToken(yytext, yylloc); return K_FOR; }
"if"		{ BeginToken(yytext, yylloc); return K_IF; }
"else"		{ BeginToken(yytext, yylloc); return K_ELSE; }
"return"	{ BeginToken(yytext, yylloc); return K_RETURN; }
"read"		{ BeginToken(yytext, yylloc); return K_READ; }
"print"		{ BeginToken(yytext, yylloc); return K_PRINT; }
"true"		{ BeginToken(yytext, yylloc); return K_TRUE; }
"false"		{ BeginToken(yytext, yylloc); return K_FALSE; }
"int"		  { BeginToken(yytext, yylloc); return K_INT; }
"void"		{ BeginToken(yytext, yylloc); return K_VOID; }
"boolean"	{ BeginToken(yytext, yylloc); return K_BOOLEAN; }
"||"		{ BeginToken(yytext, yylloc); p_info->oper = OpOr; return BOOL_OP_OR; }
"&&"		{ BeginToken(yytext, yylloc); p_info->oper = OpAnd; return BOOL_OP_AND; }
">>"		{ BeginToken(yytext, yylloc); p_info->oper = OpRShift; return BIT_SHIFT_OP; }
"<<"		{ BeginToken(yytext, yylloc); p_info->oper = OpLShift; return BIT_SHIFT_OP; }
"rot"		{ BeginToken(yytext, yylloc); p_info->oper = OpRot; return BIT_SHIFT_OP; }
">"			{ BeginToken(yytext, yylloc); p_info->oper = OpGT; return REL_OP; }
"<"			{ BeginToken(yytext, yylloc); p_info->oper = OpLT; return REL_OP; }
">="		{ BeginToken(yytext, yylloc); p_info->oper = OpGTE; return REL_OP; }
"<="		{ BeginToken(yytext, yylloc); p_info->oper = OpLTE; return REL_OP; }
"=="		{ BeginToken(yytext, yylloc); p_info->oper = OpEq; return REL_OP; }
"!="		{ BeginToken(yytext, yylloc); p_info->oper = OpNotEq; return REL_OP; }
"+"			{ BeginToken(yytext, yylloc); p_info->oper = OpAdd; return ARITH_OP_SUM; }
"-"			{ BeginToken(yytext, yylloc); p_info->oper = OpSub; return ARITH_OP_SUM; }
"*"			{ BeginToken(yytext, yylloc); p_info->oper = OpMul; return ARITH_OP_MUL; }
"/"			{ BeginToken(yytext, yylloc); p_info->oper = OpDiv; return ARITH_OP_MUL; }
"%"			{ BeginToken(yytext, yylloc); p_info->oper = OpMod; return ARITH_OP_MUL; }
\"([^"]|\"\")*\"	{
						BeginToken(yytext, yylloc);
						p_info->strValue = strdup(yytext);
						return STRING_CONSTANT;
					}
{DIGIT}+		{
					BeginToken(yytext, yylloc);
					p_info->intValue = atoi(yytext);
					return INT_CONSTANT;
				}
(_|{LETTER})(_|{LETTER}|{DIGIT})*	{
										BeginToken(yytext, yylloc);
										p_info->strValue = strdup(yytext);
										return ID;
									}
";"		{ BeginToken(yytext, yylloc); return T_SEMICOLON; }
","		{ BeginToken(yytext, yylloc); return T_COMMA; }
"("		{ BeginToken(yytext, yylloc); return T_OPAR; }
")"		{ BeginToken(yytext, yylloc); return T_CPAR; }
"{"		{ BeginToken(yytext, yylloc); return T_OSET; }
"}"		{ BeginToken(yytext, yylloc); return T_CSET; }
"["		{ BeginToken(yytext, yylloc); return T_OBRACKET; }
"]"		{ BeginToken(yytext, yylloc); return T_CBRACKET; }
"="		{ BeginToken(yytext, yylloc); return T_ASSIGN; }
"!"		{ BeginToken(yytext, yylloc); return T_NOT; }
"//".*"\n"	{ BeginToken(yytext, yylloc); };
[ \t]+		{ BeginToken(yytext, yylloc); }
"\n"		{ yylloc->last_line++; yylloc->first_column = 0; }
<<EOF>> { BeginToken(yytext, yylloc); return T_EOF; }
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

    case T_OSET:
    case T_CSET:
    case REL_OP:
    case T_OPAR:
    case T_CPAR:
    case T_SEMICOLON:
        tokenName = "symbol";
        break;

    case ID: tokenName = "identifier"; break;
    case INT_CONSTANT: tokenName = "number"; break;
    default:
        tokenName = ::convertToString(token);
    }

    string result = tokenName;

    //cout<<"       getTokenString"<<endl;
    if (info != NULL){
    //    cout << info->strValue<<endl;
        result += " '" + ::convertToString(info->strValue) + "'";
    //    cout << "tokenName: "<<result<<endl;
    }

    return result;
}
