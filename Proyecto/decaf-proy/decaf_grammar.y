%include {
		#include <stdio.h>
		#include <string>
		#include "Value.h"
		#include "Variable.h"
		#include "Expression.h"
		#include "Statement.h"
		#include "MethodDef.h"
		#include "ClassDef.h"
		#include "decaf_tokens.h"

		extern ClassDef *class_def;
		extern YYLTYPE *yylloc;

		//int yylex(YYSTYPE*, YYLTYPE*); //YYSTYPE is from bison, is not necessary define it.
		//void yyerror(const char *message);
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
%default_type {TokenInfo *}

%union {
	ExpressionOperator	oper;
	ResultValue		constant;
	LValue			lvalue;
	int			integer;
	bool			boolean;
}

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

%syntax_error {
    string strErr = getTokenString(yymajor, TOKEN);
    reportError("Line %d: Syntax error. Unexpected %s\n", yylloc->last_line, strErr.c_str());
}

%start_symbol init

init ::= program.

program
	::=	class_def(B).	{ class_def = B; }

class_def(A) ::=
		K_CLASS class_name(B) T_OSET optional_field_decl_list(C) optional_method_decl_list(D) T_CSET.
		{ A = new ClassDef(B, C, D); }


optional_field_decl_list(A) ::= field_decl_list(B).		{ A = B; }
optional_field_decl_list(A) ::= . 		{ A = 0; }

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

var	(A)::= 	 ID(B) optional_initialization(C).	{
							A = new VariableDef(B->strValue, @1.last_line, @1.first_column);
							A->initial_value = C;
						}
var	(A)::= ID(B) T_OBRACKET INT_CONSTANT(D) T_CBRACKET.	{
							A = new VariableDef(B->strValue, @1.last_line, @1.first_column);
							A->is_array_def = true;
							A->array_dimension = D->intValue;
						}

optional_initialization(A)::=	T_ASSIGN constant(C).	{ A = C; }
optional_initialization(A)::=.		{ A = 0; }



CONTINUAR AQUI



method_decl
	(A)::= 	return_type ID '(' opt_parameter_decl_list ')' block.
		{
			A = new MethodDef(C);
			A->method_return_type = B;
			A->method_parameters = E;
			A->method_body =  G;
		}

return_type(A)::=
		type.		{ A = B; }
		| K_VOID.	{ A = Void; }

opt_parameter_decl_list(A)::=
			parameter_decl_list. 	{ A = B; }
			|. /*Nada*/		{ A = 0; }

parameter_decl_list(A)::=
			parameter_decl_list T_COMMA parameter_decl.	{
									A = B;
									A->push_back(D);
								}
			| parameter_decl.			{
									A = new ParameterDefList;
									A->push_back(B);
								}

parameter_decl(A)::=
		type ID.		{ A = new ParameterDef(C, B); }

block
	(A)::= 	T_OSET opt_var_decl_list opt_statement_list T_CSET.
		{ A = new BlockStatement(C, D ); }

opt_var_decl_list(A)::= 	var_decl_list. { A = B; }
			| ./*Nada*/	{ A = 0; }

opt_statement_list(A)::= 	statement_list.	{ A = B; }
			|. /*Nada*/	{ A = 0; }

var_decl_list(A)::= 	var_decl_list var_decl.	{
						A = B;
						A->insert(A->end(), C->begin(), C->end());
						delete C;
					}
		| var_decl.		{ A = B; }

var_decl(A)::=
		type var_list T_SEMICOLON. { A = SetType(C, B); }

type	(A)::=
		K_INT.		{ A = Int; }
		| K_BOOLEAN.	{ A = Boolean; }

statement_list(A)::=
		statement_list statement.	{ A = B; A->push_back(C); }
		| statement.			{ A = new StatementList; A->push_back(B); }

statement
	(A)::= 	assign T_SEMICOLON.			{ A = B; }
		| method_call T_SEMICOLON.		{ A = B; }
		| if_statement.			{ A = B; }
		| while_statement .		{ A = B; }
		| for_statement	.		{ A = B; }
		| return_statement T_SEMICOLON.		{ A = B; }
		| break_statement T_SEMICOLON	.	{ A = B; }
		| continue_statement T_SEMICOLON.	{ A = B; }
		| block .			{ A = B; }

assign	(A)::=
		lvalue T_ASSIGN expr . { A = new AssignmentStatement(B, D, @1.first_line, @1.first_column); }

method_call(A)::=
		method_name '(' opt_method_call_argument_list ')'.	{ A = new MethodCallStatement(B, D, @1.first_line, @1.first_column); }
		| K_PRINT print_argument_list.				{ A = new MethodCallStatement("print", C, @1.first_line, @1.first_column); }
		| K_READ read_argument_list.			{ A = new MethodCallStatement("read", C, @1.first_line, @1.first_column); }

method_name
	(A)::= 	ID.	{ A = B; }

opt_method_call_argument_list(A)::=
				method_call_argument_list.	{ A = B; }
				| . /*Nada*/			{ A = 0; }

method_call_argument_list(A)::=
				method_call_argument_list T_COMMA expr.	{ A = B; A->push_back(D); }
				| expr	.				{ A = new ExpressionList; A->push_back(B); }

print_argument_list(A)::=
			print_argument_list T_COMMA print_argument.	{ A = B; A->push_back(D); }
			| print_argument.			{ A = new ExpressionList; A->push_back(B); }

print_argument
	(A)::= 	STRING_CONSTANT	.	{ A = new ConstantExpression(B); }
		| expr	.		{ A = B; }

read_argument_list(A)::=
			read_argument_list T_COMMA lvalue.	{ A = B; A->push_back(D); }
			| lvalue.			{ A = new ExpressionList; A->push_back(B); }

lvalue
	(A)::= 	ID opt_array_dimension.	{ A = new LValueExpression(B, C); }

opt_array_dimension(A)::=
			T_OBRACKET expr T_CBRACKET.	{ A = C; }
			|. /*Nada*/	{ A = 0; }

if_statement(A)::=
		K_IF '(' expr ')' block opt_else.	{ A = new IfStatement(D, F, G, @1.first_line, @1.first_column); }

opt_else(A)::=
		K_ELSE block.	{ A = C; }
		|. /*Nada*/	{ A = 0; }

while_statement(A)::=
		K_WHILE '(' expr ')' block.	{ A = new WhileStatement(D, F, @1.first_line, @1.first_column); }

for_statement(A)::=
		K_FOR '(' for_assignment_list T_SEMICOLON expr T_SEMICOLON for_assignment_list ')' block.
		{ A = new ForStatement(D, F, H, J, @1.first_line, @1.first_column); }

for_assignment_list(A)::=
			for_assignment_list T_COMMA assign.		{ A = B; ((BlockStatement *)A)->AddStatement(D); }
			| assign.				{ A = new BlockStatement(@1.first_line, @1.first_column); ((BlockStatement *)A)->AddStatement(B); }

return_statement(A)::=
			 K_RETURN opt_expr.	{ A = new ReturnStatement(C, @1.first_line, @1.first_column); }

break_statement(A)::=
			K_BREAK	.	{ A = new BreakStatement(@1.first_line, @1.first_column); }

continue_statement(A)::=
			K_CONTINUE.	{ A = new ContinueStatement(@1.first_line, @1.first_column); }

opt_expr(A)::=
		expr.		{ A = B; }
		|. /*Nada*/	{ A = 0; }

expr	(A)::=
		expr BOOL_OP_OR bool_term.	{ A = new BinaryExpression(B, D, C); }
		| bool_term	.		{ A = B; }

bool_term(A)::= 	bool_term BOOL_OP_AND relational_expr.	{ A = new BinaryExpression(B, D, C); }
		| relational_expr.			{ A = B; }

relational_expr(A)::=
			relational_expr  REL_OP bit_shift_expr.	{ A = new BinaryExpression(B, D, C); }
			| bit_shift_expr.			{ A = B; }

bit_shift_expr(A)::=
			bit_shift_expr BIT_SHIFT_OP arith_expr.	{ A = new BinaryExpression(B, D, C); }
			| arith_expr.				{ A = B; }

arith_expr(A)::=
		arith_expr ARITH_OP_SUM arith_term.		{ A = new BinaryExpression(B, D, C); }
		| arith_term.					{ A = B; }

arith_term(A)::= 	arith_term ARITH_OP_MUL	factor.			{ A = new BinaryExpression(B, D, C); }
		| factor.					{ A = B; }

factor(A)::=
		'!' factor.					{ A = new UnaryExpression(C, OpNot); }
		| ARITH_OP_SUM factor.				{ A = new UnaryExpression(C, B); }
		| lvalue.					{ A = B; }
		| method_name '(' opt_method_call_argument_list ')'.	{ A = new MethodCallExpression(B, D); }
		| constant.					{ A = B; }
		| '(' expr ')'.					{ A = C; }

constant(A)::= 	INT_CONSTANT. 	{ A = new ConstantExpression(B); }
		| CHAR_CONSTANT. { A = new ConstantExpression(B); }
		| REAL_CONSTANT. { A = new ConstantExpression(B); }
		| bool_constant. { A = B; }

bool_constant(A)::=
		K_TRUE.		{ A = new ConstantExpression(true); }
		| K_FALSE.	{ A = new ConstantExpression(false); }
