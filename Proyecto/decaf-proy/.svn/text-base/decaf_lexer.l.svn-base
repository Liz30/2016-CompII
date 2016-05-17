%option noyywrap
%option bison-bridge bison-locations

%{

#include <math.h>
#include "Value.h"
#include "Variable.h"
#include "Expression.h"
#include "Statement.h"
#include "MethodDef.h"
#include "ClassDef.h"
#include "Util.h"
#include "decaf_tokens.h"

#define YY_INPUT(buf,result,max_size)  {\
    result = GetNextChar(buf, max_size); \
    if (  result <= 0  ) \
      result = YY_NULL; \
    }

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
"int"		{ BeginToken(yytext, yylloc); return K_INT; }
"void"		{ BeginToken(yytext, yylloc); return K_VOID; }
"boolean"	{ BeginToken(yytext, yylloc); return K_BOOLEAN; }
"||"		{ BeginToken(yytext, yylloc); yylval->oper = OpOr; return BOOL_OP_OR; }
"&&"		{ BeginToken(yytext, yylloc); yylval->oper = OpAnd; return BOOL_OP_AND; }
">>"		{ BeginToken(yytext, yylloc); yylval->oper = OpRShift; return BIT_SHIFT_OP; }
"<<"		{ BeginToken(yytext, yylloc); yylval->oper = OpLShift; return BIT_SHIFT_OP; }
"rot"		{ BeginToken(yytext, yylloc); yylval->oper = OpRot; return BIT_SHIFT_OP; }
">"			{ BeginToken(yytext, yylloc); yylval->oper = OpGT; return REL_OP; }
"<"			{ BeginToken(yytext, yylloc); yylval->oper = OpLT; return REL_OP; }
">="		{ BeginToken(yytext, yylloc); yylval->oper = OpGTE; return REL_OP; }
"<="		{ BeginToken(yytext, yylloc); yylval->oper = OpLTE; return REL_OP; }
"=="		{ BeginToken(yytext, yylloc); yylval->oper = OpEq; return REL_OP; }
"!="		{ BeginToken(yytext, yylloc); yylval->oper = OpNotEq; return REL_OP; }
"+"			{ BeginToken(yytext, yylloc); yylval->oper = OpAdd; return ARITH_OP_SUM; }
"-"			{ BeginToken(yytext, yylloc); yylval->oper = OpSub; return ARITH_OP_SUM; }
"*"			{ BeginToken(yytext, yylloc); yylval->oper = OpMul; return ARITH_OP_MUL; }
"/"			{ BeginToken(yytext, yylloc); yylval->oper = OpDiv; return ARITH_OP_MUL; }
"%"			{ BeginToken(yytext, yylloc); yylval->oper = OpMod; return ARITH_OP_MUL; }
\"([^"]|\"\")*\"	{
						BeginToken(yytext, yylloc);
						yylval->string = strdup(yytext);
						return STRING_CONSTANT;
					}
{DIGIT}+		{
					BeginToken(yytext, yylloc);
					yylval->integer = atoi(yytext);
					return INT_CONSTANT;
				}
(_|{LETTER})(_|{LETTER}|{DIGIT})*	{
										BeginToken(yytext, yylloc);
										yylval->string = strdup(yytext);
										return ID;
									}
";"		{ BeginToken(yytext, yylloc); return ';'; }
","		{ BeginToken(yytext, yylloc); return ','; }
"("		{ BeginToken(yytext, yylloc); return '('; }
")"		{ BeginToken(yytext, yylloc); return ')'; }
"{"		{ BeginToken(yytext, yylloc); return '{'; }
"}"		{ BeginToken(yytext, yylloc); return '}'; }
"["		{ BeginToken(yytext, yylloc); return '['; }
"]"		{ BeginToken(yytext, yylloc); return ']'; }
"="		{ BeginToken(yytext, yylloc); return '='; }
"!"		{ BeginToken(yytext, yylloc); return '!'; }
"//".*"\n"	{ BeginToken(yytext, yylloc); };
[ \t]+		{ BeginToken(yytext, yylloc); }
"\n"		{ yylloc->last_line++; yylloc->first_column = 0; }
.           printf( "%d:Caracter no reconocido: #%d, %s\n", yylloc->last_line, yytext[0], yytext );

%%


