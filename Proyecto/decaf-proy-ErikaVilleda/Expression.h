/*
 * Expression.h
 *
 *  Created on: Mar 27, 2009
 *      Author: Ivan Deras
 */

#ifndef EXPRESSION_H_
#define EXPRESSION_H_

#include <string>
#include <list>
#include <cstring>
#include <cstdlib>
#include <map>

#include "Value.h"
#include "Util.h"

using namespace std;


enum ExpressionKind
{
	ekBinary,
	ekUnary,
	ekLValue,
	ekMethodCall,
	ekConstant
};

/*
 * Operadores validos en una expression (binaria o unaria)
 *  1. OpAdd = Suma
 *  2. OpSub = Resta
 *  3. OpMul = Multiplicacion
 *  4. OpDiv = Division
 *  5. OpMod = Modulo
 *  6. OpAnd = Y booleano
 *  7. OpOr = O booleano
 *  8. OpNot = Negacion booleana
 *  9. OpGT = Mayor que
 * 10. OpLT = Menor que
 * 11. OpGTE = Mayor o Igual que
 * 12. OpLTE = Menor o Igual que
 * 13. OpEq = Igualdad
 * 14. OpNotEq = No igual
 * 15. OpRShift = Corrimiento de bits a la derecha
 * 16. OpLShift = Corrimiento de bits a la izquierda
 * 17. OpRot = Rotacion de bits
 */

enum ExpressionOperator
{
	OpAdd,
	OpSub,
	OpMul,
	OpDiv,
	OpMod,
	OpAnd,
	OpOr,
	OpNot,
	OpGT,
	OpLT,
	OpGTE,
	OpLTE,
	OpEq,
	OpNotEq,
	OpRShift,
	OpLShift,
	OpRot
};

bool ExistVarGlobal(string key);
bool ExistVarTemp(string key);
void ShowTemp();
void ShowTempAvailable();
bool ExistMethod(string key);
string newTempsS();
string newTemp();
string newParam();
void releaseParam(string key);
void releaseTempS(string key);
void releaseTemp(string key);

class Expression
{
	public:
		Expression(int line, int column){
				this->line = line;
				this->column = column;
		}
		Expression(){}

		virtual ExpressionKind GetKind() = 0;
		virtual ResultValue Evaluate() = 0;
		virtual string ToString() = 0;
		virtual ResultValue GenerateCode() = 0;
		virtual bool ExecuteSemantic() = 0;

		int line, column;
		string place;
};

typedef list<Expression *> ExpressionList;

class BinaryExpression: public Expression
{
	public:
		BinaryExpression(Expression *expr1, Expression *expr2, ExpressionOperator oper, int line, int column): Expression(line, column)
		{
			this->expr1 = expr1;
			this->expr2 = expr2;
			this->oper = oper;
		}

		virtual ExpressionKind GetKind()
		{
			return ekBinary;
		}

		virtual ResultValue Evaluate();
		virtual string ToString();
		virtual ResultValue GenerateCode();
		virtual bool ExecuteSemantic();

		Expression *expr1;
		Expression *expr2;
		ExpressionOperator oper;
};

class UnaryExpression: public Expression
{
	public:
		UnaryExpression(Expression *expr, ExpressionOperator oper, int line, int column): Expression(line, column)
		{
			this->expr = expr;
			this->oper = oper;
		}

		~UnaryExpression()
		{
			if (expr != 0)
				delete expr;
		}

		virtual ExpressionKind GetKind()
		{
			return ekUnary;
		}

		virtual ResultValue Evaluate();
		virtual string ToString();
		virtual ResultValue GenerateCode();
		virtual bool ExecuteSemantic();

		Expression *expr;
		ExpressionOperator oper;
};

class LValueExpression: public Expression
{
	public:
		LValueExpression(string variable_name, Expression *array_index, int line, int column): Expression(line, column)
		{
			this->variable_name = variable_name;
			this->array_index = array_index;
		}

		~LValueExpression()
		{
			if (array_index != 0)
				delete array_index;
		}

		virtual ExpressionKind GetKind()
		{
			return ekLValue;
		}

		virtual ResultValue Evaluate();
		virtual string ToString();
		virtual ResultValue GenerateCode();
		virtual bool ExecuteSemantic();

		string variable_name;
		Expression *array_index;
};

class MethodCallExpression: public Expression
{
	public:
		MethodCallExpression(string method_name, ExpressionList *method_arguments, int line, int column): Expression(line, column)
		{
			this->method_name = method_name;
			this->method_arguments = method_arguments;
		}

		~MethodCallExpression()
		{
			if (method_arguments != 0) {
				FreeList(method_arguments);
				delete method_arguments;
			}
		}

		virtual ExpressionKind GetKind()
		{
			return ekMethodCall;
		}

		virtual ResultValue Evaluate();
		virtual string ToString();
		virtual ResultValue GenerateCode();
		virtual bool ExecuteSemantic();

		string method_name;
		ExpressionList *method_arguments;
};

class ConstantExpression: public Expression
{
	public:
		ConstantExpression(int value, int line, int column): Expression(line, column)
		{
			constant_type = Int;
			constant_value.int_value = value;
		}

		ConstantExpression(bool value, int line, int column): Expression(line, column)
		{
			constant_type = Boolean;
			constant_value.bool_value = value;
		}

		ConstantExpression(char *value, int line, int column): Expression(line, column)
		{
			constant_type = String;
			constant_value.string_value = strdup(value);
		}

		~ConstantExpression()
		{
			if (constant_type == String && constant_value.string_value != 0)
				free(constant_value.string_value);
		}

		virtual ExpressionKind GetKind() { return ekConstant; }

		virtual ResultValue Evaluate(); // DONE
		virtual string ToString();
		virtual ResultValue GenerateCode();
		virtual bool ExecuteSemantic();

		Type constant_type;
		union
		{
				int int_value;
				bool bool_value;
				char *string_value;
		} constant_value;
};


#endif /* EXPRESSION_H_ */
