%option noyywrap

%{

    #include <math.h>
    #include "Value.h"
    #include "Variable.h"
    #include "Expression.h"
    #include "Statement.h"
    #include "MethodDef.h"
    #include "ClassDef.h"
    #include "Util.h"
    #include "TokenInfo.h"
    //#include "decaf_tokens.h"
    #include "tokens.h"

    //#define YY_DECL int nextToken(struct TokenInfo *&p_info)

    #define YY_INPUT(buf,result,max_size)  {\
        result = GetNextChar(buf, max_size); \
        if (  result <= 0  ) \
          result = YY_NULL; \
        }

    YYLTYPE *yylloc = new YYLTYPE;

        int tokenType;
        char* strValue;
        int intValue;
        ExpressionOperator	oper;

    string getTokenString(int token, TokenInfo *info);

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
"||"		{ BeginToken(yytext, yylloc); oper = OpOr; return BOOL_OP_OR; }
"&&"		{ BeginToken(yytext, yylloc);  oper = OpAnd; return BOOL_OP_AND; }
">>"		{ BeginToken(yytext, yylloc);  oper = OpRShift; return BIT_SHIFT_OP; }
"<<"		{ BeginToken(yytext, yylloc);  oper = OpLShift; return BIT_SHIFT_OP; }
"rot"		{ BeginToken(yytext, yylloc);  oper = OpRot; return BIT_SHIFT_OP; }
">"			{ BeginToken(yytext, yylloc);  oper = OpGT; return REL_OP; }
"<"			{ BeginToken(yytext, yylloc);  oper = OpLT; return REL_OP; }
">="		{ BeginToken(yytext, yylloc);  oper = OpGTE; return REL_OP; }
"<="		{ BeginToken(yytext, yylloc);  oper = OpLTE; return REL_OP; }
"=="		{ BeginToken(yytext, yylloc);  oper = OpEq; return REL_OP; }
"!="		{ BeginToken(yytext, yylloc);  oper = OpNotEq; return REL_OP; }
"+"			{ BeginToken(yytext, yylloc);  oper = OpAdd; return ARITH_OP_SUM; }
"-"			{ BeginToken(yytext, yylloc);  oper = OpSub; return ARITH_OP_SUM; }
"*"			{ BeginToken(yytext, yylloc);  oper = OpMul; return ARITH_OP_MUL; }
"/"			{ BeginToken(yytext, yylloc);  oper = OpDiv; return ARITH_OP_MUL; }
"%"			{ BeginToken(yytext, yylloc);  oper = OpMod; return ARITH_OP_MUL; }
\"([^"]|\"\")*\"	{
						BeginToken(yytext, yylloc);
						 strValue = strdup(yytext);
						return STRING_CONSTANT;
					}
{DIGIT}+		{
					BeginToken(yytext, yylloc);
					 intValue = atoi(yytext);
					return INT_CONSTANT;
				}
(_|{LETTER})(_|{LETTER}|{DIGIT})*	{
										BeginToken(yytext, yylloc);
										 strValue = strdup(yytext);
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
<<EOF>> { /*BeginToken(yytext, yylloc);*/ return T_EOF; }
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

    if (info != NULL)
        result += " '" + ::convertToString(info->strValue) + "'";

    return result;
}
