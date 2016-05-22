%include {
		#include <stdio.h>
		#include <string>
		#include "Value.h"
		#include "Variable.h"
		#include "Expression.h"
		#include "Statement.h"
		#include "MethodDef.h"
		#include "ClassDef.h"
		#include "TokenInfo.h"
		#include "decaf_tokens.h"

		using namespace std;

		extern ClassDef *class_def;
		extern YYLTYPE *yylloc;

		void reportError(const char *format, ...);

		VariableDefList *SetType(VariableDefList *list, Type type)
		{
			VariableDefList::iterator it = list->begin();
			while (it != list->end()) {
				VariableDef *var = *it;
				var->variable_type = type;
				it++;
			}
			return list;
		}
}

%token_type {TokenInfo *}
%default_type {int}

%type statement {Statement*}
%type assign {Statement*}
%type method_call {Statement*}
%type if_statement {Statement*}
%type while_statement {Statement*}
%type for_statement {Statement*}
%type return_statement {Statement*}
%type break_statement {Statement*}
%type continue_statement {Statement*}
%type block{Statement*}
%type for_assignment_list {Statement*}
%type opt_else {Statement*}

%type opt_expr {Expression*}
%type expr {Expression*}
%type bool_term {Expression*}
%type relational_expr {Expression*}
%type bit_shift_expr {Expression*}
%type arith_expr {Expression*}
%type arith_term {Expression*}
%type factor {Expression*}
%type constant {Expression*}
%type bool_constant {Expression*}
%type print_argument {Expression*}
%type lvalue {Expression*}
%type opt_array_dimension {Expression*}
%type optional_initialization {Expression*}

%type opt_method_call_argument_list {ExpressionList*}
%type method_call_argument_list {ExpressionList*}
%type read_argument_list {ExpressionList*}
%type print_argument_list {ExpressionList*}

%type var {VariableDef*}
%type field_decl {VariableDefList*}
%type field_decl_list {VariableDefList*}
%type var_decl {VariableDefList*}
%type var_list {VariableDefList*}
%type opt_var_decl_list {VariableDefList*}
%type var_decl_list {VariableDefList*}
%type optional_field_decl_list {VariableDefList*}

%type method_decl {MethodDef*}
%type optional_method_decl_list {MethodDefList*}
%type method_decl_list {MethodDefList*}

%type parameter_decl {ParameterDef*}
%type opt_parameter_decl_list {ParameterDefList*}
%type parameter_decl_list {ParameterDefList*}

%type class_def {ClassDef*}
%type class_name {char*}
%type method_name {char*}
%type	opt_statement_list {StatementList*}
%type statement_list {StatementList*}
%type return_type {Type}
%type type {Type}

%parse_accept {
  printf("Parsing completed!\n\n\n");
}

%syntax_error {
    string strErr = getTokenString(yymajor, TOKEN);
    reportError("Line %d: Syntax error. Unexpected %s\n", yylloc->last_line, strErr.c_str());
}

%start_symbol init

init ::= program T_EOF.

program::=	class_def(B).	{ class_def = B; }

class_def(A) ::=
		K_CLASS class_name(B) T_OSET optional_field_decl_list(C) optional_method_decl_list(D) T_CSET.
		{ A = new ClassDef(B, C, D); }


optional_field_decl_list(A) ::= field_decl_list(B).		{ A = B; }
optional_field_decl_list(A) ::= . 										{ A = 0; }

optional_method_decl_list(A)::= method_decl_list(B).	{ A = B; }
optional_method_decl_list(A)::= .		{ A = 0; }

field_decl_list(A)::=	field_decl_list(B) field_decl(C).	{ A = B; A->insert(A->end(), C->begin(), C->end()); delete C;}
field_decl_list(A)::= field_decl(B).			{ A = B; }

method_decl_list(A)::= method_decl_list(B) method_decl(C).	{ A = B; A->push_back(C); }
method_decl_list(A)::= method_decl(B).			{ A = new MethodDefList; A->push_back(B); }

class_name(A)::= 	ID(B). { A = B->strValue; }

field_decl(A)::= 	type(B) var_list(C) T_SEMICOLON. { A = SetType(C, B); }

var_list(A)::= var_list(B) T_COMMA var(D).	{ A = B; A->push_back(D); }
var_list(A)::= var(B).			{
															A = new VariableDefList;
															A->push_back(B);
														}

var	(A)::= 	 ID(B) optional_initialization(C).					 {
																													 A = new VariableDef(B->strValue, yylloc->last_line, yylloc->first_column);
																													 A->initial_value = C;
																												 }
var	(A)::= ID(B) T_OBRACKET INT_CONSTANT(D) T_CBRACKET.	 {
																														A = new VariableDef(B->strValue, yylloc->last_line, yylloc->first_column);
																														A->is_array_def = true;
																														A->array_dimension = D->intValue;
																													}

optional_initialization(A)::=	T_ASSIGN constant(C).	{ A = C; }
optional_initialization(A)::=.											{ A = 0; }

method_decl(A)::= 	return_type(B) ID(C) T_OPAR opt_parameter_decl_list(E) T_CPAR block(G).
																																		{
																																			A = new MethodDef(C->strValue);
																																			A->method_return_type = B;
																																			A->method_parameters = E;
																																			A->method_body =  G;
																																		}

return_type(A)::= K_VOID.		{ A = Void; }
return_type(A)::= type(B).	{ A = B; }

opt_parameter_decl_list(A)::= parameter_decl_list(B). 	{ A = B; }
opt_parameter_decl_list(A)::=.		{ A = 0; }

parameter_decl_list(A)::=	parameter_decl_list(B) T_COMMA parameter_decl(D).	{
																																							A = B;
																																							A->push_back(D);
																																						}
parameter_decl_list(A)::= parameter_decl(B).	{
																									A = new ParameterDefList;
																									A->push_back(B);
																							}

parameter_decl(A)::= type(B) ID(C).		{ A = new ParameterDef(C->strValue, B); }

block(A)::= 	T_OSET opt_var_decl_list(C) opt_statement_list(D) T_CSET. { A = new BlockStatement(C, D ); }

opt_var_decl_list(A)::= 	var_decl_list(B). { A = B; }
opt_var_decl_list(A)::= .										{ A = 0; }

opt_statement_list(A)::= 	statement_list(B).	{ A = B; }
opt_statement_list(A)::= .										 { A = 0; }

var_decl_list(A)::= 	var_decl_list(B) var_decl(C).	{
																											A = B;
																											A->insert(A->end(), C->begin(), C->end());
																											delete C;
																										}
var_decl_list(A)::= var_decl(B).										{ A = B; }

var_decl(A)::= type(B) var_list(C) T_SEMICOLON. { A = SetType(C, B); }

type(A)::= K_INT.			{ A = Int; }
type(A)::= K_BOOLEAN.	{ A = Boolean; }

statement_list(A)::= statement_list(B) statement(C).	{ A = B; A->push_back(C); }
statement_list(A)::= statement(B).										{ A = new StatementList; A->push_back(B); }

statement(A)::= assign(B) T_SEMICOLON.						{ A = B; }
statement(A)::= method_call(B) T_SEMICOLON.				{ A = B; }
statement(A)::= if_statement(B).									{ A = B; }
statement(A)::= while_statement(B).								{ A = B; }
statement(A)::= for_statement(B).									{ A = B; }
statement(A)::= return_statement(B) T_SEMICOLON.	{ A = B; }
statement(A)::= break_statement(B) T_SEMICOLON	.	{ A = B; }
statement(A)::= continue_statement(B) T_SEMICOLON.{ A = B; }
statement(A)::= block(B) .												{ A = B; }

assign(A)::= lvalue(B) T_ASSIGN expr(D) . { A = new AssignmentStatement(B, D, yylloc->first_line, yylloc->first_column); }

method_call(A)::= method_name(B) T_OPAR opt_method_call_argument_list(D) T_CPAR.	{ A = new MethodCallStatement(B, D, yylloc->first_line, yylloc->first_column); }
method_call(A)::= K_PRINT print_argument_list(C).																	{ A = new MethodCallStatement("print", C, yylloc->first_line, yylloc->first_column); }
method_call(A)::= K_READ read_argument_list(C).																		{ A = new MethodCallStatement("read", C, yylloc->first_line, yylloc->first_column); }

method_name(A)::= ID(B).	{ A = B->strValue; }

opt_method_call_argument_list(A)::=	method_call_argument_list(B).	{ A = B; }
opt_method_call_argument_list(A)::= . 														{ A = 0; }

method_call_argument_list(A)::=	method_call_argument_list(B) T_COMMA expr(D).	{ A = B; A->push_back(D); }
method_call_argument_list(A)::= expr(B)	.																			{ A = new ExpressionList; A->push_back(B); }

print_argument_list(A)::=	print_argument_list(B) T_COMMA print_argument(D).	{ A = B; A->push_back(D); }
print_argument_list(A)::= print_argument(B).																{ A = new ExpressionList; A->push_back(B); }

print_argument(A)::= STRING_CONSTANT(B)	.	{ A = new ConstantExpression(B->strValue); }
print_argument(A)::= expr(B)	.								{ A = B; }

read_argument_list(A)::= read_argument_list(B) T_COMMA lvalue(D).	{ A = B; A->push_back(D); }
read_argument_list(A)::= lvalue(B).																{ A = new ExpressionList; A->push_back(B); }

lvalue(A)::= 	ID(B) opt_array_dimension(C).	{ A = new LValueExpression(B->strValue, C); }

opt_array_dimension(A)::=	T_OBRACKET expr(C) T_CBRACKET.	{ A = C; }
opt_array_dimension(A)::= .																{ A = 0; }

if_statement(A)::= K_IF T_OPAR expr(D) T_CPAR block(F) opt_else(G).	{ A = new IfStatement(D, F, G, yylloc->first_line, yylloc->first_column); }

opt_else(A)::= K_ELSE block(C).	{ A = C; }
opt_else(A)::= .								{ A = 0; }

while_statement(A)::= K_WHILE T_OPAR expr(D) T_CPAR block(F).	{ A = new WhileStatement(D, F, yylloc->first_line, yylloc->first_column); }

for_statement(A)::=	K_FOR T_OPAR for_assignment_list(D) T_SEMICOLON expr(F) T_SEMICOLON for_assignment_list(H) T_CPAR block(J).
																																			{ A = new ForStatement(D, F, H, J, yylloc->first_line, yylloc->first_column); }

for_assignment_list(A)::= for_assignment_list(B) T_COMMA assign(D).		{ A = B; ((BlockStatement *)A)->AddStatement(D); }
for_assignment_list(A)::= assign(B).																	{ A = new BlockStatement(yylloc->first_line, yylloc->first_column); ((BlockStatement *)A)->AddStatement(B); }

return_statement(A)::=  K_RETURN opt_expr(C).	{ A = new ReturnStatement(C, yylloc->first_line, yylloc->first_column); }

break_statement(A)::= K_BREAK	.	{ A = new BreakStatement(yylloc->first_line, yylloc->first_column); }

continue_statement(A)::= K_CONTINUE.	{ A = new ContinueStatement(yylloc->first_line, yylloc->first_column); }

opt_expr(A)::= expr(B).		{ A = B; }
opt_expr(A)::= .					{ A = 0; }

expr(A)::= expr(B) BOOL_OP_OR(C) bool_term(D).	{ A = new BinaryExpression(B, D, C->oper); }
expr(A)::= bool_term(B)	.												{ A = B; }

bool_term(A)::= bool_term(B) BOOL_OP_AND(C) relational_expr(D).	{ A = new BinaryExpression(B, D, C->oper); }
bool_term(A)::= relational_expr(B).															{ A = B; }

relational_expr(A)::= relational_expr(B)  REL_OP(C) bit_shift_expr(D).	{ A = new BinaryExpression(B, D, C->oper); }
relational_expr(A)::= bit_shift_expr(B).																{ A = B; }

bit_shift_expr(A)::= bit_shift_expr(B) BIT_SHIFT_OP(C) arith_expr(D).	{ A = new BinaryExpression(B, D, C->oper); }
bit_shift_expr(A)::= arith_expr(B).																		{ A = B; }

arith_expr(A)::= arith_expr(B) ARITH_OP_SUM(C) arith_term(D).		{ A = new BinaryExpression(B, D, C->oper); }
arith_expr(A)::= arith_term(B).																	{ A = B; }

arith_term(A)::= arith_term(B) ARITH_OP_MUL(C)	factor(D).	{ A = new BinaryExpression(B, D, C->oper); }
arith_term(A)::= factor(B).																	{ A = B; }

factor(A)::= T_NOT factor(C).																								{ A = new UnaryExpression(C, OpNot); }
factor(A)::= ARITH_OP_SUM(B) factor(C).																			{ A = new UnaryExpression(C, B->oper); }
factor(A)::= lvalue(B).																											{ A = B; }
factor(A)::= method_name(B) T_OPAR opt_method_call_argument_list(D) T_CPAR.	{ A = new MethodCallExpression(B, D); }
factor(A)::= constant(B).																										{ A = B; }
factor(A)::= T_OPAR expr(C) T_CPAR.																					{ A = C; }

constant(A)::= INT_CONSTANT(B).  { A = new ConstantExpression(B->intValue); }
constant(A)::= CHAR_CONSTANT(B). { A = new ConstantExpression(B); }
constant(A)::= REAL_CONSTANT(B). { A = new ConstantExpression(B); }
constant(A)::= bool_constant(B). { A = B; }

bool_constant(A)::= K_TRUE.		{ A = new ConstantExpression(true); }
bool_constant(A)::= K_FALSE.	{ A = new ConstantExpression(false); }
